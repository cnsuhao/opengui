// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_BrushModifier_Color.h"

namespace OpenGUI {
	//############################################################################
	void BrushModifier_Color::apply( RenderOperation& in_out ) {
		TriangleList::iterator iter, iterend = in_out.triangleList->end();
		for ( iter = in_out.triangleList->begin(); iter != iterend; iter++ ) {
			Triangle& tri = ( *iter );
			tri.vertex[0].color = mColor;
			tri.vertex[1].color = mColor;
			tri.vertex[2].color = mColor;
		}
	}
	//############################################################################
} // namespace OpenGUI{
