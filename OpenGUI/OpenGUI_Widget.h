#ifndef B2B428BD_BA97_41F4_AF2E_EF32498FC240
#define B2B428BD_BA97_41F4_AF2E_EF32498FC240

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Object.h"
#include "OpenGUI_ObjectAccessor.h"
#include "OpenGUI_Brush.h"

namespace OpenGUI {

	class Renderer; //forward declaration
	class I_WidgetContainer; //forward declaration
	class Screen;

	//! Base class for all input processing, containable GUI objects
	class OPENGUI_API Widget : public Object {
		friend class I_WidgetContainer; //we'll need this so containers can manage our handle to them
		friend class Screen; // Screen needs access to the protected input event triggers
	public:
		//! public constructor
		Widget();
		//! public destructor
		virtual ~Widget();


		//! returns the name of this Widget
		const std::string& getName();
		//! sets the name of this Widget
		void setName( const std::string& name );

		//! invalidate any caches of this Widget's render output
		/*! This will cause the Widget's Draw routine to be called on the next
		update of the Screen this Widget is attached to. */
		void invalidate();

		//! invalidate this Widget, as well as any and all potential children
		void flush();


		//! returns the container this widget is held within
		/*! Every Widget is guaranteed to have a container, but not every container is
			guaranteed to be a Widget. To test if the returned pointer is, in fact, another
			Widget you should perform a dynamic_cast on the returned pointer.
			\code
			//optionally replace "this" with a pointer to the desired child Widget
			Widget* myParent = dynamic_cast<Widget*>( this->getContainer() );
			\endcode */
		I_WidgetContainer* getContainer();



		//Object Functions
		virtual ObjectAccessorList* getAccessors();
		virtual char* getClassName();

	protected:
//!\name Event Handlers
//@{
		/*
		//! Called whenever this widget needs to redraw itself.
		virtual void onDraw( Brush& brushRef );
		virtual void onMove();

		virtual void onCursor_Enter();
		virtual void onCursor_Leave();
		virtual void onCursor_Move();

		virtual void onActivate();
		*/

		//! "Attached" event
		virtual void onAttached();
		//! "Detached" event
		virtual void onDetached();
//@}

//!\name Event Triggers
//@{
		//! Widget was attached to a container
		virtual void eventAttached( I_WidgetContainer* newParent ) {}
		//! Widget was removed from a container
		virtual void eventDetached( I_WidgetContainer* prevParent ) {}

		//! Draws this object
		virtual void eventDraw() {}
		//! Widget is invalidate and will need to be redrawn next Screen::update()
		virtual void eventInvalidated() {}

		//! Called for cursor movement
		virtual void eventCursor_Move() {}

		/*

		Move_Begin
		Moving
		Move_End
		Moved

		Move_Begin
		Moving
		Move_End
		Moved

		Resize_Being
		Resizing
		Resize_End
		Resized

		Cursor_Enter
		Cursor_Leave
		Cursor_Move
		Cursor_Press
		Cursor_Release
		Cursor_Click

		Menu_Up
		Menu_Down
		Menu_Left
		Menu_Right
		Menu_Targeted
		Menu_UnTargeted
		Menu_Activate

		Targeted
		UnTargeted

		Focus
		Focus_Lost

		Activated
		*/
//@}
		//! returns the screen that this Widget is attached to, or 0 if not attached
		Screen* getScreen();
		void _doflush();
	private:
		std::string mWidgetName;
		I_WidgetContainer* mContainer;
	};

} //namespace OpenGUI{

#endif // B2B428BD_BA97_41F4_AF2E_EF32498FC240
