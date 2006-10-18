#ifndef A1DECE9F_DE6D_4bf8_BE7A_5D2AEC440CD3
#define A1DECE9F_DE6D_4bf8_BE7A_5D2AEC440CD3

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_BrushModifier.h"
#include "OpenGUI_RenderOperation.h"

namespace OpenGUI {
	//! \internal Mask modifier stored by modifier stack
	class OPENGUI_API BrushModifier_Mask : public BrushModifier {
	public:
		virtual ModifierType getType() {
			return MASK;
		}
		ImageryPtr mImagery;
		FRect mRect;
		virtual void apply( RenderOperation& in_out );
	};
} // namespace OpenGUI{
#endif // A1DECE9F_DE6D_4bf8_BE7A_5D2AEC440CD3
