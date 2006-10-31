
#include "OpenGUI_Imagery.h"
#include "OpenGUI_LogSystem.h"
//#include "OpenGUI_Imageset.h"

namespace OpenGUI {
	//############################################################################
	Imagery::Imagery( const std::string Name, FRect areaRect, IRect nativeRect, TexturePtr texture )
			: mName( Name ), mAreaRect( areaRect ), mNativeRect( nativeRect ), mTexture( texture ) {
		LogManager::SlogMsg( "Imagery", OGLL_INFO2 ) << "(" << mName << ") "
		<< "Creation" << Log::endlog;
	}
	//############################################################################
	Imagery::~Imagery() {
		LogManager::SlogMsg( "Imagery", OGLL_INFO2 ) << "(" << mName << ") "
		<< "Destruction" << Log::endlog;
	}
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
		return mTexture;
	}
	//############################################################################
	std::string Imagery::getName() {
		return mName;
	}
	//############################################################################

}
;//namespace OpenGUI{


