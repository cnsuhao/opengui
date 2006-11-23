// OpenGUI.cpp : Defines the entry point for the DLL application.
//
// Since we don't really use this for anything, we'll just define it
// to do absolutely nothing.

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI.h"

#if OPENGUI_PLATFORM == OPENGUI_PLATFORM_WIN32

BOOL APIENTRY DllMain( HANDLE hModule,
					   DWORD  ul_reason_for_call,
					   LPVOID lpReserved
					 ) {
	switch ( ul_reason_for_call ) {
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

#endif


