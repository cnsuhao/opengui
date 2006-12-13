
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
			wm.RegisterWidgetFactory( "Label", "Amethyst", &Label::createLabelFactory );
			wm.RegisterWidgetFactory( "Button", "Amethyst", &Button::createButtonFactory );
			wm.RegisterWidgetFactory( "CheckBox", "Amethyst", &CheckBox::createCheckBoxFactory );
			wm.RegisterWidgetFactory( "RadioButton", "Amethyst", &RadioButton::createRadioButtonFactory );
			wm.RegisterWidgetFactory( "StaticImage", "Amethyst", &StaticImage::createStaticImageFactory );
			wm.RegisterWidgetFactory( "ProgressBar", "Amethyst", &ProgressBar::createProgressBarFactory );
			wm.RegisterWidgetFactory( "Panel", "Amethyst", &Panel::createPanelFactory );
			wm.RegisterWidgetFactory( "ScrollBar", "Amethyst", &ScrollBar::createScrollBarFactory );
			wm.RegisterWidgetFactory( "Window", "Amethyst", &Window::createWindowFactory );
		}
		//############################################################################
		void Shutdown() {
			LogManager::SlogMsg( "Amethyst", OGLL_MSG )
			<< "Shutting down Amethyst" << Log::endlog;

			// remove widget registrations
			WidgetManager& wm = WidgetManager::getSingleton();
			wm.UnregisterWidgetFactory( "Label", "Amethyst" );
			wm.UnregisterWidgetFactory( "Button", "Amethyst" );
			wm.UnregisterWidgetFactory( "CheckBox", "Amethyst" );
			wm.UnregisterWidgetFactory( "RadioButton", "Amethyst" );
			wm.UnregisterWidgetFactory( "StaticImage", "Amethyst" );
			wm.UnregisterWidgetFactory( "ProgressBar", "Amethyst" );
			wm.UnregisterWidgetFactory( "Panel", "Amethyst" );
			wm.UnregisterWidgetFactory( "ScrollBar", "Amethyst" );
			wm.UnregisterWidgetFactory( "Window", "Amethyst" );
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
