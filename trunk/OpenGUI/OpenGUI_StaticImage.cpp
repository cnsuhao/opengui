#include "OpenGUI_BaseWidgets.h"

namespace OpenGUI{
	namespace Widgets{
		//#####################################################################
		Widget* StaticImage::createStaticImageFactory()
		{
			return new StaticImage;
		}
		//#####################################################################
		StaticImage::StaticImage() {
			PropertySet_BindProperty("Imagery", OpenGUI::PT_STRING, &StaticImage::_prop_SetImagery, &StaticImage::_prop_GetImagery);
		}
		//#####################################################################
		StaticImage::~StaticImage() {}
		//#####################################################################
		Render::RenderOperationList StaticImage::buildWidgetRenderOpList()
		{
			Render::PrimitiveBox box;
			box.setRect(this->getRect());
			box.setTextureImagery(mImageryPtr);
			return box.getRenderOperationList();
		}
		//#####################################################################
		void StaticImage::setImagery(std::string imageryName)
		{
			dirtyCache();
			mImageryPtr = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		bool StaticImage::_prop_SetImagery(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			StaticImage* w = static_cast<StaticImage*>(widget);
			w->setImagery(newValueStr);
			return true;
		}
		//#####################################################################
		bool StaticImage::_prop_GetImagery(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			StaticImage* w = static_cast<StaticImage*>(widget);
			curValue = w->mImageryPtr ? w->mImageryPtr->getName() : "";
			return true;
		}
		//#####################################################################
	};
};

