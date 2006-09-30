#include "OpenGUI_ScreenManager.h"

namespace OpenGUI{
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
	ScreenManager::ScreenManager(){
		/**/
	}
	//############################################################################
	ScreenManager::~ScreenManager(){
		/**/
	}
	//############################################################################
}//namespace OpenGUI{