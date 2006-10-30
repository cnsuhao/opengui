
#include "../DemoAppFramework/DemoAppFrameWork.h"

class Demo2App : public DemoApp {
public:
	Demo2App() : DemoApp( "OpenGUI - Demo 2" ) {}
	virtual void preRun();
	virtual void perframeRun();
	virtual void postRun() {
		int i = 0;
	}
	virtual void mousePositionCallback( int x, int y );
	virtual void mouseButtonCallback( int button, int action );
private:
	//OpenGUI::Widgets::TextLabel* mLabel;
	OpenGUI::TimerPtr mTimer;
	OpenGUI::Screen* mScreen;
};

using namespace OpenGUI;


void Demo2App::preRun() {
	//XMLParser::getSingleton().LoadFromFile("demo1.xml");

	mScreen = ScreenManager::getSingleton().createScreen( "MainScreen", FVector2( 800, 600 ) );
	//CursorPtr cursorPtr = CursorManager::getSingleton().CreateDefinedCursor("Square");
	//mScreen->setCursor(cursorPtr);
	//mScreen->enableCursor();

}
void Demo2App::perframeRun() {
	
}
void Demo2App::mousePositionCallback( int x, int y ) {
	int sx,sy;
	getWindowSize(sx,sy);
	mScreen->injectCursorPosition_Percent(((float)x) / ((float)sx),((float)y) / ((float)sy) );
}
void Demo2App::mouseButtonCallback( int button, int action ) {
	if ( button == 0 ) {
		if ( action == 1 )
			mScreen->injectCursorPress();
		else
			mScreen->injectCursorRelease();
	}
}

int main( void ) {
	Demo2App app;

	app.run();

	return 0;
}


