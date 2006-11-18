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


	//! %OpenGUI Renderer implementation that works with Ogre
	class OGR_OGRE_API OgreRenderer: public Renderer {
	public:

		//! Constructor.
		OgreRenderer( Ogre::Root* ogreRoot = 0, Ogre::RenderSystem* ogreRenderSystem = 0 );

		virtual ~OgreRenderer();

		//! Sets the resource group from which future textures will be loaded. Default is Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
		void setTextureResourceGroup( const std::string& ogreResourceGroup );

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

		//Ogre Specific
		Ogre::Root* mOgreRoot;
		Ogre::RenderSystem* mRenderSystem;
		std::string mTextureResourceGroup;
		FVector2 mTexelOffset; //holds the pixel level texel offset that needs to be applied to each vertex to maintain pixel alignment

		//Capabilities
		bool mSupportRTT; // render system supports render to texture
		bool mSupportNPOT; // render system supports non-power of 2 textures

		Ogre::HardwareVertexBufferSharedPtr mVertexBuffer; //hardware buffer used for drawing
		Ogre::RenderOperation mRenderOperation; //reused for all draw operations



		Ogre::TextureUnitState::UVWAddressingMode mTextureAddressMode; //we cache this to save cpu time
		Ogre::LayerBlendModeEx mColorBlendMode; //we cache this to save cpu time
		Ogre::LayerBlendModeEx mAlphaBlendMode; //we cache this to save cpu time

		// This is used to store and test if a particular texture unit was disabled in the last pass.
		// We need to know this so we can reset that unit's blending settings before we use it
		bool mTexUnitDisabledLastPass[2];

		

		//! Struct used to make accessing the Ogre VertexBuffer easier to follow/more efficient
		struct PolyVertex {
			float x, y, z;
			Ogre::RGBA color;
			float u, v;
		};
	};
}//namespace OpenGUI{

#endif // _H_OGR_OGRE_RENDERER
