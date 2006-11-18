// -----------------------------------------------------------------------------
// Renderer_Ogre_Renderer.cpp
// -----------------------------------------------------------------------------

#include "Renderer_Ogre_Renderer.h"
#include "Renderer_Ogre_Texture.h"

//#include "Ogre.h"
#include <OgreRenderSystem.h>
#include <OgreRoot.h>
#include <OgreHardwareBufferManager.h>
#include <OgreRenderWindow.h>

namespace OpenGUI {
//OgreRenderQueueListener implementation



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

		// get capabilities
		const RenderSystemCapabilities* caps = mRenderSystem->getCapabilities();
		mSupportRTT = caps->hasCapability( RSC_HWRENDER_TO_TEXTURE );
		mSupportNPOT = caps->hasCapability( RSC_NON_POWER_OF_2_TEXTURES );

		// get pixel alignment offset
		mTexelOffset.x = mRenderSystem->getHorizontalTexelOffset();
		mTexelOffset.y = mRenderSystem->getVerticalTexelOffset();

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
	}
	//#####################################################################
	OgreRenderer::~OgreRenderer() {
		teardownHardwareBuffer();
	}
	//#####################################################################
	void OgreRenderer::setTextureResourceGroup( const std::string& ogreResourceGroup ) {
		mTextureResourceGroup = ogreResourceGroup;
	}
	//#####################################################################

	//#####################################################################
	void OgreRenderer::selectViewport( Viewport* activeViewport ) {
		/**/
		OG_NYI;
	}
	//#####################################################################
	void OgreRenderer::preRenderSetup() {
		using namespace Ogre;

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

		mRenderSystem->_disableTextureUnitsFrom( 1 );
		mTexUnitDisabledLastPass[0] = true;
		mTexUnitDisabledLastPass[1] = true;

		// enable alpha blending
		mRenderSystem->_setSceneBlending( SBF_SOURCE_ALPHA, SBF_ONE_MINUS_SOURCE_ALPHA );
	}
	//#####################################################################
	void OgreRenderer::doRenderOperation( RenderOperation& renderOp ) {
		if ( !renderOp.triangleList || renderOp.triangleList->size() == 0 ) return; //skip if no triangles to render

		TriangleList& triList = *( renderOp.triangleList );


		if ( renderOp.texture && static_cast<OgreTexture*>( renderOp.texture.get() )->validOgreTexture() ) {

			if ( mTexUnitDisabledLastPass[0] ) {
				mRenderSystem->_setTextureBlendMode( 0, mColorBlendMode );
				mRenderSystem->_setTextureBlendMode( 0, mAlphaBlendMode );
				mTexUnitDisabledLastPass[0] = false;
			}

			mRenderSystem->_setTexture( 0, // texture unit id
										true, //enable texture
										static_cast<OgreTexture*>( renderOp.texture.get() )->getOgreTextureName() ); //ogre texture name
		} else {
			mTexUnitDisabledLastPass[0] = true;
			mTexUnitDisabledLastPass[1] = true;
			mRenderSystem->_setTexture( 0, // texture unit id
										false, //disable texture (temporary)
										"" ); //ogre texture name
		}


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
	void OgreRenderer::postRenderCleanup() {
		//we'll let everyone else fend for themselves after we've finished making a mess of things
	}
	//#####################################################################
	Texture* OgreRenderer::createTextureFromFile( const std::string &filename ) {
		OgreTexture* tex = new OgreTexture();
		tex->loadFile( filename, mTextureResourceGroup );
		return tex;
	}
	//#####################################################################
	Texture* OgreRenderer::createTextureFromTextureData( const TextureData *textureData ) {
		OgreTexture* tex = new OgreTexture();
		tex->loadFromTextureData( textureData, mTextureResourceGroup );
		return tex;
	}
	//#####################################################################
	Texture* OgreRenderer::createTextureFromOgreTexturePtr( Ogre::TexturePtr& texture ) {
		OgreTexture* tex = new OgreTexture();
		tex->loadOgreTexture( texture );
		return tex;
	}
	//#####################################################################
	void OgreRenderer::updateTextureFromTextureData( Texture* texture, const TextureData *textureData ) {
		if ( texture )
			static_cast<OgreTexture*>( texture )->loadFromTextureData( textureData, mTextureResourceGroup );
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
		OG_NYI;
	}
	//#####################################################################
	void OgreRenderer::clearContents() {
		OG_NYI;
	}
	//#####################################################################
	RenderTexture* OgreRenderer::createRenderTexture( const IVector2 &size ) {
		OG_NYI;
	}
	//#####################################################################
	void OgreRenderer::destroyRenderTexture( RenderTexture *texturePtr ) {
		OG_NYI;
	}
	//#####################################################################
}

