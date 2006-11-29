#include "Amethyst_ThemeManager.h"

namespace OpenGUI {

	// This has to be in the OpenGUI namespace because of the template it comes from
	template<> Amethyst::ThemeManager* Singleton<Amethyst::ThemeManager>::mptr_Singleton = 0;
	
	namespace Amethyst {		
		//############################################################################
		ThemeManager& ThemeManager::getSingleton( void ) {
			assert( mptr_Singleton );
			return ( *mptr_Singleton );
		}
		//############################################################################
		ThemeManager* ThemeManager::getSingletonPtr( void ) {
			return mptr_Singleton;
		}
		//############################################################################

	} // namespace Amethyst{
} // namespace OpenGUI{
