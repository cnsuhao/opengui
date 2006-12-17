// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "Stdafx.h"

#include "Renderer.h"
#include "Viewport.h"

namespace OpenGUI_Net {
	//############################################################################
	// standard required functions
	//############################################################################
	void RendererExchange::selectViewport( OpenGUI::Viewport* activeViewport ){
		if(activeViewport == 0){
			m_Renderer->selectViewport(nullptr);
		}else{
			ViewportExchange* vp = static_cast<ViewportExchange*>(activeViewport);
			m_Renderer->selectViewport(vp->getManagedViewport());
		}
	}
	//############################################################################
	void RendererExchange::preRenderSetup(){
		m_Renderer->preRenderSetup();
	}
	//############################################################################
	void RendererExchange::doRenderOperation( OpenGUI::RenderOperation& renderOp ){
		throw 0;
	}
	//############################################################################
	void RendererExchange::postRenderCleanup(){
		m_Renderer->postRenderCleanup();
	}
	//############################################################################
	OpenGUI::Texture* RendererExchange::createTextureFromFile( const std::string& filename ){
		throw 0;
	}
	//############################################################################
	OpenGUI::Texture* RendererExchange::createTextureFromTextureData( const OpenGUI::TextureData* textureData ){
		throw 0;
	}
	//############################################################################
	void RendererExchange::updateTextureFromTextureData( OpenGUI::Texture* texture, const OpenGUI::TextureData* textureData ){
		throw 0;
	}
	//############################################################################
	void RendererExchange::destroyTexture( OpenGUI::Texture* texturePtr ){
		throw 0;
	}
	//############################################################################
	// render to texture functions
	//############################################################################
	bool RendererExchange::supportsRenderToTexture(){
		return m_Renderer->supportsRenderToTexture();
	}
	//############################################################################
	void RendererExchange::selectRenderContext( OpenGUI::RenderTexture* context ){
		throw 0;
	}
	//############################################################################
	void RendererExchange::clearContents(){
		m_Renderer->clearContents();
	}
	//############################################################################
	OpenGUI::RenderTexture* RendererExchange::createRenderTexture( const OpenGUI::IVector2& size ){
		throw 0;
	}
	//############################################################################
	void RendererExchange::destroyRenderTexture( OpenGUI::RenderTexture* texturePtr ){
		throw 0;
	}
	//############################################################################
} // namespace OpenGUI_Net {
