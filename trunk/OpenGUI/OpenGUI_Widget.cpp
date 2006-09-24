#include "OpenGUI_Widget.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
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


	class Widget_ObjectAccessorList : public ObjectAccessorList {
	public:
		Widget_ObjectAccessorList() {
			addAccessor( &gWidget_Name_ObjectProperty );
		}
		~Widget_ObjectAccessorList() {
		}
	}
	gWidget_ObjectAccessorList;

	//############################################################################
	//############################################################################


	Widget::Widget() {
		if ( gWidget_ObjectAccessorList.getParent() == 0 )
			gWidget_ObjectAccessorList.setParent( Object::getAccessors() );
	}
	//############################################################################
	Widget::~Widget() {
	}
	//############################################################################
	ObjectAccessorList* Widget::getAccessors() {
		return &gWidget_ObjectAccessorList;
	}
	//############################################################################
	char* Widget::getClassName() {
		return "OpenGUI::Widget";
	}
	//############################################################################
	const std::string& Widget::getName() {
		return mWidgetName;
	}
	//############################################################################
	void Widget::setName( const std::string& name ) {
		mWidgetName = name;
	}
	//############################################################################
}//namespace OpenGUI{
