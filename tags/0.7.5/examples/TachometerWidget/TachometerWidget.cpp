
#define OPENGUI_WIDGET_EXPORTS
#include "OpenGUI.h"
#include "Tachometer.h"


extern "C"{

	void OPENGUI_WIDGET_API pluginStart(){
		OpenGUI::LogManager::SlogMsg("Tachometer", OGLL_MSG)
			<< "pluginStart() was called" << OpenGUI::Log::endlog;
		
		OpenGUI::WidgetFactoryManager::getSingleton().registerWidgetFactory("OpenGUIExt", "Tachometer", OpenGUI::WidgetFactoryCallback( &OpenGUI::Widgets::Tachometer::createTachometerFactory ) );
	}

	void OPENGUI_WIDGET_API pluginStop(){
		OpenGUI::LogManager::SlogMsg("Tachometer", OGLL_MSG)
			<< "pluginStop() was called" << OpenGUI::Log::endlog;
	}

};