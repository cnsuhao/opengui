#include "OpenGUI_Texture.h"
#include "OpenGUI_Renderer.h"
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
		if(tm) // only do this if we have something to call
			tm->destroyTexture( this );
	}
	//############################################################################

}
;//namespace OpenGUI{

