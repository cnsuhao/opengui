// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_Imagery.h"
#include "OpenGUI_LogSystem.h"
//#include "OpenGUI_Imageset.h"

namespace OpenGUI {
	//############################################################################
	Imagery::Imagery( const String ImagesetName, const String Name, FRect areaRect, IRect nativeRect, TexturePtr texture )
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
	const String& Imagery::getName() const {
		return mName;
	}
	//############################################################################
	const String& Imagery::getFQN() const {
		return mFQN;
	}
	//############################################################################

}
;//namespace OpenGUI{


