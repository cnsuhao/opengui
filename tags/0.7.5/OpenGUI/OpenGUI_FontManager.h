#ifndef E066B8D8_F5B9_4e34_84C2_9BE53ACFA533
#define E066B8D8_F5B9_4e34_84C2_9BE53ACFA533

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Singleton.h"

#include "OpenGUI_FontGlyph.h"


namespace OpenGUI{
	class Font;		//forward declaration
	class Texture;	//forward declaration
	class FontCache; //forward declaration

	//! Provides font loading and texture UV generation for glyphs loaded from fonts.
	class OPENGUI_API FontManager : public Singleton<FontManager>{
		friend class Font;
		friend class XMLParser;
	public:
		FontManager();

		~FontManager();

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static FontManager& getSingleton(void);

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static FontManager* getSingletonPtr(void);


		//! Creates a new font
		/*! If an existing font already exists with the same \c fontName, it will destroyed and replaced
			by the new font. This will, of course, cause a complete cache unload for that font.
			\note
			The first font loaded is automatically set as the default. To manually set the default
			font to something else, use \c SetDefaultFont().
		*/
		Font* CreateFont(std::string filename, std::string fontName, bool autoscale=true, unsigned int xres=800, unsigned int yres=600);
		
		//! Sets the default font
		/*! This sets the default font and font size (in points) that is used when no font is specified.
		*/
		void SetDefaultFont(std::string fontName, unsigned int fontSize=12);
		//! Destroys a loaded font
		void DestroyFont(std::string fontName);

		//! Destroys all loaded fonts
		/*! Performed automatically as part of FontManager shutdown */
		void DestroyAllFonts();

		//! Retrieves a font by name
		Font* GetFont(std::string name);

		//! Retrieves a pointer to the default font, or 0 if no default font is available
		Font* GetDefaultFont()
			{
				if(mDefaultFontName != ""){
					return GetFont(mDefaultFontName);
				}else
					return 0;
			}
		//! Retrieves the default font size, if no default size was set, then 12 is returned
		unsigned int GetDefaultFontSize() { return mDefaultFontSize?mDefaultFontSize:12; }

		//! Retrieves a single glyph from the given fontName at the specified point size.
		/*! This function will automatically substitute the default font if the requested
			font cannot be found (or you request ""), and will also substitute the default
			size if you request a size of 0;
		*/
		void getGlyph(IRect& outPixelRect, FontGlyph& outFontGlyph,
			char glyph_charCode, const std::string& fontName="", unsigned int pointSize=0);

		//! Retrieves the line spacing of the requested font and the given size.
		/*! This function will automatically substitute the default font if the requested
			font cannot be found (or you request ""), and will also substitute the default
			size if you request a size of 0;
		*/
		unsigned int getLineSpacing(const std::string& fontName="", unsigned int pointSize=0);
		

		//! Loads Fonts from an XML document.
		/*! Any conflicting Fonts will be overwritten, any non-font related
			XML entities are silently ignored.
		*/
		void LoadFontsFromXML(std::string xmlFilename);

	private:

		Font* _loadFontFromTinyXMLElement(void* tXelementPtr);

		//! \internal Returns a string containing the error description from FreeType for the given FreeType error code. If the error is not found, "*UNKNOWN ERROR*" is returned.
		std::string _GetFTErrorString(int errorCode);

		//! \internal This is a pointer to the freetype2 library handle. It is held as a (void*) to remove the need for the freetype includes in OpenGUI using applications.
		void* mFTLibrary;

		FontCache* mFontCache;

		typedef std::map<std::string, Font*> FontCPtrMap;
		FontCPtrMap mFontMap;

		std::string mDefaultFontName;
		unsigned int mDefaultFontSize;

	};
}//namespace OpenGUI{
#endif
