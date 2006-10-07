#include "OpenGUI_Window.h"

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

	class Window_ObjectAccessorList : public ObjectAccessorList {
	public:
		Window_ObjectAccessorList() {
			//addAccessor( &gWidget_Name_ObjectProperty );
		}
		~Window_ObjectAccessorList() {}
	}
	gWindow_ObjectAccessorList;

	//############################################################################
	//############################################################################


	//############################################################################
	Window::Window() {
		if ( gWindow_ObjectAccessorList.getParent() == 0 )
			gWindow_ObjectAccessorList.setParent( ContainerControl::getAccessors() );
	}
	//############################################################################
	Window::~Window() {
		/**/
	}
	//############################################################################
	ObjectAccessorList* Window::getAccessors() {
		return &gWindow_ObjectAccessorList;
	}
	//############################################################################
	char* Window::getClassName() {
		return "OpenGUI::Window";
	}
	//############################################################################
} // namespace OpenGUI {
