#ifndef BF42C704_4B33_4932_AC87_3778F5E8E64F
#define BF42C704_4B33_4932_AC87_3778F5E8E64F

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_BrushModifier.h"
#include "OpenGUI_RenderOperation.h"

namespace OpenGUI{

	//! \internal Position modifier stored by modifier stack
	class OPENGUI_API BrushModifier_Position : public BrushModifier {
	public:
		virtual ModifierType getType() {
			return POSITION;
		}
		FVector2 mPosition;
		virtual void apply( RenderOperation& in_out );
	};

} // namespace OpenGUI{
#endif // BF42C704_4B33_4932_AC87_3778F5E8E64F
