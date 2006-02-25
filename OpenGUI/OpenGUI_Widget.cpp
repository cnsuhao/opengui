#include "OpenGUI.h"


namespace OpenGUI{
	namespace Widgets{
		//#####################################################################
		Render::RenderOperationList Widget::buildWidgetRenderOpList()
		{
			Render::PrimitiveBox box;
			box.setRect(mElementRect);
			return box.getRenderOperationList();
		}
		//#####################################################################
	};
};


