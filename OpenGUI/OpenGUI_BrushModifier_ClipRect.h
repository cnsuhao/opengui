#ifndef D2E223AF_BA0E_4db7_B29D_7C80FEC5FB16
#define D2E223AF_BA0E_4db7_B29D_7C80FEC5FB16

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_BrushModifier.h"

namespace OpenGUI {
	//! \internal ClipRect modifier stored by modifier stack
	class OPENGUI_API BrushModifier_ClipRect : public BrushModifier {
	public:
		virtual ModifierType getType() {
			return CLIPRECT;
		}
		FRect mRect;
		virtual void apply( RenderOperation& in_out );
	};
}

#endif // D2E223AF_BA0E_4db7_B29D_7C80FEC5FB16