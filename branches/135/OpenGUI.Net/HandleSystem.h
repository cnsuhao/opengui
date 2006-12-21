// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details


#ifndef HandleSystem_h__
#define HandleSystem_h__

using namespace System;

namespace OpenGUI_Net {

	class HandleSystem; // forward declaration

	class HandleListener: public OpenGUI::HandleManagerListener {
	public:
		HandleListener( HandleSystem* system ): mHandleSystem( system ) {}
		// Called when a HandledObject is created.
		virtual void onObjectCreated( OpenGUI::Object* handledObject );
		// Called when a HandledObject is destroyed.
		virtual void onObjectDestroyed( OpenGUI::Object* handledObject );
	private:
		HandleSystem* mHandleSystem;
	};

	class HandleSystem {
	public:
		HandleSystem();
		~HandleSystem();
	private:
		HandleListener* mHandleListener;
	};

} // namespace OpenGUI_Net {

#endif // HandleSystem_h__
