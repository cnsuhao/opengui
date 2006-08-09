
#include <Windows.h>
#include "OgreRefApp.h"
#include <OgreEventListeners.h> 


#include "OpenGUI_BaseWidgets.h"


// Kids, don't ever make an entire program in a single file like this.
//   It's bad karma.



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class GUIState{
	friend class GUIStateMngr;
public:
	enum Mode {
		Waiting, //waiting to start
		Starting, //spinning up
		Running, //waiting to stop
		Ending, //spinning down
		Done //stopped
	};
	GUIState(){
		OpenGUI::LogManager::SlogMsg("GUIState", 0)
			<< "+++ New State Created" << OpenGUI::Log::endlog;
	}
	virtual ~GUIState(){
		OpenGUI::LogManager::SlogMsg("GUIState", 0)
			<< "--- New State Created" << OpenGUI::Log::endlog;
	}
protected:
	//return false from any of these to quit the application
	virtual bool run_Running(){ return true; }
	virtual bool run_Starting(){ advanceMyMode(); return true; }
	virtual bool run_Ending(){ advanceMyMode(); return true; }

	void advanceMyMode()
	{
		switch(mCurMode){
			case Starting:
				setMode(Running);
				break;
			case Ending:
				setMode(Done);
				break;
			case Waiting:
			case Done:
			case Running:
			default:
				break;
		};
	}
	bool justSwitched(){return mJustSwitched;}
private:
	//returns false to quit
	bool run()
	{
		bool retval;
		switch(mCurMode){
			case Waiting:
			case Done: retval = true; break;
			case Starting: retval = run_Starting(); break;
			case Running: retval = run_Running(); break;
			case Ending: retval = run_Ending(); break;
			default:
				retval = false;
		};
		if(mJustSwitched) mJustSwitched = false;
		return retval;
	}
	void setMode(Mode newMode){
		mCurMode = newMode;
		unsigned int stateInt = newMode;
		OpenGUI::LogManager::SlogMsg("GUIState", 0)
			<< "<<<< Entered New State: " << stateInt << OpenGUI::Log::endlog;
		mJustSwitched = true;
	}
	
	bool mJustSwitched; //read only
	Mode mCurMode; //this is controlled directly by GUIStateMngr
	
};
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class GUIStateMngr{
public:
	GUIStateMngr()
	{
		mCurState = 0;
		mNextState = 0;
		mStop = false;
	}
	~GUIStateMngr()
	{
		if(mCurState) delete mCurState;
		if(mNextState) delete mNextState;
	}
	bool needShutdown() { return mStop; }
	void setNextState(GUIState* nextState){
		if(mNextState) delete mNextState;
		mNextState = nextState;
	}
	void runStates(){
		if(mCurState){
			if(mCurState->mCurMode == GUIState::Waiting)
				mCurState->setMode(GUIState::Starting);

			mStop = mStop || !mCurState->run();
		}
		tryStateChange();
	}

private:
	bool mStop;
	GUIState* mCurState;
	GUIState* mNextState;
	void tryStateChange(){
		if( mNextState ){
			if( mCurState ){
				if( mCurState->mCurMode == GUIState::Running){
					mCurState->setMode(GUIState::Ending);
				}
				if( mCurState->mCurMode == GUIState::Done ){
					delete mCurState;
					mCurState = mNextState;
					mNextState = 0;
				}
			}else{
				mCurState = mNextState;
				mNextState = 0;
			}
		}
	}
};
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
GUIStateMngr* gState = 0;
OpenGUI::GenericCursor* mCursor = 0;
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class AppEndState : public GUIState{
public:
	virtual bool run_Running(){ return false; }
};
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class LogoState : public GUIState{
	/*
	virtual bool run_Starting(){ advanceMyMode(); return true; }
	virtual bool run_Running(){ advanceMyMode(); return true; }
	virtual bool run_Ending(){ advanceMyMode(); return true; }
	*/
	virtual bool run_Starting()
	{
		if(justSwitched()){
			mLogoWidget = (OpenGUI::Widgets::StaticImage* ) 
				OpenGUI::System::getSingletonPtr()->getElementByName("Logo");
			if(!mLogoWidget)
				return false;

			float x;
			x = 0.0f - mLogoWidget->getRect().getWidth();
			mLogoWidget->setPos(x,0.0f);
			mTimer = OpenGUI::TimerManager::getSingleton().getTimer();
			mFirstMove = 0;
			return true;
		}

		if(mFirstMove < 10){
			mFirstMove++;
			mTimer->reset();
			return true;
		}

		const float dist_per_sec = 0.6f;
		float movDist = mTimer->getMilliseconds() * dist_per_sec / 1000.0f;
		mTimer->reset();

		float curX = mLogoWidget->getRect().getPosition().x;
		mLogoWidget->setPos(curX + movDist, 0.0f);
		curX = mLogoWidget->getRect().getPosition().x;

		if( curX > 0.0f ){
			mLogoWidget->setPos(0.0f ,0.0f);
			advanceMyMode();
		}
		return true;
	}
	virtual bool run_Running(){ advanceMyMode(); return true; }
	virtual bool run_Ending()
	{
		if(justSwitched()){
			mTimer->reset();
			return true;
		}

		const float dist_per_sec = -0.6f;
		float movDist = mTimer->getMilliseconds() * dist_per_sec / 1000.0f;
		mTimer->reset();

		float curX = mLogoWidget->getRect().getPosition().x;
		mLogoWidget->setPos(curX + movDist, 0.0f);
		float curX2 = mLogoWidget->getRect().getPosition().x +
			mLogoWidget->getRect().getWidth();

		if( curX2 < 0.0f ){
			mLogoWidget->setPos(-0.6f ,0.0f);
			advanceMyMode();
		}
		return true;
	}

private:
	int mFirstMove;
	OpenGUI::TimerPtr mTimer; 
	OpenGUI::Widgets::StaticImage* mLogoWidget;
};
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class OpenGUIState : public GUIState{
	/*
	virtual bool run_Starting(){ advanceMyMode(); return true; }
	virtual bool run_Running(){ advanceMyMode(); return true; }
	virtual bool run_Ending(){ advanceMyMode(); return true; }
	*/
};


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class OpenGUIInputReader : Ogre::FrameListener
{
public:
	OpenGUIInputReader(OpenGUI::System* system, Ogre::RenderWindow* window)
	{
		mSystem = system;
		Ogre::Root::getSingleton().addFrameListener(this);
		mInputDevice = Ogre::PlatformManager::getSingleton().createInputReader();
		mInputDevice->initialise(window,true, true);
		//whatever the default scale is, it need to be double that!
		mInputDevice->setMouseScale( mInputDevice->getMouseScale() * 2.0f );
		mButtonWasDown = false;
	}
	virtual ~OpenGUIInputReader()
	{
		Ogre::Root::getSingleton().removeFrameListener(this);
		Ogre::PlatformManager::getSingleton().destroyInputReader( mInputDevice );
	}

	virtual bool frameStarted (const FrameEvent &evt)
	{
		mInputDevice->capture();

		gState->runStates();

		if( mInputDevice->isKeyDown( KC_GRAVE ) )
			return false; //forced bail out

		if( mInputDevice->isKeyDown( KC_ESCAPE ) ){
			gState->setNextState( new AppEndState );
		}

		if( mInputDevice->isKeyDown( KC_L ) )
			gState->setNextState( new LogoState );
		

		if( gState ){
			if( gState->needShutdown() )
				return false;
		}


		long mx = mInputDevice->getMouseRelX();
		long my = mInputDevice->getMouseRelY();
		mSystem->injectMouseMovement(mx * mInputDevice->getMouseScale(),
			my * mInputDevice->getMouseScale());

		bool curBtnState;
		curBtnState = mInputDevice->getMouseButton( 0 );
		if( curBtnState != mButtonWasDown ){
			mButtonWasDown = curBtnState;
			if(curBtnState)
				mSystem->injectMouseButtonDown( OpenGUI::MouseButtonLeft );
			else
				mSystem->injectMouseButtonUp( OpenGUI::MouseButtonLeft );
		}
		
		return true;
	}
	
	//virtual bool frameEnded(const FrameEvent &evt){return true;}
protected:
	OpenGUI::System* mSystem;
	Ogre::InputReader* mInputDevice;
	bool mButtonWasDown;
};
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class OgreDemoApp : public OgreRefApp
{
public:
	OgreDemoApp()
	{
		m_ogInputReader = 0;
		gState = new GUIStateMngr;
		mCursor = new OpenGUI::GenericCursor;
	}
	virtual ~OgreDemoApp()
	{
		if(m_ogInputReader)
			delete m_ogInputReader;
		if(gState) delete gState;
		if(mCursor){
			OpenGUI::CursorManager::getSingleton().removeCursor(mCursor);
			delete mCursor;
		}
	}
protected:
	OpenGUIInputReader* m_ogInputReader;
	virtual void createFrameListener(void)
	{
		m_ogInputReader = new OpenGUIInputReader(ogSystem, mWindow);
	}

	virtual void createScene(void)
	{
		OpenGUI::XMLParser::LoadFromFile("DemoO.xml");
		ogSystem->setGUISheet( ogSystem->getGUISheetByName("root") );
		
		gState->setNextState( new LogoState );
		gState->runStates();
		OpenGUI::CursorManager::getSingleton().addCursor(mCursor, "DefaultCursor");
		mCursor->setImagery("Cursor", OpenGUI::FVector2(0,0));
	}
};

int main( void )
{
	OgreDemoApp demoApp;
	demoApp.go();

	return 0;
}

#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){return main();}
#endif
