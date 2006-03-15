#ifndef A1AF9FB1_0056_415f_A32B_3499D103BCD9
#define A1AF9FB1_0056_415f_A32B_3499D103BCD9
#include "OpenGUI_BaseWidgets.h"


namespace OpenGUI{
	namespace Widgets{
		class OPENGUI_API SimpleButton : public Widget
		{
		public:
			SimpleButton();
			virtual ~SimpleButton();
			//! Sets the normal button imagery.
			void setImagery(std::string imageryName);
			//! Sets the pressed button imagery. If none specified, uses the Normal imagery.
			void setImageryPressed(std::string imageryName);
			//! Sets the mouse over button imagery. If none specified, uses the Normal imagery.
			void setImageryMouseOver(std::string imageryName);
			//! Sets the disabled button imagery. If none specified, uses the Normal imagery.
			void setImageryDisabled(std::string imageryName);

			//! This is just a factory interface.
			static Widget* createSimpleButtonFactory();
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
			static bool _prop_SetImagery(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetImagery(PropertySet* widget, const std::string& propertyName, std::string& curValue);
			static bool _prop_SetImageryPressed(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetImageryPressed(PropertySet* widget, const std::string& propertyName, std::string& curValue);
			static bool _prop_SetImageryMouseOver(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetImageryMouseOver(PropertySet* widget, const std::string& propertyName, std::string& curValue);
			static bool _prop_SetImageryDisabled(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetImageryDisabled(PropertySet* widget, const std::string& propertyName, std::string& curValue);
		};
	};//namespace Widgets{
};//namespace OpenGUI{
#endif
