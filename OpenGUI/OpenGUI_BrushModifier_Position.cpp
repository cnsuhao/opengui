#include "OpenGUI_BrushModifier_Position.h"

namespace OpenGUI {
	//############################################################################
	void BrushModifier_Position::apply( RenderOperation& in_out ) {
		for ( TriangleList::iterator iter = in_out.triangleList->begin();
				iter != in_out.triangleList->end(); iter++ ) {
			Triangle& tri = ( *iter );
			for ( int i = 0; i < 3; i++ ) {
				Vertex& vert = tri.vertex[i];
				vert.position = mPosition + vert.position;
			}
		}
	}
	//############################################################################
} // namespace OpenGUI{
