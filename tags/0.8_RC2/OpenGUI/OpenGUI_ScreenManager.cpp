// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_ScreenManager.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Screen.h"
#include "OpenGUI_LogSystem.h"
#include "OpenGUI_TimerManager.h"
#include "OpenGUI_XMLParser.h"
#include "OpenGUI_StrConv.h"
#include "OpenGUI_WidgetCollection.h"
#include "OpenGUI_CursorManager.h"
#include "OpenGUI_WidgetManager.h"
#include "OpenGUI_FormManager.h"

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

		XMLParser::getSingleton().RegisterLoadHandler( "Screen", &ScreenManager::_Screen_XMLNode_Load );
		XMLParser::getSingleton().RegisterUnloadHandler( "Screen", &ScreenManager::_Screen_XMLNode_Unload );
	}
	//############################################################################
	ScreenManager::~ScreenManager() {
		LogManager::SlogMsg( "SHUTDOWN", OGLL_INFO2 ) << "Destroying ScreenManager" << Log::endlog;
		destroyAllScreens();

		XMLParser::getSingleton().UnregisterLoadHandler( "Screen", &ScreenManager::_Screen_XMLNode_Load );
		XMLParser::getSingleton().UnregisterUnloadHandler( "Screen", &ScreenManager::_Screen_XMLNode_Unload );
	}
	//############################################################################
	Screen* ScreenManager::createScreen( const std::string& screenName, const FVector2& initialSize, Viewport* viewport ) {
		ScreenMap::iterator iter = mScreenMap.find( screenName );
		if ( iter != mScreenMap.end() )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM,
					  "Screen by given name already exists: " + screenName, __FUNCTION__ );

		Screen* tmp = new Screen( screenName, initialSize, viewport );
		mScreenMap[screenName] = tmp;
		return tmp;
	}
	//############################################################################
	void ScreenManager::destroyScreen( Screen* screenPtr ) {
		ScreenMap::iterator iter = mScreenMap.find( screenPtr->mName );
		if ( iter == mScreenMap.end() )
			OG_THROW( Exception::ERR_INTERNAL_ERROR,
					  "Invalid Screen pointer", __FUNCTION__ );
		Screen* tmp = iter->second;
		if ( tmp != screenPtr )
			OG_THROW( Exception::ERR_INTERNAL_ERROR,
					  "Invalid Screen pointer", __FUNCTION__ );
		delete screenPtr;
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
	void ScreenManager::_stat_UpdateFPS() {
		mStatFPS.addRecord( mFPSTimer->getSeconds() );
		mFPSTimer->reset();
	}
	//############################################################################
	float ScreenManager::statGetFPS() {
		return 1.0f / mStatFPS.getAverage();
	}
	//############################################################################
	bool ScreenManager::_Screen_XMLNode_Load( const XMLNode& node, const std::string& nodePath ) {
		ScreenManager& manager = ScreenManager::getSingleton();

		// we only handle these tags within <OpenGUI>
		if ( nodePath != "/OpenGUI/" )
			return false;


		const std::string name = node.getAttribute( "Name" );
		const std::string sizeStr = node.getAttribute( "Size" );
		FVector2 size;
		StrConv::toFVector2( sizeStr, size );
		Screen* screen = manager.createScreen( name, size );
		if ( !screen )
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "Failed to create valid screen", __FUNCTION__ );

		try {
			if ( node.hasAttribute( "UPI" ) ) {
				const std::string upiStr = node.getAttribute( "UPI" );
				FVector2 upi;
				StrConv::toFVector2( upiStr, upi );
				screen->setUPI( upi );
			}

			if ( node.hasAttribute( "AutoUpdating" ) ) {
				const std::string autoUpdateStr = node.getAttribute( "AutoUpdating" );
				bool autoUpdate;
				StrConv::toBool( autoUpdateStr, autoUpdate );
				screen->setAutoUpdating( autoUpdate );
			}

			if ( node.hasAttribute( "AutoTiming" ) ) {
				const std::string autoTimingStr = node.getAttribute( "AutoTiming" );
				bool autoTiming;
				StrConv::toBool( autoTimingStr, autoTiming );
				screen->setAutoTiming( autoTiming );
			}

			if ( node.hasAttribute( "DefaultCursor" ) ) {
				const std::string defCurStr = node.getAttribute( "DefaultCursor" );
				CursorPtr cur = CursorManager::getSingleton().CreateDefinedCursor( defCurStr );
				screen->setCursor( cur );
			}

			if ( node.hasAttribute( "CursorEnabled" ) ) {
				const std::string enabledStr = node.getAttribute( "CursorEnabled" );
				bool enabled;
				StrConv::toBool( enabledStr, enabled );
				if ( enabled )
					screen->enableCursor();
				else
					screen->disableCursor();
			}

			if ( node.hasAttribute( "CursorVisible" ) ) {
				const std::string visibleStr = node.getAttribute( "CursorVisible" );
				bool visible;
				StrConv::toBool( visibleStr, visible );
				if ( visible )
					screen->showCursor();
				else
					screen->hideCursor();
			}

			//at this point we can start loading <Widget> and <Form> tags as needed
			WidgetCollection& container = ( screen->Children );
			XMLNodeList children = node.getChildren();
			for ( XMLNodeList::iterator iter = children.begin(); iter != children.end(); iter++ ) {
				XMLNode* child = ( *iter );
				if ( child->getTagName() == "Widget" ) {
					WidgetManager::_Widget_XMLNode_IntoContainer( *child, container );
				} else if ( child->getTagName() == "Form" ) {
					const std::string formDef = child->getAttribute( "FormDef" );
					if ( child->hasAttribute( "Name" ) ) {
						std::string rootName =  child->getAttribute( "Name" );
						FormManager::getSingleton().CreateForm( formDef, &container, rootName );
					} else {
						FormManager::getSingleton().CreateForm( formDef, &container );
					}
				}
			}

		} catch ( Exception& ) {
			//if we fail for any reason, we should destroy the screen and continue the throw
			manager.destroyScreen( screen );
			throw;
		}

		return true;
	}
	//############################################################################
	bool ScreenManager::_Screen_XMLNode_Unload( const XMLNode& node, const std::string& nodePath ) {
		ScreenManager& manager = ScreenManager::getSingleton();

		// we only handle these tags within <OpenGUI>
		if ( nodePath != "/OpenGUI/" )
			return false;

		const std::string name = node.getAttribute( "Name" );
		Screen* screen = manager.getScreen( name );
		if ( !screen )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "No Screen found with name: " + name, __FUNCTION__ );
		manager.destroyScreen( screen );

		return true;
	}
	//############################################################################

}//namespace OpenGUI{
