
#include "OpenGUI_Imagery.h"
#include "OpenGUI_LogSystem.h"
//#include "OpenGUI_Imageset.h"

namespace OpenGUI {
	//############################################################################
	Imagery::Imagery( const std::string ImagesetName, const std::string Name, FRect areaRect, IRect nativeRect, TexturePtr texture )
			: mName( Name ), mAreaRect( areaRect ), mNativeRect( nativeRect ), mTexture( texture ) {
		std::stringstream ss;
		ss << ImagesetName << ":" << Name;
		mFQN = ss.str();
		LogManager::SlogMsg( "Imagery", OGLL_INFO2 ) << "(" << mFQN << ") "
		<< "Creation" << Log::endlog;
	}
	//############################################################################
	Imagery::~Imagery() {
		LogManager::SlogMsg( "Imagery", OGLL_INFO2 ) << "(" << mFQN << ") "
		<< "Destruction" << Log::endlog;
	}
	//############################################################################
	const FRect& Imagery::getTextureUVRect() const {
		return mAreaRect;
	}
	//############################################################################
	const IRect& Imagery::getImagesetRect() const {
		return mNativeRect;
	}
	//############################################################################
	TexturePtr Imagery::getTexture() const {
		return mTexture;
	}
	//############################################################################
	const std::string& Imagery::getName() const {
		return mName;
	}
	//############################################################################
	const std::string& Imagery::getFQN() const {
		return mFQN;
	}
	//############################################################################

}
;//namespace OpenGUI{


