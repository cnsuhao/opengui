//#include "OpenGUI.h"

#include "OpenGUI_Object.h"
#include "OpenGUI_ObjectAccessor.h"
#include "OpenGUI_Exception.h"


namespace OpenGUI {

	//############################################################################
	Object::Object() {
		mEventReceiver.mParent = this;
	}
	//############################################################################
	Object::~Object() {}
	//############################################################################
	char* Object::getClassName() {
		return "OpenGUI::Object";
	}
	//############################################################################
	Event::EventReceiver& Object::getEvents() {
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
				if ( accessor->getAccessorType() != ObjectAccessor::TYPE_PROPERTY ) {
					OG_THROW( Exception::OP_FAILED, "ObjectAccessor: '"
							  + propertyName
							  + "' is not TYPE_PROPERTY", "Object::getProperty" );
				} else {
					ObjectProperty* prop = dynamic_cast<ObjectProperty*>( accessor );
					if ( prop ) {
						prop->get( valueOut );
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
				if ( accessor->getAccessorType() != ObjectAccessor::TYPE_PROPERTY ) {
					OG_THROW( Exception::OP_FAILED, "ObjectAccessor: '"
							  + propertyName
							  + "' is not TYPE_PROPERTY", "Object::setProperty" );
				} else {
					ObjectProperty* prop = dynamic_cast<ObjectProperty*>( accessor );
					if ( prop ) {
						prop->set( valueIn );
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
				if ( accessor->getAccessorType() != ObjectAccessor::TYPE_METHOD ) {
					OG_THROW( Exception::OP_FAILED, "ObjectAccessor: '"
							  + methodName
							  + "' is not TYPE_METHOD", "Object::callMethod" );
				} else {
					ObjectMethod* method = dynamic_cast<ObjectMethod*>( accessor );
					if ( method ) {
						method->invoke( paramIn, returnOut );
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


}//namespace OpenGUI{