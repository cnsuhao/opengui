#include "OpenGUI_Control.h"

namespace OpenGUI {
	/*
	//############################################################################
	class Widget_Name_ObjectProperty : public ObjectProperty {
	public:
		virtual const char* getAccessorName() {
			return "Name";
		}
		//############################################################################
		virtual void get( Object& objectRef, Value& valueOut ) {
			try {
				Widget &w = dynamic_cast<Widget &>( objectRef );
				valueOut.setValue( w.getName() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual void set( Object& objectRef, Value& valueIn ) {
			try {
				Widget &w = dynamic_cast<Widget &>( objectRef );
				w.setName( valueIn.getValueAsString() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual Value::ValueType getPropertyType() {
			return Value::T_STRING;
		}
	}
	gWidget_Name_ObjectProperty;
	//############################################################################
	//############################################################################
	*/

	class Control_ObjectAccessorList : public ObjectAccessorList {
	public:
		Control_ObjectAccessorList() {
			//addAccessor( &gWidget_Name_ObjectProperty );
		}
		~Control_ObjectAccessorList() {}
	}
	gControl_ObjectAccessorList;

	//############################################################################
	//############################################################################


	//############################################################################
	Control::Control() {
		if ( gControl_ObjectAccessorList.getParent() == 0 )
			gControl_ObjectAccessorList.setParent( Widget::getAccessors() );
	}
	//############################################################################
	Control::~Control() {
		/**/
	}
	//############################################################################
	ObjectAccessorList* Control::getAccessors() {
		return &gControl_ObjectAccessorList;
	}
	//############################################################################
	char* Control::getClassName() {
		return "OpenGUI::Control";
	}
	//############################################################################
} // namespace OpenGUI {
