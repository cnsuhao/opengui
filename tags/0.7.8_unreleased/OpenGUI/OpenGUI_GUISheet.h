#ifndef D440A1F1_8CDF_4162_9E63_E604DFE59D75
#define D440A1F1_8CDF_4162_9E63_E604DFE59D75

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Element.h"

namespace OpenGUI{
	class Renderer;

	//! This is the base Element from which all GUI hierarchies are built upon.
	class OPENGUI_API GUISheet : public Element
	{
		friend class System;
	protected:
		//! Applications should not create GUISheets directly, instead they should use System::createGUISheet()
		GUISheet(std::string name);

		//! Renders the contents of this GUI sheet by sending the render operations to the given Renderer
		void renderGUISheet(Renderer* rendererPtr);

	private:
		
	};
};//namespace OpenGUI{
#endif
