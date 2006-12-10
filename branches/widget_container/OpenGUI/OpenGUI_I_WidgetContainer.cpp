#include "OpenGUI_I_WidgetContainer.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	//############################################################################
	I_WidgetContainer::I_WidgetContainer() {
		Children.mIContainer = this;
	}
	//############################################################################
	void I_WidgetContainer::notifyChildDelete( Widget* widgetToRemove ) {
		Children.remove( widgetToRemove );
	}
	//############################################################################
	void I_WidgetContainer::notifyChildAdding( Widget* widgetPtr ) {
		if ( widgetPtr->mContainer != 0 )
			OG_THROW( Exception::ERR_INTERNAL_ERROR,
					  "Widget is already a child of another container!", __FUNCTION__ );
		widgetPtr->_attaching();
		widgetPtr->mContainer = this;
	}
	//############################################################################
	void I_WidgetContainer::notifyChildRemoving( Widget* widgetPtr ) {
		if ( widgetPtr->mContainer != this )
			OG_THROW( Exception::ERR_INTERNAL_ERROR,
					  "Widget is not a child of this container!", __FUNCTION__ );
		widgetPtr->_detaching();
		widgetPtr->mContainer = 0;
	}
	//############################################################################
	void I_WidgetContainer::notifyChildAdded( Widget* widgetPtr ) {
		eventChildAttached( this, widgetPtr );
		widgetPtr->eventAttached( this, widgetPtr );
	}
	//############################################################################
	void I_WidgetContainer::notifyChildRemoved( Widget* widgetPtr ) {
		eventChildDetached( this, widgetPtr );
		widgetPtr->eventDetached( this, widgetPtr );
	}
	//############################################################################
	void I_WidgetContainer::eventChildAttached( I_WidgetContainer* container, Widget* newChild ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void I_WidgetContainer::eventChildDetached( I_WidgetContainer* container, Widget* prevChild ) {
		/*! Default is to do nothing */
	}
	//############################################################################
} // namespace OpenGUI {
