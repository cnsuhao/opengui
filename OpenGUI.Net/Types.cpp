// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "Stdafx.h"
#include "Types.h"

using namespace System;
namespace OpenGUI_Net {
	//############################################################################
	Radian::Radian() {
		mValue = 0.0f;
	}
	//############################################################################
	Radian::Radian( float radian_value ) {
		mValue = radian_value;
	}
	//############################################################################
	Radian ^ Radian::operator = ( const Radian ^ right ) {
		mValue = right->mValue;
		return this;
	}
	//############################################################################
	Radian ^ Radian::operator + ( const Radian ^ right ) {
		return gcnew Radian( mValue + right->mValue );
	}
	//############################################################################
	Radian ^ Radian::operator += ( const Radian ^ right ) {
		mValue += right->mValue;
		return this;
	}
	//############################################################################
	Radian ^ Radian::operator - () {
		return gcnew Radian( -mValue );
	}
	//############################################################################
	Radian ^ Radian::operator - ( const Radian ^ right ) {
		return gcnew Radian( mValue - right->mValue );
	}
	//############################################################################
	Radian ^ Radian::operator -= ( const Radian ^ right ) {
		mValue -= right->mValue;
		return this;
	}
	//############################################################################
	bool Radian::operator == ( const Radian ^ right ) {
		return mValue == right->mValue;
	}
	//############################################################################
	bool Radian::operator != ( const Radian ^ right ) {
		return mValue != right->mValue;
	}
	//############################################################################
	bool Radian::operator < ( const Radian ^ right ) {
		return mValue <  right->mValue;
	}
	//############################################################################
	bool Radian::operator <= ( const Radian ^ right ) {
		return mValue <= right->mValue;
	}
	//############################################################################
	bool Radian::operator > ( const Radian ^ right ) {
		return mValue >  right->mValue;
	}
	//############################################################################
	bool Radian::operator >= ( const Radian ^ right ) {
		return mValue >= right->mValue;
	}
	//############################################################################
	Degree ^ Radian::toDegree() {
		return gcnew Degree( OpenGUI::Math::RadiansToDegrees( mValue ) );
	}
	//############################################################################
//############################################################################
	//############################################################################
	Degree::Degree() {
		mValue = 0.0f;
	}
	//############################################################################
	Degree::Degree( float degree_value ) {
		mValue = degree_value;
	}
	//############################################################################
	Degree ^ Degree::operator = ( const Degree ^ right ) {
		mValue = right->mValue;
		return this;
	}
	//############################################################################
	Degree ^ Degree::operator + ( const Degree ^ right ) {
		return gcnew Degree( mValue + right->mValue );
	}
	//############################################################################
	Degree ^ Degree::operator += ( const Degree ^ right ) {
		mValue += right->mValue;
		return this;
	}
	//############################################################################
	Degree ^ Degree::operator - () {
		return gcnew Degree( -mValue );
	}
	//############################################################################
	Degree ^ Degree::operator - ( const Degree ^ right ) {
		return gcnew Degree( mValue - right->mValue );
	}
	//############################################################################
	Degree ^ Degree::operator -= ( const Degree ^ right ) {
		mValue -= right->mValue;
		return this;
	}
	//############################################################################
	bool Degree::operator == ( const Degree ^ right ) {
		return mValue == right->mValue;
	}
	//############################################################################
	bool Degree::operator != ( const Degree ^ right ) {
		return mValue != right->mValue;
	}
	//############################################################################
	bool Degree::operator < ( const Degree ^ right ) {
		return mValue <  right->mValue;
	}
	//############################################################################
	bool Degree::operator <= ( const Degree ^ right ) {
		return mValue <= right->mValue;
	}
	//############################################################################
	bool Degree::operator > ( const Degree ^ right ) {
		return mValue >  right->mValue;
	}
	//############################################################################
	bool Degree::operator >= ( const Degree ^ right ) {
		return mValue >= right->mValue;
	}
	//############################################################################
	Radian ^ Degree::toRadian() {
		return gcnew Radian( OpenGUI::Math::DegreesToRadians( mValue ) );
	}
	//############################################################################
} // namespace OpenGUINet {