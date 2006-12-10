#ifndef E65861C2_92D6_4345_8B3B_5B65D114F3C1
#define E65861C2_92D6_4345_8B3B_5B65D114F3C1

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"

namespace OpenGUI {
	class Widget; // forward declaration

	//! Interface for objects that contain collections of children Widget objects
	/*!
	*/
	class OPENGUI_API I_WidgetContainer {
		friend class WidgetCollection; //need this for add/remove notifications
	public:
		I_WidgetContainer();
		virtual ~I_WidgetContainer() {}

	protected:
		//! Container had a child attached
		virtual void eventChildAttached( WidgetCollection* container, Widget* newChild )=0;
		//! Container had a child detached
		virtual void eventChildDetached( WidgetCollection* container, Widget* prevChild )=0;

	private:
		//! automatically called by WidgetCollection after it added a widget to the collection
		void _notifyChildAdded( WidgetCollection* container, Widget* widgetPtr );
		//! automatically called by WidgetCollection after it removed a widget from the collection
		void _notifyChildRemoved( WidgetCollection* container, Widget* widgetPtr );
	};

}

#endif // E65861C2_92D6_4345_8B3B_5B65D114F3C1