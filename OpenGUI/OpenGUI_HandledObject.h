// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef B0BDEF13_B844_499a_859C_A7D3D68B6427
#define B0BDEF13_B844_499a_859C_A7D3D68B6427

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_CONFIG.h"

namespace OpenGUI {

	//class ObjectHandle; // forward declaration
	//! Provides a single base class to maintain object handles for use with bindings
	/*! Each base class that is likely to require a retrievable handle derives from
	HandledObject. Each HandledObject provides creation and destruction notification
	to the HandleManager, which allows languages to attach listeners to intercept these
	events so that they may attach their own ObjectHandle to the object for later retrieval.

	Any single HandledObject is capable of storing multiple ObjectHandles, allowing multiple
	bindings to interact with the same HandledObject without stumbling over each other. The
	stored ObjectHandles are referenced by the value of their HandleManagerListener pointer.
	It is intended that a binding only use a single HandleManagerListener, and this mechanism
	ensures that all bindings have a unique value to identify their specific handle for the
	object.
	*/
	class OPENGUI_API HandledObject {
	public:
		HandledObject() {}
		~HandledObject() {}
		void _Init_ObjectHandles() {}
		void _Free_ObjectHandles() {}
		void _Get_ObjectHandle() {}
	private:

	};
} // namespace OpenGUI {

#endif // B0BDEF13_B844_499a_859C_A7D3D68B6427
