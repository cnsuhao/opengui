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
	void WidgetFactoryManager::registerWidgetFactory(std::string widgetName, WidgetFactoryCallback factoryCallback)
	{
		mCallbackmap[widgetName]=factoryCallback;
	}
	//############################################################################
	void WidgetFactoryManager::unregisterWidgetFactory(std::string widgetName)
	{
		CallbackMap::iterator iter = mCallbackmap.find(widgetName);
		if(iter != mCallbackmap.end())
			mCallbackmap.erase(iter);
	}
	//############################################################################
	Widgets::Widget* WidgetFactoryManager::createWidget(std::string widgetName)
	{
		CallbackMap::iterator iter = mCallbackmap.find(widgetName);
		if(iter != mCallbackmap.end()){
			try{ //undefined? you bet! but hey, we've got faith.
				return iter->second.Call();
			}catch(...){
				return 0;
			}
		}else
			return 0;
	}
	//############################################################################
}; //namespace OpenGUI{


