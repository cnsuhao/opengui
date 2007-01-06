// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef E87C0C09_B206_4074_B083_0675D189FAD5
#define E87C0C09_B206_4074_B083_0675D189FAD5

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_RenderOperation.h"

namespace OpenGUI {

	//! \internal Marker modifier used to mark the stack size for guaranteed pop-backs
	class OPENGUI_API BrushModifier_Marker : public BrushModifier {
	public:
		virtual ModifierType getType() {
			return MARKER;
		}
		void* mID;
		virtual void apply( RenderOperation& in_out ) {
			/* These work purely by existing, so there is nothing special to do */
		}
	};

} // namespace OpenGUI{

#endif // E87C0C09_B206_4074_B083_0675D189FAD5
