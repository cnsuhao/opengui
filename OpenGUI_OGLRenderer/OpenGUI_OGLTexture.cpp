#include "OpenGUI_OGLRenderer.h"
#include "OpenGUI_OGLTexture.h"

#include "OpenGUI_FBO.h"

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
	OGLRTexture::OGLRTexture(){
		textureId = 0;
		fboId = 0;
		glGenFramebuffersEXT(1, &fboId);
	}
	//###########################################################
	OGLRTexture::~OGLRTexture(){
		/**/
		glDeleteFramebuffersEXT(1, &fboId);
	}
	//###########################################################
	void OGLRTexture::bind(){
		glBindTexture( GL_TEXTURE_2D, 0);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId);
	}
	//###########################################################
	void OGLRTexture::unbind(){
		glBindTexture( GL_TEXTURE_2D, 0);
		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
	}
	//###########################################################
};//namespace OpenGUI{