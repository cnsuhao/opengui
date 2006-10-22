#ifndef DEA5BEFE_2592_4893_B0D2_AB7A54DF71A7
#define DEA5BEFE_2592_4893_B0D2_AB7A54DF71A7

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_Cursor.h"
#include "OpenGUI_Value.h"

namespace OpenGUI {
	class System; // forward declaration

	//! Cursor factory callback declaration/template
	typedef CursorPtr CursorFactoryCallback();

	class OPENGUI_API CursorManager : public Singleton<CursorManager> {
		friend class System; //so System can create and destroy us
		CursorManager(); // private constructor
		~CursorManager(); // private destructor
	public:
		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static CursorManager& getSingleton( void );

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static CursorManager* getSingletonPtr( void );

		//! Create a Cursor that was registered under the given \c Name and optionally \c Library
		CursorPtr CreateRawCursor( const std::string& Name, const std::string& Library = "" );

		//! Creates and initializes a cursor that was previously defined by DefineCursor()
		CursorPtr CreateDefinedCursor( const std::string& Name );

		//! Defines a new cursor under the given \c Name with the given \c propertyList, using \c BaseName and \c BaseLibrary as the source
		void DefineCursor( const std::string& Name, const ValueList& propertyList, const std::string& BaseName, const std::string& BaseLibrary );
		//! Undefines an existing cursor definition by \c Name
		void UndefineCursor( const std::string& Name );

		//! Register a Cursor factory
		void RegisterCursorFactory( const std::string& Name, const std::string& Library, CursorFactoryCallback* factoryCallback );
		//! Unregister a Cursor factory
		void UnregisterCursorFactory( const std::string& Name, const std::string& Library );

	private:
		typedef std::map<std::string, CursorFactoryCallback*> CursorFactoryMap;
		typedef std::map<std::string, CursorFactoryMap> LibraryMap;
		LibraryMap mLibraryMap;

		struct CursorDefinition {
			std::string Name;
			std::string Library;
			ValueList Properties;
		};
		typedef std::map<std::string, CursorDefinition> CursorDefinitionMap;
		CursorDefinitionMap mCursorDefinitionMap;
	};
} //namespace OpenGUI {
#endif // DEA5BEFE_2592_4893_B0D2_AB7A54DF71A7
