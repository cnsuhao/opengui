// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef BD2BBBC1_8162_4B02_A871_4AEAC49BAC26
#define BD2BBBC1_8162_4B02_A871_4AEAC49BAC26

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Imagery.h"
#include "OpenGUI_RenderOperation.h"

namespace OpenGUI {

	//! \internal Base class for brush modifiers stored by modifier stack
	class OPENGUI_API BrushModifier {
	public:
		BrushModifier() {}
		virtual ~BrushModifier() {}
		enum ModifierType{
			POSITION,
			ROTATION,
			COLOR,
			ALPHA,
			MASK,
			CLIPRECT,
			MARKER
		};
		virtual ModifierType getType() = 0;
		virtual void apply( RenderOperation& in_out ) = 0;
	};

} // namespace OpenGUI{

#endif // BD2BBBC1_8162_4B02_A871_4AEAC49BAC26

