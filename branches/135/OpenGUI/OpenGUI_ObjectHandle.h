// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef DB9F5599_38BF_4325_B7E1_4067DF5DD7B0
#define DB9F5599_38BF_4325_B7E1_4067DF5DD7B0

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"

namespace OpenGUI {

	class Object; // forward declaration

	//! Base class for custom handles to Object derived objects
	/*! The Object will automatically manage the pointer this class
	holds to it, so you don't have to deal with that aspect. */
	class OPENGUI_API ObjectHandle {
		friend class Object; // so Object can reach m_HandledObject

	public:
		ObjectHandle(): m_HandledObject( 0 ) {}
		~ObjectHandle() {}
		//! Returns a pointer to the object referenced by this handle
		Object* getObject() {
			return m_HandledObject;
		}

	private:
		//This is automatically set by Object when the handle is added, and cleared when removed
		Object* m_HandledObject;
	};

} // namespace OpenGUI {

#endif // DB9F5599_38BF_4325_B7E1_4067DF5DD7B0
