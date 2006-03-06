#ifndef D440A1F1_8CDF_4162_9E63_E604DFE59D75
#define D440A1F1_8CDF_4162_9E63_E604DFE59D75

#include "OpenGUI_Exports.h"
#include "OpenGUI_Element.h"

namespace OpenGUI{
	class OPENGUI_API GUISheet : public Element
	{
	public:
		//! Applications should not create GUISheets directly, instead they should use System::createGUISheet()
		GUISheet(std::string name);
	protected:

	private:
		
	};
};//namespace OpenGUI{
#endif
