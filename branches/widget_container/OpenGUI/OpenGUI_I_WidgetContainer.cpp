#include "OpenGUI_I_WidgetContainer.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	//############################################################################
	I_WidgetContainer::I_WidgetContainer() {
		//Children.mIContainer = this;
	}
	//############################################################################
	void I_WidgetContainer::_notifyChildAdded( WidgetCollection* container, Widget* widgetPtr ) {
		eventChildAttached( container, widgetPtr );
		//widgetPtr->eventAttached( this, widgetPtr );
	}
	//############################################################################
	void I_WidgetContainer::_notifyChildRemoved( WidgetCollection* container, Widget* widgetPtr ) {
		eventChildDetached( container, widgetPtr );
		//widgetPtr->eventDetached( this, widgetPtr );
	}
	//############################################################################
} // namespace OpenGUI {
