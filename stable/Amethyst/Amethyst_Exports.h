#include "OpenGUI_Platform.h"

#if OPENGUI_COMPILER == OPENGUI_COMPILER_MSVC

#   ifdef AMETHYST_EXPORTS
#       define AMETHYST_API __declspec(dllexport)
#   else
#       define AMETHYST_API __declspec(dllimport)
#   endif

#else

#   define OPENGUI_API

#endif
