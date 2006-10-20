#include "OpenGUI_CursorManager.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_LogSystem.h"

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
		LogManager::SlogMsg( "INIT", OGLL_INFO2 ) << "Creating CursorManager" << Log::endlog;
	}
	//############################################################################
	CursorManager::~CursorManager() {
		LogManager::SlogMsg( "SHUTDOWN", OGLL_INFO2 ) << "Destroying CursorManager" << Log::endlog;
	}
	//############################################################################
	/*! */
	CursorPtr CursorManager::CreateCursor( const std::string& Name, const std::string& Library ) {
		if ( Library == "" ) { // either packed Name:Library or just Name with first match
			size_t nPos;
			nPos = Name.find( ':' );
			if ( nPos != std::string::npos ) { // packed Name:Library, so explode and recall
				std::string NewName, NewLib;
				NewName = Name.substr( 0, nPos );
				NewLib = Name.substr( nPos + 1 );
				return CreateCursor( NewName, NewLib );
			} else { // if we weren't given a library then we need to search for first match by Name
				for ( LibraryMap::iterator iter = mLibraryMap.begin(); iter != mLibraryMap.end(); iter++ ) {
					CursorFactoryMap& fMap = iter->second;
					CursorFactoryMap::iterator iter2 = fMap.find( Name );
					if ( iter2 != fMap.end() ) {
						const std::string& Lib = iter->first;
						return CreateCursor( Name, Lib );
					}
				}
				OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "No Cursor registered with Name: " + Name, __FUNCTION__ );
			}
		}
		CursorFactoryMap& fMap = mLibraryMap[Library];
		CursorFactoryMap::iterator iter = fMap.find( Name );
		if ( iter == fMap.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Cursor not registered: " + Name + ":" + Library, __FUNCTION__ );
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
		LogManager::SlogMsg( "CursorManager", OGLL_INFO ) << "Register Cursor: "
		<< Name << ":" << Library
		<< Log::endlog;
		fMap[Name] = factoryCallback;
	}
	//############################################################################
	void CursorManager::UnregisterCursorFactory( const std::string& Name, const std::string& Library ) {
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
		if ( iter == fMap.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Cursor not registered: " + Name + ":" + Library, __FUNCTION__ );

		LogManager::SlogMsg( "CursorManager", OGLL_INFO ) << "Unregister Cursor: "
		<< Name << ":" << Library
		<< Log::endlog;
		fMap.erase( iter );
	}
	//############################################################################
}//namespace OpenGUI {
