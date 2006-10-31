#ifndef B3FCBF40_F18D_4102_BE5C_33E8A087C5D1
#define B3FCBF40_F18D_4102_BE5C_33E8A087C5D1

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Widget.h"
#include "OpenGUI_I_WidgetContainer.h"
#include "OpenGUI_Control.h"
#include "OpenGUI_ContainerControl.h"

namespace OpenGUI {

	//! base class for Windows
	/*! Windows are ContainerControls that cache the output of their children.
	They also provide some basic built in window-like functionality, such as
	resizing and moving based on cursor input. It is up to the inheriting class
	to initiate and end these behaviors via the eventMove_Begin(), eventMove_End(),
	eventResize_Begin(), eventResize_End() functions. You will also need to
	ensure that m_Moveable and m_Resizable have the proper values, as they provide
	an overall lock mechanism for the built in functions.

	\par Events Introduced
		- \ref Event_Move_Begin "Move_Begin"
		- \ref Event_Move_End "Move_End"
		- \ref Event_Resize_Begin "Resize_Begin"
		- \ref Event_Resize_End "Resize_End"
	\see \ref EventList_Window "Window Events"
	*/
	class OPENGUI_API Window : public ContainerControl {
	public:
		//! public constructor
		Window();
		//! public destructor
		virtual ~Window();

//!\name Event Injectors
//@{
		//! Called to trigger beginning of a click & drag move sequence
		void eventMove_Begin();
		//! Called to trigger end of a click & drag move sequence
		void eventMove_End();
		//! Called to trigger beginning of a click & drag resize sequence
		void eventResize_Begin();
		//! Called to trigger end of a click & drag resize sequence
		void eventResize_End();
//@}

		//Object Functions
		virtual ObjectAccessorList* getAccessors();
		virtual char* getClassName();

	protected:
//!\name Event Handlers
//@{
		//! "Move_Begin" event
		virtual void onMove_Begin( Object* sender, EventArgs& evtArgs );
		//! "Move_End" event
		virtual void onMove_End( Object* sender, EventArgs& evtArgs );
		//! "Resize_Begin" event
		virtual void onResize_Begin( Object* sender, EventArgs& evtArgs );
		//! "Resize_End" event
		virtual void onResize_End( Object* sender, EventArgs& evtArgs );
//@}

		//! Sets if Window is resizable
		/*! This toggles if this Window will perform automatic resizing when triggered
		to do so by \c Resize_Begin events. The default value is \c false, which will
		cause the Window to ignore \c Resize_Begin events. */
		bool m_Resizable;
		//! Sets if Window is movable
		/*! This toggles if this Window will perform automatic moving when triggered
		to do so by \c Move_Begin events. The default value is \c false, which will
		cause the Window to ignore \c Move_Begin events. */
		bool m_Moveable;

	private:
		bool mMoving;
		bool mResizing;
		FVector2 mInitial; // used by both auto move and auto resize to hold an initial value
	};

} // namespace OpenGUI{

#endif // B3FCBF40_F18D_4102_BE5C_33E8A087C5D1
