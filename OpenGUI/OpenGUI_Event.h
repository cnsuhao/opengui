#ifndef BA005A9D_5FCE_4363_A3C3_CDE071FA13B5
#define BA005A9D_5FCE_4363_A3C3_CDE071FA13B5

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"


namespace OpenGUI {

	class Object; //forward declaration

	//! Defines all built in event types
	/*! These are Events that %OpenGUI will send and handle internally. Some events,
		such as DRAW have default actions that are meant to be overridden under certain
		circumstances. All events that are meant to be overridden have their handlers
		exposed as protected virtual functions.

		\attention
		Users creating new widgets are encouraged to create new events of their own if
		the existing event set cannot represent the necessary action, but should use
		event ID values that are negative to prevent %OpenGUI from mistakenly trying to
		process those events on its own. New events IDs may be added in the future and
		could potentially collide with non-negative custom event IDs. So even if using
		a non-negative custom event ID works right now, there is no guarantee that it will
		work in future versions.

		\note You'll undoubtedly notice the presence of events that seem to be markers.
		They are, in fact, just that. They are in the common format "_[section]_begin" and
		"_[section]_end". These markers are used to group together similar events so that
		they can be quickly sorted during event processing. Think of them like the letter
		placards in a Rolodex. They aren't valid entries for use, but they allow us to
		sacrifice a small amount of memory to achieve a net speed gain.

	*/
	namespace EventID{
		//!
		enum{
			//! Does absolutely nothing. You're firing blanks!
			BLANK = 0,

			//! Marks the beginning of the event list
			_events_begin,


			/*! Invalidates the render cache of the target and recursively all its children
			causing a DRAW event on the next rendering pass. */
			INVALIDATE,


			/*! During this event the Widget is expected to draw itself using a provided
			Brush object as an interface to the renderer.
			*/
			DRAW,

			//! Mark of beginning of input related events
			_input_begin,

			/*! Occurs when the cursor is moved around the scene. */
			CURSOR_MOVE,

			/*! Occurs when cursor press input is injected into the Screen. */
			CURSOR_PRESS,

			/*! Occurs when cursor release input is injected into the Screen. */
			CURSOR_RELEASE,

			/*! Occurs when the cursor is clicked (PRESSed and RELEASEd over the same target). */
			CURSOR_CLICK,

			//! Mark of end of input related events
			_input_end,

			/*! Some Widgets can be ACTIVATEd due to various circumstances. A button, for instance,
			would be ACTIVATEd when it is CLICKed. This message allows for more generic activations
			as well. The enter key being pressed while an input dialog has focus is another example
			of an ACTIVATE condition. */
			ACTIVATE,


			//! Marks the end of the event list
			_events_end

		};
	}

	//! Base class for event arguments
	class OPENGUI_API EventArgs {
	public:
		//! Constructor requires the EventID to identify the event type
		EventArgs( int eventID ): mEventID(eventID) {}
		//! virtual destructor to support polymorphism
		virtual ~EventArgs() {}
		//! returns the EventID that describes this event
		/*! Ultra const-ness to encourage compiler optimizations */
		const int EventID() const {
			return mEventID;
		}
	private:
		const int mEventID;
	};

	class EventHandlerList; //forward declaration

	//! Provides a unified event definition, binding, and relaying service.
	class OPENGUI_API EventReceiver {
		//Only allow Object to create and destroy us. We're not for random reuse.
		friend class Object;
	public:

		//EventReceiver (){}
		//! Adds the given \c name to the list of valid (and bindable) events
		void createEvent( const std::string& name );
		//! Sends an event of the given \c name to all such bound EventHandler instances
		void sendEvent( const std::string& name, EventArgs& args );

		//! Returns the list of EventHandler objects for the event of given \c name
		EventHandlerList* getEventHandlers( const std::string& name );
		//! Returns reference to the list of EventHandler objects for the event of given \c name, throws exception if event does not exist
		EventHandlerList& operator[]( const std::string& name );
	private:
		EventReceiver();
		~EventReceiver();
		typedef std::map<std::string, EventHandlerList*> EventHandlerListMap;
		EventHandlerListMap mEventHandlerListMap;
		Object* mParent;
	};

}
;//namespace OpenGUI{
#endif
