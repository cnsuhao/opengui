#include "tinyxml.h"
#include "OpenGUI_XMLParser.h"
#include "OpenGUI_XML.h"
#include "OpenGUI_LogSystem.h"

namespace OpenGUI {
	//############################################################################
	void XMLParser::LoadFromFile( const std::string& xmlFilename ) {
		LogManager::SlogMsg( "XMLParser", OGLL_INFO ) << "BEGIN LoadFromFile: " << xmlFilename << Log::endlog;
		XMLDoc doc;
		doc.loadFile(xmlFilename);
		LogManager::SlogMsg( "XMLParser", OGLL_INFO ) << "END LoadFromFile: " << xmlFilename << Log::endlog;
	}
	//############################################################################
}//namespace OpenGUI {
/*
namespace OpenGUI {
	//############################################################################
	void XMLParser::LoadFromFile( const std::string& xmlFilename ) {
		LogManager::SlogMsg( "XMLParser", OGLL_INFO ) << "BEGIN LoadFromFile: " << xmlFilename << Log::endlog;
		IncludeSet includesToIgnore;
		XMLParser::ParseXMLFile( xmlFilename, includesToIgnore, 1 );
		LogManager::SlogMsg( "XMLParser", OGLL_INFO ) << "END LoadFromFile: " << xmlFilename << Log::endlog;
	}
	//############################################################################
	void XMLParser::ParseXMLFile( const std::string& xmlFilename, IncludeSet& includesToIgnore, unsigned int depth ) {
		for ( unsigned int i = 0; i < depth; i++ ) //stupid log indent trick
			LogManager::SlogMsg( "XMLParser", OGLL_INFO ) << "  ";
		LogManager::SlogMsg( "XMLParser", OGLL_INFO ) << "Parsing XML file: " << xmlFilename << Log::endlog;

		includesToIgnore.insert( xmlFilename );

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
				if ( 0 == strcmpi( section->Value(), "Include" ) ) {
					TiXmlAttribute* attrib = section->FirstAttribute();
					const char* fileName = 0;
					if ( attrib ) {
						do {
							if ( 0 == strcmpi( attrib->Name(), "file" ) ) {
								fileName = attrib->Value();
							}
						} while (( attrib = attrib->Next() ) );
					}
					if ( fileName ) {
						if ( includesToIgnore.find( std::string( fileName ) ) == includesToIgnore.end() ) {
							XMLParser::ParseXMLFile( fileName, includesToIgnore, depth + 1 );
						} else {
							LogManager::SlogMsg( "XMLParser", OGLL_WARN )
							<< "Skipping reference to \"" << fileName << "\" in file \""
							<< xmlFilename << "\". (" << fileName << " has already been included previously)"
							<< Log::endlog;
						}
					}
				}
				if ( 0 == strcmpi( section->Value(), "imageset" ) ) {
					ImageryManager::getSingleton()._loadImagesetFromTinyXMLElement( section );
				}
				if ( 0 == strcmpi( section->Value(), "template" ) ) {
					WidgetTemplateManager::getSingleton()._loadTemplateFromTinyXMLElement( section );
				}
				if ( 0 == strcmpi( section->Value(), "GUISheet" ) ) {
					LayoutLoader::_loadGUISheetFromTinyXMLElement( section );
				}
				if ( 0 == strcmpi( section->Value(), "font" ) ) {
					FontManager::getSingleton()._loadFontFromTinyXMLElement( section );
				}
				if ( 0 == strcmpi( section->Value(), "plugin" ) ) {
					PluginManager::getSingleton()._loadFromTinyXMLElement( section );
				}
			} while (( section = section->NextSiblingElement() ) );
		}
	}
	//############################################################################
}
;//namespace OpenGUI{
*/

