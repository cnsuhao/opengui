#ifndef B2B428BD_BA97_41F4_AF2E_EF32498FC240
#define B2B428BD_BA97_41F4_AF2E_EF32498FC240

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Object.h"
#include "OpenGUI_ObjectAccessor.h"
#include "OpenGUI_Event.h"
#include "OpenGUI_Brush.h"

namespace OpenGUI {

	class Renderer; //forward declaration
	class I_WidgetContainer; //forward declaration
	class Screen;

	//! Base class for all input processing, containable, and potentially visible GUI objects
	/*!
	\par Properties
		- Name (setName, getName)

	\par Events
		- Attached
		- Detached
		- Draw
		- Invalidated
		- Cursor_Move
		- Cursor_Press
		- Cursor_Release
		- Cursor_Hidden
		- Cursor_Shown
		\see \ref EventList_Widget "Widget Events"
	*/
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
		//! Widget was attached to a container
		void eventAttached( I_WidgetContainer* newParent, Widget* widget );
		//! Widget was removed from a container
		void eventDetached( I_WidgetContainer* prevParent, Widget* widget );

		//! Draw this object using the given brush
		void eventDraw( Brush& brush );
		//! Widget was invalidated and will need to be redrawn next Screen::update()
		void eventInvalidated();

		//! Widget's state has changed to Enabled
		void eventEnabled();
		//! Widget's state has changed to Disabled
		void eventDisabled();

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
		//! returns the screen that this Widget is attached to, or 0 if not attached
		Screen* getScreen();
		void _doflush();
	private:
		I_WidgetContainer* mContainer;
		bool mValid; // used to prevent multiple calls to invalidate from constantly causing Invalidated events

		bool mEnabled;
		std::string mWidgetName;
	};

} //namespace OpenGUI{

#endif // B2B428BD_BA97_41F4_AF2E_EF32498FC240
