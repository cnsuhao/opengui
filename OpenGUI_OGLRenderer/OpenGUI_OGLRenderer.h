#ifndef D10A6A7B_DE80_49a2_A962_92696C85AFB8
#define D10A6A7B_DE80_49a2_A962_92696C85AFB8
#include <OpenGUI.h>
namespace OpenGUI{
	class OGLRenderer : public Renderer
	{
	public:
		OGLRenderer();
		~OGLRenderer();
		void getViewportDimensions(IVector2& dims);
		void doRenderOperation(Render::RenderOperation& renderOp);
		void preRenderSetup();
		void postRenderCleanup();


		Texture* createTextureFromFile(std::string filename);
		Texture* createTextureFromTextureData(TextureData *textureData);
		void updateTextureFromTextureData(Texture* texture, TextureData *textureData);
		void destroyTexture(Texture* texturePtr);
	};
};//namespace OpenGUI{
#endif