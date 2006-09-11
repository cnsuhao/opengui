#include "OpenGUI.h"

namespace OpenGUI {
	void Cursor::RegisterForDraw() {
		if ( CursorManager::getSingletonPtr() ) {
			CursorManager::getSingleton().cursorRegisterDraw( this );
		}
	}
	void Cursor::UnRegisterForDraw() {
		if ( CursorManager::getSingletonPtr() ) {
			CursorManager::getSingleton().cursorUnregisterDraw( this );
		}
	}
}
;//namespace OpenGUI{

