
#include "../DemoAppFramework/DemoAppFrameWork.h"

#include "../Amethyst/Amethyst_Label.h"
#include "../Amethyst/Amethyst_StaticImage.h"
#include "../Amethyst/Amethyst_Button.h"
#include "../Amethyst/Amethyst_CheckBox.h"
#include "../Amethyst/Amethyst_RadioButton.h"
#include "../Amethyst/Amethyst_ProgressBar.h"
#include "../Amethyst/Amethyst_Panel.h"
#include "../Amethyst/Amethyst_Frame.h"
#include "../Amethyst/Amethyst_ListBox.h"

#include "OpenGUI.h"
#include "OpenGUI_EventHandler.h"
#include "Renderer_OpenGL.h"

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

Amethyst::ProgressBar *g_pProgressBar = NULL;
Amethyst::Panel *g_pPanel = NULL;

void buttonCallback( Object *pObj , EventArgs *pEvent )
{
//	g_pProgressBar->doStep();

	g_pPanel->Scroll(FVector2(-3,-3));
}


void Demo2App::preRun() {
	XMLParser::getSingleton().LoadFromFile("metal.xml");
	XMLParser::getSingleton().LoadFromFile("demo2.xml");
	XMLParser::getSingleton().LoadFromFile("Amethyst.xml");

	mScreen = ScreenManager::getSingleton().createScreen( "MainScreen", FVector2( 800, 600 ) );
	Viewport* v = (static_cast<Renderer_OpenGL*>(Renderer::getSingletonPtr()))->getDefaultViewport();
	mScreen->setViewport(v);

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
	headerText->setAlignment(TextAlignment::ALIGN_LEFT, TextAlignment::ALIGN_TOP);
	mScreen->Children.add_back( headerText, true );

	Amethyst::SimpleButton* testButton = new Amethyst::SimpleButton();
	testButton->setName("SampleMetalButton");
	testButton->setImagery("MetalButtonNormal");
	testButton->setImageryMouseOver("MetalButtonHover");
	testButton->setImageryPressed("MetalButtonPress"); 
	testButton->setImageryDisabled("MetalButtonDisabled");
	testButton->setTop(70);
	testButton->setLeft(40);
	testButton->setWidth(300);
	testButton->setHeight(60);
	testButton->setText("Button!");
	mScreen->Children.add_back( testButton, true );

	testButton->getEvents().createEvent("Activate");
	testButton->getEvents()["Activate"].add( new EventCallback((EventCallback::EventCallbackFunc *)&buttonCallback) );

	Amethyst::CheckBox* testCheck = new Amethyst::CheckBox();
	testCheck->setName("SampleMetalCheck");
	testCheck->setImagery("MetalButtonNormal");
	testCheck->setImageryMouseOver("MetalButtonHover");
	testCheck->setImageryPressed("MetalButtonPress"); 
	testCheck->setImageryDisabled("MetalButtonDisabled");
	testCheck->setSelImagery("MetalButtonNormalX");
	testCheck->setSelImageryMouseOver("MetalButtonHoverX");
	testCheck->setSelImageryPressed("MetalButtonPressX"); 
	testCheck->setSelImageryDisabled("MetalButtonDisabledX");
	testCheck->setTop(70);
	testCheck->setLeft(400);
	testCheck->setWidth(60);
	testCheck->setHeight(60);
	mScreen->Children.add_back( testCheck, true );

	testCheck->getEvents().createEvent("Activate");
	testCheck->getEvents()["Activate"].add( new EventCallback((EventCallback::EventCallbackFunc *)&buttonCallback) );


	Amethyst::RadioButton* testRadio1 = new Amethyst::RadioButton();
	testRadio1->setName("SampleMetalCheckRadio1");
	testRadio1->setImagery("MetalButtonNormal");
	testRadio1->setImageryMouseOver("MetalButtonHover");
	testRadio1->setImageryPressed("MetalButtonPress"); 
	testRadio1->setImageryDisabled("MetalButtonDisabled");
	testRadio1->setSelImagery("MetalButtonNormalX");
	testRadio1->setSelImageryMouseOver("MetalButtonHoverX");
	testRadio1->setSelImageryPressed("MetalButtonPressX"); 
	testRadio1->setSelImageryDisabled("MetalButtonDisabledX");
	testRadio1->setTop(150);
	testRadio1->setLeft(40);
	testRadio1->setWidth(60);
	testRadio1->setHeight(60);
	testRadio1->setGroup("testGroup");
	mScreen->Children.add_back( testRadio1, true );

	testRadio1->getEvents().createEvent("Activate");
	testRadio1->getEvents()["Activate"].add( new EventCallback((EventCallback::EventCallbackFunc *)&buttonCallback) );

	Amethyst::RadioButton* testRadio2 = new Amethyst::RadioButton();
	testRadio2->setName("SampleMetalCheckRadio2");
	testRadio2->setImagery("MetalButtonNormal");
	testRadio2->setImageryMouseOver("MetalButtonHover");
	testRadio2->setImageryPressed("MetalButtonPress"); 
	testRadio2->setImageryDisabled("MetalButtonDisabled");
	testRadio2->setSelImagery("MetalButtonNormalX");
	testRadio2->setSelImageryMouseOver("MetalButtonHoverX");
	testRadio2->setSelImageryPressed("MetalButtonPressX"); 
	testRadio2->setSelImageryDisabled("MetalButtonDisabledX");
	testRadio2->setTop(220);
	testRadio2->setLeft(40);
	testRadio2->setWidth(60);
	testRadio2->setHeight(60);
	testRadio2->setGroup("testGroup");
	mScreen->Children.add_back( testRadio2, true );

	testRadio2->getEvents().createEvent("Activate");
	testRadio2->getEvents()["Activate"].add( new EventCallback((EventCallback::EventCallbackFunc *)&buttonCallback) );

	Amethyst::RadioButton* testRadio3 = new Amethyst::RadioButton();
	testRadio3->setName("SampleMetalCheckRadio3");
	testRadio3->setImagery("MetalButtonNormal");
	testRadio3->setImageryMouseOver("MetalButtonHover");
	testRadio3->setImageryPressed("MetalButtonPress"); 
	testRadio3->setImageryDisabled("MetalButtonDisabled");
	testRadio3->setSelImagery("MetalButtonNormalX");
	testRadio3->setSelImageryMouseOver("MetalButtonHoverX");
	testRadio3->setSelImageryPressed("MetalButtonPressX"); 
	testRadio3->setSelImageryDisabled("MetalButtonDisabledX");
	testRadio3->setTop(290);
	testRadio3->setLeft(40);
	testRadio3->setWidth(60);
	testRadio3->setHeight(60);
	testRadio3->setGroup("testGroup");
	mScreen->Children.add_back( testRadio3, true );

	testRadio3->getEvents().createEvent("Activate");
	testRadio3->getEvents()["Activate"].add( new EventCallback((EventCallback::EventCallbackFunc *)&buttonCallback) );

	Amethyst::ProgressBar *bar = new Amethyst::ProgressBar;
	bar->setTop(290);
	bar->setLeft(110);
	bar->setHeight(60);
	bar->setWidth(400);
	bar->setFont(Font( "pecot", 20 ));
	mScreen->Children.add_back(bar, true);

	g_pProgressBar = bar;

	Amethyst::Panel *pPanel = (Amethyst::Panel *) Amethyst::Panel::CreatePanelFactory();
	pPanel->setTop(220);
	pPanel->setLeft(110);
	pPanel->setHeight(53);
	pPanel->setWidth(51);
	mScreen->Children.add_back(pPanel, true);
	g_pPanel = pPanel;

	Amethyst::StaticImage *pStaticImage = (Amethyst::StaticImage *) Amethyst::StaticImage::CreateStaticImageFactory();
	pStaticImage->setTop(0);
	pStaticImage->setLeft(0);
	pStaticImage->setHeight(106);
	pStaticImage->setWidth(103);
	pStaticImage->setImagery("PieFace");
	pPanel->Children.add_back(pStaticImage, true);

	Amethyst::Frame *pFrame = (Amethyst::Frame *) Amethyst::Frame::CreateFrameFactory();
	pFrame->setTop(430);
	pFrame->setLeft(110);
	pFrame->setHeight(150);
	pFrame->setWidth(400);
	pFrame->setImagery("FrameUL", Amethyst::Frame::UL);
	pFrame->setImagery("FrameUM", Amethyst::Frame::UM);
	pFrame->setImagery("FrameUR", Amethyst::Frame::UR);
	pFrame->setImagery("FrameML", Amethyst::Frame::ML);
	pFrame->setImagery("FrameMM", Amethyst::Frame::MM);
//	pFrame->setImagery("PieFace", Amethyst::Frame::MM);
	pFrame->setImagery("FrameMR", Amethyst::Frame::MR);
	pFrame->setImagery("FrameLL", Amethyst::Frame::LL);
	pFrame->setImagery("FrameLM", Amethyst::Frame::LM);
	pFrame->setImagery("FrameLR", Amethyst::Frame::LR);
	mScreen->Children.add_back(pFrame, true);
}


int count = 0;
void Demo2App::perframeRun() {
	if(++count >= 100)
	{
		count = 0;
		g_pProgressBar->doStep();
	}
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




