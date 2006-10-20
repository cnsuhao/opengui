#include "OpenGUI_CursorManager.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	template<> CursorManager* Singleton<CursorManager>::mptr_Singleton = 0;
	CursorManager& CursorManager::getSingleton( void ) {
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	CursorManager* CursorManager::getSingletonPtr( void ) {
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	//############################################################################
	CursorManager::CursorManager() {
		/**/
	}
	//############################################################################
	CursorManager::~CursorManager() {
		/**/
	}
	//############################################################################
	/*! */
	CursorPtr CursorManager::CreateCursor( const std::string& Name, const std::string& Library ) {
		CursorFactoryMap& fMap = mLibraryMap[Library];
		CursorFactoryMap::iterator iter = fMap.find(Name);
		if(iter == fMap.end())
			OG_THROW(Exception::ERR_ITEM_NOT_FOUND, "Cursor not registered: " + Name + ":" + Library,__FUNCTION__);
		CursorFactoryCallback* callback = iter->second;
		CursorPtr cursor = ( *callback )();
		return cursor;
	}
	//############################################################################
	void CursorManager::RegisterCursorFactory( const std::string& Name, const std::string& Library,
			CursorFactoryCallback* factoryCallback ) {
		size_t nPos, lPos;
		nPos = Name.find( ':' );
		lPos = Library.find( ':' );
		if ( nPos != std::string::npos || lPos != std::string::npos )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Separator character ':' is not allowed in Name or Library", __FUNCTION__ );
		if ( Name.length() == 0 )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Name cannot be 0 length", __FUNCTION__ );
		if ( Library.length() == 0 )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Library cannot be 0 length", __FUNCTION__ );

		CursorFactoryMap& fMap = mLibraryMap[Library];

		CursorFactoryMap::iterator iter = fMap.find( Name );
		if ( iter != fMap.end() )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM, "Cursor already registered: " + Name + ":" + Library, __FUNCTION__ );
		fMap[Name] = factoryCallback;
	}
	//############################################################################
	void CursorManager::UnregisterCursorFactory( const std::string& Name, const std::string& Library ) {
		CursorFactoryMap& fMap = mLibraryMap[Library];
		CursorFactoryMap::iterator iter = fMap.find( Name );
		if ( iter == fMap.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Cursor not registered: " + Name + ":" + Library, __FUNCTION__ );
		fMap.erase( iter );
	}
	//############################################################################
}//namespace OpenGUI {
