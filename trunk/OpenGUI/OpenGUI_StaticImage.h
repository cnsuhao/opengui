#ifndef FC5CDB66_5B26_40b7_8978_1CA8F3E11442
#define FC5CDB66_5B26_40b7_8978_1CA8F3E11442
#include "OpenGUI_BaseWidgets.h"

namespace OpenGUI {
	namespace Widgets {

		//! Built in Widget that displays a static image.
		/*!
			\see \ref BW_StaticImage "StaticImage widget documentation"
		*/
		class OPENGUI_API StaticImage : public Widget {
		public:
			//! Constructor
			StaticImage();
			//! virtual Destructor
			virtual ~StaticImage();
			//! Sets the imagery to be used by this object
			void setImagery( std::string imageryName );

			//! This is just a factory interface.
			static Widget* createStaticImageFactory();

		protected:
			virtual Render::RenderOperationList buildWidgetRenderOpList();
			ImageryPtr mImageryPtr;

		private:
			static bool _prop_SetImagery( PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr );
			static bool _prop_GetImagery( PropertySet* widget, const std::string& propertyName, std::string& curValue );
		};
	}
	;//namespace Widgets{
}
;//namespace OpenGUI{
#endif
