#include "OpenGUI_Screen.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_System.h"
#include "OpenGUI_Renderer.h"

namespace OpenGUI {
	//############################################################################
	Screen::Screen( const std::string& screenName, const FVector2& initialSize ) {
		mName = screenName;
		mSize = initialSize;
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
	const FVector2& Screen::getPPU() const{
		OG_NYI; //need to fix this to properly cache the result
		const IVector2& targetSize = getRenderTargetSize();
		static FVector2 dpu;
		dpu.x = ((float)targetSize.x) / mSize.x;
		dpu.y = ((float)targetSize.y) / mSize.y;
		return dpu;
	}
	//############################################################################
	const IVector2& Screen::getUPI() const{
		return mUPI;
	}
	//############################################################################
	void Screen::setUPI(const IVector2& newUPI ){
		mUPI = newUPI;
		OG_NYI; //need to invalidate pixel alignment guarantee
	}
	//############################################################################
	void Screen::update() {
	}
	//############################################################################
	const std::string& Screen::getName()const {
		return mName;
	}
	//############################################################################
	const FVector2& Screen::getSize()const {
		return mSize;
	}
	//############################################################################
	void Screen::setSize( const FVector2& newSize ){
		mSize = newSize;
		OG_NYI; //need to invalidate pixel alignment guarantee
	}
	//############################################################################
	/*! For screens rendering to the full window, this is equal to the render window resolution.
		For screens rendering to a render texture, it is the texture size.
	*/
	const IVector2& Screen::getRenderTargetSize()const {
		OG_NYI; //can I get this so I don't call System::getSingleton()._getRenderer()??
		/*
		if(isBound()){
			return renderTarget->getSize();
		}else{
			Renderer* r = System::getSingleton()._getRenderer();
			IVector2 t; r->getViewportDimensions(t);
			return t;
		}
		*/
	}
	//############################################################################
	void Screen::bindRenderTexture( RenderTexturePtr renderTexture ) {
		renderTarget = renderTexture;
		Texture* tex = 0;
		RenderTexture* rtex = 0;

		TexturePtr tptr( tex );
		RenderTexturePtr rtexPtr( rtex );
		//! \todo add recursive invalidation because pixel alignment guarantee is broken
		OG_NYI;
	}
	//############################################################################
	void Screen::unbindRenderTexture() {
		bindRenderTexture( 0 );
	}
	//############################################################################
	bool Screen::isBound()const {
		return !renderTarget.isNull();
	}

	//############################################################################
}//namespace OpenGUI{