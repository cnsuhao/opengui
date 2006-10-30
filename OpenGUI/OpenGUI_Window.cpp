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
			/* Currently has no accessors to bind */
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

		m_Resizable = false;
		m_Moveable = false;

		//Set up events and default bindings
		getEvents().createEvent( "Move_Begin" );
		getEvents().createEvent( "Move_End" );
		getEvents().createEvent( "Resize_Begin" );
		getEvents().createEvent( "Resize_End" );
		getEvents()["Move_Begin"].add( new EventDelegate( this, &Window::onMove_Begin ) );
		getEvents()["Move_End"].add( new EventDelegate( this, &Window::onMove_End ) );
		getEvents()["Resize_Begin"].add( new EventDelegate( this, &Window::onResize_Begin ) );
		getEvents()["Resize_End"].add( new EventDelegate( this, &Window::onResize_End ) );
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
	void Window::eventMove_Begin() {
		EventArgs event;
		triggerEvent( "Move_Begin", event );
	}
	//############################################################################
	void Window::eventMove_End() {
		EventArgs event;
		triggerEvent( "Move_End", event );
	}
	//############################################################################
	void Window::eventResize_Begin() {
		EventArgs event;
		triggerEvent( "Resize_Begin", event );
	}
	//############################################################################
	void Window::eventResize_End() {
		EventArgs event;
		triggerEvent( "Resize_End", event );
	}
	//############################################################################
	void Window::onMove_Begin( Object* sender, EventArgs& evtArgs ) {
		if ( m_Moveable ) {
			mInitial = getPosition();
			mMoving = true;
		}
	}
	//############################################################################
	void Window::onMove_End( Object* sender, EventArgs& evtArgs ) {
		if ( m_Moveable ) {
			mMoving = false;
		}
	}
	//############################################################################
	void Window::onResize_Begin( Object* sender, EventArgs& evtArgs ) {
		if ( m_Resizable ) {
			mInitial = getSize();
			mResizing = true;
		}
	}
	//############################################################################
	void Window::onResize_End( Object* sender, EventArgs& evtArgs ) {
		if ( m_Resizable ) {
			mResizing = false;
		}
	}
	//############################################################################
} // namespace OpenGUI {
