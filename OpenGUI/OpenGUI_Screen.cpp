#include "OpenGUI_Screen.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_System.h"
#include "OpenGUI_Renderer.h"

namespace OpenGUI {
	//############################################################################
	Screen::Screen( const std::string& screenName, const FVector2& initialSize ) {
		mName = screenName;
		mSize = initialSize;
		_DirtyPPUcache();
		mAutoUpdating = true;
		LogManager::SlogMsg( "Screen", OGLL_INFO ) << "(" << mName << ")"
		<< " Creation"
		<< " [" << mSize.toStr() << "]"
		<< Log::endlog;
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
	void Screen::setUPI( const IVector2& newUPI ) {
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
		if(isBound()){
			return renderTarget->getSize();
		}else{
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
	void Screen::_notifyViewportDimensionsChanged(){
		if(!isBound()){
			invalidateAll();
		}
	}
	//############################################################################
	void Screen::invalidateAll() {
		WidgetCollection::iterator iter = Children.begin();
		while( iter != Children.end() ){
			iter->flush();
			iter++;
		}			
	}
	//############################################################################
	void Screen::update() {
		OG_NYI;
	}
	//############################################################################
}//namespace OpenGUI{