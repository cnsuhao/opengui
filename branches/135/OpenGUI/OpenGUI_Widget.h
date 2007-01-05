// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef B2B428BD_BA97_41F4_AF2E_EF32498FC240
#define B2B428BD_BA97_41F4_AF2E_EF32498FC240

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Object.h"
#include "OpenGUI_ObjectAccessor.h"
#include "OpenGUI_Event.h"
#include "OpenGUI_Brush.h"
#include "OpenGUI_StrConv.h"

namespace OpenGUI {

	class Renderer; //forward declaration
	class WidgetCollection; //forward declaration
	class Screen; //forward declaration
	class Widget; //forward declaration

	//! List of Widget pointers
	typedef std::list<Widget*> WidgetPtrList;

	//! Base class for all input processing, containable, and potentially visible GUI objects
	/*!
	\par Properties
		- Name: setName(), getName()
		- Enabled: setEnabled(), getEnabled()

	\par Events Introduced
		- \ref Event_Enabled "Enabled"
		- \ref Event_Disabled "Disabled"
		- \ref Event_Attached "Attached"
		- \ref Event_Detached "Detached"
		- \ref Event_Draw "Draw"
		- \ref Event_Invalidated "Invalidated"
		- \ref Event_CursorMoving "CursorMoving"
		- \ref Event_CursorMove "CursorMove"
		- \ref Event_CursorPressing "CursorPressing"
		- \ref Event_CursorPress "CursorPress"
		- \ref Event_CursorReleasing "CursorReleasing"
		- \ref Event_CursorRelease "CursorRelease"
		- \ref Event_CursorFocused "CursorFocused"
		- \ref Event_CursorFocusLost "CursorFocusLost"
		- \ref Event_KeyUp "KeyUp"
		- \ref Event_KeyDown "KeyDown"
		- \ref Event_KeyPressed "KeyPressed"
		- \ref Event_KeyFocused "KeyFocused"
		- \ref Event_KeyFocusLost "KeyFocusLost"
		- \ref Event_Tick "Tick"
	\see \ref EventList_Widget "Widget Events"
	*/
	class OPENGUI_API Widget : public Object {
		friend class WidgetCollection; //we'll need this so containers can manage our handle to them
		//friend class Screen; // Screen needs access to the protected input event triggers
	public:
		//! public constructor
		Widget( bool delayObjectInit = false );
		//! public destructor
		virtual ~Widget();

		//! returns the name of this Widget
		const std::string& getName();
		//! sets the name of this Widget
		void setName( const std::string& name );

		//! returns the enabled/disabled state of this Widget
		bool getEnabled();
		//! sets the enabled/disabled state of this Widget
		void setEnabled( bool value );

		//! invalidate any caches of this Widget's render output
		/*! This will cause the Widget's Draw routine to be called on the next
		update of the Screen this Widget is attached to. */
		void invalidate();

		//! invalidate this Widget, as well as any and all potential children
		void flush();
		//! Needs to be overridden by container widgets to invalidate self and call _doFlush() for all children
		virtual void _doflush();

		//! returns the collection this widget is held within
		/*! Every displayable Widget is guaranteed to have a container.*/
		WidgetCollection* getContainer() const;

		//! Fills the given \c outList with pointers to all child Widgets that are under the given \c position
		/*! The list is depth sorted, with top-most widgets at the top and bottom-most widgets at the bottom.
		\param position The position to test in the same coordinates that \em this widget is defined in.
		\param outList Filled with pointers to the Widgets that matched the query criteria
		\param recursive \c TRUE to recurse into the matching children, asking the same question. \c FALSE to only test the direct children of this widget.
		*/
		void getChildrenAt( const FVector2& position, WidgetPtrList& outList, bool recursive = false );
		//! Returns a pointer to the top-most child at the given \c position. Returns 0 if no child is found at the position.
		/*! \param position The position to test in the same coordinates that \em this widget is defined in.
		\param recursive \c TRUE to recurse into the matching child, asking the same question. \c FALSE to only test the direct children of this widget.
		*/
		Widget* getChildAt( const FVector2& position, bool recursive = false );

		//! Returns a pointer to the widget at the given path, 0 if no widget is found
		Widget* getPath( const std::string& path ) const;
		//! \internal follows the given \c pathList, returning the ending location. The \c pathList is modified along the way
		Widget* _getPath( StringList& pathList ) const;

		//! Translates the given point from coordinates local to this Widget into Screen level coordinates
		FVector2 pointToScreen( const FVector2& local_point );
		//! Translates the given point from Screen level coordinates into coordinates local to this Widget
		FVector2 pointFromScreen( const FVector2& screen_point );
		//! Translate the given point from local coordinates to inside coordinates
		virtual void _translatePointIn( FVector2& point );
		//! Translate the given point from inside coordinates to local coordinates
		virtual void _translatePointOut( FVector2& point );

		//! \internal prepares the Brush for use, calls eventDraw, and then ensures restored Brush to initial state
		virtual void _draw( Brush& brush );

		//!\internal injects tick events to this widget
		virtual void _tick( float seconds );

		//! Returns \c true if this Widget has cursor focus within its Screen
		bool hasCursorFocus();
		//! Returns \c true if this Widget has key focus within its Screen
		bool hasKeyFocus();

		//Object Functions
		virtual ObjectAccessorList* getAccessors();
		virtual unsigned int getObjectType() const;

		//! Returns true if the given point is inside this Widget
		virtual bool isInside( const FVector2& position );

		//! Informs this widget of cursor movement
		void _injectCursorMove( Cursor_EventArgs& moveEvent );
		//! Should inject the CursorMove event to all children
		virtual void _sendToChildren_CursorMove( Cursor_EventArgs& moveEvent );
		//! Informs this widget of cursor press
		void _injectCursorPress( Cursor_EventArgs& pressEvent );
		//! Should inject the CursorPress event to all children
		virtual void _sendToChildren_CursorPress( Cursor_EventArgs& pressEvent );
		//! Informs this widget of cursor release
		void _injectCursorRelease( Cursor_EventArgs& releaseEvent );
		//! Should inject the CursorRelease event to all children
		virtual void _sendToChildren_CursorRelease( Cursor_EventArgs& releaseEvent );
		//! Informs this widget of cursor focus acquisition
		void _injectCursorFocused( Widget* next, Widget* prev );
		//! Informs this widget of cursor focus loss
		void _injectCursorFocusLost( Widget* next, Widget* prev );

		//! Informs this widget of key down
		void _injectKeyDown( Key_EventArgs& evtArgs );
		//! Informs this widget of key press
		void _injectKeyPressed( Key_EventArgs& evtArgs );
		//! Informs this widget of key up
		void _injectKeyUp( Key_EventArgs& evtArgs );
		//! Informs this widget of key focus acquisition
		void _injectKeyFocused( Widget* next, Widget* prev );
		//! Informs this widget of key focus loss
		void _injectKeyFocusLost( Widget* next, Widget* prev );

	protected:
//!\name Event Triggers
//@{
		//! Widget was attached to a container
		void eventAttached( WidgetCollection* newContainer, Widget* widget );
		//! Widget was removed from a container
		void eventDetached( WidgetCollection* prevContainer, Widget* widget );

		//! Draw this object's foreground using the given brush
		void eventDraw( Brush& brush );
		//! Widget was invalidated and will need to be redrawn next Screen::update()
		void eventInvalidated();

		//! Widget's state has changed to Enabled
		void eventEnabled();
		//! Widget's state has changed to Disabled
		void eventDisabled();

		//! Called for cursor movement before sending to children, giving the X,Y position of the cursor
		bool eventCursorMoving( float xPos, float yPos );
		//! Called for cursor movement, giving the X,Y position of the cursor
		bool eventCursorMove( float xPos, float yPos );
		//! Called for cursor press before sending to children, giving the X,Y position of the cursor
		bool eventCursorPressing( float xPos, float yPos );
		//! Called when the cursor button is pressed
		bool eventCursorPress( float xPos, float yPos );
		//! Called for cursor release before sending to children, giving the X,Y position of the cursor
		bool eventCursorReleasing( float xPos, float yPos );
		//! Called when the cursor button is released
		bool eventCursorRelease( float xPos, float yPos );
		//! Called when the cursor enters this Control
		void eventCursorEnter();
		//! Called when the cursor leaves this Control
		void eventCursorLeave();
		//! Called then this widget receives cursor focus
		void eventCursorFocused( Widget* cur, Widget* prev );
		//! Called then this widget loses cursor focus
		void eventCursorFocusLost( Widget* cur, Widget* prev );

		//! Called when the given \c character is released
		bool eventKeyUp( char character );
		//! Called when the given \c character is pressed down
		bool eventKeyDown( char character );
		//! Called when the given \c character is entered
		bool eventKeyPressed( char character );
		//! Called then this widget receives key focus
		void eventKeyFocused( Widget* cur, Widget* prev );
		//! Called then this widget loses key focus
		void eventKeyFocusLost( Widget* cur, Widget* prev );

		//! Called when the passage of time has been measured
		void eventTick( float seconds );
//@}

//!\name Event Handlers
//@{
		//! "Attached" event
		virtual void onAttached( Object* sender, Attach_EventArgs& evtArgs );
		//! "Detached" event
		virtual void onDetached( Object* sender, Attach_EventArgs& evtArgs );

		//! "Draw" event
		virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );
		//! "Invalidated" event
		virtual void onInvalidated( Object* sender, EventArgs& evtArgs );

		//! "Enabled" event
		virtual void onEnabled( Object* sender, EventArgs& evtArgs );
		//! "Disabled" event
		virtual void onDisabled( Object* sender, EventArgs& evtArgs );

		//! "CursorMoving" event
		virtual void onCursorMoving( Object* sender, Cursor_EventArgs& evtArgs );
		//! "CursorMove" event
		virtual void onCursorMove( Object* sender, Cursor_EventArgs& evtArgs );
		//! "CursorPressing" event
		virtual void onCursorPressing( Object* sender, Cursor_EventArgs& evtArgs );
		//! "CursorPress" event
		virtual void onCursorPress( Object* sender, Cursor_EventArgs& evtArgs );
		//! "CursorReleasing" event
		virtual void onCursorReleasing( Object* sender, Cursor_EventArgs& evtArgs );
		//! "CursorRelease" event
		virtual void onCursorRelease( Object* sender, Cursor_EventArgs& evtArgs );
		//! "CursorEnter" event
		virtual void onCursorEnter( Object* sender, EventArgs& evtArgs );
		//! "CursorLeave" event
		virtual void onCursorLeave( Object* sender, EventArgs& evtArgs );
		//! "CursorFocused" event
		virtual void onCursorFocused( Object* sender, Focus_EventArgs& evtArgs );
		//! "CursorFocusLost" event
		virtual void onCursorFocusLost( Object* sender, Focus_EventArgs& evtArgs );

		//! "Key_Up" event
		virtual void onKeyUp( Object* sender, Key_EventArgs& evtArgs );
		//! "Key_Down" event
		virtual void onKeyDown( Object* sender, Key_EventArgs& evtArgs );
		//! "Key_Pressed" event
		virtual void onKeyPressed( Object* sender, Key_EventArgs& evtArgs );
		//! "Key_Focused" event
		virtual void onKeyFocused( Object* sender, Focus_EventArgs& evtArgs );
		//! "Key_FocusLost" event
		virtual void onKeyFocusLost( Object* sender, Focus_EventArgs& evtArgs );

		//! "Tick" event
		virtual void onTick( Object* sender, Tick_EventArgs& evtArgs );
//@}

		//! returns the screen that this Widget is attached to, or 0 if not attached
		Screen* getScreen() const;

		//! returns a pointer to the parenting Object of this Widget, or 0 if there isn't one
		Object* getParent() const;

		//! grabs focus for this Widget for keyboard events
		void grabKeyFocus();
		//! releases focus for this Widget for keyboard events
		void releaseKeyFocus();

		//! grabs focus for this Widget for cursor events
		void grabCursorFocus();
		//! releases focus for this Widget for cursor events
		void releaseCursorFocus();

		//! \internal virtual implementation for getChildrenAt(). Hidden because overriding is almost always unnecessary
		virtual void _getChildrenAt( const FVector2& position, WidgetPtrList& outList, bool recursive );
		//! \internal virtual implementation for getChildAt(). Hidden because overriding is almost always unnecessary
		virtual Widget* _getChildAt( const FVector2& position, bool recursive );

		//! \internal returns the child with the given name. Virtual so that container widgets can redefine it to fit their storage type. Default returns 0 always
		virtual Widget* _getChildByName( const std::string& childName ) const;

		//! \internal called by a child when they have been invalidated. Default does nothing. Override me if you need more functionality
		virtual void _invalidatedChild();
	private:
		WidgetCollection* mContainer; // <- managed by WidgetCollection. We should never touch this.
		bool mValid; // used to prevent multiple calls to invalidate from constantly causing Invalidated events

		bool mEnabled;
		std::string mWidgetName;
		bool m_CursorInside; // state variable used by _injectCursorMove()

		void _detaching(); // called directly before the detach occurs (used for last minute cleanup)
		void _attaching(); // called directly before the attach occurs
		void _doPointToScreen( FVector2& local_point );
		void _doPointFromScreen( FVector2& screen_point );

	};

} //namespace OpenGUI{

#endif // B2B428BD_BA97_41F4_AF2E_EF32498FC240
