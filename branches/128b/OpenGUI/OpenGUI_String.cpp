// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_String.h"

///////////////////////////////////////////////////////////////////////
// just a bunch of UTF-8 constants we'll be using later
#define _lead1      0xC0 //110xxxxx
#define _lead1_mask 0x1F //00011111
#define _lead2      0xE0 //1110xxxx
#define _lead2_mask 0x0F //00001111
#define _lead3      0xF0 //11110xxx
#define _lead3_mask 0x07 //00000111
#define _lead4      0xF8 //111110xx
#define _lead4_mask 0x03 //00000011
#define _lead5      0xFC //1111110x
#define _lead5_mask 0x01 //00000001
#define _cont       0x80 //10xxxxxx
#define _cont_mask  0x3F //00111111

namespace OpenGUI {
	//#########################################################################
	UTFString::UTFString() {
		_init();
	}
	//#########################################################################
	UTFString::~UTFString() {
		_cleanBuffer();
	}
	//#########################################################################
	UTFString::UTFString( const UTFString& copy ) {
		_init();
		mData = copy.mData;
	}
	//#########################################################################
	UTFString::UTFString( size_type length, const code_point& ch ) {
		_init();
		assign( length, ch );
	}
	//#########################################################################
	UTFString::UTFString( const code_point* cp_str ) {
		_init();
		assign( cp_str );
	}
	//#########################################################################
	UTFString::UTFString( const code_point* str, size_type length ) {
		_init();
		assign( str, length );
	}
	//#########################################################################
	UTFString::UTFString( const UTFString& str, size_type index, size_type length ) {
		_init();
		assign( str, index, length );
	}
	//#########################################################################
	UTFString::UTFString( const wchar_t* w_str ) {
		_init();
		assign( w_str );
	}
	//#########################################################################
	UTFString::UTFString( const std::wstring& wstr ) {
		_init();
		assign( wstr );
	}
	//#########################################################################
	UTFString::UTFString( const wchar_t* w_str, size_type length ) {
		_init();
		assign( w_str, length );
	}
	//#########################################################################
	UTFString::UTFString( const char* c_str ) {
		_init();
		assign( c_str );
	}
	//#########################################################################
	UTFString::UTFString( const char* c_str, size_type length ) {
		_init();
		assign( c_str, length );
	}
	//#########################################################################
	UTFString::UTFString( const std::string& str ) {
		_init();
		assign( str );
	}
	//#########################################################################
	UTFString::iterator UTFString::begin() {
		return iterator( mData.begin(), this );
	}
	//#########################################################################
	UTFString::const_iterator UTFString::begin() const {
		dstring& tmp = const_cast<dstring&>( mData );
		return const_iterator( tmp.begin(), const_cast<UTFString*>( this ) );
	}
	//#########################################################################
	UTFString::iterator UTFString::end() {
		return iterator( mData.end(), this );
	}
	//#########################################################################
	UTFString::const_iterator UTFString::end() const {
		dstring& tmp = const_cast<dstring&>( mData );
		return const_iterator( tmp.end(), const_cast<UTFString*>( this ) );
	}
	//#########################################################################
	UTFString::reverse_iterator UTFString::rbegin() {
		return reverse_iterator( mData.rbegin(), this );
	}
	//#########################################################################
	UTFString::const_reverse_iterator UTFString::rbegin() const {
		dstring& tmp = const_cast<dstring&>( mData );
		return reverse_iterator( tmp.rbegin(), const_cast<UTFString*>( this ) );
	}
	//#########################################################################
	UTFString::reverse_iterator UTFString::rend() {
		return const_reverse_iterator( mData.rend(), this );
	}
	//#########################################################################
	UTFString::const_reverse_iterator UTFString::rend() const {
		dstring& tmp = const_cast<dstring&>( mData );
		return const_reverse_iterator( tmp.rend(), const_cast<UTFString*>( this ) );
	}
	//#########################################################################
	UTFString::size_type UTFString::length() const {
		return size();
	}
	//#########################################################################
	UTFString::size_type UTFString::size() const {
		return mData.size();
	}
	//#########################################################################
	UTFString::size_type UTFString::max_size() const {
		return mData.max_size();
	}
	//#########################################################################
	void UTFString::reserve( size_type size ) {
		mData.reserve( size );
	}
	//#########################################################################
	void UTFString::resize( size_type num, const code_point& val ) {
		mData.resize( num, val );
	}
	//#########################################################################
	void UTFString::swap( UTFString& from ) {
		mData.swap( from.mData );
	}
	//#########################################################################
	UTFString& UTFString::assign( iterator start, iterator end ) {
		mData.assign( start.mIter, end.mIter );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::assign( const UTFString& str ) {
		mData.assign( str.mData );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::assign( const code_point* str ) {
		mData.assign( str );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::assign( const code_point* str, size_type num ) {
		mData.assign( str, num );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::assign( const UTFString& str, size_type index, size_type len ) {
		mData.assign( str.mData, index, len );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::assign( size_type num, const code_point& ch ) {
		mData.assign( num, ch );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::assign( const std::wstring& wstr ) {
		const code_point* ptr = ( const code_point* )wstr.c_str();
		mData.assign( ptr );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::assign( const wchar_t* w_str ) {
		const code_point* ptr = ( const code_point* )w_str;
		mData.assign( ptr );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::assign( const wchar_t* w_str, size_type num ) {
		const code_point* ptr = ( const code_point* )w_str;
		mData.assign( ptr, num );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::assign( const std::string& str ) {
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
			utf8len = _utf8_char_length(( unsigned char )( *i ) ); // estimate bytes to load
			for ( size_t j = 0; j < utf8len; j++ ) { // load the needed UTF-8 bytes
				utf8buf[j] = (( unsigned char )( *( i + j ) ) ); // we don't increment 'i' here just in case the estimate is wrong (shouldn't happen, but we're being careful)
			}
			utf8buf[utf8len] = 0; // nul terminate so we throw an exception before running off the end of the buffer
			utf8len = _utf8_to_utf32( utf8buf, uc ); // do the UTF-8 -> UTF-32 conversion
			i += utf8len - 1; // we subtract 1 for the increment of the 'for' loop

			utf16len = _utf32_to_utf16( uc, utf16buff ); // UTF-32 -> UTF-16 conversion
			append( utf16buff, utf16len ); // append the characters to the string
		}
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::assign( const char* c_str ) {
		std::string tmp( c_str );
		return assign( tmp );
	}
	//#########################################################################
	UTFString& UTFString::assign( const char* c_str, size_type num ) {
		std::string tmp;
		tmp.assign( c_str, num );
		return assign( tmp );
	}
	//#########################################################################
	UTFString& UTFString::append( const UTFString& str ) {
		mData.append( str.mData );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::append( const code_point* str ) {
		mData.append( str );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::append( const UTFString& str, size_type index, size_type len ) {
		mData.append( str.mData, index, len );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::append( const code_point* str, size_type num ) {
		mData.append( str, num );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::append( size_type num, code_point ch ) {
		mData.append( num, ch );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::append( const std::wstring& wstr ) {
		UTFString tmp( wstr );
		append( tmp );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::append( const wchar_t* w_str ) {
		std::wstring tmp( w_str );
		return append( tmp );
	}
	//#########################################################################
	UTFString& UTFString::append( const std::wstring& wstr, size_type index, size_type len ) {
		std::wstring tmp( wstr, index, len );
		return append( tmp );
	}
	//#########################################################################
	UTFString& UTFString::append( const wchar_t* w_str, size_type num ) {
		std::wstring tmp( w_str, num );
		return append( tmp );
	}
	//#########################################################################
	UTFString& UTFString::append( size_type num, wchar_t ch ) {
		return append( num, ( code_point )ch );
	}
	//#########################################################################
	UTFString& UTFString::append( iterator start, iterator end ) {
		mData.append( start.mIter, end.mIter );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::append( const std::string& str ) {
		UTFString tmp( str );
		append( tmp );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::append( const char* c_str ) {
		UTFString tmp( c_str );
		append( tmp );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::append( const std::string& str, size_type index, size_type len ) {
		UTFString tmp( str, index, len );
		append( tmp );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::append( const char* c_str, size_type num ) {
		UTFString tmp( c_str, num );
		append( tmp );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::append( size_type num, char ch ) {
		append( num, ( code_point )ch );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::append( size_type num, unicode_char ch ) {
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
	//#########################################################################
	/*! This can be used to push surrogate pair code points, you'll just need to push them
	one after the other. */
	void UTFString::push_back( code_point val ) {
		mData.push_back( val );
	}
	//#########################################################################
	void UTFString::push_back( wchar_t val ) {
		mData.push_back(( code_point )val );
	}
	//#########################################################################
	/*! Limited to characters under the 127 value barrier. */
	void UTFString::push_back( char val ) {
		mData.push_back(( code_point )val );
	}
	//#########################################################################
	void UTFString::push_back( unicode_char val ) {
		code_point cp[2];
		size_t c = _utf32_to_utf16( val, cp );
		if ( c > 0 ) push_back( cp[0] );
		if ( c > 1 ) push_back( cp[1] );
	}

	//#########################################################################
	UTFString::iterator UTFString::insert( iterator i, const code_point& ch ) {
		return iterator( mData.insert( i.mIter, ch ), this );
	}
	//#########################################################################
	UTFString& UTFString::insert( size_type index, const UTFString& str ) {
		mData.insert( index, str.mData );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::insert( size_type index, const code_point* str ) {
		mData.insert( index, str );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::insert( size_type index1, const UTFString& str, size_type index2, size_type num ) {
		mData.insert( index1, str.mData, index2, num );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::insert( size_type index, const code_point* str, size_type num ) {
		mData.insert( index, str, num );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::insert( size_type index, size_type num, code_point ch ) {
		mData.insert( index, num, ch );
		return *this;
	}
	//#########################################################################
	void UTFString::insert( iterator i, size_type num, const code_point& ch ) {
		mData.insert( i.mIter, num, ch );
	}
	//#########################################################################
	void UTFString::insert( iterator i, iterator start, iterator end ) {
		mData.insert( i.mIter, start.mIter, end.mIter );
	}
	//#########################################################################
	UTFString::iterator UTFString::erase( iterator loc ) {
		return iterator( mData.erase( loc.mIter ), this );
	}
	//#########################################################################
	UTFString::iterator UTFString::erase( iterator start, iterator end ) {
		return iterator( mData.erase( start.mIter, end.mIter ), this );
	}
	//#########################################################################
	UTFString& UTFString::erase( size_type index, size_type num ) {
		if ( num == npos )
			mData.erase( index );
		else
			mData.erase( index, num );
		return *this;
	}
	//#########################################################################
	UTFString::code_point& UTFString::at( size_type loc ) {
		return mData.at( loc );
	}
	//#########################################################################
	const UTFString::code_point& UTFString::at( size_type loc ) const {
		return mData.at( loc );
	}
	//#########################################################################
	const UTFString::code_point* UTFString::c_str() const {
		return mData.c_str();
	}
	//#########################################################################
	const UTFString::code_point* UTFString::data() const {
		return c_str();
	}
	//#########################################################################
	UTFString::size_type UTFString::capacity() const {
		return mData.capacity();
	}
	//#########################################################################
	void UTFString::clear() {
		mData.clear();
	}
	//#########################################################################
	int UTFString::compare( const UTFString& str ) {
		return mData.compare( str.mData );
	}
	//#########################################################################
	int UTFString::compare( const code_point* str ) {
		return mData.compare( str );
	}
	//#########################################################################
	int UTFString::compare( size_type index, size_type length, const UTFString& str ) {
		return mData.compare( index, length, str.mData );
	}
	//#########################################################################
	int UTFString::compare( size_type index, size_type length, const UTFString& str, size_type index2, size_type length2 ) {
		return mData.compare( index, length, str.mData, index2, length2 );
	}
	//#########################################################################
	int UTFString::compare( size_type index, size_type length, const code_point* str, size_type length2 ) {
		return mData.compare( index, length, str, length2 );
	}
	//#########################################################################
	bool UTFString::empty() const {
		return mData.empty();
	}
	//#########################################################################

	void UTFString::_init() {
		//mVersion = 0;
		//mLength = 0;
		m_buffer.mVoidBuffer = 0;
		m_bufferType = none;
		m_bufferSize = 0;
	}
	//#########################################################################
	void UTFString::_cleanBuffer() const {
		if ( m_buffer.mVoidBuffer != 0 ) {
			assert( m_bufferType != none ); // this should help catch issues during debug sessions
			switch ( m_bufferType ) {
			case string:
				delete m_buffer.mStrBuffer;
				break;
			case wstring:
				delete m_buffer.mWStrBuffer;
				break;
			case cstring:
				delete[] m_buffer.mCStrBuffer;
				break;
				// under the worse of circumstances, this is all we can really do
			case none:
			default:
				delete m_buffer.mVoidBuffer;
				break;
			}
			m_buffer.mVoidBuffer = 0;
			m_bufferSize = 0;
		}
	}
	//#########################################################################
	void UTFString::_getBufferCStr( size_t len ) const {
		if ( m_bufferType != cstring || m_bufferSize < len ) {
			_cleanBuffer();
			m_buffer.mCStrBuffer = new char[len+1];
			m_buffer.mCStrBuffer[len] = 0;
			m_bufferSize = len;
			m_bufferType = cstring;
		}
	}
	//#########################################################################
	//#########################################################################
	bool UTFString::_utf16_independent_char( code_point cp ) {
		if ( 0xD800 <= cp && cp <= 0xDFFF ) // tests if the cp is within the surrogate pair range
			return false; // it matches a surrogate pair signature
		return true; // everything else is a standalone code point
	}
	//#########################################################################
	bool UTFString::_utf16_surrogate_lead( code_point cp ) {
		if ( 0xD800 <= cp && cp <= 0xDBFF ) // tests if the cp is within the 2nd word of a surrogate pair
			return true; // it is a 1st word
		return false; // it isn't
	}
	//#########################################################################
	bool UTFString::_utf16_surrogate_follow( code_point cp ) {
		if ( 0xDC00 <= cp && cp <= 0xDFFF ) // tests if the cp is within the 2nd word of a surrogate pair
			return true; // it is a 2nd word
		return false; // everything else isn't
	}
	//#########################################################################
	size_t UTFString::_utf16_char_length( code_point cp ) {
		if ( 0xD800 <= cp && cp <= 0xDBFF ) // test if cp is the beginning of a surrogate pair
			return 2; // if it is, then we are 2 words long
		return 1; // otherwise we are only 1 word long
	}
	//#########################################################################
	size_t UTFString::_utf16_char_length( unicode_char uc ) {
		if ( uc > 0xFFFF ) // test if uc is greater than the single word maximum
			return 2; // if so, we need a surrogate pair
		return 1; // otherwise we can stuff it into a single word
	}
	//#########################################################################
	/*! This function does it's best to prevent error conditions, verifying complete
	surrogate pairs before applying the algorithm. In the event that half of a pair
	is found it will happily generate a value in the 0xD800 - 0xDFFF range, which is
	normally an invalid Unicode value but we preserve them for use as sentinel values. */
	size_t UTFString::_utf16_to_utf32( const code_point in_cp[2], unicode_char& out_uc ) {
		const code_point& cp1 = in_cp[0];
		const code_point& cp2 = in_cp[1];
		bool wordPair = false;

		// does it look like a surrogate pair?
		if ( 0xD800 <= cp1 && cp1 <= 0xDBFF ) {
			// looks like one, but does the other half match the algorithm as well?
			if ( 0xDC00 <= cp2 && cp2 <= 0xDFFF )
				wordPair = true; // yep!
		}

		if ( !wordPair ) { // if we aren't a 100% authentic surrogate pair, then just copy the value
			out_uc = cp1;
			return 1;
		}

		unsigned short cU = cp1, cL = cp2; // copy upper and lower words of surrogate pair to writable buffers
		cU -= 0xD800; // remove the encoding markers
		cL -= 0xDC00;

		assert(( cU & ~0x03FF ) == 0 ); // value range assertions
		assert(( cL & ~0x03FF ) == 0 );

		out_uc = ( cU & 0x03FF ) << 10; // grab the 10 upper bits and set them in their proper location
		out_uc |= ( cL & 0x03FF ); // combine in the lower 10 bits
		out_uc += 0x10000; // add back in the value offset

		return 2; // this whole operation takes to words, so that's what we'll return
	}
	//#########################################################################
	/*! This function, like its counterpart, will happily create invalid UTF-16 surrogate pairs. These
	invalid entries will be created for any value of \c in_uc that falls in the range U+D800 - U+DFFF.
	These are generally useful as sentinel values to represent various program specific conditions. */
	size_t UTFString::_utf32_to_utf16( const unicode_char& in_uc, code_point out_cp[2] ) {
		if ( in_uc <= 0xFFFF ) { // we preserve sentinel values because our decoder understands them
			out_cp[0] = in_uc;
			return 1;
		}
		unicode_char uc = in_uc; // copy to writable buffer
		unsigned short tmp; // single code point buffer
		uc -= 0x10000; // subtract value offset

		//process upper word
		tmp = ( uc >> 10 ) & 0x03FF; // grab the upper 10 bits
		tmp += 0xD800; // add encoding offset
		out_cp[0] = tmp; // write

		// process lower word
		tmp = uc & 0x03FF; // grab the lower 10 bits
		tmp += 0xDC00; // add encoding offset
		out_cp[1] = tmp; // write

		return 2; // return used word count (2 for surrogate pairs)
	}
	//#########################################################################
	//#########################################################################
	bool UTFString::_utf8_start_char( unsigned char cp ) {
		return ( cp & ~_cont_mask ) != _cont;
	}
	//#########################################################################
	size_t UTFString::_utf8_char_length( unsigned char cp ) {
		if ( !( cp & 0x80 ) ) return 1;
		if (( cp & ~_lead1_mask ) == _lead1 ) return 2;
		if (( cp & ~_lead2_mask ) == _lead2 ) return 3;
		if (( cp & ~_lead3_mask ) == _lead3 ) return 4;
		if (( cp & ~_lead4_mask ) == _lead4 ) return 5;
		if (( cp & ~_lead5_mask ) == _lead5 ) return 6;
		throw std::range_error( "invalid UTF-8 sequence header value" );
	}
	//#########################################################################
	size_t UTFString::_utf8_char_length( unicode_char uc ) {
		/*
		7 bit:  U-00000000 – U-0000007F: 0xxxxxxx
		11 bit: U-00000080 – U-000007FF: 110xxxxx 10xxxxxx
		16 bit: U-00000800 – U-0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx
		21 bit: U-00010000 – U-001FFFFF: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		26 bit: U-00200000 – U-03FFFFFF: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		31 bit: U-04000000 – U-7FFFFFFF: 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		*/
		if ( !( uc & ~0x0000007F ) ) return 1;
		if ( !( uc & ~0x000007FF ) ) return 2;
		if ( !( uc & ~0x0000FFFF ) ) return 3;
		if ( !( uc & ~0x001FFFFF ) ) return 4;
		if ( !( uc & ~0x03FFFFFF ) ) return 5;
		if ( !( uc & ~0x7FFFFFFF ) ) return 6;
		throw std::range_error( "invalid UTF-8 lead byte" );
	}
	//#########################################################################
	size_t UTFString::_utf8_to_utf32( const unsigned char in_cp[6], unicode_char& out_uc ) {
		size_t len = _utf8_char_length( in_cp[0] );
		if ( len == 1 ) { // if we are only 1 byte long, then just grab it and exit
			out_uc = in_cp[0];
			return 1;
		}

		unicode_char c = 0; // temporary buffer
		size_t i = 0;
		switch ( len ) { // load header byte
		case 6:
			c = in_cp[i] & _lead5_mask;
			break;
		case 5:
			c = in_cp[i] & _lead4_mask;
			break;
		case 4:
			c = in_cp[i] & _lead3_mask;
			break;
		case 3:
			c = in_cp[i] & _lead2_mask;
			break;
		case 2:
			c = in_cp[i] & _lead1_mask;
			break;
		}

		for ( ++i; i < len; i++ ) { // load each continuation byte
			if (( in_cp[i] & ~_cont_mask ) != _cont )
				throw invalid_data( "bad UTF-8 continuation byte" );
			c <<= 6;
			c |= ( in_cp[i] & _cont_mask );
		}

		out_uc = c; // write the final value and return the used byte length
		return len;
	}
	//#########################################################################
	size_t UTFString::_utf32_to_utf8( const unicode_char& in_uc, unsigned char out_cp[6] ) {
		size_t len = _utf8_char_length( in_uc ); // predict byte length of sequence
		unicode_char c = in_uc; // copy to temp buffer

		//stuff all of the lower bits
		for ( size_t i = len - 1; i > 0; i-- ) {
			out_cp[i] = (( c ) & _cont_mask ) | _cont;
			c >>= 6;
		}

		//now write the header byte
		switch ( len ) {
		case 6:
			out_cp[0] = (( c ) & _lead5_mask ) | _lead5;
			break;
		case 5:
			out_cp[0] = (( c ) & _lead4_mask ) | _lead4;
			break;
		case 4:
			out_cp[0] = (( c ) & _lead3_mask ) | _lead3;
			break;
		case 3:
			out_cp[0] = (( c ) & _lead2_mask ) | _lead2;
			break;
		case 2:
			out_cp[0] = (( c ) & _lead1_mask ) | _lead1;
			break;
		case 1:
		default:
			out_cp[0] = ( c ) & 0x7F;
			break;
		}

		// return the byte length of the sequence
		return len;
	}
	//#########################################################################
	UTFString::size_type UTFString::_verifyUTF8( const unsigned char* c_str ) {
		std::string tmp(( char* )c_str );
		return _verifyUTF8( tmp );
	}
	//#########################################################################
	UTFString::size_type UTFString::_verifyUTF8( const std::string& str ) {
		std::string::const_iterator i, ie = str.end();
		i = str.begin();
		size_type length = 0;

		while ( i != ie ) {
			// characters pass until we find an extended sequence
			if (( *i ) & 0x80 ) {
				unsigned char c = ( *i );
				size_t contBytes = 0;

				// get continuation byte count and test for overlong sequences
				if (( c & ~_lead1_mask ) == _lead1 ) { // 1 additional byte
					if ( c == _lead1 ) throw invalid_data( "overlong UTF-8 sequence" );
					contBytes = 1;

				} else if (( c & ~_lead2_mask ) == _lead2 ) { // 2 additional bytes
					contBytes = 2;
					if ( c == _lead2 ) { // possible overlong UTF-8 sequence
						c = ( *( i + 1 ) ); // look ahead to next byte in sequence
						if (( c & _lead2 ) == _cont ) throw invalid_data( "overlong UTF-8 sequence" );
					}

				} else if (( c & ~_lead3_mask ) == _lead3 ) { // 3 additional bytes
					contBytes = 3;
					if ( c == _lead3 ) { // possible overlong UTF-8 sequence
						c = ( *( i + 1 ) ); // look ahead to next byte in sequence
						if (( c & _lead3 ) == _cont ) throw invalid_data( "overlong UTF-8 sequence" );
					}

				} else if (( c & ~_lead4_mask ) == _lead4 ) { // 4 additional bytes
					contBytes = 4;
					if ( c == _lead4 ) { // possible overlong UTF-8 sequence
						c = ( *( i + 1 ) ); // look ahead to next byte in sequence
						if (( c & _lead4 ) == _cont ) throw invalid_data( "overlong UTF-8 sequence" );
					}

				} else if (( c & ~_lead5_mask ) == _lead5 ) { // 5 additional bytes
					contBytes = 5;
					if ( c == _lead5 ) { // possible overlong UTF-8 sequence
						c = ( *( i + 1 ) ); // look ahead to next byte in sequence
						if (( c & _lead5 ) == _cont ) throw invalid_data( "overlong UTF-8 sequence" );
					}
				}

				// check remaining continuation bytes for
				while ( contBytes-- ) {
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont )
						throw invalid_data( "bad continuation sequence header" );
				}
			}
			length++;
			i++;
		}
		return length;
	}
	//#########################################################################
} // namespace OpenGUI{
