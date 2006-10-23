#include "OpenGUI_CONFIG.h"
#include "OpenGUI_Screen.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_System.h"
#include "OpenGUI_Renderer.h"
#include "OpenGUI_Brush.h"

namespace OpenGUI {
	class ScreenBrush: public Brush {
	public:
		ScreenBrush( Screen* screenPtr, RenderTexturePtr renderTexture ):
				mScreen( screenPtr ), mRenderTexture( renderTexture ) {}
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

	protected:
		virtual void appendRenderOperation( RenderOperation& renderOp ) {
			if ( !isActive() ) {
				Renderer::getSingleton().selectRenderContext( mRenderTexture.get() );
				markActive();
			}
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
	private:
		Screen* mScreen;
		RenderTexturePtr mRenderTexture;
	};

	//############################################################################
	Screen::Screen( const std::string& screenName, const FVector2& initialSize ) {
		mName = screenName;
		mSize = initialSize;
		mUPI = FVector2( DEFAULT_SCREEN_UPI_X, DEFAULT_SCREEN_UPI_Y );
		_DirtyPPUcache();
		mAutoUpdating = true;
		LogManager::SlogMsg( "Screen", OGLL_INFO ) << "(" << mName << ")"
		<< " Creation"
		<< " [" << mSize.toStr() << "]"
		<< Log::endlog;

		mCursorPressed = false; // cursor starts not pressed
		mCursorPos.x = mSize.x / 2.0f; // cursor starts in the middle of the Screen
		mCursorPos.y = mSize.y / 2.0f;

		m_CursorEnabled = false; // cursor starts disabled
		m_CursorVisible = true;  // cursor starts shown
	}
	//############################################################################
	Screen::~Screen() {
		LogManager::SlogMsg( "Screen", OGLL_INFO ) << "(" << mName << ") Destruction" << Log::endlog;
		/**/
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
		ScreenBrush b( this, 0 );
		WidgetCollection::iterator iter = Children.begin();
		while ( iter != Children.end() ) {
			iter->_draw( b );
			iter++;
		}
		if ( m_CursorEnabled && m_CursorVisible ) {
			// Draw the cursor
			mDefaultCursor->eventDraw( mCursorPos.x, mCursorPos.y, b );
		}
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
	If the cursor is disabled, this will always return false.*/
	bool Screen::injectCursorPosition( float x_pos, float y_pos ) {
		if ( !m_CursorEnabled ) return false;
		//store the new cursor position for future use
		mCursorPos.x = x_pos;
		mCursorPos.y = y_pos;
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
		m_CursorVisible = false;
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
}//namespace OpenGUI{