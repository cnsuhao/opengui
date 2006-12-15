// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

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
#include "../Amethyst/Amethyst_ScrollBar_H.h"
#include "../Amethyst/Amethyst_ScrollBar_V.h"
#include "../Amethyst/Amethyst_TextBox.h"

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
	virtual void keyCallback( int key, int action );

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
	XMLParser::getSingleton().LoadFromFile("BlueGui.xml");
	XMLParser::getSingleton().LoadFromFile("Generic.xml");
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

#if 0
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
#else
	// create a container for the button
	Amethyst::Panel *pButtonPanel = (Amethyst::Panel *) Amethyst::Panel::CreatePanelFactory();
	pButtonPanel->setTop(70);
	pButtonPanel->setLeft(40);
	pButtonPanel->setHeight(60);
	pButtonPanel->setWidth(200);
	mScreen->Children.add_back(pButtonPanel, true);

	Amethyst::SimpleButton* testButton = new Amethyst::SimpleButton();
	testButton->setName("SampleBlueButton");
	testButton->setImagery("BlueGuiButtonNormal");
	testButton->setImageryMouseOver("BlueGuiButtonHover");
	testButton->setImageryPressed("BlueGuiButtonPress");
	testButton->setImageryDisabled("BlueGuiButtonDisabled");
	testButton->setTop(10);
	testButton->setLeft(30);
	testButton->setWidth(32);
	testButton->setHeight(32);
	testButton->setText("Button!");
	pButtonPanel->Children.add_back( testButton, true );
#endif

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

	Amethyst::Panel *pPanelFrame = (Amethyst::Panel *) Amethyst::Panel::CreatePanelFactory();
	pPanelFrame->setTop(430);
	pPanelFrame->setLeft(5);
	pPanelFrame->setHeight(100);
	pPanelFrame->setWidth(200);
	mScreen->Children.add_back(pPanelFrame, true);


	Amethyst::Frame *pFrame = (Amethyst::Frame *) Amethyst::Frame::CreateFrameFactory();
	pFrame->setTop(25);
	pFrame->setLeft(25);
	pFrame->setHeight(50);
	pFrame->setWidth(150);
#if 0
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
#else
	pFrame->setImagery("GenericFrameUL", Amethyst::Frame::UL);
	pFrame->setImagery("GenericFrameUM", Amethyst::Frame::UM);
	pFrame->setImagery("GenericFrameUR", Amethyst::Frame::UR);
	pFrame->setImagery("GenericFrameML", Amethyst::Frame::ML);
	pFrame->setImagery("GenericFrameMM", Amethyst::Frame::MM);
	pFrame->setImagery("GenericFrameMR", Amethyst::Frame::MR);
	pFrame->setImagery("GenericFrameLL", Amethyst::Frame::LL);
	pFrame->setImagery("GenericFrameLM", Amethyst::Frame::LM);
	pFrame->setImagery("GenericFrameLR", Amethyst::Frame::LR);
#endif
	pPanelFrame->Children.add_back(pFrame, true);

	Amethyst::StaticImage *pBGImage = (Amethyst::StaticImage *) Amethyst::StaticImage::CreateStaticImageFactory();
	pBGImage->setTop(0);
	pBGImage->setLeft(0);
	pBGImage->setHeight(100);
	pBGImage->setWidth(200);
	pBGImage->setImagery("PieFace");
	pPanelFrame->Children.add_back(pBGImage, true);


	Amethyst::ScrollBar_H *pSH = (Amethyst::ScrollBar_H *) Amethyst::ScrollBar_H::CreateScrollBar_HFactory();
	pSH->setTop(430);
	pSH->setLeft(370);
	pSH->setHeight(35);
	pSH->setWidth(150);
	pSH->setImagery("GenericHScroll1");
	pSH->setThumbImagery("GenericHScrollThumb1");
	mScreen->Children.add_back(pSH, true);

	Amethyst::ScrollBar_V *pSV = (Amethyst::ScrollBar_V *) Amethyst::ScrollBar_V::CreateScrollBar_VFactory();
	pSV->setTop(430);
	pSV->setLeft(550);
	pSV->setHeight(150);
	pSV->setWidth(35);
	pSV->setImagery("GenericVScroll1");
	pSV->setThumbImagery("GenericVScrollThumb1");
	mScreen->Children.add_back(pSV, true);


	Amethyst::TextBox *pBox = (Amethyst::TextBox *) Amethyst::TextBox::createTextBoxFactory();
	pBox->setTop(400);
	pBox->setLeft(370);
	pBox->setHeight(35);
	pBox->setWidth(150);
	pBox->setImagery("GenericHScroll1");
	mScreen->Children.add_back(pBox, true);

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

void Demo2App::keyCallback( int key, int action )
{
	if(action)
		mScreen->injectCharacter(key);
}


int main( void ) {
	Demo2App app;

	app.run();

	return 0;
}




