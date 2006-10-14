#ifndef C98415A7_E835_4241_AC5B_7DB94CB10233
#define C98415A7_E835_4241_AC5B_7DB94CB10233

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Widget.h"
#include "OpenGUI_I_WidgetContainer.h"
#include "OpenGUI_Control.h"

namespace OpenGUI {

	//! base class for all Controls that are also containers
	/*!
	In addition to simply being a Control that contains child Controls, this Widget
	also supplies an automatic layout system that will reposition and resize child controls
	according to their exposed layout preferences.

	\par Events
	- ChildAttached
	- ChildDetached
	\see \ref EventList_ContainerControl "ContainerControl Events"
	*/
	class OPENGUI_API ContainerControl : public Control, public I_WidgetContainer {
	public:
		//! public constructor
		ContainerControl();
		//! public destructor
		virtual ~ContainerControl();

		//! suspends automatic layout updates until resumeLayout() is called
		void suspendLayout();
		//! resumes automatic layout updates and performs an immediate layout update if the current layout is out of date
		void resumeLayout();
		//! returns true if the current layout schema is still valid
		bool layoutValid();
		//! Performs the layout operation for child widgets, marking the new layout as valid.
		void updateLayout();
		//! Marks the current layout schema as invalid.
		void invalidateLayout();

		//! \internal In addition to previous functionality, this adds a "DrawBG" operation and calls the children _draw between the foreground and background onDraws
		virtual void _draw( Brush& brush );

		//Object Functions
		virtual ObjectAccessorList* getAccessors();
		virtual char* getClassName();

	protected:
//!\name Event Handlers
//@{
		//! "DrawBG" event
		virtual void onDrawBG( Object* sender, Draw_EventArgs& evtArgs );
		//! "ChildAttached" event
		virtual void onChildAttached( Object* sender, Attach_EventArgs& evtArgs );
		//! "ChildDetached" event
		virtual void onChildDetached( Object* sender, Attach_EventArgs& evtArgs );
//@}

//!\name Event Processors
//@{
		//! Draw this object's background using the given brush
		void eventDrawBG( Brush& brush );
		//! A new child has been attached to this container
		void eventChildAttached( I_WidgetContainer* container, Widget* newChild );
		//! A child has been detached from this container
		void eventChildDetached( I_WidgetContainer* container, Widget* prevChild );
//@}

		//! Returns the client area position and size
		virtual const FRect& getClientArea();

		//! This performs the actual layout operation
		virtual void _doUpdateLayout();

	private:
		void _setChildControlLayoutState( bool state );
		bool m_LayoutSuspended; // state variable: marks if layouts are suspended
		bool m_LayoutValid; // state variable: holds layout validity
		bool m_InUpdateLayout; // state variable: true if currently running updateLayout()

		FRect m_RemClntArea;
	};

} // namespace OpenGUI{

#endif // C98415A7_E835_4241_AC5B_7DB94CB10233
