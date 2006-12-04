#ifndef Amethyst_ThemeManager_h__
#define Amethyst_ThemeManager_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"
#include "Amethyst_Theme.h"

namespace OpenGUI {
	namespace Amethyst {

		class AMETHYST_API ThemeManager: public Singleton<ThemeManager> {
		public:
			//Reimplementation required for this style of singleton implementation to work across DLLs
			//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
			static ThemeManager& getSingleton( void );

			//Reimplementation required for this style of singleton implementation to work across DLLs
			//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
			static ThemeManager* getSingletonPtr( void );

			ThemeManager();
			~ThemeManager();

			//! Creates a new theme with the given \c themeName, copied from the given \c theme object
			void createTheme( const std::string& themeName, const Theme& theme );
			//! Returns a reference to the requested theme, or the default theme if the requested theme does not exist, or throws an exception if both fail
			const Theme& getTheme( const std::string& themeName );
			//! Returns a reference to the WidgetTheme from the requested theme. If the theme or widget in that theme does not exist, the default theme will be attempted. An exception is thrown if that fails as well.
			const WidgetTheme& getWidgetTheme( const std::string& themeName, const std::string& widgetName );
			//! Destroys the given theme by \c themeName
			void destroyTheme( const std::string& themeName );
			//! Sets the name of the theme that is used as a fall back when getTheme() cannot find the requested theme
			void setDefaultThemeName( const std::string& themeName );
		private:
			std::string mDefaultTheme;
			typedef std::map<std::string, Theme> ThemeMap;
			ThemeMap mThemeMap;
		};

	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_ThemeManager_h__
