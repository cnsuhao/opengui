#include "OpenGUI_BaseWidgets.h"

namespace OpenGUI{
	namespace Widgets{
		Widget* Container::createContainerFactory()
		{
			return new Container;
		}
		Container::Container()
		{
			//
		}
		Container::~Container()
		{
			//
		}
		Render::RenderOperationList Container::buildWidgetRenderOpList()
		{
			return Render::RenderOperationList();
		}
	}//namespace Widgets{
}//namespace OpenGUI{