#include "OpenGUI.h"


namespace OpenGUI{
	namespace Widgets{
		//#####################################################################
		Render::RenderOperationList Widget::buildWidgetRenderOpList()
		{
			Render::PrimitiveBox box;
			box.setRect(this->getRect());
			return box.getRenderOperationList();
		}
		//#####################################################################
	};
};


