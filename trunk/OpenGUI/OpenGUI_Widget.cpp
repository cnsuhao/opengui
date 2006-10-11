#include "OpenGUI_Widget.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Renderer.h"
#include "OpenGUI_I_WidgetContainer.h"
#include "OpenGUI_Screen.h"

namespace OpenGUI {
	//############################################################################
	class Widget_Name_ObjectProperty : public ObjectProperty {
	public:
		virtual const char* getAccessorName() {
			return "Name";
		}
		//############################################################################
		virtual void get( Object& objectRef, Value& valueOut ) {
			try {
				Widget& w = dynamic_cast<Widget&>( objectRef );
				valueOut.setValue( w.getName() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual void set( Object& objectRef, Value& valueIn ) {
			try {
				Widget& w = dynamic_cast<Widget&>( objectRef );
				w.setName( valueIn.getValueAsString() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual Value::ValueType getPropertyType() {
			return Value::T_STRING;
		}
	}
	gWidget_Name_ObjectProperty;
	//############################################################################
	//############################################################################

	class Widget_ObjectAccessorList : public ObjectAccessorList {
	public:
		Widget_ObjectAccessorList() {
			addAccessor( &gWidget_Name_ObjectProperty );
		}
		~Widget_ObjectAccessorList() {}
	}
	gWidget_ObjectAccessorList;

	//############################################################################
	//############################################################################


	Widget::Widget() {
		mContainer = 0; //we always start with no container
		if ( gWidget_ObjectAccessorList.getParent() == 0 )
			gWidget_ObjectAccessorList.setParent( Object::getAccessors() );

		// set up defaults for properties
		mWidgetName = "";

		//Set up events and default bindings
		getEvents().createEvent( "Attached" );
		getEvents().createEvent( "Detached" );
		getEvents()["Attached"].add( new EventDelegate( this, &Widget::onAttached ) );
		getEvents()["Detached"].add( new EventDelegate( this, &Widget::onDetached ) );
		getEvents().createEvent( "Draw" );
		getEvents().createEvent( "Invalidated" );
		getEvents()["Draw"].add( new EventDelegate( this, &Widget::onDraw ) );
		getEvents()["Invalidated"].add( new EventDelegate( this, &Widget::onInvalidated ) );
		getEvents().createEvent( "Cursor_Move" );
		getEvents().createEvent( "Cursor_Press" );
		getEvents().createEvent( "Cursor_Release" );
		getEvents().createEvent( "Cursor_Hidden" );
		getEvents().createEvent( "Cursor_Shown" );
		getEvents()["Cursor_Move"].add( new EventDelegate( this, &Widget::onCursor_Move ) );
		getEvents()["Cursor_Press"].add( new EventDelegate( this, &Widget::onCursor_Press ) );
		getEvents()["Cursor_Release"].add( new EventDelegate( this, &Widget::onCursor_Release ) );
		getEvents()["Cursor_Hidden"].add( new EventDelegate( this, &Widget::onCursor_Hidden ) );
		getEvents()["Cursor_Shown"].add( new EventDelegate( this, &Widget::onCursor_Shown ) );
	}
	//############################################################################
	Widget::~Widget() {
		if ( mContainer )
			mContainer->notifyChildDelete( this );
	}
	//############################################################################
	ObjectAccessorList* Widget::getAccessors() {
		return &gWidget_ObjectAccessorList;
	}
	//############################################################################
	char* Widget::getClassName() {
		return "OpenGUI::Widget";
	}
	//############################################################################
	const std::string& Widget::getName() {
		return mWidgetName;
	}
	//############################################################################
	void Widget::setName( const std::string& name ) {
		mWidgetName = name;
	}
	//############################################################################
	I_WidgetContainer* Widget::getContainer() {
		return mContainer;
	}
	//############################################################################
	void Widget::invalidate() {
		eventInvalidated();
		Widget* parent = dynamic_cast<Widget*>( getContainer() );
		if ( parent )
			parent->invalidate();
	}
	//############################################################################
	void Widget::flush() {
		Widget* parent = dynamic_cast<Widget*>( mContainer );
		if ( parent )
			parent->invalidate();
		_doflush();
	}
	//############################################################################
	void Widget::_doflush() {
		eventInvalidated();
		I_WidgetContainer* meContainer = dynamic_cast<I_WidgetContainer*>( this );
		if ( meContainer ) {
			WidgetCollection::iterator iter = meContainer->Children.begin();
			while ( iter != meContainer->Children.end() ) {
				iter->_doflush();
				iter++;
			}
		}
	}
	//############################################################################
	Screen* Widget::getScreen() {
		if ( !mContainer ) return 0;
		Widget* parentW = dynamic_cast<Widget*>( mContainer );
		if ( parentW )
			return parentW->getScreen();
		Screen* parentS = dynamic_cast<Screen*>( mContainer );
		if ( parentS )
			return parentS;
		return 0;
	}
	//############################################################################
	void Widget::onAttached( Object* obj, Attach_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Widget::onDetached( Object* obj, Attach_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Widget::eventAttached( I_WidgetContainer* newParent, Widget* widget ) {
		Attach_EventArgs event( newParent, widget );
		triggerEvent( "Attached", event );
	}
	//############################################################################
	void Widget::eventDetached( I_WidgetContainer* prevParent, Widget* widget ) {
		Attach_EventArgs event( prevParent, widget );
		triggerEvent( "Detached", event );
	}
	//############################################################################
	void Widget::onDraw( Object* obj, Draw_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Widget::onInvalidated( Object* obj, EventArgs& evtArgs ) {
		/* Default is to do nothing */
		/* If we were a caching object, we should invalidate our cache here */
	}
	//############################################################################
	void Widget::eventDraw( Brush& brush ) {
		Draw_EventArgs event( brush );
		triggerEvent( "Draw", event );
	}
	//############################################################################
	void Widget::eventInvalidated() {
		EventArgs event;
		triggerEvent( "Invalidated", event );
	}
	//############################################################################
	void Widget::onCursor_Move( Object* sender, Cursor_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Widget::onCursor_Press( Object* sender, Cursor_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Widget::onCursor_Release( Object* sender, Cursor_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Widget::onCursor_Hidden( Object* sender, Cursor_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Widget::onCursor_Shown( Object* sender, Cursor_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	/*! Cursor position will be in the same coordinate space as the receiving Widget.
	This message may be culled by containers if the cursor is not within their bounds.
	(Meaning that children may not receive this event unless it is potentially relevant
	to them as determined by the container.)
	\param xPos X position of the cursor 
	\param yPos Y position of the cursor 
	*/
	void Widget::eventCursor_Move( float xPos, float yPos ) {
		EventArgs event;
		triggerEvent( "Cursor_Move", event );
	}
	//############################################################################
	/*! Cursor position will be in the same coordinate space as the receiving Widget.
	This message may be culled by containers if the cursor is not within their bounds.
	(Meaning that children may not receive this event unless it is potentially relevant
	to them as determined by the container.)
	\param xPos X position of the cursor 
	\param yPos Y position of the cursor 
	*/
	void Widget::eventCursor_Press( float xPos, float yPos ) {
		EventArgs event;
		triggerEvent( "Cursor_Press", event );
	}
	//############################################################################
	/*! Cursor position will be in the same coordinate space as the receiving Widget.
	This message may be culled by containers if the cursor is not within their bounds.
	(Meaning that children may not receive this event unless it is potentially relevant
	to them as determined by the container.)
	\param xPos X position of the cursor 
	\param yPos Y position of the cursor 
	*/
	void Widget::eventCursor_Release( float xPos, float yPos ) {
		EventArgs event;
		triggerEvent( "Cursor_Release", event );
	}
	//############################################################################
	/*! Containers should not cull this message. */
	void Widget::eventCursor_Hidden() {
		EventArgs event;
		triggerEvent( "Cursor_Hidden", event );
	}
	//############################################################################
	/*! Containers should not cull this message.
	Cursor position will be in the same coordinate space as the receiving Widget.
	\param xPos X position of the cursor 
	\param yPos Y position of the cursor 
	*/
	void Widget::eventCursor_Shown( float xPos, float yPos ) {
		EventArgs event;
		triggerEvent( "Cursor_Shown", event );
	}
	//############################################################################

}//namespace OpenGUI{
