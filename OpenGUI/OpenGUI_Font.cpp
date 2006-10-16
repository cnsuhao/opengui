
#include "ft2build.h"
#include FT_FREETYPE_H

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_LogSystem.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_FontManager.h"
#include "OpenGUI_Font.h"
#include "OpenGUI_FontCache.h"
#include "OpenGUI_TextureDataRect.h"
#include "OpenGUI_System.h"
#include "OpenGUI_ResourceProvider.h"

namespace OpenGUI {
	//############################################################################
	/*! This will attempt to bind, but will fall back to delayed binding if the
	bind fails. */
	Font::Font( const std::string& fontName, float fontSize ) {
		m_Bound = false;
		m_FontName = fontName;
		m_FontSize = fontSize;
		_tryBind();
	}
	//############################################################################
	/*! This will force an immediate binding to the given FontSet at the given size.
	If the given \c fontSet is an empty pointer, the default font will be used. */
	Font::Font( FontSetPtr fontSet, float fontSize ) {
		m_Bound = false;
		m_FontSize = fontSize;
		m_FontSetPtr = fontSet;
		bind();
	}
	//############################################################################
	/*! This constructor forces delayed binding to the default Font */
	Font::Font() {
		m_Bound = false;
	}
	//############################################################################
	/*! If the Font is already bound, this function will exit immediately with no ill effect. */
	void Font::bind() {
		if ( isBound() )
			return;
		if ( !_tryBind() )
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "Failed to bind Font", __FUNCTION__ );
	}
	//############################################################################
	bool Font::_tryBind() {
		// try to bind to the FontSet by name
		if ( m_FontSetPtr.isNull() && m_FontName != "" ) {
			FontSetPtr fset = FontManager::getSingleton().GetFontSet( m_FontName );
			if ( fset.isNull() )
				return false;
			m_FontSetPtr = fset;
			m_FontName = m_FontSetPtr->getName();
		}

		// try to bind to the default FontSet
		if ( m_FontSetPtr.isNull() && m_FontName == "" ) {
			Font fnt = FontManager::getSingleton().GetDefaultFont();
			if ( !fnt.isBound() )
				return false;
			FontSetPtr fset = fnt.getFontSetPtr();
			if ( fset.isNull() )
				return false;
			m_FontSetPtr = fset;
			m_FontName = m_FontSetPtr->getName();
		}

		//if we already have a valid FontSet, then just copy the name
		if (( !m_FontSetPtr.isNull() ) && m_FontName == "" )
			m_FontName = m_FontSetPtr->getName();

		// if size is 0.0f or less and we have a valid FontSet binding, copy the default Font size
		if (( !m_FontSetPtr.isNull() ) && m_FontSize <= 0.0f ) {
			Font dFont = FontManager::getSingleton().GetDefaultFont();
			if ( !dFont.isBound() )
				return false;
			m_FontSize = dFont.m_FontSize;
		}

		//this should never happen, but we'll test anyhow
		if ( m_FontSetPtr.isNull() || m_FontSize <= 0.0f )
			return false;

		m_Bound = true;
		return true;
	}
	//############################################################################
	//////////////////////////////////////////////////////////////////////////////
	//############################################################################
	void FontSet::finalize() {
		delete this;
	}
	//############################################################################
	FontSet::FontSet( const std::string& sourceFilename, const std::string& fontName ) {
		LogManager::SlogMsg( "Font", OGLL_INFO ) << "(" << fontName << ") [" << sourceFilename << "]"
		<< " Creation" << Log::endlog;

		mFilename = sourceFilename;
		mFontName = fontName;

		mFT_Face = 0;
		mFontResource = new Resource;

		ResourceProvider* resProvider = System::getSingleton()._getResourceProvider();
		resProvider->loadResource( sourceFilename, *mFontResource );

		FT_Library* library = ( FT_Library* ) FontManager::getSingleton().mFTLibrary;
		FT_Face* tFace = new FT_Face;

		FT_Open_Args ftOpenArgs;
		ftOpenArgs.flags = FT_OPEN_MEMORY;
		ftOpenArgs.memory_base = mFontResource->getData();
		ftOpenArgs.memory_size = mFontResource->getSize();
		FT_Error error = FT_Open_Face( *library, &ftOpenArgs, 0, tFace );
		if ( error ) {
			LogManager::SlogMsg( "Font", OGLL_ERR )
			<< "FreeType 2 Error: (" << (( int )error ) << ") "
			<< FontManager::getSingleton()._GetFTErrorString( error )
			<< Log::endlog;
			delete tFace;
			tFace = 0;
			delete mFontResource;
			mFontResource = 0;
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "Fatal Error loading Font. Freetype error occurred during Font creation.", "FontSet::Font" );
		}
		mFT_Face = tFace;
	}
	//############################################################################
	FontSet::~FontSet() {
		LogManager::SlogMsg( "Font", OGLL_INFO ) << "(" << mFontName << ") [" << mFilename << "]"
		<< " Destruction" << Log::endlog;
		if ( FontManager::getSingletonPtr() )
			if ( FontManager::getSingleton().mFontCache ) {
				FontManager::getSingleton().mFontCache->FlushFont( this );
			}

		FT_Face* tFace = ( FT_Face* ) mFT_Face;
		if ( tFace ) {
			FT_Error error = FT_Done_Face( *tFace );
			if ( error ) {
				LogManager::SlogMsg( "Font", OGLL_ERR )
				<< "Error unloading Font - "
				<< "FreeType 2 Error: (" << (( int )error ) << ") "
				<< FontManager::getSingleton()._GetFTErrorString( error )
				<< Log::endlog;
			}
			delete tFace;
		}
		mFT_Face = 0;
		if ( mFontResource )
			delete mFontResource;
		mFontResource = 0;
	}
	//############################################################################
	void FontSet::renderGlyph( char glyph_charCode, const IVector2& pixelSize,
							   TextureDataRect* destTDR, FontGlyphMetrics& destGlyphMetrics ) {
		FT_Error error;
		FT_Face* tFace = ( FT_Face* ) mFT_Face;

		//set the glyph size requested
		error = FT_Set_Pixel_Sizes( *tFace, pixelSize.x, pixelSize.y );
		if ( error ) {
			LogManager::SlogMsg( "Font", OGLL_ERR ) << "[renderGlyph] "
			<< "FreeType 2 Error: (" << (( int )error ) << ") "
			<< FontManager::getSingleton()._GetFTErrorString( error )
			<< Log::endlog;
			return;
		}
		error = FT_Load_Char( *tFace, glyph_charCode, FT_LOAD_RENDER );
		if ( error ) {
			LogManager::SlogMsg( "Font", OGLL_ERR ) << "[renderGlyph] "
			<< "FreeType 2 Error: (" << (( int )error ) << ") "
			<< FontManager::getSingleton()._GetFTErrorString( error )
			<< Log::endlog;
			return;
		}

		FT_Size_Metrics* sMetrics = &(( *tFace )->size->metrics );
		FT_Glyph_Metrics* metrics = &(( *tFace )->glyph->metrics );
		destGlyphMetrics.width = metrics->width / 64;
		destGlyphMetrics.height = metrics->height / 64;
		destGlyphMetrics.horiBearingX = metrics->horiBearingX / 64;
		destGlyphMetrics.horiBearingY = metrics->horiBearingY / 64;
		destGlyphMetrics.horiAdvance = metrics->horiAdvance / 64;
		destGlyphMetrics.vertBearingX = metrics->vertBearingX / 64;
		destGlyphMetrics.vertBearingY = metrics->vertBearingY / 64;
		destGlyphMetrics.vertAdvance = metrics->vertAdvance / 64;
		destGlyphMetrics.horizLineSpacing = sMetrics->height / 64;


		FT_Bitmap* bitmap = &(( *tFace )->glyph->bitmap ); //easier pointer

		//Resize the destTDR to perfectly hold the output
		destTDR->setSize( IVector2( bitmap->width, bitmap->rows ), TDRColor() );

		//Copy the rendered bitmap to the TDR buffer
		IVector2 writeLoc;
		TDRColor writeColor;
		for ( int y = 0; y < bitmap->rows; y++ ) {
			writeLoc.y = y;
			for ( int x = 0; x < bitmap->width; x++ ) {
				writeLoc.x = x;
				unsigned char* data_slot =
					&( bitmap->buffer[( y * bitmap->width ) + x] );
				writeColor.Alpha = *data_slot;
				destTDR->write( writeLoc, writeColor );
			}
		}
	}
	//############################################################################
	//! Returns the line height in pixels for a given pixelSizeY
	unsigned int FontSet::getLineSpacing( unsigned int pointSize ) {
		IVector2 pixelRes;
		pixelRes.x = pointSize;
		pixelRes.y = pointSize;

		FT_Error error;
		FT_Face* tFace = ( FT_Face* ) mFT_Face;

		//set the glyph size requested
		error = FT_Set_Pixel_Sizes( *tFace, pixelRes.x, pixelRes.y );
		if ( error ) {
			LogManager::SlogMsg( "Font", OGLL_ERR ) << "[getLineSpacing] "
			<< "FreeType 2 Error: (" << (( int )error ) << ") "
			<< FontManager::getSingleton()._GetFTErrorString( error )
			<< Log::endlog;
			return pointSize; //fugly fallback value
		}
		FT_Size_Metrics* sMetrics = &(( *tFace )->size->metrics );
		return sMetrics->height / 64;
	}
	//############################################################################
	bool FontSet::getGlyph( const char glyph_charCode, const IVector2& pixelSize, FontGlyph& outFontGlyph ) {

		if ( !FontManager::getSingletonPtr() ) {
			//err msg
			return false;
		}


		FontManager::getSingletonPtr()->mFontCache
		->GetGlyph( this, glyph_charCode, pixelSize, outFontGlyph );

		return true;
	}
	//############################################################################
};
