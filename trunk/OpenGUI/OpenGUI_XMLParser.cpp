
#include "tinyxml.h"

#include "OpenGUI.h"

namespace OpenGUI{
	void XMLParser::LoadFromFile(const std::string& xmlFilename)
	{
		TiXmlDocument doc;
		doc.LoadFile(xmlFilename);
		TiXmlElement* root = doc.RootElement();
		TiXmlElement* section;
		section = root;


		if(section){
			do{
				if(0 == strcmpi(section->Value(),"GUISheet")){
					//LayoutLoader::_loadGUISheetFromTinyXMLElement(section);
				}
			}while( (section = section->NextSiblingElement()) );
		}
	}
};//namespace OpenGUI{

