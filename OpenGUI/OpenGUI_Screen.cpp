#include "OpenGUI_Screen.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_System.h"
#include "OpenGUI_Renderer.h"

namespace OpenGUI{
	//############################################################################
	Screen::Screen(const std::string& screenName, const FVector2& initialSize){
		mName = screenName;
		mSize = initialSize;
		mAutoUpdating = true;
	}
	//############################################################################
	Screen::~Screen(){
		/**/
	}
	//############################################################################
	void Screen::update(){

	}
	//############################################################################
	const std::string& Screen::getName()const{
		return mName;
	}
	//############################################################################
	const FVector2& Screen::getSize()const{
		return mSize;
	}
	//############################################################################
	/*! For screens rendering to the full window, this is equal to the render window resolution.
		For screens rendering to a render texture, it is the texture size.
	*/
	IVector2 Screen::getRenderTargetSize()const{
		if(isBound()){
			return renderTarget->getSize();
		}else{
			Renderer* r = System::getSingleton()._getRenderer();
			IVector2 t; r->getViewportDimensions(t);
			return t;
		}
	}
	//############################################################################
	void Screen::bindRenderTexture( RenderTexturePtr renderTexture ){
		OG_NYI;
		renderTarget = renderTexture;
		//! \todo add recursive invalidation because pixel alignment guarantee is broken
	}
	//############################################################################
	void Screen::unbindRenderTexture(){
		bindRenderTexture( 0 );
	}
	//############################################################################
	bool Screen::isBound()const{
		return !renderTarget.isNull();
	}
	//############################################################################
}//namespace OpenGUI{