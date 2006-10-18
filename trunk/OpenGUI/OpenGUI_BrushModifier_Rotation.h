#ifndef C6517636_F5AE_4efb_A784_EABE7E95F570
#define C6517636_F5AE_4efb_A784_EABE7E95F570

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_BrushModifier.h"
#include "OpenGUI_RenderOperation.h"

namespace OpenGUI{

	//! \internal Rotation modifier stored by modifier stack
	class OPENGUI_API BrushModifier_Rotation : public BrushModifier {
	public:
		virtual ModifierType getType() {
			return ROTATION;
		}
		Radian mRotationAngle;
		virtual void apply( RenderOperation& in_out );
	};

} // namespace OpenGUI{
#endif // C6517636_F5AE_4efb_A784_EABE7E95F570