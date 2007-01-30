// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#ifndef B3FEF87E_3BE5_4c98_9E93_C8CDFFA7504C
#define B3FEF87E_3BE5_4c98_9E93_C8CDFFA7504C

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_String.h"
#include "OpenGUI_Types.h"

namespace OpenGUI {
	class Font; //forward declaration

	//! A list of strings
	typedef std::list<String> StringList;

	//! String Converter providing conversions back and forth between strings and both common and %OpenGUI specific types, and a few minor utility functions
	/*! For details on the formatting of strings that these functions expect and produce, see the \ref StringFormats document. */
	class OPENGUI_API StrConv {
	public:
//!\name Conversion Functions
//@{
		//! Turn a string into an int
		static void toInt( const String& in, int& out );
		//! Turn a string into an unsigned int
		static void toUInt( const String& in, unsigned int& out );
		//! Turn an int into a string
		static void fromInt( int in, String& out );
		//! Turn an unsigned int into a string
		static void fromUInt( unsigned int in, String& out );
		//! Turn a string into a float
		static void toFloat( const String& in, float& out );
		//! Turn a float into a string
		static void fromFloat( float in, String& out );
		//! Turn an IVector2 into a string
		static void fromIVector2( const IVector2& in, String& out );
		//! Turn a string into an IVector2
		static void toIVector2( const String& in, IVector2& out );
		//! Turn an IRect into a string
		static void fromIRect( const IRect& in, String& out );
		//! Turn a string into an IRect
		static void toIRect( const String& in, IRect& out );
		//! Turn an FVector2 into a string
		static void fromFVector2( const FVector2& in, String& out );
		//! Turn a string into an FVector2
		static void toFVector2( const String& in, FVector2& out );
		//! Turn an FRect into a string
		static void fromFRect( const FRect& in, String& out );
		//! Turn a string into an FRect
		static void toFRect( const String& in, FRect& out );
		//! Turn a Color into a string
		static void fromColor( const Color& in, String& out );
		//! Turn a string into a Color
		static void toColor( const String& in, Color& out );
		//! Turn a bool into a string
		static void fromBool( bool in, String& out );
		//! Turn a string into a bool
		static void toBool( const String& in, bool& out );
		//! Turn a Font into a string
		static void fromFont(const Font& in, String& out );
		//! Turn a string into a Font
		static void toFont( const String& in, Font& out );
		//! Turn a TextAlignment into a string
		static void fromTextAlignment( const TextAlignment& in, String& out );
		//! Turn a string into a TextAlignment
		static void toTextAlignment( const String& in, TextAlignment& out );
//@}

//!\name Utility Functions
//@{
		//! Trims spaces from the beginning and end of the given string
		static void trim( String& str );
		//! Explodes a string into a StringList based on separator tokens.
		static void tokenize( const String& inputStr, StringList& outputStrList, Char token );
		//! Converts any Latin characters in \a in_out to their English lower case equivalent
		static void toLower_Latin( String& in_out );
//@}
	};
}

#endif // B3FEF87E_3BE5_4c98_9E93_C8CDFFA7504C
