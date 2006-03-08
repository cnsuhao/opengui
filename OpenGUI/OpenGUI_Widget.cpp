#include "OpenGUI.h"


namespace OpenGUI{
	namespace Widgets{

		//#####################################################################
		Widget::Widget()
		{
			PropertySet_BindProperty("Position", OpenGUI::PT_FVECTOR2, &Widget::_prop_SetPos, &Widget::_prop_GetPos);
		}
		//#####################################################################
		Render::RenderOperationList Widget::buildWidgetRenderOpList()
		{
			Render::PrimitiveBox box;
			box.setRect(this->getRect());
			return box.getRenderOperationList();
		}
		//#####################################################################
		bool Widget::_prop_SetPos(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			Widget* w = static_cast<Widget*>(widget);
			if(!newValuePtr) return false;
			FVector2 newPos = *static_cast<const FVector2*>(newValuePtr);
			w->setPos(newPos);
			return true;
		}
		//#####################################################################
		bool Widget::_prop_GetPos(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			Widget* w = static_cast<Widget*>(widget);
			PropertyParser::toStrFVector2(w->getRect().getPosition(),curValue);
			return true;
		}
		//#####################################################################
	};
};


