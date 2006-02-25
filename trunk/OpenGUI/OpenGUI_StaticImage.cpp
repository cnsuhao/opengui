#include "OpenGUI_BaseWidgets.h"
//#include "mmgr.h"
namespace OpenGUI{
	namespace Widgets{
		StaticImage::StaticImage() {}
		//#####################################################################
		StaticImage::~StaticImage() {}
		//#####################################################################
		Render::RenderOperationList StaticImage::buildWidgetRenderOpList()
		{
			Render::PrimitiveBox box;
			box.setRect(mElementRect);
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