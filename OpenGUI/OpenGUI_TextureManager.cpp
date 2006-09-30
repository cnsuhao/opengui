#include "OpenGUI_TextureManager.h"

namespace OpenGUI{
	//############################################################################
	template<> TextureManager* Singleton<TextureManager>::mptr_Singleton = 0;
	//############################################################################
	TextureManager& TextureManager::getSingleton( void ) {
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	TextureManager* TextureManager::getSingletonPtr( void ) {
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	//############################################################################
	TextureManager::TextureManager( Renderer* renderer ){
		mRenderer = renderer;
	}
	//############################################################################
	TextureManager::~TextureManager(){
		/**/
	}
	//############################################################################
}//namespace OpenGUI{