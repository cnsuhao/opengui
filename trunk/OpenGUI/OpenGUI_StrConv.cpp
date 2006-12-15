// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_StrConv.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Font.h"

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
	void _Tokenize( const std::string& inputStr, StringList& outputStrList, char token ) {
		std::string tmpStr;
		const char* cstr = inputStr.c_str();
		unsigned int epos, spos;
		spos = epos = 0;
		while ( cstr[epos] != 0 ) {
			if ( cstr[epos] == token ) {
				tmpStr = inputStr.substr( spos, epos - spos );
				outputStrList.push_back( tmpStr );
				spos = epos + 1;
			}
			epos++;
		}
		if ( spos != epos ) {
			tmpStr = inputStr.substr( spos, epos - spos );
			outputStrList.push_back( tmpStr );
		}
	}
	//############################################################################
	void StrConv::trim( std::string& str ) {
		_strTrim( str );
	}
	//############################################################################
	/*! The token is not included in the output strings. */
	void StrConv::tokenize( const std::string& inputStr, StringList& outputStrList, char token ) {
		_Tokenize( inputStr, outputStrList, token );
	}
	//############################################################################
	void StrConv::toLower( std::string& in_out ) {
		std::transform( in_out.begin(), in_out.end(), in_out.begin(), static_cast < int( * )( int ) > ( std::tolower ) );
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
	void StrConv::fromColor( const Color& in, std::string& out ) {
		std::stringstream ss;
		std::string r, g, b, a;
		fromFloat( in.Red, r );
		fromFloat( in.Green, g );
		fromFloat( in.Blue, b );
		fromFloat( in.Alpha, a );
		ss << r << ":" << g << ":" << b << ":" << a;
		out = ss.str();
	}
	//############################################################################
	void StrConv::toColor( const std::string& in, Color& out ) {
		std::string inCopy = in;
		trim( inCopy );

		// test for hex encoding
		if ( inCopy.length() > 0 && inCopy[0] == '#' ) {
			inCopy = inCopy.substr( 1 );
			// split on spaces, only a single contiguous string is valid
			StringList strList;
			_Tokenize( inCopy, strList, ' ' );
			if ( strList.size() != 1 ) // make sure we only came back with 1 result
				OG_THROW( Exception::OP_FAILED, "Color conversion failed: " + in, __FUNCTION__ );
			inCopy = strList.front();

			unsigned int dwordContaner = 0;
			std::istringstream iss;
			iss.exceptions( std::ios_base::failbit | std::ios_base::badbit );
			iss.str( inCopy );
			iss >> std::hex; // set hex input
			iss >> dwordContaner; // read whatever we have
			size_t shift = ( 8 - inCopy.length() ); // number of missing characters
			shift *= 4; // each character is 4 bits
			dwordContaner = dwordContaner << shift; // shift for each missing character


			unsigned char tmp;
			out = Color::PresetWhite(); // preset all values to 1.0 in case we do not reach them

			// red
			if ( inCopy.length() > 0 ) {
				tmp = ( dwordContaner >> 24 ) & 0xFF;
				out.Red = ( float )tmp / 255.0f;
			}

			// green
			if ( inCopy.length() > 2 ) {
				tmp = ( dwordContaner >> 16 ) & 0xFF;
				out.Green = ( float )tmp / 255.0f;
			}

			// blue
			if ( inCopy.length() > 4 ) {
				tmp = ( dwordContaner >> 8 ) & 0xFF;
				out.Blue = ( float )tmp / 255.0f;
			}

			// alpha
			if ( inCopy.length() > 6 ) {
				tmp = dwordContaner & 0xFF;
				out.Alpha = ( float )tmp / 255.0f;
			}

			// and we're done (yay)

		} else {
			StringList strList;
			_Tokenize( in, strList, ':' );
			int i = 0;
			StringList::iterator iter = strList.begin();
			while ( i < 4 && iter != strList.end() ) {
				if ( i == 0 )
					toFloat(( *iter ), out.Red );
				if ( i == 1 )
					toFloat(( *iter ), out.Green );
				if ( i == 2 )
					toFloat(( *iter ), out.Blue );
				if ( i == 3 )
					toFloat(( *iter ), out.Alpha );
				iter++;
				i++;
			}
			if ( i < 3 )
				OG_THROW( Exception::OP_FAILED, "Color conversion failed: " + in, __FUNCTION__ );
		}
	}
	//############################################################################
	void StrConv::fromBool( bool in, std::string& out ) {
		if ( in )
			out = "true";
		else
			out = "false";
	}
	//############################################################################
	void StrConv::toBool( const std::string& in, bool& out ) {
		std::string tmp = in;
		_strTrim( tmp );
		if ( tmp == "0" ) {
			out = false;
			return;
		}
		if ( tmp == "1" ) {
			out = true;
			return;
		}

		toLower( tmp );

		if ( tmp == "true" ) {
			out = true;
			return;
		}
		if ( tmp == "false" ) {
			out = false;
			return;
		}
		OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );
	}
	//############################################################################
	void StrConv::fromFont( Font& in, std::string& out ) {
		std::stringstream ss;
		ss << in.getName();
		ss << " @ ";
		ss << in.getSize();
		out = ss.str();
	}
	//############################################################################
	void StrConv::toFont( const std::string& in, Font& out ) {
		StringList slist;
		tokenize( in, slist, '@' );
		if ( slist.size() != 2 )
			OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );
		std::string name = slist.front();
		trim( name );
		float size;
		toFloat( slist.back(), size );
		out = Font( name, size );
	}
	//############################################################################
	void StrConv::fromTextAlignment( const TextAlignment& in, std::string& out ) {
		std::stringstream ss;
		switch ( in.getHorizontal() ) {
		case TextAlignment::ALIGN_LEFT:
			ss << "Left";
			break;
		case TextAlignment::ALIGN_CENTER:
			ss << "Center";
			break;
		case TextAlignment::ALIGN_RIGHT:
			ss << "Right";
			break;
		case TextAlignment::ALIGN_JUSTIFIED:
			ss << "Justified";
			break;
		default:
			OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );
		}
		ss << " | ";
		switch ( in.getVertical() ) {
		case TextAlignment::ALIGN_TOP:
			ss << "Top";
			break;
		case TextAlignment::ALIGN_CENTER:
			ss << "Center";
			break;
		case TextAlignment::ALIGN_BOTTOM:
			ss << "Bottom";
			break;
		case TextAlignment::ALIGN_JUSTIFIED:
			ss << "Justified";
			break;
		default:
			OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );
		}
		out = ss.str();
	}
	//############################################################################
	void StrConv::toTextAlignment( const std::string& in, TextAlignment& out ) {
		StringList slist;
		tokenize( in, slist, '|' );
		if ( slist.size() > 2 )
			OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );

		// get the string components
		std::string h, v;
		if ( slist.size() == 2 ) {
			h = slist.front();
			v = slist.back();
			trim( h );
			trim( v );
			toLower( h );
			toLower( v );
		}
		if ( slist.size() == 1 ) {
			h = slist.front();
			trim( h );
			toLower( h );
			v = h;
		}

		//convert the strings into values
		TextAlignment::Alignment ha, va;
		if ( h == "left" )
			ha = TextAlignment::ALIGN_LEFT;
		else if ( h == "center" )
			ha = TextAlignment::ALIGN_CENTER;
		else if ( h == "right" )
			ha = TextAlignment::ALIGN_RIGHT;
		else if ( h == "justified" )
			ha = TextAlignment::ALIGN_JUSTIFIED;
		else
			OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );
		if ( v == "top" )
			va = TextAlignment::ALIGN_TOP;
		else if ( v == "center" )
			va = TextAlignment::ALIGN_CENTER;
		else if ( v == "bottom" )
			va = TextAlignment::ALIGN_BOTTOM;
		else if ( v == "justified" )
			va = TextAlignment::ALIGN_JUSTIFIED;
		else
			OG_THROW( Exception::OP_FAILED, "Type conversion failed", __FUNCTION__ );

		// assign the values to out
		out = TextAlignment( ha, va );
	}
	//############################################################################
}
