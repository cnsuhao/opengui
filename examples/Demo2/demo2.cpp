
#include "../DemoAppFramework/DemoAppFrameWork.h"

#include "../Amethyst/Amethyst_Label.h"
#include "../Amethyst/Amethyst_Button.h"



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
	XMLParser::getSingleton().LoadFromFile("metal.xml");
	XMLParser::getSingleton().LoadFromFile("demo2.xml");
	XMLParser::getSingleton().LoadFromFile("Amethyst.xml");

	mScreen = ScreenManager::getSingleton().createScreen( "MainScreen", FVector2( 800, 600 ) );
	CursorPtr cursorPtr = CursorManager::getSingleton().CreateDefinedCursor("MetalCursor");
	mScreen->setCursor(cursorPtr);
	mScreen->enableCursor();

	Amethyst::Label* headerText = new Amethyst::Label();
	headerText->setName( "Header" );
	headerText->setFont( Font( "pecot", 40 ) );
	headerText->setText( "OpenGUI Amethyst Demo" );
	headerText->setTop( 0 );
	headerText->setLeft( 0 );
	headerText->setWidth( 400 );
	headerText->setHeight( 60 );
//	headerText->setAlignment(TextAlignment::ALIGN_LEFT, TextAlignment::ALIGN_TOP);
	mScreen->Children.add_back( headerText, true );

	Amethyst::SimpleButton* testButton = new Amethyst::SimpleButton();
	testButton->setImagery("MetalButtonNormal");
	testButton->setImageryMouseOver("MetalButtonHover");
	testButton->setImageryPressed("MetalButtonPress");
	testButton->setImageryDisabled("MetalButtonDisabled");
	testButton->setTop(70);
	testButton->setLeft(40);
	testButton->setWidth(100);
	testButton->setHeight(100);
	mScreen->Children.add_back( testButton, true );

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


