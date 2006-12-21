// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_Object.h"
#include "OpenGUI_ObjectAccessor.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Value.h"
#include "OpenGUI_ObjectHandle.h"
#include "OpenGUI_HandleManager.h"

namespace OpenGUI {

	//############################################################################
	Object::Object() {
		mEventReceiver.mParent = this;
		mInitialized = false;
	}
	//############################################################################
	void Object::_Initialize_Object() {
		assert( !mInitialized );
		mInitialized = true;
		_Init_ObjectHandles();
	}
	//############################################################################
	Object::~Object() {
		_Free_ObjectHandles();
	}
	//############################################################################
	EventReceiver& Object::getEvents() {
		return mEventReceiver;
	}
	//############################################################################
	ObjectAccessorList* Object::getAccessors() {
		return 0;
	}
	//############################################################################
	void Object::getProperty( const std::string& propertyName, Value& valueOut ) {
		ObjectAccessorList* oal = getAccessors();
		if ( !oal ) {
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "getAccessors() returned invalid ObjectAccessorList", "Object::getProperty" );
		} else {
			ObjectAccessor* accessor = oal->getAccessor( propertyName );
			if ( !accessor ) {
				OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "getAccessor( '"
						  + propertyName
						  + "' ) returned invalid ObjectAccessor", "Object::getProperty" );
			} else {
				if ( accessor->_getAccessorType() != ObjectAccessor::TYPE_PROPERTY ) {
					OG_THROW( Exception::OP_FAILED, "ObjectAccessor: '"
							  + propertyName
							  + "' is not TYPE_PROPERTY", "Object::getProperty" );
				} else {
					ObjectProperty* prop = dynamic_cast<ObjectProperty*>( accessor );
					if ( prop ) {
						prop->get( *this, valueOut );
					} else {
						OG_THROW( Exception::OP_FAILED, "ObjectAccessor: '"
								  + propertyName
								  + "' is TYPE_PROPERTY but failed dynamic_cast<ObjectProperty*>", "Object::getProperty" );
					}
				}
			}
		}
	}
	//############################################################################
	void Object::setProperty( const std::string& propertyName, Value& valueIn ) {
		ObjectAccessorList* oal = getAccessors();
		if ( !oal ) {
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "getAccessors() returned invalid ObjectAccessorList", "Object::setProperty" );
		} else {
			ObjectAccessor* accessor = oal->getAccessor( propertyName );
			if ( !accessor ) {
				OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "getAccessor( '"
						  + propertyName
						  + "' ) returned invalid ObjectAccessor", "Object::setProperty" );
			} else {
				if ( accessor->_getAccessorType() != ObjectAccessor::TYPE_PROPERTY ) {
					OG_THROW( Exception::OP_FAILED, "ObjectAccessor: '"
							  + propertyName
							  + "' is not TYPE_PROPERTY", "Object::setProperty" );
				} else {
					ObjectProperty* prop = dynamic_cast<ObjectProperty*>( accessor );
					if ( prop ) {
						if ( !prop->getPermSettable() ) {
							OG_THROW( Exception::OP_FAILED, "Property is read only: '"
									  + propertyName
									  + "'", "Object::setProperty" );
						} else {
							prop->set( *this, valueIn );
						}
					} else {
						OG_THROW( Exception::OP_FAILED, "ObjectAccessor: '"
								  + propertyName
								  + "' is TYPE_PROPERTY but failed dynamic_cast<ObjectProperty*>", "Object::setProperty" );
					}
				}
			}
		}
	}
	//############################################################################
	void Object::callMethod( const std::string& methodName, ValueList& paramIn, ValueList& returnOut ) {
		ObjectAccessorList* oal = getAccessors();
		if ( !oal ) {
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "getAccessors() returned invalid ObjectAccessorList", "Object::callMethod" );
		} else {
			ObjectAccessor* accessor = oal->getAccessor( methodName );
			if ( !accessor ) {
				OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "getAccessor( '"
						  + methodName
						  + "' ) returned invalid ObjectAccessor", "Object::callMethod" );
			} else {
				if ( accessor->_getAccessorType() != ObjectAccessor::TYPE_METHOD ) {
					OG_THROW( Exception::OP_FAILED, "ObjectAccessor: '"
							  + methodName
							  + "' is not TYPE_METHOD", "Object::callMethod" );
				} else {
					ObjectMethod* method = dynamic_cast<ObjectMethod*>( accessor );
					if ( method ) {
						method->invoke( *this, paramIn, returnOut );
					} else {
						OG_THROW( Exception::OP_FAILED, "ObjectAccessor: '"
								  + methodName
								  + "' is TYPE_METHOD but failed dynamic_cast<ObjectMethod*>", "Object::callMethod" );
					}
				}
			}
		}
	}
	//############################################################################


	//############################################################################
	void Object::_Add_ObjectHandle( ObjectHandle* handle, HandleManagerListener* sourceListener ) {
		assert( sourceListener );
		assert( handle );
		HandleMap::iterator iter = mHandleMap.find( sourceListener );
		if ( iter != mHandleMap.end() )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM, "Already have a handle stored for the given listener", __FUNCTION__ );
		handle->m_HandledObject = this;
		mHandleMap[sourceListener] = handle;
	}
	//############################################################################
	void Object::_Remove_ObjectHandle( ObjectHandle* handle, HandleManagerListener* sourceListener ) {
		assert( sourceListener );
		HandleMap::iterator iter = mHandleMap.find( sourceListener );
		if ( iter != mHandleMap.end() ) {
			assert( handle == iter->second );
			iter->second->m_HandledObject = 0;
			mHandleMap.erase( iter );
			return;
		}
		OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "No handle stored for the given listener", __FUNCTION__ );
	}
	//############################################################################
	/*! If no handle was added for the given listener, the return value will be 0. */
	ObjectHandle* Object::_Get_ObjectHandle( HandleManagerListener* sourceListener ) {
		assert( sourceListener );
		HandleMap::iterator iter = mHandleMap.find( sourceListener );
		if ( iter != mHandleMap.end() )
			return iter->second;
		return 0;
	}
	//############################################################################
	void Object::_Init_ObjectHandles() {
		HandleManager::_Object_Created( this );
	}
	//############################################################################
	void Object::_Free_ObjectHandles() {
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

}//namespace OpenGUI{