#include "OpenGUI_CONFIG.h"
#include "OpenGUI_Screen.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_System.h"
#include "OpenGUI_Renderer.h"
#include "OpenGUI_Brush.h"
#include "OpenGUI_Control.h"
#include "OpenGUI_TimerManager.h"

//#include "OpenGUI_Brush_RTT.h"
#include "OpenGUI_TextureManager.h"

namespace OpenGUI {
	class ScreenBrush: public Brush {
	public:
		ScreenBrush( Screen* screenPtr ): mScreen( screenPtr ) {}
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
			Renderer::getSingleton().clearContents();
		}
	private:
		Screen* mScreen;
	};

	//############################################################################
	Screen::Screen( const std::string& screenName, const FVector2& initialSize ) {
		mName = screenName;
		mSize = initialSize;
		mUPI = FVector2( DEFAULT_SCREEN_UPI_X, DEFAULT_SCREEN_UPI_Y );
		_DirtyPPUcache();

		mAutoUpdating = true; // we auto update by default
		mAutoTiming = true; // we get time from System by default

		LogManager::SlogMsg( "Screen", OGLL_INFO ) << "(" << mName << ")"
		<< " Creation"
		<< " [" << mSize.toStr() << "]"
		<< Log::endlog;

		mCursorPressed = false; // cursor starts not pressed
		mCursorPos.x = mSize.x / 2.0f; // cursor starts in the middle of the Screen
		mCursorPos.y = mSize.y / 2.0f;

		m_CursorEnabled = false; // cursor starts disabled
		m_CursorVisible = true;  // cursor starts shown

		m_CursorFocus = 0; // start with no cursor focused widget
		m_KeyFocus = 0; // start with no keyboard focused widget

		mStatUpdateTimer = TimerManager::getSingleton().getTimer();
	}
	//############################################################################
	Screen::~Screen() {
		LogManager::SlogMsg( "Screen", OGLL_INFO ) << "(" << mName << ") Destruction" << Log::endlog;
		_setKeyFocus( 0 );
		_setCursorFocus( 0 );
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
			prev->eventKey_FocusLost( next, prev );
		}

		//set the new focus target
		m_KeyFocus = next;

		//notify the new of focus acquired
		if ( next ) {
			next->eventKey_Focused( next, prev );
		}
	}
	//############################################################################
	void Screen::_setCursorFocus( Widget* widget ) {
		Widget* prev = m_CursorFocus;
		Widget* next = widget;

		if ( prev == next )
			return; //skip pointless operations

		//notify previous of focus lost
		if ( prev ) {
			prev->eventCursor_FocusLost( next, prev );
		}

		//set the new focus target
		m_CursorFocus = next;

		//notify the new of focus acquired
		if ( next ) {
			next->eventCursor_Focused( next, prev );
		}

		//inject a Cursor_Move to update the new receiver about the cursor's position
		_injectCursorPosition( mCursorPos.x, mCursorPos.y );
	}
	//############################################################################
	void Screen::_UpdatePPU() const {
		const IVector2& targetSize = getRenderTargetSize();
		mPPUcache.x = (( float )targetSize.x ) / mSize.x;
		mPPUcache.y = (( float )targetSize.y ) / mSize.y;
		mPPUcache_valid = true;
	}
	//############################################################################
	void Screen::setUPI( const FVector2& newUPI ) {
		LogManager::SlogMsg( "Screen", OGLL_INFO ) << "(" << mName << ")"
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
		LogManager::SlogMsg( "Screen", OGLL_INFO ) << "(" << mName << ")"
		<< " Changed Size"
		<< " From:" << mSize.toStr() << " To:" << newSize.toStr()
		<< Log::endlog;

		mSize = newSize;
		_DirtyPPUcache();

		invalidateAll();
	}
	//############################################################################
	/*! For screens rendering to the full window, this is equal to the render window resolution.
		For screens rendering to a render texture, it is the texture size.
	*/
	const IVector2& Screen::getRenderTargetSize()const {
		if ( isBound() ) {
			return renderTarget->getSize();
		} else {
			return Renderer::getSingleton().getViewportDimensions();
		}
	}
	//############################################################################
	void Screen::bindRenderTexture( RenderTexturePtr renderTexture ) {
		renderTarget = renderTexture;
		Texture* tex = 0;
		RenderTexture* rtex = 0;

		TexturePtr tptr( tex );
		RenderTexturePtr rtexPtr( rtex );

		_DirtyPPUcache();

		invalidateAll();
	}
	//############################################################################
	void Screen::unbindRenderTexture() {
		bindRenderTexture( 0 );
		_DirtyPPUcache();
	}
	//############################################################################
	bool Screen::isBound()const {
		return !renderTarget.isNull();
	}
	//############################################################################
	void Screen::_notifyViewportDimensionsChanged() {
		if ( !isBound() ) {
			invalidateAll();
		}
		_DirtyPPUcache();
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
	void Screen::update() {
		ScreenBrush b( this  );

		WidgetCollection::iterator iter = Children.begin();
		while ( iter != Children.end() ) {
			iter->_draw( b );
			iter++;
		}
		if ( m_CursorEnabled && m_CursorVisible ) {
			// determine the cursor we're drawing
			CursorPtr drawCursor;
			Widget* overWidget = getWidgetAt( mCursorPos, true );
			if ( overWidget ) {
				Control* overControl = dynamic_cast<Control*>( overWidget );
				if ( overControl ) {
					drawCursor = overControl->_getCursor();
				}
			}
			if ( !drawCursor )
				drawCursor = mDefaultCursor;

			// send notifications if necessary
			if ( drawCursor != mPrevCursor ) {
				if ( mPrevCursor )
					mPrevCursor->eventCursor_Hidden();
				mPrevCursor = drawCursor;
				if ( mPrevCursor )
					mPrevCursor->eventCursor_Shown( mCursorPos.x, mCursorPos.y );
			}

			// Draw the cursor
			if ( drawCursor )
				drawCursor->eventDraw( mCursorPos.x, mCursorPos.y, b );
		}

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
		m_KeyFocus->eventKey_Down( character );
		retval = m_KeyFocus->eventKey_Entered( character );
		m_KeyFocus->eventKey_Up( character );
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
	bool Screen::_injectCursorPosition( float x_pos, float y_pos ) {
		//store the new cursor position for future use
		mCursorPos.x = x_pos;
		mCursorPos.y = y_pos;

		//send to focus holder if present
		if ( m_CursorFocus ) {
			return m_CursorFocus->eventCursor_Move( x_pos, y_pos );
		}

		//send to everyone
		bool retval = false;
		WidgetCollection::iterator iter = Children.begin();
		while ( iter != Children.end() ) {
			retval = iter->eventCursor_Move( x_pos, y_pos ) ? true : retval;
			iter++;
		}
		return retval;
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

		//send to focus holder if present
		if ( m_CursorFocus ) {
			return m_CursorFocus->eventCursor_Press( mCursorPos.x, mCursorPos.y );
		}

		//send to everyone else
		bool retval = false;
		WidgetCollection::iterator iter = Children.begin();
		while ( iter != Children.end() ) {
			retval = iter->eventCursor_Press( mCursorPos.x, mCursorPos.y ) ? true : retval;
			iter++;
		}
		return retval;
	}
	//############################################################################
	/*! If the cursor is disabled, this will always return false. */
	bool Screen::injectCursorRelease() {
		if ( !m_CursorEnabled ) return false;
		mCursorPressed = false;

		//send to focus holder if present
		if ( m_CursorFocus ) {
			return m_CursorFocus->eventCursor_Release( mCursorPos.x, mCursorPos.y );
		}

		//send to everyone else
		bool retval = false;
		WidgetCollection::iterator iter = Children.begin();
		while ( iter != Children.end() ) {
			retval = iter->eventCursor_Release( mCursorPos.x, mCursorPos.y ) ? true : retval;
			iter++;
		}
		return retval;
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
	/*! Cursor starts disabled, so you will need to call this to enabled it before
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
			WidgetCollection::iterator iter = Children.begin();
			while ( iter != Children.end() ) {
				iter->eventCursor_Enabled( mCursorPos.x, mCursorPos.y );
				iter++;
			}
		}
	}
	//############################################################################
	/*! Multiple calls have no ill effect. */
	void Screen::disableCursor() {
		if ( m_CursorEnabled ) {
			if ( mPrevCursor ) {
				mPrevCursor->eventCursor_Hidden();
				mPrevCursor = 0;
			}
			m_CursorEnabled = false;
			WidgetCollection::iterator iter = Children.begin();
			while ( iter != Children.end() ) {
				iter->eventCursor_Disabled();
				iter++;
			}
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
				mPrevCursor->eventCursor_Hidden();
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
			if ( child->_isInside( position ) ) {
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
			if ( child->_isInside( position ) ) {
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
}//namespace OpenGUI{