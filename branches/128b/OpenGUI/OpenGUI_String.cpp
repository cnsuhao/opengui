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
	//##################
	//#########################################################################
	//#########################################################################
	UTFString::iterator UTFString::insert( iterator i, const code_point& ch ) {
		iterator ret;
		ret.mIter = mData.insert( i.mIter, ch );
		ret.mString = this;
		return ret;
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
	UTFString& UTFString::insert( size_type index, const wchar_t* w_str, size_type num ) {
		UTFString tmp( w_str, num );
		insert( index, tmp );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::insert( size_type index, size_type num, unicode_char ch ) {
		code_point cp[3] = {0, 0, 0};
		size_t l = _utf32_to_utf16( ch, cp );
		if ( l == 1 ) {
			return insert( index, num, cp[0] );
		}
		for ( size_type c = 0; c < num; c++ ) {
			// insert in reverse order to preserve ordering after insert
			insert( index, 1, cp[1] );
			insert( index, 1, cp[0] );
		}
		return *this;
	}
	//#########################################################################
	void UTFString::insert( iterator i, size_type num, const unicode_char& ch ) {
		code_point cp[3] = {0, 0, 0};
		size_t l = _utf32_to_utf16( ch, cp );
		if ( l == 1 ) {
			insert( i, num, cp[0] );
		} else {
			for ( size_type c = 0; c < num; c++ ) {
				// insert in reverse order to preserve ordering after insert
				insert( i, 1, cp[1] );
				insert( i, 1, cp[0] );
			}
		}
	}
	//#########################################################################
	UTFString& UTFString::insert( size_type index, size_type num, wchar_t ch ) {
		insert( index, num, ( unicode_char )ch );
		return *this;
	}
	//#########################################################################
	void UTFString::insert( iterator i, size_type num, const wchar_t& ch ) {
		insert( i, num, ( unicode_char )ch );
	}
	//#########################################################################
	UTFString& UTFString::insert( size_type index, const char* c_str, size_type num ) {
		UTFString tmp( c_str, num );
		insert( index, tmp );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::insert( size_type index, size_type num, char ch ) {
		insert( index, num, ( code_point )ch );
		return *this;
	}
	//#########################################################################
	void UTFString::insert( iterator i, size_type num, const char& ch ) {
		insert( i, num, ( code_point )ch );
	}
	//#########################################################################
	//#########################################################################
	UTFString::iterator UTFString::erase( iterator loc ) {
		iterator ret;
		ret.mIter = mData.erase( loc.mIter );
		ret.mString = this;
		return ret;
	}
	//#########################################################################
	UTFString::iterator UTFString::erase( iterator start, iterator end ) {
		iterator ret;
		ret.mIter = mData.erase( start.mIter, end.mIter );
		ret.mString = this;
		return ret;
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
	UTFString& UTFString::replace( size_type index1, size_type num1, const UTFString& str ) {
		mData.replace( index1, num1, str.mData, 0, npos );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::replace( size_type index1, size_type num1, const UTFString& str, size_type num2 ) {
		mData.replace( index1, num1, str.mData, 0, num2 );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::replace( size_type index1, size_type num1, const UTFString& str, size_type index2, size_type num2 ) {
		mData.replace( index1, num1, str.mData, index2, num2 );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::replace( iterator start, iterator end, const UTFString& str, size_type num ) {
		size_type index1 = begin() - start;
		size_type num1 = end - start;
		return replace( index1, num1, str, 0, num );
	}
	//#########################################################################
	UTFString& UTFString::replace( size_type index, size_type num1, size_type num2, code_point ch ) {
		mData.replace( index, num1, num2, ch );
		return *this;
	}
	//#########################################################################
	UTFString& UTFString::replace( iterator start, iterator end, size_type num, code_point ch ) {
		size_type index1 = begin() - start;
		size_type num1 = end - start;
		return replace( index1, num1, num, ch );
	}
	//##############################################################
	//############################################### 
	//#####################
	//#########################################################################
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
	int UTFString::compare( size_type index, size_type length, const wchar_t* w_str, size_type length2 ) {
		UTFString tmp( w_str, length2 );
		return compare( index, length, tmp );
	}
	//#########################################################################
	int UTFString::compare( size_type index, size_type length, const char* c_str, size_type length2 ) {
		UTFString tmp( c_str, length2 );
		return compare( index, length, tmp );
	}
	//##########################
	//#########################################################################
	//#########################################################################
	UTFString::size_type UTFString::find( const UTFString& str, size_type index ) {
		return mData.find( str.c_str(), index );
	}
	//#########################################################################
	UTFString::size_type UTFString::find( const code_point* cp_str, size_type index, size_type length ) {
		UTFString tmp( cp_str );
		return mData.find( tmp.c_str(), index, length );
	}
	//#########################################################################
	UTFString::size_type UTFString::find( const char* c_str, size_type index, size_type length ) {
		UTFString tmp( c_str );
		return mData.find( tmp.c_str(), index, length );
	}
	//#########################################################################
	UTFString::size_type UTFString::find( const wchar_t* w_str, size_type index, size_type length ) {
		UTFString tmp( w_str );
		return mData.find( tmp.c_str(), index, length );
	}
	//#########################################################################
	UTFString::size_type UTFString::find( code_point ch, size_type index ) {
		return mData.find( ch, index );
	}
	//#########################################################################
	UTFString::size_type UTFString::find( char ch, size_type index ) {
		return find(( code_point )ch, index );
	}
	//#########################################################################
	UTFString::size_type UTFString::find( wchar_t ch, size_type index ) {
		return find(( unicode_char )ch, index );
	}
	//#########################################################################
	UTFString::size_type UTFString::find( unicode_char ch, size_type index ) {
		code_point cp[3] = {0, 0, 0};
		size_t l = _utf32_to_utf16( ch, cp );
		return find( UTFString( cp, l ), index );
	}
	//#########################################################################
	UTFString::size_type UTFString::rfind( const UTFString& str, size_type index ) {
		return mData.rfind( str.c_str(), index );
	}
	//#########################################################################
	UTFString::size_type UTFString::rfind( const code_point* cp_str, size_type index, size_type num ) {
		UTFString tmp( cp_str );
		return mData.rfind( tmp.c_str(), index, num );
	}
	//#########################################################################
	UTFString::size_type UTFString::rfind( const char* c_str, size_type index, size_type num ) {
		UTFString tmp( c_str );
		return mData.rfind( tmp.c_str(), index, num );
	}
	//#########################################################################
	UTFString::size_type UTFString::rfind( const wchar_t* w_str, size_type index, size_type num ) {
		UTFString tmp( w_str );
		return mData.rfind( tmp.c_str(), index, num );
	}
	//#########################################################################
	UTFString::size_type UTFString::rfind( char ch, size_type index ) {
		return rfind(( code_point )ch, index );
	}
	//#########################################################################
	UTFString::size_type UTFString::rfind( code_point ch, size_type index ) {
		return mData.rfind( ch, index );
	}
	//#########################################################################
	UTFString::size_type UTFString::rfind( wchar_t ch, size_type index ) {
		return rfind(( unicode_char )ch, index );
	}
	//#########################################################################
	UTFString::size_type UTFString::rfind( unicode_char ch, size_type index ) {
		code_point cp[3] = {0, 0, 0};
		size_t l = _utf32_to_utf16( ch, cp );
		return rfind( UTFString( cp, l ), index );
	}
	
	//################################################
	//#########################################################################
	UTFString::size_type UTFString::find_first_of( const UTFString &str, size_type index, size_type num ) {
		size_type i = 0;
		const size_type len = length();
		while ( i < num && ( index + i ) < len ) {
			unicode_char ch = getChar( index + i );
			if ( str.inString( ch ) )
				return index + i;
			i += _utf16_char_length( ch ); // increment by the Unicode character length
		}
		return npos;
	}
	//#########################################################################
	UTFString::size_type UTFString::find_first_of( code_point ch, size_type index ) {
		UTFString tmp;
		tmp.assign( 1, ch );
		return find_first_of( tmp, index );
	}
	//#########################################################################
	UTFString::size_type UTFString::find_first_of( char ch, size_type index ) {
		return find_first_of(( code_point )ch, index );
	}
	//#########################################################################
	UTFString::size_type UTFString::find_first_of( wchar_t ch, size_type index ) {
		return find_first_of(( unicode_char )ch, index );
	}
	//#########################################################################
	UTFString::size_type UTFString::find_first_of( unicode_char ch, size_type index ) {
		code_point cp[3] = {0, 0, 0};
		size_t l = _utf32_to_utf16( ch, cp );
		return find_first_of( UTFString( cp, l ), index );
	}
	//#########################################################################
	UTFString::size_type UTFString::find_first_not_of( const UTFString& str, size_type index, size_type num ) {
		size_type i = 0;
		const size_type len = length();
		while ( i < num && ( index + i ) < len ) {
			unicode_char ch = getChar( index + i );
			if ( !str.inString( ch ) )
				return index + i;
			i += _utf16_char_length( ch ); // increment by the Unicode character length
		}
		return npos;
	}
	//#########################################################################
	UTFString::size_type UTFString::find_first_not_of( code_point ch, size_type index ) {
		UTFString tmp;
		tmp.assign( 1, ch );
		return find_first_not_of( tmp, index );
	}
	//#########################################################################
	UTFString::size_type UTFString::find_first_not_of( char ch, size_type index ) {
		return find_first_not_of(( code_point )ch, index );
	}
	//#########################################################################
	UTFString::size_type UTFString::find_first_not_of( wchar_t ch, size_type index ) {
		return find_first_not_of(( unicode_char )ch, index );
	}
	//#########################################################################
	UTFString::size_type UTFString::find_first_not_of( unicode_char ch, size_type index ) {
		code_point cp[3] = {0, 0, 0};
		size_t l = _utf32_to_utf16( ch, cp );
		return find_first_not_of( UTFString( cp, l ), index );
	}
	//#########################################################################
	UTFString::size_type UTFString::find_last_of( const UTFString& str, size_type index, size_type num ) {
		size_type i = 0;
		const size_type len = length();
		if ( index > len ) index = len - 1;

		while ( i < num && ( index - i ) != npos ) {
			size_type j = index - i;
			// careful to step full Unicode characters
			code_point cur = at( j );
			if ( j != 0 && _utf16_surrogate_follow( at( j ) ) && _utf16_surrogate_lead( at( j - 1 ) ) ) {
				j = index - ++i;
			}
			// and back to the usual dull test
			unicode_char ch = getChar( j );
			if ( str.inString( ch ) )
				return j;
			i++;
		}
		return npos;
	}
	//#########################################################################
	UTFString::size_type UTFString::find_last_of( code_point ch, size_type index ) {
		UTFString tmp;
		tmp.assign( 1, ch );
		return find_last_of( tmp, index );
	}
	//#########################################################################
	UTFString::size_type UTFString::find_last_of( char ch, size_type index ) {
		return find_last_of(( code_point )ch, index );
	}
	//#########################################################################
	UTFString::size_type UTFString::find_last_of( wchar_t ch, size_type index ) {
		return find_last_of(( unicode_char )ch, index );
	}
	//#########################################################################
	UTFString::size_type UTFString::find_last_of( unicode_char ch, size_type index ) {
		code_point cp[3] = {0, 0, 0};
		size_t l = _utf32_to_utf16( ch, cp );
		return find_last_of( UTFString( cp, l ), index );
	}
	//#########################################################################
	UTFString::size_type UTFString::find_last_not_of( const UTFString& str, size_type index , size_type num ) {
		size_type i = 0;
		const size_type len = length();
		if ( index > len ) index = len - 1;

		while ( i < num && ( index - i ) != npos ) {
			size_type j = index - i;
			// careful to step full Unicode characters
			code_point cur = at( j );
			if ( j != 0 && _utf16_surrogate_follow( at( j ) ) && _utf16_surrogate_lead( at( j - 1 ) ) ) {
				j = index - ++i;
			}
			// and back to the usual dull test
			unicode_char ch = getChar( j );
			if ( !str.inString( ch ) )
				return j;
			i++;
		}
		return npos;
	}
	//#########################################################################
	UTFString::size_type UTFString::find_last_not_of( code_point ch, size_type index ) {
		UTFString tmp;
		tmp.assign( 1, ch );
		return find_last_not_of( tmp, index );
	}
	//#########################################################################
	UTFString::size_type UTFString::find_last_not_of( char ch, size_type index ) {
		return find_last_not_of(( code_point )ch, index );
	}
	//#########################################################################
	UTFString::size_type UTFString::find_last_not_of( wchar_t ch, size_type index ) {
		return find_last_not_of(( unicode_char )ch, index );
	}
	//#########################################################################
	UTFString::size_type UTFString::find_last_not_of( unicode_char ch, size_type index ) {
		code_point cp[3] = {0, 0, 0};
		size_t l = _utf32_to_utf16( ch, cp );
		return find_last_not_of( UTFString( cp, l ), index );
	}
	//############################################################### 
	//#######################################################
	//#########################################################################
	void UTFString::_init() {
		m_buffer.mVoidBuffer = 0;
		m_bufferType = bt_none;
		m_bufferSize = 0;
	}
	//#########################################################################
	void UTFString::_cleanBuffer() const {
		if ( m_buffer.mVoidBuffer != 0 ) {
			assert( m_bufferType != bt_none ); // this should help catch issues during debug sessions
			switch ( m_bufferType ) {
			case bt_string:
				delete m_buffer.mStrBuffer;
				break;
			case bt_wstring:
				delete m_buffer.mWStrBuffer;
				break;
			case bt_utf32string:
				delete m_buffer.mUTF32StrBuffer;
				break;
			case bt_none: // under the worse of circumstances, this is all we can do, and hope it works out
			default:
				delete m_buffer.mVoidBuffer;
				break;
			}
			m_buffer.mVoidBuffer = 0;
			m_bufferSize = 0;
		}
	}
	//#########################################################################
	void UTFString::_getBufferStr() const {
		if ( m_bufferType != bt_string ) {
			_cleanBuffer();
			m_buffer.mStrBuffer = new std::string();
			m_bufferType = bt_string;
		}
		m_buffer.mStrBuffer->clear();
	}
	//#########################################################################
	void UTFString::_getBufferWStr() const {
		if ( m_bufferType != bt_wstring ) {
			_cleanBuffer();
			m_buffer.mWStrBuffer = new std::wstring();
			m_bufferType = bt_wstring;
		}
		m_buffer.mWStrBuffer->clear();
	}
	//#########################################################################
	void UTFString::_getBufferUTF32Str() const {
		if ( m_bufferType != bt_utf32string ) {
			_cleanBuffer();
			m_buffer.mUTF32StrBuffer = new utf32string();
			m_bufferType = bt_utf32string;
		}
		m_buffer.mUTF32StrBuffer->clear();
	}
	//#########################################################################
	//#########################################################################
	void UTFString::_load_buffer_UTF8() const {
		_getBufferStr();
		std::string& buffer = ( *m_buffer.mStrBuffer );
		buffer.reserve( length() );

		unsigned char utf8buf[6];
		char* charbuf = ( char* )utf8buf;
		unicode_char c;
		size_t len;

		const_iterator i, ie = end();
		for ( i = begin(); i != ie; i.moveNext() ) {
			c = i.getCharacter();
			len = _utf32_to_utf8( c, utf8buf );
			size_t j = 0;
			while ( j < len )
				buffer.push_back( charbuf[j++] );
		}
	}
	//#########################################################################
	void UTFString::_load_buffer_WStr() const {
		_getBufferWStr();
		std::wstring& buffer = ( *m_buffer.mWStrBuffer );
		buffer.reserve( length() ); // may over reserve, but should be close enough
#ifdef WCHAR_UTF16 // wchar_t matches UTF-16
		const_iterator i, ie = end();
		for ( i = begin(); i != ie; ++i ) {
			buffer.push_back(( wchar_t )( *i ) );
		}
#else // wchar_t fits UTF-32
		unicode_char c;
		const_iterator i, ie = end();
		for ( i = begin(); i != ie; i.moveNext() ) {
			c = i.getCharacter();
			buffer.push_back(( wchar_t )c );
		}
#endif
	}
	//#########################################################################
	void UTFString::_load_buffer_UTF32() const {
		_getBufferUTF32Str();
		utf32string& buffer = ( *m_buffer.mUTF32StrBuffer );
		buffer.reserve( length() ); // may over reserve, but should be close enough

		unicode_char c;

		const_iterator i, ie = end();
		for ( i = begin(); i != ie; i.moveNext() ) {
			c = i.getCharacter();
			buffer.push_back( c );
		}
	}
	//####################################### 
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
	These are generally useful as sentinel values to represent various program specific conditions.
	\note This function will also pass through any single UTF-16 code point without modification,
	making it a safe method of ensuring a stream that is unknown UTF-32 or UTF-16 is truly UTF-16.*/
	size_t UTFString::_utf32_to_utf16( const unicode_char& in_uc, code_point out_cp[2] ) {
		if ( in_uc <= 0xFFFF ) { // we blindly preserve sentinel values because our decoder understands them
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
		throw invalid_data( "invalid UTF-8 sequence header value" );
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
		throw invalid_data( "invalid UTF-32 value" );
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
						throw invalid_data( "bad UTF-8 continuation byte" );
				}
			}
			length++;
			i++;
		}
		return length;
	}
	//#########################################################################
} // namespace OpenGUI{
