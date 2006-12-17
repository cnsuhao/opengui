// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef System_h__
#define System_h__

using namespace System;

namespace OpenGUI_Net {
	public ref class System {
	public:
		static System ^ getHandle();
		static System ^ initialize();
		void shutdown();

		void loadPlugin( String ^ fileName );
		void unloadPlugin( String ^ fileName );
	private:
		System( OpenGUI::System* systemPtr );
		OpenGUI::System* gSystem;
		void sanityTest();

		static System ^ gHandle;
	};

} // namespace OpenGUINet {
#endif // System_h__
