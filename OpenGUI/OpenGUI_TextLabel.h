#ifndef E3B7005D_9A7A_4bd1_B9DF_8C50A140033E
#define E3B7005D_9A7A_4bd1_B9DF_8C50A140033E
#include "OpenGUI_BaseWidgets.h"


namespace OpenGUI{
	namespace Widgets{
		class OPENGUI_API TextLabel : public Widget
		{
		public:
			TextLabel();
			~TextLabel();

			//! This is just a factory interface.
			static Widget* createTextLabelFactory();

		protected:
			virtual Render::RenderOperationList buildWidgetRenderOpList();

		private:
		};
	};//namespace Widgets{
};//namespace OpenGUI{
#endif
