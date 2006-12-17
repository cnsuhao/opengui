// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Renderer_h__
#define Renderer_h__

using namespace System;

namespace OpenGUI_Net {

	public ref class Renderer abstract {
	public:
		virtual OpenGUI::Renderer* getNativeRenderer() = 0;
	};

	class TestRenderer_Native: public OpenGUI::Renderer {
	public:
		virtual void selectViewport( OpenGUI::Viewport* activeViewport ) {}
		virtual void preRenderSetup() {}
		virtual void doRenderOperation( OpenGUI::RenderOperation& renderOp ) {}
		virtual void postRenderCleanup() {}
		virtual OpenGUI::Texture* createTextureFromFile( const std::string& filename ) {
			return 0;
		}
		virtual OpenGUI::Texture* createTextureFromTextureData( const OpenGUI::TextureData* textureData ) {
			return 0;
		}
		virtual void updateTextureFromTextureData( OpenGUI::Texture* texture, const OpenGUI::TextureData* textureData ) {}
		virtual void destroyTexture( OpenGUI::Texture* texturePtr ) {}
	};
	public ref class TestRenderer: Renderer {
	public:
		TestRenderer() {
			mRenderer = new TestRenderer_Native();
		}
		~TestRenderer() {
			delete mRenderer;
		}
		virtual OpenGUI::Renderer* getNativeRenderer() override {
			return mRenderer;
		}
	private:
		TestRenderer_Native* mRenderer;
	};
} // namespace OpenGUI_Net {

#endif // Renderer_h__