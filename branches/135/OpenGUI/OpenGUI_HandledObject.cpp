// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_HandledObject.h"

namespace OpenGUI {
	//############################################################################
	void HandledObject::_Add_ObjectHandle( ObjectHandle* handle, HandleManagerListener* sourceListener ) {}
	//############################################################################
	void HandledObject::_Remove_ObjectHandle( ObjectHandle* handle ) {}
	//############################################################################
	ObjectHandle* HandledObject::_Get_ObjectHandle( HandleManagerListener* sourceListener ) {
		return 0;
	}
	//############################################################################
	void HandledObject::_Init_ObjectHandles() {}
	//############################################################################
	void HandledObject::_Free_ObjectHandles() {}
	//############################################################################
} //namespace OpenGUI {
