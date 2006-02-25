
#include <string>
#include "OpenGUI.h"

namespace OpenGUI{

	//############################################################################
	FRect Imagery::getTextureUVRect()
	{
		return mAreaRect;
	}
	//############################################################################
	Texture* Imagery::getTexture()
	{
		if(!mParentImageset) return 0;
		return mParentImageset->mpTexture;
	}
	//############################################################################
	std::string Imagery::getName()
	{
		return mName;
	}
	//############################################################################

};//namespace OpenGUI{


