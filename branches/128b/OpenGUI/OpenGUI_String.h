// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
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

	=REQUIRED PREPROCESSOR MACROS=
	This class requires two preprocessor macros to be defined in order to
	work as advertised.
	UINT32 - must be mapped to an unsigned 32 bit integer (ex. #define UINT32 unsigned int)
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
#if !(WCHAR_MAX > 0xFFFF) // this is a last resort fall back test WCHAR_MAX is defined in <wchar.h>
#define WCHAR_UTF16 // best we can tell, wchar_t is not larger than 16-bit
#endif // #if !(WCHAR_MAX > 0xFFFF)
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
	code point.)


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
		typedef UINT32 unicode_char;

		//! a single UTF-16 code point
		typedef UINT16 code_point;

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
			_iterator operator+( size_type n ) const {
				_iterator tmp( *this );
				tmp._seekFwd( n );
				return tmp;
			}
			//! addition operator
			_iterator operator+( difference_type n ) const {
				_iterator tmp( *this );
				if ( n < 0 )
					tmp._seekRev( n );
				else
					tmp._seekFwd( n );
				return tmp;
			}
			//! subtraction operator
			_iterator operator-( size_type n ) const {
				_iterator tmp( *this );
				tmp._seekRev( n );
				return tmp;
			}
			//! subtraction operator
			_iterator operator-( difference_type n ) const {
				_iterator tmp( *this );
				if ( n < 0 )
					tmp._seekFwd( n );
				else
					tmp._seekRev( n );
				return tmp;
			}

			//! addition assignment operator
			_iterator& operator+=( size_type n ) const {
				_seekFwd( n );
				return const_cast<_iterator&>( *this );
			}
			//! addition assignment operator
			_iterator& operator+=( difference_type n ) const {
				if ( n < 0 )
					_seekRev( n );
				else
					_seekFwd( n );
				return const_cast<_iterator&>( *this );
			}
			//! subtraction assignment operator
			_iterator& operator-=( size_type n ) const {
				_seekRev( n );
				return const_cast<_iterator&>( *this );
			}
			//! subtraction assignment operator
			_iterator& operator-=( difference_type n ) const {
				if ( n < 0 )
					_seekFwd( n );
				else
					_seekRev( n );
				return const_cast<_iterator&>( *this );
			}

			//! difference operator
			size_type operator-( const _iterator& right ) const {
				return ( mIter - right.mIter );
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
			reference operator[]( size_type n ) {
				_iterator tmp( *this );
				tmp += n;
				return tmp.operator*();
			}
			//! dereference at offset operator
			const_reference operator[]( size_type n ) const {
				_iterator tmp( *this );
				tmp += n;
				return tmp.operator*();
			}
			//! dereference at offset operator
			reference operator[]( difference_type n ) {
				_iterator tmp( *this );
				tmp += n;
				return tmp.operator*();
			}
			//! dereference at offset operator
			const_reference operator[]( difference_type n ) const {
				_iterator tmp( *this );
				tmp += n;
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
			//! less than
			bool operator<( const _iterator& right ) const {
				return mIter < right.mIter;
			}
			//! less than or equal
			bool operator<=( const _iterator& right ) const {
				return mIter <= right.mIter;
			}
			//! greater than
			bool operator>( const _iterator& right ) const {
				return mIter > right.mIter;
			}
			//! greater than or equal
			bool operator>=( const _iterator& right ) const {
				return mIter >= right.mIter;
			}
			//! Returns the Unicode value of the character at the current position (decodes surrogate pairs if needed)
			unicode_char getCharacter() const {
				size_type current_index = _get_index( mIter );
				return mString->getChar( current_index );
			}
			//! Sets the Unicode value of the character at the current position (adding a surrogate pair if needed); returns the amount of string length change caused by the operation
			int setCharacter( unicode_char uc ) {
				size_type current_index = _get_index( mIter );
				int change = mString->setChar( current_index, uc );
				_jump_to( mIter, current_index );
				return change;
			}

			//! advances to the next Unicode character, honoring surrogate pairs in the UTF-16 stream
			_iterator& moveNext() {
				operator++(); // move 1 code point
				if ( _test_end( mIter ) ) return *this; // exit if we hit the end
				if ( _utf16_surrogate_follow( mIter[0] ) ) {
					// landing on a follow code point means we might be part of a bigger character
					// so we test for that
					code_point lead_half = 0;
					try { // we need to try/catch here in case we test outside the range of the string
						lead_half = mIter[-_inc_value( *this )]; // check the previous character to see if we're part of a surrogate pair
						if ( _utf16_surrogate_lead( lead_half ) ) {
							operator++(); // for both forward and reverse iterators, this will always result in the correct location
						}
					} catch ( ... ) {
						return *this; // if something threw, then we'll just stay where we are
					}
				}
				return *this;
			}
			//! rewinds to the previous Unicode character, honoring surrogate pairs in the UTF-16 stream
			_iterator& movePrev() {
				operator--(); // move 1 code point
				if ( _test_begin( mIter ) ) return *this; // exit if we hit the beginning
				if ( _utf16_surrogate_follow( mIter[0] ) ) {
					// landing on a follow code point means we might be part of a bigger character
					// so we test for that
					code_point lead_half = 0;
					try { // we need to try/catch here in case we test outside the range of the string
						lead_half = mIter[-_inc_value( *this )]; // check the previous character to see if we're part of a surrogate pair
						if ( _utf16_surrogate_lead( lead_half ) ) {
							operator--(); // for both forward and reverse iterators, this will always result in the correct location
						}
					} catch ( ... ) {
						return *this; // if something threw, then we'll just stay where we are
					}
				}
				return *this;
			}



		protected:
			_iterator( const ITER_TYPE& init, UTFString* utfstr ) {
				mIter = init;
				mString = utfstr;
			}
		private:
			void _seekFwd( size_type c ) const {
				ITER_TYPE& iter = const_cast<ITER_TYPE&>( mIter );
				iter += c;
			}
			void _seekRev( size_type c ) const {
				ITER_TYPE& iter = const_cast<ITER_TYPE&>( mIter );
				iter -= c;
			}

			// specializations for testing if _iter is at the beginning of the string
			template <class T>
			bool _test_begin( const T& ) const {
				throw std::exception( "invalid iterator type for operation" );
			}
			template<> bool _test_begin<UTFString::dstring::iterator>( const dstring::iterator& _iter ) const {
				return _iter == mString->mData.begin();
			}
			template<> bool _test_begin<UTFString::dstring::reverse_iterator>( const dstring::reverse_iterator& _iter ) const {
				return _iter == mString->mData.rbegin();
			}

			// specializations for testing if _iter is at the end of the string
			template <class T>
			bool _test_end( const T& ) const {
				throw std::exception( "invalid iterator type for operation" );
			}
			template<> bool _test_end<UTFString::dstring::iterator>( const dstring::iterator& _iter ) const {
				return _iter == mString->mData.end();
			}
			template<> bool _test_end<UTFString::dstring::reverse_iterator>( const dstring::reverse_iterator& _iter ) const {
				return _iter == mString->mData.rend();
			}

			// specializations for determining true increment direction regardless of iterator type
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

			// specialization to retrieve current index
			template <class T>
			size_type _get_index( const T& ) const {
				throw std::exception( "invalid iterator type for operation" );
			}
			template<> size_type _get_index<UTFString::dstring::iterator>( const dstring::iterator& _iter ) const {
				return mIter - mString->mData.begin();
			}
			template<> size_type _get_index<UTFString::dstring::reverse_iterator>( const dstring::reverse_iterator& _iter ) const {
				return ( mIter - mString->mData.rend() ) - 1;
			}

			// specialization to jump to a given index from the string's beginning
			template <class T>
			void _jump_to( T&, size_type ) const {
				throw std::exception( "invalid iterator type for operation" );
			}
			template<> void _jump_to<UTFString::dstring::iterator>( dstring::iterator& _iter, size_type index ) const {
				_iter = mString->mData.begin() + index;
			}
			template<> void _jump_to<UTFString::dstring::reverse_iterator>( dstring::reverse_iterator& _iter, size_type index ) const {
				_iter = mString->mData.rend() - ( index + 1 );
			}

			ITER_TYPE mIter;
			UTFString* mString;
		};

		typedef _iterator<dstring::iterator> iterator;                 //!< iterator
		typedef _iterator<dstring::reverse_iterator> reverse_iterator; //!< reverse iterator
		typedef const iterator const_iterator;                         //!< const iterator
		typedef const reverse_iterator const_reverse_iterator;         //!< const reverse iterator


		//!\name Constructors/Destructor
		//@{
		//! default constructor, creates an empty string
		UTFString();
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
		//! destructor
		~UTFString();
		//@}

		//!\name Utility functions
		//@{
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
		//! returns \c true if the string has no elements, \c false otherwise
		bool empty() const;
		//! returns a const pointer to a regular C string, identical to the current string
		const code_point* c_str() const;
		//! returns a pointer to the first character in the current string
		const code_point* data() const;
		//! returns the number of elements that the string can hold before it will need to allocate more space
		size_type capacity() const;
		//! deletes all of the elements in the string
		void clear();
		//! returns a substring of the current string, starting at \a index, and \a num characters long.
		/*! If \a num is omitted, it will default to \c UTFString::npos, and the substr() function will simply return the remainder of the string starting at \a index. */
		UTFString substr( size_type index, size_type num = npos );
		//! appends \a val to the end of the string
		void push_back( unicode_char val );
		//! appends \a val to the end of the string
		void push_back( wchar_t val );
		//! appends \a val to the end of the string
		void push_back( code_point val );
		//! appends \a val to the end of the string
		void push_back( char val );
		//! returns \c true if the given Unicode character is in this string
		bool inString( unicode_char ch ) const;
		//@}

		//!\name Single Character Access
		//@{
		//! returns a reference to the element in the string at index \c loc
		code_point& at( size_type loc );
		//! returns a reference to the element in the string at index \c loc
		const code_point& at( size_type loc ) const;
		//! returns the data point \a loc evaluated as a UTF-32 value
		/*! This function will will only properly decode surrogate pairs when \a loc points to the index
		of a lead code point that is followed by a trailing code point. Evaluating the trailing code point
		itself, or pointing to a code point that is a sentinel value (part of a broken pair) will return
		the value of just that code point (not a valid Unicode value, but useful as a sentinel value). */
		unicode_char getChar( size_type loc ) const;
		//! sets the value of the character at \a loc to the Unicode value \a ch (UTF-32)
		/*! Providing sentinel values (values between U+D800-U+DFFF) are accepted, but you should be aware
		that you can also unwittingly create a valid surrogate pair if you don't pay attention to what you
		are doing. \note This operation may also lengthen the string if a surrogate pair is needed to
		represent the value given, but one is not available to replace; or alternatively shorten the string
		if an existing surrogate pair is replaced with a character that is representable without a surrogate
		pair. The return value will signify any lengthening or shortening performed, returning 0 if no change
		was made, -1 if the string was shortened, or 1 if the string was lengthened. Any single call can
		only change the string length by + or - 1. */
		int setChar( size_type loc, unicode_char ch );
		//@}

		//!\name iterator acquisition
		//@{
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
		//@}

		//!\name assign
		//@{
		//! gives the current string the values from \a start to \a end
		UTFString& assign( iterator start, iterator end );
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
		//@}

		//!\name append
		//@{
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
		//! appends the sequence denoted by \a start and \a end on to the end of the current string
		UTFString& append( iterator start, iterator end );
		//! appends \c num characters of \c str on to the end of the current string
		UTFString& append( const wchar_t* w_str, size_type num );
		//! appends \c num repetitions of \c ch on to the end of the current string
		UTFString& append( size_type num, wchar_t ch );
		//! appends \c num characters of \c str on to the end of the current string  (UTF-8 encoding)
		UTFString& append( const char* c_str, size_type num );
		//! appends \c num repetitions of \c ch on to the end of the current string (Unicode values less than 128)
		UTFString& append( size_type num, char ch );
		//! appends \c num repetitions of \c ch on to the end of the current string (Full Unicode spectrum)
		UTFString& append( size_type num, unicode_char ch );
		//@}


		//!\name insert
		//@{
		//! inserts \a ch before the code point denoted by \a i
		iterator insert( iterator i, const code_point& ch );
		//! inserts \a str into the current string, at location \a index
		UTFString& insert( size_type index, const UTFString& str );
		//! inserts \a str into the current string, at location \a index
		UTFString& insert( size_type index, const code_point* str );
		//! inserts a substring of \a str (starting at \a index2 and \a num characters long) into the current string, at location \a index1
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
		//! removes the characters between \a start and \a end (including the one at \a start but not the one at \a end), returning an iterator to the character after the last character removed
		iterator erase( iterator start, iterator end );
		//! removes \a num characters from the current string, starting at \a index
		UTFString& erase( size_type index = 0, size_type num = npos );
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
		//! returns the index of the first character within the current string that does not match \a, starting the search at \a index; returns \c UTFString::npos if nothing is found
		size_type find_first_not_of( code_point ch, size_type index = 0 );
		//! returns the index of the first character within the current string that does not match \a, starting the search at \a index; returns \c UTFString::npos if nothing is found
		size_type find_first_not_of( char ch, size_type index = 0 );
		//! returns the index of the first character within the current string that does not match \a, starting the search at \a index; returns \c UTFString::npos if nothing is found
		size_type find_first_not_of( wchar_t ch, size_type index = 0 );
		//! returns the index of the first character within the current string that does not match \a, starting the search at \a index; returns \c UTFString::npos if nothing is found
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
		//@}


		//!\name UTF-16 encoding/decoding
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
		static size_type _verifyUTF8( const unsigned char* c_str );
		//! verifies a UTF-8 stream, returning the total number of Unicode characters found
		static size_type _verifyUTF8( const std::string& str );
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
