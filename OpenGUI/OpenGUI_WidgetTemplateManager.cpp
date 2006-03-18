
#include "tinyxml.h"

#include "OpenGUI.h"


namespace OpenGUI{
	//############################################################################
	template<> WidgetTemplateManager* Singleton<WidgetTemplateManager>::mptr_Singleton = 0;
	//############################################################################
	WidgetTemplateManager& WidgetTemplateManager::getSingleton(void)
	{
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	WidgetTemplateManager* WidgetTemplateManager::getSingletonPtr(void)
	{
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	//############################################################################
	WidgetTemplateManager::WidgetTemplateManager()
	{
		LogManager::SlogMsg("INIT", OGLL_INFO2) << "Creating WidgetTemplateManager" << Log::endlog;
	}
	//############################################################################
	WidgetTemplateManager::~WidgetTemplateManager()
	{
		LogManager::SlogMsg("SHUTDOWN", OGLL_INFO2) << "Destroying WidgetTemplateManager" << Log::endlog;
		WidgetTemplateMap::iterator iter = mWidgetTemplateMap.begin();
		while(mWidgetTemplateMap.end() != iter){
			delete (*iter).second;
			iter++;
		}
		mWidgetTemplateMap.clear();
	}
	//############################################################################
	void WidgetTemplateManager::createTemplate(std::string templateName, std::string baseGroupName, std::string baseWidgetName)
	{
		LogManager::SlogMsg("WidgetTemplateManager", OGLL_INFO2) << "Creating Template: " << templateName;
		LogManager::SlogMsg("WidgetTemplateManager", OGLL_INFO2) << " source: " << baseGroupName << "/" << baseWidgetName;
		LogManager::SlogMsg("WidgetTemplateManager", OGLL_INFO2) << Log::endlog;

		WidgetTemplateMap::iterator iter = mWidgetTemplateMap.find(templateName);
		if(mWidgetTemplateMap.end() != iter){
			LogManager::SlogMsg("WidgetTemplateManager", OGLL_INFO2) << "Removing Duplicate Template: " << templateName << Log::endlog;
			//remove duplicate templates
			WidgetTemplateManager::destroyTemplate(templateName);
		}
		
		mWidgetTemplateMap[templateName] = new WidgetTemplate(baseGroupName, baseWidgetName);
	}
	//############################################################################
	void WidgetTemplateManager::destroyTemplate(std::string templateName)
	{
		LogManager::SlogMsg("WidgetTemplateManager", OGLL_INFO2) << "Destroying Template: " << templateName;
		LogManager::SlogMsg("WidgetTemplateManager", OGLL_INFO2) << Log::endlog;

		WidgetTemplateMap::iterator iter = mWidgetTemplateMap.find(templateName);
		if(mWidgetTemplateMap.end() != iter){
			delete (*iter).second;
			mWidgetTemplateMap.erase(iter);
			LogManager::SlogMsg("WidgetTemplateManager", OGLL_INFO2) << templateName << " destroyed" << Log::endlog;
			return;
		}
		LogManager::SlogMsg("WidgetTemplateManager", OGLL_ERR) << templateName << " not found!" << Log::endlog;
	}
	//############################################################################
	void WidgetTemplateManager::addTemplateProperty(std::string templateName, std::string propertyName, std::string propertyValue)
	{
		LogManager::SlogMsg("WidgetTemplateManager", OGLL_INFO3) << "Add Template Property: " << templateName << " <- " << propertyName << ":" << propertyValue << Log::endlog;
		WidgetTemplateMap::iterator iter = mWidgetTemplateMap.find(templateName);
		if(mWidgetTemplateMap.end() != iter){
			(*iter).second->addProperty(propertyName ,propertyValue);
		}else{
			OG_THROW(Exception::ERR_ITEM_NOT_FOUND, "Template '" + templateName + "' does not exist, cannot add property: " + propertyName, "WidgetTemplateManager");
		}
	}
	//############################################################################
	void WidgetTemplateManager::removeTemplateProperty(std::string templateName, std::string propertyName)
	{
		LogManager::SlogMsg("WidgetTemplateManager", OGLL_INFO3) << "Remove Template Property: " << templateName << " <- " << propertyName << Log::endlog;
		WidgetTemplateMap::iterator iter = mWidgetTemplateMap.find(templateName);
		if(mWidgetTemplateMap.end() != iter){
			(*iter).second->removeProperty(propertyName);
		}else{
			OG_THROW(Exception::ERR_ITEM_NOT_FOUND, "Template '" + templateName + "' does not exist, cannot remove property: " + propertyName, "WidgetTemplateManager");
		}
	}
	//############################################################################
	Widgets::Widget* WidgetTemplateManager::createWidget(std::string templateName)
	{
		LogManager::SlogMsg("WidgetTemplateManager", OGLL_INFO3) << "CreateWidget from Template: ";
		LogManager::SlogMsg("WidgetTemplateManager", OGLL_INFO3) << templateName << Log::endlog;

		WidgetTemplateMap::iterator iter = mWidgetTemplateMap.find(templateName);
		if(mWidgetTemplateMap.end() != iter){
			Widgets::Widget* widget;
			widget = (*iter).second->createWidget();
			return widget;
		}else{
			OG_THROW(Exception::ERR_ITEM_NOT_FOUND, "Template '" + templateName + "' does not exist, cannot create widget.", "WidgetTemplateManager");
		}
	}
	//############################################################################
	void WidgetTemplateManager::LoadTemplatesFromXML(std::string xmlFilename)
	{
		LogManager::SlogMsg("WidgetTemplateManager", OGLL_INFO) << "LoadTemplatesFromXML: " << xmlFilename << Log::endlog;

		TiXmlDocument doc;
		doc.LoadFile(xmlFilename);
		TiXmlElement* root = doc.RootElement();
		TiXmlElement* section;
		section = root;
		if(section){
			do{
				//iterate through all of the root level elements and react to every "Imageset" found
				if(0 == strcmpi(section->Value(),"template")){
					WidgetTemplateManager::_loadTemplateFromTinyXMLElement(section);
				}
			}while( (section = section->NextSiblingElement()) );
		}
	}
	//############################################################################
	void WidgetTemplateManager::_loadTemplateFromTinyXMLElement(void* tXelementPtr)
	{
		TiXmlElement* tXelement = (TiXmlElement*)tXelementPtr;
		TiXmlAttribute* attrib = tXelement->FirstAttribute();
		const char* name = 0;
		const char* group = 0;
		const char* type = 0;
		if(attrib){
			do{
				if(0 == strcmpi(attrib->Name(),"name"))
					name = attrib->Value();
				if(0 == strcmpi(attrib->Name(),"group"))
					group = attrib->Value();
				if(0 == strcmpi(attrib->Name(),"type"))
					type = attrib->Value();
			}while( (attrib = attrib->Next()) );
		}
		if(name && group && type){
			WidgetTemplateMap::iterator iter = mWidgetTemplateMap.find(name);
			if(iter == mWidgetTemplateMap.end()){
				//only create if it does not already exist
				createTemplate(name, group, type);
			}
			TiXmlElement* propElement = tXelement->FirstChildElement();
			if(propElement){
				do{
					if(0 == strcmpi(propElement->Value(), "property")){
						const char* propName = 0;
						const char* propValue = 0;
						TiXmlAttribute* propAttrib = propElement->FirstAttribute();
						if(propAttrib){
							do{
								if(0 == strcmpi(propAttrib->Name(), "name"))
									propName = propAttrib->Value();
								if(0 == strcmpi(propAttrib->Name(), "value"))
									propValue = propAttrib->Value();
							}while( (propAttrib = propAttrib->Next()) );
						}
						if(propName && propValue){
							addTemplateProperty(name, propName, propValue);
						}
					}
				}while( (propElement = propElement->NextSiblingElement()) );
			}
		}
	}
	//############################################################################
	//############################################################################
	//############################################################################
	Widgets::Widget* WidgetTemplate::createWidget()
	{
		Widgets::Widget* widget;
		widget = WidgetFactoryManager::getSingleton().createWidget(mBaseGroupName, mBaseWidgetName);
		if(!widget) return 0;
		TemplatePropertyMap::iterator iter = mPropertyMap.begin();
		while(iter != mPropertyMap.end()){
			widget->propertySet( (*iter).first, (*iter).second );
			iter++;
		}
		return widget;
	}
	//############################################################################
	void WidgetTemplate::addProperty(std::string propertyName, std::string propertyValue)
	{
		std::string tmpstr = propertyName;
		std::transform(tmpstr.begin(), tmpstr.end(), tmpstr.begin(), static_cast<int(*)(int)>(std::tolower));

		mPropertyMap[tmpstr] = propertyValue;
	}
	//############################################################################
	void WidgetTemplate::removeProperty(std::string propertyName)
	{
		std::string tmpstr = propertyName;
		std::transform(tmpstr.begin(),tmpstr.end(),tmpstr.begin(),static_cast<int(*)(int)>(std::tolower));

		TemplatePropertyMap::iterator iter = mPropertyMap.find(tmpstr);
		if(iter != mPropertyMap.end())
			mPropertyMap.erase(iter);
	}
	//############################################################################
};//namespace OpenGUI{
