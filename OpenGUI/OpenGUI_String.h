// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef E5AE9E12_AF34_48ff_B669_2802A0C3DC0A
#define E5AE9E12_AF34_48ff_B669_2802A0C3DC0A

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"

namespace OpenGUI {
	//! Provides UTF-8 string representation with several implicit conversions for Unicode (wide) / std::string / C-string
	/*! It is \b extremely important that you realize that this class expects that all
	non std::wstring byte streams are already UTF-8 encoded and are simply lacking the
	proper UTF-8 representation. This is true for all constructors, and overloaded operators.
	It will properly handle std::wstring as Unicode, otherwise it fully expects
	pre-formatted UTF-8 streams unless explicitly stated otherwise in the function
	description. For those of us that are English speaking, this means very little, as
	UTF-8 already handles all <128 char values natively without any special decorations
	necessary. Languages that would normally require use of the >127 char values in the
	ASCII table should either provide UTF-8 encoded streams or use wide strings to
	initialize this class.

	\remarks
	Why do we store UTF-8 instead of UTF-32/USC-4  or UTF-16 (like most people)? Well, UTF-32
	is horribly large. In fact it will quadruple the size of any ASCII encoded string, and
	all of the additional data that is adds in that case is nothing but zeros. Even for most
	European languages, the majority of UTF-32 data is just wasted space. UTF-16 (wchar_t
	and std::wstring) are arguably just as bad. UTF-16 only outperforms UTF-8 in certain
	conditions that, as far as I'm aware, are rare occurances that are dwarfed when compared
	to the number of situations where UTF-8 outperforms UTF-16.	On the other hand, UTF-8
	is an effective way to encode Unicode without adding a ton of additional cruft, and it
	naturally preserves the most important aspects of C string functionality, while the
	unpreserved functionality is still very cost efficient. Additionally, converting from
	UTF-32 to UTF-8 and back is trivial and very efficient, comprised mostly of simple
	bit-shifts. So in short, OpenGUI utilizes UTF-8 internally because, not only is it more
	space efficient, but that additional space savings tends to also contribute to better
	performance.

	\see
	For additional information on UTF-8 encoding: http://en.wikipedia.org/wiki/UTF-8
	*/
	class OPENGUI_API UTF8String {
	public:
		//! size type used to indicate character positions within the string
		typedef size_t size_type;
		//! the usual constant representing: not found, no limit, etc
		static const size_type npos;
		//! type for representing a UTF-32/UCS-4 code point
		typedef unsigned int code_point;

		//! default constructor, creates an empty string
		UTF8String();
		//! destructor
		~UTF8String();

	private:
		std::string mData; // this is the actual UTF-8 data we are storing

		// dumbly appends the given string, no verification performed
		void _append( const std::string& str );
		// dumbly assigns the given string, no verification performed
		void _assign( const std::string& str );

		//! predicts the number of UTF-8 stream bytes that will be needed to represent the given UCS-4 character
		static size_t _predictBytes( const code_point& c );
		//! returns the length of the sequence starting with \c s
		static size_t _getSequenceLen( const char& s );

		//! returns the UCS-4 code point in the UTF-8 stream at the given position
		static code_point _utf8_to_utf32( const char* utf8_str );
		//! decodes the given code point and append the stream bytes to the given string
		void _utf32_to_utf8( code_point c, std::string& out ) const;

		//! runs the held stream through the other _verifyUTF8() test
		bool _verifyUTF8() const {
			return _verifyUTF8( mData );
		};

		//! tests the given UTF-8 stream for proper continuation bytes and sequence length identifiers
		static bool _verifyUTF8( const std::string& str );

		///////////////////////////////////////////////////////////////////////
		// Scratch buffer
		void _init(); //!< common constructor operations
		void _cleanBuffer() const; //!< auto cleans the scratch buffer using the proper delete for the stored type
		void _getBufferCStr( size_t len ) const; //!< creates a scratch buffer of at least \c len size

		// data type identifier
		enum BufferType {
			none,
			string,
			wstring,
			cstring
		};

		mutable BufferType m_bufferType; // identifies the data type held in m_buffer
		mutable size_t m_bufferSize; // size of the CString buffer

		// multi-purpose buffer used everywhere we need a throw-away buffer. (Yes, we're that brave ;-)
		union {
			mutable void* mVoidBuffer;
			mutable char* mCStrBuffer;
			mutable std::string* mStrBuffer;
			mutable std::wstring* mWStrBuffer;
		}
		m_buffer;

	};

	//////////////////////////////////////////////////////////////////////////
	// Define the base types used throughout the rest of the library
	typedef char Char;
	typedef std::string String;
	/*
	//! maps the String type to UTF8String
	typedef UTF8String String;
	//! maps the Char type to wchar_t
	typedef wchar_t Char; // a single character is only usefully representable using wide characters
	*/

} // namespace OpenGUI{

#endif // E5AE9E12_AF34_48ff_B669_2802A0C3DC0A
