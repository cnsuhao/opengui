#include "OpenGUI_BrushModifier_Mask.h"

namespace OpenGUI {
	//############################################################################
	void BrushModifier_Mask::apply( RenderOperation& in_out ) {
		in_out.mask = mImagery->getTexture();

		FVector2 size = mRect.getSize();
		const FVector2& pos = mRect.getPosition();

		TriangleList& tlist = *in_out.triangleList;
		for ( TriangleList::iterator iter = tlist.begin();
				iter != tlist.end(); iter++ ) {
			Triangle& tri = ( *iter );
			float& x1 = tri.vertex[0].position.x;
			float& y1 = tri.vertex[0].position.y;
			float& x2 = tri.vertex[1].position.x;
			float& y2 = tri.vertex[1].position.y;
			float& x3 = tri.vertex[2].position.x;
			float& y3 = tri.vertex[2].position.y;

			tri.vertex[0].maskUV.x = ( x1 - pos.x ) / size.x;
			tri.vertex[0].maskUV.y = ( y1 - pos.y ) / size.y;
			tri.vertex[1].maskUV.x = ( x2 - pos.x ) / size.x;
			tri.vertex[1].maskUV.y = ( y2 - pos.y ) / size.y;
			tri.vertex[2].maskUV.x = ( x3 - pos.x ) / size.x;
			tri.vertex[2].maskUV.y = ( y3 - pos.y ) / size.y;
		}
	}
	//############################################################################
} // namespace OpenGUI {
