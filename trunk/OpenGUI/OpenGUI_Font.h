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
		bool getGlyph( const char glyph_charCode, const IVector2& pixelSize, FontGlyph& outFontGlyph );

		//! Returns the line height in pixels for a given \c pointSize
		unsigned int getLineSpacing( unsigned int pointSize );

		//! Returns the font wide ascender in pixels for a given \c pointSize
		unsigned int getAscender( unsigned int pointSize );

		//! Returns the font wide descender in pixels for a given \c pointSize
		unsigned int getDescender( unsigned int pointSize );

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


	//! A handle representing font type and size
	/*! Fonts are referenced using the Font object, which contain a reference to a FontSet and
	the desired size. These handles can be created at will by the user, and are automatically
	bound to the appropriate FontSet during the constructor. These handles are also capable of
	referencing the default FontSet at the default size, and this is usually accomplished by
	creating the object using the default constructor.

	Font handles also provide automatic support for	delayed binding under certain conditions
	and uses. If a Font is using delayed binding, the actual binding will occur on first use
	in a rendering context. If the desired FontSet cannot be found, the Font handle will
	automatically bind to the default Font. If no default Font is available, an exception will
	occur. ( The default Font is automatically bound to the first FontSet registered with the
	FontManager, and can be changed by FontManager::SetDefaultFont(). )

	\note You'll notice there are no methods for changing the size or FontSet of a Font object.
	That is because it is intended that a new Font object be created whenever the size or font
	type needs to be changed. Enough information about a Font handle can be retrieved to provide
	an avenue for changing only a single attribute.

	\warning Font sizes that are less than or equal to 0.0f are not legal for bound Font handles,
	and will automatically be interpretted as a request for the default font size.
	*/
	class OPENGUI_API Font {
	public:
		//! Create a font handle that will either immediate or delayed bind to the default font.
		Font();

		//! Create a font handle to the given \c fontSet at the given \c fontSize.
		Font( FontSetPtr fontSet, float fontSize );

		//! Create a font handle to the given registered \c fontName at the given \c fontSize.
		Font( const std::string& fontName, float fontSize );

		//! public destructor does nothing special
		~Font() {
			/**/
		}

		//! Returns \c true if this handle is bound to a FontSet
		bool isBound() const {
			return m_Bound;
		}

		//! Forces immediate binding of this Font, throwing an exception if the binding does not complete.
		void bind();

		//! Returns the name of the FontSet this Font is currently or will be bound to
		const std::string& getName() const {
			return m_FontName;
		}

		//! Returns the font size of this Font handle
		float getSize() const {
			return m_FontSize;
		}

		//! Returns the FontSetPtr of the Font handle
		FontSetPtr getFontSetPtr() const {
			return m_FontSetPtr;
		}

		//! Provides direct access to the bound FontSet's functions
		/*! This causes an immediate bind, throwing an exception if the bind fails. */
		FontSet* operator->() {
			bind();
			return m_FontSetPtr.operator ->();
		}

	private:
		bool m_Bound;
		FontSetPtr m_FontSetPtr;
		float m_FontSize;
		std::string m_FontName;

		bool _tryBind(); // tries to bind the font, returning false if failed for any reason
	};
};

#endif

