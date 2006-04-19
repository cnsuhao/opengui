

#include "../DemoAppFramework/DemoAppFrameWork.h"


class Demo1App : public DemoApp
{
public:
	Demo1App() : DemoApp("OpenGUI - Demo 1") {}
	virtual void preRun();
	virtual void perframeRun(){};
	virtual void postRun(){};
};

void Demo1App::preRun()
{
	OpenGUI::XMLParser::LoadFromFile("demo1.xml");
	OpenGUI::System::getSingleton().setGUISheet(
		OpenGUI::System::getSingleton().getGUISheetByName("root")
		);
	
}

int main( void )
{
	Demo1App app;
	
	app.run();

	return 0;
	
}


