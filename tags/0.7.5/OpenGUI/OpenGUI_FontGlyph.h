#ifndef E868AE54_0012_4735_9BFC_9AF9EE255A59
#define E868AE54_0012_4735_9BFC_9AF9EE255A59

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Imagery.h"

namespace OpenGUI{

	struct FontGlyphMetrics{
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

	struct FontGlyph{
		FontGlyphMetrics metrics;
		ImageryPtr imageryPtr;
	};

};//namespace OpenGUI{

#endif
