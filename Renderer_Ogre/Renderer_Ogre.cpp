// OgreFusion.cpp : Defines the entry point for the DLL application.
//


//#include "OgreFusion_PreRequisites.h"
#include "OgreFusion.h" //this just ensures that all headers are working correctly for client apps

#if OGREFUSION_PLATFORM == OGREFUSION_PLATFORM_WIN32

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

