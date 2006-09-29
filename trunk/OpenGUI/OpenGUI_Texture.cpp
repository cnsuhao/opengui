#include "OpenGUI_Texture.h"
#include "OpenGUI_Renderer.h"

namespace OpenGUI {
	//#############################################
	std::string Texture::getName() {
		return mTextureName;
	}
	//#############################################
	Texture::Texture( Renderer* renderer ) : mRenderer( renderer ) {
		// always start out as a valid texture that requires deletion
		mValid = true;
	}
	//#############################################
	Texture::~Texture() {
		if ( mValid && mRenderer ) {
			mRenderer->destroyTexture( this );
			mValid = false;
		}
	}
}
;//namespace OpenGUI{

