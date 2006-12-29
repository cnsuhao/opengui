// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

// Renderer_Ogre.cpp : Defines the entry point for the DLL application.
//


//#include "Renderer_Ogre_PreRequisites.h"
#include "Renderer_Ogre.h" //this just ensures that all headers are working correctly for client apps

#if OGR_OGRE_PLATFORM == OGR_OGRE_PLATFORM_WIN32

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

