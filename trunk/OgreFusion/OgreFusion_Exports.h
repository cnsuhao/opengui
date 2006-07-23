// -----------------------------------------------------------------------------
// OgreFusion_Exports.h
// -----------------------------------------------------------------------------

#ifndef	_H_OGREFUSION_EXPORTS
#define _H_OGREFUSION_EXPORTS

#include "OgreFusion_PreRequisites.h"

#if OPENGUI_COMPILER == OPENGUI_COMPILER_MSVC

#   ifdef OGREFUSION_EXPORTS
#       define OGREFUSION_API __declspec(dllexport)
#   else
#       define OGREFUSION_API __declspec(dllimport)
#   endif

#else

#   define OPENGUI_API

#endif


#endif // _H_OGREFUSION_EXPORTS
