// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef DB9F5599_38BF_4325_B7E1_4067DF5DD7B0
#define DB9F5599_38BF_4325_B7E1_4067DF5DD7B0

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"

namespace OpenGUI {

	class HandledObject; // forward declaration

	class OPENGUI_API ObjectHandle {
	public:
		ObjectHandle();
		~ObjectHandle();
		//! Returns a pointer to the object referenced by this handle
		HandledObject* getHandledObject();
		//! Returns an integer signifying the type of object referenced by this handle
		unsigned int getHandledObjectType();

		//! Must be overridden to return a unique ID number to signify the type of handle
		virtual unsigned int getHandleType() = 0;
	private:
		HandledObject* m_HandledObject;
	};

} // namespace OpenGUI {

#endif // DB9F5599_38BF_4325_B7E1_4067DF5DD7B0
