#include "OpenGUI.h"


namespace OpenGUI {
	//############################################################################
	template<> WidgetFactoryManager* Singleton<WidgetFactoryManager>::mptr_Singleton = 0;
	//############################################################################
	WidgetFactoryManager& WidgetFactoryManager::getSingleton( void ) {
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	WidgetFactoryManager* WidgetFactoryManager::getSingletonPtr( void ) {
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	//############################################################################
	WidgetFactoryManager::WidgetFactoryManager() {
		//
		LogManager::SlogMsg( "INIT", OGLL_INFO2 ) << "Creating WidgetFactoryManager" << Log::endlog;
	}
	//############################################################################
	WidgetFactoryManager::~WidgetFactoryManager() {
		//
		LogManager::SlogMsg( "SHUTDOWN", OGLL_INFO2 ) << "Destroying WidgetFactoryManager" << Log::endlog;
	}
	//############################################################################
	void WidgetFactoryManager::registerWidgetFactory( std::string groupName, std::string widgetName, WidgetFactoryCallback factoryCallback ) {
		LogManager::SlogMsg( "WidgetFactoryManager", OGLL_INFO ) << "RegisterWidgetFactory: ";
		LogManager::SlogMsg( "WidgetFactoryManager", OGLL_INFO ) << groupName << "/" << widgetName << " <" << (( void* )( factoryCallback ) ) << ">" << Log::endlog;

		CallbackMapItem item;
		item.callBack = factoryCallback;
		item.groupName = groupName;
		item.widgetName = widgetName;
		mCallbackmap[_buildGroupNameComposite( groupName,widgetName )] = item;
	}
	//############################################################################
	void WidgetFactoryManager::unregisterWidgetFactory( std::string groupName, std::string widgetName ) {
		LogManager::SlogMsg( "WidgetFactoryManager", OGLL_INFO ) << "UnregisterWidgetFactory: ";
		LogManager::SlogMsg( "WidgetFactoryManager", OGLL_INFO ) << groupName << "/" << widgetName << Log::endlog;

		CallbackMap::iterator iter = mCallbackmap.find( _buildGroupNameComposite( groupName, widgetName ) );
		if ( iter != mCallbackmap.end() ) {
			mCallbackmap.erase( iter );
			return;
		}
		OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Could not find widget factory to unregister " + groupName + "/" + widgetName, "WidgetFactoryManager::unregisterWidgetFactory" );
	}
	//############################################################################
	Widgets::Widget* WidgetFactoryManager::createWidget( std::string groupName, std::string widgetName ) {
		LogManager::SlogMsg( "WidgetFactoryManager", OGLL_INFO3 ) << "CreateWidget: ";
		LogManager::SlogMsg( "WidgetFactoryManager", OGLL_INFO3 ) << groupName << "/" << widgetName << Log::endlog;

		CallbackMap::iterator iter = mCallbackmap.find( _buildGroupNameComposite( groupName, widgetName ) );
		if ( iter != mCallbackmap.end() ) {
			//call me paranoid, but i'm going to check again just to make sure
			if ( iter->second.groupName == groupName && iter->second.widgetName == widgetName ) {
				try { //If func is unknown/garbage the result is undefined? you bet! but hey, we've got faith.
					WidgetFactoryCallback func;
					func = iter->second.callBack;
					return ( *func )();
				} catch ( ... ) {
					return 0;
				}
			}
		}
		return 0;
	}
	//############################################################################
	std::string WidgetFactoryManager::_buildGroupNameComposite( const std::string& groupName, const std::string& widgetName ) {
		std::stringstream ss;
		ss << groupName << ":" << widgetName;
		return ss.str();
	}
	//############################################################################
	//! Internal predicate function for sorting WidgetFactoryLists
	struct SortWidgetFactoryList {
		//return left < right
		bool operator()( const WidgetFactoryManager::WidgetFactoryListItem& left,
						 const WidgetFactoryManager::WidgetFactoryListItem& right ) {
			if ( left.WidgetGroup < right.WidgetGroup )
				return true;
			if ( left.WidgetGroup == right.WidgetGroup && left.WidgetName < right.WidgetName )
				return true;
			return false;
		}
	};
	//############################################################################
	WidgetFactoryManager::WidgetFactoryList WidgetFactoryManager::getWidgetFactoryList() {
		WidgetFactoryList retval;
		for ( CallbackMap::iterator iter = mCallbackmap.begin(); iter != mCallbackmap.end(); iter++ ) {
			WidgetFactoryListItem item;
			item.WidgetGroup = iter->second.groupName;
			item.WidgetName = iter->second.widgetName;
			retval.push_back( item );
		}
		retval.sort( SortWidgetFactoryList() );
		return retval;
	}
	//############################################################################
}
; //namespace OpenGUI{


