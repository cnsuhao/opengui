// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef BE0429DB_7CC6_424c_8AF8_96B0BE08270D
#define BE0429DB_7CC6_424c_8AF8_96B0BE08270D

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_RefObject.h"

namespace OpenGUI {

	class TextureDataRect;
	struct FontGlyph;
	struct FontGlyphMetrics;
	class Resource;

	//! Used to load fonts and render glyphs from those fonts into memory segments.
	class OPENGUI_API FontSet: public RefObject {
		friend class FontManager;
	protected:
		//! Font creation implies loading of the font via FreeType.
		/*! \param sourceFilename filename of the font to load
		\param fontName the friendly name for this FontSet */
		FontSet( const std::string& sourceFilename, const std::string& fontName );
		//! Destruction also unloads the font from FreeType
		~FontSet();
		virtual void finalize();
	public:
		//! Returns the filename used to load the font
		const std::string& getFilename() {
			return mFilename;
		}

		//! Returns the name of this font
		const std::string& getName() {
			return mFontName;
		}

		//! Retrieves the imagery backing a font glyph, as well as a pixel based rect defining the glyph extents.
		/*!
		\return \c true on success, \c false if the glyph cannot be generated because of some FreeType error
		\param glyph_charCode The character code (currently ASCII) of the glyph you are requesting
		\param pixelSize The size of the glyph you'd like, in pixels. Translation to/from pixels is up to
		the user. (See: Screen::getPPU(), Screen::getUPI())
		\param outFontGlyph On success, this is initialized with information about the glyph.

		The imagery provided by \c outImageryPtr will provide pixel alignment if the glyph is drawn to the
		screen in the exact size as outPixelRect. It is up to the user to provide this last stage pixel
		alignment. In most cases, users should use the PrimitiveText object to generate their text output,
		as it will perform the necessary steps to provide pixel alignment.
		*/
		bool getGlyph( const char glyph_charCode, const IVector2& pixelSize, FontGlyph& outFontGlyph );

		//! Returns the line height in pixels for a given \c pointSize
		unsigned int getLineSpacing( unsigned int pointSize );

		//! Returns the font wide ascender in pixels for a given \c pointSize
		int getAscender( unsigned int pointSize );

		//! Returns the font wide descender in pixels for a given \c pointSize
		int getDescender( unsigned int pointSize );

		//! Returns the maximum horizontal advance for all characters at the given \c pointSize
		int getMaxAdvance( unsigned int pointSize );

		//! Returns the true width for the given \c text at the given \c pointSize
		int getTextWidth( const IVector2& pixelSize, const std::string& text );

		//! Renders the requested glyph to the given TextureDataRect in the size specified.
		/*!
		\note The TextureDataRect will be resized to exactly hold the glyph. \c destGlyphMetrics will
		contain the glyph metrics in pixels for the glyph at the requested size
		\remarks This function is used by the FontCache to generate glyphs for storage in FontAtlases
		so that they can be renderer to the screen.
		\see Most users are probably looking for PrimitiveText, or at the most getGlyph().
		*/
		void renderGlyph( char glyph_charCode, const IVector2& pixelSize, TextureDataRect* destTDR, FontGlyphMetrics& destGlyphMetrics );

	private:
		void* mFT_Face;
		std::string mFilename;
		std::string mFontName;
		Resource *mFontResource;
	};
	typedef RefObjHandle<FontSet> FontSetPtr;

} // namespace OpenGUI{

#endif // BE0429DB_7CC6_424c_8AF8_96B0BE08270D
