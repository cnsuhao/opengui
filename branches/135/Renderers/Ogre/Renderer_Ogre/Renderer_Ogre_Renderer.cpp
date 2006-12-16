// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

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
	// Constants for buffer management control
	// Sizes are in vertices. Values should ideally be divisible by 3 (since we work in triangle lists)
	const size_t BUFFER_SIZE_INITIAL = 6; // just the cursor alone takes 2 polygons minimum
	const size_t BUFFER_SIZE_MAX = 1536; // 1536(vertices) = 3(points) * 512(triangles)
	/* Note: BUFFER_SIZE_MAX is a SOFT LIMIT
	It is the maximum buffer growth size to use to promote batch combining. However, if a single
	batch comes along that is larger than BUFFER_SIZE_MAX all by itself, this limit will be broken.
	The soft limit is enforced in such a way that the buffer size will not willingly grow beyond
	the specified limit. It will grow to fill the needs of the largest overflowing batch, and will
	utilize this newfound space to further batch other operations, but it will not grow to attempt
	to batch an overflowing batch with other non-overflowing batches. If such combining is possible
	without buffer growth, it will be performed, but otherwise a new batch will be started to
	contain the overflowing batch.
	*/

//OgreFrameListener implementation
	//#####################################################################
	OgreFrameListener::OgreFrameListener( OgreRenderer* renderer ) {
		mRenderer = renderer;
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
	bool OgreFrameListener::frameEnded( const Ogre::FrameEvent& evt ) {
		mRenderer->reclaimBufferMemory();
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
		mOgreFrameListener = new OgreFrameListener( this );
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

		// set up buffer and tracking variables
		m_HWBufferSize = 0;
		m_HWBufferUsage = 0;
		m_HWBuffer_MaxUsageThisFrame = 0;
		m_HWBufferPtr = 0;
		_setupHardwareBuffer( BUFFER_SIZE_INITIAL );
	}
	//#####################################################################
	OgreRenderer::~OgreRenderer() {
		_teardownHardwareBuffer();
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

		// set initial viewport and rendering context
		mRenderSystem->_setViewport( mCurrentViewport->getOgreViewport() );
		mCurrentContext = 0;
		mViewportPixelShift.x = mTexelOffset.x / ( float )( mCurrentViewport->getOgreViewport()->getActualWidth() / 2 );
		mViewportPixelShift.y = mTexelOffset.y / ( float )( mCurrentViewport->getOgreViewport()->getActualHeight() / 2 );

		// begin ogre frame, temporarily canceling any existing viewport clearing
		Ogre::Viewport* vp = mCurrentViewport->getOgreViewport();
		unsigned int clearedBuffers = vp->getClearBuffers();
		if ( clearedBuffers ) {
			vp->setClearEveryFrame( false );
			mRenderSystem->_beginFrame();
			vp->setClearEveryFrame( true, clearedBuffers );
		} else
			mRenderSystem->_beginFrame();

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
		mRenderSystem->_setTexture( 0, false, "" );
		mCurrentTextureState_Texture = 0;
		mCurrentTextureState_Mask = 0;
		mTextureUVScale.x = 1.0f;
		mTextureUVScale.y = 1.0f;

		// enable alpha blending
		mRenderSystem->_setSceneBlending( SBF_SOURCE_ALPHA, SBF_ONE_MINUS_SOURCE_ALPHA );
	}
	//#####################################################################
	void OgreRenderer::postRenderCleanup() {
		// finish up any remaining render operations
		safeExecuteBuffer();

		mRenderSystem->_endFrame();
		mInRender = false;
		//we'll let everyone else fend for themselves after we've finished making a mess of things
	}
	//#####################################################################
	void OgreRenderer::_setTextureState( OgreTexture* texture, OgreTexture* mask ) {
		if ( texture ) {
			mRenderSystem->_setTextureBlendMode( 0, mColorBlendMode );
			mRenderSystem->_setTextureBlendMode( 0, mAlphaBlendMode );
			mRenderSystem->_setTexture( 0, // texture unit id
										true, //enable texture
										texture->getOgreTextureName() );
			texture->getOgreUVScale( mTextureUVScale.x, mTextureUVScale.y );
		} else {
			mTextureUVScale.x = 1.0f;
			mTextureUVScale.y = 1.0f;
			mRenderSystem->_disableTextureUnit( 0 );
		}
	}
	//#####################################################################
	void OgreRenderer::doRenderOperation( RenderOperation& renderOp ) {
		if ( !renderOp.triangleList || renderOp.triangleList->size() == 0 ) return; //skip if no triangles to render

		// update texture state
		safeSetTextureState( renderOp.texture.get(), renderOp.mask.get() );

		// add render operations to buffer
		TriangleList& triList = *( renderOp.triangleList );
		safeAppendBuffer( triList );
	}
	//#####################################################################
	void OgreRenderer::safeExecuteBuffer() {
		if ( !m_HWBufferUsage ) return; // abort if nothing to do

		// otherwise update usage stats and execute the buffer
		if ( m_HWBufferUsage > m_HWBuffer_MaxUsageThisFrame )
			m_HWBuffer_MaxUsageThisFrame = m_HWBufferUsage;
		_executeBuffer();
	}
	//#####################################################################
	void OgreRenderer::safeSetTextureState( Texture* texture, Texture* mask ) {
		// abort if the needed texture state == current texture state
		if ( mCurrentTextureState_Texture == texture && mCurrentTextureState_Mask == mask )
			return;

		safeExecuteBuffer(); // execute any operations using the old texture state

		//set texture state (this polymorphism madness is brought to you by the letter F)
		OgreTexture* ogreTexture = 0;
		OgreTexture* ogreMask = 0;

		if ( texture )
			if ( texture->isRenderTexture() )
				ogreTexture = static_cast<OgreTexture*>( static_cast<OgreRenderTexture*>( texture ) );
			else
				ogreTexture = static_cast<OgreTexture*>( static_cast<OgreStaticTexture*>( texture ) );


		if ( mask )
			if ( mask->isRenderTexture() )
				ogreMask = static_cast<OgreTexture*>( static_cast<OgreRenderTexture*>( mask ) );
			else
				ogreMask = static_cast<OgreTexture*>( static_cast<OgreStaticTexture*>( mask ) );

		mCurrentTextureState_Texture = texture;
		mCurrentTextureState_Mask = mask;
		_setTextureState( ogreTexture, ogreMask );
	}
	//#####################################################################
	void OgreRenderer::reclaimBufferMemory() {
		if ( mInRender || m_HWBufferPtr )
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "Cannot reclaim buffer memory during draw operations", __FUNCTION__ );
		if ( m_HWBufferSize > BUFFER_SIZE_INITIAL && m_HWBufferSize / 2 > m_HWBuffer_MaxUsageThisFrame ) {
			size_t newSize = m_HWBufferSize / 2;
			if ( newSize < BUFFER_SIZE_INITIAL )
				newSize = BUFFER_SIZE_INITIAL;
			_resizeHardwareBuffer( newSize );
		}
		m_HWBuffer_MaxUsageThisFrame = 0;
	}
	//#####################################################################
	void OgreRenderer::safeAppendBuffer( TriangleList& triList ) {
		/**/
		size_t neededSpace = triList.size() * 3; // we know there are 3 vertices for each triangle
		size_t remainingSpace = m_HWBufferSize - m_HWBufferUsage;

		// if it fits in the available buffer: stick it in there and return
		if ( remainingSpace >= neededSpace ) {
			_appendBuffer( triList );
			return;
		}
		//otherwise we need to do some leg work... as follows below

		// do we need to break soft limit to perform this batch at all?
		if ( BUFFER_SIZE_MAX < neededSpace ) {
			// do we need to force a resize of the buffer to fit?
			if ( m_HWBufferSize < neededSpace ) {
				safeExecuteBuffer(); // flush what we have, we're going to be resizing
				_resizeHardwareBuffer( neededSpace );
				_appendBuffer( triList );
				m_HWBuffer_MaxUsageThisFrame = neededSpace;
				safeExecuteBuffer(); // run the new batch immediately to make room for the next batch
			} else {
				safeExecuteBuffer(); // flush what we have, we need the space
				_appendBuffer( triList ); // send batch contents into the buffer
			}
			return; // we're done, return
		}

		//would a resize break the max buffer limit?
		if ( BUFFER_SIZE_MAX <= m_HWBufferSize ) {
			// if so, all we can do is flush the buffer for the room, append, and continue
			safeExecuteBuffer(); // flush what we have, we need the space
			_appendBuffer( triList ); // send batch contents into the buffer
			return;
		}

		// if we reach this point, a buffer resize is in order
		size_t newBufferSize;
		if ( BUFFER_SIZE_MAX / 2 <= m_HWBufferSize ) // test for final growth size
			newBufferSize = BUFFER_SIZE_MAX;// final resize means we just jump right to max buffer size
		else {
			// otherwise double the buffer until we can fit what we need
			newBufferSize = m_HWBufferSize;
			while ( newBufferSize - m_HWBufferUsage < neededSpace ) //(this usually only takes 1 iteration)
				newBufferSize *= 2;
			if ( newBufferSize > BUFFER_SIZE_MAX ) //paranoia test
				newBufferSize = BUFFER_SIZE_MAX;
		}

		safeExecuteBuffer(); // flush the current contents
		_resizeHardwareBuffer( newBufferSize ); // resize the buffer
		_appendBuffer( triList ); // send batch contents into the buffer

		// we prevent downsizing for at least 1 frame
		if ( m_HWBuffer_MaxUsageThisFrame < newBufferSize )
			m_HWBuffer_MaxUsageThisFrame = newBufferSize;
	}
	//#####################################################################
	void OgreRenderer::_appendBuffer( TriangleList& triList ) {
		if ( !m_HWBufferPtr ) // lock the buffer if we haven't already
			m_HWBufferPtr = ( PolyVertex* )mVertexBuffer->lock ( Ogre::HardwareVertexBuffer::HBL_DISCARD );

		PolyVertex*	hwbuffer_start = m_HWBufferPtr + m_HWBufferUsage;
		PolyVertex*	hwbuffer = hwbuffer_start; // starting point is here

		size_t vertexCount = 0; // holds the number of vertices we iterate across

		TriangleList::iterator iter, iterend = triList.end();
		for ( iter = triList.begin(); iter != iterend; iter++ ) {
			Triangle& tri = ( *iter );
			for ( unsigned int i = 0; i < 3; i++ ) { // compiler will probably unroll this loop
				vertexCount++; // increment vertex counter for later

				// store vertex position data
				hwbuffer[i].x = (( tri.vertex[i].position.x * 2 ) - 1.0f ) + mViewportPixelShift.x;
				hwbuffer[i].y = (( tri.vertex[i].position.y * 2 ) - 1.0f ) - mViewportPixelShift.y;
				if ( !mCurrentContext )
					hwbuffer[i].y *= -1;
				hwbuffer[i].z = 0.0f; // we don't deal in Z, so it's always 0

				// store the color value
				mRenderSystem->convertColourValue(
					Ogre::ColourValue(	tri.vertex[i].color.Red,
									   tri.vertex[i].color.Green,
									   tri.vertex[i].color.Blue,
									   tri.vertex[i].color.Alpha ),
					&( hwbuffer[i].color )
				);

				// store UVs
				hwbuffer[i].u = tri.vertex[i].textureUV.x * mTextureUVScale.x;
				hwbuffer[i].v = tri.vertex[i].textureUV.y * mTextureUVScale.y;
			}

			hwbuffer += 3; // advance to next polygon
		}

		m_HWBufferUsage += vertexCount; // store new buffer usage data

		//DEBUG
		//safeExecuteBuffer();
	}
	//#####################################################################
	void OgreRenderer::_executeBuffer() {
		if ( m_HWBufferPtr ) { // unlock the buffer if it's locked
			mVertexBuffer->unlock();
			m_HWBufferPtr = 0;
		}

		// execute
		mRenderOperation.vertexData->vertexCount = m_HWBufferUsage;
		mRenderSystem->_render( mRenderOperation ); //render it
		m_HWBufferUsage = 0;
	}
	//#####################################################################
	void OgreRenderer::_setupHardwareBuffer( size_t numVerts ) {
		using namespace Ogre;

		mRenderOperation.vertexData = new VertexData;
		mRenderOperation.vertexData->vertexStart = 0;

		VertexDeclaration* vd = mRenderOperation.vertexData->vertexDeclaration;
		size_t vd_offset = 0;
		vd->addElement( 0, vd_offset, VET_FLOAT3, VES_POSITION ); // 12 bytes = 4 bytes per vertex * 3 vertices
		vd_offset += VertexElement::getTypeSize( VET_FLOAT3 );
		vd->addElement( 0, vd_offset, VET_COLOUR, VES_DIFFUSE ); // 4 bytes = 8 bits per channel (1byte) * 4 channels
		vd_offset += VertexElement::getTypeSize( VET_COLOUR );
		vd->addElement( 0, vd_offset, VET_FLOAT2, VES_TEXTURE_COORDINATES ); // 8 bytes = 4 bytes per float * 2 floats (U & V)
		// total estimated size is 24 bytes per vertex

		mVertexBuffer = HardwareBufferManager::getSingleton().createVertexBuffer(
							vd->getVertexSize( 0 ), //vertexes are <= this => big
							numVerts, // use the calculated size we were given
							HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE, //throw it away, I don't care
							false ); //shadow buffers are for Ninnies

		mRenderOperation.vertexData->vertexBufferBinding->setBinding( 0, mVertexBuffer ); // one ring to bind them...

		mRenderOperation.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
		mRenderOperation.useIndexes = false; // I like to do it the hard way

		m_HWBufferSize = numVerts; // store the size
	}
	//#####################################################################
	void OgreRenderer::_teardownHardwareBuffer() {
		delete mRenderOperation.vertexData;
		mRenderOperation.vertexData = 0;
		mVertexBuffer.setNull();
	}
	//#####################################################################
	void OgreRenderer::_resizeHardwareBuffer( size_t numVerts ) {
		using namespace Ogre;

		VertexDeclaration* vd = mRenderOperation.vertexData->vertexDeclaration;
		mVertexBuffer = HardwareBufferManager::getSingleton().createVertexBuffer(
							vd->getVertexSize( 0 ), //vertexes are <= this => big
							numVerts, // use the calculated size we were given
							HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE, //throw it away, I don't care
							false ); //shadow buffers are for Ninnies

		mRenderOperation.vertexData->vertexBufferBinding->setBinding( 0, mVertexBuffer ); // one ring to bind them...

		m_HWBufferSize = numVerts; // store the size
	}
	//#####################################################################
	Texture* OgreRenderer::createTextureFromFile( const std::string &filename ) {
		if ( mInRender ) // need to flush the buffer because texture operations tend to mess with texture states
			safeExecuteBuffer();
		OgreStaticTexture* tex = new OgreStaticTexture();
		tex->loadFile( filename, mTextureResourceGroup );
		return tex;
	}
	//#####################################################################
	Texture* OgreRenderer::createTextureFromTextureData( const TextureData *textureData ) {
		if ( mInRender ) // need to flush the buffer because texture operations tend to mess with texture states
			safeExecuteBuffer();
		OgreStaticTexture* tex = new OgreStaticTexture();
		tex->loadFromTextureData( textureData, mTextureResourceGroup );
		return tex;
	}
	//#####################################################################
	Texture* OgreRenderer::createTextureFromOgreTexturePtr( Ogre::TexturePtr& texture ) {
		if ( mInRender ) // need to flush the buffer because texture operations tend to mess with texture states
			safeExecuteBuffer();
		OgreStaticTexture* tex = new OgreStaticTexture();
		tex->loadOgreTexture( texture );
		return tex;
	}
	//#####################################################################
	void OgreRenderer::updateTextureFromTextureData( Texture* texture, const TextureData *textureData ) {
		if ( mInRender ) // need to flush the buffer because texture operations tend to mess with texture states
			safeExecuteBuffer();
		if ( texture )
			static_cast<OgreStaticTexture*>( texture )->loadFromTextureData( textureData, mTextureResourceGroup );
	}
	//#####################################################################
	void OgreRenderer::destroyTexture( Texture* texturePtr ) {
		if ( mInRender ) // need to flush the buffer because texture operations tend to mess with texture states
			safeExecuteBuffer();
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
		if ( mCurrentContext == context ) return; // don't do anything if we don't need to

		safeExecuteBuffer(); // flush current buffer before we change targets
		safeSetTextureState( 0, 0 );

		if ( !context ) {
			mCurrentContext = 0;
			mRenderSystem->_setViewport( mCurrentViewport->getOgreViewport() );
			mViewportPixelShift.x = mTexelOffset.x / ( float )( mCurrentViewport->getOgreViewport()->getActualWidth() / 2 );
			mViewportPixelShift.y = mTexelOffset.y / ( float )( mCurrentViewport->getOgreViewport()->getActualHeight() / 2 );
		} else {
			OgreRenderTexture* rtex = static_cast<OgreRenderTexture*>( context );
			mCurrentContext = context;
			mRenderSystem->_setViewport( rtex->getOgreViewport() );
			mViewportPixelShift.x = mTexelOffset.x / ( float )( rtex->getOgreViewport()->getActualWidth() / 2 );
			mViewportPixelShift.y = mTexelOffset.y / ( float )( rtex->getOgreViewport()->getActualHeight() / 2 );
		}

		// fix what Ogre just broke ;)
		mRenderSystem->_setCullingMode( Ogre::CULL_NONE ); // _setViewport has a habit of turning culling back on
		mRenderSystem->_setProjectionMatrix( Ogre::Matrix4::IDENTITY ); // and it also likes to break the projection matrix :(
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
		if ( mInRender ) // need to flush the buffer because texture operations tend to mess with texture states
			safeExecuteBuffer();
		OgreRenderTexture* tex = new OgreRenderTexture( size );
		return tex;
	}
	//#####################################################################
	void OgreRenderer::destroyRenderTexture( RenderTexture *texturePtr ) {
		if ( mInRender ) // need to flush the buffer because texture operations tend to mess with texture states
			safeExecuteBuffer();
		if ( texturePtr )
			delete texturePtr;
	}
	//#####################################################################
}

