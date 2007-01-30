// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_BrushModifier_Position.h"

namespace OpenGUI {
	//############################################################################
	void BrushModifier_Position::apply( RenderOperation& in_out ) {
		TriangleList::iterator iter, iterend = in_out.triangleList->end();
		for ( iter = in_out.triangleList->begin(); iter != iterend; iter++ ) {
			Triangle& tri = ( *iter );
			for ( int i = 0; i < 3; i++ ) {
				Vertex& vert = tri.vertex[i];
				vert.position = mPosition + vert.position;
			}
		}
	}
	//############################################################################
} // namespace OpenGUI{
