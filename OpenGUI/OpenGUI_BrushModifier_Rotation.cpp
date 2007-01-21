// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_BrushModifier_Rotation.h"

namespace OpenGUI {
	//############################################################################
	void BrushModifier_Rotation::apply( RenderOperation& in_out ) {
		/*
		We're performing the same rotation angle for all vertices,
		so we can reuse pre calculated Sin and Cos results
		*/
		const float preCos = Math::Cos( mRotationAngle.valueRadians() );
		const float preSin = Math::Sin( mRotationAngle.valueRadians() );

		TriangleList::iterator iter, iterend = in_out.triangleList->end();
		for ( iter = in_out.triangleList->begin(); iter != iterend; iter++ ) {
			Triangle& tri = ( *iter );
			for ( int i = 0; i < 3; i++ ) {
				Vertex& vert = tri.vertex[i];
				float x = vert.position.x;
				float y = vert.position.y;
				vert.position.x = preCos * x - preSin * y;
				vert.position.y = preSin * x + preCos * y;
			}
		}
	}
	//############################################################################
} // namespace OpenGUI{
