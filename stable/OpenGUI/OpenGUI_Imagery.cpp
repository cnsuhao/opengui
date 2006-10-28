
#include "OpenGUI_Imagery.h"
#include "OpenGUI_Imageset.h"

namespace OpenGUI {

	//############################################################################
	FRect Imagery::getTextureUVRect() {
		return mAreaRect;
	}
	//############################################################################
	IRect Imagery::getImagesetRect() {
		return mNativeRect;
	}
	//############################################################################
	TexturePtr Imagery::getTexture() {
		if ( !mParentImageset ) return 0;
		return mParentImageset->mpTexture;
	}
	//############################################################################
	std::string Imagery::getName() {
		return mName;
	}
	//############################################################################

}
;//namespace OpenGUI{


