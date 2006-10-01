#ifndef CA247652_FCF4_483C_B34C_810A39296B18
#define CA247652_FCF4_483C_B34C_810A39296B18

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Event.h"

namespace OpenGUI {
	class Object; //forward declaration

	namespace Event {

		class EventArgs; //forward declaration

		//! Base class for custom event handler implementations
		class OPENGUI_API EventHandler {
		public:
			EventHandler() {}
			virtual ~EventHandler() {}
			//! Interface for receiving event notifications
			virtual void onEvent( Object* sender, EventArgs& args ) = 0;
		};


		//! Provides event handler multi cast service.
		class OPENGUI_API EventHandlerList {
		public:
			EventHandlerList() {}
			virtual ~EventHandlerList() {}
			//! add a new EventHandler to the list
			void add( EventHandler* handler );
			//! remove an EventHandler from the list
			void remove( EventHandler* handler );
			//! executes all held EventHandlers with the given parameters
			void invoke( Object* sender, EventArgs& args );
		private:
			typedef std::set<EventHandler*> EventHandlerSet;
			EventHandlerSet mEventHandlerSet;
		};

	}// namespace Event {
}// namespace OpenGUI {

#endif // CA247652_FCF4_483C_B34C_810A39296B18

