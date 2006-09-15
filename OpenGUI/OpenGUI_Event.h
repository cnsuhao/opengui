#ifndef BA005A9D_5FCE_4363_A3C3_CDE071FA13B5
#define BA005A9D_5FCE_4363_A3C3_CDE071FA13B5

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_MouseButton.h"

namespace OpenGUI {

	class Object; //forward declaration

	//! Contains all object types that directly involve the Event System
	namespace Event {
		//! Base class for event arguments
		class OPENGUI_API EventArgs {
		public:
			virtual ~EventArgs() {}
		};


		class EventHandlerList; //forward declaration

		//! Provides a unified event definition, binding, and relaying service.
		class OPENGUI_API EventReceiver {
			//Only allow Object to create and destroy us. We're not for random reuse.
			friend class OpenGUI::Object;
		public:
			
			//EventReceiver (){}
			//! Adds the given \c name to the list of valid (and bindable) events
			void createEvent( const std::string& name );
			//! Sends an event of the given \c name to all such bound EventHandler instances
			void sendEvent( const std::string& name, EventArgs& args );

			//! Returns the list of EventHandler objects for the event of given \c name
			EventHandlerList* getEventHandlers( const std::string& name );
		private:
			EventReceiver();
			~EventReceiver();
			typedef std::map<std::string, EventHandlerList*> EventHandlerListMap;
			EventHandlerListMap mEventHandlerListMap;
			Object* mParent;
		};

	}//namespace Event {


	namespace Msg {

		//! Contains all the event specific structs that are used
		/*! \deprecated replaced by new event system */
		namespace EventData {

			//! Event specific data struct.
			struct MouseButtonEvent {
				unsigned int mouseButtonID;//!< The mouse button ID. \see OpenGUI::MouseButton
			};

			//! Event specific data struct.
			struct MouseMoveEvent {
				FVector2 mousePosition; //!< The new mouse position in absolute world space coordinates.
			};

			//! Event specific data struct.
			struct KeyEvent {
				char key; //!< ASCII char of the key
			};

			//! Event specific data struct.
			struct TickEvent {
				unsigned int timeDelta; //!< The time delta in milliseconds since the previous tick event
			};


		}
		;//namespace EventData{
	}
	;//namespace Msg{
}
;//namespace OpenGUI{
#endif
