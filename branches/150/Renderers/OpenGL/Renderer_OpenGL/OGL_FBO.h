// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#ifndef OpenGUI_FBO_h__
#define OpenGUI_FBO_h__

#include "OGL_Platform.h"

#if OGL_PLATFORM == OGL_PLATFORM_WIN32
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library
#endif // OGL_PLATFORM == OGL_PLATFORM_WIN32

#if OGL_PLATFORM == OGL_PLATFORM_LINUX
#include <GL/gl.h>			// Header File For The OpenGL Library
#include <GL/glu.h>			// Header File For The GLu Library
#endif // OGL_PLATFORM == OGL_PLATFORM_LINUX

#define GL_FRAMEBUFFER_EXT                     0x8D40
#define GL_RENDERBUFFER_EXT                    0x8D41

#define GL_STENCIL_INDEX_EXT                   0x8D45
#define GL_STENCIL_INDEX1_EXT                  0x8D46
#define GL_STENCIL_INDEX4_EXT                  0x8D47
#define GL_STENCIL_INDEX8_EXT                  0x8D48
#define GL_STENCIL_INDEX16_EXT                 0x8D49

#define GL_RENDERBUFFER_WIDTH_EXT              0x8D42
#define GL_RENDERBUFFER_HEIGHT_EXT             0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT_EXT    0x8D44

#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT            0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT            0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_EXT          0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_EXT  0x8CD3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_EXT     0x8CD4

#define GL_COLOR_ATTACHMENT0_EXT                0x8CE0
#define GL_COLOR_ATTACHMENT1_EXT                0x8CE1
#define GL_COLOR_ATTACHMENT2_EXT                0x8CE2
#define GL_COLOR_ATTACHMENT3_EXT                0x8CE3
#define GL_COLOR_ATTACHMENT4_EXT                0x8CE4
#define GL_COLOR_ATTACHMENT5_EXT                0x8CE5
#define GL_COLOR_ATTACHMENT6_EXT                0x8CE6
#define GL_COLOR_ATTACHMENT7_EXT                0x8CE7
#define GL_COLOR_ATTACHMENT8_EXT                0x8CE8
#define GL_COLOR_ATTACHMENT9_EXT                0x8CE9
#define GL_COLOR_ATTACHMENT10_EXT               0x8CEA
#define GL_COLOR_ATTACHMENT11_EXT               0x8CEB
#define GL_COLOR_ATTACHMENT12_EXT               0x8CEC
#define GL_COLOR_ATTACHMENT13_EXT               0x8CED
#define GL_COLOR_ATTACHMENT14_EXT               0x8CEE
#define GL_COLOR_ATTACHMENT15_EXT               0x8CEF
#define GL_DEPTH_ATTACHMENT_EXT                 0x8D00
#define GL_STENCIL_ATTACHMENT_EXT               0x8D20

#define GL_FRAMEBUFFER_COMPLETE_EXT                          0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT             0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT     0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT_EXT   0x8CD8
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT             0x8CD9
#define GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT                0x8CDA
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT            0x8CDB
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT            0x8CDC
#define GL_FRAMEBUFFER_UNSUPPORTED_EXT                       0x8CDD
#define GL_FRAMEBUFFER_STATUS_ERROR_EXT                      0x8CDE

#define GL_FRAMEBUFFER_BINDING_EXT             0x8CA6
#define GL_RENDERBUFFER_BINDING_EXT            0x8CA7
#define GL_MAX_COLOR_ATTACHMENTS_EXT           0x8CDF
#define GL_MAX_RENDERBUFFER_SIZE_EXT           0x84E8

#define GL_INVALID_FRAMEBUFFER_OPERATION_EXT   0x0506


//boolean IsRenderbufferEXT(uint renderbuffer);
typedef GLboolean( APIENTRY * IsRenderbufferEXT_OG )( GLuint renderbuffer );
extern IsRenderbufferEXT_OG _IsRenderbufferEXT_OG;
#define glIsRenderbufferEXT _IsRenderbufferEXT_OG

//void BindRenderbufferEXT(enum target, uint renderbuffer);
typedef void( APIENTRY * BindRenderbufferEXT_OG )( GLenum target, GLuint renderbuffer );
extern BindRenderbufferEXT_OG _BindRenderbufferEXT_OG;
#define glBindRenderbufferEXT _BindRenderbufferEXT_OG

//////////////////////////////////////////

//void DeleteRenderbuffersEXT(sizei n, const uint *renderbuffers);
typedef void( APIENTRY * DeleteRenderbuffersEXT_OG )( GLsizei n, const GLuint *renderbuffers );
extern DeleteRenderbuffersEXT_OG _DeleteRenderbuffersEXT_OG;
#define glDeleteRenderbuffersEXT _DeleteRenderbuffersEXT_OG

//void GenRenderbuffersEXT(sizei n, uint *renderbuffers);
typedef void( APIENTRY * GenRenderbuffersEXT_OG )( GLsizei n, GLuint *renderbuffers );
extern GenRenderbuffersEXT_OG _GenRenderbuffersEXT_OG;
#define glGenRenderbuffersEXT _GenRenderbuffersEXT_OG

//void RenderbufferStorageEXT(enum target, enum internalformat, sizei width, sizei height);
typedef void( APIENTRY * RenderbufferStorageEXT_OG )( GLenum target, GLenum internalformat, GLsizei width, GLsizei height );
extern RenderbufferStorageEXT_OG _RenderbufferStorageEXT_OG;
#define glRenderbufferStorageEXT _RenderbufferStorageEXT_OG

//void GetRenderbufferParameterivEXT(enum target, enum pname, int* params);
typedef void( APIENTRY * GetRenderbufferParameterivEXT_OG )( GLenum target, GLenum pname, GLint* params );
extern GetRenderbufferParameterivEXT_OG _GetRenderbufferParameterivEXT_OG;
#define glGetRenderbufferParameterivEXT _GetRenderbufferParameterivEXT_OG

//boolean IsFramebufferEXT(uint framebuffer);
typedef GLboolean( APIENTRY * IsFramebufferEXT_OG )( GLuint framebuffer );
extern IsFramebufferEXT_OG _IsFramebufferEXT_OG;
#define glIsFramebufferEXT _IsFramebufferEXT_OG

//void BindFramebufferEXT(enum target, uint framebuffer);
typedef void( APIENTRY * BindFramebufferEXT_OG )( GLenum target, GLuint framebuffer );
extern BindFramebufferEXT_OG _BindFramebufferEXT_OG;
#define glBindFramebufferEXT _BindFramebufferEXT_OG

//void DeleteFramebuffersEXT(sizei n, const uint *framebuffers);
typedef void( APIENTRY * DeleteFramebuffersEXT_OG )( GLsizei n, const GLuint *framebuffers );
extern DeleteFramebuffersEXT_OG _DeleteFramebuffersEXT_OG;
#define glDeleteFramebuffersEXT _DeleteFramebuffersEXT_OG

//void GenFramebuffersEXT(sizei n, uint *framebuffers);
typedef void( APIENTRY * GenFramebuffersEXT_OG )( GLsizei n, GLuint *framebuffers );
extern GenFramebuffersEXT_OG _GenFramebuffersEXT_OG;
#define glGenFramebuffersEXT _GenFramebuffersEXT_OG

//enum CheckFramebufferStatusEXT(enum target);
typedef void( APIENTRY * CheckFramebufferStatusEXT_OG )( GLenum target );
extern CheckFramebufferStatusEXT_OG _CheckFramebufferStatusEXT_OG;
#define glCheckFramebufferStatusEXT _CheckFramebufferStatusEXT_OG

//void FramebufferTexture1DEXT(enum target, enum attachment,enum textarget, uint texture,int level);
typedef void( APIENTRY * FramebufferTexture1DEXT_OG )( GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level );
extern FramebufferTexture1DEXT_OG _FramebufferTexture1DEXT_OG;
#define glFramebufferTexture1DEXT _FramebufferTexture1DEXT_OG

//void FramebufferTexture2DEXT(enum target, enum attachment,enum textarget, uint texture,int level);
typedef void( APIENTRY * FramebufferTexture2DEXT_OG )( GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level );
extern FramebufferTexture2DEXT_OG _FramebufferTexture2DEXT_OG;
#define glFramebufferTexture2DEXT _FramebufferTexture2DEXT_OG

//void FramebufferTexture3DEXT(enum target, enum attachment,enum textarget, uint texture,int level, int zoffset);
typedef void( APIENTRY * FramebufferTexture3DEXT_OG )( GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset );
extern FramebufferTexture3DEXT_OG _FramebufferTexture3DEXT_OG;
#define glFramebufferTexture3DEXT _FramebufferTexture3DEXT_OG

//void FramebufferRenderbufferEXT(enum target, enum attachment,enum renderbuffertarget, uint renderbuffer);
typedef void( APIENTRY * FramebufferRenderbufferEXT_OG )( GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer );
extern FramebufferRenderbufferEXT_OG _FramebufferRenderbufferEXT_OG;
#define glFramebufferRenderbufferEXT _FramebufferRenderbufferEXT_OG

//void GetFramebufferAttachmentParameterivEXT(enum target, enum attachment,enum pname, int *params);
typedef void( APIENTRY * GetFramebufferAttachmentParameterivEXT_OG )( GLenum target, GLenum attachment, GLenum pname, GLint *params );
extern GetFramebufferAttachmentParameterivEXT_OG _GetFramebufferAttachmentParameterivEXT_OG;
#define glGetFramebufferAttachmentParameterivEXT _GetFramebufferAttachmentParameterivEXT_OG

//void GenerateMipmapEXT(enum target);
typedef void( APIENTRY * GenerateMipmapEXT_OG )( GLenum target );
extern GenerateMipmapEXT_OG _GenerateMipmapEXT_OG;
#define glGenerateMipmapEXT _GenerateMipmapEXT_OG

// Prepares the FBO functions and returns true if the extension is fully supported, false otherwise
bool InitializeFBO();

#endif // OpenGUI_FBO_h__
