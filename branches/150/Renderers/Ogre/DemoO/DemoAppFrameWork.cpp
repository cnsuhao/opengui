// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#include "OgreRefApp.h"

#include "DemoAppFrameWork.h"
//#include "Renderer_OpenGL.h"

#ifdef WIN32
int main( void );
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	return main();
}
#endif


class OpenGUIInputReader : Ogre::FrameListener
{
public:
	OpenGUIInputReader(Ogre::RenderWindow* window)
	{
		Ogre::Root::getSingleton().addFrameListener(this);
		mInputDevice = Ogre::PlatformManager::getSingleton().createInputReader();
		mInputDevice->initialise(window,true, true);
		//whatever the default scale is, it need to be double that!
		mInputDevice->setMouseScale( mInputDevice->getMouseScale() * 2.0f );
		mButtonWasDown = false;
		mMousePos.x = window->getWidth() / 2;
		mMousePos.y = window->getHeight() / 2;
		mWindow = window;
	}
	virtual ~OpenGUIInputReader()
	{
		Ogre::Root::getSingleton().removeFrameListener(this);
		Ogre::PlatformManager::getSingleton().destroyInputReader( mInputDevice );
	}


	virtual bool frameStarted (const FrameEvent &evt)
	{
		mInputDevice->capture();

		if( mInputDevice->isKeyDown( KC_ESCAPE ) ){
			return false;
		}

		long mx = mInputDevice->getMouseRelativeX();
		long my = mInputDevice->getMouseRelativeY();
		mMousePos.x += mx;
		mMousePos.y += my;
		if(mMousePos.x < 0) mMousePos.x = 0;
		if(mMousePos.y < 0) mMousePos.y = 0;
		if(mMousePos.x > (int)mWindow->getWidth()) mMousePos.x = mWindow->getWidth();
		if(mMousePos.y > (int)mWindow->getHeight()) mMousePos.y = mWindow->getHeight();

		DemoApp::getSingleton()._mousePositionCallback(mMousePos.x, mMousePos.y);

		bool curBtnState;
		curBtnState = mInputDevice->getMouseButton( 0 );
		if( curBtnState != mButtonWasDown ){
 			mButtonWasDown = curBtnState;
			if(curBtnState){
				DemoApp::getSingleton()._mouseButtonCallback(0,1);
			}else{
				DemoApp::getSingleton()._mouseButtonCallback(0,0);
			}
		}

		DemoApp::getSingleton()._perframeRun();

		return true;
	}

protected:
	OpenGUI::IVector2 mMousePos;
	Ogre::InputReader* mInputDevice;
	bool mButtonWasDown;
	Ogre::RenderWindow* mWindow;
};



OpenGUIInputReader* mptr_InputReader = 0;
OgreRefApp* mptr_OgreRefApp = 0;
DemoApp* DemoApp::mptr_Singleton = 0;
DemoApp* DemoApp::getSingletonPtr() {
	assert( mptr_Singleton );
	return mptr_Singleton;
}
DemoApp& DemoApp::getSingleton() {
	assert( mptr_Singleton );
	return ( *mptr_Singleton );
}
Ogre::RenderWindow* DemoApp::getWindow(){
	return mptr_OgreRefApp->mWindow;
}
Ogre::Camera* DemoApp::getCamera(){
	return mptr_OgreRefApp->mCamera;
}
void DemoApp::_perframeRun(){
	perframeRun();
}
void DemoApp::_mousePositionCallback( int x, int y ){
	mousePositionCallback(x,y);
}
void DemoApp::_mouseButtonCallback( int button, int action ){
	mouseButtonCallback(button,action);
}
DemoApp::DemoApp( std::string windowTitle ) {
	//singleton stuff
	assert( !mptr_Singleton );
	mptr_Singleton = ( this );

	mConfigured = false;
	mSystem = 0;
	mRenderer = 0;
	mptr_InputReader = 0;
	mptr_OgreRefApp = new OgreRefApp();
	if(mptr_OgreRefApp->setup()){
		mConfigured = true;
		mSystem = OpenGUI::System::getSingletonPtr();
		mRenderer = OpenGUI::Renderer::getSingletonPtr();
		mptr_InputReader = new OpenGUIInputReader(mptr_OgreRefApp->mWindow);
	}
}
DemoApp::~DemoApp() {
	assert( mptr_Singleton );
	mptr_Singleton = 0;

	if(mptr_InputReader)
		delete mptr_InputReader;

	if(mptr_OgreRefApp)
		delete mptr_OgreRefApp;
	mptr_OgreRefApp = 0;

	mSystem = 0;
	mRenderer = 0;
}
void DemoApp::run() {
	preRun();

	mptr_OgreRefApp->go();

	postRun();

	/*
	bool running = true;

	preRun();

	while ( running ) {
		// OpenGL rendering goes here...
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		perframeRun();

		mSystem->update();

		postframeRun();

		// Swap front and back rendering buffers
		glfwSwapBuffers();
		// Check if ESC key was pressed or window was closed
		running = !glfwGetKey( GLFW_KEY_ESC ) &&
				  glfwGetWindowParam( GLFW_OPENED );
	}

	postRun();
	*/
}

void DemoApp::windowSizeChanged( int width, int height ) {
	OG_NYI;
}
void DemoApp::getWindowSize( int& width, int& height ){
	if(mptr_OgreRefApp){
		width = mptr_OgreRefApp->mWindow->getWidth();
		height = mptr_OgreRefApp->mWindow->getHeight();
	}else{
		width = 0;
		height = 0;
	}
}



