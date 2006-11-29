#ifndef Amethyst_ThemeManager_h__
#define Amethyst_ThemeManager_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"

namespace OpenGUI {
	namespace Amethyst {

		class AMETHYST_API ThemeManager: public Singleton<ThemeManager>{
		public:
			//Reimplementation required for this style of singleton implementation to work across DLLs
			//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
			static ThemeManager& getSingleton( void );

			//Reimplementation required for this style of singleton implementation to work across DLLs
			//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
			static ThemeManager* getSingletonPtr( void );
		};

	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_ThemeManager_h__
