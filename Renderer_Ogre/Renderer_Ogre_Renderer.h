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

	//! FrameListener that updates OpenGUI timing every frame
	/*! An instance of this class is always created and managed by OgreRenderer.
	During the "frameStarted" event this class will update OpenGUI's internal
	timer via System::updateTime(), then inject time delta events into each
	Screen that is auto timing via ScreenManager::updateTime(). 
	
	*/
	class OGR_OGRE_API OgreFrameListener: public Ogre::FrameListener {
	public:
		OgreFrameListener();
		virtual ~OgreFrameListener();
		//! performs the timing updates as specified in the class documentation
		virtual bool frameStarted( const Ogre::FrameEvent& evt );
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
		void setupHardwareBuffer();
		void teardownHardwareBuffer();


		// set up the given texture states
		void setTextureState(OgreTexture* texture, OgreTexture* mask);


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
		

		Ogre::HardwareVertexBufferSharedPtr mVertexBuffer; //hardware buffer used for drawing
		Ogre::RenderOperation mRenderOperation; //reused for all draw operations

		Ogre::TextureUnitState::UVWAddressingMode mTextureAddressMode; //we cache this to save cpu time
		Ogre::LayerBlendModeEx mColorBlendMode; //we cache this to save cpu time
		Ogre::LayerBlendModeEx mAlphaBlendMode; //we cache this to save cpu time

		



		//! Struct used to make accessing the Ogre VertexBuffer easier to follow/more efficient
		struct PolyVertex {
			float x, y, z;
			Ogre::RGBA color;
			float u, v;
		};
	};
}//namespace OpenGUI{

#endif // _H_OGR_OGRE_RENDERER
