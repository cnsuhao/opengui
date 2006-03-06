#include "OpenGUI.h"


namespace OpenGUI{
	//############################################################################
	template<> WidgetFactoryManager* Singleton<WidgetFactoryManager>::mptr_Singleton = 0;
	//############################################################################
	WidgetFactoryManager& WidgetFactoryManager::getSingleton(void)
	{
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	WidgetFactoryManager* WidgetFactoryManager::getSingletonPtr(void)
	{
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	//############################################################################
	WidgetFactoryManager::WidgetFactoryManager()
	{
		//
	}
	//############################################################################
	WidgetFactoryManager::~WidgetFactoryManager()
	{
		//
	}
	//############################################################################
	void WidgetFactoryManager::registerWidgetFactory(std::string groupName, std::string widgetName, WidgetFactoryCallback factoryCallback)
	{
		CallbackMapItem item;
		item.callBack=factoryCallback;
		item.groupName=groupName;
		item.widgetName=widgetName;
		mCallbackmap[_buildGroupNameComposite(groupName,widgetName)]=item;
	}
	//############################################################################
	void WidgetFactoryManager::unregisterWidgetFactory(std::string groupName, std::string widgetName)
	{
		CallbackMap::iterator iter = mCallbackmap.find(_buildGroupNameComposite(groupName,widgetName));
		if(iter != mCallbackmap.end())
			mCallbackmap.erase(iter);
	}
	//############################################################################
	Widgets::Widget* WidgetFactoryManager::createWidget(std::string groupName, std::string widgetName)
	{
		CallbackMap::iterator iter = mCallbackmap.find(_buildGroupNameComposite(groupName,widgetName));
		if(iter != mCallbackmap.end()){
			//call me paranoid, but i'm going to check again just to make sure
			if(iter->second.groupName == groupName && iter->second.widgetName == widgetName){
				try{ //undefined? you bet! but hey, we've got faith.
					return iter->second.callBack.Call();
				}catch(...){
					return 0;
				}
			}
		}
		return 0;
	}
	//############################################################################
	std::string WidgetFactoryManager::_buildGroupNameComposite(const std::string& groupName, const std::string& widgetName)
	{
		std::stringstream ss;
		ss << groupName << ":" << widgetName;
		return ss.str();
	}
	//############################################################################
}; //namespace OpenGUI{


