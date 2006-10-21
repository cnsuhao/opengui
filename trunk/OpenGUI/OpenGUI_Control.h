#ifndef F9497A73_9AD4_4241_8A38_7566DBC752BE
#define F9497A73_9AD4_4241_8A38_7566DBC752BE

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Widget.h"
#include "OpenGUI_I_WidgetContainer.h"

namespace OpenGUI {
	class ContainerControl; //forward declaration

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
	- Visible (setVisible, getVisible)
	- Alpha (setAlpha, getAlpha)

	\par Events
	- Moved
	- Resized
	- Cursor_Click
	- Cursor_Enter
	- Cursor_Leave
	- Targeted
	- UnTargeted
	\see \ref EventList_Control "Control Events"
	*/
	class OPENGUI_API Control : public Widget {
		friend class ContainerControl; //needed for layout state protection
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

		//! Returns the minimum size this Control will allow itself to be resized to
		const FVector2& getMinimumSize();
		//! Sets the minimum size this Control will allow itself to be resized to
		void setMinimumSize( const FVector2& size );
		//! Returns the maximum size this Control will allow itself to be resized to
		const FVector2& getMaximumSize();
		//! Sets the maximum size this Control will allow itself to be resized to
		void setMaximumSize( const FVector2& size );

		//! Sets the visibility of this Control
		void setVisible( bool visible );
		//! Returns the visibility of this Control
		bool getVisible();

		//! Sets the alpha transparency of this Control
		void setAlpha( float alpha );
		//! Returns the alpha transparency of this Control
		float getAlpha();

		//Object Functions
		virtual ObjectAccessorList* getAccessors();
		virtual char* getClassName();

		//! Values used by get/setDocking and get/setAnchor
		enum ControlSides {
			None = 0, //!< No side
			Left = 1, //!< Left side
			Right = 1 << 1, //!< Right side
			Top = 1 << 2, //!< Top side
			Bottom = 1 << 3, //!< Bottom side
			All = Left | Right | Top | Bottom, //!< All sides
			Fill = All //!< Alias for All sides
		};

		//! Sets the docking preference for this Control
		void setDocking( int dockStyle );
		//! Gets the current docking preference for this Control
		int getDocking();

		//! Sets the anchored sides for this Control
		void setAnchor( int anchoredSides );
		//! Gets the current anchored sides for this control
		int getAnchor();

		//! \internal In addition to previous functionality, this enforces Alpha and Visibility before the Draw event is issued
		virtual void _draw( Brush& brush );

	protected:
//!\name Event Handlers
//@{
		//! "Moved" event
		virtual void onMoved( Object* sender, Moved_EventArgs& evtArgs );
		//! "Resized" event
		virtual void onResized( Object* sender, Resized_EventArgs& evtArgs );

		//! "Cursor_Click" event
		virtual void onCursor_Click( Object* sender, Cursor_EventArgs& evtArgs );
		//! "Cursor_Enter" event; invokes Targeted
		virtual void onCursor_Enter( Object* sender, Cursor_EventArgs& evtArgs );
		//! "Cursor_Leave" event; invokes UnTargeted
		virtual void onCursor_Leave( Object* sender, Cursor_EventArgs& evtArgs );

		//! Adds cursor tracking to trigger Cursor_Enter and Cursor_Leave when appropriate.
		virtual void onCursor_Move( Object* sender, Cursor_EventArgs& evtArgs );

		//! "Targeted" event
		virtual void onTargeted( Object* sender, EventArgs& evtArgs );
		//! "UnTargeted" event
		virtual void onUnTargeted( Object* sender, EventArgs& evtArgs );
//@}

//!\name Event Injectors
//@{
		//! Control has been moved
		void eventMoved( const FVector2& oldPosition, const FVector2& newPosition );
		//! Control has been resized
		void eventResized( const FVector2& oldSize, const FVector2& newSize );

		//! Called when cursor was pressed and released within this Control
		void eventCursor_Click( Cursor_EventArgs& evtArgs );
		//! Called when the cursor enters this Control
		void eventCursor_Enter( Cursor_EventArgs& evtArgs );
		//! Called when the cursor leaves this Control
		void eventCursor_Leave( Cursor_EventArgs& evtArgs );

		//! Called when this Control is targeted, either by cursor or by menu navigation
		void eventTargeted();
		//! Called when this Control is no longer targeted, either by cursor or by menu navigation
		void eventUnTargeted();
//@}

	private:
		//! Call for any operation that invalidates layouts, like moves and resizes.
		void _invalidateLayout();
		//! Call for any operation that breaks docking. (Moves and resizes along a conflicting axis)
		void _breakDocking();

		FRect mRect; // position & size of this Control
		bool mVisible; // visibility of this Control
		float mAlpha; // alpha of this Control
		FVector2 mMinSize; // Minimum Size
		FVector2 mMaxSize; // Maximum Size

		int mAnchors; // anchored sides
		int mDock; // docking preference

		bool mCursorInside; // cursor position state variable
		bool m_InDockAnchor; // prevents re-entry into setDocking/setAnchor
		bool m_InLayout; // managed entirely by ContainerControl.
		// ^-- Signifies that layout is in process, so ignore invalidations and docking breaking operations

	};

} // namespace OpenGUI{

#endif // F9497A73_9AD4_4241_8A38_7566DBC752BE
