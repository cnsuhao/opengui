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
	/*! Windows are ContainerControls that cache the output of their children
	*/
	class OPENGUI_API Window : public ContainerControl {
	public:
		//! public constructor
		Window();
		//! public destructor
		virtual ~Window();


		//! window
		void window();



		//Object Functions
		virtual ObjectAccessorList* getAccessors();
		virtual char* getClassName();
	protected:
	private:
	};

} // namespace OpenGUI{

#endif // B3FCBF40_F18D_4102_BE5C_33E8A087C5D1
