#include "OpenGUI_BrushModifier_Color.h"

namespace OpenGUI{
	//############################################################################
	void BrushModifier_Color::apply( RenderOperation& in_out ) {
		for ( TriangleList::iterator iter = in_out.triangleList->begin();
			iter != in_out.triangleList->end(); iter++ ) {
				Triangle& tri = ( *iter );
				tri.vertex[0].color = mColor;
				tri.vertex[1].color = mColor;
				tri.vertex[2].color = mColor;
		}
	}
	//############################################################################
} // namespace OpenGUI{
