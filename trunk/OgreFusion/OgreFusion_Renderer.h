// -----------------------------------------------------------------------------
// OgreFusion_Renderer.h
// -----------------------------------------------------------------------------

#ifndef	_H_OGREFUSION_RENDERER
#define _H_OGREFUSION_RENDERER

#include "OgreFusion_Exports.h"

#include <OpenGUI.h>

#include <OgreRenderQueueListener.h>
#include <OgreSceneManagerEnumerator.h>
#include <OgreTextureUnitState.h>

namespace OpenGUI{
	class OgreRenderer; //forward declaration

	//! Used internally by OgreFusion to hook into Ogre for automatic GUI rendering.
	/*! \note Symbols not exported */
	class OgreRenderQueueListener : public Ogre::RenderQueueListener
	{
	public:
		OgreRenderQueueListener(OgreRenderer* renderer, Ogre::uint8 queueId, bool postQueue)
			:mRenderer(renderer), mQueueId(queueId), mPostQueue(postQueue) {}

		virtual ~OgreRenderQueueListener() {}

		virtual void renderQueueStarted(Ogre::uint8 id, const Ogre::String& invocation, bool& skipThisQueue);
		virtual void renderQueueEnded(Ogre::uint8 id, const Ogre::String& invocation, bool& repeatThisQueue);

		void setTargetRenderQueue(Ogre::uint8 queueId) {mQueueId = queueId; }
		void setPostRenderQueue(bool postQueue) { mPostQueue = postQueue; }

	private:
		OgreRenderer* mRenderer;
		Ogre::uint8 mQueueId;
		bool mPostQueue;
	};


	//! OpenGUI Renderer implementation that works with Ogre
	class OGREFUSION_API OgreRenderer: public Renderer
	{
	public:

		//! Constructor. If you use this constructor, be sure you call setSceneManager before rendering
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
		void setSceneManager(Ogre::SceneManager* sceneManager);

		//! Sets the Ogre RenderQueue that the GUI will be renderer from
		void setRenderQueue(Ogre::uint8 queueId = Ogre::RENDER_QUEUE_OVERLAY, bool postQueue = false);

		//! Sets the resource group from which future textures will be loaded. Default is Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
		void setTextureResourceGroup(const std::string& ogreResourceGroup);

		//! Create a texture from an existing Ogre::TexturePtr object.
		Texture* createTextureFromOgreTexturePtr(Ogre::TexturePtr& texture);


		//Standard OpenGUI Renderer functions
		virtual void getViewportDimensions(IVector2& dims);
		virtual void getScreenDimensions(IVector2& dims);
		virtual void preRenderSetup();
		virtual void doRenderOperation(Render::RenderOperation& renderOp);
		virtual void postRenderCleanup();
		virtual Texture* createTextureFromFile(std::string filename);
		virtual Texture* createTextureFromTextureData(TextureData *textureData);
		virtual void updateTextureFromTextureData(Texture* texture, TextureData *textureData);
		virtual void destroyTexture(Texture* texturePtr);

	private:
		//constructor implementation
		void initialize(Ogre::RenderWindow* ogreRenderWindow,
			Ogre::SceneManager* ogreSceneManager, Ogre::uint8 queueId,
			bool postQueue);
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

		IVector2 mScreenDim; //last stored screen dimensions


		struct PolyVertex{
			float x, y, z;
			Ogre::RGBA color;
			float u, v;
		};
	};
}//namespace OpenGUI{

#endif // _H_OGREFUSION_RENDERER
