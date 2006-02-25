#ifndef A281092A_998D_41f4_962D_E22EC01A9B67
#define A281092A_998D_41f4_962D_E22EC01A9B67

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library


#include <cassert>


#if defined(_WINDOWS) && defined(_MSC_VER) //thanks for the warning Bill
#   pragma warning (disable : 4311)
#   pragma warning (disable : 4312)
#   pragma warning (disable : 4661)
#endif


//Reference to author of this singleton's base:
/* "Portions Copyright (C) Scott Bilas, 2000" */

template <typename T> class Singleton
{
protected:
	static T* mptr_Singleton;
public:
	Singleton()
	{
		assert( !mptr_Singleton );
		mptr_Singleton = static_cast<T*>(this);
	}

	~Singleton()
	{
		assert( mptr_Singleton );
		mptr_Singleton = 0;
	}

	static T& getSingleton( void )
	{
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	static T* getSingletonPtr( void )
	{
		assert( mptr_Singleton );
		return mptr_Singleton;
	}
};


class OpenGLBase : public Singleton<OpenGLBase>
{
public:
	//Reimplementation required for this style of singleton implementation to work across DLLs
	static OpenGLBase& getSingleton(void);

	//Reimplementation required for this style of singleton implementation to work across DLLs
	static OpenGLBase* getSingletonPtr(void);

	OpenGLBase(void);
	~OpenGLBase(void);

	int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	
	virtual void CustomInit();
	virtual void CustomShutdown();
	virtual void CustomDrawOperations();
	HWND GetHWND() {return hWnd;}

private:
	int InitGL(GLvoid);
	GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
	GLvoid KillGLWindow(GLvoid);
	int DrawGLScene(GLvoid);
	BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag);
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT MemberWndProc(HWND, UINT, WPARAM, LPARAM);
private:
	HDC			hDC;		// Private GDI Device Context
	HGLRC		hRC;		// Permanent Rendering Context
	HWND		hWnd;		// Holds Our Window Handle
	HINSTANCE	hInstance;		// Holds The Instance Of The Application
protected:
	bool	mouseButtons[3];
	bool	keys[256];			// Array Used For The Keyboard Routine
private:
	bool	active;		// Window Active Flag Set To TRUE By Default
	bool	fullscreen;	// Fullscreen Flag Set To Fullscreen Mode By Default
};


#endif