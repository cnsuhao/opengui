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

