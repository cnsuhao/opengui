
#include "../DemoAppFramework/DemoAppFrameWork.h"
#include "../TachometerWidget/Tachometer.h"
#include "Renderer_OpenGL.h"

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
	OpenGUI::Widget* mStatText;
	OpenGUI::Examples::Tachometer* mTach;
};

using namespace OpenGUI;

class SimpleText: public Control {
public:
	SimpleText() {
		mVAlign = TextAlignment::ALIGN_TOP;
		mHAlign = TextAlignment::ALIGN_LEFT;
		mAutoWrap = false;
	}
	virtual ~SimpleText() {}
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
	void setAlignment( TextAlignment h_align, TextAlignment v_align ) {
		invalidate();
		mVAlign = v_align;
		mHAlign = h_align;
	}
	void setWrap(bool wrap){
		invalidate();
		mAutoWrap = wrap;
	}
protected:
	virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs ) {
		Brush& b = evtArgs.brush;
		b.Text.drawTextArea( mText, getRect(), mFont, mAutoWrap, mHAlign, mVAlign );
	}
private:
	std::string mText;
	Font mFont;
	TextAlignment mVAlign;
	TextAlignment mHAlign;
	bool mAutoWrap;
};

class MyWnd: public Window {
public:
	MyWnd() {}
	virtual ~MyWnd() {}
protected:
	virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs ) {
		Brush& b = evtArgs.brush;
		b.Primitive.drawOutlineRect( getRect(), -1 );
	}
};

void Demo1App::preRun() {
	XMLParser::getSingleton().LoadFromFile( "demo1.xml" );

	mScreen = ScreenManager::getSingleton().createScreen( "MainScreen", FVector2( 800, 600 ) );
	Viewport* v = (static_cast<Renderer_OpenGL*>(Renderer::getSingletonPtr()))->getDefaultViewport();
	mScreen->setViewport(v);
	CursorPtr cursorPtr = CursorManager::getSingleton().CreateDefinedCursor( "Square" );
	mScreen->setCursor( cursorPtr );
	mScreen->enableCursor();

	mTach = new Examples::Tachometer;
	mTach->setName( "Tachometer" );
	mTach->setBackgroundImagery( "TachBG" );
	mTach->setNeedleImagery( "TachNeedle" );
	mTach->setNeedleStartAngle(135.0f);
	mTach->setNeedleMaxValue(900.0f);
	mTach->setNeedleSweepAngle(225.0f);
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
	headerText->setAlignment( TextAlignment::ALIGN_LEFT, TextAlignment::ALIGN_TOP );
	mScreen->Children.add_back( headerText, true );

	SimpleText* statText = new SimpleText();
	mStatText = statText;
	statText->setName( "Stats" );
	statText->setFont( Font( "pecot", 20 ) );
	statText->setText( "Stats on the way!\nPreload\n1234567890." );
	statText->setTop( 0 );
	statText->setLeft( 500 );
	statText->setWidth( 400 );
	statText->setHeight( 60 );
	statText->setAlignment( TextAlignment::ALIGN_LEFT, TextAlignment::ALIGN_TOP );
	mScreen->Children.add_back( statText, true );

	MyWnd* wnd = new MyWnd();
	wnd->setName( "MyWnd" );
	wnd->setTop( 200 );
	wnd->setLeft( 100 );
	wnd->setWidth( 200 );
	wnd->setHeight( 200 );
	mScreen->Children.add_back( wnd, true );

	SimpleText* wndText = new SimpleText();
	wndText->setName( "wndText" );
	wndText->setFont( Font( "pecot", 12 ) );
	wndText->setText( "The contents of this small window are cached. The mini-tach shows your FPS as well.");
	wndText->setWrap(true);
	wndText->setTop( 0 );
	wndText->setLeft( 5 );
	wndText->setWidth( 200 );
	wndText->setHeight( 200 );
	wndText->setAlignment( TextAlignment::ALIGN_LEFT, TextAlignment::ALIGN_TOP );
	wnd->Children.add_back( wndText, true );
	//wnd->setVisible(false);

	Examples::Tachometer* wndTach = new Examples::Tachometer;
	wndTach->setName( "wndTach" );
	wndTach->setBackgroundImagery( "TachBG" );
	wndTach->setNeedleImagery( "TachNeedle" );
	wndTach->setNeedleStartAngle(135.0f);
	wndTach->setNeedleMaxValue(900.0f);
	wndTach->setNeedleSweepAngle(225.0f);
	wndTach->setNeedlePivot( FVector2( 0.5f, 0.5f ) );
	wndTach->setNeedleAnchor( FVector2( 0.10f, 0.50f ) );
	wndTach->setNeedleValue( 0.0f );
	wndTach->setLeft( 0.0f );
	wndTach->setTop( 100.0f );
	wndTach->setWidth( 100.0f );
	wnd->Children.add_back( wndTach, true );

	mTimer = OpenGUI::TimerManager::getSingleton().getTimer();
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

		if ( mTimer->getMilliseconds() > 500 ) {
			mTimer->reset();
			float FPS = ScreenManager::getSingleton().statGetFPS();
			std::stringstream ss;
			ss << "Update Time: " << mScreen->statsGetUpdateTime();
			ss << "\n";
			ss << "FPS: " << FPS;

			(( SimpleText* )mStatText )->setText( ss.str() );
			MyWnd* wnd = ( MyWnd* )mScreen->Children.getWidget( "MyWnd" );
			if ( wnd ) {
				Examples::Tachometer* wndTach = ( Examples::Tachometer* ) wnd->Children.getWidget( "wndTach" );
				wndTach->setNeedleValue( FPS );
				//wnd->setWidth(Math::Ceil(FPS));
				//wndTach->setAlpha(FPS/300.0f);
				//wnd->setAlpha(FPS/300.0f);
			}
		}
	}
}
void Demo1App::mousePositionCallback( int x, int y ) {
	int sx, sy;
	getWindowSize( sx, sy );
	mScreen->injectCursorPosition_Percent((( float )x ) / (( float )sx ), (( float )y ) / (( float )sy ) );
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


