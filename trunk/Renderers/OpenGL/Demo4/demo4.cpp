
#include "../DemoAppFramework/DemoAppFrameWork.h"
#include "Renderer_OpenGL.h"
#include "Amethyst.h"

class Demo4App : public DemoApp {
public:
	Demo4App() : DemoApp( "OpenGUI - Demo 4" ) {}
	virtual void preRun();
	virtual void perframeRun();
	virtual void postRun() {
		int i = 0;
	}
	virtual void mousePositionCallback( int x, int y );
	virtual void mouseButtonCallback( int button, int action );
private:
	OpenGUI::Widget* mLabel;
	OpenGUI::TimerPtr mTimer;
	OpenGUI::Screen* mScreen;
};

using namespace OpenGUI;


class TestFrame:public Control{
public:
	TestFrame(FacePtr face):mFace(face){}
protected:
	virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs ) {
		Brush& b = evtArgs.brush;
		b.Image.drawFace(mFace,getRect());
	}
	FacePtr mFace;
};



void Demo4App::preRun() {
	hideSystemCursor();
	XMLParser::getSingleton().LoadFromFile( "demo4.xml" );

	Viewport* v = (static_cast<Renderer_OpenGL*>(Renderer::getSingletonPtr()))->getDefaultViewport();
	mScreen = ScreenManager::getSingleton().createScreen( "MainScreen", FVector2( 800, 600 ), v );

	CursorPtr cursorPtr = CursorManager::getSingleton().CreateDefinedCursor( "Arrow" );
	mScreen->setCursor( cursorPtr );
	mScreen->enableCursor();


	FacePtr fptr;
	fptr = ImageryManager::getSingleton().getFace("GenericFrame");


	TestFrame* frame = new TestFrame(fptr);
	frame->setTop( 200 );
	frame->setLeft( 250 );
	frame->setWidth( 190 );
	frame->setHeight( 160 );
	mScreen->Children.add_front(frame,true);

	Widget* w;
	// Application label in the upper left
	w = WidgetManager::getSingleton().CreateDefinedWidget("BrassBalls:Label");
	w->setProperty("Top", Value(0.0f));
	w->setProperty("Left", Value(0.0f));
	w->setProperty("Width", Value(250.0f));
	w->setProperty("Height", Value(25.f));
	w->setProperty("Text", Value("Amethyst Regression Test Bed"));
	mScreen->Children.add_front(w, true);


	w = WidgetManager::getSingleton().CreateDefinedWidget("BrassBalls:Button");
	w->setProperty("Top", Value(50.0f));
	w->setProperty("Left", Value(50.0f));
	w->setProperty("Width", Value(55.0f));
	w->setProperty("Height", Value(30.f));
	w->setProperty("Text",Value("Test"));
	mScreen->Children.add_front(w, true);


	w = WidgetManager::getSingleton().CreateDefinedWidget("BrassBalls:CheckBox");
	w->setProperty("Top", Value(150.0f));
	w->setProperty("Left", Value(150.0f));
	w->setProperty("Width", Value(15.0f));
	w->setProperty("Height", Value(15.0f));
	mScreen->Children.add_front(w, true);
	w = WidgetManager::getSingleton().CreateDefinedWidget("BrassBalls:CheckBox");
	w->setProperty("Top", Value(170.0f));
	w->setProperty("Left", Value(150.0f));
	w->setProperty("Width", Value(15.0f));
	w->setProperty("Height", Value(15.f));
	mScreen->Children.add_front(w, true);

	w = WidgetManager::getSingleton().CreateDefinedWidget("BrassBalls:RadioButton");
	w->setProperty("Top", Value(150.0f));
	w->setProperty("Left", Value(190.0f));
	w->setProperty("Width", Value(15.0f));
	w->setProperty("Height", Value(15.f));
	w->setProperty("Group", Value("One"));
	mScreen->Children.add_front(w, true);

	w = WidgetManager::getSingleton().CreateDefinedWidget("BrassBalls:RadioButton");
	w->setProperty("Top", Value(150.0f));
	w->setProperty("Left", Value(210.0f));
	w->setProperty("Width", Value(15.0f));
	w->setProperty("Height", Value(15.f));
	w->setProperty("Group", Value("One"));
	mScreen->Children.add_front(w, true);

	w = WidgetManager::getSingleton().CreateDefinedWidget("BrassBalls:RadioButton");
	w->setProperty("Top", Value(170.0f));
	w->setProperty("Left", Value(190.0f));
	w->setProperty("Width", Value(15.0f));
	w->setProperty("Height", Value(15.f));
	w->setProperty("Group", Value("Two"));
	mScreen->Children.add_front(w, true);

	w = WidgetManager::getSingleton().CreateDefinedWidget("BrassBalls:RadioButton");
	w->setProperty("Top", Value(170.0f));
	w->setProperty("Left", Value(210.0f));
	w->setProperty("Width", Value(15.0f));
	w->setProperty("Height", Value(15.f));
	w->setProperty("Group", Value("Two"));
	mScreen->Children.add_front(w, true);

	

	// Show the full source Imageset in the lower right
	w = WidgetManager::getSingleton().CreateRawWidget("StaticImage","Amethyst");
	w->setProperty("Top", Value(600.0f - 256.0f));
	w->setProperty("Left", Value(800.0f - 256.0f));
	w->setProperty("Width", Value(256.0f));
	w->setProperty("Height", Value(256.0f));
	w->setProperty("Native_Scale", Value(false));
	w->setProperty("Imagery", Value(ImageryManager::getSingleton().getImagery("BrassBalls.png:All")));
	mScreen->Children.add_back(w, true);


	//Widget* label = WidgetManager::CreateDefinedWidget("Label");
	//label->setProperty("Text","This is some text");
	//label->setProperty("Left", 0.0f);
	//label->setProperty("Top", 0.0f);
	//mScreen->Children.add_front(label,true);
/*
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

*/




	mTimer = OpenGUI::TimerManager::getSingleton().getTimer();
}
void Demo4App::perframeRun() {


	if ( OpenGUI::System::getSingletonPtr() ) {


		if ( mTimer->getMilliseconds() > 500 ) {
			mTimer->reset();
			float FPS = ScreenManager::getSingleton().statGetFPS();
			std::stringstream ss;
			ss << "Update Time: " << mScreen->statsGetUpdateTime();
			ss << "\n";
			ss << "FPS: " << FPS;

			//(( SimpleText* )mStatText )->setText( ss.str() );
			//MyWnd* wnd = ( MyWnd* )mScreen->Children.getWidget( "MyWnd" );
			/*if ( wnd ) {
				Examples::Tachometer* wndTach = ( Examples::Tachometer* ) wnd->Children.getWidget( "wndTach" );
				wndTach->setNeedleValue( FPS );
				//wnd->setWidth(Math::Ceil(FPS));
				//wndTach->setAlpha(FPS/300.0f);
				//wnd->setAlpha(FPS/300.0f);
			}*/
		}
	}
}
void Demo4App::mousePositionCallback( int x, int y ) {
	int sx, sy;
	getWindowSize( sx, sy );
	mScreen->injectCursorPosition_Percent((( float )x ) / (( float )sx ), (( float )y ) / (( float )sy ) );
}
void Demo4App::mouseButtonCallback( int button, int action ) {
	if ( button == 0 ) {
		if ( action == 1 )
			mScreen->injectCursorPress();
		else
			mScreen->injectCursorRelease();
	}
}

int main( void ) {
	Demo4App app;

	app.run();

	return 0;
}

