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
			handle->_setManaged( screen );
		}
	}
	//############################################################################
	void HandleListener::onObjectDestroyed( OpenGUI::Object* handledObject ) {
		ObjectHandle* handle = static_cast<ObjectHandle*>( handledObject->_Get_ObjectHandle( this ) );
		if ( handle ) {
			handle->getManaged()->_setHandle( 0 );
			OpenGUI::Object* nativeObject = handle->getObject();
			nativeObject->_Remove_ObjectHandle( handle, this );
			delete handle;
		}
	}
	//############################################################################
	HandleSystem* HandleSystem::mCurrentHandleSystem = 0;
	//############################################################################
	HandleSystem::HandleSystem() {
		if ( mCurrentHandleSystem )
			throw gcnew ::System::Exception( "Cannot create more than one HandleSystem" );
		mHandleListener = new HandleListener( this );
		OpenGUI::HandleManager::attachListener( mHandleListener );
		mCurrentHandleSystem = this;
	}
	//############################################################################
	HandleSystem::~HandleSystem() {
		OpenGUI::HandleManager::detachListener( mHandleListener );
		delete mHandleListener;
		mCurrentHandleSystem = 0;
	}
	//############################################################################
	Object ^ HandleSystem::getManaged( OpenGUI::Object* object ) {
		return static_cast<ObjectHandle*>( object->_Get_ObjectHandle( mCurrentHandleSystem->mHandleListener ) )->getManaged();
	}
	//############################################################################
} // namespace OpenGUI_Net {
