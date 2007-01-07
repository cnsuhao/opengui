// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_CursorManager.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_LogSystem.h"
#include "OpenGUI_GenericCursor.h"
#include "OpenGUI_XMLParser.h"

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
		XMLParser::getSingleton().RegisterLoadHandler( "CursorDef", &CursorManager::_CursorDef_XMLNode_Load );
		XMLParser::getSingleton().RegisterUnloadHandler( "CursorDef", &CursorManager::_CursorDef_XMLNode_Unload );

		// register generic cursor
		RegisterCursorFactory( "Generic", "OpenGUI", &GenericCursor::GenericCursorFactory );
	}
	//############################################################################
	CursorManager::~CursorManager() {
		LogManager::SlogMsg( "SHUTDOWN", OGLL_INFO2 ) << "Destroying CursorManager" << Log::endlog;

		// unregister generic cursor
		UnregisterCursorFactory( "Generic", "OpenGUI" );

		XMLParser::getSingleton().UnregisterLoadHandler( "CursorDef", &CursorManager::_CursorDef_XMLNode_Load );
		XMLParser::getSingleton().UnregisterUnloadHandler( "CursorDef", &CursorManager::_CursorDef_XMLNode_Unload );

		size_t w, l, d;
		getStats( w, l, d );
		LogManager::SlogMsg( "CursorManager", OGLL_INFO )
		<< "Stagnant Entries Tally - "
		<< "Registration (Cursor:Library): "
		<< "[" << w << ":" << l << "] "
		<< "Definitions: " << d
		<< Log::endlog;
	}
	//############################################################################
	/*! If \a Library is not given or is "", the value of \a Name will be tested to see
	if it is in a packed Name:Library format. If so then the packed value will be exploded and
	used, otherwise the full list of registered cursors is walked and the first entry with
	a matching \a Name is used. */
	CursorPtr CursorManager::CreateRawCursor( const String& Name, const String& Library ) {
		if ( Library == "" ) { // either packed Name:Library or just Name with first match
			size_t nPos;
			nPos = Name.find( ':' );
			if ( nPos != std::string::npos ) { // packed Name:Library, so explode and recall
				String NewName, NewLib;
				NewName = Name.substr( 0, nPos );
				NewLib = Name.substr( nPos + 1 );
				return CreateRawCursor( NewName, NewLib );
			} else { // if we weren't given a library then we need to search for first match by Name
				for ( LibraryMap::iterator iter = mLibraryMap.begin(); iter != mLibraryMap.end(); iter++ ) {
					CursorFactoryMap& fMap = iter->second;
					CursorFactoryMap::iterator iter2 = fMap.find( Name );
					if ( iter2 != fMap.end() ) {
						const String& Lib = iter->first;
						return CreateRawCursor( Name, Lib );
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
		cursor->mName = Name + ":" + Library;
		return cursor;
	}
	//############################################################################
	void CursorManager::RegisterCursorFactory( const String& Name, const String& Library,
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
	void CursorManager::UnregisterCursorFactory( const String& Name, const String& Library ) {
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
	void CursorManager::DefineCursor( const String& Name, const ValueList& propertyList,
									  const String& BaseName, const String& BaseLibrary ) {
		CursorDefinitionMap::iterator iter = mCursorDefinitionMap.find( Name );
		if ( iter != mCursorDefinitionMap.end() )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM, "Cursor already defined with given Name: " + Name, __FUNCTION__ );
		if ( BaseName.length() == 0 )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "BaseName cannot be 0 length", __FUNCTION__ );
		if ( BaseLibrary.length() == 0 )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "BaseLibrary cannot be 0 length", __FUNCTION__ );

		LogManager::SlogMsg( "CursorManager", OGLL_INFO ) << "Define Cursor: "
		<< Name << " -> " << BaseName << ":" << BaseLibrary
		<< Log::endlog;

		CursorDefinition& cd = mCursorDefinitionMap[Name];
		cd.Name = BaseName;
		cd.Library = BaseLibrary;
		cd.Properties = propertyList;
	}
	//############################################################################
	void CursorManager::UndefineCursor( const String& Name ) {
		CursorDefinitionMap::iterator iter = mCursorDefinitionMap.find( Name );
		if ( iter == mCursorDefinitionMap.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "No Cursor defined with given Name: " + Name, __FUNCTION__ );
		LogManager::SlogMsg( "CursorManager", OGLL_INFO ) << "Undefine Cursor: " << Name << Log::endlog;
		mCursorDefinitionMap.erase( iter );
	}
	//############################################################################
	CursorPtr CursorManager::CreateDefinedCursor( const String& Name ) {
		CursorDefinitionMap::iterator iter = mCursorDefinitionMap.find( Name );
		if ( iter == mCursorDefinitionMap.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "No Cursor defined with given Name: " + Name, __FUNCTION__ );
		CursorDefinition& cd = iter->second;
		CursorPtr cursor = CreateRawCursor( cd.Name, cd.Library );
		ValueList proplist = cd.Properties;
		while ( proplist.size() > 0 ) {
			Value val = proplist.pop_front();
			if ( val.getName().length() > 0 ) {
				cursor->setProperty( val.getName(), val );
			}
		}
		cursor->mName = Name;
		return cursor;
	}
	//############################################################################
	CursorManager::CursorRegPairList CursorManager::GetRegisteredCursors() {
		CursorRegPairList retval;
		for ( LibraryMap::iterator iter = mLibraryMap.begin(); iter != mLibraryMap.end(); iter++ ) {
			String LibName = iter->first;
			CursorFactoryMap& factoryMap = iter->second;
			for ( CursorFactoryMap::iterator iter = factoryMap.begin(); iter != factoryMap.end(); iter++ ) {
				String BaseName = iter->first;
				retval.push_back( CursorRegPair( BaseName, LibName ) );
			}
		}
		return retval;
	}
	//############################################################################
	CursorManager::CursorDefList CursorManager::GetDefinedCursors() {
		CursorDefList retval;
		for ( CursorDefinitionMap::iterator iter = mCursorDefinitionMap.begin(); iter != mCursorDefinitionMap.end(); iter++ ) {
			retval.push_back( iter->first );
		}
		return retval;
	}
	//############################################################################
	void CursorManager::getStats( size_t& RegCursors, size_t& RegLibs, size_t& DefCursors ) {
		RegLibs = 0;
		RegCursors = 0;
		for ( LibraryMap::iterator iter = mLibraryMap.begin(); iter != mLibraryMap.end(); iter++ ) {
			bool hadValue = false;
			CursorFactoryMap& factoryMap = iter->second;
			for ( CursorFactoryMap::iterator iter = factoryMap.begin(); iter != factoryMap.end(); iter++ ) {
				hadValue = true;
				RegCursors++;
			}
			if ( hadValue ) RegLibs++;
		}

		DefCursors = 0;
		for ( CursorDefinitionMap::iterator iter = mCursorDefinitionMap.begin(); iter != mCursorDefinitionMap.end(); iter++ ) {
			DefCursors++;
		}
	}
	//############################################################################
	bool CursorManager::_CursorDef_XMLNode_Load( const XMLNode& node, const String& nodePath ) {
		CursorManager& manager = CursorManager::getSingleton();

		// we only handle these tags within <OpenGUI>
		if ( nodePath != "/OpenGUI/" )
			return false;

		const String name = node.getAttribute( "Name" );
		const String basename = node.getAttribute( "BaseName" );
		const String baselib = node.getAttribute( "BaseLibrary" );
		ValueList propertyList;
		XMLNodeList xmlProps = node.getChildren( "Property" );
		for ( XMLNodeList::iterator iter = xmlProps.begin(); iter != xmlProps.end(); iter++ ) {
			XMLNode* prop = ( *iter );
			Value value;
			value.LoadFromXMLNode( *prop );
			propertyList.push_back( value );
		}
		manager.DefineCursor( name, propertyList, basename, baselib );
		return true;
	}
	//############################################################################
	bool CursorManager::_CursorDef_XMLNode_Unload( const XMLNode& node, const String& nodePath ) {
		CursorManager& manager = CursorManager::getSingleton();

		// we only handle these tags within <OpenGUI>
		if ( nodePath != "/OpenGUI/" )
			return false;

		const String name = node.getAttribute( "Name" );
		const String basename = node.getAttribute( "BaseName" );
		const String baselib = node.getAttribute( "BaseLibrary" );
		manager.UndefineCursor( name );
		return true;
	}
	//############################################################################
}//namespace OpenGUI {
