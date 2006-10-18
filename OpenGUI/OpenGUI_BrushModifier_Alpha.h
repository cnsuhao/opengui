#ifndef D6CC0CE9_BAD5_4536_B09B_B1BC02EE9722
#define D6CC0CE9_BAD5_4536_B09B_B1BC02EE9722

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_BrushModifier.h"
#include "OpenGUI_RenderOperation.h"

namespace OpenGUI{
	//! \internal Alpha modifier stored by modifier stack
	class OPENGUI_API BrushModifier_Alpha : public BrushModifier {
	public:
		virtual ModifierType getType() {
			return ALPHA;
		}
		float mAlpha;
		virtual void apply( RenderOperation& in_out );
	};
} // namespace OpenGUI{
#endif // D6CC0CE9_BAD5_4536_B09B_B1BC02EE9722
