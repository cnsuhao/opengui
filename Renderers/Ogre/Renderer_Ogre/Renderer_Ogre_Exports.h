// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

// -----------------------------------------------------------------------------
// Renderer_Ogre_Exports.h
// -----------------------------------------------------------------------------

#ifndef	_H_OGR_OGRE_EXPORTS
#define _H_OGR_OGRE_EXPORTS

#include "Renderer_Ogre_PreRequisites.h"

#if OGR_OGRE_COMPILER == OGR_OGRE_COMPILER_MSVC

#   ifdef OGR_OGRE_EXPORTS
#       define OGR_OGRE_API __declspec(dllexport)
#   else
#       define OGR_OGRE_API __declspec(dllimport)
#   endif

#else

#   define OGR_OGRE_API

#endif


#endif // _H_OGR_OGRE_EXPORTS
