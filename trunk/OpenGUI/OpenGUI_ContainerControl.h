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

		//Object Functions
		virtual ObjectAccessorList* getAccessors();
		virtual char* getClassName();

	protected:
//!\name Event Handlers
//@{
		//! "ChildAttached" event
		virtual void onChildAttached( Object* sender, Attach_EventArgs& evtArgs );
		//! "ChildDetached" event
		virtual void onChildDetached( Object* sender, Attach_EventArgs& evtArgs );
//@}

//!\name Event Processors
//@{
		//! A new child has been attached to this container
		void eventChildAttached( I_WidgetContainer* container, Widget* newChild );
		//! A child has been detached from this container
		void eventChildDetached( I_WidgetContainer* container, Widget* prevChild );
//@}
	private:
	};

} // namespace OpenGUI{

#endif // C98415A7_E835_4241_AC5B_7DB94CB10233
