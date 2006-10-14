#ifndef C1299AA7_4E0D_4E2D_88C1_4E8F5F79C438
#define C1299AA7_4E0D_4E2D_88C1_4E8F5F79C438

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"

namespace OpenGUI {

	//! Provides math library functions in an inline-able yet abstracted form.
	/*! This math lib exists so that the function they represent can be replaced
	with high speed alternatives or hardware acceleration where appropriate. */
	class OPENGUI_API Math {
	public:
		//! converts degrees into radians
		static float DegreesToRadians( float degrees ) {
			return degrees * fDeg2Rad;
		}
		//! converts radians into degrees
		static float RadiansToDegrees( float radians ) {
			return radians * fRad2Deg;
		}

		//! sine
		static float Sin( float fValue ) {
			return sin( fValue );
		}
		//! cosine
		static float Cos( float fValue ) {
			return cos( fValue );
		}
		//! tangent
		static float Tan( float fValue ) {
			return tan( fValue );
		}

		//! arc sine
		static float ASin( float fValue ) {
			return asin( fValue );
		}
		//! arc cosine
		static float ACos( float fValue ) {
			return acos( fValue );
		}
		//! arc tangent
		static float ATan( float fValue ) {
			return atan( fValue );
		}
		//! arc tangent of y/x
		static float ATan2( float fY, float fX ) {
			return atan2( fY, fX );
		}

		//! ceiling
		static float Ceil( float fValue ) {
			return ceil( fValue );
		}
		//! floor
		static float Floor( float fValue ) {
			return floor( fValue );
		}

		//! exponential
		static float Exp( float fValue ) {
			return exp( fValue );
		}
		//! absolute value of floating-point
		static float FAbs( float fValue ) {
			return fabs( fValue );
		}

		//! floating point modular division
		static float FMod( float fX, float fY ) {
			return fmod( fX, fY );
		}

		//! natural logarithm
		static float Log( float fValue ) {
			return log( fValue );
		}
		//! numeric power
		static float Pow( float fBase, float fExponent ) {
			return pow( fBase, fExponent );
		}

		//! square
		static float Sqr( float fValue ) {
			return fValue * fValue;
		}
		//! square root
		static float Sqrt( float fValue ) {
			return sqrt( fValue );
		}
		//! inverse square root
		static float InvSqrt( float fValue ) {
			return 1.0f / sqrt( fValue );
		}

		//! Returns the angle from the origin to the given point, in float radians
		static float AngleOfPoint( float x, float y ) {
			return ATan2( y, x );
		}


	private:
		static const float POS_INFINITY;
		static const float NEG_INFINITY;
		static const float PI; //!< value for Pi
		static const float TWO_PI; //!< value for 2 * Pi
		static const float HALF_PI; //!< value for Pi / 2
		static const float fDeg2Rad;
		static const float fRad2Deg;
	};

}//namespace OpenGUI{
#endif // C1299AA7_4E0D_4E2D_88C1_4E8F5F79C438

