#ifndef A1AF9FB1_0056_415f_A32B_3499D103BCD9
#define A1AF9FB1_0056_415f_A32B_3499D103BCD9
#include "OpenGUI_BaseWidgets.h"


namespace OpenGUI{
	namespace Widgets{

		//! The tachometer widget provides an RPM gauge functionality, most commonly used in racing games.
		/*! This widget also provides the ability to display a small amount of information on top of the
			tachometer, like a small LCD screen. This is originally intended to display vehicle speed.
		*/
		class OPENGUI_API Tachometer : public Widget
		{
		public:
			Tachometer();
			virtual ~Tachometer();
			//! Sets the normal button imagery.
			void setImagery(std::string imageryName);


			//! This is just a factory interface.
			static Widget* createTachometerFactory();
		protected:
			virtual Render::RenderOperationList buildWidgetRenderOpList();

			bool defaultMessageHandler(const Msg::Message &message);

			ImageryPtr mImageryPtr;
			ImageryPtr mImageryPtrPressed;
			ImageryPtr mImageryPtrMouseOver;
			ImageryPtr mImageryPtrDisabled;
			bool m_MouseOver;
			bool m_ButtonDown;

		private:
// 			static bool _prop_SetImagery(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
// 			static bool _prop_GetImagery(PropertySet* widget, const std::string& propertyName, std::string& curValue);
// 			static bool _prop_SetImageryPressed(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
// 			static bool _prop_GetImageryPressed(PropertySet* widget, const std::string& propertyName, std::string& curValue);
// 			static bool _prop_SetImageryMouseOver(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
// 			static bool _prop_GetImageryMouseOver(PropertySet* widget, const std::string& propertyName, std::string& curValue);
// 			static bool _prop_SetImageryDisabled(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
// 			static bool _prop_GetImageryDisabled(PropertySet* widget, const std::string& propertyName, std::string& curValue);
		};
	};//namespace Widgets{
};//namespace OpenGUI{
#endif

