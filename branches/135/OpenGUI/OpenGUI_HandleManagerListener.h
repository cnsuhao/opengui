// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef A5043AE3_0C68_4889_ABB9_6467E540ABE6
#define A5043AE3_0C68_4889_ABB9_6467E540ABE6

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"

namespace OpenGUI {

	class Object; // forward declaration
	class ObjectHandle; // forward declaration


	//! Listener for the creation and destruction of Object classes
	/*! These listeners are registered through the HandleManager
	*/
	class HandleManagerListener {
	public:
		//! Called when an Object is created
		/*! This is called for all newly created objects.
		Objects that already exist at the time of listener attachment will not be provided. */
		virtual void onObjectCreated( Object* handledObject ) = 0;
		//! Called when an Object is destroyed
		/*! This is only called for each HandleManagerListener that has attached an ObjectHandle to the object.
		If you do not attach a handle, you will not receive notification about the object's destruction.
		Also, your handle will be automatically deleted by Object if you do not remove it yourself
		during this call. */
		virtual void onObjectDestroyed( Object* handledObject ) = 0;
	};

} // namespace OpenGUI {

#endif // A5043AE3_0C68_4889_ABB9_6467E540ABE6
