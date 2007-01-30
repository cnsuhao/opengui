// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#include "OGL_Platform.h"
#include "OGL_FBO.h"
#include "GL/glfw.h"

IsRenderbufferEXT_OG _IsRenderbufferEXT_OG;
BindRenderbufferEXT_OG _BindRenderbufferEXT_OG;
DeleteRenderbuffersEXT_OG _DeleteRenderbuffersEXT_OG;
GenRenderbuffersEXT_OG _GenRenderbuffersEXT_OG;
RenderbufferStorageEXT_OG _RenderbufferStorageEXT_OG;
GetRenderbufferParameterivEXT_OG _GetRenderbufferParameterivEXT_OG;
IsFramebufferEXT_OG _IsFramebufferEXT_OG;
BindFramebufferEXT_OG _BindFramebufferEXT_OG;
DeleteFramebuffersEXT_OG _DeleteFramebuffersEXT_OG;
GenFramebuffersEXT_OG _GenFramebuffersEXT_OG;
CheckFramebufferStatusEXT_OG _CheckFramebufferStatusEXT_OG;


FramebufferTexture1DEXT_OG _FramebufferTexture1DEXT_OG;
FramebufferTexture2DEXT_OG _FramebufferTexture2DEXT_OG;
FramebufferTexture3DEXT_OG _FramebufferTexture3DEXT_OG;

FramebufferRenderbufferEXT_OG _FramebufferRenderbufferEXT_OG;
GetFramebufferAttachmentParameterivEXT_OG _GetFramebufferAttachmentParameterivEXT_OG;
GenerateMipmapEXT_OG _GenerateMipmapEXT_OG;

bool InitializeFBO() {
	int i = glfwExtensionSupported( "GL_EXT_framebuffer_object" );
	if ( i != GL_TRUE )
		return false;

	_IsRenderbufferEXT_OG = ( IsRenderbufferEXT_OG ) glfwGetProcAddress( "glIsRenderbufferEXT" );
	if ( !_IsRenderbufferEXT_OG ) return false;
	_BindRenderbufferEXT_OG = ( BindRenderbufferEXT_OG ) glfwGetProcAddress( "glBindRenderbufferEXT" );
	if ( !_BindRenderbufferEXT_OG ) return false;
	_DeleteRenderbuffersEXT_OG = ( DeleteRenderbuffersEXT_OG ) glfwGetProcAddress( "glDeleteRenderbuffersEXT" );
	if ( !_DeleteRenderbuffersEXT_OG ) return false;
	_GenRenderbuffersEXT_OG = ( GenRenderbuffersEXT_OG ) glfwGetProcAddress( "glGenRenderbuffersEXT" );
	if ( !_GenRenderbuffersEXT_OG ) return false;
	_RenderbufferStorageEXT_OG = ( RenderbufferStorageEXT_OG ) glfwGetProcAddress( "glRenderbufferStorageEXT" );
	if ( !_RenderbufferStorageEXT_OG ) return false;
	_GetRenderbufferParameterivEXT_OG = ( GetRenderbufferParameterivEXT_OG ) glfwGetProcAddress( "glGetRenderbufferParameterivEXT" );
	if ( !_GetRenderbufferParameterivEXT_OG ) return false;
	_IsFramebufferEXT_OG = ( IsFramebufferEXT_OG ) glfwGetProcAddress( "glIsFramebufferEXT" );
	if ( !_IsFramebufferEXT_OG ) return false;
	_BindFramebufferEXT_OG = ( BindFramebufferEXT_OG ) glfwGetProcAddress( "glBindFramebufferEXT" );
	if ( !_BindFramebufferEXT_OG ) return false;
	_DeleteFramebuffersEXT_OG = ( DeleteFramebuffersEXT_OG ) glfwGetProcAddress( "glDeleteFramebuffersEXT" );
	if ( !_DeleteFramebuffersEXT_OG ) return false;
	_GenFramebuffersEXT_OG = ( GenFramebuffersEXT_OG ) glfwGetProcAddress( "glGenFramebuffersEXT" );
	if ( !_GenFramebuffersEXT_OG ) return false;
	_CheckFramebufferStatusEXT_OG = ( CheckFramebufferStatusEXT_OG ) glfwGetProcAddress( "glCheckFramebufferStatusEXT" );
	if ( !_CheckFramebufferStatusEXT_OG ) return false;

	_FramebufferTexture1DEXT_OG = ( FramebufferTexture1DEXT_OG ) glfwGetProcAddress( "glFramebufferTexture1DEXT" );
	if ( !_FramebufferTexture1DEXT_OG ) return false;
	_FramebufferTexture2DEXT_OG = ( FramebufferTexture2DEXT_OG ) glfwGetProcAddress( "glFramebufferTexture2DEXT" );
	if ( !_FramebufferTexture2DEXT_OG ) return false;
	_FramebufferTexture3DEXT_OG = ( FramebufferTexture3DEXT_OG ) glfwGetProcAddress( "glFramebufferTexture3DEXT" );
	if ( !_FramebufferTexture3DEXT_OG ) return false;

	_FramebufferRenderbufferEXT_OG = ( FramebufferRenderbufferEXT_OG ) glfwGetProcAddress( "glFramebufferRenderbufferEXT" );
	if ( !_FramebufferRenderbufferEXT_OG ) return false;

	_GetFramebufferAttachmentParameterivEXT_OG = ( GetFramebufferAttachmentParameterivEXT_OG ) glfwGetProcAddress( "glGetFramebufferAttachmentParameterivEXT" );
	if ( !_GetFramebufferAttachmentParameterivEXT_OG ) return false;

	_GenerateMipmapEXT_OG = ( GenerateMipmapEXT_OG ) glfwGetProcAddress( "glGenerateMipmapEXT" );
	if ( !_GenerateMipmapEXT_OG ) return false;

	return true;
}

