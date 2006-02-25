#ifndef FC5CDB66_5B26_40b7_8978_1CA8F3E11442
#define FC5CDB66_5B26_40b7_8978_1CA8F3E11442
#include "OpenGUI_BaseWidgets.h"

namespace OpenGUI{
	namespace Widgets{
		class OPENGUI_API StaticImage : public Widget
		{
		public:
			StaticImage();
			~StaticImage();
			void setImagery(std::string imageryName);
		protected:
			virtual Render::RenderOperationList buildWidgetRenderOpList();
			ImageryPtr mImageryPtr;
		};
	};//namespace Widgets{
};//namespace OpenGUI{
#endif
