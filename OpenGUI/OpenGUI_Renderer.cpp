
#include "OpenGUI_Renderer.h"

namespace OpenGUI {
	//############################################################################
	template<> Renderer* Singleton<Renderer>::mptr_Singleton = 0;
	//############################################################################
	Renderer& Renderer::getSingleton( void ) {
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	Renderer* Renderer::getSingletonPtr( void ) {
		return mptr_Singleton;
	}
	//############################################################################
};

