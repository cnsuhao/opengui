// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef _H_RENDERER_OGRE_VIEWPORT_
#define _H_RENDERER_OGRE_VIEWPORT_

#include "Renderer_Ogre_Exports.h"

#include "OpenGUI.h"
#include "OgreViewport.h"
#include "OgreRenderTargetListener.h"


namespace OpenGUI {
	//! Implementation of OpenGUI::Viewport for use with the Ogre rendering engine.
	/*! This class provides the interconnect logic between Ogre::Viewport updates and
	OpenGUI::Screen updates and output targetting. After every refresh of the given
	Ogre::Viewport, this OpenGUI::Viewport implementation will iterate through all
	attached Screens and call Screen::update() for any Screen that is marked as auto
	updating.

	\note Due to Ogre's current lack of a true ViewportListener, this class cannot
	follow Ogre::Viewports that move between RenderTargets. To help remind you of this
	fact, upon detection that the watched Ogre::Viewport is being detached from the
	RenderTarget, an exception is thrown. Catching and disregarding this exception
	is legal, but the connection will be irrevocably broken, and updates to the Screens
	attached will cease to occur. It is recommended that you avoid this practice, and
	delete this Viewport object before detaching the Ogre::Viewport from its RenderTarget.

	*/
	class OGR_OGRE_API OgreViewport : public Ogre::RenderTargetListener, public Viewport {
	public:
		//! Constructor requires a pointer to a valid Ogre::Viewport that is attached to an Ogre::RenderTarget
		OgreViewport( Ogre::Viewport* ogreViewportPtr );
		//! destructor
		virtual ~OgreViewport();
		//! returns a pointer to the Ogre::Viewport this Viewport is rendering to
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
		virtual void preRenderTargetUpdate( const Ogre::RenderTargetEvent& evt );
		virtual void postRenderTargetUpdate( const Ogre::RenderTargetEvent& evt );
		virtual void preViewportUpdate( const Ogre::RenderTargetViewportEvent& evt );
		virtual void postViewportUpdate( const Ogre::RenderTargetViewportEvent& evt );
		virtual void viewportAdded( const Ogre::RenderTargetViewportEvent& evt );
		virtual void viewportRemoved( const Ogre::RenderTargetViewportEvent &evt );
	};

} // namespace OpenGUI {
#endif //_H_RENDERER_OGRE_VIEWPORT
