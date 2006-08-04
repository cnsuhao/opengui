
#include <Windows.h>
#include "OgreRefApp.h"

class OpenGUIInputReader : Ogre::FrameListener
{
public:
	OpenGUIInputReader(OpenGUI::System* system, Ogre::RenderWindow* window)
	{
		mSystem = system;
		Ogre::Root::getSingleton().addFrameListener(this);
		mInputDevice = Ogre::PlatformManager::getSingleton().createInputReader();
		mInputDevice->initialise(window,true, true);
	}
	virtual ~OpenGUIInputReader()
	{
		Ogre::Root::getSingleton().removeFrameListener(this);
		Ogre::PlatformManager::getSingleton().destroyInputReader( mInputDevice );
	}

	virtual bool frameStarted (const FrameEvent &evt)
	{
		mInputDevice->capture();
		if( mInputDevice->isKeyDown( KC_ESCAPE) )            
			return false;
		return true;
	}
	
	//virtual bool frameEnded(const FrameEvent &evt){return true;}
protected:
	OpenGUI::System* mSystem;
	Ogre::InputReader* mInputDevice;
};

class OgreDemoApp : public OgreRefApp
{
public:
	OgreDemoApp()
	{
		m_ogInputReader = 0;
	}
	virtual ~OgreDemoApp()
	{
		if(m_ogInputReader)
			delete m_ogInputReader;
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
