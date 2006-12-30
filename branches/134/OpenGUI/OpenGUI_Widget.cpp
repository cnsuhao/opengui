// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_Widget.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Renderer.h"
#include "OpenGUI_WidgetCollection.h"
#include "OpenGUI_Screen.h"
#include "OpenGUI_StrConv.h"

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
		m_CursorInside = false;

		//Set up events and default bindings
		getEvents().createEvent( "Attached" );
		getEvents().createEvent( "Detached" );
		getEvents()["Attached"].add( new EventDelegate( this, &Widget::onAttached ) );
		getEvents()["Detached"].add( new EventDelegate( this, &Widget::onDetached ) );
		getEvents().createEvent( "Draw" );
		getEvents().createEvent( "Invalidated" );
		getEvents()["Draw"].add( new EventDelegate( this, &Widget::onDraw ) );
		getEvents()["Invalidated"].add( new EventDelegate( this, &Widget::onInvalidated ) );

		getEvents().createEvent( "CursorMove" );
		getEvents().createEvent( "CursorPress" );
		getEvents().createEvent( "CursorRelease" );
		getEvents().createEvent( "CursorEnter" );
		getEvents().createEvent( "CursorLeave" );
		getEvents().createEvent( "CursorFocused" );
		getEvents().createEvent( "CursorFocusLost" );
		getEvents()["CursorMove"].add( new EventDelegate( this, &Widget::onCursorMove ) );
		getEvents()["CursorPress"].add( new EventDelegate( this, &Widget::onCursorPress ) );
		getEvents()["CursorRelease"].add( new EventDelegate( this, &Widget::onCursorRelease ) );
		getEvents()["CursorEnter"].add( new EventDelegate( this, &Widget::onCursorEnter ) );
		getEvents()["CursorLeave"].add( new EventDelegate( this, &Widget::onCursorLeave ) );
		getEvents()["CursorFocused"].add( new EventDelegate( this, &Widget::onCursorFocused ) );
		getEvents()["CursorFocusLost"].add( new EventDelegate( this, &Widget::onCursorFocusLost ) );

		getEvents().createEvent( "Enabled" );
		getEvents().createEvent( "Disabled" );
		getEvents()["Enabled"].add( new EventDelegate( this, &Widget::onEnabled ) );
		getEvents()["Disabled"].add( new EventDelegate( this, &Widget::onDisabled ) );

		getEvents().createEvent( "KeyUp" );
		getEvents().createEvent( "KeyDown" );
		getEvents().createEvent( "KeyPressed" );
		getEvents().createEvent( "KeyFocused" );
		getEvents().createEvent( "KeyFocusLost" );
		getEvents()["KeyUp"].add( new EventDelegate( this, &Widget::onKeyUp ) );
		getEvents()["KeyDown"].add( new EventDelegate( this, &Widget::onKeyDown ) );
		getEvents()["KeyPressed"].add( new EventDelegate( this, &Widget::onKeyPressed ) );
		getEvents()["KeyFocused"].add( new EventDelegate( this, &Widget::onKeyFocused ) );
		getEvents()["KeyFocusLost"].add( new EventDelegate( this, &Widget::onKeyFocusLost ) );

		getEvents().createEvent( "Tick" );
		getEvents()["Tick"].add( new EventDelegate( this, &Widget::onTick ) );
	}
	//############################################################################
	Widget::~Widget() {
		if ( mContainer )
			mContainer->_notifyChildDelete( this );
	}
	//############################################################################
	ObjectAccessorList* Widget::getAccessors() {
		return &gWidget_ObjectAccessorList;
	}
	//############################################################################
	unsigned int Widget::getObjectType() const {
		return OT_WIDGET;
	}
	//############################################################################
	const std::string& Widget::getName() {
		return mWidgetName;
	}
	//############################################################################
	void Widget::setName( const std::string& name ) {
		if ( name == "" ) { // empty names (anonymous) are always ok
			mWidgetName = name;
			return;
		}
		if ( name == ".." || name == "." || name.find( '/' ) != std::string::npos ) {
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Widget names cannot contain '/' and cannot be '.' or '..'", __FUNCTION__ );
			return;
		}

		WidgetCollection* container = getContainer();
		if ( container ) {
			Widget* w = container->getWidget( name );
			if ( w && w != this ) {
				OG_THROW( Exception::ERR_DUPLICATE_ITEM, "Cannot assign name '" + name + "'. Current WidgetContainer holds another widget with the same name.", __FUNCTION__ );
				return;
			}
		}
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
	WidgetCollection* Widget::getContainer() const {
		return mContainer;
	}
	//############################################################################
	/*! This is a helper function for Widget::getContainer()->WidgetCollection::getParent()
	with some additional safety checks. */
	Object* Widget::getParent() const {
		WidgetCollection* c = getContainer();
		if ( c ) {
			Object* p = c->getParent();
			return p;
		}
		return 0;
	}
	//############################################################################
	void Widget::invalidate() {
		if ( mValid ) { // only trigger "Invalidated" once per invalidation period
			mValid = false;
			eventInvalidated();

			Widget* parent = dynamic_cast<Widget*>( getParent() );
			if ( parent )
				parent->_invalidatedChild();
		}
	}
	//############################################################################
	void Widget::_invalidatedChild() {
		/* Default does nothing */
	}
	//############################################################################
	void Widget::flush() {
		Widget* parent = dynamic_cast<Widget*>( getParent() );
		if ( parent )
			parent->invalidate();
		_doflush();
	}
	//############################################################################
	void Widget::_doflush() {
		eventInvalidated();
	}
	//############################################################################
	void Widget::_draw( Brush& brush ) {
		brush._pushMarker( this );
		eventDraw( brush );
		brush._popMarker( this );
	}
	//############################################################################
	/*! This function is intended to be overridden by subclasses to reflect their
	own personal interpretation of the given point (in local coordinates) and if
	that point is considered to be inside the widget. This allows new widgets to
	break free from the existing "axis aligned rect" paradigm that is usually
	in place.

	\note
	Widget implementation always returns true since they have no position or size.
	Control, however, will test the point against its known size and position.
	*/
	bool Widget::isInside( const FVector2& position ) {
		return true;
	}
	//############################################################################
	Screen* Widget::getScreen() const {
		if ( !mContainer ) return 0;
		Widget* parentW = dynamic_cast<Widget*>( getParent() );
		if ( parentW )
			return parentW->getScreen();
		Screen* parentS = dynamic_cast<Screen*>( getParent() );
		if ( parentS )
			return parentS;
		return 0;
	}
	//############################################################################
	//############################################################################
	void Widget::onAttached( Object* obj, Attach_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Widget::eventAttached( WidgetCollection* newContainer, Widget* widget ) {
		Attach_EventArgs event( newContainer, widget );
		triggerEvent( "Attached", event );
	}
	//############################################################################
	void Widget::onDetached( Object* obj, Attach_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Widget::eventDetached( WidgetCollection* prevContainer, Widget* widget ) {
		Attach_EventArgs event( prevContainer, widget );
		triggerEvent( "Detached", event );
	}
	//############################################################################
	void Widget::onDraw( Object* obj, Draw_EventArgs& evtArgs ) {
		/* Default is to do nothing */
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
	//############################################################################
	/*! \param xPos X position of the cursor
		\param yPos Y position of the cursor
		\return true if the input was consumed, false otherwise
	*/
	bool Widget::eventCursorMove( float xPos, float yPos ) {
		Cursor_EventArgs event( xPos, yPos );
		triggerEvent( "CursorMove", event );
		return event.Consumed;
	}
	//############################################################################
	void Widget::onCursorMove( Object* sender, Cursor_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	/*! \param xPos X position of the cursor
		\param yPos Y position of the cursor
		\return true if the input was consumed, false otherwise
	*/
	bool Widget::eventCursorPress( float xPos, float yPos ) {
		Cursor_EventArgs event( xPos, yPos );
		triggerEvent( "CursorPress", event );
		return event.Consumed;
	}
	//############################################################################
	void Widget::onCursorPress( Object* sender, Cursor_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	/*! \param xPos X position of the cursor
		\param yPos Y position of the cursor
		\return true if the input was consumed, false otherwise
	*/
	bool Widget::eventCursorRelease( float xPos, float yPos ) {
		Cursor_EventArgs event( xPos, yPos );
		triggerEvent( "CursorRelease", event );
		return event.Consumed;
	}
	//############################################################################
	void Widget::onCursorRelease( Object* sender, Cursor_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Widget::eventCursorEnter() {
		EventArgs event;
		triggerEvent( "CursorEnter", event );
	}
	//############################################################################
	void Widget::onCursorEnter( Object* sender, Cursor_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Widget::eventCursorLeave() {
		EventArgs event;
		triggerEvent( "CursorLeave", event );
	}
	//############################################################################
	void Widget::onCursorLeave( Object* sender, Cursor_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Widget::eventCursorFocused( Widget* cur, Widget* prev ) {
		Focus_EventArgs event( cur, prev );
		triggerEvent( "CursorFocused", event );
	}
	//############################################################################
	void Widget::onCursorFocused( Object* sender, Focus_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Widget::eventCursorFocusLost( Widget* cur, Widget* prev ) {
		Focus_EventArgs event( cur, prev );
		triggerEvent( "CursorFocusLost", event );
	}
	//############################################################################
	void Widget::onCursorFocusLost( Object* sender, Focus_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	//############################################################################
	bool Widget::eventKeyUp( char character ) {
		Key_EventArgs event( character );
		triggerEvent( "KeyUp", event );
		return event.Consumed;
	}
	//############################################################################
	void Widget::onKeyUp( Object* sender, Key_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	bool Widget::eventKeyDown( char character ) {
		Key_EventArgs event( character );
		triggerEvent( "KeyDown", event );
		return event.Consumed;
	}
	//############################################################################
	void Widget::onKeyDown( Object* sender, Key_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	bool Widget::eventKeyPressed( char character ) {
		Key_EventArgs event( character );
		triggerEvent( "KeyPressed", event );
		return event.Consumed;
	}
	//############################################################################
	void Widget::onKeyPressed( Object* sender, Key_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Widget::eventKeyFocused( Widget* cur, Widget* prev ) {
		Focus_EventArgs event( cur, prev );
		triggerEvent( "KeyFocused", event );
	}
	//############################################################################
	void Widget::onKeyFocused( Object* sender, Focus_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Widget::eventKeyFocusLost( Widget* cur, Widget* prev ) {
		Focus_EventArgs event( cur, prev );
		triggerEvent( "KeyFocusLost", event );
	}
	//############################################################################
	void Widget::onKeyFocusLost( Object* sender, Focus_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	//############################################################################
	void Widget::eventEnabled() {
		EventArgs event;
		triggerEvent( "Enabled", event );
	}
	//############################################################################
	void Widget::onEnabled( Object* sender, EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Widget::eventDisabled() {
		EventArgs event;
		triggerEvent( "Disabled", event );
	}
	//############################################################################
	void Widget::onDisabled( Object* sender, EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
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
	when not attached to a screen will cause an exception.
	\see releaseKeyFocus() */
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
	to a Screen at time of calling or will have no effect.
	\see grabKeyFocus() */
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
	event.
	\see releaseCursorFocus() */
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
	event.
	\see grabCursorFocus() */
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
	void Widget::_tick( float seconds ) {
		eventTick( seconds );
	}
	//############################################################################
	void Widget::eventTick( float seconds ) {
		Tick_EventArgs event( seconds );
		triggerEvent( "Tick", event );
	}
	//############################################################################
	void Widget::onTick( Object* sender, Tick_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	Widget* Widget::_getChildByName( const std::string& childName ) const {
		return 0;
	}
	//############################################################################
	/*! Widget paths are much like file system paths. They are comprised of Widget
	names separated by forward slashes ('/'). They provide some common concepts,
	that are familiar to file system navigation.
	- <i>previous level</i> - signified by the double period ('..')
	- <i>current level</i> - signified by the single period ('.')
	- <i>absolute paths</i> - signified by starting the path with a forward slash ('/')
	- <i>relative paths</i> - signified by starting the path with anything other than a forward slash
	\note Wildcards are currently not supported. This may be changed in a later version.
	\attention All widget names are case-sensitive. Trailing slashes are not allowed.
	Blank entries (double slashes) are not allowed ('somechild/somechild//willNeverReach').
	\warning Because absolute paths would behave differently depending on if the widget's
	hierarchy is attached or detached from a Screen (root location moves), attempting to use
	an absolute path when not attached to a Screen will result in an exception. Additionally,
	you cannot obtain a pointer to a screen by using paths. Querying for "/" alone will
	result in an exception. If you want the screen, use getScreen().
	*/
	Widget* Widget::getPath( const std::string& path ) const {
		std::string tmpPath = path;
		StrConv::trim( tmpPath );

		//handle absolute paths by deferring to Screen
		if ( tmpPath.at( 0 ) == '/' ) {
			Screen* screen = getScreen();
			if ( !screen ) {
				OG_THROW( Exception::ERR_INTERNAL_ERROR, "Cannot resolve absolute path when not attached to a Screen", __FUNCTION__ );
				return 0;
			}
			return screen->getPath( tmpPath );
		}

		StringList pathList;
		StrConv::tokenize( tmpPath, pathList, '/' );
		return _getPath( pathList );
	}
	//############################################################################
	Widget* Widget::_getPath( StringList& pathList ) const {
		if ( pathList.size() == 0 ) return const_cast<Widget*>( this );

		const std::string top = pathList.front();
		pathList.pop_front();
		if ( !( top.length() > 0 ) ) {
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Empty path locations are not allowed", __FUNCTION__ );
			return 0;
		}
		if ( top == "." ) {
			return _getPath( pathList );
		}
		if ( top == ".." ) {
			Widget* parent = dynamic_cast<Widget*>( getParent() );
			if ( parent ) {
				return parent->_getPath( pathList );
			}
			Screen* screen = dynamic_cast<Screen*>( getParent() );
			if ( screen ) {
				return screen->_getPath( pathList );
			}
			OG_THROW( Exception::OP_FAILED, "Unknown container type. Cannot proceed to parent path", __FUNCTION__ );
		}

		Widget* child = _getChildByName( top );
		if ( child ) {
			return child->_getPath( pathList );
		}
		return 0;
	}
	//############################################################################
	/*! This function is intended for overriding should the existing method not
	produce accurate results. Overriding should only be necessary if the widget has
	children and displays them in a non-standard fashion (rotated, for example).

	This function takes the given \c point and translates its value from local
	coordinates to inner coordinates. As an example, the ContainerControl
	takes the given \c point and subtracts its position and upper left client area
	offset to it to produce a resulting point that is local to its children.
	(The children's position and size are defined within the resulting coordinate
	space)

	The result of the transform is written back to the given \c point
	*/
	void Widget::_translatePointIn( FVector2& point ) {
		/* we are not a container, so do nothing */
	}
	//############################################################################
	/*! This function is intended for overriding should the existing method not
	produce accurate results.

	It should produce the inverse result of _translatePointIn()

	This function takes the given \c point and translates its value from inner
	coordinates to local coordinates. As an example, the ContainerControl
	takes the given \c point and adds its position and upper left client area
	offset to it to produce a resulting point that is local to itself.
	(Its own position and size are defined within the resulting coordinate space)

	The result of the transform is written back to the given \c point
	*/
	void Widget::_translatePointOut( FVector2& point ) {
		/* we are not a container, so do nothing */
	}
	//############################################################################
	FVector2 Widget::pointToScreen( const FVector2& local_point ) {
		FVector2 point = local_point;
		Widget* parent = dynamic_cast<Widget*>( getParent() );
		if ( parent ) {
			parent->_doPointToScreen( point );
		}
		return point;
	}
	//############################################################################
	FVector2 Widget::pointFromScreen( const FVector2& screen_point ) {
		FVector2 point = screen_point;
		Widget* parent = dynamic_cast<Widget*>( getParent() );
		if ( parent ) {
			parent->_doPointFromScreen( point );
		}
		return point;
	}
	//############################################################################
	void Widget::_doPointToScreen( FVector2& local_point ) {
		_translatePointOut( local_point );
		Widget* parent = dynamic_cast<Widget*>( getParent() );
		if ( parent ) {
			parent->_doPointToScreen( local_point );
		}
	}
	//############################################################################
	void Widget::_doPointFromScreen( FVector2& screen_point ) {
		Widget* parent = dynamic_cast<Widget*>( getParent() );
		if ( parent ) {
			parent->_doPointFromScreen( screen_point );
		}
		_translatePointIn( screen_point );
	}
	//############################################################################
	/*! If this Widget is not attached to a Screen, the return value is always \c false. */
	bool Widget::hasCursorFocus() {
		Screen* screen = getScreen();
		if ( !screen ) return false;
		return screen->getCursorFocusedWidget() == this;
	}
	//############################################################################
	/*! If this Widget is not attached to a Screen, the return value is always \c false. */
	bool Widget::hasKeyFocus() {
		Screen* screen = getScreen();
		if ( !screen ) return false;
		return screen->getKeyFocusedWidget() == this;
	}
	//############################################################################
	bool Widget::_injectCursorMove( float xPos, float yPos ) {
		/*
		This function is responsible for culling out move events we aren't interested in,
		as well as maintaining the cursor's enter/leave state.
		This particular implementation should be flexible enough to work for all widgets,
		including containers, however it will need to be extended for containers to
		pass the events on to the children.
		*/

		// gather info about the focus state and convert the given move position if necessary
		const bool isFocused = hasCursorFocus();
		FVector2 localPos;
		if ( isFocused ) {
			localPos = pointFromScreen( FVector2( xPos, yPos ) );
		} else {
			localPos = FVector2( xPos, yPos );
		}

		bool consumed = false; // we don't consume unless we're explicitly consumed during CursorMove
		// we only pass through move events that we actually care about
		if ( isInside( localPos ) ) {
			if ( !m_CursorInside ) {
				m_CursorInside = true;
				eventCursorEnter();
			}
			assert( m_CursorInside );
			consumed = eventCursorMove( xPos, yPos );
		} else {
			if ( m_CursorInside ) {
				m_CursorInside = false;
				eventCursorLeave();
			}
			if ( isFocused ) { // if we're focused, then we should supply the move even if it is outside of our coverage area
				consumed = eventCursorMove( xPos, yPos );
			}
		}
		return consumed;
	}
	//############################################################################
	void Widget::_sendCursorMoveConsumed() {
		/*
		This function ensures that we properly receive the CursorLeave event if
		we haven't already. It will need to be extended in containers to notify
		children.
		*/
		if ( m_CursorInside ) {
			m_CursorInside = false;
			eventCursorLeave();
		}
		assert( !m_CursorInside );
	}
	//############################################################################
	bool Widget::_injectCursorPress( float xPos, float yPos ) {
		return eventCursorPress( xPos, yPos );
	}
	//############################################################################
	bool Widget::_injectCursorRelease( float xPos, float yPos ) {
		return eventCursorRelease( xPos, yPos );
	}
	//############################################################################
	bool Widget::_injectKeyDown( char character ) {
		return eventKeyDown( character );
	}
	//############################################################################
	bool Widget::_injectKeyPressed( char character ) {
		return eventKeyPressed( character );
	}
	//############################################################################
	bool Widget::_injectKeyUp( char character ) {
		return eventKeyUp( character );
	}
	//############################################################################
	void Widget::_sendCursorFocused( Widget* cur, Widget* prev ) {
		eventCursorFocused( cur, prev );
	}
	//############################################################################
	void Widget::_sendCursorFocusLost( Widget* cur, Widget* prev ) {
		eventCursorFocusLost( cur, prev );
	}
	//############################################################################
	void Widget::_sendKeyFocused( Widget* cur, Widget* prev ) {
		eventKeyFocusLost( cur, prev );
	}
	//############################################################################
	void Widget::_sendKeyFocusLost( Widget* cur, Widget* prev ) {
		eventKeyFocusLost( cur, prev );
	}
	//############################################################################
	void Widget::_getEventChildList(WidgetPtrList& childList){
		/* we have no children, so we do nothing */
	}
	//############################################################################
}//namespace OpenGUI{
