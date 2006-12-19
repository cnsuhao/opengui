// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_HandledObject.h"
#include "OpenGUI_ObjectHandle.h"
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
	ObjectHandle* HandledObject::_Get_ObjectHandle( HandleManagerListener* sourceListener ) {
		assert( sourceListener );
		HandleMap::iterator iter = mHandleMap.find( sourceListener );
		if ( iter != mHandleMap.end() )
			return iter->second;
		OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "No handle stored for the given listener", __FUNCTION__ );
	}
	//############################################################################
	void HandledObject::_Init_ObjectHandles() {
		HandleManager::_Object_Created( this );
	}
	//############################################################################
	void HandledObject::_Free_ObjectHandles() {
		HandleManager::_Object_Destroyed( this );
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
