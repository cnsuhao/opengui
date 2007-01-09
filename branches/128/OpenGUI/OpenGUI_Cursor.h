// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef B7CF3B5F_D4DC_4d03_99AF_67494B0B2E38
#define B7CF3B5F_D4DC_4d03_99AF_67494B0B2E38

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_String.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Object.h"
#include "OpenGUI_ObjectAccessor.h"
#include "OpenGUI_Event.h"
#include "OpenGUI_Brush.h"
#include "OpenGUI_RefPtr.h"

namespace OpenGUI {

	class Screen; // forward declaration
	class CursorManager; // forward declaration

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
	the Screen is updated and is never cached, and the event arguments are of a different type
	(DrawCursor_EventArgs). The Brush that is given in the \c DrawCursor_EventArgs of \c onDraw()
	is always in the context of the Screen as a whole, so you need to apply your own
	Brush::pushPosition() as necessary.

	\note
	Take notice that, while the input related events reuse the same EventArgs, cursors cannot
	consume events. So whether you \c eat() the event or not makes no difference.

	\note
	When implementing your own cursors, you should take notice of the \c Size property that
	the Cursor base class exposes. This property represents the display size of the cursor
	for both the X and Y axis in Screen units. If the size is never specified by the application
	it will be the default size of (20.0x20.0f).

	\see \ref EventList_Control "Cursor Events"
	*/
	class OPENGUI_API Cursor: public Object {
		friend class Screen; // Screen needs access to the protected input event triggers
		friend class CursorManager;
	public:
		Cursor();
		virtual ~Cursor();

		//! return the name of this cursor, as set by the CursorManager at creation
		const String& getName() const {
			return mName;
		}

		//! returns the size of this cursor
		const FVector2& getSize() const {
			return mSize;
		}
		//! sets the size of this cursor
		void setSize( const FVector2& newSize ) {
			mSize = newSize;
		}
//!\name Event Injectors
//@{
		//! Draw this object's foreground using the given brush
		void eventDraw( float xPos, float yPos, Brush& brush );

		//! Called for cursor movement, giving the X,Y position of the cursor
		void eventCursorMove( float xPos, float yPos );
		//! Called when the cursor button is pressed
		void eventCursorPress( float xPos, float yPos );
		//! Called when the cursor button is released
		void eventCursorRelease( float xPos, float yPos );
		//! Called when the cursor is hidden
		void eventCursorHidden();
		//! Called when the cursor is shown.
		void eventCursorShown( float xPos, float yPos );
//@}

		//Object Functions
		virtual ObjectAccessorList* getAccessors();
		virtual unsigned int getObjectType() const;

	protected:
//!\name Event Handlers
//@{
		//! "Draw" event
		virtual void onDraw( Object* sender, DrawCursor_EventArgs& evtArgs );

		//! "CursorMove" event
		virtual void onCursorMove( Object* sender, Cursor_EventArgs& evtArgs );
		//! "CursorPress" event
		virtual void onCursorPress( Object* sender, Cursor_EventArgs& evtArgs );
		//! "CursorRelease" event
		virtual void onCursorRelease( Object* sender, Cursor_EventArgs& evtArgs );
		//! "CursorHidden" event
		virtual void onCursorHidden( Object* sender, EventArgs& evtArgs );
		//! "CursorShown" event
		virtual void onCursorShown( Object* sender, Cursor_EventArgs& evtArgs );
//@}

	private:
		String mName;
		FVector2 mSize;
	};

	//! Reference counted, auto deleting Cursor pointer
	typedef RefPtr<Cursor> CursorPtr;
}//namespace OpenGUI{

#endif // B7CF3B5F_D4DC_4d03_99AF_67494B0B2E38
