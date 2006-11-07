#ifndef D10A6A7B_DE80_49a2_A962_92696C85AFB8
#define D10A6A7B_DE80_49a2_A962_92696C85AFB8
#include <OpenGUI.h>
namespace OpenGUI {
	class OGLRenderer : public Renderer {
	public:
		OGLRenderer( int initial_width, int initial_height );
		virtual ~OGLRenderer();
		// Application should call this whenever viewport resolution changes
		void setDim( int w, int h ) {
			mDimensions.y = h;
			mDimensions.x = w;
			if ( System::getSingletonPtr() )
				System::getSingleton().notifyViewportDimensionsChanged();
		}

		// Required implementations for OpenGUI Renderer
		virtual const IVector2& getViewportDimensions();
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

		IVector2 mDimensions;
		//! Loads the given \c filename into a TextureData object and returns the resulting object pointer, or 0 on fail.
		/*! \note This uses the Corona library to read the file format.	*/
		static TextureData* LoadTextureData( std::string filename );
		bool mSupportRTT;
		RenderTexture* mCurrentContext;
		Texture* mCurrentTextureState;
		bool mSupportRectTex;
		bool mInGLBegin;
	};
}
;//namespace OpenGUI{
#endif