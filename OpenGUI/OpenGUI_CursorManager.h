#ifndef DEA5BEFE_2592_4893_B0D2_AB7A54DF71A7
#define DEA5BEFE_2592_4893_B0D2_AB7A54DF71A7

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_Cursor.h"

namespace OpenGUI {
	class System; // forward declaration

	//! Cursor factory callback declaration/template
	typedef CursorPtr CursorFactoryCallback();

	class OPENGUI_API CursorManager : public Singleton<CursorManager> {
		friend class System; //so System can create and destroy us
		CursorManager();
		~CursorManager();
	public:
		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static CursorManager& getSingleton( void );

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static CursorManager* getSingletonPtr( void );
		
		//! Create a Cursor that was registered under the given \c Name and optionally \c Library
		CursorPtr CreateCursor(const std::string& Name, const std::string& Library="");
		//! Register a Cursor factory
		void RegisterCursorFactory(const std::string& Name, const std::string& Library, CursorFactoryCallback* factoryCallback);
		//! Unregister a Cursor factory
		void UnregisterCursorFactory(const std::string& Name, const std::string& Library);

	private:
		
		typedef std::map<std::string, CursorFactoryCallback*> CursorFactoryMap;
		typedef std::map<std::string, CursorFactoryMap> LibraryMap;
		LibraryMap mLibraryMap;
	};
} //namespace OpenGUI {
#endif // DEA5BEFE_2592_4893_B0D2_AB7A54DF71A7
