// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef DEA5BEFE_2592_4893_B0D2_AB7A54DF71A7
#define DEA5BEFE_2592_4893_B0D2_AB7A54DF71A7

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_String.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_Cursor.h"
#include "OpenGUI_Value.h"
#include "OpenGUI_XML.h"

namespace OpenGUI {
	class System; // forward declaration

	//! Cursor factory callback declaration/template
	typedef CursorPtr CursorFactoryCallback();

	//! Provides Cursor registration and definition functionality
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
		CursorPtr CreateRawCursor( const String& Name, const String& Library = "" );

		//! Creates and initializes a cursor that was previously defined by DefineCursor()
		CursorPtr CreateDefinedCursor( const String& Name );

		//! Defines a new cursor under the given \c Name with the given \c propertyList, using \c BaseName and \c BaseLibrary as the source
		void DefineCursor( const String& Name, const ValueList& propertyList, const String& BaseName, const String& BaseLibrary );
		//! Undefines an existing cursor definition by \c Name
		void UndefineCursor( const String& Name );

		//! Register a Cursor factory
		void RegisterCursorFactory( const String& Name, const String& Library, CursorFactoryCallback* factoryCallback );
		//! Unregister a Cursor factory
		void UnregisterCursorFactory( const String& Name, const String& Library );

		//! inner type of CursorRegPairList
		typedef std::pair<String, String> CursorRegPair;
		//! return type of GetRegisteredCursors()
		typedef std::list<CursorRegPair> CursorRegPairList;
		//! returns a pair list of all registered Cursors
		CursorRegPairList GetRegisteredCursors();

		//! return type of GetDefinedCursors()
		typedef std::list<String> CursorDefList;
		//! returns a list of all defined Cursors
		CursorDefList GetDefinedCursors();

		//! returns the number of registered widgets across the number of libraries, as well as the number of widget definitions
		void getStats( size_t& RegWidgets, size_t& RegLibs, size_t& DefWidgets );

	private:
		typedef std::map<String, CursorFactoryCallback*> CursorFactoryMap;
		typedef std::map<String, CursorFactoryMap> LibraryMap;
		LibraryMap mLibraryMap;

		struct CursorDefinition {
			String Name;
			String Library;
			ValueList Properties;
		};
		typedef std::map<String, CursorDefinition> CursorDefinitionMap;
		CursorDefinitionMap mCursorDefinitionMap;

		// XML tag handlers for <CursorDef> tags
		static bool _CursorDef_XMLNode_Load( const XMLNode& node, const String& nodePath );
		static bool _CursorDef_XMLNode_Unload( const XMLNode& node, const String& nodePath );
	};
} //namespace OpenGUI {
#endif // DEA5BEFE_2592_4893_B0D2_AB7A54DF71A7
