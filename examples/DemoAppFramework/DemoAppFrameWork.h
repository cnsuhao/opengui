#ifndef E6185E16_E45B_4f38_AAAA_1FBB6E914D78
#define E6185E16_E45B_4f38_AAAA_1FBB6E914D78

#include "OpenGUI.h"
#include "GL/glfw.h"


class DemoApp{
public:
	DemoApp(std::string windowTitle);
	virtual ~DemoApp();
	void run();
protected:
	OpenGUI::System* mSystem;
	OpenGUI::Renderer* mRenderer;

	//Application specific virtual functions
	virtual void preRun(){};
	virtual void perframeRun(){};
	virtual void postRun(){};
	//Override this to alter normal window close querying, default always allows close
	virtual bool queryCloseWindow(){ return true; };
	virtual void windowSizeChanged(int width, int height);
	virtual void windowRefresh(){}
	virtual void charCallback(int character, int action){}
	virtual void keyCallback(int key, int action){}

	virtual void mousePositionCallback(int x, int y){}
	virtual void mouseButtonCallback(int button, int action){}
	virtual void mouseWheelCallback(int pos){}

private:
	//Connectors to GLFW
	static int GLFWCALL _queryCloseWindow()
		{ return getSingletonPtr()->queryCloseWindow()?GL_TRUE:GL_FALSE; }; 
	static void GLFWCALL _windowSizeChanged(int w, int h)
		{ getSingletonPtr()->windowSizeChanged(w,h); }
	static void GLFWCALL _windowRefresh()
		{ getSingletonPtr()->windowRefresh(); }
	static void GLFWCALL _charCallback(int c, int a)
		{ getSingletonPtr()->charCallback(c,a); }
	static void GLFWCALL _keyCallback(int k, int a)
		{ getSingletonPtr()->keyCallback(k,a); }
	static void GLFWCALL _mousePosCallback(int x, int y)
		{ getSingletonPtr()->mousePositionCallback(x,y); }
	static void GLFWCALL _mouseBtnCallback(int b, int a)
		{ getSingletonPtr()->mouseButtonCallback(b,a); }
	static void GLFWCALL _mouseWhlCallback(int p)
		{ getSingletonPtr()->mouseWheelCallback(p); }


	//Singleton specific code
protected:
	static DemoApp* mptr_Singleton;
public:
	static DemoApp* getSingletonPtr();
	static DemoApp& getSingleton();

};

#endif

