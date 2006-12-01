// -----------------------------------------------------------------------------
// Renderer_Ogre_PreRequisites.h
// -----------------------------------------------------------------------------

#ifndef	_H_OGR_OGRE_PREREQUISITES
#define _H_OGR_OGRE_PREREQUISITES

#include "Renderer_Ogre_Platform.h"

#if OGR_OGRE_PLATFORM == OGR_OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#endif // _H_OGR_OGRE_PREREQUISITES
