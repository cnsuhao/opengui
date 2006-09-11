// -----------------------------------------------------------------------------
// OpenGUI_EventListener.h
// -----------------------------------------------------------------------------

#ifndef	_H_OPENGUI_EVENTLISTENER
#define _H_OPENGUI_EVENTLISTENER

#include "OpenGUI_PreRequisites.h"

#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Event.h"
#include "OpenGUI_Message.h"


namespace OpenGUI {

	class Element; //forward declaration

	//! Abstract interface class for capturing events from an Element
	/*! Only a single Element may be attached at a time.
		Attaching can be performed either by the EventListener::attach() method, or by
		Element::attachEventListener().
	*/
	class OPENGUI_API EventListener {
	public:
		//! Newly created listeners can be created in either an initially attached or detached state according to \c elementToBind
		EventListener( Element* elementToBind = 0 );
		//! Automatically detaches on destruction if necessary
		virtual ~EventListener();
		//! Attaches this listener to the given \c elementToBind.
		/*! This will automatically detach any existing Element before binding to
			the new one.
		*/
		void attach( Element* elementToBind );
		//! Detaches from the current Element. Multiple calls cause no ill effect
		void detach();
		//! Returns \c TRUE if the listener is attached to an Element
		bool isAttached() {
			return 0 != mAttachedElement;
		}
		//! Returns a pointer to the currently attached Element, or 0 if not attached
		Element* getElement() {
			return mAttachedElement;
		}

		//! Pure Virtual, Needs Implementing by subclass
		/*! This function will be called whenever an event passes through the attached
			Element. This applies for all events, even those not directed at the
			attached Element. It is highly recommended that implementations perform
			event filtering at this point to only process events that they are truly
			interested in dealing with.

			\param msg const reference to the Msg::Message struct that
			\return Return \c TRUE to allow continued propagation of this event toward its
				destination, or \c FALSE to stop the propagation at the current Element.
				(All event handlers at the current Element are guaranteed a chance to
				run, even if one of them returns false. If any one event handler returns
				false then propagation will be stopped, regardless of the return values of
				other event handlers that already ran or will run.) If unsure what to do
				with an event (ie. default action), you should return \c TRUE.
		*/
		virtual bool onEvent( const Msg::Message& msg ) = 0;

	protected:
	private:
		friend class Element; //needed for access to _setAttachedElement()
		//! \internal This is called by the to-be-attached Element to complete the attachment process
		void _setAttachedElement( Element* newElement );
		Element* mAttachedElement; //!< \internal pointer to the Element to which this listener is currently attached
	};

}//namespace OpenGUI{



#endif // _H_OPENGUI_EVENTLISTENER
