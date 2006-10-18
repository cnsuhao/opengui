
#include "../DemoAppFramework/DemoAppFrameWork.h"
//#include "../TachometerWidget/Tachometer.h"

class Demo1App : public DemoApp
{
public:
	Demo1App() : DemoApp("OpenGUI - Demo 1") {}
	virtual void preRun();
	virtual void perframeRun();
	virtual void postRun(){
		int i = 0;
	}
private:
	//OpenGUI::Widgets::TextLabel* mLabel;
	OpenGUI::TimerPtr mTimer;
	OpenGUI::Screen* mScreen;
};

using namespace OpenGUI;

class MyWidget:public Widget{
protected:
	void onDraw(Object* sender, Draw_EventArgs& evtArgs ){
		Brush& b = evtArgs.brush;
		FVector2 pos(400,300);
		Font fnt("pecot",12);
		
		FRect outlineRect(pos, FVector2(pos.x + 200, pos.y + 200));
		b.Text.drawTextArea("CAPITOL\nI am a sentence\nyjyjsupercalafragalisticexpialidocious",
			outlineRect, fnt, true, TextAlignment::ALIGN_JUSTIFIED, TextAlignment::ALIGN_CENTER);
		b.pushAlpha(0.5f);
		b.pushColor(Color::PresetBlue());
		b.Primitive.drawRect( outlineRect );
		b.pop();
		b.Primitive.drawOutlineRect( outlineRect, -5);
		b.pop();


		ImageryPtrList imgrylist = FontManager::getSingleton()._getFontAtlases();
		if ( imgrylist.size() > 0 ){
			//b.Image.drawImageUnscaled( imgrylist.front(), FVector2( 0, 0 ) );
			b.Image.drawImageUnscaledAndTiled(imgrylist.front(), FRect(0,0,150,400));
		}
	}
};
void Demo1App::preRun()
{
	mScreen = ScreenManager::getSingleton().createScreen("MainScreen", FVector2(800,600) );
	FontManager::getSingleton().RegisterFontSet("pecot.ttf","pecot");

	Widget* w = new MyWidget();
	w->setName("Blah");

	mScreen->Children.add_back( w, true );
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
void Demo1App::perframeRun()
{
	/*
	static int val = 0;
	static bool dirUp = true;
	if(dirUp) val++;
	else val--;
	if(val <= 0) dirUp=true;
	if(val >= 900) dirUp=false;

	if(OpenGUI::System::getSingletonPtr()){
		OpenGUI::Widgets::Widget* w = (OpenGUI::Widgets::Widget*)
			OpenGUI::System::getSingleton().getElementByName("myTach");

		OpenGUI::Widgets::Tachometer* t = static_cast<OpenGUI::Widgets::Tachometer*>(w);
		t->setNeedleValue((float) val);

		if(mTimer->getMilliseconds() > 200){
			mTimer->reset();
			std::stringstream ss;
			ss << "FPS: " << OpenGUI::System::getSingleton().statRenderFPS();
			mLabel->setText(ss.str());
		}
	}
	*/
}


int main( void )
{
	Demo1App app;
	
	app.run();

	return 0;
}


