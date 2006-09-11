#ifndef BA005A9D_5FCE_4363_A3C3_CDE071FA13B5
#define BA005A9D_5FCE_4363_A3C3_CDE071FA13B5

#include "OpenGUI_Types.h"
#include "OpenGUI_MouseButton.h"

namespace OpenGUI{
		
	namespace Msg{

		//! Contains all the event specific structs that are used
		namespace EventData{

			//! Event specific data struct.
			struct MouseButtonEvent{
				unsigned int mouseButtonID;//!< The mouse button ID. \see OpenGUI::MouseButton
			};

			//! Event specific data struct.
			struct MouseMoveEvent{
				FVector2 mousePosition; //!< The new mouse position in absolute world space coordinates.
			};

			//! Event specific data struct.
			struct KeyEvent{
				char key; //!< ASCII char of the key
			};

			//! Event specific data struct.
			struct TickEvent{
				unsigned int timeDelta; //!< The time delta in milliseconds since the previous tick event
			};


		};//namespace EventData{
	};//namespace Msg{
};//namespace OpenGUI{
#endif
