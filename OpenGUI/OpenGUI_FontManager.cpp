
#include "ft2build.h"
#include FT_FREETYPE_H


#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_LogSystem.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_TextureData.h"
#include "OpenGUI_FontManager.h"
#include "OpenGUI_Font.h"
#include "OpenGUI_FontCache.h"
#include "OpenGUI_System.h"

#include "OpenGUI_CONFIG.h"

OpenGUI::TextureData gTexData;

namespace OpenGUI{
	Texture* FontManager::getDebugTexture()
	{
		return mFontCache->getDebugTexture();
	}
	void FontManager::DebugTest()
	{
		//mFontCache->GetGlyphImagery()
	}

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
		LogManager::SlogMsg("INIT", OGLL_INFO2) << "Creating FontManager..." << Log::endlog;
		
		mFTLibrary = 0;
		mDefaultFontName = "";
		mDefaultFontSize = 12;

		LogManager::SlogMsg("FontManager", OGLL_VERB) << "Initializing FreeType 2..." << Log::endlog;
		FT_Library* library = new FT_Library;
		FT_Error error = FT_Init_FreeType(library);
		if(error){
			LogManager::SlogMsg("FontManager", OGLL_ERR) 
				<< "Error Initializing FreeType 2: Code " << ((int)error) 
				<< Log::endlog;
			OG_THROW(Exception::ERR_INTERNAL_ERROR, "FreeType 2 failed to initialize, cannot continue.","FontManager");
		}
		mFTLibrary = (void*) library;

		mFontCache = new FontCache;

	}
	//############################################################################
	FontManager::~FontManager()
	{
		LogManager::SlogMsg("SHUTDOWN", OGLL_INFO2) << "Destroying FontManager..." << Log::endlog;
		
		//destroy all loaded Fonts
		DestroyAllFonts();

		//destroy the font cache
		if(mFontCache)
			delete mFontCache;

		//shutdown freetype
		FT_Library* library = (FT_Library*) mFTLibrary;
		mFTLibrary = 0;
		FT_Error error = FT_Done_FreeType(*library);
		if(error){
			LogManager::SlogMsg("FontManager", OGLL_ERR) 
				<< "Error Shutting Down FreeType 2: (" << ((int)error) << ") "
				<< _GetFTErrorString(error)
				<< Log::endlog;
		}
		delete library;
	}
	//############################################################################
	std::string FontManager::_GetFTErrorString(int errorCode)
	{                                                              
		#undef __FTERRORS_H__
		#define FT_ERRORDEF( e, v, s )  { e, s },
		#define FT_ERROR_START_LIST     {
		#define FT_ERROR_END_LIST       { 0, 0 } };

		const struct
		{
			int          err_code;
			const char*  err_msg;
		} ft_errors[] =
		#include FT_ERRORS_H
		for(int i=0; ft_errors[i].err_msg!=0; i++){
			if(ft_errors[i].err_code == errorCode)
				return ft_errors[i].err_msg;
		}
		return "*UNKNOWN ERROR*";
	}
	//############################################################################
	Font* FontManager::CreateFont(std::string filename, std::string fontName, bool autoscale, unsigned int xres, unsigned int yres)
	{
		LogManager::SlogMsg("FontManager", OGLL_INFO) << "CreateFont:"
			<< " Name: " << fontName
			<< " Source: " << filename
			<< Log::endlog;

		Font* retval = 0;
		
		try{
			retval = new Font(filename, xres, yres, autoscale);
		}catch(Exception e){
			return 0;
		}
		bool makeThisDefaultFont = false;

		//now that we know the new font was successfully created, we should test for and remove any duplicate
		if( GetFont(fontName) ){
			if( mDefaultFontName == fontName) makeThisDefaultFont = true;
			DestroyFont(fontName);
		}

		mFontMap[fontName] = retval;
		if(mDefaultFontName == "" || makeThisDefaultFont ){
			SetDefaultFont(fontName, 12);
		}

		return retval;
	}
	//############################################################################
	void FontManager::SetDefaultFont(std::string fontName, unsigned int fontSize)
	{
		LogManager::SlogMsg("FontManager", OGLL_INFO) << "Set Default Font: "
			<< fontName << " @" << fontSize << "pt" << Log::endlog;
		mDefaultFontName = fontName;
		mDefaultFontSize = fontSize;
	}
	//############################################################################
	void FontManager::DestroyFont(std::string fontName)
	{
		LogManager::SlogMsg("FontManager", OGLL_INFO2) << "Destroying Font: '" << fontName << "'..." << Log::endlog;

		FontCPtrMap::iterator iter = mFontMap.find(fontName);
		if(iter != mFontMap.end()){
			Font* curFont = iter->second;
			if(curFont)
				delete curFont;
			mFontMap.erase( iter );

			if(mDefaultFontName == fontName){ //gracefully handle deletion of default font
				LogManager::SlogMsg("FontManager", OGLL_VERB) << "Destroying Default Font: '" << fontName << "' ";
				mDefaultFontName = "";
				FontCPtrMap::iterator tmpIter = mFontMap.begin();
				if(tmpIter != mFontMap.end()){
					mDefaultFontName = tmpIter->first;
					LogManager::SlogMsg("FontManager", OGLL_VERB) << " replacement found! ("
						<< mDefaultFontName << ")" << Log::endlog;
				}else{
					LogManager::SlogMsg("FontManager", OGLL_VERB) << " ...no suitable replacement found!" << Log::endlog;
				}
			}
			return;
		}
	}
	//############################################################################
	void FontManager::DestroyAllFonts()
	{
		LogManager::SlogMsg("FontManager", OGLL_INFO2) << "Destroying All Fonts..." << Log::endlog;

		FontCPtrMap::iterator iter = mFontMap.begin();
		while(iter != mFontMap.end()){
			Font* curFont = iter->second;
			if(curFont)
				delete curFont;
			iter++;
		}
		mFontMap.clear();
	}
	//############################################################################
	Font* FontManager::GetFont(std::string name)
	{
		//
		FontCPtrMap::iterator iter = mFontMap.find(name);
		if(iter != mFontMap.end()){
			return iter->second;
		}
		return 0;
	}
	//############################################################################
	void FontManager::getGlyph(IRect& outPixelRect, FontGlyph& outFontGlyph,
		char glyph_charCode, const std::string& fontName, unsigned int pointSize)
	{
		Font* fntPtr = 0;
		if(fontName != "")
			fntPtr = GetFont(fontName);
		if(!fntPtr)
			fntPtr = GetFont(mDefaultFontName);

		if(!fntPtr){
			OG_THROW(Exception::ERR_ITEM_NOT_FOUND,
				"Could not find requested font '" + fontName 
				+ "' and no default font was available as substitute",
				"FontManager::getGlyph");
			return;
		}

		if(pointSize == 0){
			pointSize = mDefaultFontSize;
			if(pointSize == 0){
				OG_THROW(Exception::ERR_ITEM_NOT_FOUND,
					"Invalid pointSize given (0), and no default font size was set",
					"FontManager::getGlyph");
			}
		}

		if( ! fntPtr->getGlyph(glyph_charCode, pointSize, outPixelRect, outFontGlyph) ){
			OG_THROW(Exception::ERR_INTERNAL_ERROR,
				"An internal error prevented proper ",
				"FontManager::getGlyph");
		}
	}
	//############################################################################
	unsigned int FontManager::getLineSpacing(const std::string& fontName, unsigned int pointSize)
	{
		Font* fntPtr = 0;
		if(fontName != "")
			fntPtr = GetFont(fontName);
		if(!fntPtr)
			fntPtr = GetFont(mDefaultFontName);

		if(!fntPtr){
			OG_THROW(Exception::ERR_ITEM_NOT_FOUND,
				"Could not find requested font '" + fontName 
				+ "' and no default font was available as substitute",
				"FontManager::getLineSpacing");
			return 0;
		}

		if(pointSize == 0){
			pointSize = mDefaultFontSize;
			if(pointSize == 0){
				OG_THROW(Exception::ERR_ITEM_NOT_FOUND,
					"Invalid pointSize given (0), and no default font size was set",
					"FontManager::getLineSpacing");
			}
		}
		return fntPtr->getLineSpacing(pointSize);
	}
	//############################################################################

}//namespace OpenGUI{



