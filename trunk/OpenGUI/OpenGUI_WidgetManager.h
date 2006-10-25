#ifndef DCA429BB_8BCE_4042_A4DA_558D1A0AAE00
#define DCA429BB_8BCE_4042_A4DA_558D1A0AAE00

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_Value.h"

namespace OpenGUI {
	class System; // forward declaration
	class Widget; // forward declaration

	//! Widget factory callback declaration/template
	typedef Widget* WidgetFactoryCallback();

	//! Provides Widget registration and definition functionality
	class OPENGUI_API WidgetManager : public Singleton<WidgetManager> {
		friend class System; //so System can create and destroy us
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
	};
}//namespace OpenGUI{

#endif // DCA429BB_8BCE_4042_A4DA_558D1A0AAE00
