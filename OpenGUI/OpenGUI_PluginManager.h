#ifndef C6B5FF01_4797_4ddd_A312_AE5468E80F5D
#define C6B5FF01_4797_4ddd_A312_AE5468E80F5D

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_DynamicLib.h"

namespace OpenGUI{

	//! Plugin manager for tracking the proper loading and unloading of plugins.
	/*!
		\note
		All plugins are given a chance for notification when they are loaded and
		unloaded. Plugins that wish to receive this notification need to export:\n
		- void pluginStart(void);\n
		- void pluginStop(void);\n
		
	*/
	class PluginManager : public Singleton<PluginManager>{
		friend class XMLParser;
	public:
		PluginManager();
		~PluginManager();

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static PluginManager& getSingleton(void);

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static PluginManager* getSingletonPtr(void);

		//! Loads a plugin by filename.
		void loadPlugin(std::string filename);
		//! Unloads a plugin by filename.
		void unloadPlugin(std::string filename);
		//! Unloads all currently loaded plugins
		void unloadAllPlugins();

		//! Loads plugins as defined by an xml file.
		void LoadPluginsFromXML(std::string xmlFilename);
	private:
		void _loadFromTinyXMLElement(void* tXelementPtr);
		static void firePluginStart(DynamicLib* lib);
		static void firePluginStop(DynamicLib* lib);
		typedef std::map<std::string,DynamicLib*> PluginMap;
		PluginMap mPluginMap;
	};

};//namespace OpenGUI{

#endif


