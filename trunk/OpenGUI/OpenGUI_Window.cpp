#include "OpenGUI_Window.h"
#include "OpenGUI_Screen.h"

namespace OpenGUI {

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

		m_Moving = false;
		m_Resizing = false;

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
		mInitial = getPosition();
		mInitialCursor = getScreen()->getCursorPos();
		m_Moving = true;
		grabCursorFocus();
	}
	//############################################################################
	void Window::onMove_End( Object* sender, EventArgs& evtArgs ) {
		m_Moving = false;
		releaseCursorFocus();
	}
	//############################################################################
	void Window::onResize_Begin( Object* sender, EventArgs& evtArgs ) {
		mInitial = getSize();
		m_Resizing = true;
		grabCursorFocus();
	}
	//############################################################################
	void Window::onResize_End( Object* sender, EventArgs& evtArgs ) {
		m_Resizing = false;
		releaseCursorFocus();
	}
	//############################################################################
	void Window::onCursor_Move( Object* sender, Cursor_EventArgs& evtArgs ) {
		if(m_Moving && hasCursorFocus()){
			FVector2 diff = evtArgs.Position - mInitialCursor;
			FVector2 newPos = mInitial + diff;
			setLeft(newPos.x);
			setTop(newPos.y);
		}
	}
	//############################################################################
} // namespace OpenGUI {
