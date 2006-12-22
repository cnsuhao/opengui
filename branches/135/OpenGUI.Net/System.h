// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef System_h__
#define System_h__

using namespace System;

namespace OpenGUI_Net {
	class HandleSystem; // forward declaration
	ref class Renderer; // forward declaration
	ref class ScreenManager; // forward declaration
	ref class WidgetManager; // forward declaration

	public ref class System sealed {
	public:
		static System ^ getHandle();
		static System ^ initialize( Renderer ^ renderer );
		void shutdown();

		void loadPlugin( String ^ fileName );
		void unloadPlugin( String ^ fileName );
		void update();
		void updateScreens();
		void updateTime();
	private:
		System( OpenGUI::System* systemPtr, HandleSystem* handleSystem );
		OpenGUI::System* mSystem;
		void sanityTest();

		static System ^ gHandle;
		HandleSystem* mHandleSystem;

		ScreenManager ^ mScreenManager;
		WidgetManager ^ mWidgetManager;
	};

} // namespace OpenGUINet {
#endif // System_h__
