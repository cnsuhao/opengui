#include "OpenGUI_BrushModifier_Alpha.h"

namespace OpenGUI {
	//############################################################################
	void BrushModifier_Alpha::apply( RenderOperation& in_out ) {
		for ( TriangleList::iterator iter = in_out.triangleList->begin();
			iter != in_out.triangleList->end(); iter++ ) {
				Triangle& tri = ( *iter );
				tri.vertex[0].color.Alpha *= mAlpha;
				tri.vertex[1].color.Alpha *= mAlpha;
				tri.vertex[2].color.Alpha *= mAlpha;
		}
	}
	//############################################################################
} // namespace OpenGUI {
