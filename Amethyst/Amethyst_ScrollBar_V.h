#ifndef Amethyst_ScrollBar_V_h__
#define Amethyst_ScrollBar_V_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"
#include "Amethyst_Button.h"

namespace OpenGUI {
	namespace Amethyst {

		class AMETHYST_API ScrollBar_V: public ContainerControl {
		public:
			ScrollBar_V();
			virtual ~ScrollBar_V();


			static Widget* CreateScrollBar_VFactory();

		protected:
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );

			ImageryPtr mTrackImage;
			ImageryPtr mThumbImage;

			FRect mTrackRect;
			float mThumbPosPct;

			SimpleButton *m_pLineUpButton;
			SimpleButton *m_pLineDownButton;
		};

	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_ScrollBar_V_h__
