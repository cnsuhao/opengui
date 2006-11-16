#include "Amethyst_ListBox.h"

namespace OpenGUI {
	namespace Amethyst {

		ListBox::ListBox()
		{
		}

		ListBox::~ListBox()
		{
		}


		Widget* ListBox::CreateListBoxFactory()
		{
			return new ListBox;
		}

		void ListBox::onDraw( Object* sender, Draw_EventArgs& evtArgs )
		{
			Control::onDraw( sender, evtArgs );
		}


	}
}
