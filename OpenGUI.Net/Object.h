// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Object_h__
#define Object_h__

using namespace System;

namespace OpenGUI_Net {

	class HandleListener; // forward declaration
	class ObjectHandle; // forward declaration

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
		void triggerEvent( String ^ eventName, EventArgs ^ evtArgs ) {}
		//returns this object's ObjectAccessorList head
		//virtual ObjectAccessorList* getAccessors ();
		//EventReceiver &  getEvents ();
	protected:
		void sanityTest();
	private:
		ObjectHandle* mNativeHandle;
	};
} // namespace OpenGUI_Net {

#endif // Object_h__
