// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Renderer_h__
#define Renderer_h__

#include "Viewport.h"

using namespace System;

namespace OpenGUI_Net {

	public ref class Renderer abstract {
	public:
		virtual OpenGUI::Renderer* getNativeRenderer() = 0;
	};

	//############################################################################
	//############################################################################
	//############################################################################
	// These are dummy classes that don't really work, but we need them to pretend we're working
	class TestViewport_Native: public OpenGUI::Viewport {
	public:
		TestViewport_Native() {
			mSize.x = 800;
			mSize.y = 600;
		}
		virtual const OpenGUI::IVector2& getSize() {
			return mSize;
		}
	protected:
		virtual void preUpdate( OpenGUI::Screen *updatingScreen ) {}
		virtual void postUpdate( OpenGUI::Screen *updatingScreen ) {}
	private:
		OpenGUI::IVector2 mSize;
	};
	//############################################################################
	public ref class TestViewport: Viewport {
	public:
		TestViewport() {
			mViewport = new TestViewport_Native();
		}
		~TestViewport() {
			delete mViewport;
		}
		virtual OpenGUI::Viewport* getNativeViewport() override {
			return mViewport;
		}
	private:
		TestViewport_Native* mViewport;
	};
	//############################################################################
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
	//############################################################################
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
		Viewport ^ getViewport() {
			return gcnew TestViewport();
		}
	private:
		TestRenderer_Native* mRenderer;
	};
	//############################################################################

} // namespace OpenGUI_Net {

#endif // Renderer_h__