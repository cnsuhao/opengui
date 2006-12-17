// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "Stdafx.h"
#include "Types.h"

using namespace System;
namespace OpenGUI_Net {
	//############################################################################
	void Radian::setDegrees(float degree_value){
		fValue = OpenGUI::Math::DegreesToRadians(degree_value);
	}
	//############################################################################
	Radian Radian::operator + ( Radian left, Radian right ) {
		Radian out;
		out.fValue = left.fValue + right.fValue;
		return out;
	}
	//############################################################################
	Radian Radian::operator - ( Radian right ) {
		Radian out;
		out.fValue = -right.fValue;
		return out;
	}
	//############################################################################
	Radian Radian::operator - ( Radian left, Radian right ){
		Radian out;
		out.fValue = left.fValue - right.fValue;
		return out;
	}
	//############################################################################
	bool Radian::operator == ( Radian left, Radian right ){
		return left.fValue == right.fValue;
	}
	//############################################################################
	bool Radian::operator != ( Radian left, Radian right ){
		return left.fValue != right.fValue;
	}
	//############################################################################
	bool Radian::operator < ( Radian left, Radian right ){
		return left.fValue < right.fValue;
	}
	//############################################################################
	bool Radian::operator <= ( Radian left, Radian right ){
		return left.fValue <= right.fValue;
	}
	//############################################################################
	bool Radian::operator > ( Radian left, Radian right ){
		return left.fValue > right.fValue;
	}
	//############################################################################
	bool Radian::operator >= ( Radian left, Radian right ){
		return left.fValue >= right.fValue;
	}
	//############################################################################
	Degree Radian::toDegree(){
		Degree out;
		out.setRadians(fValue);
		return out;
	}
	//############################################################################
	//////////////////////////////////////////////////////////////////////////
	//############################################################################
	void Degree::setRadians(float radian_value){
		fValue = OpenGUI::Math::RadiansToDegrees(radian_value);
	}
	//############################################################################
	Degree Degree::operator + ( Degree left, Degree right ) {
		Degree out;
		out.fValue = left.fValue + right.fValue;
		return out;
	}
	//############################################################################
	Degree Degree::operator - ( Degree right ) {
		Degree out;
		out.fValue = -right.fValue;
		return out;
	}
	//############################################################################
	Degree Degree::operator - ( Degree left, Degree right ){
		Degree out;
		out.fValue = left.fValue - right.fValue;
		return out;
	}
	//############################################################################
	bool Degree::operator == ( Degree left, Degree right ){
		return left.fValue == right.fValue;
	}
	//############################################################################
	bool Degree::operator != ( Degree left, Degree right ){
		return left.fValue != right.fValue;
	}
	//############################################################################
	bool Degree::operator < ( Degree left, Degree right ){
		return left.fValue < right.fValue;
	}
	//############################################################################
	bool Degree::operator <= ( Degree left, Degree right ){
		return left.fValue <= right.fValue;
	}
	//############################################################################
	bool Degree::operator > ( Degree left, Degree right ){
		return left.fValue > right.fValue;
	}
	//############################################################################
	bool Degree::operator >= ( Degree left, Degree right ){
		return left.fValue >= right.fValue;
	}
	//############################################################################
	Radian Degree::toRadian(){
		Radian out;
		out.setDegrees(fValue);
		return out;
	}
	//############################################################################
	//////////////////////////////////////////////////////////////////////////
	//############################################################################
	String ^ IVector2::toStr() {
		OpenGUI::IVector2 iv2;
		iv2 = Marshal::IVECTOR2( *this );
		std::string cstr;
		OpenGUI::StrConv::fromIVector2( iv2, cstr );
		String ^ ret = Marshal::STRING( cstr );
		return ret;
	}
	//############################################################################
	//////////////////////////////////////////////////////////////////////////
	//############################################################################
	String ^ FVector2::toStr() {
		OpenGUI::FVector2 fv2;
		fv2 = Marshal::FVECTOR2( *this );
		std::string cstr;
		OpenGUI::StrConv::fromFVector2( fv2, cstr );
		String ^ ret = Marshal::STRING( cstr );
		return ret;
	}
	//############################################################################
	//////////////////////////////////////////////////////////////////////////
	//############################################################################
	String ^ IRect::toStr() {
		OpenGUI::IRect ir;
		ir = Marshal::IRECT( *this );
		std::string cstr;
		OpenGUI::StrConv::fromIRect( ir, cstr );
		String ^ ret = Marshal::STRING( cstr );
		return ret;
	}
	//############################################################################
	//////////////////////////////////////////////////////////////////////////
	//############################################################################
	String ^ FRect::toStr() {
		OpenGUI::FRect fr;
		fr = Marshal::FRECT( *this );
		std::string cstr;
		OpenGUI::StrConv::fromFRect( fr, cstr );
		String ^ ret = Marshal::STRING( cstr );
		return ret;
	}
	//############################################################################
} // namespace OpenGUINet {