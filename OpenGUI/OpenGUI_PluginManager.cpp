#include "tinyxml.h"

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_DynamicLib.h"
#include "OpenGUI_PluginManager.h"

typedef void (*PLUGIN_START_FUNC)(void);
typedef void (*PLUGIN_STOP_FUNC)(void);

namespace OpenGUI{
	//############################################################################
	template<> PluginManager* Singleton<PluginManager>::mptr_Singleton = 0;
	//############################################################################
	PluginManager& PluginManager::getSingleton(void)
	{
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	PluginManager* PluginManager::getSingletonPtr(void)
	{
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	//############################################################################
	PluginManager::PluginManager()
	{
		//
	}
	//############################################################################
	PluginManager::~PluginManager()
	{
		PluginManager::unloadAllPlugins();
	}
	//############################################################################
	void PluginManager::loadPlugin(std::string filename)
	{
		PluginMap::iterator iter = mPluginMap.find(filename);
		if(iter == mPluginMap.end())
			throw Exception("Plugin already loaded: " + filename);

		//attach the module
		DynamicLib* lib = new DynamicLib(filename);
		try{
			lib->load();
		}catch(Exception e){
			delete lib;
			throw;
		}

		mPluginMap[filename] = lib;

		//run start plugin
		PluginManager::firePluginStart(lib);
	}
	//############################################################################
	void PluginManager::unloadPlugin(std::string filename)
	{
		DynamicLib* lib;
		PluginMap::iterator iter = mPluginMap.find(filename);
		if(iter == mPluginMap.end())
			throw Exception("Plugin not found in PluginManager's list: " + filename);

		lib = iter->second;
		mPluginMap.erase(iter);

		//run stop plugin
		PluginManager::firePluginStop(lib);

		//detach the module
		lib->unload();

		delete lib;
	}
	//############################################################################
	void PluginManager::unloadAllPlugins()
	{
		DynamicLib* lib;
		PluginMap::iterator iter = mPluginMap.begin();
		while(iter != mPluginMap.end()){
			lib = iter->second;
			//run stop plugin
			PluginManager::firePluginStop(lib);
			//detach the module
			lib->unload();
			delete lib;
			iter++;
		}

		mPluginMap.clear();
	}
	//############################################################################
	void PluginManager::firePluginStart(DynamicLib* lib)
	{
		PLUGIN_START_FUNC func;
		func = (PLUGIN_START_FUNC) lib->getSymbol("pluginSart");
		if(func)
			func();
	}
	//############################################################################
	void PluginManager::firePluginStop(DynamicLib* lib)
	{
		PLUGIN_STOP_FUNC func;
		func = (PLUGIN_STOP_FUNC) lib->getSymbol("pluginStop");
		if(func)
			func();
	}
	//############################################################################
	void PluginManager::_loadFromTinyXMLElement(void* tXelementPtr)
	{
		TiXmlElement* tXelement = (TiXmlElement*)tXelementPtr;
		const char* pluginFilename = 0;
		TiXmlAttribute* attrib = tXelement->FirstAttribute();
		if(attrib){
			do{
				if(0 == strcmpi(attrib->Name(),"file")){
					pluginFilename = attrib->Value();
					break;
				}
			}while(attrib = attrib->Next());
		}
		if(pluginFilename){
			loadPlugin(pluginFilename);
		}
	}
	//############################################################################
	void PluginManager::LoadPluginsFromXML(std::string xmlFilename)
	{
		TiXmlDocument doc;
		doc.LoadFile(xmlFilename);
		TiXmlElement* root = doc.RootElement();
		TiXmlElement* section;
		section = root;
		if(section){
			do{
				//iterate through all of the root level elements and react to every "Imageset" found
				if(0 == strcmpi(section->Value(),"Plugin")){
					PluginManager::_loadFromTinyXMLElement(section);
				}
			}while(section = section->NextSiblingElement());
		}

	}
	//############################################################################
};


