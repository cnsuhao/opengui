#ifndef F7817EF2_3AC8_4cd1_9117_72EECA430C97
#define F7817EF2_3AC8_4cd1_9117_72EECA430C97
#include "OpenGUI_Widget.h"



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
 			
};
	};//namespace Widgets{
};//namespace OpenGUI{
#endif

