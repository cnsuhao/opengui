#include "tinyxml.h"

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_LogSystem.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_DynamicLib.h"
#include "OpenGUI_PluginManager.h"
#include "OpenGUI_System.h"
#include "OpenGUI_ResourceProvider.h"
#include "OpenGUI_Resource.h"

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
		LogManager::SlogMsg("INIT", OGLL_INFO2) << "Created PluginManager" << Log::endlog;
	}
	//############################################################################
	PluginManager::~PluginManager()
	{
		LogManager::SlogMsg("SHUTDOWN", OGLL_INFO2) << "Destroying PluginManager" << Log::endlog;
		PluginManager::unloadAllPlugins();
	}
	//############################################################################
	void PluginManager::loadPlugin(std::string filename)
	{
		LogManager::SlogMsg("PluginManager", OGLL_INFO2) << "LoadPlugin: " << filename << Log::endlog;

		PluginMap::iterator iter = mPluginMap.find(filename);
		if(iter != mPluginMap.end()){
			OG_THROW(Exception::ERR_DUPLICATE_ITEM, "Plugin already loaded: " + filename, "PluginManager::loadPlugin");
		}

		//attach the module
		DynamicLib* lib = new DynamicLib(filename);
		if(!lib)
			return;

		try{
			lib->load();
		}catch(Exception e){
			delete lib;
			return;
		}

		mPluginMap[filename] = lib;

		//run start plugin
		PluginManager::firePluginStart(lib);
	}
	//############################################################################
	void PluginManager::unloadPlugin(std::string filename)
	{
		LogManager::SlogMsg("PluginManager", OGLL_INFO2) << "UnloadPlugin: " << filename << Log::endlog;

		DynamicLib* lib;
		PluginMap::iterator iter = mPluginMap.find(filename);
		if(iter == mPluginMap.end()){
			OG_THROW(Exception::ERR_ITEM_NOT_FOUND, "Plugin not found in list of loaded plugins: " + filename, "PluginManager::unloadPlugin");
		}

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
		LogManager::SlogMsg("PluginManager", OGLL_INFO2) << "UnloadAllPlugins..."  << Log::endlog;

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
		LogManager::SlogMsg("PluginManager", OGLL_INFO3) << "firePluginStart: " << lib->getName() << Log::endlog;

		PLUGIN_START_FUNC func;
		func = (PLUGIN_START_FUNC) lib->getSymbol("pluginStart");
		if(func)
			func();
	}
	//############################################################################
	void PluginManager::firePluginStop(DynamicLib* lib)
	{
		LogManager::SlogMsg("PluginManager", OGLL_INFO3) << "firePluginStop: " << lib->getName() << Log::endlog;

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
			}while( (attrib = attrib->Next()) );
		}
		if(pluginFilename){
			loadPlugin(pluginFilename);
		}
	}
	//############################################################################
	void PluginManager::LoadPluginsFromXML(std::string xmlFilename)
	{
		LogManager::SlogMsg("PluginManager", OGLL_INFO) << "LoadPluginsFromXML: " << xmlFilename << Log::endlog;

		TiXmlDocument doc;
		//doc.LoadFile(xmlFilename);
		Resource_CStr res;
		ResourceProvider* resProvider = System::getSingleton()._getResourceProvider();
		resProvider->loadResource(xmlFilename, res);
		doc.Parse(res.getString());
		TiXmlElement* root = doc.RootElement();
		TiXmlElement* section;
		section = root;
		if(section){
			do{
				//iterate through all of the root level elements and react to every "Imageset" found
				if(0 == strcmpi(section->Value(),"Plugin")){
					PluginManager::_loadFromTinyXMLElement(section);
				}
			}while( (section = section->NextSiblingElement()) );
		}

	}
	//############################################################################
};


