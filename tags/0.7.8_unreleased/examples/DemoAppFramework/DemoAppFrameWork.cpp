


#include "DemoAppFrameWork.h"
#include "../../OpenGUI_OGLRenderer/OpenGUI_OGLRenderer.h"

#ifdef WIN32
int main( void );
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){return main();}
#endif

DemoApp* DemoApp::mptr_Singleton = 0;
DemoApp* DemoApp::getSingletonPtr()
{
	assert( mptr_Singleton );
	return mptr_Singleton;
}
DemoApp& DemoApp::getSingleton()
{
	assert( mptr_Singleton );
	return ( *mptr_Singleton );
}

DemoApp::DemoApp(std::string windowTitle)
{
	//singleton stuff
	assert( !mptr_Singleton );
	mptr_Singleton = (this);

	mSystem = 0;
	mRenderer = 0;

	glfwInit();
	if( !glfwOpenWindow( 800,600, 0,0,0,0,0,0, GLFW_WINDOW ) ){
		glfwTerminate();
		OG_THROW(OpenGUI::Exception::ERR_INTERNAL_ERROR, "", "DemoApp::DemoApp");
		exit(-1);
	}
	glfwSetWindowTitle(windowTitle.c_str());
	glfwSetWindowCloseCallback( &DemoApp::_queryCloseWindow );
	glfwSetWindowRefreshCallback( &DemoApp::_windowRefresh );
	glfwSetWindowSizeCallback( &DemoApp::_windowSizeChanged );
	glfwSetCharCallback( &DemoApp::_charCallback );
	glfwSetKeyCallback( &DemoApp::_keyCallback );
	glfwSetMousePosCallback( &DemoApp::_mousePosCallback );
	glfwSetMouseButtonCallback( &DemoApp::_mouseBtnCallback );
	glfwSetMouseWheelCallback( &DemoApp::_mouseWhlCallback );

	mRenderer = new OpenGUI::OGLRenderer();
	
	int w,h;
	glfwGetWindowSize(&w, &h);
	DemoApp::windowSizeChanged(w, h);
	static_cast<OpenGUI::OGLRenderer*>(mRenderer)->setScreenDim(w, h);

	mSystem = new OpenGUI::System(mRenderer);

	
}
DemoApp::~DemoApp()
{
	assert( mptr_Singleton );
	mptr_Singleton = 0;

	delete mSystem;
	delete mRenderer;
	glfwTerminate();
}
void DemoApp::run()
{
	bool running = true;

	preRun();

	while( running )
	{
		// OpenGL rendering goes here...
		//glClearColor(1.0f,0.0f,0.0f,0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		perframeRun();

		mSystem->renderGUI();

		// Swap front and back rendering buffers
		glfwSwapBuffers();
		// Check if ESC key was pressed or window was closed
		running = !glfwGetKey( GLFW_KEY_ESC ) &&
			glfwGetWindowParam( GLFW_OPENED );
	}

	postRun();
}

void DemoApp::windowSizeChanged(int width, int height)
{
	glViewport(0,0,width,height);
	if(mRenderer){
		static_cast<OpenGUI::OGLRenderer*>(mRenderer)->setDim(width,height);
	}
}



