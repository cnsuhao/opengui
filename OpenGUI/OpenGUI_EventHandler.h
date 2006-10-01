#ifndef CA247652_FCF4_483C_B34C_810A39296B18
#define CA247652_FCF4_483C_B34C_810A39296B18

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Event.h"

namespace OpenGUI {
	class Object; //forward declaration
	class EventArgs; //forward declaration

	//! Base class for custom event handler implementations
	class OPENGUI_API EventHandler {
	public:
		EventHandler() {}
		virtual ~EventHandler() {}
		//! Interface for receiving event notifications
		virtual void onEvent( Object* sender, EventArgs& args ) = 0;

		//! Called during destruction of a bound event
		/*! Useful for auto deleting delegates */
		virtual void onEventDestruction() {}
	};


	//! Provides event handler multi cast service.
	class OPENGUI_API EventHandlerList {
	public:
		EventHandlerList() {}
		virtual ~EventHandlerList();
		//! add a new EventHandler to the list
		void add( EventHandler* handler );
		//! remove an EventHandler from the list
		void remove( EventHandler* handler );
		//! executes all held EventHandlers with the given parameters
		void invoke( Object* sender, EventArgs& args );
	private:
		typedef std::set<EventHandler*> EventHandlerSet;
		EventHandlerSet mEventHandlerSet;
		EventHandlerSet mHandlersToDelete;
	};



	//! Self destroying C-callback style event delegate
	/*!
	\par "Example usage:"
	Assume \c obj is a pointer to a valid Object, and \c desiredEvent is a valid event for that Object.
	\code
	obj->getEvents()["desiredEvent"].add( new EventCallback(&myCallback) );
	\endcode
	*/
	class EventCallback: public EventHandler {
	public:
		//! Function signature required for use as C-style event callback
		/*! \code void myCallback( Object* , EventArgs* ); \endcode */
		typedef void EventCallbackFunc( Object* , EventArgs& );
		//! Constructor requires a pointer to a valid C function pointer
		EventCallback( EventCallbackFunc* C_funcPtr ): mFunc( C_funcPtr ) {}
		//! Calls the function given at event callback creation on event trigger
		virtual void onEvent( Object* sender, EventArgs& args ) {
			( *mFunc )( sender, args );
		}
		//! Automatically deletes self on event destruction
		/*! This is so that you do not need to retain a pointer to it. In fact, you probably shouldn't. */
		virtual void onEventDestruction() {
			delete this;
		}
	private:
		EventCallbackFunc* mFunc;
	};


	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//! \internal generic delegate interface class
	class _EventBinder_Interface {
	public:
		_EventBinder_Interface() {}
		virtual ~_EventBinder_Interface() {}
		virtual void fire( Object* sender, EventArgs& args ) const = 0;
	};
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//! \internal generic delegate class for member function callbacks
	template <class CLASS>
	class _Event_memberFunc: public _EventBinder_Interface {
	public:
		typedef void( CLASS::*MEMBER )( Object* sender, EventArgs& args );
		virtual ~_Event_memberFunc() {}
		_Event_memberFunc( MEMBER memberPtr, CLASS* class_objPtr ): mMemberPtr( memberPtr ), mClassObject( class_objPtr ) {}
		virtual void fire( Object* sender, EventArgs& args ) const {
			( mClassObject->*mMemberPtr )( sender, args );
		}
	private:
		CLASS* mClassObject;
		MEMBER mMemberPtr;
	};
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//! \internal generic delegate class for C function callbacks
	class _Event_callbackFunc: public _EventBinder_Interface {
	public:
		typedef void EventCallbackFunc( Object* , EventArgs& );
		_Event_callbackFunc( EventCallbackFunc* function ): mFunc( function ) {}
		virtual ~_Event_callbackFunc() {}
		virtual void fire( Object* sender, EventArgs& args ) const {
			( *mFunc )( sender, args );
		}
	private:
		EventCallbackFunc* mFunc;
	};
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//! Self destroying multi-purpose event delegate
	/*!
	This delegate class is capable of binding to either C-style function pointers
	or object specific member function pointers. It performs the smoke and magic
	through an abstract interface class system, and the use of a very light
	template in the specific case of member function callbacks.
	*/
	class EventDelegate: public EventHandler {
	public:
		typedef void EventCallbackFunc( Object*, EventArgs& );
		~EventDelegate() {
			delete mBoundFunc;
		}

		//! Create the delegate from a C function pointer
		/*!
		\par "Example usage:"
		Assume \c obj is a pointer to a valid Object, and \c desiredEvent is a valid event for that Object.
		\code
		obj->getEvents()["desiredEvent"].add( new EventDelegate(&myCallback) );
		\endcode
		*/
		EventDelegate( EventCallbackFunc* C_funcPtr ) {
			mBoundFunc = new _Event_callbackFunc( C_funcPtr );
		}

		//! Create the delegate from an object bound member function pointer
		/*!
		\par "Example usage:"
		First we'll define an example class with a member function capable of receiving the event.
		\code
		class MyClass{
		public:
			void myMethod(Object* sender,EventArgs& args){
				//do something important
			}
		};
		\endcode
		And now an example of binding an object of the example class and its method to an event.
		Assume \c obj is a pointer to a valid Object, \c desiredEvent is a valid event for that 
		Object, and \c myClassObj is a valid pointer to an instance of \c MyClass.
		\code
		obj->getEvents()["desiredEvent"].add( new EventDelegate(myClassObj, &MyClass::myMethod) );
		\endcode
		*/
		template <class CLASS>
		EventDelegate( CLASS* classObjPtr, void( CLASS::*memberFunc )( Object*, EventArgs& ) ) {
			mBoundFunc = new _Event_memberFunc<CLASS>( memberFunc, classObjPtr );
		}

		//! Calls the function/member given at EventDelegate creation on event trigger
		virtual void onEvent( Object* sender, EventArgs& args ) {
			mBoundFunc->fire( sender, args );
		}
		//! Automatically deletes self on event destruction
		/*! This is so that you do not need to retain a pointer to it. In fact, you probably shouldn't. */
		virtual void onEventDestruction() {
			delete this;
		}
	private:
		_EventBinder_Interface* mBoundFunc;
	};

}// namespace OpenGUI {

#endif // CA247652_FCF4_483C_B34C_810A39296B18

