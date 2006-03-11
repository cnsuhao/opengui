
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
		//
	}
	//############################################################################
	WidgetTemplateManager::~WidgetTemplateManager()
	{
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
		//remove duplicate templates
		WidgetTemplateManager::destroyTemplate(templateName);
		mWidgetTemplateMap[templateName] = new WidgetTemplate(baseGroupName, baseWidgetName);
	}
	//############################################################################
	void WidgetTemplateManager::destroyTemplate(std::string templateName)
	{
		WidgetTemplateMap::iterator iter = mWidgetTemplateMap.find(templateName);
		if(mWidgetTemplateMap.end() != iter){
			delete (*iter).second;
			mWidgetTemplateMap.erase(iter);
		}
	}
	//############################################################################
	void WidgetTemplateManager::addTemplateProperty(std::string templateName, std::string propertyName, std::string propertyValue)
	{
		WidgetTemplateMap::iterator iter = mWidgetTemplateMap.find(templateName);
		if(mWidgetTemplateMap.end() == iter){
			(*iter).second->addProperty(propertyName ,propertyValue);
		}else{
			throw Exception("Template '" + templateName + "' does not exist, cannot remove property.");
		}
	}
	//############################################################################
	void WidgetTemplateManager::removeTemplateProperty(std::string templateName, std::string propertyName)
	{
		WidgetTemplateMap::iterator iter = mWidgetTemplateMap.find(templateName);
		if(mWidgetTemplateMap.end() != iter){
			(*iter).second->removeProperty(propertyName);
		}else{
			throw Exception("Template '" + templateName + "' does not exist, cannot remove property.");
		}
	}
	//############################################################################
	Widgets::Widget* WidgetTemplateManager::createWidget(std::string templateName)
	{
		WidgetTemplateMap::iterator iter = mWidgetTemplateMap.find(templateName);
		if(mWidgetTemplateMap.end() != iter){
			Widgets::Widget* widget;
			widget = (*iter).second->createWidget();
			return widget;
		}else{
			throw Exception("Template '" + templateName + "' does not exist, cannot create widget.");
		}
	}
	//############################################################################
	//############################################################################
	//############################################################################
	Widgets::Widget* WidgetTemplate::createWidget()
	{
		Widgets::Widget* widget;
		widget = WidgetFactoryManager::getSingleton().createWidget(mBaseGroupName,mBaseWidgetName);
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
		std::transform(tmpstr.begin(),tmpstr.end(),tmpstr.begin(),static_cast<int(*)(int)>(std::tolower));

		mPropertyMap[tmpstr]=propertyValue;
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
