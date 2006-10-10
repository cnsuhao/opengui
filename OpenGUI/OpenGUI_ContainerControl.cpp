#include "OpenGUI_ContainerControl.h"

namespace OpenGUI {
	//############################################################################
	class ContainerControl_ObjectAccessorList : public ObjectAccessorList {
	public:
		ContainerControl_ObjectAccessorList() {
			/* Currently has no accessors to bind */
		}
		~ContainerControl_ObjectAccessorList() {}
	}
	gContainerControl_ObjectAccessorList;

	//############################################################################
	//############################################################################


	//############################################################################
	ContainerControl::ContainerControl() {
		if ( gContainerControl_ObjectAccessorList.getParent() == 0 )
			gContainerControl_ObjectAccessorList.setParent( Control::getAccessors() );

		//Set up events and default bindings
		getEvents().createEvent( "ChildAttached" );
		getEvents().createEvent( "ChildDetached" );
		getEvents()["ChildAttached"].add( new EventDelegate( this, &ContainerControl::onChildAttached ) );
		getEvents()["ChildDetached"].add( new EventDelegate( this, &ContainerControl::onChildDetached ) );
	}
	//############################################################################
	ContainerControl::~ContainerControl() {
		/**/
	}
	//############################################################################
	ObjectAccessorList* ContainerControl::getAccessors() {
		return &gContainerControl_ObjectAccessorList;
	}
	//############################################################################
	char* ContainerControl::getClassName() {
		return "OpenGUI::ContainerControl";
	}
	//############################################################################
	void ContainerControl::onChildAttached( Object* sender, Attach_EventArgs& evtArgs ) {
		invalidate(); // need to invalidate caches for hierarchy change
	}
	//############################################################################
	void ContainerControl::onChildDetached( Object* sender, Attach_EventArgs& evtArgs ) {
		invalidate(); // need to invalidate caches for hierarchy change
	}
	//############################################################################
	void ContainerControl::eventChildAttached( I_WidgetContainer* container, Widget* newChild ) {
		Attach_EventArgs event( container, newChild );
		getEvents()["ChildAttached"].invoke( this, event );
	}
	//############################################################################
	void ContainerControl::eventChildDetached( I_WidgetContainer* container, Widget* prevChild ) {
		Attach_EventArgs event( container, prevChild );
		triggerEvent("ChildDetached", event);
	}
	//############################################################################
} // namespace OpenGUI {
