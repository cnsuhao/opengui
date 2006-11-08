#ifndef DCA429BB_8BCE_4042_A4DA_558D1A0AAE00
#define DCA429BB_8BCE_4042_A4DA_558D1A0AAE00

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_Value.h"
#include "OpenGUI_XML.h"

namespace OpenGUI {
	class System; // forward declaration
	class Widget; // forward declaration
	class ScreenManager; // forward declaration
	class I_WidgetContainer; // forward declaration

	//! Widget factory callback declaration/template
	typedef Widget* WidgetFactoryCallback();

	//! Provides Widget registration and definition functionality
	class OPENGUI_API WidgetManager : public Singleton<WidgetManager> {
		friend class System; //so System can create and destroy us
		friend class ScreenManager; // need access via ScreenManager::_Screen_XMLNode_Load()
		WidgetManager(); // private constructor
		~WidgetManager(); // private destructor
	public:
		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static WidgetManager& getSingleton( void );

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static WidgetManager* getSingletonPtr( void );

		//! Create a Widget that was registered under the given \c Name and optionally \c Library
		Widget* CreateRawWidget( const std::string& Name, const std::string& Library = "" );

		//! Creates and initializes a Widget that was previously defined by DefineWidget()
		Widget* CreateDefinedWidget( const std::string& Name );

		//! Defines a new Widget under the given \c Name with the given \c propertyList, using \c BaseName and \c BaseLibrary as the source
		void DefineWidget( const std::string& Name, const ValueList& propertyList, const std::string& BaseName, const std::string& BaseLibrary );
		//! Undefines an existing Widget definition by \c Name
		void UndefineWidget( const std::string& Name );

		//! Register a Widget factory
		void RegisterWidgetFactory( const std::string& Name, const std::string& Library, WidgetFactoryCallback* factoryCallback );
		//! Unregister a Widget factory
		void UnregisterWidgetFactory( const std::string& Name, const std::string& Library );

		//! inner type of WidgetRegPairList
		typedef std::pair<std::string, std::string> WidgetRegPair;
		//! return type of GetRegisteredWidgets()
		typedef std::list<WidgetRegPair> WidgetRegPairList;
		//! returns a pair list of all registered widgets
		WidgetRegPairList GetRegisteredWidgets();

		//! return type of GetDefinedWidgets()
		typedef std::list<std::string> WidgetDefList;
		//! returns a list of all defined widgets
		WidgetDefList GetDefinedWidgets();

		//! returns the number of registered widgets across the number of libraries, as well as the number of widget definitions
		void getStats( size_t& RegWidgets, size_t& RegLibs, size_t& DefWidgets );

	private:
		typedef std::map<std::string, WidgetFactoryCallback*> WidgetFactoryMap;
		typedef std::map<std::string, WidgetFactoryMap> LibraryMap;
		LibraryMap mLibraryMap;

		struct WidgetDefinition {
			std::string Name;
			std::string Library;
			ValueList Properties;
		};
		typedef std::map<std::string, WidgetDefinition> WidgetDefinitionMap;
		WidgetDefinitionMap mWidgetDefinitionMap;

		// XML tag handlers for <WidgetDef> tags
		static bool _WidgetDef_XMLNode_Load( const XMLNode& node, const std::string& nodePath );
		static bool _WidgetDef_XMLNode_Unload( const XMLNode& node, const std::string& nodePath );
		static void _Widget_XMLNode_IntoContainer( const XMLNode& widgetNode, I_WidgetContainer& widgetContainer );
	};
}//namespace OpenGUI{

#endif // DCA429BB_8BCE_4042_A4DA_558D1A0AAE00
