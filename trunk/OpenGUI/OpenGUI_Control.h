#ifndef F9497A73_9AD4_4241_8A38_7566DBC752BE
#define F9497A73_9AD4_4241_8A38_7566DBC752BE

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Widget.h"
#include "OpenGUI_I_WidgetContainer.h"

namespace OpenGUI {

	//! Base class for all GUI objects that have position and size
	/*!
	\par Properties
	- Left (setLeft, getLeft)
	- Top (setTop, getTop)
	- Width (setWidth, getWidth)
	- Height (setHeight, getHeight)
	- Position (getPosition)
	- Size (getSize)
	- Rect (getRect)

	\par Events
	- Cursor_Click (onCursor_Click, eventCursor_Click)
	- Cursor_Enter (onCursor_Enter, eventCursor_Enter)
	- Cursor_Leave (onCursor_Leave, eventCursor_Leave)
	*/
	class OPENGUI_API Control : public Widget {
	public:
		//! public constructor
		Control();
		//! public destructor
		virtual ~Control();

		//! Sets the position of the left side of the Control
		void setLeft( float left );
		//! Returns the position of the left side of the Control
		float getLeft();
		//! Sets the position of the top side of the Control
		void setTop( float top );
		//! Returns the position of the top side of the Control
		float getTop();
		//! Sets the width of the Control
		void setWidth( float width );
		//! Returns the width of the Control
		float getWidth();
		//! Sets the height of the Control
		void setHeight( float height );
		//! Returns the height of the Control
		float getHeight();

		//! Returns the position of the upper left corner of the Control
		const FVector2& getPosition();
		//! Returns the size of the Control
		FVector2 getSize();
		//! Returns the FRect describing this Control's size and position
		const FRect& getRect();

		//Object Functions
		virtual ObjectAccessorList* getAccessors();
		virtual char* getClassName();

	protected:
//!\name Event Handlers
//@{
		//! "Cursor_Click" event
		virtual void onCursor_Click( Object* sender, EventArgs& evtArgs );
		//! "Cursor_Enter" event
		virtual void onCursor_Enter( Object* sender, EventArgs& evtArgs );
		//! "Cursor_Leave" event
		virtual void onCursor_Leave( Object* sender, EventArgs& evtArgs );
//@}

//!\name Event Processors
//@{
		//! Called when cursor was pressed and released within this Control
		virtual void eventCursor_Click();
		//! Called when the cursor enters this Control
		virtual void eventCursor_Enter();
		//! Called when the cursor leaves this Control
		virtual void eventCursor_Leave();
//@}

		/*
		Move_Begin
		Moving
		Move_End
		Moved

		Resize_Being
		Resizing
		Resize_End
		Resized


		Menu_Up
		Menu_Down
		Menu_Left
		Menu_Right
		Menu_Activate
		Menu_Targeted
		Menu_UnTargeted

		Targeted
		UnTargeted

		Focus
		Focus_Lost

		Activated
		*/
	private:
		FRect mRect; // position & size of this Control
	};

} // namespace OpenGUI{

#endif // F9497A73_9AD4_4241_8A38_7566DBC752BE
