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
			XMLParser::getSingleton().RegisterLoadHandler( "Theme", &ThemeManager::_Theme_XMLNode_Load );
			XMLParser::getSingleton().RegisterUnloadHandler( "Theme", &ThemeManager::_Theme_XMLNode_Unload );
		}
		//############################################################################
		ThemeManager::~ThemeManager() {
			XMLParser::getSingleton().UnregisterLoadHandler( "Theme", &ThemeManager::_Theme_XMLNode_Load );
			XMLParser::getSingleton().UnregisterUnloadHandler( "Theme", &ThemeManager::_Theme_XMLNode_Unload );
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
		bool ThemeManager::_Theme_XMLNode_Load( const XMLNode& node, const std::string& nodePath ) {
			ThemeManager& manager = ThemeManager::getSingleton();
			ImageryManager& imgmgr = ImageryManager::getSingleton();
			// we only handle these tags within <Amethyst>
			if ( nodePath != "/Amethyst/" )
				return false;

			const std::string themeName = node.getAttribute("Name");
			Theme theme;
			XMLNodeList widgetNodes = node.getChildren("WidgetTheme");
			XMLNodeList::iterator wni,wniend = widgetNodes.end();
			for(wni=widgetNodes.begin(); wni!=wniend; wni++){
				XMLNode* widgetNode = (*wni);
				const std::string widgetThemeName = widgetNode->getAttribute("Name");
				WidgetTheme wtheme;
				
				XMLNodeList stateNodes = widgetNode->getChildren("StateImage");
				XMLNodeList propNodes = widgetNode->getChildren("Property");

				XMLNodeList::iterator iter,iterend; // we're going to reuse these

				// process all StateImage tags
				iterend = stateNodes.end();
				for(iter = stateNodes.begin(); iter != iterend; iter++){
					XMLNode* stateNode = (*iter);
					const std::string stateName = stateNode->getAttribute("Name");

					// handle condition that has a face
					if(stateNode->hasAttribute("Face")){
						const std::string faceName = stateNode->getAttribute("Face");
						FacePtr facePtr = imgmgr.getFace(faceName);
						StateImage state(facePtr);
						wtheme.mStateImageMap[stateName] = state;
						continue; // advance to next state tag
					}

					// handle condition that has an imagery
					if(stateNode->hasAttribute("Imagery")){
						const std::string imageryName = stateNode->getAttribute("Imagery");
						ImageryPtr imageryPtr = imgmgr.getImagery(imageryName);
						StateImage state(imageryPtr);
						wtheme.mStateImageMap[stateName] = state;
						continue; // advance to next state tag
					}

					// must have either face or imagery, so if we get here then we throw
					OG_THROW(Exception::ERR_INVALIDPARAMS,"<StateImage> tag requires either a Face or Imagery attribute",__FUNCTION__);
				}

				// process all Property tags
				iterend = propNodes.end();
				for(iter = propNodes.begin(); iter != iterend; iter++){
					XMLNode* propNode = (*iter);
					Value propValue;
					propValue.LoadFromXMLNode(*propNode);
					wtheme.mValueMap[propValue.getName()] = propValue;
				}

				// store the widget theme into the theme group
				theme.mWidgetThemeMap[widgetThemeName] = wtheme;
			}

			// finally add the theme
			manager.createTheme(themeName, theme);

			return true;
		}
		//############################################################################
		bool ThemeManager::_Theme_XMLNode_Unload( const XMLNode& node, const std::string& nodePath ) {
			ThemeManager& manager = ThemeManager::getSingleton();
			// we only handle these tags within <Amethyst>
			if ( nodePath != "/Amethyst/" )
				return false;

			const std::string themeName = node.getAttribute("Name");
			manager.destroyTheme(themeName);

			return true;
		}
		//############################################################################
	} // namespace Amethyst{
} // namespace OpenGUI{
