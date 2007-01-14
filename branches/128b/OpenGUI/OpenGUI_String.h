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

		//! This exception is used when invalid data streams are encountered
	class invalid_data: public std::runtime_error { // i don't know why the beautifier is freaking out on this line
		public:
			//! constructor takes a string message that can be later retrieved by the what() function
			explicit invalid_data( const std::string& _Message ): std::runtime_error( _Message ) {
				/* The thing is, Bob, it's not that I'm lazy, it's that I just don't care. */
			}
		};

		//! base class of iterator for UTFString
		template<class ITER_TYPE>
		class _iterator {
			friend class UTFString;
		public:
			typedef code_point  value_type;      //!< The value type we normally access
			typedef int         difference_type;
			typedef value_type& reference;       //!< reference to a UTF-16 code point
			typedef const value_type& const_reference;
			typedef value_type* pointer;

			_iterator() {
				mString = 0;
			}
			_iterator( const _iterator& copy ) {
				mIter = copy.mIter;
				mString = copy.mString;
			}

			//! assignment operator
			_iterator& operator=( const _iterator& right ) const {
				ITER_TYPE& iter = const_cast<ITER_TYPE&>( mIter );
				iter = right.mIter;
				const_cast<UTFString*>( mString ) = right.mString;
				return const_cast<_iterator&>( *this );
			}

			//! pre-increment
			_iterator& operator++() const {
				_seekFwd( 1 );
				return const_cast<_iterator&>( *this );
			}
			//! post-increment
			_iterator operator++( int ) const {
				_iterator tmp( *this );
				_seekFwd( 1 );
				return tmp;
			}

			//! pre-decrement
			_iterator& operator--() const {
				_seekRev( 1 );
				return const_cast<_iterator&>( *this );
			}
			//! post-decrement
			_iterator operator--( int ) const {
				_iterator tmp( *this );
				_seekRev( 1 );
				return tmp;
			}
			//! addition operator
			_iterator operator+( difference_type n ) const {
				_iterator tmp( *this );
				tmp._seekFwd( n );
				return tmp;
			}
			//! subtraction operator
			_iterator operator-( difference_type n ) const {
				_iterator tmp( *this );
				tmp._seekRev( n );
				return tmp;
			}
			_iterator& operator+=( difference_type n ) const {
				_seekFwd( n );
				return const_cast<_iterator&>( *this );
			}
			_iterator& operator-=( difference_type n ) const {
				_seekRev( n );
				return const_cast<_iterator&>( *this );
			}
			//! difference operator
			difference_type operator-( const _iterator& right ) const {
				return ( difference_type )( mIter - right.mIter );
			}
			//! dereference operator
			reference operator*() {
				return mIter.operator*();
			}
			//! dereference operator
			const_reference operator*() const {
				return mIter.operator*();
			}

			//! dereference at offset operator
			reference operator[]( difference_type n ) {
				_iterator tmp( *this );
				tmp._seekFwd( n );
				return tmp.operator*();
			}
			//! dereference at offset operator
			const_reference operator[]( difference_type n ) const {
				_iterator tmp( *this );
				tmp._seekFwd( n );
				return tmp.operator*();
			}

			//! equality operator
			bool operator==( const _iterator& right ) const {
				return mIter == right.mIter;
			}
			//! inequality operator
			bool operator!=( const _iterator& right ) const {
				return mIter != right.mIter;
			}
			bool operator<( const _iterator& right ) const {
				return mIter < right.mIter;
			}
			bool operator<=( const _iterator& right ) const {
				return mIter <= right.mIter;
			}
			bool operator>( const _iterator& right ) const {
				return mIter > right.mIter;
			}
			bool operator>=( const _iterator& right ) const {
				return mIter >= right.mIter;
			}
			//! returns the Unicode value of the character at the current position (decodes surrogate pairs if needed)
			unicode_char getCharacter() const {
				unicode_char uc;
				size_t l = _utf16_char_length(( *mIter ) );
				code_point cp[2] = {0, 0};
				cp[0] = mIter[0];
				if ( l == 2 ) {
					try {
						cp[1] = mIter[_inc_value( mIter )];
					} catch ( ... ) {
						cp[1] = 0;
					}
				}
				_utf16_to_utf32( cp, uc );
				return uc;
			}
			//! sets the Unicode value of the character at the current position (adding a surrogate pair if needed)
			void setCharacter( unicode_char uc ) {
				code_point cp[2] = {0, 0};
				size_t l = _utf32_to_utf16( uc, cp );
				if ( _inc_value( mIter ) == 1 ) { // forward iterator
					// insert the new character (gets inserted before our position)
					mIter = mString->insert( *this, cp[0] ).mIter; // 1st half (or possibly this is all there is)
					if ( cp[1] != 0 ) mIter = mString->insert( *this, cp[1] ).mIter; // 2nd half (if present)
					//
					uc = getCharacter(); // grab the character at the current position so we can determine the encoded length
					l = _utf16_char_length( uc );
				} else { // reverse iterator
					//
				}


				/*
								unicode_char uc_tmp;
								size_t l = _utf16_char_length(( *mIter ) );
								code_point cp[2] = {0, 0};
								cp[0] = mIter[0];
								if ( l == 2 ) {
									try {
										cp[1] = mIter[_inc_value()];
									} catch ( ... ) {
										cp[1] = 0;
									}
								}
								l = _utf16_to_utf32( cp, uc_tmp );

								code_point cp[2] = {0, 0};*/
				throw 0;
			}

			//! advances to the next Unicode character, honoring surrogate pairs in the UTF-16 stream
			_iterator& nextCharacter() {
				throw 0;
			}
			//! rewinds to the previous Unicode character, honoring surrogate pairs in the UTF-16 stream
			_iterator& prevCharacter() {
				throw 0;
			}



		protected:
			_iterator( const ITER_TYPE& init, UTFString* utfstr ) {
				mIter = init;
				mString = utfstr;
			}
		private:
			void _seekFwd( difference_type c ) const {
				ITER_TYPE& iter = const_cast<ITER_TYPE&>( mIter );
				iter += c;
			}
			void _seekRev( difference_type c ) const {
				ITER_TYPE& iter = const_cast<ITER_TYPE&>( mIter );
				iter -= c;
			}

			template <class T>
			int _inc_value( const T& ) const {
				throw std::exception( "invalid iterator type for operation" );
			}
			template<> int _inc_value<UTFString::dstring::iterator>( const dstring::iterator& ) const {
				return 1;
			}
			template<> int _inc_value<UTFString::dstring::reverse_iterator>( const dstring::reverse_iterator& ) const {
				return -1;
			}

			ITER_TYPE mIter;
			UTFString* mString;
		};

		typedef _iterator<dstring::iterator> iterator;                 //!< iterator
		typedef _iterator<dstring::reverse_iterator> reverse_iterator; //!< reverse iterator
		typedef const iterator const_iterator;                         //!< const iterator
		typedef const reverse_iterator const_reverse_iterator;         //!< const reverse iterator

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
		//! \a length copies of \a ch
		UTFString( size_type length, const code_point& ch );
		//! duplicate of \a str
		UTFString( const code_point* str );
		//! duplicate of \a str, \a length characters long
		UTFString( const code_point* str, size_type length );
		//! substring of \a str starting at \a index and \a length characters long
		UTFString( const UTFString& str, size_type index, size_type length );

		//! nul-terminated wchar_t array initialized constructor (UTF-16 encoding)
		UTFString( const wchar_t* w_str );
		//! wchar_t array initialized constructor (UTF-16 encoding), \a length characters long
		UTFString( const wchar_t* w_str, size_type length );
		//! std::wstring (wide string) initialized constructor (UTF-16 encoding)
		UTFString( const std::wstring& wstr );

		//! nul-terminated C-string initialized constructor (UTF-8 encoding)
		UTFString( const char* c_str );
		//! nul-terminated C-string initialized constructor (UTF-8 encoding)
		UTFString( const char* c_str, size_type length );
		//! std::string initialized constructor (UTF-8 encoding)
		UTFString( const std::string& str );

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

		//! returns an iterator to the first element of the string
		iterator begin();
		//! returns an iterator to the first element of the string
		const_iterator begin() const;
		//! returns an iterator just past the end of the string
		iterator end();
		//! returns an iterator just past the end of the string
		const_iterator end() const;

		//! returns a reverse iterator to the last element of the string
		reverse_iterator rbegin();
		//! returns a reverse iterator to the last element of the string
		const_reverse_iterator rbegin() const;
		//! returns a reverse iterator just past the beginning of the string
		reverse_iterator rend();
		//! returns a reverse iterator just past the beginning of the string
		const_reverse_iterator rend() const;

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

		//! assign \a wstr to the current string (\a wstr is treated as a UTF-16 stream)
		UTFString& assign( const std::wstring& wstr );
		//! assign \a w_str to the current string (\a w_str is treated as a 0 terminated UTF-16 stream)
		UTFString& assign( const wchar_t* w_str );
		//! assign the first \a num characters of \a w_str to the current string (\a w_str is treated as a UTF-16 stream)
		UTFString& assign( const wchar_t* w_str, size_type num );

		//! assign \a str to the current string (\a str is treated as a UTF-8 stream)
		UTFString& assign( const std::string& str );
		//! assign \a c_str to the current string (\a c_str is treated as a UTF-8 stream)
		UTFString& assign( const char* c_str );
		//! assign the first \a num characters of \a c_str to the current string (\a c_str is treated as a UTF-8 stream)
		UTFString& assign( const char* c_str, size_type num );


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
		//! appends \a val to the end of the string
		void push_back( code_point val );
		//! appends the sequence denoted by \a start and \a end on to the end of the current string
		UTFString& append( iterator start, iterator end );

		//! appends \c str on to the end of the current string
		UTFString& append( const std::wstring& wstr );
		//! appends \c str on to the end of the current string
		UTFString& append( const wchar_t* w_str );
		//! appends a substring of \c str starting at \c index that is \c len characters long on to the end of the current string
		UTFString& append( const std::wstring& wstr, size_type index, size_type len );
		//! appends \c num characters of \c str on to the end of the current string
		UTFString& append( const wchar_t* w_str, size_type num );
		//! appends \c num repetitions of \c ch on to the end of the current string
		UTFString& append( size_type num, wchar_t ch );
		//! appends \a val to the end of the string
		void push_back( wchar_t val );
		//! appends \a val to the end of the string
		void push_back( unicode_char val );

		//! inserts \a ch before the code point denoted by \a i
		iterator insert( iterator i, const code_point& ch );
		//! inserts \a str into the current string, at location \a index
		UTFString& insert( size_type index, const UTFString& str );
		//! inserts \a str into the current string, at location \a index
		UTFString& insert( size_type index, const code_point* str );
		//! inserts a substring of \a str (starting at \a index2 and \a num characters long) into the current string, at location \a index1
		UTFString& insert( size_type index1, const UTFString& str, size_type index2, size_type num );
		//! inserts \a num code points of \a str into the current string, at location \a index
		UTFString& insert( size_type index, const code_point* str, size_type num );
		//! inserts \a num copies of \a ch into the current string, at location \a index
		UTFString& insert( size_type index, size_type num, code_point ch );
		//! inserts \a num copies of \a ch into the current string, before the code point denoted by \a i
		void insert( iterator i, size_type num, const code_point& ch );
		//! inserts the code points denoted by start and end into the current string, before the code point specified by i
		void insert( iterator i, iterator start, iterator end );

		//! removes the code point pointed to by \a loc, returning an iterator to the next character
		iterator erase( iterator loc );
		//! removes the characters between \a start and \a end (including the one at \a start but not the one at \a end), returning an iterator to the character after the last character removed
		iterator erase( iterator start, iterator end );
		//! removes \a num characters from the current string, starting at \a index
		UTFString& erase( size_type index = 0, size_type num = npos );

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

		//!\name UTF-16 encoding/decoding
		//@{
		//! returns \c true if \c cp is the beginning of a UTF-16 sequence (either surrogate pair lead word, or a standalone word)
		static bool _utf16_start_char( code_point cp );
		//! returns \c true if \ cp matches the signature of a surrogate pair lead character
		static bool _utf16_surrogate_lead( code_point cp );
		//! returns \c true if \ cp matches the signature of a surrogate pair following character
		static bool _utf16_surrogate_follow( code_point cp );
		//! estimates the number of UTF-16 code points in the sequence starting with \c cp
		static size_t _utf16_char_length( code_point cp );
		//! returns the number of UTF-16 code points needed to represent the given UTF-32 character \c cp
		static size_t _utf16_char_length( unicode_char uc );
		//! converts the given UTF-16 character buffer to a single UTF-32 Unicode character, returns the number of code_points used to create the output character (2 for surrogate pairs, otherwise 1)
		static size_t _utf16_to_utf32( const code_point in_cp[2], unicode_char& out_uc );
		//! writes the given UTF-32 \c uc_in to the buffer location \c out_cp using UTF-16 encoding, returns the number of code_points used to encode the input
		static size_t _utf32_to_utf16( const unicode_char& in_uc, code_point out_cp[2] );
		//@}

		//!\name UTF-8 encoding/decoding
		//@{
		//! returns \c true if \c cp is the beginning of a UTF-8 sequence
		static bool _utf8_start_char( unsigned char cp );
		//! estimates the number of UTF-8 code points in the sequence starting with \c cp
		static size_t _utf8_char_length( unsigned char cp );
		//! returns the number of UTF-8 code points needed to represent the given UTF-32 character \c cp
		static size_t _utf8_char_length( unicode_char uc );

		//! converts the given UTF-8 character buffer to a single UTF-32 Unicode character, returns the number of bytes used to create the output character (maximum of 6)
		static size_t _utf8_to_utf32( const unsigned char in_cp[6], unicode_char& out_uc );
		//! writes the given UTF-32 \c uc_in to the buffer location \c out_cp using UTF-8 encoding, returns the number of bytes used to encode the input
		static size_t _utf32_to_utf8( const unicode_char& in_uc, unsigned char out_cp[6] );

		//! verifies a UTF-8 stream, returning the total number of Unicode characters found
		size_type _verifyUTF8( const unsigned char* c_str );
		//! verifies a UTF-8 stream, returning the total number of Unicode characters found
		size_type _verifyUTF8( const std::string& str );
		//@}


	private:
		//template<class ITER_TYPE> friend class _iterator;
		dstring mData;

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

		// multi-purpose buffer used everywhere we need a throw-away buffer. Yes, we're that brave ;-)
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
