#include "OpenGUI_OGLRenderer.h"
#include "OpenGUI_OGLTexture.h"

namespace OpenGUI {
	//###########################################################
	OGLTexture::OGLTexture( Renderer* owner ): Texture( owner ) {
		textureId = 0;
	}
	//###########################################################
	OGLTexture::~OGLTexture() {}
	//###########################################################
};//namespace OpenGUI{