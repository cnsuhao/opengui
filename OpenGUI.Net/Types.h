// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Types_h__
#define Types_h__

using namespace System;

namespace OpenGUI_Net {
	ref class Degree;

	public ref class Radian {
	public:
		Radian();
		Radian( float radian_value );
		Radian ^ operator = ( const Radian ^ right );
		Radian ^ operator + ( const Radian ^ right );
		Radian ^ operator += ( const Radian ^ right );
		Radian ^ operator - ();
		Radian ^ operator - ( const Radian ^ right );
		Radian ^ operator -= ( const Radian ^ right );
		bool operator == ( const Radian ^ right );
		bool operator != ( const Radian ^ right );
		bool operator < ( const Radian ^ right );
		bool operator <= ( const Radian ^ right );
		bool operator > ( const Radian ^ right );
		bool operator >= ( const Radian ^ right );
		Degree ^ toDegree();
	private:
		float mValue;
	};
	//############################################################################
	public ref class Degree {
	public:
		Degree();
		Degree( float degree_value );
		Degree ^ operator = ( const Degree ^ right );
		Degree ^ operator + ( const Degree ^ right );
		Degree ^ operator += ( const Degree ^ right );
		Degree ^ operator - ();
		Degree ^ operator - ( const Degree ^ right );
		Degree ^ operator -= ( const Degree ^ right );
		bool operator == ( const Degree ^ right );
		bool operator != ( const Degree ^ right );
		bool operator < ( const Degree ^ right );
		bool operator <= ( const Degree ^ right );
		bool operator > ( const Degree ^ right );
		bool operator >= ( const Degree ^ right );
		Radian ^ toRadian();
	private:
		float mValue;
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
		String ^ toStr();
		//////////////////////////////////////////////////////////////////////////
		float x;
		float y;
	};
} // namespace OpenGUINet {

#endif // Types_h__
