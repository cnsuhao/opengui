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
	}
	//############################################################################
	void Screen::injectCursorMovement( float x_rel, float y_rel ) {
		x_rel += mCursorPos.x;
		y_rel += mCursorPos.y;
		injectCursorPosition( x_rel, y_rel );
	}
	//############################################################################
	void Screen::injectCursorPosition( float x_pos, float y_pos ) {
		//store the new cursor position for future use
		mCursorPos.x = x_pos;
		mCursorPos.y = y_pos;

		WidgetCollection::iterator iter = Children.begin();
		while ( iter != Children.end() ) {
			iter->eventCursor_Move( x_pos, y_pos );
			iter++;
		}
	}
	//############################################################################
	void Screen::injectCursorPosition_Percent( float x_perc, float y_perc ) {
		x_perc *= mSize.x;
		y_perc *= mSize.y;
		injectCursorPosition( x_perc, y_perc );
	}
	//############################################################################
	void Screen::injectCursorPress() {
		mCursorPressed = true;
		WidgetCollection::iterator iter = Children.begin();
		while ( iter != Children.end() ) {
			iter->eventCursor_Press( mCursorPos.x, mCursorPos.y );
			iter++;
		}
	}
	//############################################################################
	void Screen::injectCursorRelease() {
		mCursorPressed = false;
		WidgetCollection::iterator iter = Children.begin();
		while ( iter != Children.end() ) {
			iter->eventCursor_Release( mCursorPos.x, mCursorPos.y );
			iter++;
		}
	}
	//############################################################################
	void Screen::injectCursorPress_State( bool pressed ) {
		if ( pressed != mCursorPressed ) {
			if ( pressed )
				injectCursorPress();
			else
				injectCursorRelease();
		}
	}
	//############################################################################
}//namespace OpenGUI{