// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#ifndef D0A9A05C_D344_4074_9BF7_9AF603749403
#define D0A9A05C_D344_4074_9BF7_9AF603749403

#include "OpenGUI_PreRequisites.h"

#if OPENGUI_PLATFORM == OPENGUI_PLATFORM_WIN32
#define DYNAMICLIB_HANDLE HMODULE
#define DYNAMICLIB_LOAD(lib) LoadLibraryW(lib.asWStr_c_str())
#define DYNAMICLIB_UNLOAD(handle) FreeLibrary(handle)
#define DYNAMICLIB_GETSYMBOL(handle,procname) GetProcAddress(handle,procname.asUTF8_c_str())

#elif OPENGUI_PLATFORM == OPENGUI_PLATFORM_LINUX
#define DYNAMICLIB_HANDLE void*
#define DYNAMICLIB_LOAD(lib) dlopen(lib.asUTF8_c_str(),RTLD_LAZY)
#define DYNAMICLIB_UNLOAD(handle) dlclose(handle)
#define DYNAMICLIB_GETSYMBOL(handle,procname) dlsym(handle,procname.asUTF8_c_str())

#endif

namespace OpenGUI {

	//! \internal An internal class used to load dynamic libraries
	class DynamicLib {
	public:
		DynamicLib( const String& filename );
		~DynamicLib();

		void load();
		void unload();

		const String& getName( void ) const {
			return mName;
		}

		void* getSymbol( const String& symbolName ) const;
	private:
		String mName;
		DYNAMICLIB_HANDLE mHandle;
	};

}
;//namespace OpenGUI{

#endif

