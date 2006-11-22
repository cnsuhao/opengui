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
			Frame::onDraw( sender, evtArgs );
		}

		void ListBox::onResized( Object* sender, Resized_EventArgs& evtArgs )
		{
			//reset the position and size of our children

			Frame::onResized(sender, evtArgs);
		}

		void ListBox::onMoved( Object* sender, Moved_EventArgs& evtArgs )
		{
			Frame::onMoved(sender, evtArgs);
		}
	}
}
