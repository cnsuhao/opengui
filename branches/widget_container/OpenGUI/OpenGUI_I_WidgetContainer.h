#ifndef E65861C2_92D6_4345_8B3B_5B65D114F3C1
#define E65861C2_92D6_4345_8B3B_5B65D114F3C1

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Widget.h"

namespace OpenGUI {

	//! Interface for objects that contain a collection of children Widget objects
	/*! This is mostly just an interface that exposes a new public member variable
		"Children" (type WidgetCollection), which is a collection of child Widget
		objects.

		This class also provides some standard services, such as child widget
		destruction so that the collection of children does not contain pointers
		to children that are no longer available. It also ensures that child Widgets
		are always kept up to date with an accurate pointer to their parenting object.

		\see Widget::getContainer()
	*/
	class OPENGUI_API I_WidgetContainer {
		friend class Widget; //need this for child widget destruction notifications
		friend class WidgetCollection; //need this for add/remove notifications
	public:
		I_WidgetContainer();
		virtual ~I_WidgetContainer() {}
		//! Collection of contained children Widget objects
		WidgetCollection Children;
	protected:
		//! Container had a child attached
		virtual void eventChildAttached( I_WidgetContainer* container, Widget* newChild );
		//! Container had a child detached
		virtual void eventChildDetached( I_WidgetContainer* container, Widget* prevChild );

	private:
		//! automatically called by Widget during destruction to notify us so we can remove its entry
		void notifyChildDelete( Widget* widgetToRemove );
		//! automatically called by WidgetCollection before it adds a widget to the collection
		void notifyChildAdding( Widget* widgetPtr );
		//! automatically called by WidgetCollection before it removes a widget from the collection
		void notifyChildRemoving( Widget* widgetPtr );
		//! automatically called by WidgetCollection after it added a widget to the collection
		void notifyChildAdded( Widget* widgetPtr );
		//! automatically called by WidgetCollection after it removed a widget from the collection
		void notifyChildRemoved( Widget* widgetPtr );
	};

}

#endif // E65861C2_92D6_4345_8B3B_5B65D114F3C1