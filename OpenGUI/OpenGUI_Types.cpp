// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_Types.h"
#include "OpenGUI_StrConv.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	//#####################################################################
	String IVector2::toStr() const {
		String ret;
		StrConv::fromIVector2( *this, ret );
		return ret;
	}
	//#####################################################################
	String FVector2::toStr() const {
		String ret;
		StrConv::fromFVector2( *this, ret );
		return ret;
	}
	//#####################################################################
	String IRect::toStr() const {
		String ret;
		StrConv::fromIRect( *this, ret );
		return ret;
	}
	//#####################################################################
	String FRect::toStr() const {
		String ret;
		StrConv::fromFRect( *this, ret );
		return ret;
	}
	//#####################################################################
}//namespace OpenGUI {
