// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_Platform.h"

#if OPENGUI_COMPILER == OPENGUI_COMPILER_MSVC

#   ifdef OPENGUI_EXPORTS
#       define OPENGUI_API __declspec(dllexport)
#   else
#       define OPENGUI_API __declspec(dllimport)
#   endif

#   ifdef OPENGUI_WIDGET_EXPORTS
#       define OPENGUI_WIDGET_API __declspec(dllexport)
#   else
#       define OPENGUI_WIDGET_API __declspec(dllimport)
#   endif

#else

#   define OPENGUI_API
#   define OPENGUI_WIDGET_API

#endif

