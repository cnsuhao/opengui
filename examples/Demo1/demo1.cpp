

#include "../DemoAppFramework/DemoAppFrameWork.h"


class Demo1App : public DemoApp
{
public:
	Demo1App() : DemoApp("OpenGUI - Demo 1") {}
	virtual void preRun();
	virtual void perframeRun();
	virtual void postRun(){}
};

void Demo1App::preRun()
{
	OpenGUI::XMLParser::LoadFromFile("demo1.xml");
	OpenGUI::System::getSingleton().setGUISheet(
		OpenGUI::System::getSingleton().getGUISheetByName("root")
		);
	
}
void Demo1App::perframeRun()
{
	static int val = 0;
	static bool dirUp = true;
	if(dirUp) val++;
	else val--;
	if(val <= 0) dirUp=true;
	if(val >= 900) dirUp=false;

	if(OpenGUI::System::getSingletonPtr()){
		OpenGUI::Widgets::Widget* w = (OpenGUI::Widgets::Widget*)
			OpenGUI::System::getSingleton().getElementByName("myTach");
		std::stringstream ss;
		ss << val;
		w->propertySet("needlevalue",ss.str());
	}
}


int main( void )
{
	Demo1App app;
	
	app.run();

	return 0;
	
}


