#include "OpenGUI_WidgetManager.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_LogSystem.h"
#include "OpenGUI_Widget.h"

namespace OpenGUI {
	template<> WidgetManager* Singleton<WidgetManager>::mptr_Singleton = 0;
	WidgetManager& WidgetManager::getSingleton( void ) {
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	WidgetManager* WidgetManager::getSingletonPtr( void ) {
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	//############################################################################
	WidgetManager::WidgetManager() {
		LogManager::SlogMsg( "INIT", OGLL_INFO2 ) << "Creating WidgetManager" << Log::endlog;
	}
	//############################################################################
	WidgetManager::~WidgetManager() {
		LogManager::SlogMsg( "SHUTDOWN", OGLL_INFO2 ) << "Destroying WidgetManager" << Log::endlog;
	}
	//############################################################################
	/*! If \a Library is not given or is "", the value of \a Name will be tested to see
	if it is in a packed Name:Library format. If so then the packed value will be exploded and
	used, otherwise the full list of registered cursors is walked and the first entry with
	a matching \a Name is used. */
	Widget* WidgetManager::CreateRawWidget( const std::string& Name, const std::string& Library ) {
		if ( Library == "" ) { // either packed Name:Library or just Name with first match
			size_t nPos;
			nPos = Name.find( ':' );
			if ( nPos != std::string::npos ) { // packed Name:Library, so explode and recall
				std::string NewName, NewLib;
				NewName = Name.substr( 0, nPos );
				NewLib = Name.substr( nPos + 1 );
				return CreateRawWidget( NewName, NewLib );
			} else { // if we weren't given a library then we need to search for first match by Name
				for ( LibraryMap::iterator iter = mLibraryMap.begin(); iter != mLibraryMap.end(); iter++ ) {
					WidgetFactoryMap& fMap = iter->second;
					WidgetFactoryMap::iterator iter2 = fMap.find( Name );
					if ( iter2 != fMap.end() ) {
						const std::string& Lib = iter->first;
						return CreateRawWidget( Name, Lib );
					}
				}
				OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "No Widget registered with Name: " + Name, __FUNCTION__ );
			}
		}
		WidgetFactoryMap& fMap = mLibraryMap[Library];
		WidgetFactoryMap::iterator iter = fMap.find( Name );
		if ( iter == fMap.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Widget not registered: " + Name + ":" + Library, __FUNCTION__ );
		WidgetFactoryCallback* callback = iter->second;
		Widget* widget = ( *callback )();
		return widget;
	}
	//############################################################################
	void WidgetManager::RegisterWidgetFactory( const std::string& Name, const std::string& Library,
			WidgetFactoryCallback* factoryCallback ) {
		size_t nPos, lPos;
		nPos = Name.find( ':' );
		lPos = Library.find( ':' );
		if ( nPos != std::string::npos || lPos != std::string::npos )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Separator character ':' is not allowed in Name or Library", __FUNCTION__ );
		if ( Name.length() == 0 )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Name cannot be 0 length", __FUNCTION__ );
		if ( Library.length() == 0 )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Library cannot be 0 length", __FUNCTION__ );

		WidgetFactoryMap& fMap = mLibraryMap[Library];

		WidgetFactoryMap::iterator iter = fMap.find( Name );
		if ( iter != fMap.end() )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM, "Widget already registered: " + Name + ":" + Library, __FUNCTION__ );
		LogManager::SlogMsg( "WidgetManager", OGLL_INFO ) << "Register Widget: "
		<< Name << ":" << Library
		<< Log::endlog;
		fMap[Name] = factoryCallback;
	}
	//############################################################################
	void WidgetManager::UnregisterWidgetFactory( const std::string& Name, const std::string& Library ) {
		size_t nPos, lPos;
		nPos = Name.find( ':' );
		lPos = Library.find( ':' );
		if ( nPos != std::string::npos || lPos != std::string::npos )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Separator character ':' is not allowed in Name or Library", __FUNCTION__ );
		if ( Name.length() == 0 )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Name cannot be 0 length", __FUNCTION__ );
		if ( Library.length() == 0 )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Library cannot be 0 length", __FUNCTION__ );

		WidgetFactoryMap& fMap = mLibraryMap[Library];
		WidgetFactoryMap::iterator iter = fMap.find( Name );
		if ( iter == fMap.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Widget not registered: " + Name + ":" + Library, __FUNCTION__ );

		LogManager::SlogMsg( "WidgetManager", OGLL_INFO ) << "Unregister Widget: "
		<< Name << ":" << Library
		<< Log::endlog;
		fMap.erase( iter );
	}
	//############################################################################
	void WidgetManager::DefineWidget( const std::string& Name, const ValueList& propertyList,
									  const std::string& BaseName, const std::string& BaseLibrary ) {
		WidgetDefinitionMap::iterator iter = mWidgetDefinitionMap.find( Name );
		if ( iter != mWidgetDefinitionMap.end() )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM, "Widget already defined with given Name: " + Name, __FUNCTION__ );
		if ( BaseName.length() == 0 )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "BaseName cannot be 0 length", __FUNCTION__ );
		if ( BaseLibrary.length() == 0 )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "BaseLibrary cannot be 0 length", __FUNCTION__ );

		LogManager::SlogMsg( "WidgetManager", OGLL_INFO ) << "Define Widget: "
		<< Name << " -> " << BaseName << ":" << BaseLibrary
		<< Log::endlog;

		WidgetDefinition& wd = mWidgetDefinitionMap[Name];
		wd.Name = BaseName;
		wd.Library = BaseLibrary;
		wd.Properties = propertyList;
	}
	//############################################################################
	void WidgetManager::UndefineWidget( const std::string& Name ) {
		WidgetDefinitionMap::iterator iter = mWidgetDefinitionMap.find( Name );
		if ( iter == mWidgetDefinitionMap.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "No Widget defined with given Name: " + Name, __FUNCTION__ );
		LogManager::SlogMsg( "WidgetManager", OGLL_INFO ) << "Undefine Cursor: " << Name << Log::endlog;
		mWidgetDefinitionMap.erase( iter );
	}
	//############################################################################
	Widget* WidgetManager::CreateDefinedWidget( const std::string& Name ) {
		WidgetDefinitionMap::iterator iter = mWidgetDefinitionMap.find( Name );
		if ( iter == mWidgetDefinitionMap.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "No Widget defined with given Name: " + Name, __FUNCTION__ );
		WidgetDefinition& wd = iter->second;
		Widget* widget = CreateRawWidget( wd.Name, wd.Library );
		ValueList proplist = wd.Properties;
		while ( proplist.size() > 0 ) {
			Value val = proplist.pop_front();
			if ( val.getName().length() > 0 ) {
				widget->setProperty( val.getName(), val );
			}
		}
		return widget;
	}
	//############################################################################
}//namespace OpenGUI{
