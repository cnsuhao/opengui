#include "OpenGUI_Texture.h"
#include "OpenGUI_Renderer.h"
#include "OpenGUI_TextureManager.h"

namespace OpenGUI {
	//############################################################################
	const std::string& Texture::getName() const {
		return mTextureName;
	}
	//############################################################################
	bool Texture::isRenderTexture(){
		return false;
	}
	//############################################################################
	void Texture::finalize(){
		TextureManager* tm = TextureManager::getSingletonPtr();
		tm->destroyTexture(this);
	}
	//############################################################################

}
;//namespace OpenGUI{

