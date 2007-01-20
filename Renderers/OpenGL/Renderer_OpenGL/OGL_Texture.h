// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef CE76573F_9B5B_4ca7_9BCE_B8173655EBAA
#define CE76573F_9B5B_4ca7_9BCE_B8173655EBAA

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library

#include <OpenGUI.h>

namespace OpenGUI {
	class OGLTexture : public Texture {
	public:
		OGLTexture();
		virtual ~OGLTexture();

		GLuint textureId;

		void setName( const String& name ) {
			_setName( name );
		}
		void setSize( const IVector2& size ) {
			_setSize( size );
		}
	};

	class OGLRTexture : public RenderTexture {
	public:
		OGLRTexture();
		virtual ~OGLRTexture();

		GLuint textureId;
		GLuint fboId;
		FVector2 maxUVs;

		void setName( const String& name ) {
			_setName( name );
		}
		void setSize( const IVector2& size ) {
			_setSize( size );
		}
		virtual void getUVs( float& max_u, float& max_v ) {
			max_u = maxUVs.x;
			max_v = maxUVs.y;
		}
	};
}
;//namespace OpenGUI{
#endif