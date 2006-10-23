
#include "../DemoAppFramework/DemoAppFrameWork.h"
#include "../TachometerWidget/Tachometer.h"


class Demo1App : public DemoApp {
public:
	Demo1App() : DemoApp( "OpenGUI - Demo 1" ) {}
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
	OpenGUI::Examples::Tachometer* mTach;
};

using namespace OpenGUI;

class SimpleText: public Control {
public:
	SimpleText(){
		mVAlign = TextAlignment::ALIGN_TOP;
		mHAlign = TextAlignment::ALIGN_LEFT;
	}
	~SimpleText(){}
	void setText( const std::string& text ) {
		invalidate();
		mText = text;
	}
	const std::string& getText() const {
		return mText;
	}
	void setFont( const Font& font ) {
		invalidate();
		mFont = font;
	}
	const Font& getFont() const {
		return mFont;
	}
	void setAlignment(TextAlignment h_align, TextAlignment v_align){
		invalidate();
		mVAlign = v_align;
		mHAlign = h_align;
	}
protected:
	virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs ) {
		Brush& b = evtArgs.brush;
		b.Text.drawTextArea( mText, getRect(), mFont, false, mHAlign, mVAlign );
	}
private:
	std::string mText;
	Font mFont;
	TextAlignment mVAlign;
	TextAlignment mHAlign;
};

void Demo1App::preRun() {

	Imageset* imgset = ImageryManager::createImagesetEx( "tachometer.png" );
	imgset->createImagery( "TachBG", 2, 2, 321, 321 );
	imgset->createImagery( "TachNeedle", 348, 42, 7, 131 );

	mScreen = ScreenManager::getSingleton().createScreen( "MainScreen", FVector2( 800, 600 ) );
	FontManager::getSingleton().RegisterFontSet( "pecot.ttf", "pecot" );
	mScreen->enableCursor();

	mTach = new Examples::Tachometer;
	mTach->setName( "Tachometer" );
	mTach->setBackgroundImagery( "TachBG" );
	mTach->setNeedleImagery( "TachNeedle" );
	mTach->setNeedleScale( 135.0f, 900.0f, 225.0f );
	mTach->setNeedlePivot( FVector2( 0.5f, 0.5f ) );
	mTach->setNeedleAnchor( FVector2( 0.10f, 0.50f ) );
	mTach->setNeedleValue( 0.0f );
	mTach->setLeft( 800.0f - 322.0f );
	mTach->setTop( 600.0f - 322.0f );
	mTach->setWidth( 321.0f );
	mScreen->Children.add_back( mTach, true );

	SimpleText* headerText = new SimpleText();
	headerText->setName( "Header" );
	headerText->setFont( Font( "pecot", 40 ) );
	headerText->setText( "OpenGUI Demo 1" );
	headerText->setTop( 0 );
	headerText->setLeft( 0 );
	headerText->setWidth( 400 );
	headerText->setHeight( 60 );
	headerText->setAlignment(TextAlignment::ALIGN_LEFT, TextAlignment::ALIGN_TOP);
	mScreen->Children.add_back( headerText, true );
	/*
		OpenGUI::XMLParser::LoadFromFile("demo1.xml");
		OpenGUI::System::getSingleton().setGUISheet(
			OpenGUI::System::getSingleton().getGUISheetByName("root")
			);
		mLabel = static_cast<OpenGUI::Widgets::TextLabel*>
			( OpenGUI::System::getSingleton().createWidget("TextLabel","OpenGUI") );
		OpenGUI::System::getSingleton().getGUISheetByName("root")->addChildElement(mLabel,"Msg");
		mLabel->setFont("pecot");
		mLabel->setFontSize(16);
		mLabel->setAlignment_Horiz(OpenGUI::TextAlignment::ALIGN_RIGHT);
		mLabel->setPos(0.0f,0.0f);
		mLabel->setSize(1.0f,1.0f);
		mLabel->setText("Press ESC to Quit");

		mLabel = static_cast<OpenGUI::Widgets::TextLabel*>
			( OpenGUI::System::getSingleton().createWidget("TextLabel","OpenGUI") );
		OpenGUI::System::getSingleton().getGUISheetByName("root")->addChildElement(mLabel,"FPS");
		mLabel->setFont("pecot");
		mLabel->setFontSize(16);
		mLabel->setPos(0.0f,0.0f);
		mLabel->setSize(1.0f,1.0f);
		mLabel->setText("FPS On the way!");

		mTimer = OpenGUI::TimerManager::getSingleton().getTimer();
		*/
}
void Demo1App::perframeRun() {
	static int val = 0;
	static bool dirUp = true;
	if ( dirUp ) val++;
	else val--;
	if ( val <= 0 ) dirUp = true;
	if ( val >= 900 ) dirUp = false;

	if ( OpenGUI::System::getSingletonPtr() ) {
		mTach->setNeedleValue(( float ) val );

		//if(mTimer->getMilliseconds() > 200){
		//	mTimer->reset();
		//	std::stringstream ss;
		//ss << "FPS: " << OpenGUI::System::getSingleton().statRenderFPS();
		//mLabel->setText(ss.str());
		//}
	}
}
void Demo1App::mousePositionCallback( int x, int y ) {
	int sx,sy;
	getWindowSize(sx,sy);
	mScreen->injectCursorPosition_Percent(((float)x) / ((float)sx),((float)y) / ((float)sy) );
}
void Demo1App::mouseButtonCallback( int button, int action ) {
	if ( button == 0 ) {
		if ( action == 1 )
			mScreen->injectCursorPress();
		else
			mScreen->injectCursorRelease();
	}
}

int main( void ) {
	Demo1App app;

	app.run();

	return 0;
}


