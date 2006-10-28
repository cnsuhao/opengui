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
	class Widget_Enabled_ObjectProperty : public ObjectProperty {
	public:
		virtual const char* getAccessorName() {
			return "Enabled";
		}
		//############################################################################
		virtual void get( Object& objectRef, Value& valueOut ) {
			try {
				Widget& w = dynamic_cast<Widget&>( objectRef );
				valueOut.setValue( w.getEnabled() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual void set( Object& objectRef, Value& valueIn ) {
			try {
				Widget& w = dynamic_cast<Widget&>( objectRef );
				w.setEnabled( valueIn.getValueAsBool() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual Value::ValueType getPropertyType() {
			return Value::T_BOOL;
		}
	}
	gWidget_Enabled_ObjectProperty;
	//############################################################################
	//############################################################################

	class Widget_ObjectAccessorList : public ObjectAccessorList {
	public:
		Widget_ObjectAccessorList() {
			addAccessor( &gWidget_Name_ObjectProperty );
			addAccessor( &gWidget_Enabled_ObjectProperty );
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
		mEnabled = true;
		mValid = false;

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
		getEvents().createEvent( "Cursor_Disabled" );
		getEvents().createEvent( "Cursor_Enabled" );
		getEvents()["Cursor_Move"].add( new EventDelegate( this, &Widget::onCursor_Move ) );
		getEvents()["Cursor_Press"].add( new EventDelegate( this, &Widget::onCursor_Press ) );
		getEvents()["Cursor_Release"].add( new EventDelegate( this, &Widget::onCursor_Release ) );
		getEvents()["Cursor_Disabled"].add( new EventDelegate( this, &Widget::onCursor_Disabled ) );
		getEvents()["Cursor_Enabled"].add( new EventDelegate( this, &Widget::onCursor_Enabled ) );
		getEvents().createEvent( "Cursor_Focused" );
		getEvents().createEvent( "Cursor_FocusLost" );
		getEvents()["Cursor_Focused"].add( new EventDelegate( this, &Widget::onCursor_Focused ) );
		getEvents()["Cursor_FocusLost"].add( new EventDelegate( this, &Widget::onCursor_FocusLost ) );
		getEvents().createEvent( "Enabled" );
		getEvents().createEvent( "Disabled" );
		getEvents()["Enabled"].add( new EventDelegate( this, &Widget::onEnabled ) );
		getEvents()["Disabled"].add( new EventDelegate( this, &Widget::onDisabled ) );
		getEvents().createEvent( "Key_Up" );
		getEvents().createEvent( "Key_Down" );
		getEvents().createEvent( "Key_Pressed" );
		getEvents()["Key_Up"].add( new EventDelegate( this, &Widget::onKey_Up ) );
		getEvents()["Key_Down"].add( new EventDelegate( this, &Widget::onKey_Down ) );
		getEvents()["Key_Pressed"].add( new EventDelegate( this, &Widget::onKey_Pressed ) );
		getEvents().createEvent( "Key_Focused" );
		getEvents().createEvent( "Key_FocusLost" );
		getEvents()["Key_Focused"].add( new EventDelegate( this, &Widget::onKey_Focused ) );
		getEvents()["Key_FocusLost"].add( new EventDelegate( this, &Widget::onKey_FocusLost ) );
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
	bool Widget::getEnabled() {
		return mEnabled;
	}
	//############################################################################
	void Widget::setEnabled( bool value ) {
		if ( mEnabled != value ) {
			mEnabled = value;
			if ( mEnabled )
				eventEnabled();
			else
				eventDisabled();
			invalidate();
		}
	}
	//############################################################################
	I_WidgetContainer* Widget::getContainer() {
		return mContainer;
	}
	//############################################################################
	void Widget::invalidate() {
		if ( mValid ) { // only trigger "Invalidated" once per invalidation period
			mValid = false;
			eventInvalidated();
		}
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
	void Widget::_draw( Brush& brush ) {
		brush._pushMarker( this );
		eventDraw( brush );
		brush._popMarker( this );
	}
	//############################################################################
	/*! Widget implementation always returns false */
	bool Widget::_isInside( const FVector2& position ) {
		return false;
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
		/*! Default is to do nothing */
	}
	//############################################################################
	void Widget::onDetached( Object* obj, Attach_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
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
		/*! Default is to do nothing */
	}
	//############################################################################
	void Widget::onInvalidated( Object* obj, EventArgs& evtArgs ) {
		/* If we were a caching object, we should invalidate our cache here */
	}
	//############################################################################
	void Widget::eventDraw( Brush& brush ) {
		mValid = true;
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
		/*! Default is to do nothing */
	}
	//############################################################################
	void Widget::onCursor_Press( Object* sender, Cursor_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Widget::onCursor_Release( Object* sender, Cursor_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Widget::onCursor_Disabled( Object* sender, Cursor_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Widget::onCursor_Enabled( Object* sender, Cursor_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	/*! Cursor position will be in the same coordinate space as the receiving Widget.
	This message may be culled by containers if the cursor is not within their bounds.
	(Meaning that children may not receive this event unless it is potentially relevant
	to them as determined by the container.)
	\param xPos X position of the cursor
	\param yPos Y position of the cursor
	\return true if the input was consumed, false otherwise
	*/
	bool Widget::eventCursor_Move( float xPos, float yPos ) {
		Cursor_EventArgs event( xPos, yPos );
		triggerEvent( "Cursor_Move", event );
		return event.Consumed;
	}
	//############################################################################
	/*! Cursor position will be in the same coordinate space as the receiving Widget.
	This message may be culled by containers if the cursor is not within their bounds.
	(Meaning that children may not receive this event unless it is potentially relevant
	to them as determined by the container.)
	\param xPos X position of the cursor
	\param yPos Y position of the cursor
	\return true if the input was consumed, false otherwise
	*/
	bool Widget::eventCursor_Press( float xPos, float yPos ) {
		Cursor_EventArgs event( xPos, yPos );
		triggerEvent( "Cursor_Press", event );
		return event.Consumed;
	}
	//############################################################################
	/*! Cursor position will be in the same coordinate space as the receiving Widget.
	This message may be culled by containers if the cursor is not within their bounds.
	(Meaning that children may not receive this event unless it is potentially relevant
	to them as determined by the container.)
	\param xPos X position of the cursor
	\param yPos Y position of the cursor
	\return true if the input was consumed, false otherwise
	*/
	bool Widget::eventCursor_Release( float xPos, float yPos ) {
		Cursor_EventArgs event( xPos, yPos );
		triggerEvent( "Cursor_Release", event );
		return event.Consumed;
	}
	//############################################################################
	/*! Containers should not cull this message. */
	void Widget::eventCursor_Disabled() {
		EventArgs event;
		triggerEvent( "Cursor_Disabled", event );
	}
	//############################################################################
	/*! Containers should not cull this message.
	Cursor position will be in the same coordinate space as the receiving Widget.
	\param xPos X position of the cursor 
	\param yPos Y position of the cursor 
	*/
	void Widget::eventCursor_Enabled( float xPos, float yPos ) {
		EventArgs event;
		triggerEvent( "Cursor_Enabled", event );
	}
	//############################################################################
	void Widget::onCursor_Focused( Object* sender, Focus_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Widget::onCursor_FocusLost( Object* sender, Focus_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Widget::eventCursor_Focused( Widget* cur, Widget* prev ) {
		Focus_EventArgs event( cur, prev );
		triggerEvent( "Cursor_Focused", event );
	}
	//############################################################################
	void Widget::eventCursor_FocusLost( Widget* cur, Widget* prev ) {
		Focus_EventArgs event( cur, prev );
		triggerEvent( "Cursor_FocusLost", event );
	}
	//############################################################################
	void Widget::onKey_Up( Object* sender, Key_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Widget::onKey_Down( Object* sender, Key_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Widget::onKey_Pressed( Object* sender, Key_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	bool Widget::eventKey_Up( char character ) {
		Key_EventArgs event( character );
		triggerEvent( "Key_Up", event );
		return event.Consumed;
	}
	//############################################################################
	bool Widget::eventKey_Down( char character ) {
		Key_EventArgs event( character );
		triggerEvent( "Key_Down", event );
		return event.Consumed;
	}
	//############################################################################
	bool Widget::eventKey_Entered( char character ) {
		Key_EventArgs event( character );
		triggerEvent( "Key_Entered", event );
		return event.Consumed;
	}
	//############################################################################
	void Widget::onKey_Focused( Object* sender, Focus_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Widget::onKey_FocusLost( Object* sender, Focus_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Widget::eventKey_Focused( Widget* cur, Widget* prev ) {
		Focus_EventArgs event( cur, prev );
		triggerEvent( "Key_Focused", event );
	}
	//############################################################################
	void Widget::eventKey_FocusLost( Widget* cur, Widget* prev ) {
		Focus_EventArgs event( cur, prev );
		triggerEvent( "Key_FocusLost", event );
	}
	//############################################################################
	void Widget::onEnabled( Object* sender, EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Widget::onDisabled( Object* sender, EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Widget::eventEnabled() {
		EventArgs event;
		triggerEvent( "Enabled", event );
	}
	//############################################################################
	void Widget::eventDisabled() {
		EventArgs event;
		triggerEvent( "Disabled", event );
	}
	//############################################################################
	void Widget::_getChildrenAt( const FVector2& position, WidgetPtrList& outList, bool recursive ) {
		return; // Widget has no children
	}
	//############################################################################
	Widget* Widget::_getChildAt( const FVector2& position, bool recursive ) {
		return 0; //Widget has no children
	}
	//############################################################################
	void Widget::getChildrenAt( const FVector2& position, WidgetPtrList& outList, bool recursive ) {
		_getChildrenAt( position, outList, recursive );
	}
	//############################################################################
	Widget* Widget::getChildAt( const FVector2& position, bool recursive ) {
		return _getChildAt( position, recursive );
	}
	//############################################################################
	/*! You can only grab focus when you are attached to a Screen. Attempts to grab focus
	when not attached to a screen will cause an exception. */
	void Widget::grabKeyFocus() {
		Screen* screen = getScreen();
		if ( !screen )
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "This operation requires attachment to a Screen", __FUNCTION__ );
		if ( screen->getKeyFocusedWidget() != this )
			screen->_setKeyFocus( this );
	}
	//############################################################################
	/*! This is automatically performed when a widget is detached from a Screen,
	which also means that it occurs during widget destruction. Requires attachment
	to a Screen at time of calling or will have no effect. */
	void Widget::releaseKeyFocus() {
		Screen* screen = getScreen();
		if ( !screen )
			return;
		if ( screen->getKeyFocusedWidget() == this )
			screen->_setKeyFocus( 0 );
	}
	//############################################################################
	/*! You can only grab focus when you are attached to a Screen. Attempts to grab
	focus when not attached to a screen will cause an exception.
	\note This operation will generate an additional (fake, but accurate) \c Cursor_Move
	event. */
	void Widget::grabCursorFocus() {
		Screen* screen = getScreen();
		if ( !screen )
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "This operation requires attachment to a Screen", __FUNCTION__ );
		if ( screen->getCursorFocusedWidget() != this )
			screen->_setCursorFocus( this );
	}
	//############################################################################
	/*! This is automatically performed when a widget is detached from a Screen,
	which also means that it occurs during widget destruction. Requires attachment
	to a Screen at time of calling or will have no effect.
	\note This operation will generate an additional (fake, but accurate) \c Cursor_Move
	event. */
	void Widget::releaseCursorFocus() {
		Screen* screen = getScreen();
		if ( !screen )
			return;
		if ( screen->getCursorFocusedWidget() == this )
			screen->_setCursorFocus( 0 );
	}
	//############################################################################
	void Widget::_detaching() {
		releaseCursorFocus();
		releaseKeyFocus();
	}
	//############################################################################
	void Widget::_attaching() {
		/**/
	}
	//############################################################################
}//namespace OpenGUI{
