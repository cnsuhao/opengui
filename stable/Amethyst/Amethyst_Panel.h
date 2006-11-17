#ifndef Amethyst_Panel_h__
#define Amethyst_Panel_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"

namespace OpenGUI {
	namespace Amethyst {

		class AMETHYST_API Panel: public ContainerControl {
		public:
			Panel();
			virtual ~Panel();

			// override this function to create the scrolling functionality.
			virtual void _draw( Brush& brush );

			static Widget* CreatePanelFactory();

		protected:
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );
		};

	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_Panel_h__
