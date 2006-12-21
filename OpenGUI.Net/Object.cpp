// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "Stdafx.h"

#include "Object.h"
#include "ObjectHandle.h"
#include "HandleSystem.h"

namespace OpenGUI_Net {

	//############################################################################
	Object::Object() {
		mNativeHandle = 0;
	}
	//############################################################################
	Object::~Object() {
		/**/
	}
	//############################################################################
	void Object::_setHandle( ObjectHandle* handle ) {
		mNativeHandle = handle;
	}
	//############################################################################
	ObjectHandle* Object::getHandle() {
		return mNativeHandle;
	}
	//############################################################################
	void Object::sanityTest() {
		if ( mNativeHandle == 0 || mNativeHandle->getObject() == 0 )
			throw gcnew ::System::Exception( "Expired OpenGUI::Object handle." );
	}
	//############################################################################

} // namespace OpenGUI_Net {
