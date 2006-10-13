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

		// initialize state variables
		m_LayoutSuspended = false; // layouts are instantaneous by default
		m_LayoutValid = true; // layout begins valid (as there are no controls to update, it does not matter)
		m_InUpdateLayout = false; // we are not in updateLayout() quite yet

		// set up defaults for properties

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
		triggerEvent( "ChildAttached", event );
	}
	//############################################################################
	void ContainerControl::eventChildDetached( I_WidgetContainer* container, Widget* prevChild ) {
		Attach_EventArgs event( container, prevChild );
		triggerEvent( "ChildDetached", event );
	}
	//############################################################################
	/*! If layout is not suspended, this triggers an immediate update of the layout.
	This function is protected from re-entry when a layout operation is currently
	under way. */
	void ContainerControl::invalidateLayout() {
		if ( !m_InUpdateLayout ) {
			m_LayoutValid = false;
			if ( !m_LayoutSuspended )
				updateLayout();
		}
	}
	//############################################################################
	void ContainerControl::suspendLayout() {
		m_LayoutSuspended = true;
	}
	//############################################################################
	void ContainerControl::resumeLayout() {
		m_LayoutSuspended = false;
		if ( !layoutValid() )
			updateLayout();
	}
	//############################################################################
	bool ContainerControl::layoutValid() {
		return m_LayoutValid;
	}
	//############################################################################
	/*! The update is performed regardless of layout being currently suspended,
	so only call this if you really want the update to occur. Layout validity,
	however, is still honored and layouts will not occur unless needed. */
	void ContainerControl::updateLayout() {
		m_InUpdateLayout = true;
		if ( !layoutValid() ) {
			_doUpdateLayout();
			m_LayoutValid = true;
		}
		m_InUpdateLayout = false;
	}
	//############################################################################
	/*! This is virtual in the case that a subclass wishes to perform their own layout logic.
	Toolbars and other specialty containers would likely need this functionality. */
	void ContainerControl::_doUpdateLayout() {

	}
	//############################################################################
} // namespace OpenGUI {
