// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

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
		m_Resizing = RS_NONE;

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
	unsigned int Window::getObjectType() const {
		return OT_WINDOW;
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
	/*! The reversal arguments allow you to control how the cursor affects the
	window resizing. By reversing an axis, the window sizing effect will be reversed
	along that axis, and the window will be moved as necessary to keep the opposite
	side to remain stationary. */
	void Window::eventResize_Begin( bool sizeHeight , bool sizeWidth , bool revWidth , bool revHeight ) {
		WindowResizeBeginEventArgs event( sizeHeight, revHeight, sizeWidth, revWidth );
		triggerEvent( "Resize_Begin", event );
	}
	//############################################################################
	void Window::eventResize_End() {
		EventArgs event;
		triggerEvent( "Resize_End", event );
	}
	//############################################################################
	void Window::onMove_Begin( Object* sender, EventArgs& evtArgs ) {
		if ( isResizing() ) // we cannot resize and move at the same time
			eventResize_End();
		mInitialPos = getPosition();
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
	void Window::onResize_Begin( Object* sender, WindowResizeBeginEventArgs& evtArgs ) {
		if ( isMoving() ) // we cannot resize and move at the same time
			eventMove_End();
		mInitialPos = getPosition();
		mInitialSize = getSize();
		mInitialCursor = getScreen()->getCursorPos();
		m_Resizing = RS_NONE;
		if ( evtArgs.sizingWidth )
			m_Resizing = ( ResizeState )( m_Resizing | RS_SWIDTH );
		if ( evtArgs.sizingHeight )
			m_Resizing = ( ResizeState )( m_Resizing | RS_SHEIGHT );
		if ( evtArgs.reverseHeight )
			m_Resizing = ( ResizeState )( m_Resizing | RS_RHEIGHT );
		if ( evtArgs.reverseWidth )
			m_Resizing = ( ResizeState )( m_Resizing | RS_RWIDTH );
		grabCursorFocus();
	}
	//############################################################################
	void Window::onResize_End( Object* sender, EventArgs& evtArgs ) {
		m_Resizing = RS_NONE;
		releaseCursorFocus();
	}
	//############################################################################
	void Window::onCursor_Move( Object* sender, Cursor_EventArgs& evtArgs ) {
		if ( isMoving() ) {
			FVector2 diff = evtArgs.Position - mInitialCursor;
			FVector2 newPos = mInitialPos + diff;
			setLeft( newPos.x );
			setTop( newPos.y );
		}
		if ( isResizing() ) {
			FVector2 diff = evtArgs.Position - mInitialCursor;
			FVector2 newPos = mInitialPos;
			FVector2 newSize = mInitialSize;

			if ( m_Resizing & RS_SWIDTH ) {
				// reverse the width resize?
				if ( m_Resizing & RS_RWIDTH ) {
					newSize.x -= diff.x;
					newPos.x += diff.x;
					setLeft( newPos.x );
				} else {
					newSize.x += diff.x;
				}
				setWidth( newSize.x );
			}

			if ( m_Resizing & RS_SHEIGHT ) {
				// reverse the height resize?
				if ( m_Resizing & RS_RHEIGHT ) {
					newSize.y -= diff.y;
					newPos.y += diff.y;
					setTop( newPos.y );
				} else {
					newSize.y += diff.y;
				}
				setHeight( newSize.y );
			}
		}
		ContainerControl::onCursor_Move( sender, evtArgs );
	}
	//############################################################################
	void Window::onCursor_Focused( Object* sender, Focus_EventArgs& evtArgs ) {
		ContainerControl::onCursor_Focused( sender, evtArgs );
	}
	//############################################################################
	void Window::onCursor_FocusLost( Object* sender, Focus_EventArgs& evtArgs ) {
		if ( isMoving() )
			eventMove_End();
		if ( isResizing() )
			eventResize_End();
		ContainerControl::onCursor_FocusLost( sender, evtArgs );
	}
	//############################################################################
	bool Window::isMoving() const {
		return m_Moving;
	}
	//############################################################################
	bool Window::isResizing() const {
		return ( m_Resizing & ( RS_SWIDTH | RS_SHEIGHT ) ) != 0;
	}
	//############################################################################
} // namespace OpenGUI {
