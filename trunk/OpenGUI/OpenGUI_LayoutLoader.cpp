#include "tinyxml.h"

//#include "OpenGUI.h"

//#include "OpenGUI_PreRequisites.h"
//#include "OpenGUI_LayoutLoader.h"
//#include "OpenGUI_System.h"

/*
namespace OpenGUI {

	//#####################################################################
	void LayoutLoader::LoadLayoutFromXML( const std::string& xmlFilename ) {
		LogManager::SlogMsg( "LayoutLoader", OGLL_INFO ) << "LoadLayoutFromXML: " << xmlFilename << Log::endlog;

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
				if ( 0 == strcmpi( section->Value(), "GUISheet" ) ) {
					LayoutLoader::_loadGUISheetFromTinyXMLElement( section );
				}
			} while (( section = section->NextSiblingElement() ) );
		}
	}
	//#####################################################################
	void LayoutLoader::_loadGUISheetFromTinyXMLElement( void* tXelementPtr ) {
		TiXmlElement* tXelement = ( TiXmlElement* )tXelementPtr;
		const char* sheetName = 0;
		TiXmlAttribute* attrib = tXelement->FirstAttribute();

		if ( attrib ) {
			do {
				if ( 0 == strcmpi( attrib->Name(), "name" ) ) {
					sheetName = attrib->Value();
					break;
				}
			} while (( attrib = attrib->Next() ) );
		}

		GUISheet* sheet;
		if ( !sheetName ) {
			OG_THROW( Exception::ERR_INVALIDPARAMS, "<GUISheet> requires a 'name' attribute", "_loadGUISheetFromTinyXMLElement" );
		} else {
			sheet = System::getSingleton().getGUISheetByName( sheetName );
			if ( !sheet ) {
				sheet = System::getSingleton().createGUISheet( sheetName );
			}
		}
		if ( !sheet ) {
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Could not find or create GUISheet: " + std::string( sheetName ), "LayoutLoader" );
		}

		//iterate through all children tags
		TiXmlElement* section;
		section = tXelement->FirstChildElement();
		if ( section ) {
			do {
				if ( 0 == strcmpi( section->Value(), "Widget" ) ) {
					LayoutLoader::_loadWidgetFromTinyXMLElement( section, sheet );
				}
			} while (( section = section->NextSiblingElement() ) );
		}

	}
	//#####################################################################
	void LayoutLoader::_loadWidgetFromTinyXMLElement( void* tXelementPtr, Element* parent ) {
		TiXmlElement* tXelement = ( TiXmlElement* )tXelementPtr;
		const char* widgetName = 0;
		const char* widgetGroup = 0;
		const char* widgetType = 0;
		TiXmlAttribute* attrib = tXelement->FirstAttribute();

		if ( attrib ) {
			do {
				if ( 0 == strcmpi( attrib->Name(), "name" ) ) {
					widgetName = attrib->Value();
				}
				if ( 0 == strcmpi( attrib->Name(), "group" ) ) {
					widgetGroup = attrib->Value();
				}
				if ( 0 == strcmpi( attrib->Name(), "type" ) ) {
					widgetType = attrib->Value();
				}
			} while (( attrib = attrib->Next() ) );
		}

		if ( widgetType ) {
			if ( !widgetName )
				widgetName = "";
			if ( !widgetGroup )
				widgetGroup = "";
			Widgets::Widget* w;
			w = System::getSingleton().createWidget( widgetType, widgetGroup );
			if ( w ) {
				parent->addChildElement( w, widgetName );

				//iterate through all children tags
				TiXmlElement* section;
				section = tXelement->FirstChildElement();
				if ( section ) {
					do {
						if ( 0 == strcmpi( section->Value(), "Widget" ) ) {
							LayoutLoader::_loadWidgetFromTinyXMLElement( section, w );
						}

						if ( 0 == strcmpi( section->Value(), "property" ) ) {
							attrib = section->FirstAttribute();
							if ( attrib ) {
								const char* propName = 0;
								const char* propValue = 0;
								do {
									if ( 0 == strcmpi( attrib->Name(), "name" ) ) {
										propName = attrib->Value();
									}
									if ( 0 == strcmpi( attrib->Name(), "value" ) ) {
										propValue = attrib->Value();
									}
								} while (( attrib = attrib->Next() ) );
								if ( !propValue ) {
									propValue = section->GetText();
								}
								if ( propValue && propName ) {
									w->propertySet( propName, propValue );
								} else {
									if ( !propValue && ! propName )
										OG_THROW( Exception::ERR_INVALIDPARAMS, "Property is missing both a name and a value", "_loadWidgetFromTinyXMLElement" );
									else if ( !propName )
										OG_THROW( Exception::ERR_INVALIDPARAMS, "Property is missing a name", "_loadWidgetFromTinyXMLElement" );
									else if ( !propValue )
										OG_THROW( Exception::ERR_INVALIDPARAMS, "Property " + std::string( propName ) + " did not provide a Value as either an attribute or in the tag body", "_loadWidgetFromTinyXMLElement" );
								}
							}
						}
					} while (( section = section->NextSiblingElement() ) );
				}

			} else {
				OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Could not create widget: System failed to return a valid widget", "LayoutLoader::_loadWidgetFromTinyXMLElement" );
			}
		} else {
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Could not create widget: XML element missing valid 'type' attribute", "LayoutLoader::_loadWidgetFromTinyXMLElement" );
		}
	}

}
;//namespace OpenGUI{
*/

