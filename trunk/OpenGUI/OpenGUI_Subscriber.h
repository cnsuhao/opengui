#ifndef CA9C2935_B11D_417d_BC51_8FE0051168FD
#define CA9C2935_B11D_417d_BC51_8FE0051168FD
#include "OpenGUI_Functors.h"
#include "OpenGUI_Event.h"
namespace OpenGUI{
	

	class Element; //forward declaration
	/*! This is the typedef used for casting to the Subscriber interface,
		as well as used internally for creating Subscriber objects. */
	typedef Functors::GenericFunctorImpl_Ret_2Arg<bool, const Msg::Message&, Element*> Subscriber;

};//namespace OpenGUI{
#endif