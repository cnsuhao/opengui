
#include "OpenGUI.h"


extern "C"{

	void __declspec(dllexport) pluginStart(){
		OpenGUI::LogManager::SlogMsg("Tachometer", OGLL_MSG)
			<< "pluginStart() was called" << OpenGUI::Log::endlog;
	}

	void __declspec(dllexport) pluginStop(){
		OpenGUI::LogManager::SlogMsg("Tachometer", OGLL_MSG)
			<< "pluginStop() was called" << OpenGUI::Log::endlog;
	}

};