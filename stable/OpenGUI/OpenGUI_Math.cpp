#include "OpenGUI_Math.h"
#include <limits>
namespace OpenGUI {

	const float Math::POS_INFINITY = std::numeric_limits<float>::infinity();
	const float Math::NEG_INFINITY = -std::numeric_limits<float>::infinity();
	const float Math::PI = float( 4.0 * atan( 1.0 ) );
	const float Math::TWO_PI = float( 2.0 * Math::PI );
	const float Math::HALF_PI = float( 0.5 * Math::PI );
	const float Math::fDeg2Rad = Math::PI / float( 180.0 );
	const float Math::fRad2Deg = float( 180.0 ) / Math::PI;

}//namespace OpenGUI{
