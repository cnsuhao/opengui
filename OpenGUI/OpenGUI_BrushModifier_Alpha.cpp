// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_BrushModifier_Alpha.h"

namespace OpenGUI {
	//############################################################################
	void BrushModifier_Alpha::apply( RenderOperation& in_out ) {
		TriangleList::iterator iter, iterend = in_out.triangleList->end();
		for ( iter = in_out.triangleList->begin(); iter != iterend; iter++ ) {
			Triangle& tri = ( *iter );
			tri.vertex[0].color.Alpha *= mAlpha;
			tri.vertex[1].color.Alpha *= mAlpha;
			tri.vertex[2].color.Alpha *= mAlpha;
		}
	}
	//############################################################################
} // namespace OpenGUI {
