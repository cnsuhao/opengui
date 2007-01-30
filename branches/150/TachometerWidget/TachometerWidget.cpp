// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#define OPENGUI_WIDGET_EXPORTS
#include "OpenGUI.h"
#include "Tachometer.h"


extern "C" {

	void OPENGUI_WIDGET_API pluginStart() {
		using namespace OpenGUI;
		using namespace OpenGUI::Examples;
		LogManager::SlogMsg( "Tachometer", OGLL_MSG ) << "pluginStart() was called" << Log::endlog;
		WidgetManager& wm = WidgetManager::getSingleton();
		wm.RegisterWidgetFactory( "Tachometer", "OpenGUIEx", &Tachometer::createTachometerFactory );
	}

	void OPENGUI_WIDGET_API pluginStop() {
		using namespace OpenGUI;
		LogManager::SlogMsg( "Tachometer", OGLL_MSG ) << "pluginStop() was called" << Log::endlog;
		WidgetManager& wm = WidgetManager::getSingleton();
		wm.UnregisterWidgetFactory( "Tachometer", "OpenGUIEx" );
	}

};