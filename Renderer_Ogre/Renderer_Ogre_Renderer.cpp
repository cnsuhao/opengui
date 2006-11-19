// -----------------------------------------------------------------------------
// Renderer_Ogre_Renderer.cpp
// -----------------------------------------------------------------------------

#include "Renderer_Ogre_Renderer.h"
#include "Renderer_Ogre_Texture.h"
#include "Renderer_Ogre_Viewport.h"

//#include "Ogre.h"
#include "OgreRenderSystem.h"
#include "OgreRoot.h"
#include "OgreHardwareBufferManager.h"
#include "OgreRenderWindow.h"

namespace OpenGUI {
//OgreFrameListener implementation
	//#####################################################################
	OgreFrameListener::OgreFrameListener() {
		/* no action required */
	}
	//#####################################################################
	OgreFrameListener::~OgreFrameListener() {
		/* no action required */
	}
	//#####################################################################
	/*! \note Because it is possible to have an OgreRenderer instance (containing
	an OgreFrameListener instance) without a complimenting OpenGUI::System,
	this automatic update process performs safety checks to ensure that each
	used Singleton exists before making the updates. */
	bool OgreFrameListener::frameStarted( const Ogre::FrameEvent& evt ) {
		System* system = System::getSingletonPtr();
		if ( system ) {
			system->updateTime();
			ScreenManager* sm = ScreenManager::getSingletonPtr();
			if ( sm ) {
				sm->updateTime();
			}
		}
		return true;
	}
	//#####################################################################


//OgreRenderer implementation
	//#####################################################################
	OgreRenderer::OgreRenderer( Ogre::Root* ogreRoot, Ogre::RenderSystem* ogreRenderSystem ) {
		using namespace Ogre;
		mTextureResourceGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
		mOgreRoot = ogreRoot;
		mRenderSystem = ogreRenderSystem;
		if ( !mOgreRoot )
			mOgreRoot = Root::getSingletonPtr();
		if ( !mOgreRoot )
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "Could not obtain Ogre::Root", __FUNCTION__ );
		if ( !mRenderSystem )
			mRenderSystem = mOgreRoot->getRenderSystem();
		if ( !mRenderSystem )
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "Could not obtain Ogre::RenderSystem", __FUNCTION__ );

		// set up initial values
		mInRender = false;
		mCurrentViewport = 0;
		mCurrentContext = 0;

		// attach frame listener for timing updates
		mOgreFrameListener = new OgreFrameListener();
		mOgreRoot->addFrameListener( mOgreFrameListener );

		// get capabilities
		const RenderSystemCapabilities* caps = mRenderSystem->getCapabilities();
		mSupportRTT = caps->hasCapability( RSC_HWRENDER_TO_TEXTURE );
		mSupportNPOT = caps->hasCapability( RSC_NON_POWER_OF_2_TEXTURES );

		// get pixel alignment offset
		mTexelOffset.x = mRenderSystem->getHorizontalTexelOffset();
		mTexelOffset.y = mRenderSystem->getVerticalTexelOffset();

		//we use these every frame, so we'll set them up now to save time later
		mTextureAddressMode.u = TextureUnitState::TAM_CLAMP;
		mTextureAddressMode.v = TextureUnitState::TAM_CLAMP;
		mTextureAddressMode.w = TextureUnitState::TAM_CLAMP;
		mColorBlendMode.blendType = Ogre::LBT_COLOUR;
		mColorBlendMode.source1 = Ogre::LBS_TEXTURE;
		mColorBlendMode.source2 = Ogre::LBS_DIFFUSE;
		mColorBlendMode.operation = Ogre::LBX_MODULATE;
		mAlphaBlendMode.blendType = Ogre::LBT_ALPHA;
		mAlphaBlendMode.source1 = Ogre::LBS_TEXTURE;
		mAlphaBlendMode.source2 = Ogre::LBS_DIFFUSE;
		mAlphaBlendMode.operation = Ogre::LBX_MODULATE;

		setupHardwareBuffer();
	}
	//#####################################################################
	OgreRenderer::~OgreRenderer() {
		teardownHardwareBuffer();
		if ( mOgreFrameListener ) {
			mOgreRoot->removeFrameListener( mOgreFrameListener );
			delete mOgreFrameListener;
		}
	}
	//#####################################################################
	void OgreRenderer::setTextureResourceGroup( const std::string& ogreResourceGroup ) {
		mTextureResourceGroup = ogreResourceGroup;
	}
	//#####################################################################
	const std::string& OgreRenderer::getTextureResourceGroup() {
		return mTextureResourceGroup;
	}
	//#####################################################################

	//#####################################################################
	void OgreRenderer::selectViewport( Viewport* activeViewport ) {
		if ( mInRender )
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "Cannot change selected Viewport within render block", __FUNCTION__ );
		if ( !activeViewport )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Invalid Viewport selected: 0", __FUNCTION__ );
		mCurrentViewport = static_cast<OgreViewport*>( activeViewport );
	}
	//#####################################################################
	void OgreRenderer::preRenderSetup() {
		using namespace Ogre;
		mInRender = true;

		// set-up matrices
		mRenderSystem->_setWorldMatrix( Matrix4::IDENTITY );
		mRenderSystem->_setViewMatrix( Matrix4::IDENTITY );
		mRenderSystem->_setProjectionMatrix( Matrix4::IDENTITY );

		// initialize render settings
		mRenderSystem->setLightingEnabled( false );
		mRenderSystem->_setDepthBufferParams( false, false );
		mRenderSystem->_setCullingMode( CULL_NONE );
		mRenderSystem->_setFog( FOG_NONE );
		mRenderSystem->_setColourBufferWriteEnabled( true, true, true, true );
		mRenderSystem->unbindGpuProgram( GPT_FRAGMENT_PROGRAM );
		mRenderSystem->unbindGpuProgram( GPT_VERTEX_PROGRAM );
		mRenderSystem->setShadingType( SO_GOURAUD );
		mRenderSystem->_setPolygonMode( PM_SOLID );

		// initialize texture settings
		mRenderSystem->_setTextureCoordCalculation( 0, TEXCALC_NONE );
		mRenderSystem->_setTextureCoordSet( 0, 0 );
		mRenderSystem->_setTextureUnitFiltering( 0, FO_LINEAR, FO_LINEAR, FO_POINT );
		mRenderSystem->_setTextureAddressingMode( 0, mTextureAddressMode );
		mRenderSystem->_setTextureMatrix( 0, Matrix4::IDENTITY );
		mRenderSystem->_setAlphaRejectSettings( CMPF_ALWAYS_PASS, 0 );

		mRenderSystem->_disableTextureUnitsFrom( 0 ); // disable ALL current texture units

		// enable alpha blending
		mRenderSystem->_setSceneBlending( SBF_SOURCE_ALPHA, SBF_ONE_MINUS_SOURCE_ALPHA );

		mRenderSystem->_setViewport( mCurrentViewport->getOgreViewport() );
	}
	//#####################################################################
	void OgreRenderer::postRenderCleanup() {
		mInRender = false;
		//we'll let everyone else fend for themselves after we've finished making a mess of things
	}
	//#####################################################################
	void OgreRenderer::setTextureState( OgreTexture* texture, OgreTexture* mask ) {
		if ( texture ) {
			mRenderSystem->_setTextureBlendMode( 0, mColorBlendMode );
			mRenderSystem->_setTextureBlendMode( 0, mAlphaBlendMode );
			mRenderSystem->_setTexture( 0, // texture unit id
										true, //enable texture
										texture->getOgreTextureName() );
		} else {
// 			mRenderSystem->_setTexture( 0, // texture unit id
// 				false, //disable texture (temporary)
// 				"" ); //ogre texture name
			mRenderSystem->_disableTextureUnit( 0 );
		}
	}
	//#####################################################################
	void OgreRenderer::doRenderOperation( RenderOperation& renderOp ) {
		if ( !renderOp.triangleList || renderOp.triangleList->size() == 0 ) return; //skip if no triangles to render

		//set texture state (this polymorphism madness is brought to you by the letter F)
		OgreTexture* texture = 0;
		OgreTexture* mask = 0;
		Texture* tmpTex;
		tmpTex = renderOp.texture.get();
		if ( tmpTex )
			if ( tmpTex->isRenderTexture() )
				texture = static_cast<OgreTexture*>( static_cast<OgreRenderTexture*>( tmpTex ) );
			else
				texture = static_cast<OgreTexture*>( static_cast<OgreStaticTexture*>( tmpTex ) );
		tmpTex = renderOp.mask.get();
		if ( tmpTex )
			if ( tmpTex->isRenderTexture() )
				mask = static_cast<OgreTexture*>( static_cast<OgreRenderTexture*>( tmpTex ) );
			else
				mask = static_cast<OgreTexture*>( static_cast<OgreStaticTexture*>( tmpTex ) );
		setTextureState( texture, mask );


		TriangleList& triList = *( renderOp.triangleList );


		//*** for each triangle, update the buffers and render ***
		for ( TriangleList::iterator iter = triList.begin(); iter != triList.end();iter++ ) {
			Triangle& tri = ( *iter );

			PolyVertex*	hwbuffer = ( PolyVertex* )mVertexBuffer->lock ( Ogre::HardwareVertexBuffer::HBL_DISCARD );

			//Would this be faster if this loop was expanded?
			for ( unsigned int i = 0; i < 3; i++ ) {
				//the simple math here corrects for the projection matrix and the texel offset
				hwbuffer[i].x = ( tri.vertex[i].position.x * 2 ) - 1 + mTexelOffset.x;
				hwbuffer[i].y = ( tri.vertex[i].position.y * -2 ) + 1 + mTexelOffset.y;

				hwbuffer[i].z = 0;
				mRenderSystem->convertColourValue(
					Ogre::ColourValue(	tri.vertex[i].color.Red,
									   tri.vertex[i].color.Green,
									   tri.vertex[i].color.Blue,
									   tri.vertex[i].color.Alpha ),
					&( hwbuffer[i].color )
				);
				hwbuffer[i].u = tri.vertex[i].textureUV.x;
				hwbuffer[i].v = tri.vertex[i].textureUV.y;
			}

			mVertexBuffer->unlock();

			mRenderOperation.vertexData->vertexCount = 3; //move this into buffer setup?
			mRenderSystem->_render( mRenderOperation ); //render it
		}
	}
	//#####################################################################
	void OgreRenderer::setupHardwareBuffer() {
		using namespace Ogre;

		mRenderOperation.vertexData = new VertexData;
		mRenderOperation.vertexData->vertexStart = 0;

		VertexDeclaration* vd = mRenderOperation.vertexData->vertexDeclaration;
		size_t vd_offset = 0;
		vd->addElement( 0, vd_offset, VET_FLOAT3, VES_POSITION );
		vd_offset += VertexElement::getTypeSize( VET_FLOAT3 );
		vd->addElement( 0, vd_offset, VET_COLOUR, VES_DIFFUSE );
		vd_offset += VertexElement::getTypeSize( VET_COLOUR );
		vd->addElement( 0, vd_offset, VET_FLOAT2, VES_TEXTURE_COORDINATES );

		mVertexBuffer = HardwareBufferManager::getSingleton().createVertexBuffer(
							vd->getVertexSize( 0 ), //vertexes are <= this => big
							3, // 3 vertexes per polygon
							HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE, //throw it away, I don't care
							false ); //shadow buffers are for Ninnies

		mRenderOperation.vertexData->vertexBufferBinding->setBinding( 0, mVertexBuffer ); // one ring to bind them...

		mRenderOperation.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
		mRenderOperation.useIndexes = false; // I like to do it the hard way
	}
	//#####################################################################
	void OgreRenderer::teardownHardwareBuffer() {
		delete mRenderOperation.vertexData;
		mRenderOperation.vertexData = 0;
		mVertexBuffer.setNull();
	}
	//#####################################################################
	Texture* OgreRenderer::createTextureFromFile( const std::string &filename ) {
		OgreStaticTexture* tex = new OgreStaticTexture();
		tex->loadFile( filename, mTextureResourceGroup );
		return tex;
	}
	//#####################################################################
	Texture* OgreRenderer::createTextureFromTextureData( const TextureData *textureData ) {
		OgreStaticTexture* tex = new OgreStaticTexture();
		tex->loadFromTextureData( textureData, mTextureResourceGroup );
		return tex;
	}
	//#####################################################################
	Texture* OgreRenderer::createTextureFromOgreTexturePtr( Ogre::TexturePtr& texture ) {
		OgreStaticTexture* tex = new OgreStaticTexture();
		tex->loadOgreTexture( texture );
		return tex;
	}
	//#####################################################################
	void OgreRenderer::updateTextureFromTextureData( Texture* texture, const TextureData *textureData ) {
		if ( texture )
			static_cast<OgreStaticTexture*>( texture )->loadFromTextureData( textureData, mTextureResourceGroup );
	}
	//#####################################################################
	void OgreRenderer::destroyTexture( Texture* texturePtr ) {
		if ( texturePtr )
			delete texturePtr;
	}
	//#####################################################################


	//#####################################################################
	//#####################################################################
	bool OgreRenderer::supportsRenderToTexture() {
		return mSupportRTT;
	}
	//#####################################################################
	void OgreRenderer::selectRenderContext( RenderTexture *context ) {
		if ( mCurrentContext == context ) return;
		if ( !context ) {
			mCurrentContext = 0;
			mRenderSystem->_setViewport( mCurrentViewport->getOgreViewport() );
		} else {
			OgreRenderTexture* rtex = static_cast<OgreRenderTexture*>( context );
			mCurrentContext = context;
			mRenderSystem->_setViewport( rtex->getOgreViewport() );
		}
	}
	//#####################################################################
	void OgreRenderer::clearContents() {
		if ( mCurrentContext != 0 ) {
			Ogre::ColourValue color = Ogre::ColourValue::ZERO;
			mRenderSystem->clearFrameBuffer(
				Ogre::FBT_COLOUR,
				color, // color
				0.0f, // depth
				0 // stencil
			);
		}
	}
	//#####################################################################
	RenderTexture* OgreRenderer::createRenderTexture( const IVector2 &size ) {
		OgreRenderTexture* tex = new OgreRenderTexture( size );
		return tex;
	}
	//#####################################################################
	void OgreRenderer::destroyRenderTexture( RenderTexture *texturePtr ) {
		if ( texturePtr )
			delete texturePtr;
	}
	//#####################################################################
}

