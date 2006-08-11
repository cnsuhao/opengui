#ifndef D98DCD89_7EDC_4859_AD42_89952365E9B5
#define D98DCD89_7EDC_4859_AD42_89952365E9B5

#include "OpenGUI_BaseWidgets.h"

namespace OpenGUI{
	namespace Widgets{

		/*! \brief This Widget provides a method of drawing auto-scaling images,
			useful for backgrounds in buttons other objects that require variable
			size but would like to maintain some level of control over pixel stretching.

			\see \ref BW_FrameImage "ScalingImage widget documentation"
		*/
		class OPENGUI_API FrameImage : public Widget
		{
		public:
			//! Constructor
			FrameImage();
			//! virtual Destructor
			virtual ~FrameImage();

			//! Sets imagery for the Upper Left zone
			void setImagery_UL(std::string imageryName);
			//! Sets imagery for the Upper Middle zone
			void setImagery_UM(std::string imageryName);
			//! Sets imagery for the Upper Right zone
			void setImagery_UR(std::string imageryName);

			//! Sets imagery for the Middle Left zone
			void setImagery_ML(std::string imageryName);
			//! Sets imagery for the Middle Middle zone
			void setImagery_MM(std::string imageryName);
			//! Sets imagery for the Middle Right zone
			void setImagery_MR(std::string imageryName);

			//! Sets imagery for the Lower Left zone
			void setImagery_LL(std::string imageryName);
			//! Sets imagery for the Lower Middle zone
			void setImagery_LM(std::string imageryName);
			//! Sets imagery for the Lower Right zone
			void setImagery_LR(std::string imageryName);

			//! This is just a factory interface.
			static Widget* createFrameImageFactory();

		protected:
			virtual Render::RenderOperationList buildWidgetRenderOpList();
			ImageryPtr mImageryPtr_UL;
			ImageryPtr mImageryPtr_UM;
			ImageryPtr mImageryPtr_UR;
			ImageryPtr mImageryPtr_ML;
			ImageryPtr mImageryPtr_MM;
			ImageryPtr mImageryPtr_MR;
			ImageryPtr mImageryPtr_LL;
			ImageryPtr mImageryPtr_LM;
			ImageryPtr mImageryPtr_LR;


		private:
			static bool _prop_SetImagery(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetImagery(PropertySet* widget, const std::string& propertyName, std::string& curValue);
		};

	}//namespace Widgets{
}//namespace OpenGUI{


#endif
