#ifndef B7CF3B5F_D4DC_4d03_99AF_67494B0B2E38
#define B7CF3B5F_D4DC_4d03_99AF_67494B0B2E38

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Object.h"
#include "OpenGUI_ObjectAccessor.h"
#include "OpenGUI_Event.h"
#include "OpenGUI_Brush.h"
#include "OpenGUI_RefPtr.h"

namespace OpenGUI {

	class Screen; // forward declaration

	//! Specialization of Draw_EventArgs for Cursor objects
	class OPENGUI_API DrawCursor_EventArgs: public Draw_EventArgs {
	public:
		//! Constructor requires the x and y position of the cursor and a valid Brush reference
		DrawCursor_EventArgs( float x_pos, float y_pos, Brush& brush )
				: Draw_EventArgs( brush ), Position( x_pos, y_pos ), X( Position.x ), Y( Position.y ) {
			/* All necessary action is performed pre-constructor */
		}
		virtual ~DrawCursor_EventArgs() {}
		//! The cursor position
		const FVector2 Position;
		//! The cursor X position
		const float& X;
		//! The cursor Y position
		const float& Y;
	};

	//! Base class for cursors
	/*! All cursors need to derive from this base class. Cursors are drawn using the same
	onDraw event logic that Widgets utilize, so creating custom cursors should be a fairly
	simple task for anyone with experience creating custom widgets. The only major differences
	between drawing a Widget and drawing a Cursor is that the onDraw event is called each time
	the Screen is updated, and the event arguments are of a different type (DrawCursor_EventArgs).

	You'll also notice that certain cursor related events are provided in the case that the Cursor
	requires this information. There is, however, a slight variation for the \c Cursor_Shown and
	\c Cursor_Hidden events. These events are called whenever this particular Cursor is being
	shown or hidden, respectively. This means that if a Widget in the GUI requests a different
	cursor, the current cursor will be given a \c Cursor_Hidden event, while the new cursor is
	given \c Cursor_Shown. All cursors can expect (and rely upon) a \c Cursor_Shown event before
	being receiving \c Draw events, but should not rely upon receiving \c Cursor_Hidden before
	they are destroyed. A cursor will never received \c Draw events after receiving \c Cursor_Hidden
	until a new \c Cursor_Shown is issued. Additionally, a cursor will only receive the other events
	(\c Cursor_Move, \c Cursor_Press, \c Cursor_Release) in between \c Cursor_Shown and \c Cursor_Hidden
	events. After receiving \c Cursor_Hidden, these events will no longer be issued to this cursor,
	so special care must be taken to properly deal with the potential that \c Cursor_Press does not
	ensure a complimenting \c Cursor_Release, as the cursor may be hidden in between those two events.
	The reverse logic is also true, in that \c Cursor_Release may be received without ever first
	receiving \c Cursor_Press.

	The Brush that is given in the \c DrawCursor_EventArgs of \c onDraw() is always in the context
	of the Screen as a whole.

	\note
	Take notice that, while the input related events reuse the same EventArgs, cursors cannot
	consume events. So whether you \c eat() the event or not makes no difference.
	*/
	class OPENGUI_API Cursor: public Object {
		friend class Screen; // Screen needs access to the protected input event triggers
	public:
		Cursor();
		virtual ~Cursor();

	protected:
//!\name Event Handlers
//@{
		//! "Draw" event
		virtual void onDraw( Object* sender, DrawCursor_EventArgs& evtArgs );

		//! "Cursor_Move" event
		virtual void onCursor_Move( Object* sender, Cursor_EventArgs& evtArgs );
		//! "Cursor_Press" event
		virtual void onCursor_Press( Object* sender, Cursor_EventArgs& evtArgs );
		//! "Cursor_Release" event
		virtual void onCursor_Release( Object* sender, Cursor_EventArgs& evtArgs );
		//! "Cursor_Hidden" event
		virtual void onCursor_Hidden( Object* sender, Cursor_EventArgs& evtArgs );
		//! "Cursor_Shown" event
		virtual void onCursor_Shown( Object* sender, Cursor_EventArgs& evtArgs );
//@}

//!\name Event Processors
//@{
		//! Draw this object's foreground using the given brush
		void eventDraw( float xPos, float yPos, Brush& brush );

		//! Called for cursor movement, giving the X,Y position of the cursor
		void eventCursor_Move( float xPos, float yPos );
		//! Called when the cursor button is pressed
		void eventCursor_Press( float xPos, float yPos );
		//! Called when the cursor button is released
		void eventCursor_Release( float xPos, float yPos );
		//! Called when the cursor is hidden
		void eventCursor_Hidden();
		//! Called when the cursor is shown.
		void eventCursor_Shown( float xPos, float yPos );
//@}

		//Object Functions
		virtual ObjectAccessorList* getAccessors();
		virtual char* getClassName();
	};

	//! Reference counted, auto deleting Cursor pointer
	typedef RefPtr<Cursor> CursorPtr;
}//namespace OpenGUI{

#endif // B7CF3B5F_D4DC_4d03_99AF_67494B0B2E38
