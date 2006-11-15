#include "OGL_Viewport.h"
#include "OGL_Texture.h"
#include "Renderer_OpenGL.h"

namespace OpenGUI{
	//###########################################################
	OGL_RTT_Viewport::OGL_RTT_Viewport( const IVector2& size ){
		mRenderTexture = (OGLRTexture*) static_cast<Renderer_OpenGL*>(Renderer::getSingletonPtr())->createRenderTexture(size);
		mRenderTexturePtr = mRenderTexture;
	}
	//###########################################################
	const IVector2& OGL_RTT_Viewport::getSize(){
		return mRenderTexture->getSize();
	}
	//###########################################################
}
