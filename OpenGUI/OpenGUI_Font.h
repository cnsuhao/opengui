#ifndef A3E35C4A_48F9_429b_B13A_F3AB9BFF90D4
#define A3E35C4A_48F9_429b_B13A_F3AB9BFF90D4

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Resource.h"
#include "OpenGUI_Imagery.h"

#include "OpenGUI_FontGlyph.h"

namespace OpenGUI {

	class TextureDataRect;


	//! Used to load fonts and render glyphs from those fonts into memory segments.
	class OPENGUI_API FontSet: public RefObject {
		friend class FontManager;
	protected:
		//! Font creation implies loading of the font via FreeType.
		/*! \param sourceFilename filename of the font to load */
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
			\param pointSize The size of the glyph you'd like, in font points. <i>This value is automatically
				adjusted according to the native resolution of the font if autoscale is enabled for the font.
				This is used to provide font glyphs that scale with resolution changes while still preserving
				the opportunity for proper pixel alignment.</i>
			\param outPixelRect On success, this is rect is set to the extents of the glyph produced. 0,0 will
				always be the glyph's horizontal baseline.
			\param outFontGlyph On success, this is initialized with information about the glyph.
			
			The imagery provided by \c outImageryPtr will provide pixel alignment if the glyph is drawn to the
			screen in the exact size as outPixelRect. It is up to the user to provide this last stage pixel
			alignment. In most cases, users should use the PrimitiveText object to generate their text output,
			as it will perform the necessary steps to provide pixel alignment.
		*/
		bool getGlyph( const char glyph_charCode, const IVector2& pointSize, IRect& outPixelRect, FontGlyph& outFontGlyph );

		//! Returns the line height in pixels for a given pointSize
		/*! \see To obtain the pixelSizeY, refer to \c calcPixelSizeFromPoints()
		*/
		unsigned int getLineSpacing( unsigned int pointSize );

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


	class OPENGUI_API Font {
	public:
		Font()
				: m_FontSetPtr( 0 ), m_FontSize( 0.0f ) {}

		Font( FontSetPtr fontSet, float fontSize )
				: m_FontSetPtr( fontSet ), m_FontSize( fontSize ) {
			if ( m_FontSize < 0.1f ) m_FontSize = 0.1f;
		}

		Font( const std::string& fontName, float fontSize );

	~Font() {}

		bool isNull() {
			return m_FontSetPtr.isNull();
		}
		const std::string& getName() {
			return m_FontSetPtr->getName();
		}
		float getSize() {
			return m_FontSize;
		}
		FontSetPtr getFontSetPtr() {
			return m_FontSetPtr;
		}

	private:
		FontSetPtr m_FontSetPtr;
		float m_FontSize;
	};
};

#endif

