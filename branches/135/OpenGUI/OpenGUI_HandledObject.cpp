// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_HandledObject.h"
#include "OpenGUI_ObjectHandle.h"
#include "OpenGUI_HandleManager.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	//############################################################################
	void HandledObject::_Add_ObjectHandle( ObjectHandle* handle, HandleManagerListener* sourceListener ) {
		assert( sourceListener );
		HandleMap::iterator iter = mHandleMap.find( sourceListener );
		if ( iter != mHandleMap.end() )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM, "Already have a handle stored for the given listener", __FUNCTION__ );
		handle->m_HandledObject = this;
		mHandleMap[sourceListener] = handle;
	}
	//############################################################################
	void HandledObject::_Remove_ObjectHandle( ObjectHandle* handle, HandleManagerListener* sourceListener ) {
		assert( sourceListener );
		HandleMap::iterator iter = mHandleMap.find( sourceListener );
		if ( iter != mHandleMap.end() ) {
			assert( handle == iter->second );
			iter->second->m_HandledObject = 0;
			mHandleMap.erase( iter );
		}
		OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "No handle stored for the given listener", __FUNCTION__ );
	}
	//############################################################################
	/*! If no handle was added for the given listener, the return value will be 0. */
	ObjectHandle* HandledObject::_Get_ObjectHandle( HandleManagerListener* sourceListener ) {
		assert( sourceListener );
		HandleMap::iterator iter = mHandleMap.find( sourceListener );
		if ( iter != mHandleMap.end() )
			return iter->second;
		return 0;
	}
	//############################################################################
	void HandledObject::_Init_ObjectHandles() {
		HandleManager::_Object_Created( this );
	}
	//############################################################################
	void HandledObject::_Free_ObjectHandles() {
		// send notifications
		HandleManager::_Object_Destroyed( this );

		// free whatever we have left over
		HandleMap::iterator iter, iterend = mHandleMap.end();
		for ( iter = mHandleMap.begin(); iter != iterend; iter++ ) {
			ObjectHandle* handle = iter->second;
			delete handle;
		}
		mHandleMap.clear();
	}
	//############################################################################
	HandledObject::HandledObject() {
		_Init_ObjectHandles();
	}
	//############################################################################
	HandledObject::~HandledObject() {
		_Free_ObjectHandles();
	}
	//############################################################################
} //namespace OpenGUI {
