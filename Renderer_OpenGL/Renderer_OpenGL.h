#ifndef D10A6A7B_DE80_49a2_A962_92696C85AFB8
#define D10A6A7B_DE80_49a2_A962_92696C85AFB8
#include <OpenGUI.h>

#include "OGL_Viewport.h"

/*
	This is a reference renderer used for OpenGUI development and demonstration purposes.
	It is not designed for production use in its current state. There are many
	additional optimization and feature paths available that were not taken,
	and it is highly recommended that you modify this renderer or create a new
	one if you plan on using OpenGUI for production use with native OpenGL.
*/

namespace OpenGUI {
	class Renderer_OpenGL : public Renderer {
	public:
		Renderer_OpenGL( int initial_width, int initial_height );
		virtual ~Renderer_OpenGL();
		// Application should call this whenever viewport resolution changes
		void setDim( int w, int h );

		//! returns a pointer to the default Viewport
		Viewport* getDefaultViewport();
		//! Creates a RTT Viewport of the given size (requires detected RTT support)
		OGL_RTT_Viewport* createRTTViewport(const IVector2& size);

		// Required implementations for OpenGUI Renderer
		virtual void selectViewport( Viewport* activeViewport );
		virtual void preRenderSetup();
		virtual void doRenderOperation( RenderOperation& renderOp );
		virtual void postRenderCleanup();
		virtual Texture* createTextureFromFile( const std::string& filename );
		virtual Texture* createTextureFromTextureData( const TextureData* textureData );
		virtual void updateTextureFromTextureData( Texture* texture, const TextureData* textureData );
		virtual void destroyTexture( Texture* texturePtr );

		// Optional Render-To-Texture support functions
		virtual bool supportsRenderToTexture();
		virtual void selectRenderContext( RenderTexture* context );
		virtual void clearContents();
		virtual RenderTexture* createRenderTexture( const IVector2& size );
		virtual void destroyRenderTexture( RenderTexture* texturePtr );
	private:
		void drawTriangles( const TriangleList& triangles, float xScaleUV, float yScaleUV );
		void drawTriangles( const TriangleList& triangles );
		void selectTextureState( Texture* texture );
		void safeBegin();
		void safeEnd();

		OGL_Default_Viewport mDefaultViewport;

		//! Loads the given \c filename into a TextureData object and returns the resulting object pointer, or 0 on fail.
		/*! \note This uses the Corona library to read the file format.	*/
		static TextureData* LoadTextureData( std::string filename );		
		bool mSupportRTT;

		OGL_Viewport* mCurrentViewport;
		RenderTexture* mCurrentContext;
		Texture* mCurrentTextureState;
		bool mSupportRectTex;
		bool mInGLBegin;
		bool mInRender;
	};
} //namespace OpenGUI{

// Rectangle Texture Tokens
#define GL_TEXTURE_RECTANGLE_ARB            0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE_ARB    0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE_ARB      0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_ARB   0x84F8
#define GL_SAMPLER_2D_RECT_ARB              0x8B63
#define GL_SAMPLER_2D_RECT_SHADOW_ARB       0x8B64

#endif
