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
	/*! This is virtual so that derived classes can redefine it to provide new client
	area sizes and positions as desired.

	The Client Area is the area of the ContainerControl that child widgets are drawn
	within. The Client Area's position is an offset from this ContainerControl's
	position. So a Client Area position of 0,0 would place the upper left of the
	Client Area exactly in the upper left corner of this ContainerControl, regardless
	of where this ContainerControl is actually placed on the Screen.

	The default implementation always returns a client area that fully encompasses
	the ContainerControl's drawing area.*/
	const FRect& ContainerControl::getClientArea() {
		static FRect tmp;
		tmp.setSize( getSize() );
		return tmp;
	}
	//############################################################################
	/*! The update is performed regardless of layout being currently suspended,
	so only call this if you really want the update to occur. Layout validity,
	however, is still honored and layouts will not occur unless needed. */
	void ContainerControl::updateLayout() {
		m_InUpdateLayout = true;
		if ( !layoutValid() ) {
			_setChildControlLayoutState( true );
			_doUpdateLayout();
			m_LayoutValid = true;
			_setChildControlLayoutState( false );
		}
		m_InUpdateLayout = false;
	}
	//############################################################################
	void ContainerControl::_setChildControlLayoutState( bool state ) {
		for ( WidgetCollection::iterator iter = Children.begin();
				iter != Children.end(); iter++ ) {
			Control* c = dynamic_cast<Control*>( iter.get() );
			if ( c )
				c->m_InLayout = state;
		}
	}
	//############################################################################
	/*! This is virtual in the case that a subclass wishes to perform their own layout logic.
	Toolbars and other specialty containers would likely need this functionality. */
	void ContainerControl::_doUpdateLayout() {
		//store previous client area space
		FRect oldClntArea = m_RemClntArea;
		m_RemClntArea = getClientArea();

		//update all docked controls
		for ( WidgetCollection::iterator iter = Children.begin();
				iter != Children.end(); iter++ ) {
			Control* ctrl = dynamic_cast<Control*>( iter.get() );
			if ( ctrl ) {
				int dock = ctrl->getDocking();
				if ( dock ) {

					//Next two IF's cover position and height for 'Fill' as well
					if (( dock & Control::Left ) || ( dock & Control::Right ) ) {
						ctrl->setTop( m_RemClntArea.getPosition().y );
						ctrl->setHeight( m_RemClntArea.getHeight() );
					}
					if (( dock & Control::Top ) || ( dock & Control::Bottom ) ) {
						ctrl->setLeft( m_RemClntArea.getPosition().x );
						ctrl->setWidth( m_RemClntArea.getWidth() );
					}

					if ( dock == Control::Left ) {
						ctrl->setLeft( m_RemClntArea.getPosition().x );
						m_RemClntArea.setWidth( m_RemClntArea.getWidth() - ctrl->getWidth() );
						m_RemClntArea.offset( FVector2( ctrl->getWidth(), 0.0f ) );
					}
					if ( dock == Control::Right ) {
						ctrl->setLeft( m_RemClntArea.getPosition().x + m_RemClntArea.getWidth() - ctrl->getWidth() );
						m_RemClntArea.setWidth( m_RemClntArea.getWidth() - ctrl->getWidth() );
					}

					if ( dock == Control::Top ) {
						ctrl->setTop( m_RemClntArea.getPosition().y );
						m_RemClntArea.setHeight( m_RemClntArea.getHeight() - ctrl->getHeight() );
						m_RemClntArea.offset( FVector2( 0.0f, ctrl->getHeight() ) );
					}
					if ( dock == Control::Bottom ) {
						ctrl->setTop( m_RemClntArea.getPosition().y + m_RemClntArea.getHeight() - ctrl->getHeight() );
						m_RemClntArea.setHeight( m_RemClntArea.getHeight() - ctrl->getHeight() );
					}
				}
			}
		}

		//use difference of new and previous client area space to update anchored controls
		float deltaLeft = m_RemClntArea.getPosition().x - oldClntArea.getPosition().x;
		float deltaTop = m_RemClntArea.getPosition().y - oldClntArea.getPosition().y ;
		float deltaRight = ( m_RemClntArea.getPosition().x + m_RemClntArea.getWidth() ) - ( oldClntArea.getPosition().x + oldClntArea.getWidth() ) ;
		float deltaBottom = ( m_RemClntArea.getPosition().y + m_RemClntArea.getHeight() ) - ( oldClntArea.getPosition().y + oldClntArea.getHeight() ) ;

		for ( WidgetCollection::iterator iter = Children.begin();
				iter != Children.end(); iter++ ) {
			Control* ctrl = dynamic_cast<Control*>( iter.get() );
			if ( ctrl ) {
				int dock = ctrl->getDocking();
				if ( dock == Control::None ) {
					int anchor = ctrl->getAnchor();
					if(anchor & Control::Left){
						ctrl->setLeft( ctrl->getLeft() + deltaLeft );
						if(anchor & Control::Right)
							ctrl->setWidth( (ctrl->getWidth() - deltaLeft) + deltaRight);
					}
					if( (anchor & Control::Left) == 0 && (anchor & Control::Right)){
						ctrl->setLeft( ctrl->getLeft() + deltaRight );
					}

					if(anchor & Control::Top){
						ctrl->setTop( ctrl->getTop() + deltaTop );
						if(anchor & Control::Bottom)
							ctrl->setHeight( (ctrl->getHeight() - deltaTop) + deltaBottom);
					}
					if( (anchor & Control::Top) == 0 && (anchor & Control::Bottom)){
						ctrl->setTop( ctrl->getTop() + deltaBottom );
					}
				}
			}
		}
	}
	//############################################################################
} // namespace OpenGUI {
