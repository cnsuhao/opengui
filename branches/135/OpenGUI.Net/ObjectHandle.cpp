// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "Stdafx.h"
#include "Object.h"
#include "ObjectHandle.h"
#include "HandleSystem.h"

namespace OpenGUI_Net {

	//############################################################################
	ObjectHandle::ObjectHandle() {
		m_ObjectRef = nullptr;
	}
	//############################################################################
	ObjectHandle::~ObjectHandle() {
		if ( m_ObjectRef && m_ObjectRef->getHandle() == this ) {
			m_ObjectRef->_setHandle( 0 );
		}
	}
	//############################################################################

} // namespace OpenGUI_Net {
