// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#ifndef E5AE9E12_AF34_48ff_B669_2802A0C3DC0A
#define E5AE9E12_AF34_48ff_B669_2802A0C3DC0A

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"

namespace OpenGUI {

	/* READ THIS NOTICE BEFORE USING IN YOUR OWN APPLICATIONS
	=NOTICE=
	This class is not a complete Unicode solution. It purposefully does not
	provide certain functionality, such as proper lexical sorting for
	Unicode values. It does provide comparison operators for the sole purpose
	of using UTFString as an index with std::map and other operator< sorted
	containers, but it should NOT be relied upon for meaningful lexical
	operations, such as alphabetical sorts. If you need this type of
	functionality, look into using ICU instead (http://icu.sourceforge.net/).

	=REQUIREMENTS=
	There are a few requirements for proper operation. They are fairly small,
	and shouldn't restrict usage on any reasonable target.
	* Compiler must support unsigned 16-bit integer types
	* Compiler must support unsigned 32-bit integer types
	* wchar_t must be either UTF-16 or UTF-32 encoding, and specified as such
	    using the WCHAR_UTF16 macro as outlined below.
	* You must include <iterator>, <string>, and <wchar>. Probably more, but
	    these are the most obvious.

	=REQUIRED PREPROCESSOR MACROS=
	This class requires two preprocessor macros to be defined in order to
	work as advertised.
	INT32 - must be mapped to a signed 32 bit integer (ex. #define INT32 int)
	UINT16 - must be mapped to an unsigned 16 bit integer (ex. #define UINT32 unsigned short)

	Additionally, a third macro should be defined to control the evaluation of wchar_t:
	WCHAR_UTF16 - should be defined when wchar_t represents UTF-16 code points,
	    such as in Windows. Otherwise it is assumed that wchar_t is a 32-bit
		integer representing UTF-32 code points.
	*/

	// THIS IS A VERY BRIEF AUTO DETECTION. YOU MAY NEED TO TWEAK THIS
#ifdef __STDC_ISO_10646__
// for any compiler that provides this, wchar_t is guaranteed to hold any Unicode value with a single code point (32-bit or larger)
// so we can safely skip the rest of the testing
#else // #ifdef __STDC_ISO_10646__
#if defined( __WIN32__ ) || defined( _WIN32 )
#define WCHAR_UTF16 // All currently known Windows platforms utilize UTF-16 encoding in wchar_t
#else // #if defined( __WIN32__ ) || defined( _WIN32 )
#if WCHAR_MAX <= 0xFFFF // this is a last resort fall back test; WCHAR_MAX is defined in <wchar.h>
#define WCHAR_UTF16 // best we can tell, wchar_t is not larger than 16-bit
#endif // #if WCHAR_MAX <= 0xFFFF
#endif // #if defined( __WIN32__ ) || defined( _WIN32 )
#endif // #ifdef __STDC_ISO_10646__

	//ADD THE UTF8 DEFINES HERE (DON'T FORGET TO UNDEFINE THEM AT THE END)


	//! A UTF-16 string with implicit conversion to/from UTF-8 and UTF-32
	/*! This class provides a complete 1 to 1 map of all std::string functions (at least to my
	knowledge). Implicit conversions allow this string class to work with all common C++ string
	formats, with specialty functions defined where implicit conversion would cause potential
	problems or is otherwise unavailable.

	Some additional functionality is present to assist in working with characters using the
	32-bit UTF-32 encoding. (Which is guaranteed to fit any Unicode character into a single
	code point.) \b Note: Reverse iterators do not have this functionality due to the
	ambiguity that surrounds working with UTF-16 in reverse. (Such as, where should an
	iterator point to represent the beginning of a surrogate pair?)


	\par Supported Input Types
	The supported string types for input, and their assumed encoding schemes, are:
	- std::string (UTF-8)
	- char* (UTF-8)
	- std::wstring (autodetected UTF-16 / UTF-32 based on compiler)
	- wchar_t* (autodetected UTF-16 / UTF-32 based on compiler)


	\see
	- For additional information on UTF-16 encoding: http://en.wikipedia.org/wiki/UTF-16
	- For additional information on UTF-8 encoding: http://en.wikipedia.org/wiki/UTF-8
	- For additional information on UTF-32 encoding: http://en.wikipedia.org/wiki/UTF-32
	*/
	class OPENGUI_API UTFString {
	public:
		//! size type used to indicate string size and character positions within the string
		typedef size_t size_type;
		//! the usual constant representing: not found, no limit, etc
		static const size_type npos = ~0;

		//! a single 32-bit Unicode character
		typedef INT32 unicode_char;

		//! a single UTF-16 code point
		typedef UINT16 code_point;

		//! value type typedef for use in iterators
		typedef code_point value_type;

		typedef std::basic_string<code_point> dstring; // data string

		//! string type used for returning UTF-32 formatted data
		typedef std::basic_string<unicode_char> utf32string;

		//! This exception is used when invalid data streams are encountered
	class invalid_data: public std::runtime_error { /* i don't know why the beautifier is freaking out on this line */
		public:
			//! constructor takes a string message that can be later retrieved by the what() function
			explicit invalid_data( const std::string& _Message ): std::runtime_error( _Message ) {
				/* The thing is, Bob, it's not that I'm lazy, it's that I just don't care. */
			}
		};

		//#########################################################################
		//! base iterator class for UTFString
	class _base_iterator: public std::iterator<std::random_access_iterator_tag, value_type> { /* i don't know why the beautifier is freaking out on this line */
			friend class UTFString;
		protected:
			_base_iterator() {
				mString = 0;
			}

			void _seekFwd( size_type c ) {
				mIter += c;
			}
			void _seekRev( size_type c ) {
				mIter -= c;
			}
			void _become( const _base_iterator& i ) {
				mIter = i.mIter;
				mString = i.mString;
			}
			bool _test_begin() const {
				return mIter == mString->mData.begin();
			}
			bool _test_end() const {
				return mIter == mString->mData.end();
			}
			size_type _get_index() const {
				return mIter - mString->mData.begin();
			}
			void _jump_to( size_type index ) {
				mIter = mString->mData.begin() + index;
			}

			unicode_char _getCharacter() const {
				size_type current_index = _get_index();
				return mString->getChar( current_index );
			}
			int _setCharacter( unicode_char uc ) {
				size_type current_index = _get_index();
				int change = mString->setChar( current_index, uc );
				_jump_to( current_index );
				return change;
			}

			void _moveNext() {
				_seekFwd( 1 ); // move 1 code point forward
				if ( _test_end() ) return; // exit if we hit the end
				if ( _utf16_surrogate_follow( mIter[0] ) ) {
					// landing on a follow code point means we might be part of a bigger character
					// so we test for that
					code_point lead_half = 0;
					//NB: we can't possibly be at the beginning here, so no need to test
					lead_half = mIter[-1]; // check the previous code point to see if we're part of a surrogate pair
					if ( _utf16_surrogate_lead( lead_half ) ) {
						_seekFwd( 1 ); // if so, then advance 1 more code point
					}
				}
			}
			void _movePrev() {
				_seekRev( 1 ); // move 1 code point backwards
				if ( _test_begin() ) return; // exit if we hit the beginning
				if ( _utf16_surrogate_follow( mIter[0] ) ) {
					// landing on a follow code point means we might be part of a bigger character
					// so we test for that
					code_point lead_half = 0;
					lead_half = mIter[-1]; // check the previous character to see if we're part of a surrogate pair
					if ( _utf16_surrogate_lead( lead_half ) ) {
						_seekRev( 1 ); // if so, then rewind 1 more code point
					}
				}
			}

			dstring::iterator mIter;
			UTFString* mString;
		};

		//#########################################################################
		// FORWARD ITERATORS
		//#########################################################################
		class _const_fwd_iterator; // forward declaration

		//! forward iterator for UTFString
	class _fwd_iterator: public _base_iterator { /* i don't know why the beautifier is freaking out on this line */
			friend class _const_fwd_iterator;
		public:
			_fwd_iterator() {}
			_fwd_iterator( const _fwd_iterator& i ) {
				_become( i );
			}

			//! pre-increment
			_fwd_iterator& operator++() {
				_seekFwd( 1 );
				return *this;
			}
			//! post-increment
			_fwd_iterator operator++( int ) {
				_fwd_iterator tmp( *this );
				_seekFwd( 1 );
				return tmp;
			}

			//! pre-decrement
			_fwd_iterator& operator--() {
				_seekRev( 1 );
				return *this;
			}
			//! post-decrement
			_fwd_iterator operator--( int ) {
				_fwd_iterator tmp( *this );
				_seekRev( 1 );
				return tmp;
			}

			//! addition operator
			_fwd_iterator operator+( size_type n ) {
				_fwd_iterator tmp( *this );
				tmp._seekFwd( n );
				return tmp;
			}
			//! addition operator
			_fwd_iterator operator+( difference_type n ) {
				_fwd_iterator tmp( *this );
				if ( n < 0 )
					tmp._seekRev( -n );
				else
					tmp._seekFwd( n );
				return tmp;
			}
			//! subtraction operator
			_fwd_iterator operator-( size_type n ) {
				_fwd_iterator tmp( *this );
				tmp._seekRev( n );
				return tmp;
			}
			//! subtraction operator
			_fwd_iterator operator-( difference_type n ) {
				_fwd_iterator tmp( *this );
				if ( n < 0 )
					tmp._seekFwd( -n );
				else
					tmp._seekRev( n );
				return tmp;
			}

			//! addition assignment operator
			_fwd_iterator& operator+=( size_type n ) {
				_seekFwd( n );
				return *this;
			}
			//! addition assignment operator
			_fwd_iterator& operator+=( difference_type n ) {
				if ( n < 0 )
					_seekRev( -n );
				else
					_seekFwd( n );
				return *this;
			}
			//! subtraction assignment operator
			_fwd_iterator& operator-=( size_type n ) {
				_seekRev( n );
				return *this;
			}
			//! subtraction assignment operator
			_fwd_iterator& operator-=( difference_type n ) {
				if ( n < 0 )
					_seekFwd( -n );
				else
					_seekRev( n );
				return *this;
			}

			//! dereference operator
			value_type& operator*() const {
				return mIter.operator*();
			}

			//! dereference at offset operator
			value_type& operator[]( size_type n ) const {
				_fwd_iterator tmp( *this );
				tmp += n;
				return tmp.operator*();
			}
			//! dereference at offset operator
			value_type& operator[]( difference_type n ) const {
				_fwd_iterator tmp( *this );
				tmp += n;
				return tmp.operator*();
			}

			//! advances to the next Unicode character, honoring surrogate pairs in the UTF-16 stream
			_fwd_iterator& moveNext() {
				_moveNext();
				return *this;
			}
			//! rewinds to the previous Unicode character, honoring surrogate pairs in the UTF-16 stream
			_fwd_iterator& movePrev() {
				_movePrev();
				return *this;
			}
			//! Returns the Unicode value of the character at the current position (decodes surrogate pairs if needed)
			unicode_char getCharacter() const {
				return _getCharacter();
			}
			//! Sets the Unicode value of the character at the current position (adding a surrogate pair if needed); returns the amount of string length change caused by the operation
			int setCharacter( unicode_char uc ) {
				return _setCharacter( uc );
			}
		};



		//#########################################################################
		//! const forward iterator for UTFString
	class _const_fwd_iterator: public _base_iterator { /* i don't know why the beautifier is freaking out on this line */
		public:
			_const_fwd_iterator() {}
			_const_fwd_iterator( const _const_fwd_iterator& i ) {
				_become( i );
			}
			_const_fwd_iterator( const _fwd_iterator& i ) {
				_become( i );
			}

			//! pre-increment
			_const_fwd_iterator& operator++() {
				_seekFwd( 1 );
				return *this;
			}
			//! post-increment
			_const_fwd_iterator operator++( int ) {
				_const_fwd_iterator tmp( *this );
				_seekFwd( 1 );
				return tmp;
			}

			//! pre-decrement
			_const_fwd_iterator& operator--() {
				_seekRev( 1 );
				return *this;
			}
			//! post-decrement
			_const_fwd_iterator operator--( int ) {
				_const_fwd_iterator tmp( *this );
				_seekRev( 1 );
				return tmp;
			}

			//! addition operator
			_const_fwd_iterator operator+( size_type n ) {
				_const_fwd_iterator tmp( *this );
				tmp._seekFwd( n );
				return tmp;
			}
			//! addition operator
			_const_fwd_iterator operator+( difference_type n ) {
				_const_fwd_iterator tmp( *this );
				if ( n < 0 )
					tmp._seekRev( -n );
				else
					tmp._seekFwd( n );
				return tmp;
			}
			//! subtraction operator
			_const_fwd_iterator operator-( size_type n ) {
				_const_fwd_iterator tmp( *this );
				tmp._seekRev( n );
				return tmp;
			}
			//! subtraction operator
			_const_fwd_iterator operator-( difference_type n ) {
				_const_fwd_iterator tmp( *this );
				if ( n < 0 )
					tmp._seekFwd( -n );
				else
					tmp._seekRev( n );
				return tmp;
			}

			//! addition assignment operator
			_const_fwd_iterator& operator+=( size_type n ) {
				_seekFwd( n );
				return *this;
			}
			//! addition assignment operator
			_const_fwd_iterator& operator+=( difference_type n ) {
				if ( n < 0 )
					_seekRev( -n );
				else
					_seekFwd( n );
				return *this;
			}
			//! subtraction assignment operator
			_const_fwd_iterator& operator-=( size_type n ) {
				_seekRev( n );
				return *this;
			}
			//! subtraction assignment operator
			_const_fwd_iterator& operator-=( difference_type n ) {
				if ( n < 0 )
					_seekFwd( -n );
				else
					_seekRev( n );
				return *this;
			}

			//! dereference operator
			const value_type& operator*() const {
				return mIter.operator*();
			}

			//! dereference at offset operator
			const value_type& operator[]( size_type n ) const {
				_const_fwd_iterator tmp( *this );
				tmp += n;
				return tmp.operator*();
			}
			//! dereference at offset operator
			const value_type& operator[]( difference_type n ) const {
				_const_fwd_iterator tmp( *this );
				tmp += n;
				return tmp.operator*();
			}

			//! advances to the next Unicode character, honoring surrogate pairs in the UTF-16 stream
			_const_fwd_iterator& moveNext() {
				_moveNext();
				return *this;
			}
			//! rewinds to the previous Unicode character, honoring surrogate pairs in the UTF-16 stream
			_const_fwd_iterator& movePrev() {
				_movePrev();
				return *this;
			}
			//! Returns the Unicode value of the character at the current position (decodes surrogate pairs if needed)
			unicode_char getCharacter() const {
				return _getCharacter();
			}

			//! difference operator
			friend size_type operator-( const _const_fwd_iterator& left, const _const_fwd_iterator& right );
			//! equality operator
			friend bool operator==( const _const_fwd_iterator& left, const _const_fwd_iterator& right );
			//! inequality operator
			friend bool operator!=( const _const_fwd_iterator& left, const _const_fwd_iterator& right );
			//! less than
			friend bool operator<( const _const_fwd_iterator& left, const _const_fwd_iterator& right );
			//! less than or equal
			friend bool operator<=( const _const_fwd_iterator& left, const _const_fwd_iterator& right );
			//! greater than
			friend bool operator>( const _const_fwd_iterator& left, const _const_fwd_iterator& right );
			//! greater than or equal
			friend bool operator>=( const _const_fwd_iterator& left, const _const_fwd_iterator& right );

		};

		//#########################################################################
		// REVERSE ITERATORS
		//#########################################################################
		class _const_rev_iterator; // forward declaration
		//! forward iterator for UTFString
	class _rev_iterator: public _base_iterator { /* i don't know why the beautifier is freaking out on this line */
			friend class _const_rev_iterator;
		public:
			_rev_iterator() {}
			_rev_iterator( const _rev_iterator& i ) {
				_become( i );
			}

			//! pre-increment
			_rev_iterator& operator++() {
				_seekRev( 1 );
				return *this;
			}
			//! post-increment
			_rev_iterator operator++( int ) {
				_rev_iterator tmp( *this );
				_seekRev( 1 );
				return tmp;
			}

			//! pre-decrement
			_rev_iterator& operator--() {
				_seekFwd( 1 );
				return *this;
			}
			//! post-decrement
			_rev_iterator operator--( int ) {
				_rev_iterator tmp( *this );
				_seekFwd( 1 );
				return tmp;
			}

			//! addition operator
			_rev_iterator operator+( size_type n ) {
				_rev_iterator tmp( *this );
				tmp._seekRev( n );
				return tmp;
			}
			//! addition operator
			_rev_iterator operator+( difference_type n ) {
				_rev_iterator tmp( *this );
				if ( n < 0 )
					tmp._seekFwd( -n );
				else
					tmp._seekRev( n );
				return tmp;
			}
			//! subtraction operator
			_rev_iterator operator-( size_type n ) {
				_rev_iterator tmp( *this );
				tmp._seekFwd( n );
				return tmp;
			}
			//! subtraction operator
			_rev_iterator operator-( difference_type n ) {
				_rev_iterator tmp( *this );
				if ( n < 0 )
					tmp._seekRev( -n );
				else
					tmp._seekFwd( n );
				return tmp;
			}

			//! addition assignment operator
			_rev_iterator& operator+=( size_type n ) {
				_seekRev( n );
				return *this;
			}
			//! addition assignment operator
			_rev_iterator& operator+=( difference_type n ) {
				if ( n < 0 )
					_seekFwd( -n );
				else
					_seekRev( n );
				return *this;
			}
			//! subtraction assignment operator
			_rev_iterator& operator-=( size_type n ) {
				_seekFwd( n );
				return *this;
			}
			//! subtraction assignment operator
			_rev_iterator& operator-=( difference_type n ) {
				if ( n < 0 )
					_seekRev( -n );
				else
					_seekFwd( n );
				return *this;
			}

			//! dereference operator
			value_type& operator*() const {
				return mIter[-1];
			}

			//! dereference at offset operator
			value_type& operator[]( size_type n ) const {
				_rev_iterator tmp( *this );
				tmp -= n;
				return tmp.operator*();
			}
			//! dereference at offset operator
			value_type& operator[]( difference_type n ) const {
				_rev_iterator tmp( *this );
				tmp -= n;
				return tmp.operator*();
			}
		};
		//#########################################################################
		//! const reverse iterator for UTFString
	class _const_rev_iterator: public _base_iterator { /* i don't know why the beautifier is freaking out on this line */
		public:
			_const_rev_iterator() {}
			_const_rev_iterator( const _const_rev_iterator& i ) {
				_become( i );
			}
			_const_rev_iterator( const _rev_iterator& i ) {
				_become( i );
			}
			//! pre-increment
			_const_rev_iterator& operator++() {
				_seekRev( 1 );
				return *this;
			}
			//! post-increment
			_const_rev_iterator operator++( int ) {
				_const_rev_iterator tmp( *this );
				_seekRev( 1 );
				return tmp;
			}

			//! pre-decrement
			_const_rev_iterator& operator--() {
				_seekFwd( 1 );
				return *this;
			}
			//! post-decrement
			_const_rev_iterator operator--( int ) {
				_const_rev_iterator tmp( *this );
				_seekFwd( 1 );
				return tmp;
			}

			//! addition operator
			_const_rev_iterator operator+( size_type n ) {
				_const_rev_iterator tmp( *this );
				tmp._seekRev( n );
				return tmp;
			}
			//! addition operator
			_const_rev_iterator operator+( difference_type n ) {
				_const_rev_iterator tmp( *this );
				if ( n < 0 )
					tmp._seekFwd( -n );
				else
					tmp._seekRev( n );
				return tmp;
			}
			//! subtraction operator
			_const_rev_iterator operator-( size_type n ) {
				_const_rev_iterator tmp( *this );
				tmp._seekFwd( n );
				return tmp;
			}
			//! subtraction operator
			_const_rev_iterator operator-( difference_type n ) {
				_const_rev_iterator tmp( *this );
				if ( n < 0 )
					tmp._seekRev( -n );
				else
					tmp._seekFwd( n );
				return tmp;
			}

			//! addition assignment operator
			_const_rev_iterator& operator+=( size_type n ) {
				_seekRev( n );
				return *this;
			}
			//! addition assignment operator
			_const_rev_iterator& operator+=( difference_type n ) {
				if ( n < 0 )
					_seekFwd( -n );
				else
					_seekRev( n );
				return *this;
			}
			//! subtraction assignment operator
			_const_rev_iterator& operator-=( size_type n ) {
				_seekFwd( n );
				return *this;
			}
			//! subtraction assignment operator
			_const_rev_iterator& operator-=( difference_type n ) {
				if ( n < 0 )
					_seekRev( -n );
				else
					_seekFwd( n );
				return *this;
			}

			//! dereference operator
			const value_type& operator*() const {
				return mIter[-1];
			}

			//! dereference at offset operator
			const value_type& operator[]( size_type n ) const {
				_const_rev_iterator tmp( *this );
				tmp -= n;
				return tmp.operator*();
			}
			//! dereference at offset operator
			const value_type& operator[]( difference_type n ) const {
				_const_rev_iterator tmp( *this );
				tmp -= n;
				return tmp.operator*();
			}

			//! difference operator
			friend size_type operator-( const _const_rev_iterator& left, const _const_rev_iterator& right );
			//! equality operator
			friend bool operator==( const _const_rev_iterator& left, const _const_rev_iterator& right );
			//! inequality operator
			friend bool operator!=( const _const_rev_iterator& left, const _const_rev_iterator& right );
			//! less than
			friend bool operator<( const _const_rev_iterator& left, const _const_rev_iterator& right );
			//! less than or equal
			friend bool operator<=( const _const_rev_iterator& left, const _const_rev_iterator& right );
			//! greater than
			friend bool operator>( const _const_rev_iterator& left, const _const_rev_iterator& right );
			//! greater than or equal
			friend bool operator>=( const _const_rev_iterator& left, const _const_rev_iterator& right );
		};
		//#########################################################################

		typedef _fwd_iterator iterator;                     //!< iterator
		typedef _rev_iterator reverse_iterator;             //!< reverse iterator
		typedef _const_fwd_iterator const_iterator;         //!< const iterator
		typedef _const_rev_iterator const_reverse_iterator; //!< const reverse iterator


		//!\name Constructors/Destructor
		//@{
		//! default constructor, creates an empty string
		UTFString() {
			_init();
		}
		//! copy constructor
		UTFString( const UTFString& copy ) {
			_init();
			mData = copy.mData;
		}
		//! \a length copies of \a ch
		UTFString( size_type length, const code_point& ch ) {
			_init();
			assign( length, ch );
		}
		//! duplicate of nul-terminated sequence \a str
		UTFString( const code_point* str ) {
			_init();
			assign( str );
		}
		//! duplicate of \a str, \a length code points long
		UTFString( const code_point* str, size_type length ) {
			_init();
			assign( str, length );
		}
		//! substring of \a str starting at \a index and \a length code points long
		UTFString( const UTFString& str, size_type index, size_type length ) {
			_init();
			assign( str, index, length );
		}
		//! duplicate of nul-terminated \c wchar_t array
		UTFString( const wchar_t* w_str ) {
			_init();
			assign( w_str );
		}
		//! duplicate of \a w_str, \a length characters long
		UTFString( const wchar_t* w_str, size_type length ) {
			_init();
			assign( w_str, length );
		}
		//! duplicate of \a wstr
		UTFString( const std::wstring& wstr ) {
			_init();
			assign( wstr );
		}
		//! duplicate of nul-terminated C-string \a c_str (UTF-8 encoding)
		UTFString( const char* c_str ) {
			_init();
			assign( c_str );
		}
		//! duplicate of \a c_str, \a length characters long (UTF-8 encoding)
		UTFString( const char* c_str, size_type length ) {
			_init();
			assign( c_str, length );
		}
		//! duplicate of \a str (UTF-8 encoding)
		UTFString( const std::string& str ) {
			_init();
			assign( str );
		}
		//! destructor
		~UTFString() {
			_cleanBuffer();
		}
		//@}

		//////////////////////////////////////////////////////////////////////////

		//!\name Utility functions
		//@{
		//! Returns the number of code points in the current string
		size_type length() const {
			return size();
		}
		//! Returns the number of code points in the current string
		size_type size() const {
			return mData.size();
		}
		//! returns the maximum number of UTF-16 code points that the string can hold
		size_type max_size() const {
			return mData.max_size();
		}
		//! sets the capacity of the string to at least \a size code points
		void reserve( size_type size ) {
			mData.reserve( size );
		}
		//! changes the size of the string to \a size, filling in any new area with \a val
		void resize( size_type num, const code_point& val = 0 ) {
			mData.resize( num, val );
		}
		//! exchanges the elements of the current string with those of \a from
		void swap( UTFString& from ) {
			mData.swap( from.mData );
		}
		//! returns \c true if the string has no elements, \c false otherwise
		bool empty() const {
			return mData.empty();
		}
		//! returns a pointer to the first character in the current string
		const code_point* c_str() const {
			return mData.c_str();
		}
		//! returns a pointer to the first character in the current string
		const code_point* data() const {
			return c_str();
		}
		//! returns the number of elements that the string can hold before it will need to allocate more space
		size_type capacity() const {
			return mData.capacity();
		}
		//! deletes all of the elements in the string
		void clear() {
			mData.clear();
		}
		//! returns a substring of the current string, starting at \a index, and \a num characters long.
		/*! If \a num is omitted, it will default to \c UTFString::npos, and the substr() function will simply return the remainder of the string starting at \a index. */
		UTFString substr( size_type index, size_type num = npos ) {
			// this could avoid the extra copy if we used a private specialty constructor
			dstring data = mData.substr( index, num );
			UTFString tmp;
			tmp.mData.swap( data );
			return tmp;
		}
		//! appends \a val to the end of the string
		void push_back( unicode_char val ) {
			code_point cp[2];
			size_t c = _utf32_to_utf16( val, cp );
			if ( c > 0 ) push_back( cp[0] );
			if ( c > 1 ) push_back( cp[1] );
		}
		//! appends \a val to the end of the string
		void push_back( wchar_t val ) {
			// we do this because the Unicode method still preserves UTF-16 code points
			mData.push_back(( unicode_char )val );
		}
		//! appends \a val to the end of the string
		/*! This can be used to push surrogate pair code points, you'll just need to push them
		one after the other. */
		void push_back( code_point val ) {
			mData.push_back( val );
		}
		//! appends \a val to the end of the string
		/*! Limited to characters under the 127 value barrier. */
		void push_back( char val ) {
			mData.push_back(( code_point )val );
		}
		//! returns \c true if the given Unicode character \a ch is in this string
		bool inString( unicode_char ch ) const {
			const_iterator i, ie = end();
			for ( i = begin(); i != ie; i.moveNext() ) {
				if ( i.getCharacter() == ch )
					return true;
			}
			return false;
		}
		//@}

		//////////////////////////////////////////////////////////////////////////

		//!\name Stream variations
		//@{
		//! returns the current string in UTF-8 form within a std::string
		const std::string& asUTF8() const {
			_load_buffer_UTF8();
			return *m_buffer.mStrBuffer;
		}
		//! returns the current string in UTF-8 form as a nul-terminated char array
		const char* asUTF8_c_str() const {
			_load_buffer_UTF8();
			return m_buffer.mStrBuffer->c_str();
		}
		//! returns the current string in UTF-32 form within a utf32string
		const utf32string& asUTF32() const {
			_load_buffer_UTF32();
			return *m_buffer.mUTF32StrBuffer;
		}
		//! returns the current string in UTF-32 form as a nul-terminated unicode_char array
		const unicode_char* asUTF32_c_str() const {
			_load_buffer_UTF32();
			return m_buffer.mUTF32StrBuffer->c_str();
		}
		//! returns the current string in the native form of std::wstring
		const std::wstring& asWStr() const {
			_load_buffer_WStr();
			return *m_buffer.mWStrBuffer;
		}
		//! returns the current string in the native form of a nul-terminated wchar_t array
		const wchar_t* asWStr_c_str() const {
			_load_buffer_WStr();
			return m_buffer.mWStrBuffer->c_str();
		}
		//@}

		//////////////////////////////////////////////////////////////////////////

		//!\name Single Character Access
		//@{
		//! returns a reference to the element in the string at index \c loc
		code_point& at( size_type loc ) {
			return mData.at( loc );
		}
		//! returns a reference to the element in the string at index \c loc
		const code_point& at( size_type loc ) const {
			return mData.at( loc );
		}
		//! returns the data point \a loc evaluated as a UTF-32 value
		/*! This function will will only properly decode surrogate pairs when \a loc points to the index
		of a lead code point that is followed by a trailing code point. Evaluating the trailing code point
		itself, or pointing to a code point that is a sentinel value (part of a broken pair) will return
		the value of just that code point (not a valid Unicode value, but useful as a sentinel value). */
		unicode_char getChar( size_type loc ) const {
			const code_point* ptr = c_str();
			unicode_char uc;
			size_t l = _utf16_char_length( ptr[loc] );
			code_point cp[2] = { /* blame the code beautifier */
								   0, 0
							   };
			cp[0] = ptr[loc];

			if ( l == 2 && ( loc + 1 ) < mData.length() ) {
				cp[1] = ptr[loc+1];
			}
			_utf16_to_utf32( cp, uc );
			return uc;
		}
		//! sets the value of the character at \a loc to the Unicode value \a ch (UTF-32)
		/*! Providing sentinel values (values between U+D800-U+DFFF) are accepted, but you should be aware
		that you can also unwittingly create a valid surrogate pair if you don't pay attention to what you
		are doing. \note This operation may also lengthen the string if a surrogate pair is needed to
		represent the value given, but one is not available to replace; or alternatively shorten the string
		if an existing surrogate pair is replaced with a character that is representable without a surrogate
		pair. The return value will signify any lengthening or shortening performed, returning 0 if no change
		was made, -1 if the string was shortened, or 1 if the string was lengthened. Any single call can
		only change the string length by + or - 1. */
		int setChar( size_type loc, unicode_char ch ) {
			const code_point* ptr = c_str();
			code_point cp[2] = { /* blame the code beautifier */
								   0, 0
							   };
			size_t l = _utf32_to_utf16( ch, cp );
			unicode_char existingChar = getChar( loc );
			size_t existingSize = _utf16_char_length( existingChar );
			size_t newSize = _utf16_char_length( ch );

			if ( newSize > existingSize ) {
				at( loc ) = cp[0];
				insert( loc + 1, 1, cp[1] );
				return 1;
			}
			if ( newSize < existingSize ) {
				erase( loc, 1 );
				at( loc ) = cp[0];
				return -1;
			}

			// newSize == existingSize
			at( loc ) = cp[0];
			if ( l == 2 ) at( loc + 1 ) = cp[1];
			return 0;
		}
		//@}

		//////////////////////////////////////////////////////////////////////////

		//!\name iterator acquisition
		//@{
		//! returns an iterator to the first element of the string
		iterator begin() {
			iterator i;
			i.mIter = mData.begin();
			i.mString = this;
			return i;
		}
		//! returns an iterator to the first element of the string
		const_iterator begin() const {
			const_iterator i;
			i.mIter = const_cast<UTFString*>( this )->mData.begin();
			i.mString = const_cast<UTFString*>( this );
			return i;
		}
		//! returns an iterator just past the end of the string
		iterator end() {
			iterator i;
			i.mIter = mData.end();
			i.mString = this;
			return i;
		}
		//! returns an iterator just past the end of the string
		const_iterator end() const {
			const_iterator i;
			i.mIter = const_cast<UTFString*>( this )->mData.end();
			i.mString = const_cast<UTFString*>( this );
			return i;
		}
		//! returns a reverse iterator to the last element of the string
		reverse_iterator rbegin() {
			reverse_iterator i;
			i.mIter = mData.end();
			i.mString = this;
			return i;
		}
		//! returns a reverse iterator to the last element of the string
		const_reverse_iterator rbegin() const {
			const_reverse_iterator i;
			i.mIter = const_cast<UTFString*>( this )->mData.end();
			i.mString = const_cast<UTFString*>( this );
			return i;
		}
		//! returns a reverse iterator just past the beginning of the string
		reverse_iterator rend() {
			reverse_iterator i;
			i.mIter = mData.begin();
			i.mString = this;
			return i;
		}
		//! returns a reverse iterator just past the beginning of the string
		const_reverse_iterator rend() const {
			const_reverse_iterator i;
			i.mIter = const_cast<UTFString*>( this )->mData.begin();
			i.mString = const_cast<UTFString*>( this );
			return i;
		}
		//@}

		//////////////////////////////////////////////////////////////////////////

		//!\name assign
		//@{
		//! gives the current string the values from \a start to \a end
		UTFString& assign( iterator start, iterator end ) {
			mData.assign( start.mIter, end.mIter );
			return *this;
		}
		//! assign \a str to the current string
		UTFString& assign( const UTFString& str ) {
			mData.assign( str.mData );
			return *this;
		}
		//! assign the nul-terminated \a str to the current string
		UTFString& assign( const code_point* str ) {
			mData.assign( str );
			return *this;
		}
		//! assign the first \a num characters of \a str to the current string
		UTFString& assign( const code_point* str, size_type num ) {
			mData.assign( str, num );
			return *this;
		}
		//! assign \a len entries from \a str to the current string, starting at \a index
		UTFString& assign( const UTFString& str, size_type index, size_type len ) {
			mData.assign( str.mData, index, len );
			return *this;
		}
		//! assign \a num copies of \a ch to the current string
		UTFString& assign( size_type num, const code_point& ch ) {
			mData.assign( num, ch );
			return *this;
		}
		//! assign \a wstr to the current string (\a wstr is treated as a UTF-16 stream)
		UTFString& assign( const std::wstring& wstr ) {
			mData.clear();
			mData.reserve( wstr.length() ); // best guess bulk allocate
#ifdef WCHAR_UTF16 // if we're already working in UTF-16, this is easy
			code_point tmp;
			std::wstring::const_iterator i, ie = wstr.end();
			for ( i = wstr.begin(); i != ie; i++ ) {
				tmp = static_cast<code_point>( *i );
				mData.push_back( tmp );
			}
#else // otherwise we do it the safe way (which is still 100% safe to pass UTF-16 through, just slower)
			code_point cp[3] = {0, 0, 0};
			unicode_char tmp;
			std::wstring::const_iterator i, ie = wstr.end();
			for ( i = wstr.begin(); i != ie; i++ ) {
				tmp = static_cast<unicode_char>( *i );
				size_t l = _utf32_to_utf16( tmp, cp );
				if ( l > 0 ) mData.push_back( cp[0] );
				if ( l > 1 ) mData.push_back( cp[1] );
			}
#endif
			return *this;
		}
		//! assign \a w_str to the current string
		UTFString& assign( const wchar_t* w_str ) {
			std::wstring tmp;
			tmp.assign( w_str );
			return assign( tmp );
		}
		//! assign the first \a num characters of \a w_str to the current string
		UTFString& assign( const wchar_t* w_str, size_type num ) {
			std::wstring tmp;
			tmp.assign( w_str, num );
			return assign( tmp );
		}
		//! assign \a str to the current string (\a str is treated as a UTF-8 stream)
		UTFString& assign( const std::string& str ) {
			size_type len = _verifyUTF8( str );
			clear(); // empty our contents, if there are any
			reserve( len ); // best guess bulk capacity growth

			// This is a 3 step process, converting each byte in the UTF-8 stream to UTF-32,
			// then converting it to UTF-16, then finally appending the data buffer

			unicode_char uc;          // temporary Unicode character buffer
			unsigned char utf8buf[7]; // temporary UTF-8 buffer
			utf8buf[6] = 0;
			size_t utf8len;           // UTF-8 length
			code_point utf16buff[3];  // temporary UTF-16 buffer
			utf16buff[2] = 0;
			size_t utf16len;          // UTF-16 length

			std::string::const_iterator i, ie = str.end();
			for ( i = str.begin(); i != ie; i++ ) {
				utf8len = _utf8_char_length( static_cast<unsigned char>( *i ) ); // estimate bytes to load
				for ( size_t j = 0; j < utf8len; j++ ) { // load the needed UTF-8 bytes
					utf8buf[j] = ( static_cast<unsigned char>( *( i + j ) ) ); // we don't increment 'i' here just in case the estimate is wrong (shouldn't happen, but we're being careful)
				}
				utf8buf[utf8len] = 0; // nul terminate so we throw an exception before running off the end of the buffer
				utf8len = _utf8_to_utf32( utf8buf, uc ); // do the UTF-8 -> UTF-32 conversion
				i += utf8len - 1; // we subtract 1 for the increment of the 'for' loop

				utf16len = _utf32_to_utf16( uc, utf16buff ); // UTF-32 -> UTF-16 conversion
				append( utf16buff, utf16len ); // append the characters to the string
			}
			return *this;
		}
		//! assign \a c_str to the current string (\a c_str is treated as a UTF-8 stream)
		UTFString& assign( const char* c_str ) {
			std::string tmp( c_str );
			return assign( tmp );
		}
		//! assign the first \a num characters of \a c_str to the current string (\a c_str is treated as a UTF-8 stream)
		UTFString& assign( const char* c_str, size_type num ) {
			std::string tmp;
			tmp.assign( c_str, num );
			return assign( tmp );
		}
		//@}

		//////////////////////////////////////////////////////////////////////////

		//!\name append
		//@{
		//! appends \a str on to the end of the current string
		UTFString& append( const UTFString& str ) {
			mData.append( str.mData );
			return *this;
		}
		//! appends \a str on to the end of the current string
		UTFString& append( const code_point* str ) {
			mData.append( str );
			return *this;
		}
		//! appends a substring of \a str starting at \a index that is \a len characters long on to the end of the current string
		UTFString& append( const UTFString& str, size_type index, size_type len ) {
			mData.append( str.mData, index, len );
			return *this;
		}
		//! appends \a num characters of \a str on to the end of the current string
		UTFString& append( const code_point* str, size_type num ) {
			mData.append( str, num );
			return *this;
		}
		//! appends \a num repetitions of \a ch on to the end of the current string
		UTFString& append( size_type num, code_point ch ) {
			mData.append( num, ch );
			return *this;
		}
		//! appends the sequence denoted by \a start and \a end on to the end of the current string
		UTFString& append( iterator start, iterator end ) {
			mData.append( start.mIter, end.mIter );
			return *this;
		}
		//! appends \a num characters of \a str on to the end of the current string
		UTFString& append( const wchar_t* w_str, size_type num ) {
			std::wstring tmp( w_str, num );
			return append( tmp );
		}
		//! appends \a num repetitions of \a ch on to the end of the current string
		UTFString& append( size_type num, wchar_t ch ) {
			return append( num, static_cast<unicode_char>( ch ) );
		}
		//! appends \a num characters of \a str on to the end of the current string  (UTF-8 encoding)
		UTFString& append( const char* c_str, size_type num ) {
			UTFString tmp( c_str, num );
			append( tmp );
			return *this;
		}
		//! appends \a num repetitions of \a ch on to the end of the current string (Unicode values less than 128)
		UTFString& append( size_type num, char ch ) {
			append( num, static_cast<code_point>( ch ) );
			return *this;
		}
		//! appends \a num repetitions of \a ch on to the end of the current string (Full Unicode spectrum)
		UTFString& append( size_type num, unicode_char ch ) {
			code_point cp[2] = {0, 0};
			if ( _utf32_to_utf16( ch, cp ) == 2 ) {
				for ( size_type i = 0; i < num; i++ ) {
					append( 1, cp[0] );
					append( 1, cp[1] );
				}
			} else {
				for ( size_type i = 0; i < num; i++ ) {
					append( 1, cp[0] );
				}
			}
			return *this;
		}
		//@}

		//////////////////////////////////////////////////////////////////////////

		//!\name insert
		//@{
		//! inserts \a ch before the code point denoted by \a i
		iterator insert( iterator i, const code_point& ch );
		//! inserts \a str into the current string, at location \a index
		UTFString& insert( size_type index, const UTFString& str );
		//! inserts \a str into the current string, at location \a index
		UTFString& insert( size_type index, const code_point* str );
		//! inserts a substring of \a str (starting at \a index2 and \a num code points long) into the current string, at location \a index1
		UTFString& insert( size_type index1, const UTFString& str, size_type index2, size_type num );
		//! inserts the code points denoted by start and end into the current string, before the code point specified by i
		void insert( iterator i, iterator start, iterator end );
		//! inserts \a num code points of \a str into the current string, at location \a index
		UTFString& insert( size_type index, const code_point* str, size_type num );
		//! inserts \a num code points of \a str into the current string, at location \a index
		UTFString& insert( size_type index, const wchar_t* w_str, size_type num );
		//! inserts \a num code points of \a str into the current string, at location \a index
		UTFString& insert( size_type index, const char* c_str, size_type num );
		//! inserts \a num copies of \a ch into the current string, at location \a index
		UTFString& insert( size_type index, size_type num, code_point ch );
		//! inserts \a num copies of \a ch into the current string, at location \a index
		UTFString& insert( size_type index, size_type num, wchar_t ch );
		//! inserts \a num copies of \a ch into the current string, at location \a index
		UTFString& insert( size_type index, size_type num, char ch );
		//! inserts \a num copies of \a ch into the current string, at location \a index
		UTFString& insert( size_type index, size_type num, unicode_char ch );
		//! inserts \a num copies of \a ch into the current string, before the code point denoted by \a i
		void insert( iterator i, size_type num, const code_point& ch );
		//! inserts \a num copies of \a ch into the current string, before the code point denoted by \a i
		void insert( iterator i, size_type num, const wchar_t& ch );
		//! inserts \a num copies of \a ch into the current string, before the code point denoted by \a i
		void insert( iterator i, size_type num, const char& ch );
		//! inserts \a num copies of \a ch into the current string, before the code point denoted by \a i
		void insert( iterator i, size_type num, const unicode_char& ch );
		//@}

		//!\name erase
		//@{
		//! removes the code point pointed to by \a loc, returning an iterator to the next character
		iterator erase( iterator loc );
		//! removes the code points between \a start and \a end (including the one at \a start but not the one at \a end), returning an iterator to the code point after the last code point removed
		iterator erase( iterator start, iterator end );
		//! removes \a num code points from the current string, starting at \a index
		UTFString& erase( size_type index = 0, size_type num = npos );
		//@}

		//!\name replace
		//@{
		//! replaces up to \a num1 code points of the current string (starting at \a index1) with \a str
		UTFString& replace( size_type index1, size_type num1, const UTFString& str );
		//! replaces up to \a num1 code points of the current string (starting at \a index1) with up to \a num2 code points from \a str
		UTFString& replace( size_type index1, size_type num1, const UTFString& str, size_type num2 );
		//! replaces up to \a num1 code points of the current string (starting at \a index1) with up to \a num2 code points from \a str beginning at \a index2
		UTFString& replace( size_type index1, size_type num1, const UTFString& str, size_type index2, size_type num2 );
		//! replaces code points in the current string from \a start to \a end with \a num code points from \a str
		UTFString& replace( iterator start, iterator end, const UTFString& str, size_type num = npos );
		//! replaces up to \a num1 code points in the current string (beginning at \a index) with \c num2 copies of \c ch
		UTFString& replace( size_type index, size_type num1, size_type num2, code_point ch );
		//! replaces the code points in the current string from \a start to \a end with \a num copies of \a ch
		UTFString& replace( iterator start, iterator end, size_type num, code_point ch );
		//@}

		//!\name compare
		//@{
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
		//! compare a substring of \c str to a substring of the current string, where the substring of \c str begins at zero and is \c length2 <b>UTF-16 code points</b> long, and the substring of the current string begins at \c index and is \c length characters long
		int compare( size_type index, size_type length, const wchar_t* w_str, size_type length2 );
		//! compare a substring of \c str to a substring of the current string, where the substring of \c str begins at zero and is \c length2 <b>UTF-8 code points</b> long, and the substring of the current string begins at \c index and is \c length characters long
		int compare( size_type index, size_type length, const char* c_str, size_type length2 );
		//@}

		//!\name find & rfind
		//@{
		//! returns the index of the first occurrence of \a str within the current string, starting at \a index; returns \c UTFString::npos if nothing is found
		/*! \a str is a UTF-16 encoded string, but through implicit casting can also be a UTF-8 encoded string (const char* or std::string) */
		size_type find( const UTFString& str, size_type index );
		//! returns the index of the first occurrence of \a str within the current string and within \a length code points, starting at \a index; returns \c UTFString::npos if nothing is found
		/*! \a cp_str is a UTF-16 encoded string */
		size_type find( const code_point* cp_str, size_type index, size_type length );
		//! returns the index of the first occurrence of \a str within the current string and within \a length code points, starting at \a index; returns \c UTFString::npos if nothing is found
		/*! \a cp_str is a UTF-8 encoded string */
		size_type find( const char* c_str, size_type index, size_type length );
		//! returns the index of the first occurrence of \a str within the current string and within \a length code points, starting at \a index; returns \c UTFString::npos if nothing is found
		/*! \a cp_str is a UTF-16 encoded string */
		size_type find( const wchar_t* w_str, size_type index, size_type length );
		//! returns the index of the first occurrence \a ch within the current string, starting at \a index; returns \c UTFString::npos if nothing is found
		/*! \a ch is only capable of representing Unicode values up to U+007F (127) */
		size_type find( char ch, size_type index );
		//! returns the index of the first occurrence \a ch within the current string, starting at \a index; returns \c UTFString::npos if nothing is found
		/*! \a ch is only capable of representing Unicode values up to U+FFFF (65535) */
		size_type find( code_point ch, size_type index );
		//! returns the index of the first occurrence \a ch within the current string, starting at \a index; returns \c UTFString::npos if nothing is found
		/*! \a ch is only capable of representing Unicode values up to U+FFFF (65535) */
		size_type find( wchar_t ch, size_type index );
		//! returns the index of the first occurrence \a ch within the current string, starting at \a index; returns \c UTFString::npos if nothing is found
		/*! \a ch can fully represent any Unicode character */
		size_type find( unicode_char ch, size_type index );

		//! returns the location of the first occurrence of \a str in the current string, doing a reverse search from \a index; returns \c UTFString::npos if nothing is found
		size_type rfind( const UTFString& str, size_type index );
		//! returns the location of the first occurrence of \a str in the current string, doing a reverse search from \a index, searching at most \a num characters; returns \c UTFString::npos if nothing is found
		size_type rfind( const code_point* cp_str, size_type index, size_type num );
		//! returns the location of the first occurrence of \a str in the current string, doing a reverse search from \a index, searching at most \a num characters; returns \c UTFString::npos if nothing is found
		size_type rfind( const char* c_str, size_type index, size_type num );
		//! returns the location of the first occurrence of \a str in the current string, doing a reverse search from \a index, searching at most \a num characters; returns \c UTFString::npos if nothing is found
		size_type rfind( const wchar_t* w_str, size_type index, size_type num );
		//! returns the location of the first occurrence of \a ch in the current string, doing a reverse search from \a index; returns \c UTFString::npos if nothing is found
		size_type rfind( char ch, size_type index );
		//! returns the location of the first occurrence of \a ch in the current string, doing a reverse search from \a index; returns \c UTFString::npos if nothing is found
		size_type rfind( code_point ch, size_type index );
		//! returns the location of the first occurrence of \a ch in the current string, doing a reverse search from \a index; returns \c UTFString::npos if nothing is found
		size_type rfind( wchar_t ch, size_type index );
		//! returns the location of the first occurrence of \a ch in the current string, doing a reverse search from \a index; returns \c UTFString::npos if nothing is found
		size_type rfind( unicode_char ch, size_type index );
		//@}

		//!\name find_first/last_(not)_of
		//@{
		//! Returns the index of the first character within the current string that matches \b any character in \a str, beginning the search at \a index and searching at most \a num characters; returns \c UTFString::npos if nothing is found
		size_type find_first_of( const UTFString &str, size_type index = 0, size_type num = npos );
		//! returns the index of the first occurrence of \a ch in the current string, starting the search at \a index; returns \c UTFString::npos if nothing is found
		size_type find_first_of( code_point ch, size_type index = 0 );
		//! returns the index of the first occurrence of \a ch in the current string, starting the search at \a index; returns \c UTFString::npos if nothing is found
		size_type find_first_of( char ch, size_type index = 0 );
		//! returns the index of the first occurrence of \a ch in the current string, starting the search at \a index; returns \c UTFString::npos if nothing is found
		size_type find_first_of( wchar_t ch, size_type index = 0 );
		//! returns the index of the first occurrence of \a ch in the current string, starting the search at \a index; returns \c UTFString::npos if nothing is found
		size_type find_first_of( unicode_char ch, size_type index = 0 );

		//! returns the index of the first character within the current string that does not match any character in \a str, beginning the search at \a index and searching at most \a num characters; returns \c UTFString::npos if nothing is found
		size_type find_first_not_of( const UTFString& str, size_type index = 0, size_type num = npos );
		//! returns the index of the first character within the current string that does not match \a ch, starting the search at \a index; returns \c UTFString::npos if nothing is found
		size_type find_first_not_of( code_point ch, size_type index = 0 );
		//! returns the index of the first character within the current string that does not match \a ch, starting the search at \a index; returns \c UTFString::npos if nothing is found
		size_type find_first_not_of( char ch, size_type index = 0 );
		//! returns the index of the first character within the current string that does not match \a ch, starting the search at \a index; returns \c UTFString::npos if nothing is found
		size_type find_first_not_of( wchar_t ch, size_type index = 0 );
		//! returns the index of the first character within the current string that does not match \a ch, starting the search at \a index; returns \c UTFString::npos if nothing is found
		size_type find_first_not_of( unicode_char ch, size_type index = 0 );

		//! returns the index of the first character within the current string that matches any character in \a str, doing a reverse search from \a index and searching at most \a num characters; returns \c UTFString::npos if nothing is found
		size_type find_last_of( const UTFString& str, size_type index = npos, size_type num = npos );
		//! returns the index of the first occurrence of \a ch in the current string, doing a reverse search from \a index; returns \c UTFString::npos if nothing is found
		size_type find_last_of( code_point ch, size_type index = npos );
		//! returns the index of the first occurrence of \a ch in the current string, doing a reverse search from \a index; returns \c UTFString::npos if nothing is found
		size_type find_last_of( char ch, size_type index = npos );
		//! returns the index of the first occurrence of \a ch in the current string, doing a reverse search from \a index; returns \c UTFString::npos if nothing is found
		size_type find_last_of( wchar_t ch, size_type index = npos );
		//! returns the index of the first occurrence of \a ch in the current string, doing a reverse search from \a index; returns \c UTFString::npos if nothing is found
		size_type find_last_of( unicode_char ch, size_type index = npos );

		//! returns the index of the last character within the current string that does not match any character in \a str, doing a reverse search from \a index; returns \c UTFString::npos if nothing is found
		size_type find_last_not_of( const UTFString& str, size_type index = npos, size_type num = npos );
		//! returns the index of the last occurrence of a character that does not match \a ch in the current string, doing a reverse search from \a index; returns \c UTFString::npos if nothing is found
		size_type find_last_not_of( code_point ch, size_type index = npos );
		//! returns the index of the last occurrence of a character that does not match \a ch in the current string, doing a reverse search from \a index; returns \c UTFString::npos if nothing is found
		size_type find_last_not_of( char ch, size_type index = npos );
		//! returns the index of the last occurrence of a character that does not match \a ch in the current string, doing a reverse search from \a index; returns \c UTFString::npos if nothing is found
		size_type find_last_not_of( wchar_t ch, size_type index = npos );
		//! returns the index of the last occurrence of a character that does not match \a ch in the current string, doing a reverse search from \a index; returns \c UTFString::npos if nothing is found
		size_type find_last_not_of( unicode_char ch, size_type index = npos );
		//@}

		//!\name Operators
		//@{
		//! less than operator
		bool operator<( const UTFString& right ) {
			return compare( right ) < 0;
		}
		//! less than or equal operator
		bool operator<=( const UTFString& right ) {
			return compare( right ) <= 0;
		}
		//! greater than operator
		bool operator>( const UTFString& right ) {
			return compare( right ) > 0;
		}
		//! greater than or equal operator
		bool operator>=( const UTFString& right ) {
			return compare( right ) >= 0;
		}
		//! equality operator
		bool operator==( const UTFString& right ) {
			return compare( right ) == 0;
		}
		//! inequality operator
		bool operator!=( const UTFString& right ) {
			return !operator==( right );
		}
		//! assignment operator, implicitly casts all compatible types
		UTFString& operator=( const UTFString& s ) {
			return assign( s );
		}
		//! assignment operator
		UTFString& operator=( code_point ch ) {
			clear();
			return append( 1, ch );
		}
		//! assignment operator
		UTFString& operator=( char ch ) {
			clear();
			return append( 1, ch );
		}
		//! assignment operator
		UTFString& operator=( wchar_t ch ) {
			clear();
			return append( 1, ch );
		}
		//! assignment operator
		UTFString& operator=( unicode_char ch ) {
			clear();
			return append( 1, ch );
		}
		//! code point dereference operator
		code_point& operator[]( size_type index ) {
			return at( index );
		}
		//@}

		//!\name Implicit Cast Operators
		//@{
		//! implicit cast to std::string
		operator std::string() const {
			return std::string( asUTF8() );
		}
		//! implicit cast to std::wstring
		operator std::wstring() const {
			return std::wstring( asWStr() );
		}
		//@}


		//!\name UTF-16 character encoding/decoding
		//@{
		//! returns \c true if \c cp does not match the signature for the lead of follow code point of a surrogate pair in a UTF-16 sequence
		static bool _utf16_independent_char( code_point cp );
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
		//! writes the given UTF-32 \c uc_in to the buffer location \c out_cp using UTF-16 encoding, returns the number of code_points used to encode the input (always 1 or 2)
		static size_t _utf32_to_utf16( const unicode_char& in_uc, code_point out_cp[2] );
		//@}

		//!\name UTF-8 character encoding/decoding
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
		static size_type _verifyUTF8( const unsigned char* c_str );
		//! verifies a UTF-8 stream, returning the total number of Unicode characters found
		static size_type _verifyUTF8( const std::string& str );
		//@}

	private:
		//template<class ITER_TYPE> friend class _iterator;
		dstring mData;

		//! buffer data type identifier
		enum BufferType {
			bt_none,
			bt_string,
			bt_wstring,
			bt_utf32string
		};

		//! common constructor operations
		void _init();

		///////////////////////////////////////////////////////////////////////
		// Scratch buffer
		//! auto cleans the scratch buffer using the proper delete for the stored type
		void _cleanBuffer() const;

		//! create a std::string in the scratch buffer area
		void _getBufferStr() const;
		//! create a std::wstring in the scratch buffer area
		void _getBufferWStr() const;
		//! create a utf32string in the scratch buffer area
		void _getBufferUTF32Str() const;

		void _load_buffer_UTF8() const;
		void _load_buffer_WStr() const;
		void _load_buffer_UTF32() const;

		mutable BufferType m_bufferType; // identifies the data type held in m_buffer
		mutable size_t m_bufferSize; // size of the CString buffer

		// multi-purpose buffer used everywhere we need a throw-away buffer. Yes, we're that brave ;-)
		union {
			mutable void* mVoidBuffer;
			mutable std::string* mStrBuffer;
			mutable std::wstring* mWStrBuffer;
			mutable utf32string* mUTF32StrBuffer;
		}
		m_buffer;
	};

	//! string addition operator \relates UTFString
	inline UTFString operator+( const UTFString& s1, const UTFString& s2 ) {
		return UTFString( s1 ).append( s2 );
	}
	//! string addition operator \relates UTFString
	inline UTFString operator+( const UTFString& s1, UTFString::code_point c ) {
		return UTFString( s1 ).append( 1, c );
	}
	//! string addition operator \relates UTFString
	inline UTFString operator+( const UTFString& s1, UTFString::unicode_char c ) {
		return UTFString( s1 ).append( 1, c );
	}
	//! string addition operator \relates UTFString
	inline UTFString operator+( const UTFString& s1, char c ) {
		return UTFString( s1 ).append( 1, c );
	}
	//! string addition operator \relates UTFString
	inline UTFString operator+( const UTFString& s1, wchar_t c ) {
		return UTFString( s1 ).append( 1, c );
	}
	//! string addition operator \relates UTFString
	inline UTFString operator+( UTFString::code_point c, const UTFString& s2 ) {
		return UTFString().append( 1, c ).append( s2 );
	}
	//! string addition operator \relates UTFString
	inline UTFString operator+( UTFString::unicode_char c, const UTFString& s2 ) {
		return UTFString().append( 1, c ).append( s2 );
	}
	//! string addition operator \relates UTFString
	inline UTFString operator+( char c, const UTFString& s2 ) {
		return UTFString().append( 1, c ).append( s2 );
	}
	//! string addition operator \relates UTFString
	inline UTFString operator+( wchar_t c, const UTFString& s2 ) {
		return UTFString().append( 1, c ).append( s2 );
	}

	// (const) forward iterator common operators
	inline UTFString::size_type operator-( const UTFString::_const_fwd_iterator& left, const UTFString::_const_fwd_iterator& right ) {
		return ( left.mIter - right.mIter );
	}
	inline bool operator==( const UTFString::_const_fwd_iterator& left, const UTFString::_const_fwd_iterator& right ) {
		return left.mIter == right.mIter;
	}
	inline bool operator!=( const UTFString::_const_fwd_iterator& left, const UTFString::_const_fwd_iterator& right ) {
		return left.mIter != right.mIter;
	}
	inline bool operator<( const UTFString::_const_fwd_iterator& left, const UTFString::_const_fwd_iterator& right ) {
		return left.mIter < right.mIter;
	}
	inline bool operator<=( const UTFString::_const_fwd_iterator& left, const UTFString::_const_fwd_iterator& right ) {
		return left.mIter <= right.mIter;
	}
	inline bool operator>( const UTFString::_const_fwd_iterator& left, const UTFString::_const_fwd_iterator& right ) {
		return left.mIter > right.mIter;
	}
	inline bool operator>=( const UTFString::_const_fwd_iterator& left, const UTFString::_const_fwd_iterator& right ) {
		return left.mIter >= right.mIter;
	}

	// (const) reverse iterator common operators
	// NB: many of these operations are evaluated in reverse because this is a reverse iterator wrapping a forward iterator
	inline UTFString::size_type operator-( const UTFString::_const_rev_iterator& left, const UTFString::_const_rev_iterator& right ) {
		return ( right.mIter - left.mIter );
	}
	inline bool operator==( const UTFString::_const_rev_iterator& left, const UTFString::_const_rev_iterator& right ) {
		return left.mIter == right.mIter;
	}
	inline bool operator!=( const UTFString::_const_rev_iterator& left, const UTFString::_const_rev_iterator& right ) {
		return left.mIter != right.mIter;
	}
	inline bool operator<( const UTFString::_const_rev_iterator& left, const UTFString::_const_rev_iterator& right ) {
		return right.mIter < left.mIter;
	}
	inline bool operator<=( const UTFString::_const_rev_iterator& left, const UTFString::_const_rev_iterator& right ) {
		return right.mIter <= left.mIter;
	}
	inline bool operator>( const UTFString::_const_rev_iterator& left, const UTFString::_const_rev_iterator& right ) {
		return right.mIter > left.mIter;
	}
	inline bool operator>=( const UTFString::_const_rev_iterator& left, const UTFString::_const_rev_iterator& right ) {
		return right.mIter >= left.mIter;
	}


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
