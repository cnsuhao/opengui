#ifndef F7817EF2_3AC8_4cd1_9117_72EECA430C97
#define F7817EF2_3AC8_4cd1_9117_72EECA430C97
#include "OpenGUI.h"



namespace OpenGUI {
	namespace Examples {
		//! The tachometer widget provides an RPM gauge functionality, most commonly used in racing games.
		/*! This widget also provides the ability to display a small amount of information on top of the
			tachometer, like a small LCD screen. This is originally intended to display vehicle speed.
		*/
		class OPENGUI_WIDGET_API Tachometer : public Control {
		public:
			Tachometer();
			virtual ~Tachometer();
			//! Sets the background imagery for the tachometer
			void setBackgroundImagery( std::string imageryName );
			//! gets the background imagery
			const std::string& getBackgroundImagery();

			//! Sets the Imagery used for the needle
			void setNeedleImagery( std::string imageryName );
			//! gets the needle imagery
			const std::string& getNeedleImagery();

			//! Sets the location within the BG imagery where the needle pivot should be
			void setNeedlePivot( const FVector2& pivotLocation );
			//! returns current needle pivot
			const FVector2& getNeedlePivot() {
				return mNeedlePivot;
			}

			//! Sets the point in the needle imagery where it attaches to the needle pivot
			void setNeedleAnchor( const FVector2& anchorLocation );
			//! returns current needle anchor
			const FVector2& getNeedleAnchor() {
				return mNeedleAnchor;
			}

			//! Specifies the startAngle (when value==0) in degrees
			void setNeedleStartAngle( float startAngle );
			//! gets the start angle
			float getNeedleStartAngle();

			//! Sets the total sweep range toward maxValue in degrees
			void setNeedleSweepAngle( float sweepAngle );
			//! gets the total sweep range
			float getNeedleSweepAngle();

			//! Sets the maximum value
			void setNeedleMaxValue( float maxValue );
			//! gets the maximum value
			float getNeedleMaxValue();

			//! Sets the current tachometer value
			void setNeedleValue( float currentValue );
			//! returns current tachometer value
			float getNeedleValue() {
				return mCurrentValue;
			}

			static Widget* createTachometerFactory();

			virtual ObjectAccessorList* getAccessors();

		protected:
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );
			virtual void onResized( Object* sender, Resized_EventArgs& evtArgs );

		private:
			ImageryPtr mBGImageryPtr;
			ImageryPtr mNeedleImageryPtr;
			FVector2 mNeedlePivot; //where the needle pivots/attaches in the background imagery
			FVector2 mNeedleAnchor; //the location in the needle imagery that needs to attach to the pivot

			float mCurrentValue;
			float mStartAngle;
			float mMaxValue;
			float mEndAngle;
		};
	}//namespace Examples{
} //namespace OpenGUI{
#endif

