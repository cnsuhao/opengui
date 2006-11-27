#ifndef E6185E16_E45B_4f38_AAAA_1FBB6E914D78
#define E6185E16_E45B_4f38_AAAA_1FBB6E914D78

#include "OpenGUI.h"
#include "GL/glfw.h"
#include "Renderer_OpenGL.h"

class DemoApp {
public:
	DemoApp( std::string windowTitle ){
		//singleton stuff
		assert( !mptr_Singleton );
		mptr_Singleton = ( this );

		mSystem = 0;
		mRenderer = 0;

		glfwInit();
		if ( !glfwOpenWindow( 800, 600, 0, 0, 0, 0, 0, 0, GLFW_WINDOW ) ) {
			glfwTerminate();
			OG_THROW( OpenGUI::Exception::ERR_INTERNAL_ERROR, "", "DemoApp::DemoApp" );
			exit( -1 );
		}
		glfwSetWindowTitle( windowTitle.c_str() );
		glfwSetWindowCloseCallback( &DemoApp::_queryCloseWindow );
		glfwSetWindowRefreshCallback( &DemoApp::_windowRefresh );
		glfwSetWindowSizeCallback( &DemoApp::_windowSizeChanged );
		glfwSetCharCallback( &DemoApp::_charCallback );
		glfwSetKeyCallback( &DemoApp::_keyCallback );
		glfwSetMousePosCallback( &DemoApp::_mousePosCallback );
		glfwSetMouseButtonCallback( &DemoApp::_mouseBtnCallback );
		glfwSetMouseWheelCallback( &DemoApp::_mouseWhlCallback );

		int w, h;
		glfwGetWindowSize( &w, &h );
		m_WndWidth = w;
		m_WndHeight = h;
		mRenderer = new OpenGUI::Renderer_OpenGL( w, h );
		mSystem = new OpenGUI::System( mRenderer );

	}
	virtual ~DemoApp(){
		assert( mptr_Singleton );
		mptr_Singleton = 0;

		delete mSystem;
		delete mRenderer;
		glfwTerminate();
	}
	void run(){
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
	}
	void getWindowSize( int& width, int& height ) {
		width = m_WndWidth;
		height = m_WndHeight;
	}

protected:
	OpenGUI::System* mSystem;
	OpenGUI::Renderer* mRenderer;

	//Application specific virtual functions
	virtual void preRun() {}
	virtual void perframeRun() {}
	virtual void postframeRun() {}
	virtual void postRun() {}
	//Override this to alter normal window close querying, default always allows close
	virtual bool queryCloseWindow() {
		return true;
	}
	virtual void windowSizeChanged( int width, int height ){
		glViewport( 0, 0, width, height );
		if ( mRenderer ) {
			static_cast<OpenGUI::Renderer_OpenGL*>( mRenderer )->setDim( width, height );
		}
	}
	virtual void windowRefresh() {}
	virtual void charCallback( int character, int action ) {}
	virtual void keyCallback( int key, int action ) {}

	virtual void mousePositionCallback( int x, int y ) {}
	virtual void mouseButtonCallback( int button, int action ) {}
	virtual void mouseWheelCallback( int pos ) {}

private:
	//Connectors to GLFW
	static int GLFWCALL _queryCloseWindow() {
		return getSingletonPtr()->queryCloseWindow() ? GL_TRUE : GL_FALSE;
	}
	static void GLFWCALL _windowSizeChanged( int w, int h ) {
		getSingletonPtr()->m_WndWidth = w;
		getSingletonPtr()->m_WndHeight = h;
		getSingletonPtr()->windowSizeChanged( w, h );
	}
	static void GLFWCALL _windowRefresh() {
		getSingletonPtr()->windowRefresh();
	}
	static void GLFWCALL _charCallback( int c, int a ) {
		getSingletonPtr()->charCallback( c, a );
	}
	static void GLFWCALL _keyCallback( int k, int a ) {
		getSingletonPtr()->keyCallback( k, a );
	}
	static void GLFWCALL _mousePosCallback( int x, int y ) {
		getSingletonPtr()->mousePositionCallback( x, y );
	}
	static void GLFWCALL _mouseBtnCallback( int b, int a ) {
		getSingletonPtr()->mouseButtonCallback( b, a );
	}
	static void GLFWCALL _mouseWhlCallback( int p ) {
		getSingletonPtr()->mouseWheelCallback( p );
	}

	int m_WndWidth;
	int m_WndHeight;

	//Singleton specific code
protected:
	static DemoApp* mptr_Singleton;
public:
	static DemoApp* getSingletonPtr(){
		assert( mptr_Singleton );
		return mptr_Singleton;
	}
	static DemoApp& getSingleton(){
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
};
DemoApp* DemoApp::mptr_Singleton = 0;

#ifdef WIN32
int main( void );
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	return main();
}
#endif

#endif

