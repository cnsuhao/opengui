// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_CONFIG.h"
#include "OpenGUI_Screen.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_System.h"
#include "OpenGUI_Renderer.h"
#include "OpenGUI_Brush.h"
#include "OpenGUI_Control.h"
#include "OpenGUI_TimerManager.h"
#include "OpenGUI_Viewport.h"
#include "OpenGUI_TextureManager.h"
#include "OpenGUI_Macros.h"


namespace OpenGUI {
	class ScreenBrush: public Brush {
	public:
		ScreenBrush( Screen* screenPtr, Viewport* viewport ): mScreen( screenPtr ), mViewport( viewport ) {
			if ( !mViewport )
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Invalid Viewport", __FUNCTION__ );
		}
		virtual ~ScreenBrush() {
			/**/
		}

		virtual const FVector2& getDrawSize() const {
			return mScreen->getSize();
		}
		virtual const FVector2& getPPU_Raw() const {
			return mScreen->getPPU();
		}
		virtual const FVector2& getUPI_Raw() const {
			return mScreen->getUPI();
		}
		virtual bool isRTTContext() const {
			/* regardless of whether we are or not, we say that we aren't */
			return false;
		}

	protected:
		virtual void appendRenderOperation( RenderOperation& renderOp ) {
			for ( TriangleList::iterator iter = renderOp.triangleList->begin();
					iter != renderOp.triangleList->end(); iter++ ) {
				Triangle& t = ( *iter );
				for ( int i = 0; i < 3; i++ ) {
					t.vertex[i].position.x /= getDrawSize().x;
					t.vertex[i].position.y /= getDrawSize().y;
				}
			}
			Renderer::getSingleton().doRenderOperation( renderOp );
		}
		virtual void onActivate() {
			Renderer::getSingleton().selectRenderContext( 0 );
		}
		virtual void onClear() {
			/* we don't try to clear viewports */
		}
	private:
		Screen* mScreen;
		Viewport* mViewport;
	};

	//############################################################################
	//############################################################################
	SimpleProperty_FVector2( ScreenProp_Size, "Size", Screen, getSize, setSize );
	SimpleProperty_Bool( ScreenProp_Active, "Active", Screen, isActive, setActive );
	SimpleProperty_Bool( ScreenProp_AUpdate, "AutoUpdate", Screen, isAutoUpdating, setAutoUpdating );
	SimpleProperty_Bool( ScreenProp_ATime, "AutoTime", Screen, isAutoTiming, setAutoTiming );
	class ScreenProp_Name_CLASS : public ObjectProperty {
	public:
		virtual ~ScreenProp_Name_CLASS() {}
		virtual const char* getAccessorName() {
			return "Name";
		}
		virtual void get( Object& objectRef, Value& valueOut ) {
			try {
				Screen& s = dynamic_cast<Screen&>( objectRef );
				valueOut.setValue( s.getName() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		virtual void set( Object& objectRef, Value& valueIn ) {
			/* read-only */
		}
		virtual Value::ValueType getPropertyType() {
			return Value::T_STRING;
		}
		virtual bool getPermSettable() {
			return false;
		}
	}
	ScreenProp_Name;
	//############################################################################
	class Screen_ObjectAccessorList : public ObjectAccessorList {
	public:
		Screen_ObjectAccessorList() {
			addAccessor( &ScreenProp_Size );
			addAccessor( &ScreenProp_Active );
			addAccessor( &ScreenProp_AUpdate );
			addAccessor( &ScreenProp_ATime );
			addAccessor( &ScreenProp_Name );
		}
		~Screen_ObjectAccessorList() {}
	}
	gScreen_ObjectAccessorList;
	//############################################################################
	ObjectAccessorList* Screen::getAccessors() {
		return &gScreen_ObjectAccessorList;
	}
	//############################################################################
	//############################################################################
	Screen::Screen( const std::string& screenName, const FVector2& initialSize, Viewport* viewport ) {
		if ( gScreen_ObjectAccessorList.getParent() == 0 )
			gScreen_ObjectAccessorList.setParent( Object::getAccessors() );

		mName = screenName;
		mSize = initialSize;
		mUPI = FVector2( DEFAULT_SCREEN_UPI_X, DEFAULT_SCREEN_UPI_Y );
		_DirtyPPUcache();

		Children.setParent( this ); // mark ownership of the WidgetCollection
		mCursorPressed = false; // cursor starts not pressed
		mCursorPos.x = mSize.x / 2.0f; // cursor starts in the middle of the Screen
		mCursorPos.y = mSize.y / 2.0f;

		m_CursorEnabled = false; // cursor starts disabled
		m_CursorVisible = true;  // cursor starts shown

		m_CursorFocus = 0; // start with no cursor focused widget
		m_KeyFocus = 0; // start with no keyboard focused widget

		mStatUpdateTimer = TimerManager::getSingleton().getTimer();

		mAutoUpdating = true; // we auto update by default
		mAutoTiming = true; // we get time from System by default
		mActive = true; // active by default
		mViewport = 0; // current viewport
		setViewport( viewport ); // we do it this way to ensure proper Screen->Viewport linkage

		std::stringstream ss;
		ss << "[" << mName << "] Creation  --  Size: " << mSize.toStr();
		if ( mViewport )
			ss << "  Viewport: " << mViewport->getSize().toStr();
		else
			ss << "  No Viewport";
		LogManager::SlogMsg( "Screen", OGLL_INFO ) << ss.str() << Log::endlog;
	}
	//############################################################################
	Screen::~Screen() {
		LogManager::SlogMsg( "Screen", OGLL_INFO ) << "[" << mName << "] Destruction" << Log::endlog;
		_setKeyFocus( 0 );
		_setCursorFocus( 0 );
		setViewport( 0 ); // release from the current viewport, if there is one
		/**/
	}
	//############################################################################
	Widget* Screen::getKeyFocusedWidget() {
		return m_KeyFocus;
	}
	//############################################################################
	Widget* Screen::getCursorFocusedWidget() {
		return m_CursorFocus;
	}
	//############################################################################
	void Screen::_setKeyFocus( Widget* widget ) {
		Widget* prev = m_KeyFocus;
		Widget* next = widget;
		//notify previous of focus lost
		if ( prev ) {
			prev->_injectKeyFocusLost( next, prev );
		}

		//set the new focus target
		m_KeyFocus = next;

		//notify the new of focus acquired
		if ( next ) {
			next->_injectKeyFocused( next, prev );
		}
	}
	//############################################################################
	void Screen::_setCursorFocus( Widget* widget, bool issueMove ) {
		Widget* prev = m_CursorFocus;
		Widget* next = widget;

		if ( prev == next )
			return; //skip pointless operations

		//notify previous of focus lost
		if ( prev ) {
			prev->_injectCursorFocusLost( next, prev );
		}

		//set the new focus target
		m_CursorFocus = next;

		//notify the new of focus acquired
		if ( next ) {
			next->_injectCursorFocused( next, prev );
		}

		//inject a CursorMove to update the new receiver about the cursor's position
		if ( issueMove )
			_injectCursorPosition( mCursorPos.x, mCursorPos.y );
	}
	//############################################################################
	void Screen::_UpdatePPU() const {
		Viewport* v = getViewport();
		if ( !v )
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "Cannot calculate UPI without a target Viewport", __FUNCTION__ );
		const IVector2& targetSize = v->getSize();
		mPPUcache.x = (( float )targetSize.x ) / mSize.x;
		mPPUcache.y = (( float )targetSize.y ) / mSize.y;
		mPPUcache_valid = true;
	}
	//############################################################################
	void Screen::setUPI( const FVector2& newUPI ) {
		LogManager::SlogMsg( "Screen", OGLL_INFO ) << "[" << mName << "]"
		<< " Changed UnitsPerInch"
		<< " From:" << mUPI.toStr() << " To:" << newUPI.toStr()
		<< Log::endlog;

		mUPI = newUPI;
		invalidateAll();
	}
	//############################################################################
	const std::string& Screen::getName() const {
		return mName;
	}
	//############################################################################
	const FVector2& Screen::getSize() const {
		return mSize;
	}
	//############################################################################
	void Screen::setSize( const FVector2& newSize ) {
		LogManager::SlogMsg( "Screen", OGLL_INFO ) << "[" << mName << "]"
		<< " Changed Size"
		<< " From:" << mSize.toStr() << " To:" << newSize.toStr()
		<< Log::endlog;

		mSize = newSize;
		_DirtyPPUcache();
		invalidateAll();
	}
	//############################################################################
	void Screen::setViewport( Viewport* viewport ) {
		if ( viewport != mViewport ) {
			if ( mViewport )
				mViewport->_screenDetach( this );
			mViewport = viewport;
			if ( mViewport )
				mViewport->_screenAttach( this );

			// any previous cache data is no longer useful
			// we can't render without a viewport, so why keep it
			_DirtyPPUcache();
			invalidateAll();
		}
	}
	//############################################################################
	Viewport* Screen::getViewport() const {
		return mViewport;
	}
	//############################################################################
	void Screen::invalidateAll() {
		WidgetCollection::iterator iter = Children.begin();
		while ( iter != Children.end() ) {
			iter->flush();
			iter++;
		}
	}
	//############################################################################
	/*! If the Screen is not marked active, or does not have a valid Viewport assigned,
	this function will return immediately with no error. */
	void Screen::update() {
		if ( !_isRenderable() )
			return; //abort if we are unsuitable for drawing for any reason

		Renderer& renderer = Renderer::getSingleton();
		renderer.selectViewport( mViewport ); // inform renderer of new viewport selection
		renderer.preRenderSetup(); // begin render sequence
		mViewport->preUpdate( this ); // inform the viewport that it is about to be updated

		// if pixel alignment changed since last render...
		if ( mPrevViewportSize != mViewport->getSize() ) {
			_DirtyPPUcache(); // this will need to be recalculated on next use
			invalidateAll(); // blow out any widget caches, since they are certainly inaccurate
			mPrevViewportSize = mViewport->getSize(); //keep this for next render
		}

		ScreenBrush b( this, mViewport );

		WidgetCollection::reverse_iterator iter, iterend = Children.rend();
		for ( iter = Children.rbegin(); iter != iterend; iter++ ) {
			iter->_draw( b );
		}
		if ( m_CursorEnabled && m_CursorVisible ) {
			// determine the cursor we're drawing
			CursorPtr drawCursor;
			Widget* overWidget = getWidgetAt( mCursorPos, true );
			if ( overWidget ) {
				Control* overControl = dynamic_cast<Control*>( overWidget );
				if ( overControl ) {
					drawCursor = overControl->_getCurrentCursor();
				}
			}
			if ( !drawCursor )
				drawCursor = mDefaultCursor;

			// send notifications if necessary
			if ( drawCursor != mPrevCursor ) {
				if ( mPrevCursor )
					mPrevCursor->eventCursorHidden();
				mPrevCursor = drawCursor;
				if ( mPrevCursor )
					mPrevCursor->eventCursorShown( mCursorPos.x, mCursorPos.y );
			}

			// Draw the cursor
			if ( drawCursor )
				drawCursor->eventDraw( mCursorPos.x, mCursorPos.y, b );
		}


		mViewport->postUpdate( this ); // inform the viewport that it is done being updated
		renderer.postRenderCleanup(); // end render sequence

		//! \todo timing here is broken. #100
		float time = (( float )mStatUpdateTimer->getMilliseconds() ) / 1000.0f;
		_updateStats_UpdateTime( time );
		mStatUpdateTimer->reset();
	}
	//############################################################################
	void Screen::injectTime( unsigned int milliseconds ) {
		float seconds;
		seconds = (( float )milliseconds ) / 1000.0f;
		injectTime( seconds );
	}
	//############################################################################
	void Screen::injectTime( float seconds ) {
		WidgetCollection::iterator iter = Children.begin();
		while ( iter != Children.end() ) {
			iter->_tick( seconds );
			iter++;
		}
	}
	//############################################################################
	/*!
	\note this is a temporary implementation that will be replaced with a more useful system
	\todo finish me
	*/
	bool Screen::injectCharacter( char character ) {
		//!\todo fix this to support separate key-up / key-down, typematic repeat, and key->character maps

		if ( !m_KeyFocus ) // we only send key events to those that ask for it
			return false;

		bool retval = false;

		Key_EventArgs downargs = Key_EventArgs( character );
		m_KeyFocus->_injectKeyDown( downargs );
		if ( downargs.Consumed ) retval = true;

		Key_EventArgs pressargs = Key_EventArgs( character );
		m_KeyFocus->_injectKeyPressed( pressargs );
		if ( pressargs.Consumed ) retval = true;

		Key_EventArgs upargs = Key_EventArgs( character );
		m_KeyFocus->_injectKeyUp( upargs );
		if ( upargs.Consumed ) retval = true;

		return retval;
	}
	//############################################################################
	/*! Positive values causes right or downward movement depending on axis.
	Values of 0.0f on both axis are ignored. If the cursor is disabled, this will always return false. */
	bool Screen::injectCursorMovement( float x_rel, float y_rel ) {
		x_rel += mCursorPos.x;
		y_rel += mCursorPos.y;
		return injectCursorPosition( x_rel, y_rel );
	}
	//############################################################################
	/*! 0.0 x 0.0 is the upper left corner of the screen.
	If the cursor is disabled, this will always return false.
	If the given position is the same as the previous position, this will return false with no event
	generated. */
	bool Screen::injectCursorPosition( float x_pos, float y_pos ) {
		//skip if cursor disabled and if no movement really occurred
		if ( !m_CursorEnabled ) return false;
		if ( mCursorPos.x == x_pos && mCursorPos.y == y_pos ) return false;

		return _injectCursorPosition( x_pos, y_pos );
	}
	//############################################################################
	bool Screen::_injectCursorPosition( float x_pos, float y_pos, bool preConsumed ) {
		// before we do anything, abort if the cursor is disabled
		if ( !m_CursorEnabled ) return false;

		//store the new cursor position for future use
		mCursorPos.x = x_pos;
		mCursorPos.y = y_pos;

		//send to the active cursor, if we have one
		if ( mPrevCursor ) {
			mPrevCursor->eventCursorMove( mCursorPos.x, mCursorPos.y );
		}

		//send to just focus holder if present
		if ( m_CursorFocus ) {
			FVector2 localPos( x_pos, y_pos );
			localPos = m_CursorFocus->pointFromScreen( localPos );
			Cursor_EventArgs moveEvent( localPos.x, localPos.y );
			if ( preConsumed ) moveEvent.eat();
			m_CursorFocus->_injectCursorMove( moveEvent );
			return true; // see end of function note
		}

		//send to everyone
		Cursor_EventArgs moveEvent( x_pos, y_pos );
		if ( preConsumed ) moveEvent.eat();
		WidgetCollection::iterator i, ie = Children.end();
		for ( i = Children.begin(); i != ie; i++ ) {
			i->_injectCursorMove( moveEvent );
		}

		// we always return true if the move was issued to the widgets, regardless if anyone consumed it
		// (merely processing it signifies that it was useful)
		return true;
	}
	//############################################################################
	/*! 0.0 x 0.0 is the upper left corner of the screen, 1.0 x 1.0 is the lower right of the screen.
	If the cursor is disabled, this will always return false.*/
	bool Screen::injectCursorPosition_Percent( float x_perc, float y_perc ) {
		x_perc *= mSize.x;
		y_perc *= mSize.y;
		return injectCursorPosition( x_perc, y_perc );
	}
	//############################################################################
	/*! If the cursor is disabled, this will always return false. */
	bool Screen::injectCursorPress() {
		if ( !m_CursorEnabled ) return false;
		mCursorPressed = true;

		//send to the active cursor, if we have one
		if ( mPrevCursor ) {
			mPrevCursor->eventCursorPress( mCursorPos.x, mCursorPos.y );
		}

		//send to just focus holder if present
		if ( m_CursorFocus ) {
			FVector2 localPos = m_CursorFocus->pointFromScreen( mCursorPos );
			Cursor_EventArgs pressEvent( localPos.x, localPos.y );
			m_CursorFocus->_injectCursorPress( pressEvent );
			return pressEvent.Consumed; // return the consumption value
		}

		//send to everyone else
		Cursor_EventArgs pressEvent( mCursorPos.x, mCursorPos.y );
		WidgetCollection::iterator i, ie = Children.end();
		for ( i = Children.begin(); i != ie; i++ ) {
			i->_injectCursorPress( pressEvent );
		}

		return pressEvent.Consumed; // return the consumption value
	}
	//############################################################################
	/*! If the cursor is disabled, this will always return false. */
	bool Screen::injectCursorRelease() {
		if ( !m_CursorEnabled ) return false;
		mCursorPressed = false;

		//send to the active cursor, if we have one
		if ( mPrevCursor ) {
			mPrevCursor->eventCursorRelease( mCursorPos.x, mCursorPos.y );
		}

		//send to just focus holder if present
		if ( m_CursorFocus ) {
			FVector2 localPos = m_CursorFocus->pointFromScreen( mCursorPos );
			Cursor_EventArgs releaseEvent( localPos.x, localPos.y );
			m_CursorFocus->_injectCursorRelease( releaseEvent );
			return releaseEvent.Consumed; // return the consumption value
		}

		//send to everyone else
		Cursor_EventArgs releaseEvent( mCursorPos.x, mCursorPos.y );
		WidgetCollection::iterator i, ie = Children.end();
		for ( i = Children.begin(); i != ie; i++ ) {
			i->_injectCursorRelease( releaseEvent );
		}

		return releaseEvent.Consumed; // return the consumption value
	}
	//############################################################################
	/*! If the cursor is disabled, this will always return false. */
	bool Screen::injectCursorPress_State( bool pressed ) {
		if ( pressed != mCursorPressed ) {
			if ( pressed )
				return injectCursorPress();
			else
				return injectCursorRelease();
		}
		return false;
	}
	//############################################################################
	/*! Cursor starts disabled, so you will need to call this to enable it before
	you can realistically use it. Multiple calls have no ill effect.
	\note You cannot enable a visible cursor until the default cursor for the Screen
	has been set. If no default cursor is set when this is called, the cursor will
	be immediately hidden via \c hideCursor().*/
	void Screen::enableCursor() {
		if ( !m_CursorEnabled ) {
			m_CursorEnabled = true;
			if ( mDefaultCursor.isNull() && cursorVisible() ) {
				hideCursor();
			}

			// send a null move to bring the GUI state into proper planetary alignment
			_injectCursorPosition( mCursorPos.x, mCursorPos.y );
		}
	}
	//############################################################################
	/*! Multiple calls have no ill effect. */
	void Screen::disableCursor() {
		if ( m_CursorEnabled ) {
			if ( mPrevCursor ) {
				mPrevCursor->eventCursorHidden();
				mPrevCursor = 0;
			}
			m_CursorEnabled = false;

			// clear any existing cursor focus, but don't issue the state updating move event
			_setCursorFocus( 0, false );

			// end any existing cursor involvement by issuing a sweeping consumed event
			_injectCursorPosition( mCursorPos.x, mCursorPos.y, true );
		}
	}
	//############################################################################
	bool Screen::cursorEnabled() {
		return m_CursorEnabled;
	}
	//############################################################################
	/*! Cursor starts shown, so you do not need to call this unless you've previously
	hidden the cursor. Multiple calls have no ill effect.
	\note As stated in enableCursor(), you cannot show the cursor until a default
	cursor for the Screen has been set. You can toggle cursor visibility freely
	while the cursor is disabled, but attempting to force showing of the cursor
	while it is enabled and there is no default will throw an exception. */
	void Screen::showCursor() {
		if ( cursorEnabled() && mDefaultCursor.isNull() )
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "Cannot show enabled cursor on Screen without a default cursor", __FUNCTION__ );
		m_CursorVisible = true;
	}
	//############################################################################
	/*! Multiple calls have no ill effect. */
	void Screen::hideCursor() {
		if ( m_CursorVisible ) {
			m_CursorVisible = false;
			if ( mPrevCursor ) {
				mPrevCursor->eventCursorHidden();
				mPrevCursor = 0;
			}
		}
	}
	//############################################################################
	bool Screen::cursorVisible() {
		return m_CursorVisible;
	}
	//############################################################################
	/*! If you assign a null pointer as the new cursor and the cursor is enabled,
	this will cause the cursor to become hidden automatically. */
	void Screen::setCursor( CursorPtr cursor ) {
		if ( cursor.isNull() && cursorEnabled() && cursorVisible() ) {
			hideCursor();
		}
		mDefaultCursor = cursor;
	}
	//############################################################################
	Widget* Screen::getWidgetAt( const FVector2& position, bool recursive ) {
		for ( WidgetCollection::iterator iter = Children.begin();iter != Children.end(); iter++ ) {
			Widget* child = iter.get();
			if ( child->isInside( position ) ) {
				Widget* ret = child;
				if ( recursive ) {
					child = child->getChildAt( position, true );
					if ( child )
						ret = child;
				}
				return ret;
			}
		}
		return 0;
	}
	//############################################################################
	void Screen::getWidgetsAt( const FVector2& position, WidgetPtrList& outList, bool recursive ) {
		for ( WidgetCollection::iterator iter = Children.begin(); iter != Children.end(); iter++ ) {
			Widget* child = iter.get();
			if ( child->isInside( position ) ) {
				if ( recursive ) {
					child->getChildrenAt( position, outList, true );
				}
				outList.push_back( child );
			}
		}
	}
	//############################################################################
	/*! */
	float Screen::statsGetUpdateTime() {
		return mStatUpdate.getAverage();
	}
	//############################################################################
	void Screen::_updateStats_UpdateTime( float newTime ) {
		mStatUpdate.addRecord( newTime );
	}
	//############################################################################
	void Screen::statsResetUpdateTime() {
		mStatUpdate.reset();
	}
	//############################################################################
	/*! \see Widget::getPath() for a more in-depth explanation of paths */
	Widget* Screen::getPath( const std::string& path ) const {
		std::string tmpPath = path;
		StrConv::trim( tmpPath );

		StringList pathList;
		StrConv::tokenize( tmpPath, pathList, '/' );
		if ( pathList.front() == "" ) {
			//this was a request for an absolute path
			//so just pop off the first entry and continue
			pathList.pop_front();
		}
		return _getPath( pathList );
	}
	//############################################################################
	Widget* Screen::_getPath( StringList& pathList ) const {
		if ( pathList.size() == 0 ) {
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Paths cannot resolve to Screen objects", __FUNCTION__ );
			return 0;
		}

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
			OG_THROW( Exception::OP_FAILED, "Cannot proceed above Screen. There is no higher container.", __FUNCTION__ );
			return 0;
		}

		Widget* child = Children.getWidget( top );
		if ( child ) {
			return child->_getPath( pathList );
		}
		return 0;
	}
	//############################################################################
	/*! A Screen cannot be truly active unless it is both set active, and has a valid Viewport assigned.
	All Screens are created with the "active" flag set initially to true regardless of if they are
	created already attached to a Viewport or not. This flag can be freely toggled regardless of
	the presence or lack of a Viewport, but the Screen will never evaluate as "renderable" unless
	it is both marked active and has an assigned Viewport.
	*/
	void Screen::setActive( bool active ) {
		mActive = active;
	}
	//############################################################################
	/*! \see setActive() */
	bool Screen::isActive() {
		return mActive;
	}
	//############################################################################
	bool Screen::_isRenderable() {
		return mActive && mViewport;
	}
	//############################################################################
	const FVector2& Screen::getCursorPos() const {
		return mCursorPos;
	}
	//############################################################################
	FVector2 Screen::getCursorPos_Percent() const {
		FVector2 ret = mCursorPos;
		ret = mCursorPos / mSize;
		return ret;
	}
	//############################################################################
	unsigned int Screen::getObjectType() const {
		return OT_SCREEN;
	}
	//############################################################################
}//namespace OpenGUI{
