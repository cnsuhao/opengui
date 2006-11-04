
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library

#include "GL/glfw.h"
#include "OpenGUI_FBO.h"

#include "corona.h"

#include "OpenGUI_OGLRenderer.h"
#include "OpenGUI_OGLTexture.h"

// Rectangle Texture Tokens
#define GL_TEXTURE_RECTANGLE_ARB            0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE_ARB    0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE_ARB      0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_ARB   0x84F8
#define GL_SAMPLER_2D_RECT_ARB              0x8B63
#define GL_SAMPLER_2D_RECT_SHADOW_ARB       0x8B64

namespace OpenGUI {
	//###########################################################
	OGLRenderer::OGLRenderer( int initial_width, int initial_height ) {
		mDimensions.x = initial_width;
		mDimensions.y = initial_height;
		mCurrentContext = 0;
		mSupportRTT = InitializeFBO();
		if ( glfwExtensionSupported( "GL_EXT_texture_rectangle" ) || glfwExtensionSupported( "GL_ARB_texture_rectangle" ) )
			mSupportRectTex = true;
		else
			mSupportRectTex = false;
	}
	//###########################################################
OGLRenderer::~OGLRenderer() {}
	//###########################################################
	const IVector2& OGLRenderer::getViewportDimensions() {
		return mDimensions;
	}
	//###########################################################
	void OGLRenderer::doRenderOperation( RenderOperation& renderOp ) {
		bool isRectTex = false;
		float xUVScale = 1.0f;
		float yUVScale = 1.0f;
		if ( renderOp.texture ) {
			GLuint texid;
			if ( renderOp.texture->isRenderTexture() ) {
				texid = static_cast<OGLRTexture*>( renderOp.texture.get() )->textureId;
				if(mSupportRectTex){
					isRectTex = true;
					glEnable(GL_TEXTURE_RECTANGLE_ARB);
					const IVector2& t = static_cast<OGLRTexture*>( renderOp.texture.get() )->getSize();
					xUVScale = (float)t.x;
					yUVScale = (float)t.y;
					glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );
					glBindTexture( GL_TEXTURE_RECTANGLE_ARB, texid );
				}else
					glBindTexture( GL_TEXTURE_2D, texid );
			} else {
				texid = static_cast<OGLTexture*>( renderOp.texture.get() )->textureId;
				glBindTexture( GL_TEXTURE_2D, texid );
			}
		} else {
			glBindTexture( GL_TEXTURE_2D, 0 );
		}

		

		if ( renderOp.triangleList ) {

			glBegin( GL_TRIANGLES );

			TriangleList& tl = *( renderOp.triangleList );
			for ( TriangleList::iterator iter = tl.begin();
					iter != tl.end(); iter++ ) {
				Triangle& t = ( *iter );
				for ( int i = 0; i < 3; i++ ) {
					glColor4f(	t.vertex[i].color.Red,
							   t.vertex[i].color.Green,
							   t.vertex[i].color.Blue,
							   t.vertex[i].color.Alpha );

					glTexCoord2f( t.vertex[i].textureUV.x * xUVScale, t.vertex[i].textureUV.y * yUVScale );

					glVertex3f( t.vertex[i].position.x, t.vertex[i].position.y, 0.0f );
				}
			}

			glEnd();

			if(isRectTex){
				glDisable(GL_TEXTURE_RECTANGLE_ARB);
				glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			}

		}
		/*
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
				glEnd();*/
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
	void OGLRenderer::postRenderCleanup() {
		selectRenderContext( 0 ); // be kind, rewind
	}
	//###########################################################
	Texture* OGLRenderer::createTextureFromFile( const std::string& filename ) {
		OGLTexture* retval = 0;

		//Load the image from the disk
		TextureData* td = LoadTextureData( filename );
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

		glBindTexture( GL_TEXTURE_2D, 0 );

		return retval;
	}
	//###########################################################
	Texture* OGLRenderer::createTextureFromTextureData( const TextureData *textureData ) {
		const TextureData* td = textureData; // copy/paste quick fix
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
	void OGLRenderer::updateTextureFromTextureData( Texture* texture, const TextureData *textureData ) {
		const TextureData* td = textureData; // copy/paste quick fix
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
		
		if (( void* )mCurrentContext == ( void* )texturePtr ) // never delete the current context
			selectRenderContext( 0 ); // so we switch back to the default context if needed

		OGLRTexture* rtexptr = dynamic_cast<OGLRTexture*>( texturePtr );
		if ( rtexptr ) {
			if ( rtexptr->textureId ) {
				glDeleteTextures( 1, &( rtexptr->textureId ) );
			}
			delete rtexptr;
			return;
		}

		OGLTexture* texptr = dynamic_cast<OGLTexture*>( texturePtr );
		if ( texptr ) {
			if ( texptr->textureId ) {
				glDeleteTextures( 1, &( texptr->textureId ) );
			}
			delete texptr;
			return;
		}
	}
	//###########################################################
	TextureData* OGLRenderer::LoadTextureData( std::string filename ) {
		//we can't load anything until the system is up
		//but we should try to play nice
		if ( !System::getSingletonPtr() )
			return 0;
		ResourceProvider* rp = System::getSingletonPtr()->_getResourceProvider();
		if ( rp == 0 ) return 0;

		//load the resource into memory via the registered resource provider
		Resource resource;
		try {
			rp->loadResource( filename, resource );
		} catch ( Exception e ) {
			return 0;
		};

		//pass the data to corona
		corona::File* cf = corona::CreateMemoryFile( resource.getData(), ( int )resource.getSize() );
		resource.release(); //at this point, we don't need the resource loaded any longer
		if ( !cf ) {
			return 0;
		}
		corona::Image* img = corona::OpenImage( cf, corona::PF_DONTCARE );
		delete cf;
		cf = 0; //at this point, we don't need the memory file any longer

		TextureData* retval = new TextureData();
		int imgHeight, imgWidth, imgBPP;
		imgHeight = img->getHeight();
		imgWidth = img->getWidth();

		//perform data format enumeration and
		switch ( img->getFormat() ) {
		case corona::PF_I8:
			imgBPP = 1;
			break;

		case corona::PF_B8G8R8A8:
			img = corona::ConvertImage( img, corona::PF_R8G8B8A8 );
			if ( img == 0 ) {//we failed to convert, bail out
				delete retval;
				return 0;
			}
		case corona::PF_R8G8B8A8:
			imgBPP = 4;
			break;

		case corona::PF_B8G8R8:
			img = corona::ConvertImage( img, corona::PF_R8G8B8 );
			if ( img == 0 ) {//we failed to convert, bail out
				delete retval;
				return 0;
			}
		case corona::PF_R8G8B8:
			imgBPP = 3;
			break;

		default:
			delete retval;
			delete img;
			return 0;
			break;//<- habit
		}

		/*	At this point, the data should now be completely loaded into a known format.
		All we need to do is copy the img buffer contents and we're done
		*/
		retval->setData( imgWidth, imgHeight, imgBPP, img->getPixels() );

		delete img; //and delete this or we leak
		return retval;
	}
	//#####################################################

	//#####################################################
	//#####################################################
	// RENDER TO TEXTURE SUPPORT FUNCTIONS
	//#####################################################
	//#####################################################
	bool OGLRenderer::supportsRenderToTexture() {
		return mSupportRTT;
	}
	//#####################################################
	void OGLRenderer::selectRenderContext( RenderTexture* context ) {
		if ( mCurrentContext != context ) {
			OGLRTexture* rtex;
			if ( mCurrentContext ) {
				rtex = static_cast<OGLRTexture*>( mCurrentContext );
				rtex->unbind();
			}
			mCurrentContext = context;
			if ( mCurrentContext ) {
				rtex = static_cast<OGLRTexture*>( mCurrentContext );
				rtex->bind();
				glViewport( 0, 0, rtex->getSize().x, rtex->getSize().y );
				//glViewport( 0, 0, 512, 512 );
			} else {
				glViewport( 0, 0, mDimensions.x, mDimensions.y );
			}
		}
	}
	//#####################################################
	void OGLRenderer::clearContents() {
		if ( 0 == mCurrentContext ) return; // don't clear the main viewport
		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
		glClear( GL_COLOR_BUFFER_BIT );
	}
	//#####################################################
	RenderTexture* OGLRenderer::createRenderTexture( const IVector2& size ) {
		OGLRTexture* ret = new OGLRTexture();
		ret->setSize( size );
		ret->setName( "__RenderTexture__" );
		GLuint textid;

		glGenTextures( 1, &textid );
		ret->textureId = textid;

		// switch rendering context so we can set things up
		RenderTexture* prevContext = mCurrentContext;
		selectRenderContext( ret );

		if ( mSupportRectTex ) {
			glBindTexture( GL_TEXTURE_RECTANGLE_ARB, textid );
			glTexParameteri( GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexImage2D( GL_TEXTURE_RECTANGLE_ARB, //2D rectangle texture
						  0, //mipmap level 0
						  GL_RGBA, // texture format
						  ret->getSize().x, // texture width
						  ret->getSize().y, // texture height
						  0, // no border
						  GL_RGBA, // input data format
						  GL_UNSIGNED_INT, // input data channel size
						  NULL ); // this is a blank texture, no input data

			if ( glGetError() == GL_INVALID_VALUE )
				OG_THROW( Exception::ERR_INTERNAL_ERROR, "Something broke with rectangle textures", __FUNCTION__ );

			// attach the texture to the frame buffer as the color destination
			glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, //target
									   GL_COLOR_ATTACHMENT0_EXT, // attachment destination
									   GL_TEXTURE_RECTANGLE_ARB, // destination attachment object type
									   textid, // destination attachment object ID
									   0 ); // level within attaching object
		}
		if ( !mSupportRectTex ) {
			glBindTexture( GL_TEXTURE_2D, textid );

			// set up texture filtering
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

			// create the blank texture
			glTexImage2D( GL_TEXTURE_2D, //2D texture
						  0, //mipmap level 0
						  GL_RGBA8, // texture format
						  ret->getSize().x, // texture width
						  ret->getSize().y, // texture height
						  0, // no border
						  GL_RGBA, // input data format
						  GL_UNSIGNED_BYTE, // input data channel size
						  NULL ); // this is a blank texture, no input data

			//!\todo Add proper handling when non power of 2 textures are not supported
			if ( glGetError() == GL_INVALID_VALUE )
				OG_THROW( Exception::ERR_INTERNAL_ERROR, "I don't support non power of 2 textures", __FUNCTION__ );

			// attach the texture to the frame buffer as the color destination
			glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, //target
									   GL_COLOR_ATTACHMENT0_EXT, // attachment destination
									   GL_TEXTURE_2D, // destination attachment object type
									   textid, // destination attachment object ID
									   0 ); // level within attaching object
		}


		//restore the previous render context
		selectRenderContext( prevContext );

		return ret;
	}
	//#####################################################
}
;//namespace OpenGUI{





