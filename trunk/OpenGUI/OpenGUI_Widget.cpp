#include "OpenGUI_Widget.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Renderer.h"
#include "OpenGUI_I_WidgetContainer.h"
#include "OpenGUI_Screen.h"

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
		~Widget_ObjectAccessorList() {}
	}
	gWidget_ObjectAccessorList;

	//############################################################################
	//############################################################################


	Widget::Widget() {
		mContainer = 0; //we always start with no container
		if ( gWidget_ObjectAccessorList.getParent() == 0 )
			gWidget_ObjectAccessorList.setParent( Object::getAccessors() );
	}
	//############################################################################
	Widget::~Widget() {
		if ( mContainer )
			mContainer->notifyChildDelete( this );
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
	I_WidgetContainer* Widget::getContainer() {
		return mContainer;
	}
	//############################################################################
	void Widget::invalidate() {
		eventInvalidated();
		Widget* parent = dynamic_cast<Widget*>( getContainer() );
		if ( parent )
			parent->invalidate();
	}
	//############################################################################
	void Widget::flush() {
		Widget* parent = dynamic_cast<Widget*>( mContainer );
		if ( parent )
			parent->invalidate();
		_doflush();
	}
	//############################################################################
	void Widget::_doflush() {
		eventInvalidated();
		I_WidgetContainer* meContainer = dynamic_cast<I_WidgetContainer*>( this );
		if ( meContainer ) {
			WidgetCollection::iterator iter = meContainer->Children.begin();
			while ( iter != meContainer->Children.end() ) {
				iter->_doflush();
				iter++;
			}
		}
	}
	//############################################################################
	Screen* Widget::getScreen(){
		if(!mContainer) return 0;
		Widget* parentW = dynamic_cast<Widget*>( mContainer );
		if ( parentW )
			return parentW->getScreen();
		Screen* parentS = dynamic_cast<Screen*>( mContainer );
		if ( parentS )
			return parentS;
		return 0;
	}
	//############################################################################
}//namespace OpenGUI{
