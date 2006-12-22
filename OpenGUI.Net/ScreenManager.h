// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef ScreenManager_h__
#define ScreenManager_h__

using namespace System;

namespace OpenGUI_Net {

	ref class Viewport;
	ref class Screen;

	public ref class ScreenManager sealed {
	public:
		static ScreenManager ^ getHandle();

		//Creates a new screen with the given screenName at the given initialSize, rendering to the given viewport.
		Screen ^ createScreen( String ^ screenName, FVector2 initialSize );
		//destroys the given screen
		void destroyScreen( Screen ^ screenRef );
		//returns the requested screen by name, or 0 on failure
		//Screen* getScreen( const std::string &screenName );
		//performs an update on all screens that are auto updating
		void updateScreens();
		//performs time injections on all screens that are auto timing using TimerManager as the time source
		void updateTime();
		// returns an iterator to walk the current list of screens
		//iterator getIterator();
		// Returns the current FPS.
		float statGetFPS();

		ScreenManager( OpenGUI::ScreenManager* screenManagerPtr );

	private:
		OpenGUI::ScreenManager* mScreenManager;
		void sanityTest();
		static ScreenManager ^ gHandle;
	};

} // namespace OpenGUINet {
#endif // ScreenManager_h__
