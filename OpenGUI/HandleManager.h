// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef A39157ED_B45C_40c0_9338_5C59FB64F708
#define A39157ED_B45C_40c0_9338_5C59FB64F708

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"

namespace OpenGUI {
	class HandledObject; // forward declaration
	class ObjectHandle; // forward declaration
	class HandleManagerListener; // forward declaration

	//! Provides notification service for the creation and destruction of HandledObject based objects
	/*! This class is 100% static so that it is always available from the moment execution begins
	until execution completes. Any attached listeners will be retained until they are explicitly
	detached, even if %OpenGUI itself is shutdown and re-initialized.

	The only exposed functions allow for the attaching and detaching of HandleManagerListener objects,
	which are notified about the creation and destruction of HandledObject based objects. There is no
	way to poll for a complete list of objects, so if you require that then you should implement such
	functionality yourself.

	\note
	This class is definitely not thread safe, nor thread aware.
	*/
	class OPENGUI_API HandleManager {
		friend class HandledObject; // needed to access the protected notification functions
	public:
		//! attach the given \c listener to begin receiving notifications
		static void attachListener( HandleManagerListener* listener );
		//! detach the given \c listener to stop receiving notifications
		static void detachListener( HandleManagerListener* listener );
	protected:
		static void _Object_Created( HandledObject* object );
		static void _Object_Destroyed( HandledObject* object );
	private:
		typedef std::set<HandleManagerListener*> ListenerSet;
		static ListenerSet mListenerSet;
	};
} // namespace OpenGUI {

#endif // A39157ED_B45C_40c0_9338_5C59FB64F708
