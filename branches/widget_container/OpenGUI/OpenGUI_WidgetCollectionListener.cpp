#include "OpenGUI_I_WidgetContainer.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	//############################################################################
	WidgetCollectionListener::WidgetCollectionListener() {
		//Children.mIContainer = this;
	}
	//############################################################################
	void WidgetCollectionListener::_notifyChildAdded( WidgetCollection* container, Widget* widgetPtr ) {
		eventChildAttached( container, widgetPtr );
		//widgetPtr->eventAttached( this, widgetPtr );
	}
	//############################################################################
	void WidgetCollectionListener::_notifyChildRemoved( WidgetCollection* container, Widget* widgetPtr ) {
		eventChildDetached( container, widgetPtr );
		//widgetPtr->eventDetached( this, widgetPtr );
	}
	//############################################################################
} // namespace OpenGUI {
