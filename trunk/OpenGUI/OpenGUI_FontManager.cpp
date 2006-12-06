#include "ft2build.h"
#include FT_FREETYPE_H
//////////////////////////////////////////////////////////////////////////
#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_LogSystem.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_TextureData.h"
#include "OpenGUI_FontManager.h"
#include "OpenGUI_Font.h"
#include "OpenGUI_FontSet.h"
#include "OpenGUI_FontCache.h"
#include "OpenGUI_System.h"
#include "OpenGUI_ResourceProvider.h"
#include "OpenGUI_Resource.h"
#include "OpenGUI_XMLParser.h"

#include "OpenGUI_CONFIG.h"

OpenGUI::TextureData gTexData;

namespace OpenGUI {


	//############################################################################
	template<> FontManager* Singleton<FontManager>::mptr_Singleton = 0;
	//############################################################################
	FontManager& FontManager::getSingleton( void ) {
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	FontManager* FontManager::getSingletonPtr( void ) {
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	//############################################################################
	FontManager::FontManager() {
		LogManager::SlogMsg( "INIT", OGLL_INFO2 ) << "Creating FontManager..." << Log::endlog;
		XMLParser::getSingleton().RegisterLoadHandler( "Font", &FontManager::_Font_XMLNode_Load );
		XMLParser::getSingleton().RegisterUnloadHandler( "Font", &FontManager::_Font_XMLNode_Unload );

		mFTLibrary = 0;

		LogManager::SlogMsg( "FontManager", OGLL_VERB ) << "Initializing FreeType 2..." << Log::endlog;
		FT_Library* library = new FT_Library;
		FT_Error error = FT_Init_FreeType( library );
		if ( error ) {
			LogManager::SlogMsg( "FontManager", OGLL_ERR )
			<< "Error Initializing FreeType 2: Code " << (( int )error )
			<< Log::endlog;
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "FreeType 2 failed to initialize, cannot continue.", "FontManager" );
		}
		mFTLibrary = ( void* ) library;

		mFontCache = new FontCache;

	}
	//############################################################################
	FontManager::~FontManager() {
		LogManager::SlogMsg( "SHUTDOWN", OGLL_INFO2 ) << "Destroying FontManager..." << Log::endlog;

		//free all registered FontSets
		mDefaultFont = Font();
		mFontSetMap.clear();

		//destroy the font cache
		if ( mFontCache )
			delete mFontCache;

		//shutdown freetype
		FT_Library* library = ( FT_Library* ) mFTLibrary;
		mFTLibrary = 0;
		FT_Error error = FT_Done_FreeType( *library );
		if ( error ) {
			LogManager::SlogMsg( "FontManager", OGLL_ERR )
			<< "Error Shutting Down FreeType 2: (" << (( int )error ) << ") "
			<< _GetFTErrorString( error )
			<< Log::endlog;
		}
		delete library;

		XMLParser::getSingleton().UnregisterLoadHandler( "Font", &FontManager::_Font_XMLNode_Load );
		XMLParser::getSingleton().UnregisterUnloadHandler( "Font", &FontManager::_Font_XMLNode_Unload );
	}
	//############################################################################
	std::string FontManager::_GetFTErrorString( int errorCode ) {
#undef __FTERRORS_H__
#define FT_ERRORDEF( e, v, s )  { e, s },
#define FT_ERROR_START_LIST     {
#define FT_ERROR_END_LIST       { 0, 0 } };

		const struct {
			int          err_code;
			const char*  err_msg;
		}
		ft_errors[] =
#include FT_ERRORS_H
			for ( int i = 0; ft_errors[i].err_msg != 0; i++ ) {
				if ( ft_errors[i].err_code == errorCode )
					return ft_errors[i].err_msg;
			}
			return "*UNKNOWN ERROR*";
	}
	//############################################################################
	FontSetPtr FontManager::RegisterFontSet( std::string filename, std::string fontName ) {
		LogManager::SlogMsg( "FontManager", OGLL_INFO )
		<< "RegisterFontSet:"
		<< " Name: " << fontName
		<< " Source: " << filename
		<< Log::endlog;

		FontSet* retval = 0;

		try {
			retval = new FontSet( filename, fontName );
		} catch ( Exception e ) {
			return 0;
		}
		FontSetPtr retvalPtr = retval;

		//now that we know the new font was successfully created, we should unregister any duplicates
		FontSetPtrMap::iterator iter = mFontSetMap.find( fontName );
		if ( iter != mFontSetMap.end() )
			UnRegisterFontSet( fontName );

		mFontSetMap[fontName] = retvalPtr;

		if ( mDefaultFont.isBound() ) {
			LogManager::SlogMsg( "FontManager", OGLL_INFO2 ) << "Auto setting default font..." << Log::endlog;
			SetDefaultFont( Font( fontName, 12 ) );
		}

		return retvalPtr;
	}
	//############################################################################
	void FontManager::SetDefaultFont( Font font ) {
		LogManager::SlogMsg( "FontManager", OGLL_INFO ) << "Setting Default Font..." << Log::endlog;
		font.bind();
		LogManager::SlogMsg( "FontManager", OGLL_INFO ) << "Set Default Font: "
		<< font.getName() << " @" << font.getSize() << "pt" << Log::endlog;
		mDefaultFont = font;
	}
	//############################################################################
	void FontManager::UnRegisterFontSet( FontSetPtr fontSet ) {
		if ( fontSet.isNull() ) return;
		for ( FontSetPtrMap::iterator iter = mFontSetMap.begin();
				iter != mFontSetMap.end(); iter++ ) {
			if ( iter->second == fontSet ) {
				UnRegisterFontSet( iter->first );
				return;
			}
		}
		LogManager::SlogMsg( "FontManager", OGLL_INFO2 ) << "UnRegister FontSet by FontSetPtr '"
		<< fontSet->getName() << "'->'" << fontSet->getFilename() << "' ITEM NOT FOUND!" << Log::endlog;
	}
	//############################################################################
	void FontManager::UnRegisterFontSet( const std::string& fontName ) {
		LogManager::SlogMsg( "FontManager", OGLL_INFO2 ) << "UnRegister FontSet: '"
		<< fontName << "'..." << Log::endlog;

		FontSetPtrMap::iterator iter = mFontSetMap.find( fontName );
		if ( iter != mFontSetMap.end() ) {
			mFontSetMap.erase( iter );
			return;
		}
		LogManager::SlogMsg( "FontManager", OGLL_INFO2 ) << "UnRegister FontSet: '"
		<< fontName << "' ITEM NOT FOUND!" << Log::endlog;
	}
	//############################################################################
	FontSetPtr FontManager::GetFontSet( const std::string& fontName ) {
		FontSetPtrMap::iterator iter = mFontSetMap.find( fontName );
		if ( iter != mFontSetMap.end() ) {
			return iter->second;
		}
		return 0;
	}
	//############################################################################
	Font FontManager::GetDefaultFont() {
		return mDefaultFont;
	}
	//############################################################################
	FontManager::FontList FontManager::getFontList() {
		FontList retval;
		for ( FontSetPtrMap::iterator iter = mFontSetMap.begin(); iter != mFontSetMap.end(); iter++ ) {
			retval.push_back( iter->first );
		}
		retval.sort();
		return retval;
	}
	//############################################################################
	/*! This is a debugging tool, so you can retrieve and display font atlases in their raw form.
	The validity of the returned list is very short, and it can easily become invalidated by calls
	to render new font glyphs or by the loading and unloading of FontSets. The best course of action
	is to use the obtained information immediately, and re-request it each time you need it (especially
	between frames) as its contents could have changed.
	\note This function is by no means fast, as it is not optimized for production use. */
	ImageryPtrList FontManager::_getFontAtlases() {
		ImageryPtrList retval;
		mFontCache->FillImageryPtrList( retval );
		return retval;
	}
	//############################################################################
	bool FontManager::_Font_XMLNode_Load( const XMLNode& node, const std::string& nodePath ) {
		FontManager& manager = FontManager::getSingleton();
		// we only handle these tags within <OpenGUI>
		if ( nodePath != "/OpenGUI/" )
			return false;

		const std::string name = node.getAttribute( "Name" );
		const std::string file = node.getAttribute( "File" );
		manager.RegisterFontSet( file, name );
		return true;
	}
	//############################################################################
	bool FontManager::_Font_XMLNode_Unload( const XMLNode& node, const std::string& nodePath ) {
		FontManager& manager = FontManager::getSingleton();
		// we only handle these tags within <OpenGUI>
		if ( nodePath != "/OpenGUI/" )
			return false;

		const std::string name = node.getAttribute( "Name" );
		const std::string file = node.getAttribute( "File" );
		manager.UnRegisterFontSet( name );
		return true;
	}
	//############################################################################
}//namespace OpenGUI{



