// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef D2E223AF_BA0E_4db7_B29D_7C80FEC5FB16
#define D2E223AF_BA0E_4db7_B29D_7C80FEC5FB16

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_BrushModifier.h"
#include "OpenGUI_RenderOperation.h"

namespace OpenGUI {
	//! \internal ClipRect modifier stored by modifier stack
	class OPENGUI_API BrushModifier_ClipRect : public BrushModifier {
	public:
		virtual ModifierType getType() {
			return CLIPRECT;
		}
		FRect mRect;
		virtual void apply( RenderOperation& in_out );
	private:
		void _sliceLineSegment( const Vertex& vert1, const Vertex& vert2, Vertex& resultVert, float cutPosition, bool cutHorizontal );
		void _SliceRenderOp_Vert_SaveLeft( Triangle& in_out1, Triangle& out2, unsigned int& outCount, float cutPosition );
		void _SliceRenderOp_Vert_SaveRight( Triangle& in_out1, Triangle& out2, unsigned int& outCount, float cutPosition );
		void _SliceRenderOp_Horiz_SaveTop( Triangle& in_out1, Triangle& out2, unsigned int& outCount, float cutPosition );
		void _SliceRenderOp_Horiz_SaveBottom( Triangle& in_out1, Triangle& out2, unsigned int& outCount, float cutPosition );
	};
}

#endif // D2E223AF_BA0E_4db7_B29D_7C80FEC5FB16