#include "Amethyst_ScrollBar_V.h"


namespace OpenGUI {
	namespace Amethyst {

		ScrollBar_V::ScrollBar_V()
		{
		}

		ScrollBar_V::~ScrollBar_V()
		{
		}


		Widget* ScrollBar_V::CreateScrollBar_VFactory()
		{
			return new ScrollBar_V;
		}

		void ScrollBar_V::onDraw( Object* sender, Draw_EventArgs& evtArgs )
		{
			Control::onDraw(sender, evtArgs);
		}



	} // namespace Amethyst{
} // namespace OpenGUI{

