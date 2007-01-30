// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#include "Renderer_OpenGL.h"
#include "OGL_Texture.h"

#include "OGL_FBO.h"

namespace OpenGUI {
	//###########################################################
	OGLTexture::OGLTexture() {
		textureId = 0;
	}
	//###########################################################
	OGLTexture::~OGLTexture() {
		/**/
	}
	//###########################################################


	//###########################################################
	//###########################################################
	//###########################################################


	//###########################################################
	OGLRTexture::OGLRTexture() {
		textureId = 0;
		fboId = 0;
		glGenFramebuffersEXT( 1, &fboId );
	}
	//###########################################################
	OGLRTexture::~OGLRTexture() {
		/**/
		glDeleteFramebuffersEXT( 1, &fboId );
	}
	//###########################################################
}
;//namespace OpenGUI{