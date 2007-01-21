// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#define OPENGUI_WIDGET_EXPORTS
#include "Tachometer.h"

namespace OpenGUI {
	namespace Examples {
		//############################################################################
		class Tachometer_StartAngle_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "NeedleStartAngle";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					Tachometer& t = dynamic_cast<Tachometer&>( objectRef );
					valueOut.setValue( t.getNeedleStartAngle() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					Tachometer& t = dynamic_cast<Tachometer&>( objectRef );
					t.setNeedleStartAngle( valueIn.getValueAsFloat() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_FLOAT;
			}
		}
		gTachometer_StartAngle_ObjectProperty;
		//############################################################################
		class Tachometer_MaxValue_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "NeedleMaxValue";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					Tachometer& t = dynamic_cast<Tachometer&>( objectRef );
					valueOut.setValue( t.getNeedleMaxValue() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					Tachometer& t = dynamic_cast<Tachometer&>( objectRef );
					t.setNeedleMaxValue( valueIn.getValueAsFloat() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_FLOAT;
			}
		}
		gTachometer_MaxValue_ObjectProperty;
		//############################################################################
		class Tachometer_SweepAngle_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "NeedleSweepAngle";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					Tachometer& t = dynamic_cast<Tachometer&>( objectRef );
					valueOut.setValue( t.getNeedleSweepAngle() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					Tachometer& t = dynamic_cast<Tachometer&>( objectRef );
					t.setNeedleSweepAngle( valueIn.getValueAsFloat() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_FLOAT;
			}
		}
		gTachometer_SweepAngle_ObjectProperty;
		//############################################################################
		class Tachometer_BackgroundImagery_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "BackgroundImagery";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					Tachometer& t = dynamic_cast<Tachometer&>( objectRef );
					valueOut.setValue( t.getBackgroundImagery() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					Tachometer& t = dynamic_cast<Tachometer&>( objectRef );
					t.setBackgroundImagery( valueIn.getValueAsString() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_STRING;
			}
		}
		gTachometer_BackgroundImagery_ObjectProperty;
		//############################################################################
		class Tachometer_NeedleImagery_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "NeedleImagery";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					Tachometer& t = dynamic_cast<Tachometer&>( objectRef );
					valueOut.setValue( t.getNeedleImagery() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					Tachometer& t = dynamic_cast<Tachometer&>( objectRef );
					t.setNeedleImagery( valueIn.getValueAsString() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_STRING;
			}
		}
		gTachometer_NeedleImagery_ObjectProperty;
		//############################################################################
		class Tachometer_NeedleValue_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "NeedleValue";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					Tachometer& t = dynamic_cast<Tachometer&>( objectRef );
					valueOut.setValue( t.getNeedleValue() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					Tachometer& t = dynamic_cast<Tachometer&>( objectRef );
					t.setNeedleValue( valueIn.getValueAsFloat() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_FLOAT;
			}
		}
		gTachometer_NeedleValue_ObjectProperty;
		//############################################################################
		class Tachometer_NeedleAnchor_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "NeedleAnchor";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					Tachometer& t = dynamic_cast<Tachometer&>( objectRef );
					valueOut.setValue( t.getNeedleAnchor() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					Tachometer& t = dynamic_cast<Tachometer&>( objectRef );
					t.setNeedleAnchor( valueIn.getValueAsFVector2() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_FVECTOR2;
			}
		}
		gTachometer_NeedleAnchor_ObjectProperty;
		//############################################################################
		class Tachometer_NeedlePivot_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "NeedlePivot";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					Tachometer& t = dynamic_cast<Tachometer&>( objectRef );
					valueOut.setValue( t.getNeedlePivot() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					Tachometer& t = dynamic_cast<Tachometer&>( objectRef );
					t.setNeedlePivot( valueIn.getValueAsFVector2() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_FVECTOR2;
			}
		}
		gTachometer_NeedlePivot_ObjectProperty;
		//############################################################################
		//############################################################################
		class Tachometer_ObjectAccessorList : public ObjectAccessorList {
		public:
			Tachometer_ObjectAccessorList() {
				addAccessor( &gTachometer_NeedlePivot_ObjectProperty );
				addAccessor( &gTachometer_NeedleAnchor_ObjectProperty );
				addAccessor( &gTachometer_NeedleValue_ObjectProperty );
				addAccessor( &gTachometer_NeedleImagery_ObjectProperty );
				addAccessor( &gTachometer_BackgroundImagery_ObjectProperty );
				addAccessor( &gTachometer_SweepAngle_ObjectProperty );
				addAccessor( &gTachometer_MaxValue_ObjectProperty );
				addAccessor( &gTachometer_StartAngle_ObjectProperty );
			}
			~Tachometer_ObjectAccessorList() {}
		}
		gTachometer_ObjectAccessorList;
		//############################################################################
		//############################################################################

		//############################################################################
		ObjectAccessorList* Tachometer::getAccessors() {
			return &gTachometer_ObjectAccessorList;
		}
		//############################################################################
		Tachometer::Tachometer() {
			if ( gTachometer_ObjectAccessorList.getParent() == 0 )
				gTachometer_ObjectAccessorList.setParent( Control::getAccessors() );

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
		void Tachometer::setBackgroundImagery( const String& imageryName ) {
			invalidate();
			mBGImageryPtr = ImageryManager::getSingleton().getImagery( imageryName );
		}
		//############################################################################
		const String& Tachometer::getBackgroundImagery() {
			static String retval;
			if ( mBGImageryPtr ) {
				retval = mBGImageryPtr->getName();
			} else {
				retval = "";
			}
			return retval;
		}
		//############################################################################
		void Tachometer::setNeedlePivot( const FVector2& pivotLocation ) {
			invalidate();
			mNeedlePivot = pivotLocation;
		}
		//############################################################################
		void Tachometer::setNeedleImagery( const String& imageryName ) {
			invalidate();
			mNeedleImageryPtr = ImageryManager::getSingleton().getImagery( imageryName );
		}
		//############################################################################
		const String& Tachometer::getNeedleImagery() {
			static String retval;
			if ( mNeedleImageryPtr ) {
				retval = mNeedleImageryPtr->getName();
			} else {
				retval = "";
			}
			return retval;
		}
		//############################################################################
		void Tachometer::setNeedleAnchor( const FVector2& anchorLocation ) {
			invalidate();
			mNeedleAnchor = anchorLocation;
		}
		//############################################################################
		void Tachometer::setNeedleStartAngle( float startAngle ) {
			invalidate();
			mStartAngle = startAngle;
		}
		//############################################################################
		float Tachometer::getNeedleStartAngle() {
			return mStartAngle;
		}
		//############################################################################
		void Tachometer::setNeedleSweepAngle( float sweepAngle ) {
			invalidate();
			mEndAngle = sweepAngle;
		}
		//############################################################################
		float Tachometer::getNeedleSweepAngle() {
			return mEndAngle;
		}
		//############################################################################
		void Tachometer::setNeedleMaxValue( float maxValue ) {
			invalidate();
			mMaxValue = maxValue;
		}
		//############################################################################
		float Tachometer::getNeedleMaxValue() {
			return mMaxValue;
		}
		//############################################################################
		void Tachometer::setNeedleValue( float currentValue ) {
			invalidate();
			mCurrentValue = currentValue;
		}
		//############################################################################
	}//namespace Examples
}//namespace OpenGUI{