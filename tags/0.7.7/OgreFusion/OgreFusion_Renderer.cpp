// -----------------------------------------------------------------------------
// OgreFusion_Renderer.cpp
// -----------------------------------------------------------------------------

#include "OgreFusion_Renderer.h"
#include "OgreFusion_Texture.h"

//#include "Ogre.h"
#include <OgreRenderSystem.h>
#include <OgreRoot.h>
#include <OgreHardwareBufferManager.h>
#include <OgreRenderWindow.h>

namespace OpenGUI{
//OgreRenderQueueListener implementation
	//#####################################################################
	void OgreRenderQueueListener::renderQueueStarted(Ogre::uint8 id,
		const Ogre::String& invocation, bool& skipThisQueue)
	{
		if( (!mPostQueue) && (mQueueId == id) )
			System::getSingleton().renderGUI();
	}
	//#####################################################################
	void OgreRenderQueueListener::renderQueueEnded(Ogre::uint8 id,
		const Ogre::String& invocation, bool& repeatThisQueue)
	{
		if( (mPostQueue) && (mQueueId == id) )
			System::getSingleton().renderGUI();
	}
	//#####################################################################
	


//OgreRenderer implementation
	//#####################################################################
	OgreRenderer::OgreRenderer( Ogre::RenderWindow* ogreRenderWindow,
		Ogre::uint8 queueId, bool postQueue )
	{
		//call the initializer using NULL as the scene manager pointer
		initialize( ogreRenderWindow, 0, queueId, postQueue );
	}
	//#####################################################################
	OgreRenderer::OgreRenderer( Ogre::RenderWindow* ogreRenderWindow,
		Ogre::SceneManager* ogreSceneManager, Ogre::uint8 queueId, bool postQueue )
	{
		initialize( ogreRenderWindow, ogreSceneManager, queueId, postQueue );
	}
	//#####################################################################
	void OgreRenderer::initialize( Ogre::RenderWindow* ogreRenderWindow,
		Ogre::SceneManager* ogreSceneManager, Ogre::uint8 queueId, bool postQueue )
	{
		using namespace Ogre;
		mTextureResourceGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
		mSceneManager = 0; //this must be 0 right now, we'll attach later
		mQueueId = queueId;
		mOgreRoot = Root::getSingletonPtr();
		mRenderSystem = mOgreRoot->getRenderSystem();
		mRenderWindow = ogreRenderWindow;

		mQueueListener = new OgreRenderQueueListener(this, mQueueId, postQueue);

		//we use these every frame, so we'll set them up now to save time later
		mTextureAddressMode.u = TextureUnitState::TAM_WRAP;
		mTextureAddressMode.v = TextureUnitState::TAM_WRAP;
		mTextureAddressMode.w = TextureUnitState::TAM_WRAP;
		mColorBlendMode.blendType = Ogre::LBT_COLOUR;
		mColorBlendMode.source1 = Ogre::LBS_TEXTURE;
		mColorBlendMode.source2 = Ogre::LBS_DIFFUSE;
		mColorBlendMode.operation = Ogre::LBX_MODULATE;
		mAlphaBlendMode.blendType = Ogre::LBT_ALPHA;
		mAlphaBlendMode.source1 = Ogre::LBS_TEXTURE;
		mAlphaBlendMode.source2 = Ogre::LBS_DIFFUSE;
		mAlphaBlendMode.operation = Ogre::LBX_MODULATE;

		setupHardwareBuffer();

		//attach to the scene manager if we have a useful pointer
		if(ogreSceneManager)
			setSceneManager(ogreSceneManager);
	}
	//#####################################################################
	OgreRenderer::~OgreRenderer(){
		setSceneManager(0);
		delete mQueueListener;
		teardownHardwareBuffer();
	}
	//#####################################################################
	void OgreRenderer::setTextureResourceGroup(const std::string& ogreResourceGroup){
		mTextureResourceGroup = ogreResourceGroup;
	}
	//#####################################################################
	void OgreRenderer::setSceneManager(Ogre::SceneManager* sceneManager){
		if(mSceneManager){
			mSceneManager->removeRenderQueueListener(mQueueListener);
			mSceneManager = 0;
		}
		if(sceneManager){
			mSceneManager = sceneManager;
			mSceneManager->addRenderQueueListener(mQueueListener);
		}
	}
	//#####################################################################
	void OgreRenderer::setRenderQueue(Ogre::uint8 queueId, bool postQueue){
		mQueueId = queueId;
		if(mQueueListener){
			mQueueListener->setTargetRenderQueue(queueId);
			mQueueListener->setPostRenderQueue(postQueue);
		}
	}
	//#####################################################################
	void OgreRenderer::getViewportDimensions(IVector2& dims){
		dims.x = mRenderWindow->getWidth();
		dims.y = mRenderWindow->getHeight();

		/*
			since the pixel level texel offset only changes when the viewport size changes,
			this is the best place to perform updates to mTexelOffset
		*/
		mTexelOffset = FVector2(	mRenderSystem->getHorizontalTexelOffset(),
									mRenderSystem->getVerticalTexelOffset() );
		const float sceneWidth = 2;
		const float sceneHeight = 2;
		mTexelOffset.x = (sceneWidth / dims.x) * mTexelOffset.x;
		mTexelOffset.y = (sceneHeight / dims.y) * -mTexelOffset.y;
	}
	//#####################################################################
	void OgreRenderer::getScreenDimensions(IVector2& dims){
#if OPENGUI_PLATFORM == OPENGUI_PLATFORM_WIN32
		DEVMODE devMode;
		devMode.dmSize = sizeof(DEVMODE);
		devMode.dmDriverExtra = 0;
		BOOL ret = EnumDisplaySettings( NULL, ENUM_CURRENT_SETTINGS, &devMode);
		if(ret){
			mScreenDim.x = devMode.dmPelsWidth;
			mScreenDim.y = devMode.dmPelsHeight;
		}
		dims = mScreenDim;
#else
		//!\todo FIX ME! This is not the required action. Not sure what to do here for Linux. =/
		getViewportDimensions(dims); //this is a cheap hack, but it works for now
#endif
	}
	//#####################################################################
	void OgreRenderer::preRenderSetup(){
		using namespace Ogre;

		//if overlay rendering is turned off in the viewport, don't render
		if(!mRenderSystem->_getViewport()->getOverlaysEnabled()){
			mOverlayRenderEnabled = false;
			return;
		}

		mOverlayRenderEnabled = true;

		// set-up matrices
		mRenderSystem->_setWorldMatrix(Matrix4::IDENTITY);
		mRenderSystem->_setViewMatrix(Matrix4::IDENTITY);
		mRenderSystem->_setProjectionMatrix(Matrix4::IDENTITY);

		// initialise render settings
		mRenderSystem->setLightingEnabled(false);
		mRenderSystem->_setDepthBufferParams(false, false);
		mRenderSystem->_setCullingMode(CULL_NONE);
		mRenderSystem->_setFog(FOG_NONE);
		mRenderSystem->_setColourBufferWriteEnabled(true, true, true, true);
		mRenderSystem->unbindGpuProgram(GPT_FRAGMENT_PROGRAM);
		mRenderSystem->unbindGpuProgram(GPT_VERTEX_PROGRAM);
		mRenderSystem->setShadingType(SO_GOURAUD);
		mRenderSystem->_setPolygonMode(PM_SOLID);

		// initialise texture settings
		mRenderSystem->_setTextureCoordCalculation(0, TEXCALC_NONE);
		mRenderSystem->_setTextureCoordSet(0, 0);
		mRenderSystem->_setTextureUnitFiltering(0, FO_LINEAR, FO_LINEAR, FO_POINT);
		mRenderSystem->_setTextureAddressingMode(0, mTextureAddressMode);
		mRenderSystem->_setTextureMatrix(0, Matrix4::IDENTITY);
		mRenderSystem->_setAlphaRejectSettings(CMPF_ALWAYS_PASS, 0);
		
		mRenderSystem->_disableTextureUnitsFrom(1);
		mTexUnitDisabledLastPass[0] = true;
		mTexUnitDisabledLastPass[1] = true;

		// enable alpha blending
		mRenderSystem->_setSceneBlending(SBF_SOURCE_ALPHA, SBF_ONE_MINUS_SOURCE_ALPHA);
	}
	//#####################################################################
	void OgreRenderer::doRenderOperation(Render::RenderOperation& renderOp){
		if(!mOverlayRenderEnabled) return; //skip this until the overlays are turned on

		PolyVertex*	hwbuffer = (PolyVertex*)mVertexBuffer->lock(Ogre::HardwareVertexBuffer::HBL_DISCARD);

		//Would this be faster if this loop was expanded?
		for(unsigned int i=0; i<3; i++){
			//the simple math here corrects for the projection matrix and the texel offset
			hwbuffer[i].x = (renderOp.vertices[i].position.x * 2) - 1 + mTexelOffset.x;
			hwbuffer[i].y = (renderOp.vertices[i].position.y * -2) + 1 + mTexelOffset.y;

			hwbuffer[i].z = 0;
			mRenderSystem->convertColourValue(
				Ogre::ColourValue(	renderOp.vertices[i].color.Red,
									renderOp.vertices[i].color.Green,
									renderOp.vertices[i].color.Blue,
									renderOp.vertices[i].color.Alpha), 
				&(hwbuffer[i].color)
				);
			hwbuffer[i].u = renderOp.vertices[i].textureUV.x;
			hwbuffer[i].v = renderOp.vertices[i].textureUV.y;
		}
		

		mVertexBuffer->unlock();

		if(renderOp.texture && static_cast<OgreTexture*>(renderOp.texture)->validOgreTexture()){

			if(mTexUnitDisabledLastPass[0]){
				mRenderSystem->_setTextureBlendMode(0, mColorBlendMode);
				mRenderSystem->_setTextureBlendMode(0, mAlphaBlendMode);
				mTexUnitDisabledLastPass[0] = false;
			}

			mRenderSystem->_setTexture( 0, // texture unit id
										true, //enable texture
										static_cast<OgreTexture*>(renderOp.texture)->getOgreTextureName()); //ogre texture name
		}else{
			mTexUnitDisabledLastPass[0] = true;
			mTexUnitDisabledLastPass[1] = true;
			mRenderSystem->_setTexture( 0, // texture unit id
										false, //disable texture (temporary)
										""); //ogre texture name
		}
		mRenderOperation.vertexData->vertexCount = 3; //move this into buffer setup?
		mRenderSystem->_render(mRenderOperation); //render it
	}
	//#####################################################################
	void OgreRenderer::setupHardwareBuffer(){
		using namespace Ogre;
		
		mRenderOperation.vertexData = new VertexData;
		mRenderOperation.vertexData->vertexStart = 0;

		VertexDeclaration* vd = mRenderOperation.vertexData->vertexDeclaration;
		size_t vd_offset = 0;
		vd->addElement(0, vd_offset, VET_FLOAT3, VES_POSITION);
		vd_offset += VertexElement::getTypeSize(VET_FLOAT3);
		vd->addElement(0, vd_offset, VET_COLOUR, VES_DIFFUSE);
		vd_offset += VertexElement::getTypeSize(VET_COLOUR);
		vd->addElement(0, vd_offset, VET_FLOAT2, VES_TEXTURE_COORDINATES);

		mVertexBuffer = HardwareBufferManager::getSingleton().createVertexBuffer(
			vd->getVertexSize(0), //vertexes are <= this => big
			3, // 3 vertexes per polygon
			HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE, //throw it away, I don't care
			false); //shadow buffers are for Ninnies

		mRenderOperation.vertexData->vertexBufferBinding->setBinding(0, mVertexBuffer); // one ring to bind them...

		mRenderOperation.operationType = RenderOperation::OT_TRIANGLE_LIST;
		mRenderOperation.useIndexes = false; // I like to do it the hard way
	}
	//#####################################################################
	void OgreRenderer::teardownHardwareBuffer(){
		delete mRenderOperation.vertexData;
		mRenderOperation.vertexData = 0;
		mVertexBuffer.setNull();
	}
	//#####################################################################
	void OgreRenderer::postRenderCleanup(){
		//we'll let everyone else fend for themselves after we've finished making a mess of things
	}
	//#####################################################################
	Texture* OgreRenderer::createTextureFromFile(std::string filename){
		OgreTexture* tex = new OgreTexture();
		tex->loadFile(filename, mTextureResourceGroup);
		return tex;
	}
	//#####################################################################
	Texture* OgreRenderer::createTextureFromTextureData(TextureData *textureData){
		OgreTexture* tex = new OgreTexture();
		tex->loadFromTextureData(textureData, mTextureResourceGroup);
		return tex;
	}
	//#####################################################################
	Texture* OgreRenderer::createTextureFromOgreTexturePtr(Ogre::TexturePtr& texture){
		OgreTexture* tex = new OgreTexture();
		tex->loadOgreTexture(texture);
		return tex;
	}
	//#####################################################################
	void OgreRenderer::updateTextureFromTextureData(Texture* texture, TextureData *textureData){
		if(texture)
			static_cast<OgreTexture*>(texture)->loadFromTextureData(textureData, mTextureResourceGroup);
	}
	//#####################################################################
	void OgreRenderer::destroyTexture(Texture* texturePtr){
		if(texturePtr)
			delete texturePtr;
	}
	//#####################################################################
}

