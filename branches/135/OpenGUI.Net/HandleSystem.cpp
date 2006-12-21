// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "Stdafx.h"

#include "HandleSystem.h"
#include "Object.h"
#include "Screen.h"

namespace OpenGUI_Net {
	//############################################################################
	void HandleListener::onObjectCreated( OpenGUI::Object* handledObject ) {
		ObjectHandle* handle = new ObjectHandle();
		handledObject->_Add_ObjectHandle( handle, this );
		if ( handledObject->getObjectType() == OpenGUI::Object::OT_SCREEN ) {
			Screen ^ screen = gcnew Screen();
			screen->_setHandle( handle );
		}
	}
	//############################################################################
	void HandleListener::onObjectDestroyed( OpenGUI::Object* handledObject ) {
		ObjectHandle* handle = static_cast<ObjectHandle*>( handledObject->_Get_ObjectHandle( this ) );
		if ( handle ) {
			delete handle;
		}
	}
	//############################################################################
	HandleSystem::HandleSystem() {
		mHandleListener = new HandleListener( this );
		OpenGUI::HandleManager::attachListener( mHandleListener );
	}
	//############################################################################
	HandleSystem::~HandleSystem() {
		OpenGUI::HandleManager::detachListener( mHandleListener );
		delete mHandleListener;
	}
	//############################################################################
} // namespace OpenGUI_Net {
