#include "OpenGUI_Screen.h"

namespace OpenGUI{
	//############################################################################
	Screen::Screen(const std::string& screenName, const FVector2& initialSize){
		mName = screenName;
		mSize = initialSize;
	}
	//############################################################################
	Screen::~Screen(){

	}
	//############################################################################
}//namespace OpenGUI{