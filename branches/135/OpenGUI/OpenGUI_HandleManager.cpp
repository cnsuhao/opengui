// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_HandleManager.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_HandleManagerListener.h"
#include "OpenGUI_HandledObject.h"

namespace OpenGUI {
	HandleManager::ListenerSet HandleManager::mListenerSet;
	//############################################################################
	//############################################################################
	void HandleManager::attachListener( HandleManagerListener* listener ) {
		assert( listener );
		ListenerSet::iterator iter = mListenerSet.find( listener );
		if ( iter != mListenerSet.end() )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM, "Given HandleManagerListener already attached", __FUNCTION__ );
		mListenerSet.insert( listener );
	}
	//############################################################################
	void HandleManager::detachListener( HandleManagerListener* listener ) {
		assert( listener );
		ListenerSet::iterator iter = mListenerSet.find( listener );
		if ( iter == mListenerSet.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Given HandleManagerListener not attached", __FUNCTION__ );
		mListenerSet.erase( listener );
	}
	//############################################################################
	void HandleManager::_Object_Created( HandledObject* object ) {
		assert( object );
		ListenerSet::iterator iter, iterend = mListenerSet.end();
		for ( iter = mListenerSet.begin(); iter != iterend; iter++ ) {
			HandleManagerListener* listener = ( *iter );
			listener->onHandledObjectCreated( object );
		}
	}
	//############################################################################
	void HandleManager::_Object_Destroyed( HandledObject* object ) {
		assert( object );
		ListenerSet::iterator iter, iterend = mListenerSet.end();
		for ( iter = mListenerSet.begin(); iter != iterend; iter++ ) {
			HandleManagerListener* listener = ( *iter );
			ObjectHandle* handle = object->_Get_ObjectHandle( listener );
			if ( handle )
				listener->onHandledObjectDestroyed( object );
		}
	}
	//############################################################################
} // namespace OpenGUI {
