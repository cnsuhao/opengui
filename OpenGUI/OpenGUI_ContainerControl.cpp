#include "OpenGUI_ContainerControl.h"

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

	class ContainerControl_ObjectAccessorList : public ObjectAccessorList {
	public:
		ContainerControl_ObjectAccessorList() {
			//addAccessor( &gWidget_Name_ObjectProperty );
		}
		~ContainerControl_ObjectAccessorList() {}
	}
	gContainerControl_ObjectAccessorList;

	//############################################################################
	//############################################################################


	//############################################################################
	ContainerControl::ContainerControl() {
		if ( gContainerControl_ObjectAccessorList.getParent() == 0 )
			gContainerControl_ObjectAccessorList.setParent( Control::getAccessors() );
	}
	//############################################################################
	ContainerControl::~ContainerControl() {
		/**/
	}
	//############################################################################
	ObjectAccessorList* ContainerControl::getAccessors() {
		return &gContainerControl_ObjectAccessorList;
	}
	//############################################################################
	char* ContainerControl::getClassName() {
		return "OpenGUI::ContainerControl";
	}
	//############################################################################
} // namespace OpenGUI {
