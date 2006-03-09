#ifndef F5ED205F_518A_42e8_86FF_D196D23C0C6A
#define F5ED205F_518A_42e8_86FF_D196D23C0C6A

#include "OpenGUI_Platform.h"

#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <map>
#include <list>
#include <cassert>


#if OPENGUI_PLATFORM == OPENGUI_PLATFORM_WIN32
    #include <time.h>
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <Mmsystem.h>
#endif

#if OPENGUI_PLATFORM == OPENGUI_PLATFORM_LINUX
    #include <dlfcn.h>
    #define strcmpi strcasecmp
#endif

#endif

