// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_Renderer.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	//############################################################################
	template<> Renderer* Singleton<Renderer>::mptr_Singleton = 0;
	//############################################################################
	Renderer& Renderer::getSingleton( void ) {
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	Renderer* Renderer::getSingletonPtr( void ) {
		return mptr_Singleton;
	}
	//############################################################################
	bool Renderer::supportsRenderToTexture() {
		return false;
	}
	//############################################################################
	RenderTexture* Renderer::createRenderTexture( const IVector2& size ) {
		OG_THROW( Exception::ERR_NOT_IMPLEMENTED, "Render Textures not supported", __FUNCTION__ );
	}
	//############################################################################
	void Renderer::destroyRenderTexture( RenderTexture* texturePtr ) {
		OG_THROW( Exception::ERR_NOT_IMPLEMENTED, "Render Textures not supported", __FUNCTION__ );
	}
	//############################################################################
};

