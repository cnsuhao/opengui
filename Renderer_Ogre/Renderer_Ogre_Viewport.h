#ifndef _H_RENDERER_OGRE_VIEWPORT_
#define _H_RENDERER_OGRE_VIEWPORT_

#include "Renderer_Ogre_Exports.h"

#include <OpenGUI.h>
#include "OgreViewport.h"
#include "OgreRenderTargetListener.h"


namespace OpenGUI {
	//! Implementation of OpenGUI::Viewport for use with the Ogre rendering engine.
	/*!
	*/
	class OGR_OGRE_API OgreViewport : public Ogre::RenderTargetListener, public Viewport {
	public:
		//! 
		OgreViewport( Ogre::Viewport* ogreViewportPtr );
		virtual ~OgreViewport();
		Ogre::Viewport* getOgreViewport();

	private:
		Ogre::Viewport* mOgreViewport;
		Ogre::RenderTarget* mOgreRenderTarget;

	// OpenGUI::Viewport methods //
	public:
		virtual const IVector2& getSize();
	protected:
		virtual void preUpdate( Screen* updatingScreen );
		virtual void postUpdate( Screen* updatingScreen );
		virtual void screenAttached( Screen* attachingScreen );
		virtual void screenDetached( Screen* detachingScreen );

	// Ogre::RenderTargetListener methods //
	public:
		virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
		virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
		virtual void preViewportUpdate(const Ogre::RenderTargetViewportEvent& evt);
		virtual void postViewportUpdate(const Ogre::RenderTargetViewportEvent& evt);
		virtual void viewportAdded(const Ogre::RenderTargetViewportEvent& evt);
		virtual void viewportRemoved(const Ogre::RenderTargetViewportEvent &evt);
	};

} // namespace OpenGUI {
#endif //_H_RENDERER_OGRE_VIEWPORT
