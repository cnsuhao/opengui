// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef C6B5FF01_4797_4ddd_A312_AE5468E80F5D
#define C6B5FF01_4797_4ddd_A312_AE5468E80F5D

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_String.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_XML.h"

namespace OpenGUI {
	class System; // forward declaration
	class DynamicLib; // forward declaration

	//! Plugin manager for tracking the proper loading and unloading of plugins.
	/*!
		\note
		All plugins are given a chance for notification when they are loaded and
		unloaded. Plugins that wish to receive this notification need to export:\n
		- void pluginStart(void);\n
		- void pluginStop(void);\n

		\remarks
		Depending on how %OpenGUI was configured when compiled the plugin system may
		perform varying degrees of filename mangling. An explanation and the current
		setting can be found in OpenGUI_CONFIG.h. To help explain how this works, the
		comment from that section of the config file is available \ref PMANGLE "here".

	*/
	class OPENGUI_API PluginManager : public Singleton<PluginManager> {
		friend class System; // so System can create/destroy
		PluginManager();
		~PluginManager();
	public:
		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static PluginManager& getSingleton( void );

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static PluginManager* getSingletonPtr( void );

		//! Loads a plugin by filename.
		void loadPlugin( String filename );

		//! Unloads a plugin by filename.
		void unloadPlugin( String filename );

		//! Unloads all currently loaded plugins
		void unloadAllPlugins();

	private:
		void firePluginStart( DynamicLib* lib );
		void firePluginStop( DynamicLib* lib );
		typedef std::map<String, DynamicLib*> PluginMap;
		PluginMap mPluginMap;

		// XML tag handlers for <Plugin> tags
		static bool _Plugin_XMLNode_Load( const XMLNode& node, const String& nodePath );
		static bool _Plugin_XMLNode_Unload( const XMLNode& node, const String& nodePath );
	};

}
;//namespace OpenGUI{

#endif


