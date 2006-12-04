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
		ThemeManager::ThemeManager() {
			/**/
		}
		//############################################################################
		ThemeManager::~ThemeManager() {
			/**/
		}
		//############################################################################
		void ThemeManager::createTheme( const std::string& themeName, const Theme& theme ) {
			ThemeMap::iterator iter = mThemeMap.find( themeName );
			if ( iter == mThemeMap.end() )
				mThemeMap[themeName] = theme;
			else
				OG_THROW( Exception::ERR_DUPLICATE_ITEM, "A theme with given name already exists: " + themeName, __FUNCTION__ );
		}
		//############################################################################
		const Theme& ThemeManager::getTheme( const std::string& themeName ) {
			ThemeMap::iterator iter = mThemeMap.find( themeName );
			if ( iter != mThemeMap.end() )
				return iter->second;
			iter = mThemeMap.find( mDefaultTheme );
			if ( iter != mThemeMap.end() )
				return iter->second;
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "No valid default theme, and could not find requested theme: " + themeName, __FUNCTION__ );
		}
		//############################################################################
		void ThemeManager::destroyTheme( const std::string& themeName ) {
			ThemeMap::iterator iter = mThemeMap.find( themeName );
			if ( iter == mThemeMap.end() )
				OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Could not find requested theme: " + themeName, __FUNCTION__ );
			else
				mThemeMap.erase( iter );
		}
		//############################################################################
		void ThemeManager::setDefaultThemeName( const std::string& themeName ) {
			mDefaultTheme = themeName;
		}
		//############################################################################
		const WidgetTheme& ThemeManager::getWidgetTheme( const std::string& themeName, const std::string& widgetName ) {
			ThemeMap::iterator iter = mThemeMap.find( themeName );
			if ( iter != mThemeMap.end() ) {
				Theme& t = iter->second;
				Theme::WidgetThemeMap::iterator i = t.mWidgetThemeMap.find( widgetName );
				if ( i != t.mWidgetThemeMap.end() )
					return i->second;
			}
			iter = mThemeMap.find( mDefaultTheme );
			if ( iter != mThemeMap.end() ) {
				Theme& t = iter->second;
				Theme::WidgetThemeMap::iterator i = t.mWidgetThemeMap.find( widgetName );
				if ( i != t.mWidgetThemeMap.end() )
					return i->second;
			}
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Could not resolve WidgetTheme: " + themeName + ":" + widgetName, __FUNCTION__ );
		}
		//############################################################################
	} // namespace Amethyst{
} // namespace OpenGUI{
