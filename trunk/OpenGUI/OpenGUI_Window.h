#ifndef B3FCBF40_F18D_4102_BE5C_33E8A087C5D1
#define B3FCBF40_F18D_4102_BE5C_33E8A087C5D1

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Widget.h"
#include "OpenGUI_Control.h"
#include "OpenGUI_ContainerControl.h"

namespace OpenGUI {
	//! EventArgs used for "Resize_Begin" event
	class OPENGUI_API WindowResizeBeginEventArgs: public EventArgs {
	public:
		//! constructor specifies any axis reversals
		WindowResizeBeginEventArgs( bool sizeHeight, bool revHeight, bool sizeWidth, bool revWidth )
				: sizingHeight( sizeHeight ), reverseHeight( revHeight ), sizingWidth( sizeWidth ), reverseWidth( revWidth ) {
			/**/
		}
		const bool sizingHeight; //!< are we sizing the height?
		const bool reverseHeight; //!< is the height axis reversed?
		const bool sizingWidth; //!< are we sizing the width?
		const bool reverseWidth; //!< is the width axis reversed?
	};

	//! base class for Windows
	/*! Windows are ContainerControls that provide some basic built in window-like
	functionality, such as resizing and moving based on cursor input. It is up to
	the inheriting class to initiate and end these behaviors via the
	eventMove_Begin(), eventMove_End(), eventResize_Begin(), eventResize_End()
	functions. You will also need to ensure that m_Moveable and m_Resizable have
	the proper values, as they provide an overall lock mechanism for the built in
	functions.

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
		void eventResize_Begin( bool sizeHeight = true, bool sizeWidth = true, bool revWidth = false, bool revHeight = false );
		//! Called to trigger end of a click & drag resize sequence
		void eventResize_End();
//@}
		bool isMoving() const;
		bool isResizing() const;

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
		virtual void onResize_Begin( Object* sender, WindowResizeBeginEventArgs& evtArgs );
		//! "Resize_End" event
		virtual void onResize_End( Object* sender, EventArgs& evtArgs );

		virtual void onCursor_Move( Object* sender, Cursor_EventArgs& evtArgs );
		virtual void onCursor_Focused( Object* sender, Focus_EventArgs& evtArgs );
		virtual void onCursor_FocusLost( Object* sender, Focus_EventArgs& evtArgs );
//@}

	private:
		typedef enum {
			RS_NONE    = 0,
			RS_SWIDTH  = 0x01,
			RS_SHEIGHT = 0x02,
			RS_RWIDTH  = 0x04,
			RS_RHEIGHT = 0x08,
			RS_UL = RS_SWIDTH | RS_SHEIGHT | RS_RHEIGHT | RS_RWIDTH,
			RS_LL = RS_SWIDTH | RS_SHEIGHT | RS_RWIDTH,
			RS_UR = RS_SWIDTH | RS_SHEIGHT | RS_RHEIGHT,
			RS_LR = RS_SWIDTH | RS_SHEIGHT,
		}
		ResizeState;
		bool m_Moving;
		ResizeState m_Resizing;
		FVector2 mInitialPos; // holds the initial position for auto resize/move
		FVector2 mInitialSize; // holds the initial size for auto resize/move
		FVector2 mInitialCursor; // holds the initial cursor position for auto resize/move
	};

} // namespace OpenGUI{

#endif // B3FCBF40_F18D_4102_BE5C_33E8A087C5D1
