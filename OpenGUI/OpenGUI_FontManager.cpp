
#include "ft2build.h"
#include FT_FREETYPE_H
#include "OpenGUI_FontManager.h"
#include "OpenGUI_LogSystem.h"

namespace OpenGUI{
	//############################################################################
	template<> FontManager* Singleton<FontManager>::mptr_Singleton = 0;
	//############################################################################
	FontManager& FontManager::getSingleton(void)
	{
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	FontManager* FontManager::getSingletonPtr(void)
	{
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	//############################################################################
	FontManager::FontManager()
	{
		LogManager::SlogMsg("INIT", OGLL_INFO2) << "Creating FontManager" << Log::endlog;
		FT_Library library;
		FT_Init_FreeType(&library);
		
	}
	//############################################################################
	FontManager::~FontManager()
	{
		LogManager::SlogMsg("SHUTDOWN", OGLL_INFO2) << "Destroying FontManager" << Log::endlog;
	}
	//############################################################################

}//namespace OpenGUI{
