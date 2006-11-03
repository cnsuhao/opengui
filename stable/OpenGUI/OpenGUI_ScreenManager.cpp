#include "OpenGUI_ScreenManager.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Screen.h"
#include "OpenGUI_LogSystem.h"
#include "OpenGUI_TimerManager.h"

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
		LogManager::SlogMsg( "INIT", OGLL_INFO2 ) << "Creating ScreenManager" << Log::endlog;
		/**/
		mTimer = TimerManager::getSingleton().getTimer();
		mFPSTimer = TimerManager::getSingleton().getTimer();
	}
	//############################################################################
	ScreenManager::~ScreenManager() {
		LogManager::SlogMsg( "SHUTDOWN", OGLL_INFO2 ) << "Destroying ScreenManager" << Log::endlog;
		destroyAllScreens();
	}
	//############################################################################
	Screen* ScreenManager::createScreen( const std::string& screenName, const FVector2& initialSize ) {
		Screen* tmp = getScreen( screenName );
		if ( tmp != 0 )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM,
					  "Screen by given name already exists:" + screenName, __FUNCTION__ );

		tmp = new Screen( screenName, initialSize );
		mScreenMap[screenName] = tmp;
		return tmp;
	}
	//############################################################################
	void ScreenManager::destroyScreen( Screen* screenPtr ) {
		Screen* tmp = getScreen( screenPtr->mName );
		ScreenMap::iterator iter = mScreenMap.find( screenPtr->mName );
		if ( iter == mScreenMap.end() )
			OG_THROW( Exception::ERR_INTERNAL_ERROR,
					  "Invalid Screen pointer", __FUNCTION__ );
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
			Screen* screen = iter->second;
			if ( screen->isAutoUpdating() )
				screen->update();
		}
		_stat_UpdateFPS();
	}
	//############################################################################
	void ScreenManager::updateTime() {
		unsigned int timepassed = mTimer->getMilliseconds();
		mTimer->reset();
		for ( ScreenMap::iterator iter = mScreenMap.begin();
				iter != mScreenMap.end(); iter++ ) {
			Screen* screen = iter->second;
			if ( screen->isAutoTiming() )
				screen->injectTime( timepassed );
		}

	}
	//############################################################################
	void ScreenManager::destroyAllScreens() {
		LogManager::SlogMsg( "ScreenManager", OGLL_INFO2 ) << "Destroy All Screens..." << Log::endlog;
		for ( ScreenMap::iterator iter = mScreenMap.begin();
				iter != mScreenMap.end(); iter++ ) {
			Screen* tmp = iter->second;
			iter->second = 0;
			delete tmp;
		}
		mScreenMap.clear();
	}
	//############################################################################
	void ScreenManager::_notifyViewportDimensionsChanged() {
		for ( ScreenMap::iterator iter = mScreenMap.begin();
				iter != mScreenMap.end(); iter++ ) {
			Screen* screen = iter->second;
			screen->_notifyViewportDimensionsChanged();
		}
	}
	//############################################################################
	void ScreenManager::_stat_UpdateFPS() {
		mStatFPS.addRecord( mFPSTimer->getSeconds() );
		mFPSTimer->reset();
	}
	//############################################################################
	float ScreenManager::statGetFPS() {
		return 1.0f / mStatFPS.getAverage();
	}
	//############################################################################
}//namespace OpenGUI{
