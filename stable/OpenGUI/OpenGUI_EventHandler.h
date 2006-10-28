#ifndef CA247652_FCF4_483C_B34C_810A39296B18
#define CA247652_FCF4_483C_B34C_810A39296B18

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Event.h"

namespace OpenGUI {
	class Object; //forward declaration
	class EventArgs; //forward declaration

	//! Base class for custom event handler implementations
	class OPENGUI_API EventHandler {
	public:
		EventHandler() {
			/**/
		}
		virtual ~EventHandler() {
			/**/
		}
		//! Interface for receiving event notifications
		virtual void onEvent( Object* sender, EventArgs& args ) = 0;

		//! Called during destruction of a bound event
		/*! Useful for auto deleting anonymous delegates */
		virtual void onEventDestruction() {}
	};


	//! Provides event handler multi cast service.
	class OPENGUI_API EventHandlerList {
		friend class EventReceiver; //allow access to constructor/destructor
	public:
		//! add a new EventHandler to the list
		void add( EventHandler* handler );
		//! remove an EventHandler from the list
		void remove( EventHandler* handler );
		//! executes all held EventHandlers with the given parameters
		void invoke( Object* sender, EventArgs& args );
	private:
		// Only EventReceiver can create/destroy us
		EventHandlerList() {
			/**/
		}
		virtual ~EventHandlerList();

		typedef std::set<EventHandler*> EventHandlerSet;
		EventHandlerSet mEventHandlerSet;
		EventHandlerSet mHandlersToDelete;
	};


	///////////////////////////////////////////////////////////////////////////
	// Note to future editors:
	// The following classes are intended only for inline compiling where used,
	// and are not exported on purpose as that would allow for non-inline uses.
	///////////////////////////////////////////////////////////////////////////


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
		typedef void EventCallbackFunc( Object* sender, EventArgs& args );
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
	template <class CLASS, class ARGS_TYPE>
	class _Event_memberFunc: public _EventBinder_Interface {
	public:
		typedef void( CLASS::*MEMBER )( Object* sender, ARGS_TYPE& args );
		virtual ~_Event_memberFunc() {
			/**/
		}
		_Event_memberFunc( MEMBER memberPtr, CLASS* class_objPtr ): mMemberPtr( memberPtr ), mClassObject( class_objPtr ) {}
		virtual void fire( Object* sender, EventArgs& args ) const {
			try {
				ARGS_TYPE& args_spec = dynamic_cast<ARGS_TYPE&>( args );
				( mClassObject->*mMemberPtr )( sender, args_spec );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad reference cast in event delegate. Probably failed to upward cast EventArgs to a more specific type.", __FUNCTION__ );
			}
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
		_Event_callbackFunc( EventCallbackFunc* function ): mFunc( function ) {
			/**/
		}
		virtual ~_Event_callbackFunc() {
			/**/
		}
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
			void myMethod( Object* sender, EventArgs& args ){
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
		\note 
		In the first code area, the \a sender is a pointer to the Object that is experiencing the event,
		and \a args is a reference to the appropriate EventArgs derived class. You can use either EventArgs
		specifically, and cast it yourself later, or you can use the specific EventArgs derived class
		for the particular event you plan on receiving. If you try to send an event to a handler that
		tries to cast \a args to the wrong type, it will compile fine but will suffer a run time
		exception because of a bad reference cast when the event is invoked. The \a sender is
		sent because you may be binding the same event across several different instances of Widgets,
		and in that case a pointer back to the Widget that is experiencing the event is most useful.
		*/
		template <class CLASS, class ARGS_TYPE>
		EventDelegate( CLASS* classObjPtr, void( CLASS::*memberFunc )( Object*, ARGS_TYPE& ) ) {
			mBoundFunc = new _Event_memberFunc<CLASS, ARGS_TYPE>( memberFunc, classObjPtr );
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

