
#include "Amethyst.h"

//! This is the OpenGUI namespace, which contains the Amethyst namespace
namespace OpenGUI {
	//! All Amethyst classes are placed within this namespace
	namespace Amethyst {

		//############################################################################
		void Initialize() {
			LogManager::SlogMsg( "Amethyst", OGLL_MSG )
			<< "Initializing Amethyst" << Log::endlog;

			// register all widgets
			WidgetManager& wm = WidgetManager::getSingleton();
			wm.RegisterWidgetFactory( "Button", "Amethyst", &Button::createButtonFactory );
		}
		//############################################################################
		void Shutdown() {
			LogManager::SlogMsg( "Amethyst", OGLL_MSG )
			<< "Shutting down Amethyst" << Log::endlog;

			// remove widget registrations
			WidgetManager& wm = WidgetManager::getSingleton();
			wm.UnregisterWidgetFactory( "Button", "Amethyst" );
		}
		//############################################################################

	}
}


extern "C" {

	void __declspec( dllexport ) pluginStart() {
		using namespace OpenGUI::Amethyst;
		Initialize();
	}

	void __declspec( dllexport ) pluginStop() {
		using namespace OpenGUI::Amethyst;
		Shutdown();
	}

} // extern "C" {
