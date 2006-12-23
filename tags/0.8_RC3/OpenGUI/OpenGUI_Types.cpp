// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_Types.h"
#include "OpenGUI_StrConv.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	//#####################################################################
	std::string IVector2::toStr() const {
		std::string ret;
		StrConv::fromIVector2( *this, ret );
		return ret;
	}
	//#####################################################################
	std::string FVector2::toStr() const {
		std::string ret;
		StrConv::fromFVector2( *this, ret );
		return ret;
	}
	//#####################################################################
	std::string IRect::toStr() const {
		std::string ret;
		StrConv::fromIRect( *this, ret );
		return ret;
	}
	//#####################################################################
	std::string FRect::toStr() const {
		std::string ret;
		StrConv::fromFRect( *this, ret );
		return ret;
	}
	//#####################################################################
}//namespace OpenGUI {
