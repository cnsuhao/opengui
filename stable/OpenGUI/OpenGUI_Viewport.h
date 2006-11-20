#ifndef AA81C3C7_DB32_41b6_A625_F39F16EFF868
#define AA81C3C7_DB32_41b6_A625_F39F16EFF868

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	class Screen;

	//! Final rendering surface for Screen objects
	/*! Viewports are, as stated, the final render targets for Screens.
	%OpenGUI does not supply any built in method to create/destroy or otherwise
	manage Viewport objects. It is up to the Renderer implementation to supply
	its own methods for the creation and destruction of Viewports.	
	*/
	class OPENGUI_API Viewport {
		friend class Screen; // screen needs access to preUpdate/postUpdate
	public:
		//! Set of Screen pointers, used to contain the list of Screens that are attached to a Viewport
		typedef std::set<Screen*> ScreenSet;

		//! Must return the current pixel size of the render target of this Viewport
		/*! The value returned by this is used in pixel alignment calculations, so
		an accurate return value is very important. */
		virtual const IVector2& getSize() = 0;

	protected:
		//! constructor is protected to prevent unauthorized creation
		Viewport();
		//! destructor is protected to prevent unauthorized deletes
		/*! This destructor will also auto-detach any attached Screens. */
		virtual ~Viewport();

		//! This is called by Screen immediately prior to the beginning of an update
		/*! If you need to clear this viewport's contents , this is where you should
		do it. A Viewport for a render texture would be a prime example of where this
		would be appropriate.
		\param updatingScreen The Screen that is calling this notification.
		
		Renderer::selectViewport() and Renderer::preRenderSetup() have already been called
		when this notification is issued.
		*/
		virtual void preUpdate( Screen* updatingScreen ) = 0;
		//! This is called by Screen immediately after the end of an update
		/*! \param updatingScreen The Screen that is calling this notification.
		
		Renderer::postRenderCleanup() has not yet been called at the time of this notification.
		*/
		virtual void postUpdate( Screen* updatingScreen ) = 0;

		//! Called when a Screen attaches to this Viewport
		virtual void screenAttached( Screen* attachingScreen ) {
			/* no default action */
		}
		//! Called when a Screen detaches from this Viewport
		/*! It is possible for this to be called during destruction if there are remaining attached Screens. */
		virtual void screenDetached( Screen* detachingScreen ) {
			/* no default action */
		}

		//! Returns a const reference to the stored set of attached Screens
		const ScreenSet& getScreenSet();

	private:
		ScreenSet mScreens;
		void _screenAttach( Screen* screen );
		void _screenDetach( Screen* screen );
	};
}

#endif // AA81C3C7_DB32_41b6_A625_F39F16EFF868