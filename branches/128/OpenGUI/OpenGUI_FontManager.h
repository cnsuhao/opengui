// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef E066B8D8_F5B9_4e34_84C2_9BE53ACFA533
#define E066B8D8_F5B9_4e34_84C2_9BE53ACFA533

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_String.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_Font.h"
#include "OpenGUI_FontSet.h"
#include "OpenGUI_FontGlyph.h"
#include "OpenGUI_XML.h"

namespace OpenGUI {
	class Texture;	//forward declaration
	class FontCache; //forward declaration


	//! Provides font loading and texture UV generation for glyphs loaded from fonts.
	class OPENGUI_API FontManager : public Singleton<FontManager> {
		friend class FontSet;
		friend class XMLParser;
	public:
		FontManager();

		~FontManager();

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static FontManager& getSingleton( void );

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static FontManager* getSingletonPtr( void );


		//! Registers a new font
		/*! If an existing font already exists with the same \c fontName, it will replaced
			by the new font. This will only affect newly created Font handles, and does not
			update the default font if the replaced font was also the default font.
			\note
			The first font registered is automatically set as the default using fontSize = 12.
			To manually set the default font to something else, use \c SetDefaultFont().
		*/
		FontSetPtr RegisterFontSet( String filename, String fontName );

		//! Sets the default font
		/*! This sets the default font and font size (in points) that is used when no font is specified.
		*/
		void SetDefaultFont( Font font );

		//! Retrieves the default font
		Font GetDefaultFont();

		//! UnRegisters a loaded font by handle
		/*! This function will bind the given Font handle if it is not already bound. */
		void UnRegisterFontSet( Font font ) {
			font.bind();
			UnRegisterFontSet( font.getFontSetPtr() );
		}

		//! UnRegisters a loaded font by name
		void UnRegisterFontSet( const String& fontName );

		//! UnRegisters a loaded font by FontSetPtr
		void UnRegisterFontSet( FontSetPtr fontSet );

		//! Retrieves a font by name
		FontSetPtr GetFontSet( const String& fontName );

		//! a list of font names that are currently loaded in the FontManager, retrieved by FontManager::getFontList()
		typedef std::list<String> FontList;

		//! Returns a FontList containing the names of all loaded fonts, which can then be fed to GetFontSet() or used with Font
		FontList getFontList();

		//! Returns an ImageryPtrList containing ImageryPtrs for each font atlas.
		ImageryPtrList _getFontAtlases();

	private:
		//! \internal Returns a string containing the error description from FreeType for the given FreeType error code. If the error is not found, "*UNKNOWN ERROR*" is returned.
		String _GetFTErrorString( int errorCode );

		//! \internal This is a pointer to the freetype2 library handle. It is held as a (void*) to remove the need for the freetype includes in OpenGUI using applications.
		void* mFTLibrary;

		FontCache* mFontCache;

		typedef std::map<String, FontSetPtr> FontSetPtrMap;
		FontSetPtrMap mFontSetMap;

		Font mDefaultFont;

		// XML tag handlers for <Font> tags
		static bool _Font_XMLNode_Load( const XMLNode& node, const String& nodePath );
		static bool _Font_XMLNode_Unload( const XMLNode& node, const String& nodePath );
	};
}//namespace OpenGUI{
#endif
