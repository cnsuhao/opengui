// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef E5AE9E12_AF34_48ff_B669_2802A0C3DC0A
#define E5AE9E12_AF34_48ff_B669_2802A0C3DC0A

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"

namespace OpenGUI {
	//! Provides UTF-16 string representation with implicit conversion from UTF-8
	/*!


	\see
	For additional information on UTF-16 encoding: http://en.wikipedia.org/wiki/UTF-16
	*/
	class OPENGUI_API UTFString {
	public:
		//! size type used to indicate string size and character positions within the string
		typedef size_t size_type;
		//! the usual constant representing: not found, no limit, etc
		static const size_type npos = ~0;

		//! a single 32-bit Unicode character
		typedef UINT32 unicode_char;

		//! a single UTF-16 code point
		typedef unsigned short code_point;
		typedef std::basic_string<code_point> dstring; // data string
		dstring mData;

		//! This exception is used when invalid data streams are encountered
	class invalid_data: public std::runtime_error { // i don't know why the beautifier is freaking out on this line
		public:
			//! constructor takes a string message that can be later retrieved by the what() function
			explicit invalid_data( const std::string& _Message ): std::runtime_error( _Message ) {
				/* The thing is, Bob, it's not that I'm lazy, it's that I just don't care. */
			}
		};

		/*
		Goals:
		Implicit conversions from char* and std::string as UTF-8, and wchar_t* and std::wstring as UTF-16.

		Default access method uses UTF-16 code points, extra methods available for working with UCS-4 code points

		Can read and write all 3 major UTF encodings

		*/

		//! default constructor, creates an empty string
		UTFString();
		//! destructor
		~UTFString();
		//! copy constructor
		UTFString( const UTFString& copy );
		//! \c length copies of \c ch
		UTFString( size_type length, const code_point& ch );
		//! duplicate of str
		UTFString( const code_point* str );
		//! duplicate of str, \c length characters long
		UTFString( const code_point* str, size_type length );
		//! substring of \c str starting at \c index and \c length characters long
		UTFString( const UTFString& str, size_type index, size_type length );

		//! nul-terminated wchar_t array initialized constructor (UTF-16 encoding)
		UTFString( const wchar_t* w_str );
		//! std::wstring (wide string) initialized constructor (UTF-16 encoding)
		UTFString( const std::wstring& wstr );

		//! nul-terminated C-string initialized constructor
		//UTFString( const char* cstr );
		//! std::string initialized constructor
		//UTFString( const std::string& str );

		//! Returns the number of code points in the current string
		size_type length() const;
		//! Returns the number of code points in the current string
		size_type size() const;
		//! returns the maximum number of UTF-16 code points that the string can hold
		size_type max_size() const;
		//! sets the capacity of the string to at least \a size code points
		void reserve( size_type size );
		//! changes the size of the string to \a size
		void resize( size_type num, const code_point& val = 0 );
		//! exchanges the elements of the current string with those of \a from
		void swap( UTFString& from );

		//UTFString& assign( input_iterator start, input_iterator end );
		//! assign \c str to the current string
		UTFString& assign( const UTFString& str );
		//! assign the nul-terminated \c str to the current string
		UTFString& assign( const code_point* str );
		//! assign the first \c num characters of \c str to the current string
		UTFString& assign( const code_point* str, size_type num );
		//! assign \c len entries from \c str to the current string, starting at \c index
		UTFString& assign( const UTFString& str, size_type index, size_type len );
		//! assign \c num copies of \c ch to the current string
		UTFString& assign( size_type num, const code_point& ch );

		//! assign \c wstr to the current string
		UTFString& assign( const std::wstring& wstr );
		//! assign \c w_str to the current string (\c w_str is treated as a 0 terminated UTF-16 stream)
		UTFString& assign( const wchar_t* w_str );
		//! assign the first \c num characters of \c w_str to the current string (\c w_str is treated as a 0 terminated UTF-16 stream)
		UTFString& assign( const wchar_t* w_str, size_type num );


		//! appends \c str on to the end of the current string
		UTFString& append( const UTFString& str );
		//! appends \c str on to the end of the current string
		UTFString& append( const code_point* str );
		//! appends a substring of \c str starting at \c index that is \c len characters long on to the end of the current string
		UTFString& append( const UTFString& str, size_type index, size_type len );
		//! appends \c num characters of \c str on to the end of the current string
		UTFString& append( const code_point* str, size_type num );
		//! appends \c num repetitions of \c ch on to the end of the current string
		UTFString& append( size_type num, code_point ch );
		//! appends the sequence denoted by \c start and \c end on to the end of the current string
		//UTFString& append( input_iterator start, input_iterator end );


		//! assign \c str to the current string (\c str is treated as a UTF-8 stream)
		//UTFString& assign( const std::string& str );
		//! assign \c c_str to the current string (\c c_str is treated as a UTF-8 stream)
		//UTFString& assign( const char* c_str );
		//! assign the first \c num characters of \c c_str to the current string (\c c_str is treated as a UTF-8 stream)
		//UTFString& assign( const char* c_str, size_type num );


		//! returns a reference to the element in the string at index \c loc
		code_point& at( size_type loc );
		//! returns a reference to the element in the string at index \c loc
		const code_point& at( size_type loc ) const;
		//! returns a const pointer to a regular C string, identical to the current string
		const code_point* c_str() const;
		//! returns a pointer to the first character in the current string
		const code_point* data() const;
		//! returns the number of elements that the string can hold before it will need to allocate more space
		size_type capacity() const;

		//! deletes all of the elements in the string
		void clear();

		//! compare \c str to the current string
		int compare( const UTFString& str );
		//! compare \c str to the current string
		int compare( const code_point* str );
		//! compare \c str to a substring of the current string, starting at \c index for \c length characters
		int compare( size_type index, size_type length, const UTFString& str );
		//! compare a substring of \c str to a substring of the current string, where \c index2 and \c length2 refer to \c str and \c index and \c length refer to the current string
		int compare( size_type index, size_type length, const UTFString& str, size_type index2, size_type length2 );
		//! compare a substring of \c str to a substring of the current string, where the substring of \c str begins at zero and is \c length2 characters long, and the substring of the current string begins at \c index and is \c length  characters long
		int compare( size_type index, size_type length, const code_point* str, size_type length2 );

		//! returns \c true if the string has no elements, \c false otherwise
		bool empty() const;

		/*
		iterator erase( iterator loc );
		iterator erase( iterator start, iterator end );
		string& erase( size_type index = 0, size_type num = npos );
		*/

	private:
		//! buffer data type identifier
		enum BufferType {
			none,
			string,
			wstring,
			cstring
		};

		//! common constructor operations
		void _init();

		///////////////////////////////////////////////////////////////////////
		// Scratch buffer
		//! auto cleans the scratch buffer using the proper delete for the stored type
		void _cleanBuffer() const;

		//! creates a scratch buffer of at least \c len size
		void _getBufferCStr( size_t len ) const;

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
