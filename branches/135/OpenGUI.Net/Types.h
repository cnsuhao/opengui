// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Types_h__
#define Types_h__

using namespace System;

namespace OpenGUI_Net {
	value class Degree; // forward declaration
	value class Radian; // forward declaration

	public value class Radian {
	public:
		void setDegrees( float degree_value );
		static Radian operator + ( Radian left, Radian right );
		static Radian operator - ( Radian right );
		static Radian operator - ( Radian left, Radian right );
		static bool operator == ( Radian left, Radian right );
		static bool operator != ( Radian left, Radian right );
		static bool operator < ( Radian left, Radian right );
		static bool operator <= ( Radian left, Radian right );
		static bool operator > ( Radian left, Radian right );
		static bool operator >= ( Radian left, Radian right );
		Degree toDegree();
		float fValue;
	};
	//############################################################################
	public value class Degree {
	public:
		void setRadians( float radian_value );
		static Degree operator + ( Degree left, Degree right );
		static Degree operator - ( Degree right );
		static Degree operator - ( Degree left, Degree right );
		static bool operator == ( Degree left, Degree right );
		static bool operator != ( Degree left, Degree right );
		static bool operator < ( Degree left, Degree right );
		static bool operator <= ( Degree left, Degree right );
		static bool operator > ( Degree left, Degree right );
		static bool operator >= ( Degree left, Degree right );
		Radian toRadian();
		float fValue;
	};
	//############################################################################
	public value class IVector2 {
	public:
		static IVector2 operator+( IVector2 left, IVector2 right ) {
			IVector2 out;
			out.x = left.x + right.x;
			out.y = left.y + right.y;
			return out;
		}
		//////////////////////////////////////////////////////////////////////////
		static IVector2 operator-( IVector2 left, IVector2 right ) {
			IVector2 out;
			out.x = left.x - right.x;
			out.y = left.y - right.y;
			return out;
		}
		//////////////////////////////////////////////////////////////////////////
		static IVector2 operator*( IVector2 left, IVector2 right ) {
			IVector2 out;
			out.x = left.x * right.x;
			out.y = left.y * right.y;
			return out;
		}
		//////////////////////////////////////////////////////////////////////////
		static IVector2 operator/( IVector2 left, IVector2 right ) {
			IVector2 out;
			out.x = left.x / right.x;
			out.y = left.y / right.y;
			return out;
		}
		//////////////////////////////////////////////////////////////////////////
		static bool operator==( IVector2 left, IVector2 right ) {
			return left.x == right.x && left.y == right.y;
		}
		//////////////////////////////////////////////////////////////////////////
		static bool operator!=( IVector2 left, IVector2 right ) {
			return !operator==( left, right );
		}
		//////////////////////////////////////////////////////////////////////////
		static IVector2 operator - ( IVector2 right ) {
			IVector2 out;
			out.x = -right.x;
			out.y = -right.y;
			return out;
		}
		//////////////////////////////////////////////////////////////////////////
		String ^ toStr();
		//////////////////////////////////////////////////////////////////////////
		int x;
		int y;
	};
	//############################################################################
	public value class FVector2 {
	public:
		static FVector2 operator+( FVector2 left, FVector2 right ) {
			FVector2 out;
			out.x = left.x + right.x;
			out.y = left.y + right.y;
			return out;
		}
		//////////////////////////////////////////////////////////////////////////
		static FVector2 operator-( FVector2 left, FVector2 right ) {
			FVector2 out;
			out.x = left.x - right.x;
			out.y = left.y - right.y;
			return out;
		}
		//////////////////////////////////////////////////////////////////////////
		static FVector2 operator*( FVector2 left, FVector2 right ) {
			FVector2 out;
			out.x = left.x * right.x;
			out.y = left.y * right.y;
			return out;
		}
		//////////////////////////////////////////////////////////////////////////
		static FVector2 operator/( FVector2 left, FVector2 right ) {
			FVector2 out;
			out.x = left.x / right.x;
			out.y = left.y / right.y;
			return out;
		}
		//////////////////////////////////////////////////////////////////////////
		static bool operator==( FVector2 left, FVector2 right ) {
			return left.x == right.x && left.y == right.y;
		}
		//////////////////////////////////////////////////////////////////////////
		static bool operator!=( FVector2 left, FVector2 right ) {
			return !operator==( left, right );
		}
		//////////////////////////////////////////////////////////////////////////
		static FVector2 operator - ( FVector2 right ) {
			FVector2 out;
			out.x = -right.x;
			out.y = -right.y;
			return out;
		}
		//////////////////////////////////////////////////////////////////////////
		FVector2 pixelAligned( IVector2 resolution ) {
			FVector2 tmpF;
			IVector2 tmpI;
			tmpI.x = ( int )( x * ( float )resolution.x );
			tmpI.y = ( int )( y * ( float )resolution.y );
			tmpF.x = (( float )tmpI.x ) / ( float )resolution.x;
			tmpF.y = (( float )tmpI.y ) / ( float )resolution.y;
			return tmpF;
		}
		//////////////////////////////////////////////////////////////////////////
		float length() {
			return sqrt(( x*x ) + ( y*y ) );
		}
		//////////////////////////////////////////////////////////////////////////
		FVector2 normalize() {
			float l = length();
			FVector2 out;
			out.x = x / l;
			out.y = y / l;
			return out;
		}
		//////////////////////////////////////////////////////////////////////////
		String ^ toStr();
		//////////////////////////////////////////////////////////////////////////
		float x;
		float y;
	};
	//############################################################################
	public value class IRect {
	public:
		IVector2 getPosition() {
			return min;
		}
		//////////////////////////////////////////////////////////////////////////
		IVector2 getSize() {
			return max - min;
		}
		//////////////////////////////////////////////////////////////////////////
		int getWidth() {
			return max.x - min.x;
		}
		//////////////////////////////////////////////////////////////////////////
		int getHeight() {
			return max.y - min.y;
		}
		//////////////////////////////////////////////////////////////////////////
		int getArea() {
			return getWidth() * getHeight();
		}
		//////////////////////////////////////////////////////////////////////////
		void setWidth( int newWidth ) {
			max.x = min.x + newWidth;
		}
		//////////////////////////////////////////////////////////////////////////
		void setHeight( int newHeight ) {
			max.y = min.y + newHeight;
		}
		//////////////////////////////////////////////////////////////////////////
		void setSize( IVector2 newSize ) {
			max = min + newSize;
		}
		//////////////////////////////////////////////////////////////////////////
		void setPosition( IVector2 newPosition ) {
			IVector2 tmpSize = max - min;
			min = newPosition;
			max = min + tmpSize;
		}
		//////////////////////////////////////////////////////////////////////////
		void offset( IVector2 offsetVector ) {
			min = min + offsetVector;
			max = max + offsetVector;
		}
		//////////////////////////////////////////////////////////////////////////
		bool inside( IVector2 point ) {
			if (	point.x >= min.x && point.x < max.x &&
					point.y >= min.y && point.y < max.y )
				return true;
			return false;
		}
		//////////////////////////////////////////////////////////////////////////
		static bool operator==( IRect left, IRect right ) {
			return left.min == right.min && left.max == right.max;
		}
		//////////////////////////////////////////////////////////////////////////
		static bool operator!=( IRect left, IRect right ) {
			return !operator==( left, right );
		}
		//////////////////////////////////////////////////////////////////////////
		String ^ toStr();
		//////////////////////////////////////////////////////////////////////////
		IVector2 min;
		IVector2 max;
	};
	//############################################################################
	public value class FRect {
	public:
		FVector2 getPosition() {
			return min;
		}
		//////////////////////////////////////////////////////////////////////////
		FVector2 getSize() {
			return max - min;
		}
		//////////////////////////////////////////////////////////////////////////
		float getWidth() {
			return max.x - min.x;
		}
		//////////////////////////////////////////////////////////////////////////
		float getHeight() {
			return max.y - min.y;
		}
		//////////////////////////////////////////////////////////////////////////
		float getArea() {
			return getWidth() * getHeight();
		}
		//////////////////////////////////////////////////////////////////////////
		void setWidth( float newWidth ) {
			max.x = min.x + newWidth;
		}
		//////////////////////////////////////////////////////////////////////////
		void setHeight( float newHeight ) {
			max.y = min.y + newHeight;
		}
		//////////////////////////////////////////////////////////////////////////
		void setSize( FVector2 newSize ) {
			max = min + newSize;
		}
		//////////////////////////////////////////////////////////////////////////
		void setPosition( FVector2 newPosition ) {
			FVector2 tmpSize = max - min;
			min = newPosition;
			max = min + tmpSize;
		}
		//////////////////////////////////////////////////////////////////////////
		void offset( FVector2 offsetVector ) {
			min = min + offsetVector;
			max = max + offsetVector;
		}
		//////////////////////////////////////////////////////////////////////////
		bool inside( FVector2 point ) {
			if (	point.x >= min.x && point.x < max.x &&
					point.y >= min.y && point.y < max.y )
				return true;
			return false;
		}
		//////////////////////////////////////////////////////////////////////////
		void normalize() {
			float tmp;
			if ( min.x > max.x ) {
				tmp = min.x;
				min.x = max.x;
				max.x = tmp;
			}
			if ( min.y > max.y ) {
				tmp = min.y;
				min.y = max.y;
				max.y = tmp;
			}
		}
		//////////////////////////////////////////////////////////////////////////
		bool isInside( FVector2 point ) {
			if ( point.x >= min.x && point.x < max.x && point.y >= min.y && point.y < max.y )
				return true;
			return false;
		}
		//////////////////////////////////////////////////////////////////////////
		FVector2 getInnerCoord( FVector2 outerFVector2 ) {
			FVector2 out;
			out.x = ( outerFVector2.x - min.x ) / getWidth();
			out.y = ( outerFVector2.y - min.y ) / getHeight();
			return out;
		}
		//////////////////////////////////////////////////////////////////////////
		FVector2 getOuterCoord( const FVector2& innerFVector2 ) {
			FVector2 out;
			out.x = (( innerFVector2.x * getWidth() ) + min.x );
			out.y = (( innerFVector2.y * getHeight() ) + min.y );
			return out;
		}
		//////////////////////////////////////////////////////////////////////////
		FRect pixelAligned( IVector2 resolution ) {
			FRect out;
			out.min = min.pixelAligned( resolution );
			out.max = max.pixelAligned( resolution );
			return out;
		}
		//////////////////////////////////////////////////////////////////////////
		static bool operator==( FRect left, FRect right ) {
			return left.min == right.min && left.max == right.max;
		}
		//////////////////////////////////////////////////////////////////////////
		static bool operator!=( FRect left, FRect right ) {
			return !operator==( left, right );
		}
		//////////////////////////////////////////////////////////////////////////
		String ^ toStr();
		//////////////////////////////////////////////////////////////////////////
		FVector2 min;
		FVector2 max;
	};
	//############################################################################
	public value class TextAlignment {
	public:
		enum class Alignment {
			LEFT = 0,
				   TOP = 0,
						 RIGHT = 1,
								 BOTTOM = 1,
										  CENTER = 2,
												   JUSTIFIED = 3
														   };
		Alignment horizontal;
		Alignment vertical;
	};
	//############################################################################
	public value class Color {
	public:
		float Red;
		float Green;
		float Blue;
		float Alpha;
		//////////////////////////////////////////////////////////////////////////
		void clamp() {
			if ( Red < 0.0f ) Red = 0.0f;
			if ( Red > 1.0f ) Red = 1.0f;
			if ( Green < 0.0f ) Green = 0.0f;
			if ( Green > 1.0f ) Green = 1.0f;
			if ( Blue < 0.0f ) Blue = 0.0f;
			if ( Blue > 1.0f ) Blue = 1.0f;
			if ( Alpha < 0.0f ) Alpha = 0.0f;
			if ( Alpha > 1.0f ) Alpha = 1.0f;
		}
		//////////////////////////////////////////////////////////////////////////
		void normalize() {
			float min = 0.0f, max;
			min = Red;
			if ( Green < min ) min = Green;
			if ( Blue < min ) min = Blue;
			if ( Alpha < min ) min = Alpha;
			Red -= min;
			Green -= min;
			Blue -= min;
			Alpha -= min;
			max = Red;
			if ( Green > max ) max = Green;
			if ( Blue > max ) max = Blue;
			if ( Alpha > max ) max = Alpha;
			Red /= max;
			Green /= max;
			Blue /= max;
			Alpha /= max;
			clamp(); //we need to clamp in case we just performed a divide by zero
		}
		//////////////////////////////////////////////////////////////////////////
		static bool operator==( Color left, Color right ) {
			return ( left.Red == right.Red
					 && left.Green == right.Green
					 && left.Blue == right.Blue
					 && left.Alpha == right.Alpha );
		}
		//////////////////////////////////////////////////////////////////////////
		static bool operator!=( Color left, Color right ) {
			return !operator==( left, right );
		}
		//////////////////////////////////////////////////////////////////////////
		static Color PresetRed() {
			Color out;
			out.Red = 1.0f;
			out.Green = 0.0f;
			out.Blue = 0.0f;
			out.Alpha = 1.0f;
			return out;
		}
		//////////////////////////////////////////////////////////////////////////
		static Color PresetGreen() {
			Color out;
			out.Red = 0.0f;
			out.Green = 1.0f;
			out.Blue = 0.0f;
			out.Alpha = 1.0f;
			return out;
		}
		//////////////////////////////////////////////////////////////////////////
		static Color PresetBlue() {
			Color out;
			out.Red = 0.0f;
			out.Green = 0.0f;
			out.Blue = 1.0f;
			out.Alpha = 1.0f;
			return out;
		}
		//////////////////////////////////////////////////////////////////////////
		static Color PresetWhite() {
			Color out;
			out.Red = 1.0f;
			out.Green = 1.0f;
			out.Blue = 1.0f;
			out.Alpha = 1.0f;
			return out;
		}
		//////////////////////////////////////////////////////////////////////////
		static Color PresetBlack() {
			Color out;
			out.Red = 0.0f;
			out.Green = 0.0f;
			out.Blue = 0.0f;
			out.Alpha = 1.0f;
			return out;
		}
		//////////////////////////////////////////////////////////////////////////
	};
} // namespace OpenGUINet {

#endif // Types_h__
