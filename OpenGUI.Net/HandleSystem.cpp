// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "Stdafx.h"

#include "HandleSystem.h"

namespace OpenGUI_Net {
	//############################################################################
	void HandleListener::onObjectCreated(OpenGUI::Object* handledObject){
		/**/
		int i = 0;
	}
	//############################################################################
	void HandleListener::onObjectDestroyed(OpenGUI::Object* handledObject){
		/**/
		int i = 0;
	}
	//############################################################################
	HandleSystem::HandleSystem(){
		mHandleListener = new HandleListener(this);
		OpenGUI::HandleManager::attachListener(mHandleListener);
	}
	//############################################################################
	HandleSystem::~HandleSystem(){
		OpenGUI::HandleManager::detachListener(mHandleListener);
		delete mHandleListener;
	}
	//############################################################################
} // namespace OpenGUI_Net {
