
#include "Amethyst.h"

//! This is the OpenGUI namespace, which contains the Amethyst namespace
namespace OpenGUI{
	//! All Amethyst classes are placed within this namespace
	namespace Amethyst{

	}
}

extern "C"{

	void __declspec(dllexport) pluginStart(){
		OpenGUI::LogManager::SlogMsg("Amethyst", OGLL_MSG)
			<< "Initializing Amethyst" << OpenGUI::Log::endlog;
	}

	void __declspec(dllexport) pluginStop(){
		OpenGUI::LogManager::SlogMsg("Amethyst", OGLL_MSG)
			<< "Shutting down Amethyst" << OpenGUI::Log::endlog;
	}

};
