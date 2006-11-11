// -----------------------------------------------------------------------------
// Renderer_Ogre_Renderer.h
// -----------------------------------------------------------------------------

#ifndef	_H_OGR_OGRE_RENDERER
#define _H_OGR_OGRE_RENDERER

#include "Renderer_Ogre_Exports.h"

#include <OpenGUI.h>

#include <OgreRenderQueueListener.h>
#include <OgreSceneManagerEnumerator.h>
#include <OgreTextureUnitState.h>

namespace OpenGUI {
	class OgreRenderer; //forward declaration

	//! Used internally by Renderer_Ogre to hook into Ogre for automatic GUI rendering.
	/*! \note Not for application use, symbols not exported */
	class OgreRenderQueueListener : public Ogre::RenderQueueListener {
	public:
		OgreRenderQueueListener( OgreRenderer* renderer, Ogre::uint8 queueId, bool postQueue )
				: mRenderer( renderer ), mQueueId( queueId ), mPostQueue( postQueue ) {}

		virtual ~OgreRenderQueueListener() {}

		virtual void renderQueueStarted( Ogre::uint8 id, const Ogre::String& invocation, bool& skipThisQueue );
		virtual void renderQueueEnded( Ogre::uint8 id, const Ogre::String& invocation, bool& repeatThisQueue );

		void setTargetRenderQueue( Ogre::uint8 queueId ) {
			mQueueId = queueId;
		}
		void setPostRenderQueue( bool postQueue ) {
			mPostQueue = postQueue;
		}

	private:
		OgreRenderer* mRenderer;
		Ogre::uint8 mQueueId;
		bool mPostQueue;
	};


	//! %OpenGUI Renderer implementation that works with Ogre
	class OGR_OGRE_API OgreRenderer: public Renderer {
	public:

		//! Constructor. If you use this constructor, be sure you call OgreRenderer::setSceneManager() before rendering
		OgreRenderer( Ogre::RenderWindow* ogreRenderWindow,
					  Ogre::uint8 queueId = Ogre::RENDER_QUEUE_OVERLAY,
					  bool postQueue = false );

		//! Constructor
		OgreRenderer( Ogre::RenderWindow* ogreRenderWindow,
					  Ogre::SceneManager* ogreSceneManager,
					  Ogre::uint8 queueId = Ogre::RENDER_QUEUE_OVERLAY,
					  bool postQueue = false );

		virtual ~OgreRenderer();

		//! Attaches the GUI renderer to the given Ogre::SceneManager
		/* \note Passing NULL to this function is legal.
			\warning Only one SceneManager can be used at a time. Calling this
			will remove the previous SceneManager association. */
		void setSceneManager( Ogre::SceneManager* sceneManager );

		//! Sets the Ogre RenderQueue that the GUI will be renderer from
		void setRenderQueue( Ogre::uint8 queueId = Ogre::RENDER_QUEUE_OVERLAY, bool postQueue = false );

		//! Sets the resource group from which future textures will be loaded. Default is Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
		void setTextureResourceGroup( const std::string& ogreResourceGroup );

		//! Create a texture from an existing Ogre::TexturePtr object.
		Texture* createTextureFromOgreTexturePtr( Ogre::TexturePtr& texture );


		//Standard OpenGUI Renderer functions
		virtual void getViewportDimensions( IVector2& dims ); //!< See Renderer documentation from %OpenGUI
		virtual void getScreenDimensions( IVector2& dims ); //!< See Renderer documentation from %OpenGUI
		virtual void preRenderSetup(); //!< See Renderer documentation from %OpenGUI
		virtual void doRenderOperation( RenderOperation& renderOp ); //!< See Renderer documentation from %OpenGUI
		virtual void postRenderCleanup(); //!< See Renderer documentation from %OpenGUI
		virtual Texture* createTextureFromFile( std::string filename ); //!< See Renderer documentation from %OpenGUI
		virtual Texture* createTextureFromTextureData( TextureData *textureData ); //!< See Renderer documentation from %OpenGUI
		virtual void updateTextureFromTextureData( Texture* texture, TextureData *textureData ); //!< See Renderer documentation from %OpenGUI
		virtual void destroyTexture( Texture* texturePtr ); //!< See Renderer documentation from %OpenGUI

	private:
		//constructor implementation
		void initialize( Ogre::RenderWindow* ogreRenderWindow,
						 Ogre::SceneManager* ogreSceneManager, Ogre::uint8 queueId,
						 bool postQueue );
		void setupHardwareBuffer();
		void teardownHardwareBuffer();

		Ogre::Root* mOgreRoot;
		Ogre::RenderSystem* mRenderSystem;
		Ogre::uint8 mQueueId;
		OgreRenderQueueListener* mQueueListener;
		Ogre::SceneManager* mSceneManager;
		Ogre::RenderWindow* mRenderWindow;
		Ogre::HardwareVertexBufferSharedPtr mVertexBuffer; //hardware buffer used for drawing
		Ogre::RenderOperation mRenderOperation; //reused for all draw operations
		bool mOverlayRenderEnabled;
		std::string mTextureResourceGroup;

		Ogre::TextureUnitState::UVWAddressingMode mTextureAddressMode; //we cache this to save cpu time
		Ogre::LayerBlendModeEx mColorBlendMode; //we cache this to save cpu time
		Ogre::LayerBlendModeEx mAlphaBlendMode; //we cache this to save cpu time

		// This is used to store and test if a particular texture unit was disabled in the last pass.
		// We need to know this so we can reset that unit's blending settings before we use it
		bool mTexUnitDisabledLastPass[2];

		IVector2 mScreenDim; //last stored screen dimensions
		FVector2 mTexelOffset; //holds the pixel level texel offset that needs to be applied to each vertex to maintain pixel alignment

		//! Struct used to make accessing the Ogre VertexBuffer easier to follow/more efficient
		struct PolyVertex {
			float x, y, z;
			Ogre::RGBA color;
			float u, v;
		};
	};
}//namespace OpenGUI{

#endif // _H_OGR_OGRE_RENDERER
