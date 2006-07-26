#ifndef CA9C2935_B11D_417d_BC51_8FE0051168FD
#define CA9C2935_B11D_417d_BC51_8FE0051168FD

#include "OpenGUI_Event.h"
#include "OpenGUI_Message.h"

namespace OpenGUI{
	

	class Element; //forward declaration

	/*! \brief This is the typedef used for the Subscriber callback.

		Example usage:
\code
bool mySubscriberCallback(Element* eventReceiver, const Msg::Message& msg)
{
	return true;
}
\endcode
		\see \ref WhyCallbacks "Why Callbacks?"
	*/
	typedef bool (*Subscriber)(Element* eventReceiver, const Msg::Message& msg);

};//namespace OpenGUI{
#endif

