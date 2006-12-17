// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Renderer_h__
#define Renderer_h__

using namespace System;

namespace OpenGUI_Net {
	ref class Texture;
	ref class Viewport;
	ref class RenderOperation;
	ref class TextureData;

	ref class Renderer; // forward declaration

	class RendererExchange: public OpenGUI::Renderer{
	public:
		RendererExchange(OpenGUI_Net::Renderer^ managedRenderer){
			m_Renderer = managedRenderer;
		}
		// standard required functions
		virtual void selectViewport( OpenGUI::Viewport* activeViewport );
		virtual void preRenderSetup();
		virtual void doRenderOperation( OpenGUI::RenderOperation& renderOp );
		virtual void postRenderCleanup();
		virtual OpenGUI::Texture* createTextureFromFile( const std::string& filename );
		virtual OpenGUI::Texture* createTextureFromTextureData( const OpenGUI::TextureData* textureData );
		virtual void updateTextureFromTextureData( OpenGUI::Texture* texture, const OpenGUI::TextureData* textureData );
		virtual void destroyTexture( OpenGUI::Texture* texturePtr );
		// render to texture functions
		virtual bool supportsRenderToTexture();
		virtual void selectRenderContext( OpenGUI::RenderTexture* context );
		virtual void clearContents();
		virtual OpenGUI::RenderTexture* createRenderTexture( const OpenGUI::IVector2& size );
		virtual void destroyRenderTexture( OpenGUI::RenderTexture* texturePtr );
	private:
		// theoretically, the garbage collector is smart enough to notice self maintaining leaks like this
		gcroot < OpenGUI_Net::Renderer ^ > m_Renderer;
	};

	public ref class Renderer abstract {
	public:
		Renderer(){
			m_RendererExchange = new RendererExchange(this);
		}
		~Renderer(){
			delete m_RendererExchange;
		}
		virtual void selectViewport( Viewport ^ activeViewport ) = 0;
		virtual void preRenderSetup() = 0;
		virtual void doRenderOperation( RenderOperation ^ renderOp ) = 0;
		virtual void postRenderCleanup() = 0;
		virtual Texture ^ createTextureFromFile( String ^ fileName ) = 0;
		virtual Texture ^ createTextureFromTextureData( const TextureData ^ textureData ) = 0;
		virtual void updateTextureFromTextureData( Texture ^ texture, const TextureData ^ textureData ) = 0;
		virtual void destroyTexture( Texture ^ texturePtr ) = 0;
	private:
		RendererExchange* m_RendererExchange;
	};
} // namespace OpenGUI_Net {

#endif // Renderer_h__