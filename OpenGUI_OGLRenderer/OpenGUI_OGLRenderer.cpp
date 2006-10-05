
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library


#include "OpenGUI_OGLRenderer.h"
#include "OpenGUI_OGLTexture.h"

namespace OpenGUI {
	//###########################################################
	OGLRenderer::OGLRenderer( int initial_width, int initial_height ) {
		mWidth = initial_width;
		mHeight = initial_height;
	}
	//###########################################################
	OGLRenderer::~OGLRenderer() {}
	//###########################################################
	void OGLRenderer::getViewportDimensions( IVector2& dims ) {
		dims.x = mWidth;
		dims.y = mHeight;
		
		/* - We'll just do this in the application
		GLint viewportDims[4];
		glGetIntegerv( GL_VIEWPORT, viewportDims );
		dims.x = viewportDims[2];
		dims.y = viewportDims[3];
		*/
	}
	//###########################################################
	void OGLRenderer::doRenderOperation( Render::RenderOperation& renderOp ) {
		if ( renderOp.texture ) {
			glBindTexture( GL_TEXTURE_2D, static_cast<OGLTexture*>( renderOp.texture )->textureId );
		} else {
			glBindTexture( GL_TEXTURE_2D, 0 );
		}

		glBegin( GL_TRIANGLES );
		//point 1
		glColor4f(	renderOp.vertices[0].color.Red,
				   renderOp.vertices[0].color.Green,
				   renderOp.vertices[0].color.Blue,
				   renderOp.vertices[0].color.Alpha );
		glTexCoord2f( renderOp.vertices[0].textureUV.x, renderOp.vertices[0].textureUV.y );
		glVertex3f( renderOp.vertices[0].position.x, renderOp.vertices[0].position.y, 0.0f );
		//point 2
		glColor4f(	renderOp.vertices[1].color.Red,
				   renderOp.vertices[1].color.Green,
				   renderOp.vertices[1].color.Blue,
				   renderOp.vertices[1].color.Alpha );
		glTexCoord2f( renderOp.vertices[1].textureUV.x, renderOp.vertices[1].textureUV.y );
		glVertex3f( renderOp.vertices[1].position.x, renderOp.vertices[1].position.y, 0.0f );
		//point 3
		glColor4f(	renderOp.vertices[2].color.Red,
				   renderOp.vertices[2].color.Green,
				   renderOp.vertices[2].color.Blue,
				   renderOp.vertices[2].color.Alpha );
		glTexCoord2f( renderOp.vertices[2].textureUV.x, renderOp.vertices[2].textureUV.y );
		glVertex3f( renderOp.vertices[2].position.x, renderOp.vertices[2].position.y, 0.0f );
		glEnd();
	}
	//###########################################################
	void OGLRenderer::preRenderSetup() {
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		glOrtho( 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 2.0f );


		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

		glEnable( GL_BLEND );
		glDisable( GL_DEPTH_TEST );
		glEnable( GL_TEXTURE_2D );
		glShadeModel( GL_SMOOTH );

		//glDisable(GL_CULL_FACE);
		glFrontFace( GL_CCW );
		glCullFace( GL_BACK );
		glEnable( GL_CULL_FACE ); //test

		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	}
	//###########################################################
	void OGLRenderer::postRenderCleanup() {}
	//###########################################################
	Texture* OGLRenderer::createTextureFromFile( std::string filename ) {
		OGLTexture* retval = 0;

		//Load the image from the disk
		TextureData* td = TextureData::LoadTextureData( filename );
		if ( !td ) return 0;

		retval = new OGLTexture();
		if ( !retval ) return 0;

		retval->setName( filename );

		retval->setSize( IVector2( td->getWidth(), td->getHeight() ) );

		GLint internalFormat;
		GLenum dataFormat;
		switch ( td->getBPP() ) {
		case 1:
			internalFormat = GL_ALPHA;
			dataFormat = GL_ALPHA;
			break;
		case 3:
			internalFormat = GL_RGB;
			dataFormat = GL_RGB;
			break;
		case 4:
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
			break;
		}


		glGenTextures( 1, &( retval->textureId ) );
		glBindTexture( GL_TEXTURE_2D, retval->textureId );
		glTexImage2D( GL_TEXTURE_2D, //2D texture
					  0, //mipmap level 0
					  internalFormat, // the texture format
					  td->getWidth(), //image width
					  td->getHeight(), //image height
					  0, //no border (does anyone ever use this?)
					  dataFormat, //the format of the pixel data
					  GL_UNSIGNED_BYTE, //each channel consists of 1 unsigned byte
					  td->getPixelData() //pointer to the image data
					);

		//set up texture filtering
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

		delete td;

		return retval;
	}
	//###########################################################
	Texture* OGLRenderer::createTextureFromTextureData( TextureData *textureData ) {
		TextureData* td = textureData; // copy/paste quick fix
		OGLTexture* retval = 0;
		retval = new OGLTexture( );
		if ( !retval ) return 0;

		retval->setName( "__## TextureFromMemory ##__" );

		retval->setSize( IVector2( td->getWidth(), td->getHeight() ) );

		GLint internalFormat;
		GLenum dataFormat;
		switch ( td->getBPP() ) {
		case 1:
			internalFormat = GL_ALPHA;
			dataFormat = GL_ALPHA;
			break;
		case 3:
			internalFormat = GL_RGB;
			dataFormat = GL_RGB;
			break;
		case 4:
			internalFormat = GL_RGBA;
			dataFormat = GL_RGBA;
			break;
		}


		glGenTextures( 1, &( retval->textureId ) );
		glBindTexture( GL_TEXTURE_2D, retval->textureId );
		glTexImage2D(	GL_TEXTURE_2D, //2D texture
					  0, //mipmap level 0
					  internalFormat, // the texture format
					  td->getWidth(), //image width
					  td->getHeight(), //image height
					  0, //no border (does anyone ever use this?)
					  dataFormat, //the format of the pixel data
					  GL_UNSIGNED_BYTE, //each channel consists of 1 unsigned byte
					  td->getPixelData() //pointer to the image data
					);

		//set up texture filtering
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

		return retval;
	}
	//###########################################################
	void OGLRenderer::updateTextureFromTextureData( Texture* texture, TextureData *textureData ) {
		TextureData* td = textureData; // copy/paste quick fix
		OGLTexture* retval = 0;
		retval = ( OGLTexture* ) texture;
		if ( !retval ) return;

		//throw away old data
		glDeleteTextures( 1, &( retval->textureId ) );

		retval->setName( "__## TextureFromMemory ##__" );

		retval->setSize( IVector2( td->getWidth(), td->getHeight() ) );

		GLint internalFormat;
		GLenum dataFormat;
		switch ( td->getBPP() ) {
		case 1:
			internalFormat = GL_ALPHA;
			dataFormat = GL_ALPHA;
			break;
		case 3:
			internalFormat = GL_RGB;
			dataFormat = GL_RGB;
			break;
		case 4:
			internalFormat = GL_RGBA;
			dataFormat = GL_RGBA;
			break;
		}


		glGenTextures( 1, &( retval->textureId ) );
		glBindTexture( GL_TEXTURE_2D, retval->textureId );
		glTexImage2D(	GL_TEXTURE_2D, //2D texture
					  0, //mipmap level 0
					  internalFormat, // the texture format
					  td->getWidth(), //image width
					  td->getHeight(), //image height
					  0, //no border (does anyone ever use this?)
					  dataFormat, //the format of the pixel data
					  GL_UNSIGNED_BYTE, //each channel consists of 1 unsigned byte
					  td->getPixelData() //pointer to the image data
					);

		//set up texture filtering
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	}
	//###########################################################
	void OGLRenderer::destroyTexture( Texture* texturePtr ) {
		if ( !texturePtr ) return;
		OGLTexture* texptr = dynamic_cast<OGLTexture*>( texturePtr );
		if ( texptr ) {
			if ( texptr->textureId ) {
				glDeleteTextures( 1, &( texptr->textureId ) );
			}
			delete texptr;
		}
	}
	//###########################################################
}
;//namespace OpenGUI{





