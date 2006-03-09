
#include "OpenGUI_Platform.h"

#if OPENGUI_COMPILER == OPENGUI_COMPILER_MSVC

#   ifdef OPENGUI_EXPORTS
#       define OPENGUI_API __declspec(dllexport)
#   else
#       define OPENGUI_API __declspec(dllimport)
#   endif

#else

#   define OPENGUI_API

#endif

