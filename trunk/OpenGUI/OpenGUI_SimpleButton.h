#ifndef A1AF9FB1_0056_415f_A32B_3499D103BCD9
#define A1AF9FB1_0056_415f_A32B_3499D103BCD9
#include "OpenGUI_BaseWidgets.h"


namespace OpenGUI{
	namespace Widgets{
		class OPENGUI_API SimpleButton : public Widget
		{
		public:
			SimpleButton();
			virtual ~SimpleButton();
			//! Sets the normal button imagery.
			void setImagery(std::string imageryName);
			//! Sets the pressed button imagery. If none specified, uses the Normal imagery.
			void setImageryPressed(std::string imageryName);
			//! Sets the mouse over button imagery. If none specified, uses the Normal imagery.
			void setImageryMouseOver(std::string imageryName);
			//! Sets the disabled button imagery. If none specified, uses the Normal imagery.
			void setImageryDisabled(std::string imageryName);
		protected:
			virtual Render::RenderOperationList buildWidgetRenderOpList();

			bool defaultMessageHandler(const Msg::Message &message);

			ImageryPtr mImageryPtr;
			ImageryPtr mImageryPtrPressed;
			ImageryPtr mImageryPtrMouseOver;
			ImageryPtr mImageryPtrDisabled;
			bool m_MouseOver;
			bool m_ButtonDown;
		};
	};//namespace Widgets{
};//namespace OpenGUI{
#endif
