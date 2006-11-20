#ifndef Amethyst_ListBox_h__
#define Amethyst_ListBox_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"
#include "Amethyst_Frame.h"

namespace OpenGUI {
	namespace Amethyst {

		class AMETHYST_API ListBox: public Frame {
		public:
			ListBox();
			virtual ~ListBox();


			static Widget* CreateListBoxFactory();

		protected:
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );
			virtual void onResized( Object* sender, Resized_EventArgs& evtArgs );
			virtual void onMoved( Object* sender, Moved_EventArgs& evtArgs );
		};

	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_ListBox_h__
