
#define OPENGUI_WIDGET_EXPORTS
#include "Tachometer.h"

namespace OpenGUI {
	namespace Examples {
		//############################################################################
		Tachometer::Tachometer() {
			mCurrentValue = 0.0f;
			mStartAngle = 0.0f;
			mMaxValue = 0.0f;
			mEndAngle = 0.0f;
		}
		//############################################################################
		Tachometer::~Tachometer() {
			/**/
		}
		//############################################################################
		Widget* Tachometer::createTachometerFactory() {
			return new Tachometer;
		}
		//############################################################################
		void Tachometer::onResized( Object* sender, Resized_EventArgs& evtArgs ) {
			if ( evtArgs.newSize.x != evtArgs.newSize.y ) {
				if ( evtArgs.newSize.x < evtArgs.newSize.y )
					setWidth( evtArgs.newSize.y );
				else
					setHeight( evtArgs.newSize.x );
			}
		}
		//############################################################################
		void Tachometer::onDraw( Object* sender, Draw_EventArgs& evtArgs ) {
			Brush& b = evtArgs.brush;
			const FVector2& PPU = b.getPPU();
			const float scaleX = getRect().getWidth() / (( float )mBGImageryPtr->getImagesetRect().getWidth() ) ;
			const float scaleY = getRect().getWidth()  / (( float )mBGImageryPtr->getImagesetRect().getHeight() );
			b.Image.drawImage( mBGImageryPtr, getRect() );

			//calculate necessary rotation to represent current needle value
			float anglePerUnit;
			anglePerUnit = mEndAngle / mMaxValue;
			float desiredAngle = ( mCurrentValue * anglePerUnit );

			FVector2 anchorPos;
			FVector2 needleOffset;
			anchorPos.x = getRect().getWidth() * mNeedlePivot.x;
			anchorPos.y = getRect().getHeight() * mNeedlePivot.y;

			b.pushPosition( getPosition() );
			b.pushPosition( anchorPos );
			b.pushRotation( Degree( mStartAngle ) );
			b.pushRotation( Degree( desiredAngle ) );

			//calculate scaled needle size
			float deg = b.getRotation().valueDegrees();
			deg = Math::FAbs( Math::FMod( deg, 180.0f ) ) / 180.0f;
			deg -= 0.5f;
			deg *= 2;
			float perc = Math::FAbs( deg );
			FVector2 needleScale;
			needleScale.x = scaleX * perc + scaleY * ( 1.0f - perc );
			needleScale.y = scaleY * perc + scaleX * ( 1.0f - perc );

			FVector2 needleSize(
				(( float )mNeedleImageryPtr->getImagesetRect().getWidth() ) * needleScale.x,
				(( float )mNeedleImageryPtr->getImagesetRect().getHeight() ) * needleScale.y
			);

			//calculate appropriate needle offset
			b.getPPU(); // force PPU recalculation
			needleOffset.x = needleSize.x * mNeedleAnchor.x;
			needleOffset.y = needleSize.y * mNeedleAnchor.y;
			needleOffset.x = -needleOffset.x;
			needleOffset.y = -needleOffset.y;
			b.pushPosition( needleOffset );

			b.Image.drawImage( mNeedleImageryPtr, FVector2(), needleSize );

			b.pop(); //b.pushPosition(needleOffset);
			b.pop(); //b.pushRotation(Degree(mStartAngle));
			b.pop(); //b.pushRotation(Degree(desiredAngle));
			b.pop(); //b.pushPosition(anchorPos);
			b.pop(); //b.pushPosition(getPosition());
		}
		//############################################################################
		void Tachometer::setBackgroundImagery( std::string imageryName ) {
			invalidate();
			mBGImageryPtr = ImageryManager::getSingleton().getImagery( imageryName );
		}
		//############################################################################
		void Tachometer::setNeedlePivot( const FVector2& pivotLocation ) {
			invalidate();
			mNeedlePivot = pivotLocation;
		}
		//############################################################################
		void Tachometer::setNeedleImagery( std::string imageryName ) {
			invalidate();
			mNeedleImageryPtr = ImageryManager::getSingleton().getImagery( imageryName );
		}
		//############################################################################
		void Tachometer::setNeedleAnchor( const FVector2& anchorLocation ) {
			invalidate();
			mNeedleAnchor = anchorLocation;
		}
		//############################################################################
		void Tachometer::setNeedleScale( float startAngle, float maxValue, float sweepAngle ) {
			invalidate();
			mStartAngle = startAngle;
			mMaxValue = maxValue;
			mEndAngle = sweepAngle;
		}
		//############################################################################
		void Tachometer::setNeedleValue( float currentValue ) {
			invalidate();
			mCurrentValue = currentValue;
		}
		//############################################################################
	}//namespace Examples
}//namespace OpenGUI{