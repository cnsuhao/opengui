#include "Renderer_Ogre_Viewport.h"
#include "OgreRenderTarget.h"

namespace OpenGUI {

	//#####################################################################
	OgreViewport::OgreViewport( Ogre::Viewport* ogreViewportPtr ) {
		mOgreViewport = ogreViewportPtr;
		if ( !mOgreViewport )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Invalid pointer to Ogre Viewport", __FUNCTION__ );

		mOgreRenderTarget = mOgreViewport->getTarget();
		if ( !mOgreRenderTarget ) // this test is required until Ogre adds true Viewport listeners
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Cannot create OpenGUI::OgreViewport from Ogre::Viewport that has no RenderTarget", __FUNCTION__ );

		mOgreRenderTarget->addListener( this );
	}
	//#####################################################################
	OgreViewport::~OgreViewport() {
		if ( mOgreRenderTarget )
			mOgreRenderTarget->removeListener( this );
	}
	//#####################################################################
	Ogre::Viewport* OgreViewport::getOgreViewport() {
		return mOgreViewport;
	}
	//#####################################################################

//////////////////////////////////////////////////////////////////////////
// OpenGUI::Viewport methods //
//////////////////////////////////////////////////////////////////////////
	const IVector2& OgreViewport::getSize() {
		if ( !mOgreViewport )
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "No attached Viewport to obtain size information", __FUNCTION__ );
		static IVector2 retval;
		retval.x = mOgreViewport->getActualWidth();
		retval.y = mOgreViewport->getActualHeight();
		return retval;
	}
	//#####################################################################
	void OgreViewport::preUpdate( Screen* updatingScreen ) {
		/* no operation */
	}
	//#####################################################################
	void OgreViewport::postUpdate( Screen* updatingScreen ) {
		/* no operation */
	}
	//#####################################################################
	void OgreViewport::screenAttached( Screen* attachingScreen ) {
		/* no operation */
	}
	//#####################################################################
	void OgreViewport::screenDetached( Screen* detachingScreen ) {
		/* no operation */
	}
	//#####################################################################

//////////////////////////////////////////////////////////////////////////
// Ogre::RenderTargetListener methods //
//////////////////////////////////////////////////////////////////////////
	void OgreViewport::preRenderTargetUpdate( const Ogre::RenderTargetEvent& evt ) {
		/* no operation */
	}
	//#####################################################################
	void OgreViewport::postRenderTargetUpdate( const Ogre::RenderTargetEvent& evt ) {
		/* no operation */
	}
	//#####################################################################
	void OgreViewport::preViewportUpdate( const Ogre::RenderTargetViewportEvent& evt ) {
		/* no operation */
	}
	//#####################################################################
	void OgreViewport::postViewportUpdate( const Ogre::RenderTargetViewportEvent& evt ) {
		// we only care about our particular viewport
		if ( mOgreViewport == evt.source && mOgreViewport->getOverlaysEnabled() ) {
			// iterate screens in order and update them
			const ScreenSet& screenSet = getScreenSet();
			ScreenSet::const_iterator iter = screenSet.begin();
			ScreenSet::const_iterator iterend = screenSet.end();
			for ( ;iter != iterend;iter++ ) {
				Screen* screen = ( *iter );
				if ( screen->isAutoUpdating() ) // only update screens that are auto updating
					screen->update();
			}
		}
	}
	//#####################################################################
	void OgreViewport::viewportAdded( const Ogre::RenderTargetViewportEvent& evt ) {
		/* no operation */
	}
	//#####################################################################
	void OgreViewport::viewportRemoved( const Ogre::RenderTargetViewportEvent &evt ) {
		// We need to warn against unlinking the target Viewport from its RenderTarget
		if ( evt.source == mOgreViewport )
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "OpenGUI::OgreViewport cannot follow detached Ogre::Viewports", __FUNCTION__ );
		// and just in case they fail to listen, do the right thing and detach
		if ( mOgreRenderTarget )
			mOgreRenderTarget->removeListener( this );
		mOgreRenderTarget = 0;
		mOgreViewport = 0;
	}
	//#####################################################################
}
