#include "tinyxml.h"
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
#include "OpenGUI_ResourceProvider.h"
#include "OpenGUI_Resource.h"

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

		//destroy all loaded Fonts
		//DestroyAllFonts();

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

		if ( mDefaultFont.isNull() ) {
			SetDefaultFont( Font( fontName, 12 ) );
		}

		return retvalPtr;
	}
	//############################################################################
	void FontManager::SetDefaultFont( Font font ) {
		if ( font.isNull() ) {
			LogManager::SlogMsg( "FontManager", OGLL_INFO ) << "Releasing Default Font"
			<< Log::endlog;
		} else {
			LogManager::SlogMsg( "FontManager", OGLL_INFO ) << "Set Default Font: "
			<< font.getName() << " @" << font.getSize() << "pt" << Log::endlog;
		}
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
	FontManager::FontList FontManager::getFontList() {
		FontList retval;
		for ( FontSetPtrMap::iterator iter = mFontSetMap.begin(); iter != mFontSetMap.end(); iter++ ) {
			retval.push_back( iter->first );
		}
		retval.sort();
		return retval;
	}
	//############################################################################
	/*void FontManager::LoadFontsFromXML( std::string xmlFilename ) {
		LogManager::SlogMsg( "FontManager", OGLL_INFO ) << "LoadFontsFromXML: " << xmlFilename << Log::endlog;

		TiXmlDocument doc;
		//doc.LoadFile(xmlFilename);
		Resource_CStr res;
		ResourceProvider* resProvider = System::getSingleton()._getResourceProvider();
		resProvider->loadResource( xmlFilename, res );
		doc.Parse( res.getString() );
		TiXmlElement* root = doc.RootElement();
		TiXmlElement* section;
		section = root;
		if ( section ) {
			do {
				//iterate through all of the root level elements and react to every "Imageset" found
				if ( 0 == strcmpi( section->Value(), "font" ) ) {
					FontManager::_loadFontFromTinyXMLElement( section );
				}
			} while (( section = section->NextSiblingElement() ) );
		}
	}
	//############################################################################
	Font* FontManager::_loadFontFromTinyXMLElement( void* tXelementPtr ) {
		TiXmlElement* tXelement = ( TiXmlElement* )tXelementPtr;
		Font* resultFont = 0;
		std::string fontFilename = "";
		std::string fontName = "";
		const char* fontAutoscale = 0;
		const char* fontXRes = 0;
		const char* fontYRes = 0;

		TiXmlAttribute* attrib = tXelement->FirstAttribute();
		if ( attrib ) {
			do {
				if ( 0 == strcmpi( attrib->Name(), "name" ) )
					fontName = attrib->Value();

				if ( 0 == strcmpi( attrib->Name(), "file" ) )
					fontFilename = attrib->Value();

				if ( 0 == strcmpi( attrib->Name(), "autoscale" ) )
					fontAutoscale = attrib->Value();

				if ( 0 == strcmpi( attrib->Name(), "xres" ) )
					fontXRes = attrib->Value();

				if ( 0 == strcmpi( attrib->Name(), "yres" ) )
					fontYRes = attrib->Value();

			} while (( attrib = attrib->Next() ) );
		}

		bool autoscale = false;
		unsigned int xres = 800;
		unsigned int yres = 600;

		if ( fontAutoscale ) {
			if ( 0 == strcmpi( fontAutoscale, "true" ) || 0 == strcmpi( fontAutoscale, "1" ) )
				autoscale = true;
		}
		if ( fontXRes ) {
			std::stringstream ss;
			std::string tmp = fontXRes;
			ss.str( tmp );
			ss >> xres;
		}
		if ( fontYRes ) {
			std::stringstream ss;
			std::string tmp = fontYRes;
			ss.str( tmp );
			ss >> yres;
		}

		if ( fontFilename != "" && fontName != "" ) {
			resultFont = FontManager::CreateFont( fontFilename, fontName, autoscale, xres, yres );
		} else {
			if ( fontFilename == "" ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS,
						  "<Font> XML Element missing required attribute 'file'",
						  "FontManager::_loadFontFromTinyXMLElement" );
			}
			if ( fontName == "" ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS,
						  "<Font> XML Element missing required attribute 'name'",
						  "FontManager::_loadFontFromTinyXMLElement" );
			}
		}

		return resultFont;
	}*/
	//############################################################################
}//namespace OpenGUI{



