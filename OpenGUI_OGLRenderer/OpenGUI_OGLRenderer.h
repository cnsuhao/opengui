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
			mHeight = h;
			mWidth = w;
			if ( System::getSingletonPtr() )
				System::getSingleton().notifyViewportDimensionsChanged();
		}

		// Required implementations for OpenGUI Renderer
		virtual void getViewportDimensions( IVector2& dims );
		virtual void doRenderOperation( Render::RenderOperation& renderOp );
		virtual void preRenderSetup();
		virtual void postRenderCleanup();
		Texture* createTextureFromFile( std::string filename );
		Texture* createTextureFromTextureData( TextureData *textureData );
		void updateTextureFromTextureData( Texture* texture, TextureData *textureData );
		void destroyTexture( Texture* texturePtr );
	private:
		int mHeight;
		int mWidth;
	};
}
;//namespace OpenGUI{
#endif