#ifndef CA9C2935_B11D_417d_BC51_8FE0051168FD
#define CA9C2935_B11D_417d_BC51_8FE0051168FD
#include "OpenGUI_Event.h"
namespace OpenGUI{
	
	/*
		This is a generic subscriber class type to which all user subscribers are cast.
		C++ is a little wierd on member function callbacks, so here's the hack that makes it work.
	*/
	class SubscriberGeneric{};

	/*
		This is the implementation of the subscriber object. It only supports 1 argument,
		and requires a non-void return value. It's specialized as much as it can be.
	*/
	template <typename RET, typename ARG, typename ARG2, class Class=SubscriberGeneric>
	class SubscriberImpl{
	public:
		//! Default constructor
		SubscriberImpl() : mcPtr(0),mmPtr(0),mfPtr(0) {}
		
		//! Constructor to build SubscriberImpl from a class object pointer and member function
		template<class T>
		SubscriberImpl(void* classPtr,RET(T::*memberPtr)(ARG,ARG2));

		//! Constructor to build SubscriberImpl from a function pointer
		SubscriberImpl(RET(*funcPtr)(ARG,ARG2));


		//!Calls the bound function and returns the result
		RET Call(ARG arg,ARG2 arg2){
			if(mcPtr && mmPtr)
				return (mcPtr->*mmPtr)(arg,arg2);
			if(mfPtr)
				return (*mfPtr)(arg,arg2);
			throw "f";
		}

		//! Declaraion of assignment operator
		template <class Class>
		SubscriberImpl& operator=(SubscriberImpl<RET,ARG,ARG2,Class>& right){
			mcPtr=reinterpret_cast<SubscriberGeneric*>(right.mcPtr);
			mmPtr=reinterpret_cast<void(SubscriberGeneric::*)()>(right.mmPtr);
			return (*this);
		}
		bool operator==(SubscriberImpl<RET,ARG,ARG2,Class>& right){
			return mcPtr == right.mcPtr && mmPtr == right.mmPtr && mfPtr == right.mfPtr;
		}
	private:
		Class* mcPtr; //class object pointer
		(RET)(Class::* mmPtr)(ARG,ARG2); //member function pointer
		(RET)(*mfPtr)(ARG,ARG2); //normal function pointer
	};
//#####################################################################
	template <typename RET, typename ARG, typename ARG2, class Class>
		template<class T>
		SubscriberImpl<RET,ARG,ARG2,Class>::
		SubscriberImpl(void* t,RET(T::*f)(ARG,ARG2))
	{
		mcPtr=reinterpret_cast<Class*>(t);
		mmPtr=reinterpret_cast<RET(Class::*)(ARG,ARG2)>(f);
		mfPtr=0;
	}
//#####################################################################
	template <typename RET, typename ARG, typename ARG2, class Class>
		SubscriberImpl<RET,ARG,ARG2,Class>::
		SubscriberImpl(RET(*funcPtr)(ARG,ARG2))
	{
		mcPtr=0;
		mmPtr=0;
		mfPtr=funcPtr;
	}
//#####################################################################

	class Element; //forward declaration
	/*! This is the typedef used for casting to the Subscriber interface,
		as well as used internally for creating Subscriber objects. */
	typedef SubscriberImpl<bool, const Msg::Message&, Element*> Subscriber;

};//namespace OpenGUI{
#endif