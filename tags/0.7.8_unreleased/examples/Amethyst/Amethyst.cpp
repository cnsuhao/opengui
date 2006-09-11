
#include "OpenGUI.h"


extern "C"{

	void __declspec(dllexport) pluginStart(){
		OpenGUI::LogManager::SlogMsg("Amethyst", OGLL_MSG)
			<< "pluginStart() was called" << OpenGUI::Log::endlog;
	}

	void __declspec(dllexport) pluginStop(){
		OpenGUI::LogManager::SlogMsg("Amethyst", OGLL_MSG)
			<< "pluginStop() was called" << OpenGUI::Log::endlog;
	}

};
