#include "OpenGUI_ScreenManager.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Screen.h"

namespace OpenGUI {
	//############################################################################
	template<> ScreenManager* Singleton<ScreenManager>::mptr_Singleton = 0;
	//############################################################################
	ScreenManager& ScreenManager::getSingleton( void ) {
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	ScreenManager* ScreenManager::getSingletonPtr( void ) {
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	//############################################################################
	ScreenManager::ScreenManager() {
		/**/
	}
	//############################################################################
	ScreenManager::~ScreenManager() {
		/**/
	}
	//############################################################################
	Screen* ScreenManager::createScreen( const std::string& screenName, const FVector2& initialSize ) {
		Screen* tmp = getScreen( screenName );
		if ( tmp != 0 )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM,
					  "Screen by given name already exists:" + screenName, __FUNCTION__ );
		
		tmp = new Screen(screenName, initialSize);
		mScreenMap[screenName] = tmp;
		return tmp;
	}
	//############################################################################
	void ScreenManager::destroyScreen( Screen* screenPtr ) {
		
	}
	//############################################################################
	Screen* ScreenManager::getScreen( const std::string& screenName ) {
		ScreenMap::iterator iter = mScreenMap.find( screenName );
		if ( iter != mScreenMap.end() )
			return iter->second;
		return 0;
	}
	//############################################################################
	void ScreenManager::updateScreens() {
		for ( ScreenMap::iterator iter = mScreenMap.begin();
				iter != mScreenMap.end(); iter++ ) {
			iter->second->update();
		}
	}
	//############################################################################
}//namespace OpenGUI{
