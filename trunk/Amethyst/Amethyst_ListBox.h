#ifndef Amethyst_ListBox_h__
#define Amethyst_ListBox_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"

namespace OpenGUI {
	namespace Amethyst {

		class AMETHYST_API ListBox: public Control {
		public:
			ListBox();
			virtual ~ListBox();


			static Widget* CreateListBoxFactory();

		protected:
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );
		};

	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_ListBox_h__
