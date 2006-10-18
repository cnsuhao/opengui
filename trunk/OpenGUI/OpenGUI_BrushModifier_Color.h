#ifndef AE27BCE0_1E70_4fa7_AEBD_FA3EB22BC778
#define AE27BCE0_1E70_4fa7_AEBD_FA3EB22BC778

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_BrushModifier.h"
#include "OpenGUI_RenderOperation.h"

namespace OpenGUI{

	//! \internal Color modifier stored by modifier stack
	class OPENGUI_API BrushModifier_Color : public BrushModifier {
	public:
		virtual ModifierType getType() {
			return COLOR;
		}
		Color mColor;
		virtual void apply( RenderOperation& in_out );
	};

} // namespace OpenGUI{

#endif // AE27BCE0_1E70_4fa7_AEBD_FA3EB22BC778
