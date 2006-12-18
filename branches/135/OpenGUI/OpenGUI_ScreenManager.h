// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef A0225006_7C8D_45CC_9C07_5328679AD103
#define A0225006_7C8D_45CC_9C07_5328679AD103

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_HandledObject.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Timer.h"
#include "OpenGUI_Iterators.h"
#include "OpenGUI_Statistic.h"
#include "OpenGUI_XML.h"

namespace OpenGUI {
	class System;
	class Screen;
	class Viewport;

	//! Manages creating, destroying, and lookup of Screen objects
	class OPENGUI_API ScreenManager: public Singleton<ScreenManager>, public HandledObject {
		friend class System;
	public:
		typedef std::map<std::string, Screen*> ScreenMap;
		typedef MapIterator<ScreenMap, ScreenMap::iterator> iterator;
		typedef MapIterator<ScreenMap, ScreenMap::const_iterator> const_iterator;

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static ScreenManager& getSingleton( void );

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static ScreenManager* getSingletonPtr( void );

		//! Creates a new screen with the given \c screenName at the given \c initialSize, rendering to the given \c viewport
		/*! The \c viewport is optional, but you cannot render a Screen without a Viewport to render to, so
		Screens with no Viewport are created disabled, and cannot be enabled until a Viewport is assigned. */
		Screen* createScreen( const std::string& screenName, const FVector2& initialSize, Viewport* viewport = 0 );
		//! destroys the given screen
		void destroyScreen( Screen* screenPtr );
		//! returns the requested screen by name, or 0 on failure
		Screen* getScreen( const std::string& screenName );

		//! performs an update on all screens that are auto updating
		void updateScreens();

		//! performs time injections on all screens that are auto timing using TimerManager as the time source
		void updateTime();

		//! returns an iterator to walk the current list of screens
		iterator getIterator() {
			return iterator( mScreenMap.begin(), mScreenMap.end() );
		}

		//! Returns the current FPS
		/*! The FPS value returned is an average over the last 5 frames. If less than
		5 frames have been rendered, then the average is based on as many frames
		as available. If no frames have been rendered, the returned value will be 0.0f.
		\note A "frame" is defined as a single call to ScreenManager::updateScreens().
		Since most applications will call this function once per scene frame, this is
		an adequate metric.

		\note The results of all statistics are dependent on the accuracy of the TimerManager.
		Feeding inaccurate information to TimerManager will result in inaccurate results
		for all statistics.
		*/
		float statGetFPS();

	protected:
		void destroyAllScreens();
	private:
		ScreenManager();
		~ScreenManager();

		ScreenMap mScreenMap;
		TimerPtr mTimer;

		//Statistics
		TimerPtr mFPSTimer;
		AverageStat mStatFPS;
		void _stat_UpdateFPS();

		// XML tag handlers for <Screen> tags
		static bool _Screen_XMLNode_Load( const XMLNode& node, const std::string& nodePath );
		static bool _Screen_XMLNode_Unload( const XMLNode& node, const std::string& nodePath );
	};
} //namespace OpenGUI {

#endif // A0225006_7C8D_45CC_9C07_5328679AD103
