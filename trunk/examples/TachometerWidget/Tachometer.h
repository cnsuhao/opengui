#ifndef A1AF9FB1_0056_415f_A32B_3499D103BCD9
#define A1AF9FB1_0056_415f_A32B_3499D103BCD9
#include "OpenGUI_BaseWidgets.h"


namespace OpenGUI{
	namespace Widgets{

		//! The tachometer widget provides an RPM gauge functionality, most commonly used in racing games.
		/*! This widget also provides the ability to display a small amount of information on top of the
			tachometer, like a small LCD screen. This is originally intended to display vehicle speed.
		*/
		class OPENGUI_WIDGET_API Tachometer : public Widget
		{
		public:
			Tachometer();
			virtual ~Tachometer();
			//! Sets the background imagery for the tachometer
			void setBackgroundImagery(std::string imageryName);
			//! Sets the location within the BG imagery where the needle pivot should be
			void setNeedlePivot(const FVector2& pivotLocation);
			//! Sets the Imagery used for the needle
			void setNeedleImagery(std::string imageryName);
			//! Sets the point in the needle imagery where it attaches to the needle pivot
			void setNeedleAnchor(const FVector2& anchorLocation);
			//! Specifies the minimum and maximum displayable values, and the angles that represent them
			void setNeedleScale(float minValue, float minValueAngle, float maxValue, float maxValueAngle);
			//! Sets the current tachometer value
			void setNeedleValue(float currentValue);

			static Widget* createTachometerFactory();
		protected:
			virtual Render::RenderOperationList buildWidgetRenderOpList();

			virtual bool defaultMessageHandler(const Msg::Message &message);

			ImageryPtr mBGImageryPtr;
			ImageryPtr mNeedleImageryPtr;
			FVector2 mNeedlePivot; //where the needle pivots/attaches in the background imagery
			FVector2 mNeedleAnchor; //the location in the needle imagery that needs to attach to the pivot

			float mCurrentValue;
			float mMinValue;
			float mMinValueAngle;
			float mMaxValue;
			float mMaxValueAngle;

		private:
 			static bool _prop_SetBGImagery(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
 			static bool _prop_GetBGImagery(PropertySet* widget, const std::string& propertyName, std::string& curValue);
			static bool _prop_SetNeedleImagery(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetNeedleImagery(PropertySet* widget, const std::string& propertyName, std::string& curValue);
			static bool _prop_SetNeedleAnchor(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetNeedleAnchor(PropertySet* widget, const std::string& propertyName, std::string& curValue);
			static bool _prop_SetNeedlePivot(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetNeedlePivot(PropertySet* widget, const std::string& propertyName, std::string& curValue);

			static bool _prop_SetNeedleValue(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetNeedleValue(PropertySet* widget, const std::string& propertyName, std::string& curValue);


			static bool _prop_SetNeedleMinValue(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetNeedleMinValue(PropertySet* widget, const std::string& propertyName, std::string& curValue);
			static bool _prop_SetNeedleMaxValue(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetNeedleMaxValue(PropertySet* widget, const std::string& propertyName, std::string& curValue);

			static bool _prop_SetNeedleMinAngle(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetNeedleMinAngle(PropertySet* widget, const std::string& propertyName, std::string& curValue);
			static bool _prop_SetNeedleMaxAngle(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetNeedleMaxAngle(PropertySet* widget, const std::string& propertyName, std::string& curValue);
};
	};//namespace Widgets{
};//namespace OpenGUI{
#endif

