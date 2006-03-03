
#ifndef E85F2599_5955_41a1_B2CB_9406ED0200B3
#define E85F2599_5955_41a1_B2CB_9406ED0200B3



namespace OpenGUI{
	namespace Functors{
		/*
		This is a generic functor class type to which all functor objects are cast.
		C++ is a little wierd on member function callbacks, so here's the hack that makes it work.
		*/
		class GenericFunctorClass{};


		/*
		Following are the implementations for 10 different generic functor classes.
		Currently, there are functor classes available for functions with 0 to 4 arguments,
		both with and without return values.

		The classes are:

		GenericFunctorImpl_Ret_0Arg
		GenericFunctorImpl_NoRet_0Arg

		GenericFunctorImpl_Ret_1Arg
		GenericFunctorImpl_NoRet_1Arg

		GenericFunctorImpl_Ret_2Arg
		GenericFunctorImpl_NoRet_2Arg

		GenericFunctorImpl_Ret_3Arg
		GenericFunctorImpl_NoRet_3Arg

		GenericFunctorImpl_Ret_4Arg
		GenericFunctorImpl_NoRet_4Arg

		Their names should give away their functionality.

		A simple usage example:

		typedef GenericFunctorImpl_Ret_1Arg<bool,int> Ret1Arg;

		class testerClass1{
		public:
		virtual bool myRet1Arg_member(int a ){ return false; }
		static bool myRet1Arg_static(int a ){ return false; }
		};

		void SomeFunction(){
		testerClass1 c1;
		Ret1Arg myFunctor = Ret1Arg(&c1,&testerClass1::myRet1Arg_member);
		Ret1Arg myFunctor_static = Ret1Arg(&testerClass1::myRet1Arg_static);
		bool someBool = myFunctor.Call(7);
		someBool = myFunctor_static.Call(9);
		}

		These functors obey the usual assignment operator, so you can store them
		within STL containers, and pass them around as function parameters by value.
		In general, they're good for event callback systems and other such nonsense. ;)
		*/


		//#####################################################################
		// 0 Argument, Has Return
		//#####################################################################
		template <typename RET, class Class=GenericFunctorClass>
		class GenericFunctorImpl_Ret_0Arg{
		public:
			// Default constructor
			GenericFunctorImpl_Ret_0Arg() : mcPtr(0),mmPtr(0),mfPtr(0) {}

			// Constructor to build SubscriberImpl from a class object pointer and member function
			template<class T>
				GenericFunctorImpl_Ret_0Arg(void* classPtr,RET(T::*memberPtr)())
			{
				mcPtr=reinterpret_cast<Class*>(classPtr);
				mmPtr=reinterpret_cast<RET(Class::*)()>(memberPtr);
				mfPtr=0;
			}

			// Constructor to build SubscriberImpl from a function pointer
			GenericFunctorImpl_Ret_0Arg(RET(*funcPtr)())
			{
				mcPtr=0;
				mmPtr=0;
				mfPtr=funcPtr;
			}


			//Calls the bound function and returns the result
			RET Call(){
				if(mcPtr && mmPtr)
					return (mcPtr->*mmPtr)();
				if(mfPtr)
					return (*mfPtr)();
				throw "f";
			}

			// Declaration of assignment operator
			template <class Class>
				GenericFunctorImpl_Ret_0Arg& operator=(GenericFunctorImpl_Ret_0Arg<RET,Class>& right){
					mcPtr=reinterpret_cast<GenericFunctorClass*>(right.mcPtr);
					mmPtr=reinterpret_cast<void(GenericFunctorClass::*)()>(right.mmPtr);
					return (*this);
				}
				bool operator==(GenericFunctorImpl_Ret_0Arg<RET,Class>& right){
					return mcPtr == right.mcPtr && mmPtr == right.mmPtr && mfPtr == right.mfPtr;
				}
		private:
			Class* mcPtr; //class object pointer
			(RET)(Class::* mmPtr)(); //member function pointer
			(RET)(*mfPtr)(); //normal function pointer
		};



		//#####################################################################
		// 0 Argument, No Return
		//#####################################################################
		template <class Class=GenericFunctorClass>
		class GenericFunctorImpl_NoRet_0Arg{
		public:
			// Default constructor
			GenericFunctorImpl_NoRet_0Arg() : mcPtr(0),mmPtr(0),mfPtr(0) {}

			// Constructor to build SubscriberImpl from a class object pointer and member function
			template<class T>
				GenericFunctorImpl_NoRet_0Arg(void* classPtr,void(T::*memberPtr)())
			{
				mcPtr=reinterpret_cast<Class*>(classPtr);
				mmPtr=reinterpret_cast<void(Class::*)()>(memberPtr);
				mfPtr=0;
			}

			// Constructor to build SubscriberImpl from a function pointer
			GenericFunctorImpl_NoRet_0Arg(void(*funcPtr)())
			{
				mcPtr=0;
				mmPtr=0;
				mfPtr=funcPtr;
			}


			//Calls the bound function and returns the result
			void Call(){
				if(mcPtr && mmPtr)
					(mcPtr->*mmPtr)();
				if(mfPtr)
					(*mfPtr)();
				throw "f";
			}

			// Declaration of assignment operator
			template <class Class>
				GenericFunctorImpl_NoRet_0Arg& operator=(GenericFunctorImpl_NoRet_0Arg<Class>& right){
					mcPtr=reinterpret_cast<GenericFunctorClass*>(right.mcPtr);
					mmPtr=reinterpret_cast<void(GenericFunctorClass::*)()>(right.mmPtr);
					return (*this);
				}
				bool operator==(GenericFunctorImpl_NoRet_0Arg<Class>& right){
					return mcPtr == right.mcPtr && mmPtr == right.mmPtr && mfPtr == right.mfPtr;
				}
		private:
			Class* mcPtr; //class object pointer
			(void)(Class::* mmPtr)(); //member function pointer
			(void)(*mfPtr)(); //normal function pointer
		};


		//#####################################################################
		// 1 Argument, Has Return
		//#####################################################################
		template <typename RET, typename ARG, class Class=GenericFunctorClass>
		class GenericFunctorImpl_Ret_1Arg{
		public:
			// Default constructor
			GenericFunctorImpl_Ret_1Arg() : mcPtr(0),mmPtr(0),mfPtr(0) {}

			// Constructor to build SubscriberImpl from a class object pointer and member function
			template<class T>
				GenericFunctorImpl_Ret_1Arg(void* classPtr,RET(T::*memberPtr)(ARG))
			{
				mcPtr=reinterpret_cast<Class*>(classPtr);
				mmPtr=reinterpret_cast<RET(Class::*)(ARG)>(memberPtr);
				mfPtr=0;
			}

			// Constructor to build SubscriberImpl from a function pointer
			GenericFunctorImpl_Ret_1Arg(RET(*funcPtr)(ARG))
			{
				mcPtr=0;
				mmPtr=0;
				mfPtr=funcPtr;
			}


			//Calls the bound function and returns the result
			RET Call(ARG arg){
				if(mcPtr && mmPtr)
					return (mcPtr->*mmPtr)(arg);
				if(mfPtr)
					return (*mfPtr)(arg);
				throw "f";
			}

			// Declaration of assignment operator
			template <class Class>
				GenericFunctorImpl_Ret_1Arg& operator=(GenericFunctorImpl_Ret_1Arg<RET,ARG,Class>& right){
					mcPtr=reinterpret_cast<GenericFunctorClass*>(right.mcPtr);
					mmPtr=reinterpret_cast<void(GenericFunctorClass::*)()>(right.mmPtr);
					return (*this);
				}
				bool operator==(GenericFunctorImpl_Ret_1Arg<RET,ARG,Class>& right){
					return mcPtr == right.mcPtr && mmPtr == right.mmPtr && mfPtr == right.mfPtr;
				}
		private:
			Class* mcPtr; //class object pointer
			(RET)(Class::* mmPtr)(ARG); //member function pointer
			(RET)(*mfPtr)(ARG); //normal function pointer
		};



		//#####################################################################
		// 1 Argument, No Return
		//#####################################################################
		template <typename ARG, class Class=GenericFunctorClass>
		class GenericFunctorImpl_NoRet_1Arg{
		public:
			// Default constructor
			GenericFunctorImpl_NoRet_1Arg() : mcPtr(0),mmPtr(0),mfPtr(0) {}

			// Constructor to build SubscriberImpl from a class object pointer and member function
			template<class T>
				GenericFunctorImpl_NoRet_1Arg(void* classPtr,void(T::*memberPtr)(ARG))
			{
				mcPtr=reinterpret_cast<Class*>(classPtr);
				mmPtr=reinterpret_cast<void(Class::*)(ARG)>(memberPtr);
				mfPtr=0;
			}

			// Constructor to build SubscriberImpl from a function pointer
			GenericFunctorImpl_NoRet_1Arg(void(*funcPtr)(ARG))
			{
				mcPtr=0;
				mmPtr=0;
				mfPtr=funcPtr;
			}


			//Calls the bound function and returns the result
			void Call(ARG arg){
				if(mcPtr && mmPtr)
					(mcPtr->*mmPtr)(arg);
				if(mfPtr)
					(*mfPtr)(arg);
				throw "f";
			}

			// Declaration of assignment operator
			template <class Class>
				GenericFunctorImpl_NoRet_1Arg& operator=(GenericFunctorImpl_NoRet_1Arg<ARG,Class>& right){
					mcPtr=reinterpret_cast<GenericFunctorClass*>(right.mcPtr);
					mmPtr=reinterpret_cast<void(GenericFunctorClass::*)()>(right.mmPtr);
					return (*this);
				}
				bool operator==(GenericFunctorImpl_NoRet_1Arg<ARG,Class>& right){
					return mcPtr == right.mcPtr && mmPtr == right.mmPtr && mfPtr == right.mfPtr;
				}
		private:
			Class* mcPtr; //class object pointer
			(void)(Class::* mmPtr)(ARG); //member function pointer
			(void)(*mfPtr)(ARG); //normal function pointer
		};


		//#####################################################################
		// 2 Argument, Has Return
		//#####################################################################
		template <typename RET, typename ARG, typename ARG2, class Class=GenericFunctorClass>
		class GenericFunctorImpl_Ret_2Arg{
		public:
			// Default constructor
			GenericFunctorImpl_Ret_2Arg() : mcPtr(0),mmPtr(0),mfPtr(0) {}

			// Constructor to build SubscriberImpl from a class object pointer and member function
			template<class T>
				GenericFunctorImpl_Ret_2Arg(void* classPtr,RET(T::*memberPtr)(ARG,ARG2))
			{
				mcPtr=reinterpret_cast<Class*>(classPtr);
				mmPtr=reinterpret_cast<RET(Class::*)(ARG,ARG2)>(memberPtr);
				mfPtr=0;
			}

			// Constructor to build SubscriberImpl from a function pointer
			GenericFunctorImpl_Ret_2Arg(RET(*funcPtr)(ARG,ARG2))
			{
				mcPtr=0;
				mmPtr=0;
				mfPtr=funcPtr;
			}


			//Calls the bound function and returns the result
			RET Call(ARG arg,ARG2 arg2){
				if(mcPtr && mmPtr)
					return (mcPtr->*mmPtr)(arg,arg2);
				if(mfPtr)
					return (*mfPtr)(arg,arg2);
				throw "f";
			}

			// Declaration of assignment operator
			template <class Class>
				GenericFunctorImpl_Ret_2Arg& operator=(GenericFunctorImpl_Ret_2Arg<RET,ARG,ARG2,Class>& right){
					mcPtr=reinterpret_cast<GenericFunctorClass*>(right.mcPtr);
					mmPtr=reinterpret_cast<void(GenericFunctorClass::*)()>(right.mmPtr);
					return (*this);
				}
				bool operator==(GenericFunctorImpl_Ret_2Arg<RET,ARG,ARG2,Class>& right){
					return mcPtr == right.mcPtr && mmPtr == right.mmPtr && mfPtr == right.mfPtr;
				}
		private:
			Class* mcPtr; //class object pointer
			(RET)(Class::* mmPtr)(ARG,ARG2); //member function pointer
			(RET)(*mfPtr)(ARG,ARG2); //normal function pointer
		};



		//#####################################################################
		// 2 Argument, No Return
		//#####################################################################
		template <typename ARG, typename ARG2, class Class=GenericFunctorClass>
		class GenericFunctorImpl_NoRet_2Arg{
		public:
			// Default constructor
			GenericFunctorImpl_NoRet_2Arg() : mcPtr(0),mmPtr(0),mfPtr(0) {}

			// Constructor to build SubscriberImpl from a class object pointer and member function
			template<class T>
				GenericFunctorImpl_NoRet_2Arg(void* classPtr,void(T::*memberPtr)(ARG,ARG2))
			{
				mcPtr=reinterpret_cast<Class*>(classPtr);
				mmPtr=reinterpret_cast<void(Class::*)(ARG,ARG2)>(memberPtr);
				mfPtr=0;
			}

			// Constructor to build SubscriberImpl from a function pointer
			GenericFunctorImpl_NoRet_2Arg(void(*funcPtr)(ARG,ARG2))
			{
				mcPtr=0;
				mmPtr=0;
				mfPtr=funcPtr;
			}


			//Calls the bound function and returns the result
			void Call(ARG arg,ARG2 arg2){
				if(mcPtr && mmPtr)
					(mcPtr->*mmPtr)(arg,arg2);
				if(mfPtr)
					(*mfPtr)(arg,arg2);
				throw "f";
			}

			// Declaration of assignment operator
			template <class Class>
				GenericFunctorImpl_NoRet_2Arg& operator=(GenericFunctorImpl_NoRet_2Arg<ARG,ARG2,Class>& right){
					mcPtr=reinterpret_cast<GenericFunctorClass*>(right.mcPtr);
					mmPtr=reinterpret_cast<void(GenericFunctorClass::*)()>(right.mmPtr);
					return (*this);
				}
				bool operator==(GenericFunctorImpl_NoRet_2Arg<ARG,ARG2,Class>& right){
					return mcPtr == right.mcPtr && mmPtr == right.mmPtr && mfPtr == right.mfPtr;
				}
		private:
			Class* mcPtr; //class object pointer
			(void)(Class::* mmPtr)(ARG,ARG2); //member function pointer
			(void)(*mfPtr)(ARG,ARG2); //normal function pointer
		};


		//#####################################################################
		// 3 Argument, Has Return
		//#####################################################################
		template <typename RET, typename ARG, typename ARG2, typename ARG3, class Class=GenericFunctorClass>
		class GenericFunctorImpl_Ret_3Arg{
		public:
			// Default constructor
			GenericFunctorImpl_Ret_3Arg() : mcPtr(0),mmPtr(0),mfPtr(0) {}

			// Constructor to build SubscriberImpl from a class object pointer and member function
			template<class T>
				GenericFunctorImpl_Ret_3Arg(void* classPtr,RET(T::*memberPtr)(ARG,ARG2,ARG3))
			{
				mcPtr=reinterpret_cast<Class*>(classPtr);
				mmPtr=reinterpret_cast<RET(Class::*)(ARG,ARG2,ARG3)>(memberPtr);
				mfPtr=0;
			}

			// Constructor to build SubscriberImpl from a function pointer
			GenericFunctorImpl_Ret_3Arg(RET(*funcPtr)(ARG,ARG2,ARG3))
			{
				mcPtr=0;
				mmPtr=0;
				mfPtr=funcPtr;
			}


			//Calls the bound function and returns the result
			RET Call(ARG arg,ARG2 arg2,ARG3 arg3){
				if(mcPtr && mmPtr)
					return (mcPtr->*mmPtr)(arg,arg2,arg3);
				if(mfPtr)
					return (*mfPtr)(arg,arg2,arg3);
				throw "f";
			}

			// Declaration of assignment operator
			template <class Class>
				GenericFunctorImpl_Ret_3Arg& operator=(GenericFunctorImpl_Ret_3Arg<RET,ARG,ARG2,ARG3,Class>& right){
					mcPtr=reinterpret_cast<GenericFunctorClass*>(right.mcPtr);
					mmPtr=reinterpret_cast<void(GenericFunctorClass::*)()>(right.mmPtr);
					return (*this);
				}
				bool operator==(GenericFunctorImpl_Ret_3Arg<RET,ARG,ARG2,ARG3,Class>& right){
					return mcPtr == right.mcPtr && mmPtr == right.mmPtr && mfPtr == right.mfPtr;
				}
		private:
			Class* mcPtr; //class object pointer
			(RET)(Class::* mmPtr)(ARG,ARG2,ARG3); //member function pointer
			(RET)(*mfPtr)(ARG,ARG2,ARG3); //normal function pointer
		};



		//#####################################################################
		// 3 Argument, No Return
		//#####################################################################
		template <typename ARG, typename ARG2, typename ARG3, class Class=GenericFunctorClass>
		class GenericFunctorImpl_NoRet_3Arg{
		public:
			//! Default constructor
			GenericFunctorImpl_NoRet_3Arg() : mcPtr(0),mmPtr(0),mfPtr(0) {}

			// Constructor to build SubscriberImpl from a class object pointer and member function
			template<class T>
				GenericFunctorImpl_NoRet_3Arg(void* classPtr,void(T::*memberPtr)(ARG,ARG2,ARG3))
			{
				mcPtr=reinterpret_cast<Class*>(classPtr);
				mmPtr=reinterpret_cast<void(Class::*)(ARG,ARG2,ARG3)>(memberPtr);
				mfPtr=0;
			}

			// Constructor to build SubscriberImpl from a function pointer
			GenericFunctorImpl_NoRet_3Arg(void(*funcPtr)(ARG,ARG2,ARG3))
			{
				mcPtr=0;
				mmPtr=0;
				mfPtr=funcPtr;
			}


			//Calls the bound function and returns the result
			void Call(ARG arg,ARG2 arg2,ARG3 arg3){
				if(mcPtr && mmPtr)
					(mcPtr->*mmPtr)(arg,arg2,arg3);
				if(mfPtr)
					(*mfPtr)(arg,arg2,arg3);
				throw "f";
			}

			// Declaration of assignment operator
			template <class Class>
				GenericFunctorImpl_NoRet_3Arg& operator=(GenericFunctorImpl_NoRet_3Arg<ARG,ARG2,ARG3,Class>& right){
					mcPtr=reinterpret_cast<GenericFunctorClass*>(right.mcPtr);
					mmPtr=reinterpret_cast<void(GenericFunctorClass::*)()>(right.mmPtr);
					return (*this);
				}
				bool operator==(GenericFunctorImpl_NoRet_3Arg<ARG,ARG2,ARG3,Class>& right){
					return mcPtr == right.mcPtr && mmPtr == right.mmPtr && mfPtr == right.mfPtr;
				}
		private:
			Class* mcPtr; //class object pointer
			(void)(Class::* mmPtr)(ARG,ARG2,ARG3); //member function pointer
			(void)(*mfPtr)(ARG,ARG2,ARG3); //normal function pointer
		};



		//#####################################################################
		// 4 Argument, Has Return
		//#####################################################################
		template <typename RET, typename ARG, typename ARG2, typename ARG3, typename ARG4, class Class=GenericFunctorClass>
		class GenericFunctorImpl_Ret_4Arg{
		public:
			// Default constructor
			GenericFunctorImpl_Ret_4Arg() : mcPtr(0),mmPtr(0),mfPtr(0) {}

			// Constructor to build SubscriberImpl from a class object pointer and member function
			template<class T>
				GenericFunctorImpl_Ret_4Arg(void* classPtr,RET(T::*memberPtr)(ARG,ARG2,ARG3,ARG4))
			{
				mcPtr=reinterpret_cast<Class*>(classPtr);
				mmPtr=reinterpret_cast<RET(Class::*)(ARG,ARG2,ARG3,ARG4)>(memberPtr);
				mfPtr=0;
			}

			// Constructor to build SubscriberImpl from a function pointer
			GenericFunctorImpl_Ret_4Arg(RET(*funcPtr)(ARG,ARG2,ARG3,ARG4))
			{
				mcPtr=0;
				mmPtr=0;
				mfPtr=funcPtr;
			}


			//Calls the bound function and returns the result
			RET Call(ARG arg,ARG2 arg2,ARG3 arg3,ARG4 arg4){
				if(mcPtr && mmPtr)
					return (mcPtr->*mmPtr)(arg,arg2,arg3,arg4);
				if(mfPtr)
					return (*mfPtr)(arg,arg2,arg3,arg4);
				throw "f";
			}

			// Declaration of assignment operator
			template <class Class>
				GenericFunctorImpl_Ret_4Arg& operator=(GenericFunctorImpl_Ret_4Arg<RET,ARG,ARG2,ARG3,ARG4,Class>& right){
					mcPtr=reinterpret_cast<GenericFunctorClass*>(right.mcPtr);
					mmPtr=reinterpret_cast<void(GenericFunctorClass::*)()>(right.mmPtr);
					return (*this);
				}
				bool operator==(GenericFunctorImpl_Ret_4Arg<RET,ARG,ARG2,ARG3,ARG4,Class>& right){
					return mcPtr == right.mcPtr && mmPtr == right.mmPtr && mfPtr == right.mfPtr;
				}
		private:
			Class* mcPtr; //class object pointer
			(RET)(Class::* mmPtr)(ARG,ARG2,ARG3,ARG4); //member function pointer
			(RET)(*mfPtr)(ARG,ARG2,ARG3,ARG4); //normal function pointer
		};



		//#####################################################################
		// 3 Argument, No Return
		//#####################################################################
		template <typename ARG, typename ARG2, typename ARG3, typename ARG4, class Class=GenericFunctorClass>
		class GenericFunctorImpl_NoRet_4Arg{
		public:
			// Default constructor
			GenericFunctorImpl_NoRet_4Arg() : mcPtr(0),mmPtr(0),mfPtr(0) {}

			// Constructor to build SubscriberImpl from a class object pointer and member function
			template<class T>
				GenericFunctorImpl_NoRet_4Arg(void* classPtr,void(T::*memberPtr)(ARG,ARG2,ARG3,ARG4))
			{
				mcPtr=reinterpret_cast<Class*>(classPtr);
				mmPtr=reinterpret_cast<void(Class::*)(ARG,ARG2,ARG3,ARG4)>(memberPtr);
				mfPtr=0;
			}

			// Constructor to build SubscriberImpl from a function pointer
			GenericFunctorImpl_NoRet_4Arg(void(*funcPtr)(ARG,ARG2,ARG3,ARG4))
			{
				mcPtr=0;
				mmPtr=0;
				mfPtr=funcPtr;
			}


			//Calls the bound function and returns the result
			void Call(ARG arg,ARG2 arg2,ARG3 arg3,ARG4 arg4){
				if(mcPtr && mmPtr)
					(mcPtr->*mmPtr)(arg,arg2,arg3,arg4);
				if(mfPtr)
					(*mfPtr)(arg,arg2,arg3,arg4);
				throw "f";
			}

			// Declaration of assignment operator
			template <class Class>
				GenericFunctorImpl_NoRet_4Arg& operator=(GenericFunctorImpl_NoRet_4Arg<ARG,ARG2,ARG3,ARG4,Class>& right){
					mcPtr=reinterpret_cast<GenericFunctorClass*>(right.mcPtr);
					mmPtr=reinterpret_cast<void(GenericFunctorClass::*)()>(right.mmPtr);
					return (*this);
				}
				bool operator==(GenericFunctorImpl_NoRet_4Arg<ARG,ARG2,ARG3,ARG4,Class>& right){
					return mcPtr == right.mcPtr && mmPtr == right.mmPtr && mfPtr == right.mfPtr;
				}
		private:
			Class* mcPtr; //class object pointer
			(void)(Class::* mmPtr)(ARG,ARG2,ARG3,ARG4); //member function pointer
			(void)(*mfPtr)(ARG,ARG2,ARG3,ARG4); //normal function pointer
		};



		//#####################################################################

		//#####################################################################

	};//namespace Functors{
};//namespace OpenGUI{

#endif