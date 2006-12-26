// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef AC660DA3_935C_49BC_AB5A_0CC6BBFBFA8E
#define AC660DA3_935C_49BC_AB5A_0CC6BBFBFA8E

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Event.h"
#include "OpenGUI_EventHandler.h"

namespace OpenGUI {

	class ObjectAccessorList; //forward declaration
	class Value; // forward declaration
	class ValueList; // forward declaration

	class HandleManagerListener; // forward declaration
	class ObjectHandle; // forward declaration

	//! Base class for all GUI objects.
	/*! Provides an exposed interface to the Accessor and Event systems.
	Each Object provides creation and destruction notification to the HandleManager,
	which allows languages to attach listeners to intercept these events so that they
	may attach their own ObjectHandle for later retrieval.

	Any single Object is capable of storing multiple ObjectHandles, allowing multiple
	bindings to interact with the same Object without stumbling over each other.
	The	stored ObjectHandles are referenced by the value of their HandleManagerListener
	pointer. It is intended that a binding only use a single HandleManagerListener, and
	this mechanism ensures that all bindings have a unique value to identify their
	specific handle for the Object.
	*/
	class OPENGUI_API Object {
	public:
		Object();
		virtual ~Object();

		//! returns the value of \c propertyName via \c valueOut
		void getProperty( const std::string& propertyName, Value& valueOut );
		//! sets the value of \c propertyName to the contents of \c valueIn
		void setProperty( const std::string& propertyName, Value& valueIn );
		//! invokes \c methodName, sending \c paramIn as arguments, and catching return values in \c returnOut
		void callMethod( const std::string& methodName, ValueList& paramIn, ValueList& returnOut );

		//! triggers the event of the given \c eventName, sending the given \c evtArgs
		/*!	\param eventName The name of the event to trigger
			\param evtArgs The EventArgs based event data, by reference */
		void triggerEvent( const std::string& eventName, EventArgs& evtArgs ) {
			getEvents()[eventName].invoke( this, evtArgs );
		}
		//############################################################################

		//! returns this object's ObjectAccessorList head
		virtual ObjectAccessorList* getAccessors();

		//! Returns the Event::EventReceiver for this Object instance
		EventReceiver& getEvents();

		//############################################################################
		//! Returns an integer identifying the type of object
		/*! \see Object_Type */
		virtual unsigned int getObjectType() const = 0;

		//! These are the possible return values for getObjectType()
		enum Object_Type {
			OT_UNKNOWN          = 0, //!< should never happen
			OT_SCREEN           = 1, //!< Object is a Screen
			OT_CURSOR           = 2, //!< Object is a Cursor
			OT_WIDGET           = 5, //!< Object is a Widget
			OT_CONTROL          = 6, //!< Object is a Control
			OT_CONTAINERCONTROL = 7, //!< Object is a ContainerControl
			OT_WINDOW           = 8, //!< Object is a Window
		};

		//! Adds a new handle to the object, indexing it by the given \c sourceListener
		void _Add_ObjectHandle( ObjectHandle* handle, HandleManagerListener* sourceListener );
		//! Removes a previously added handle, retrieving it by the given \c sourceListener
		void _Remove_ObjectHandle( ObjectHandle* handle, HandleManagerListener* sourceListener );
		//! Gets the handle that was previously added for the given \c sourceListener
		ObjectHandle* _Get_ObjectHandle( HandleManagerListener* sourceListener );

	protected:
		//! \internal This should be called once at the end of the last constructor that overrides getObjectType()
		void _Initialize_Object();
	private:
		EventReceiver mEventReceiver;

		void _Init_ObjectHandles();
		void _Free_ObjectHandles();
		typedef std::map<HandleManagerListener*, ObjectHandle*> HandleMap;
		HandleMap mHandleMap;
		bool mInitialized;
	};

}//namespace OpenGUI{

#endif
