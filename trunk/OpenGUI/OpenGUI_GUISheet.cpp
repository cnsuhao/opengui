
#include "OpenGUI.h"

namespace OpenGUI{
	//#####################################################################
	GUISheet::GUISheet(std::string name)
	{
		mObjectName=name;
		mElementRect.min = FVector2(0.0f,0.0f);
		mElementRect.max = FVector2(1.0f,1.0f);
	}
	//#####################################################################
};//namespace OpenGUI{