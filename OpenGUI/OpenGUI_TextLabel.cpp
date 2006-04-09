#include "OpenGUI_BaseWidgets.h"

namespace OpenGUI{
	namespace Widgets{
		//#####################################################################
		TextLabel::TextLabel()
		{
			//
		}
		//#####################################################################
		TextLabel::~TextLabel()
		{
			//
		}
		//#####################################################################
		Widget* TextLabel::createTextLabelFactory()
		{
			//
			return 0;
		}
		//#####################################################################
		Render::RenderOperationList TextLabel::buildWidgetRenderOpList()
		{
			return Render::RenderOperationList();
		}
	};
};
