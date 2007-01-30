// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#ifndef AC660DA3_935C_49BC_AB5A_0CC6BBFBFA8E
#define AC660DA3_935C_49BC_AB5A_0CC6BBFBFA8E

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_String.h"
#include "OpenGUI_Event.h"
#include "OpenGUI_EventHandler.h"

namespace OpenGUI {

	class ObjectAccessorList; //forward declaration
	class Value; // forward declaration
	class ValueList; // forward declaration

	//! Base class for all GUI objects. Provides an exposed interface to the Accessor and Event systems.
	class OPENGUI_API Object {
	public:
		Object();
		virtual ~Object();

		//! returns the value of \c propertyName via \c valueOut
		void getProperty( const String& propertyName, Value& valueOut );
		//! sets the value of \c propertyName to the contents of \c valueIn
		void setProperty( const String& propertyName, Value& valueIn );
		//! invokes \c methodName, sending \c paramIn as arguments, and catching return values in \c returnOut
		void callMethod( const String& methodName, ValueList& paramIn, ValueList& returnOut );

		//! triggers the event of the given \c eventName, sending the given \c evtArgs
		/*!	\param eventName The name of the event to trigger
			\param evtArgs The EventArgs based event data, by reference */
		void triggerEvent( const String& eventName, EventArgs& evtArgs ) {
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

	private:
		EventReceiver mEventReceiver;
	};

}//namespace OpenGUI{

#endif
