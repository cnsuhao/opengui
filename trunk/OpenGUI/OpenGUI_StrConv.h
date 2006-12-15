// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef B3FEF87E_3BE5_4c98_9E93_C8CDFFA7504C
#define B3FEF87E_3BE5_4c98_9E93_C8CDFFA7504C

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"

namespace OpenGUI {
	class Font; //forward declaration

	//! A list of strings
	typedef std::list<std::string> StringList;

	//! String Converter providing conversions back and forth between strings and both common and %OpenGUI specific types, and a few minor utility functions
	/*! For details on the formatting of strings that these functions expect and produce, see the \ref StringFormats document. */
	class OPENGUI_API StrConv {
	public:
//!\name Conversion Functions
//@{
		//! Turn a string into an int
		static void toInt( const std::string& in, int& out );
		//! Turn a string into an unsigned int
		static void toUInt( const std::string& in, unsigned int& out );
		//! Turn an int into a string
		static void fromInt( int in, std::string& out );
		//! Turn an unsigned int into a string
		static void fromUInt( unsigned int in, std::string& out );
		//! Turn a string into a float
		static void toFloat( const std::string& in, float& out );
		//! Turn a float into a string
		static void fromFloat( float in, std::string& out );
		//! Turn an IVector2 into a string
		static void fromIVector2( const IVector2& in, std::string& out );
		//! Turn a string into an IVector2
		static void toIVector2( const std::string& in, IVector2& out );
		//! Turn an IRect into a string
		static void fromIRect( const IRect& in, std::string& out );
		//! Turn a string into an IRect
		static void toIRect( const std::string& in, IRect& out );
		//! Turn an FVector2 into a string
		static void fromFVector2( const FVector2& in, std::string& out );
		//! Turn a string into an FVector2
		static void toFVector2( const std::string& in, FVector2& out );
		//! Turn an FRect into a string
		static void fromFRect( const FRect& in, std::string& out );
		//! Turn a string into an FRect
		static void toFRect( const std::string& in, FRect& out );
		//! Turn a Color into a string
		static void fromColor( const Color& in, std::string& out );
		//! Turn a string into a Color
		static void toColor( const std::string& in, Color& out );
		//! Turn a bool into a string
		static void fromBool( bool in, std::string& out );
		//! Turn a string into a bool
		static void toBool( const std::string& in, bool& out );
		//! Turn a Font into a string
		static void fromFont( Font& in, std::string& out );
		//! Turn a string into a Font
		static void toFont( const std::string& in, Font& out );
		//! Turn a TextAlignment into a string
		static void fromTextAlignment( const TextAlignment& in, std::string& out );
		//! Turn a string into a TextAlignment
		static void toTextAlignment( const std::string& in, TextAlignment& out );
//@}

//!\name Utility Functions
//@{
		//! Trims whitespace from the beginning and end of the given string
		static void trim( std::string& str );
		//! Explodes a string into a StringList based on separator tokens.
		static void tokenize( const std::string& inputStr, StringList& outputStrList, char token );
		//! Converts a string to all lower case
		static void toLower( std::string& in_out );
//@}
	};
}

#endif // B3FEF87E_3BE5_4c98_9E93_C8CDFFA7504C
