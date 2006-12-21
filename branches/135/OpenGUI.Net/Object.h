// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Object_h__
#define Object_h__

using namespace System;

namespace OpenGUI_Net {

	ref class Object; // forward declaration
	class HandleListener; // forward declaration

	class ObjectHandle: public OpenGUI::ObjectHandle {
	public:
		ObjectHandle();
		~ObjectHandle();
		Object ^ getManaged() {
			return m_ObjectRef;
		}
		void _setManaged( Object ^ mObject ) {
			m_ObjectRef = mObject;
		}
	private:
		gcroot < Object ^ > m_ObjectRef;
	};

	public ref class Object {
	public:
		// constructor requires the pointer to the original native object
		Object();
		~Object();
		void _setHandle( ObjectHandle* handle );
		ObjectHandle* getHandle();

		//returns the value of propertyName via valueOut
		//void getProperty (String^propertyName, Value &valueOut);
		//sets the value of propertyName to the contents of valueIn
		//void setProperty(String^propertyName, Value &valueIn);
		//invokes methodName, sending paramIn as arguments, and catching return values in returnOut
		//void callMethod(String^methodName, ValueList &paramIn, ValueList &returnOut);
		//triggers the event of the given eventName, sending the given evtArgs
		void triggerEvent( String ^ eventName, EventArgs ^ evtArgs ){}
		//returns this object's ObjectAccessorList head
		//virtual ObjectAccessorList* getAccessors ();
		//EventReceiver &  getEvents ();
	private:
		ObjectHandle* mNativeHandle;
	};
} // namespace OpenGUI_Net {

#endif // Object_h__
