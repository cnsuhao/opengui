#include "OpenGUI_StrConv.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	//######################################################################
	void _strTrim( std::string& str ) {
		std::string::size_type pos = str.find_last_not_of( ' ' );
		if ( pos != std::string::npos ) {
			str.erase( pos + 1 );
			pos = str.find_first_not_of( ' ' );
			if ( pos != std::string::npos ) str.erase( 0, pos );
		} else str.erase( str.begin(), str.end() );
	}
	//############################################################################
	void StrConv::toInt( const std::string& in, int& out ) {
		std::string tmp = in;
		_strTrim( tmp );
		std::istringstream iss;
		iss.exceptions( std::ios_base::failbit | std::ios_base::badbit );
		iss.str( tmp );
		iss >> out;
	}
	//############################################################################
	void StrConv::toUInt( const std::string& in, unsigned int& out ) {
		std::string tmp = in;
		_strTrim( tmp );
		std::istringstream iss;
		iss.exceptions( std::ios_base::failbit | std::ios_base::badbit );
		iss.str( tmp );
		iss >> out;
	}
	//############################################################################
	void StrConv::fromInt( int in, std::string& out ) {
		std::stringstream ss;
		ss << in;
		out = ss.str();
	}
	//############################################################################
	void StrConv::fromUInt( unsigned int in, std::string& out ) {
		std::stringstream ss;
		ss << in;
		out = ss.str();
	}
	//############################################################################
	void StrConv::toFloat( const std::string& in, float& out ) {
		std::string tmp = in;
		_strTrim( tmp );
		std::istringstream iss;
		iss.exceptions( std::ios_base::failbit | std::ios_base::badbit );
		iss.str( tmp );
		iss >> out;
	}
	//############################################################################
	void StrConv::fromFloat( float in, std::string& out ) {
		std::stringstream ss;
		ss << in;
		out = ss.str();
	}
	//############################################################################

	void StrConv::fromIVector2( const IVector2& in, std::string& out ) {
		std::stringstream ss;
		ss << "( " << in.x << " x " << in.y << " )" ;
		out = ss.str();
	}
	//############################################################################
	void StrConv::toIVector2( const std::string& in, IVector2& out ) {
		std::string tmp = in;
		_strTrim( tmp );
		if ( tmp.substr( 0, 1 ) != "(" )
			OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );
		tmp = tmp.substr( 1 );
		if ( tmp.substr( tmp.length() - 1, 1 ) != ")" )
			OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );
		tmp = tmp.substr( 0, tmp.length() - 1 );

		std::string::size_type tokenPos = tmp.find( "x" );
		if ( tokenPos == std::string::npos )
			OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );
		std::string xHalf = tmp.substr( 0, tokenPos );
		std::string yHalf = tmp.substr( tokenPos + 1, std::string::npos );

		try {
			toInt( xHalf, out.x );
			toInt( yHalf, out.y );
		} catch ( ... ) {
			//throw a more meaningful exception
			OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );
		}
	}
	//############################################################################
	void StrConv::fromIRect( const IRect& in, std::string& out ) {
		std::stringstream ss;
		std::string min, max;
		fromIVector2( in.min, min );
		fromIVector2( in.max, max );
		ss << "{ " << min << " X " << max << " }";
		out = ss.str();
	}
	//############################################################################
	void StrConv::toIRect( const std::string& in, IRect& out ) {
		std::string tmp = in;
		_strTrim( tmp );
		if ( tmp.substr( 0, 1 ) != "{" )
			OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );
		tmp = tmp.substr( 1 );
		if ( tmp.substr( tmp.length() - 1, 1 ) != "}" )
			OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );
		tmp = tmp.substr( 0, tmp.length() - 1 );

		std::string::size_type tokenPos = tmp.find( "X" );
		if ( tokenPos == std::string::npos )
			OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );
		std::string minHalf = tmp.substr( 0, tokenPos );
		std::string maxHalf = tmp.substr( tokenPos + 1, std::string::npos );

		toIVector2( minHalf, out.min );
		toIVector2( maxHalf, out.max );
	}
	//############################################################################
	void StrConv::fromFVector2( const FVector2& in, std::string& out ) {
		std::stringstream ss;
		ss << "( " << in.x << " x " << in.y << " )";
		out = ss.str();
	}
	//############################################################################
	void StrConv::toFVector2( const std::string& in, FVector2& out ) {
		std::string tmp = in;
		_strTrim( tmp );
		if ( tmp.substr( 0, 1 ) != "(" )
			OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );
		tmp = tmp.substr( 1 );
		if ( tmp.substr( tmp.length() - 1, 1 ) != ")" )
			OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );
		tmp = tmp.substr( 0, tmp.length() - 1 );

		std::string::size_type tokenPos = tmp.find( "x" );
		if ( tokenPos == std::string::npos )
			OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );
		std::string xHalf = tmp.substr( 0, tokenPos );
		std::string yHalf = tmp.substr( tokenPos + 1, std::string::npos );

		try {
			toFloat( xHalf, out.x );
			toFloat( yHalf, out.y );
		} catch ( ... ) {
			//throw a more meaningful exception
			OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );
		}
	}
	//############################################################################
	void StrConv::fromFRect( const FRect& in, std::string& out ) {
		std::stringstream ss;
		std::string min, max;
		fromFVector2( in.min, min );
		fromFVector2( in.max, max );
		ss << "{ " << min << " X " << max << " }";
		out = ss.str();
	}
	//############################################################################
	void StrConv::toFRect( const std::string& in, FRect& out ) {
		std::string tmp = in;
		_strTrim( tmp );
		if ( tmp.substr( 0, 1 ) != "{" )
			OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );
		tmp = tmp.substr( 1 );
		if ( tmp.substr( tmp.length() - 1, 1 ) != "}" )
			OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );
		tmp = tmp.substr( 0, tmp.length() - 1 );

		std::string::size_type tokenPos = tmp.find( "X" );
		if ( tokenPos == std::string::npos )
			OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );
		std::string minHalf = tmp.substr( 0, tokenPos );
		std::string maxHalf = tmp.substr( tokenPos + 1, std::string::npos );

		toFVector2( minHalf, out.min );
		toFVector2( maxHalf, out.max );
	}
	//############################################################################
}
