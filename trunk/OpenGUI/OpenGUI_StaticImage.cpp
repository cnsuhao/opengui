#include "OpenGUI_BaseWidgets.h"
//#include "mmgr.h"
namespace OpenGUI{
	namespace Widgets{
		//#####################################################################
		Widget* StaticImage::createStaticImageFactory()
		{
			return new StaticImage;
		}
		//#####################################################################
		StaticImage::StaticImage() {}
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
			mImageryPtr = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
	};
};