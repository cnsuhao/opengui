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
} // namespace OpenGUINet {

#endif // Types_h__
