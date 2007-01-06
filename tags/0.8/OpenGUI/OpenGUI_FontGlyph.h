// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef E868AE54_0012_4735_9BFC_9AF9EE255A59
#define E868AE54_0012_4735_9BFC_9AF9EE255A59

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Imagery.h"

namespace OpenGUI {

	//! \internal This is an internal object definition
	struct FontGlyphMetrics {
		int width;
		int height;

		int horiBearingX;
		int horiBearingY;
		int horiAdvance;

		int vertBearingX;
		int vertBearingY;
		int vertAdvance;

		int horizLineSpacing;
	};

	//! \internal This is an internal object definition
	struct FontGlyph {
		FontGlyphMetrics metrics;
		ImageryPtr imageryPtr;
	};

}
;//namespace OpenGUI{

#endif
