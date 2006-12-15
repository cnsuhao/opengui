// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

// -----------------------------------------------------------------------------
// Renderer_Ogre_Renderer.h
// -----------------------------------------------------------------------------

#ifndef	_H_OGR_OGRE_RENDERER
#define _H_OGR_OGRE_RENDERER

#include "Renderer_Ogre_Exports.h"

#include "OpenGUI.h"

#include "OgreRenderQueueListener.h"
#include "OgreSceneManagerEnumerator.h"
#include "OgreTextureUnitState.h"
#include "OgreFrameListener.h"

namespace OpenGUI {
	class OgreViewport; // forward declaration
	class OgreTexture; // forward declaration
	class OgreRenderer; // forward declaration

	//! FrameListener that updates OpenGUI timing every frame
	/*! An instance of this class is always created and managed by OgreRenderer.

	During the "frameStarted" event this class will update OpenGUI's internal
	timer via System::updateTime(), then inject time delta events into each
	Screen that is auto timing via ScreenManager::updateTime().

	Additionally, this object initiates automatic buffer reclamation processing
	at the end of frames via OgreRenderer::reclaimBufferMemory().

	This FrameListener will always return true, and should never cause unintended
	exiting from Ogre::Root::startRendering()
	*/
	class OGR_OGRE_API OgreFrameListener: public Ogre::FrameListener {
		friend class OgreRenderer;
	private:
		OgreFrameListener( OgreRenderer* renderer );
		virtual ~OgreFrameListener();
		OgreRenderer* mRenderer;
	public:
		//! performs the timing updates as specified in the class documentation
		virtual bool frameStarted( const Ogre::FrameEvent& evt );
		//! calls OgreRenderer::reclaimBufferMemory() once per frame
		virtual bool frameEnded( const Ogre::FrameEvent& evt );
	};

	//! %OpenGUI Renderer implementation that works with Ogre
	class OGR_OGRE_API OgreRenderer: public Renderer {
	public:

		//! Constructor.
		OgreRenderer( Ogre::Root* ogreRoot = 0, Ogre::RenderSystem* ogreRenderSystem = 0 );

		virtual ~OgreRenderer();

		//! Sets the resource group from which future textures will be loaded. Default is Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
		void setTextureResourceGroup( const std::string& ogreResourceGroup );
		//! Returns the current resource group that textures are loaded from
		const std::string& getTextureResourceGroup();

		//! This tests the batch buffer usage since the previous call to this function, and shortens it there is significant under utilization
		/*! Automatically called by the OgreFrameListener. You only need to call this if frame listeners are not being fired for some reason. */
		void reclaimBufferMemory();

		//! Create a texture from an existing Ogre::TexturePtr object.
		Texture* createTextureFromOgreTexturePtr( Ogre::TexturePtr& texture );

		//Standard OpenGUI Renderer functions
		virtual void selectViewport( Viewport* activeViewport ); //!< See Renderer documentation from %OpenGUI
		virtual void preRenderSetup(); //!< See Renderer documentation from %OpenGUI
		virtual void doRenderOperation( RenderOperation& renderOp ); //!< See Renderer documentation from %OpenGUI
		virtual void postRenderCleanup(); //!< See Renderer documentation from %OpenGUI
		virtual Texture* createTextureFromFile( const std::string& filename ); //!< See Renderer documentation from %OpenGUI
		virtual Texture* createTextureFromTextureData( const TextureData* textureData ); //!< See Renderer documentation from %OpenGUI
		virtual void updateTextureFromTextureData( Texture* texture, const TextureData *textureData ); //!< See Renderer documentation from %OpenGUI
		virtual void destroyTexture( Texture* texturePtr ); //!< See Renderer documentation from %OpenGUI

		//RTT support functions
		virtual bool supportsRenderToTexture();
		virtual void selectRenderContext( RenderTexture *context );
		virtual void clearContents();
		virtual RenderTexture* createRenderTexture( const IVector2 &size );
		virtual void destroyRenderTexture( RenderTexture *texturePtr );

	private:
		//NB: any function starting with in underscore in here does NOT perform sanity checks, simply doing what it is told


		// set up the given texture states
		void safeSetTextureState( Texture* texture, Texture* mask ); // changes the texture state if necessary, executing current buffer first if needed
		void _setTextureState( OgreTexture* texture, OgreTexture* mask );

		// frame listener for timing injections
		OgreFrameListener* mOgreFrameListener;

		//Ogre Specific
		Ogre::Root* mOgreRoot;
		Ogre::RenderSystem* mRenderSystem;
		std::string mTextureResourceGroup;
		FVector2 mTexelOffset; //holds the pixel level texel offset that needs to be applied to each vertex to maintain pixel alignment

		//Capabilities
		bool mSupportRTT; // render system supports render to texture
		bool mSupportNPOT; // render system supports non-power of 2 textures

		//Render State
		bool mInRender; // signifies within pre/post Render
		OgreViewport* mCurrentViewport; // current selected viewport
		RenderTexture* mCurrentContext; // current render target context
		FVector2 mTextureUVScale; // UV scales for current texture state
		Texture* mCurrentTextureState_Texture; // holds texture state for textures
		Texture* mCurrentTextureState_Mask; // holds texture state for masks

		//Cache Data
		Ogre::TextureUnitState::UVWAddressingMode mTextureAddressMode; //we cache this to save cpu time
		Ogre::LayerBlendModeEx mColorBlendMode; //we cache this to save cpu time
		Ogre::LayerBlendModeEx mAlphaBlendMode; //we cache this to save cpu time
		FVector2 mViewportPixelShift; // holds the pixel shift necessary for correcting pixel alignment in the current render context (value assumes 0.0 to 1.0 viewport size)

		// struct used to make accessing the Ogre VertexBuffer easier to follow/more efficient
		struct PolyVertex {
			float x, y, z;
			Ogre::RGBA color;
			float u, v;
		};

		// Hardware Buffer Management
		void _setupHardwareBuffer( size_t numVerts ); // create the buffer
		void _teardownHardwareBuffer(); // fully tear down the buffer
		void _resizeHardwareBuffer( size_t numVerts ); // resize the buffer to the given size
		Ogre::HardwareVertexBufferSharedPtr mVertexBuffer; //hardware buffer used for drawing
		Ogre::RenderOperation mRenderOperation; //reused for all draw operations
		size_t m_HWBufferSize; // the current size of the buffer in vertices
		size_t m_HWBufferUsage; // the current usage of the buffer in vertices
		size_t m_HWBuffer_MaxUsageThisFrame; // the maximum attempted usage of the buffer in vertices over the entire frame
		PolyVertex* m_HWBufferPtr; // holds a pointer to the current HW buffer when locked. 0 when there is no lock
		void _appendBuffer( TriangleList& triList ); //append the given contents to the buffer
		void _executeBuffer(); // execute the current buffer
		void safeExecuteBuffer(); // executes the current buffer only if it has data
		void safeAppendBuffer( TriangleList& triList ); //append the given contents to the buffer, executing the current buffer and resizing if necessary
	};
}//namespace OpenGUI{

#endif // _H_OGR_OGRE_RENDERER
