#include "OpenGUI_Texture.h"
#include "OpenGUI_TextureManager.h"

namespace OpenGUI {
	//############################################################################
	const std::string& Texture::getName() const {
		return mTextureName;
	}
	//############################################################################
	bool Texture::isRenderTexture() {
		return false;
	}
	//############################################################################
	void Texture::finalize() {
		TextureManager* tm = TextureManager::getSingletonPtr();
		if ( tm ) // only do this if we have something to call
			tm->destroyTexture( this );
	}
	//############################################################################
	void Texture::getUVs( float& max_u, float& max_v ) {
		max_u = 1.0f;
		max_v = 1.0f;
	}
	//############################################################################
}
;//namespace OpenGUI{

