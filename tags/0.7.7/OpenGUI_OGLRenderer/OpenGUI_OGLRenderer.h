#ifndef D10A6A7B_DE80_49a2_A962_92696C85AFB8
#define D10A6A7B_DE80_49a2_A962_92696C85AFB8
#include <OpenGUI.h>
namespace OpenGUI{
	class OGLRenderer : public Renderer
	{
	public:
		OGLRenderer();
		~OGLRenderer();
		virtual void getViewportDimensions(IVector2& dims);
		virtual void getScreenDimensions(IVector2& dims);
		virtual void doRenderOperation(Render::RenderOperation& renderOp);
		virtual void preRenderSetup();
		virtual void postRenderCleanup();

		void setDim(int w, int h) {mHeight = h; mWidth=w; alertViewportDimensionsChanged();}
		void setScreenDim(int w, int h) {mSHeight = h; mSWidth=w; alertScreenDimensionsChanged(); }


		Texture* createTextureFromFile(std::string filename);
		Texture* createTextureFromTextureData(TextureData *textureData);
		void updateTextureFromTextureData(Texture* texture, TextureData *textureData);
		void destroyTexture(Texture* texturePtr);
	private:
		int mHeight;
		int mWidth;
		int mSHeight;
		int mSWidth;
	};
};//namespace OpenGUI{
#endif