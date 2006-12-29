// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef E939FE64_239A_451b_8320_FE38D560CBAE
#define E939FE64_239A_451b_8320_FE38D560CBAE

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"

namespace OpenGUI {
	//! Provides loading of layouts from XML
	class OPENGUI_API LayoutLoader {
		friend class XMLParser;
	public:
		//! Loads GUISheets from an XML document.
		/*! Any non-Layout related XML entities are silently ignored (only processes \<GUISheet\> and other enclosed tags). */
		static void LoadLayoutFromXML( const std::string& xmlFilename );
	private:
		static void _loadGUISheetFromTinyXMLElement( void* tXelementPtr );
		static void _loadWidgetFromTinyXMLElement( void* tXelementPtr, Element* parent );
	};
};
#endif

