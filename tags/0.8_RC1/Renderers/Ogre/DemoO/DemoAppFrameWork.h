#ifndef D99F07AC_F0B7_4434_978D_CEF7D16D46DE
#define D99F07AC_F0B7_4434_978D_CEF7D16D46DE

#include "OpenGUI.h"

namespace Ogre{
class RenderWindow; //forward declaration
class Camera; //forward declaration
}

class DemoApp {
public:
	DemoApp( std::string windowTitle );
	virtual ~DemoApp();
	void run();
	void getWindowSize( int& width, int& height );

	void _perframeRun();
	void _mousePositionCallback( int x, int y );
	void _mouseButtonCallback( int button, int action );

	bool isReady(){
		return mConfigured;
	}
protected:
	OpenGUI::System* mSystem;
	OpenGUI::Renderer* mRenderer;
	bool mConfigured;

	Ogre::RenderWindow* getWindow();
	Ogre::Camera* getCamera();

	//Application specific virtual functions
	virtual void preRun() {}
	virtual void perframeRun() {}
	virtual void postframeRun() {}
	virtual void postRun() {}
	//Override this to alter normal window close querying, default always allows close
	virtual bool queryCloseWindow() {
		return true;
	}
	virtual void windowSizeChanged( int width, int height );
	virtual void windowRefresh() {}
	virtual void charCallback( int character, int action ) {}
	virtual void keyCallback( int key, int action ) {}

	virtual void mousePositionCallback( int x, int y ) {}
	virtual void mouseButtonCallback( int button, int action ) {}
	virtual void mouseWheelCallback( int pos ) {}

private:
	

	int m_WndWidth;
	int m_WndHeight;

	//Singleton specific code
protected:
	static DemoApp* mptr_Singleton;
public:
	static DemoApp* getSingletonPtr();
	static DemoApp& getSingleton();

};

#endif

