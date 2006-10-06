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
	class OPENGUI_API ContainerControl : public Control, public I_WidgetContainer {
	public:
		//! public constructor
		ContainerControl();
		//! public destructor
		virtual ~ContainerControl();


		//! containercontrol
		void containercontrol();


		//Object Functions
		virtual ObjectAccessorList* getAccessors();
		virtual char* getClassName();
	protected:
	private:
	};

} // namespace OpenGUI{

#endif // C98415A7_E835_4241_AC5B_7DB94CB10233
