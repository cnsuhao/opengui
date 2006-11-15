#include "OpenGUI_RenderTexture.h"
#include "OpenGUI_TextureManager.h"

namespace OpenGUI {

	//############################################################################
	bool RenderTexture::isRenderTexture() {
		return true;
	}
	//############################################################################
	void RenderTexture::finalize() {
		TextureManager* tm = TextureManager::getSingletonPtr();
		if ( tm ) // only do this if we have something to call
			tm->destroyRenderTexture( this );
	}
	//############################################################################
} //namespace OpenGUI {
