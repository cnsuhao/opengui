#include "OpenGUI_Types.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	//#####################################################################
	Enum::Enum() {
		mSelected = "";
	}
	//#####################################################################
	Enum::~Enum() {}

	//#####################################################################
	void Enum::addValue( std::string value ) {
		if ( value.length() == 0 ) {
			OG_THROW( Exception::ERR_INVALIDPARAMS, "cannot add an empty value", "Enum::addValue" );
		}

		//make it lower case first
		std::transform( value.begin(), value.end(), value.begin(), static_cast < int( * )( int ) > ( std::tolower ) );

		if ( !testValue( value ) )
			mEnumList.insert( value );
	}
	//#####################################################################
	void Enum::setValue( std::string value ) {
		//make it lower case first
		std::transform( value.begin(), value.end(), value.begin(), static_cast < int( * )( int ) > ( std::tolower ) );

		if ( !testValue( value ) ) {
			OG_THROW( Exception::ERR_INVALIDPARAMS, "[value] is not in the list of valid selections", "Enum::setValue" );
		} else {
			mSelected = value;
		}
	}
	//#####################################################################
	void Enum::setValue( const  char* value ) {
		std::string tmp = value;
		setValue( tmp );
	}
	//#####################################################################
	std::string Enum::getValue() {
		return mSelected;
	}
	//#####################################################################
	bool Enum::testValue( std::string value ) {
		//make it lower case first
		std::transform( value.begin(), value.end(), value.begin(), static_cast < int( * )( int ) > ( std::tolower ) );

		if ( mEnumList.find( value ) != mEnumList.end() )
			return true;
		return false;
	}
	//#####################################################################
	Enum_TextAligntment_H::Enum_TextAligntment_H() {
		addValue( "ALIGN_LEFT" );
		addValue( "ALIGN_RIGHT" );
		addValue( "ALIGN_CENTER" );
		addValue( "ALIGN_JUSTIFIED" );
	}
	//#####################################################################
	Enum_TextAligntment_V::Enum_TextAligntment_V() {
		addValue( "ALIGN_TOP" );
		addValue( "ALIGN_BOTTOM" );
		addValue( "ALIGN_CENTER" );
		addValue( "ALIGN_JUSTIFIED" );
	}
	//#####################################################################
	void Enum_TextAligntment_base::setValue( TextAlignment alignmentObj ) {
		setValue( alignmentObj.value ); //pass through to more specific handler
	}
	//#####################################################################
	//Implemented here because ALIGN_LEFT==ALIGN_TOP and ALIGN_RIGHT == ALIGN_BOTTOM
	void Enum_TextAligntment_V::setValue( TextAlignment::Alignment alignment ) {
		/*
		need to call by Enum::setValue(), since MSVC can't seem to tell 
		the difference between const char* and TextAlignment::Alignment
		*/
		switch ( alignment ) {
		case TextAlignment::ALIGN_TOP:
			Enum::setValue( "ALIGN_TOP" );
			break;
		case TextAlignment::ALIGN_BOTTOM:
			Enum::setValue( "ALIGN_BOTTOM" );
			break;
		case TextAlignment::ALIGN_CENTER:
			Enum::setValue( "ALIGN_CENTER" );
			break;
		case TextAlignment::ALIGN_JUSTIFIED:
			Enum::setValue( "ALIGN_JUSTIFIED" );
			break;
		}
	}
	//#####################################################################
	//Implemented here because ALIGN_LEFT==ALIGN_TOP and ALIGN_RIGHT == ALIGN_BOTTOM
	void Enum_TextAligntment_H::setValue( TextAlignment::Alignment alignment ) {
		/*
		need to call by Enum::setValue(), since MSVC can't seem to tell 
		the difference between const char* and TextAlignment::Alignment
		*/
		switch ( alignment ) {
		case TextAlignment::ALIGN_LEFT:
			Enum::setValue( "ALIGN_LEFT" );
			break;
		case TextAlignment::ALIGN_RIGHT:
			Enum::setValue( "ALIGN_RIGHT" );
			break;
		case TextAlignment::ALIGN_CENTER:
			Enum::setValue( "ALIGN_CENTER" );
			break;
		case TextAlignment::ALIGN_JUSTIFIED:
			Enum::setValue( "ALIGN_JUSTIFIED" );
			break;
		}
	}
	//#####################################################################
	TextAlignment Enum_TextAligntment_base::getTextAlignment() {
		std::string tmp = getValue();
		TextAlignment ret;

		if ( tmp == "align_top" )
			ret = TextAlignment::ALIGN_TOP;
		else if ( tmp == "align_bottom" )
			ret = TextAlignment::ALIGN_BOTTOM;
		else if ( tmp == "align_center" )
			ret = TextAlignment::ALIGN_CENTER;
		else if ( tmp == "align_justified" )
			ret = TextAlignment::ALIGN_JUSTIFIED;
		else if ( tmp == "align_left" )
			ret = TextAlignment::ALIGN_LEFT;
		else if ( tmp == "align_right" )
			ret = TextAlignment::ALIGN_RIGHT;
		else
			OG_THROW( Exception::ERR_INTERNAL_ERROR,
					  "Current Enum value is not a valid TextAlignment",
					  "Enum_TextAligntment_base::getTextAlignment" );

		return ret;
	}
	//#####################################################################
}//namespace OpenGUI {
