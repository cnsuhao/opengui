
#include "OpenGUI.h"

namespace OpenGUI{
	void Renderer::alertViewportDimensionsChanged()
	{
		if(System::getSingletonPtr()){
			System::getSingletonPtr()->notifyViewportDimensionsChanged();
		}
	}
	//############################################################################
	void Renderer::alertScreenDimensionsChanged()
	{
		if(System::getSingletonPtr()){
			System::getSingletonPtr()->notifyScreenDimensionsChanged();
		}
	}
};

