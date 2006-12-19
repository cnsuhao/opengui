// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef DB9F5599_38BF_4325_B7E1_4067DF5DD7B0
#define DB9F5599_38BF_4325_B7E1_4067DF5DD7B0

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"

namespace OpenGUI {

	class HandledObject; // forward declaration

	//! Base class for custom handles to HandledObject derived objects
	/*! The HandledObject will automatically manage the pointer this class
	holds to it, so you don't have to deal with that aspect. */
	class OPENGUI_API ObjectHandle {
		friend class HandledObject; // so HandledObject can reach m_HandledObject

	public:
		ObjectHandle(): m_HandledObject( 0 ) {}
		~ObjectHandle() {}
		//! Returns a pointer to the object referenced by this handle
		HandledObject* getHandledObject() {
			return m_HandledObject;
		}

	private:
		//This is automatically set by HandledObject when the handle is added, and cleared when removed
		HandledObject* m_HandledObject;
	};

} // namespace OpenGUI {

#endif // DB9F5599_38BF_4325_B7E1_4067DF5DD7B0
