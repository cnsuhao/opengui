// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_String.h"

///////////////////////////////////////////////////////////////////////
// just a bunch of constants we'll be using later. Should probably turn them into macros to force proper inlining
typedef unsigned char byte; // 1 byte ;-)
const byte _lead1      = 0xC0; //110xxxxx
const byte _lead1_mask = 0x1F; //00011111
const byte _lead2      = 0xE0; //1110xxxx
const byte _lead2_mask = 0x0F; //00001111
const byte _lead3      = 0xF0; //11110xxx
const byte _lead3_mask = 0x07; //00000111
const byte _lead4      = 0xF8; //111110xx
const byte _lead4_mask = 0x03; //00000011
const byte _lead5      = 0xFC; //1111110x
const byte _lead5_mask = 0x01; //00000001
const byte _cont       = 0x80; //10xxxxxx
const byte _cont_mask  = 0x3F; //00111111

namespace OpenGUI {
	//#########################################################################
	const UTF8String::size_type UTF8String::npos = ~0;
	//#########################################################################
	UTF8String::UTF8String() {
		_init();
	}
	//#########################################################################
	UTF8String::~UTF8String() {
		_cleanBuffer();
	}
	//#########################################################################
	UTF8String::UTF8String( const UTF8String& copy ) {
		_init();
		mData = copy.mData;
		mLength = copy.mLength;
	}
	//#########################################################################
	UTF8String::UTF8String( const char* cstr ) {
		_init();
		mData = ( const data_point* )cstr;
		try {
			mLength = _verifyUTF8();
		} catch ( invalid_data& ) {
			mData.clear();
			mLength = 0;
			_cleanBuffer();
			invalid_data( "initializer string failed UTF-8 validity test" );
		}
	}
	//#########################################################################
	UTF8String::UTF8String( const std::string& str ) {
		_init();
		mData = ( const data_point* )str.c_str();
		try {
			mLength = _verifyUTF8();
		} catch ( invalid_data& ) {
			mData.clear();
			mLength = 0;
			_cleanBuffer();
			invalid_data( "initializer string failed UTF-8 validity test" );
		}
	}
	//#########################################################################
	UTF8String::UTF8String( const std::wstring& wstr ) {
		_init();
		mLength = _loadWString( wstr, mData );
	}
	//#########################################################################
	void UTF8String::clear() {
		mData.clear();
		mLength = 0;
		_cleanBuffer();
	}
	//#########################################################################
	UTF8String::iterator UTF8String::begin() {
		return iterator( mData.begin() );
	}
	//#########################################################################
	UTF8String::iterator UTF8String::end() {
		return iterator( mData.end() );
	}
	//#########################################################################
	void UTF8String::_init() {
		mLength = 0;
		m_buffer.mVoidBuffer = 0;
		m_bufferType = none;
		m_bufferSize = 0;
	}
	//#########################################################################
	void UTF8String::_cleanBuffer() const {
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
	void UTF8String::_getBufferCStr( size_t len ) const {
		if ( m_bufferType != cstring || m_bufferSize < len ) {
			_cleanBuffer();
			m_buffer.mCStrBuffer = new char[len+1];
			m_buffer.mCStrBuffer[len] = 0;
			m_bufferSize = len;
			m_bufferType = cstring;
		}
	}
	//#########################################################################
	void UTF8String::_append( const ustring& str ) {
		mData.append( str );
	}
	//#########################################################################
	void UTF8String::_assign( const ustring& str ) {
		mData = str;
	}
	//#########################################################################
	void UTF8String::_utf16_to_utf32( const code_point& c, code_point& c_out ) {
		unsigned short wU, wL;
		if ( c > 0xFFFF ) {
			wU = c >> 16;
			wL = c & 0xFFFF;
		} else {
			// just store the lower word
			wU = 0;
			wL = c & 0xFFFF;
		}
		if ( wU && 0xD800 <= wU && wU <= 0xDBFF && 0xDC00 <= wL && wL && 0xDFFF ) {
			// valid surrogate pair, time to decode
			wU -= 0xD800; // remove the encoding marker
			wL -= 0xDC00; // remove the encoding marker
			assert(( wU & ~0x03FF ) == 0 );
			assert(( wL & ~0x03FF ) == 0 );
			c_out = ( wU & 0x03FF ) << 10;
			c_out |= ( wL & 0x03FF );
			c_out += 0x10000;
			return;
		}
		if ( 0xD800 <= wL && wL <= 0xDFFF ) {
			throw std::range_error( "invalid UTF-16 single point value, not a valid surrogate pair but falls in that range" );
		}
		c_out = wL;
	}
	//#########################################################################
	void UTF8String::_utf32_to_utf16( const code_point& c, code_point& c_out ) {
		if ( c > 0xFFFF ) {
			// we're over the single point limit, so we need to generate surrogate pairs
			code_point v = c - 0x10000;
			unsigned short vh, vl; // higher and lower 10 bits
			vh = ( v >> 10 ) & 0x03FF;
			vl = v & 0x03FF;
			vh |= 0xD800; // add encoding marker
			vl |= 0xDC00; // add encoding marker
			c_out = vh << 16;
			c_out |= vl & 0xFFFF;
		} else {
			// we actually fit into 16 bits, so just write it and move on
			c_out = c;
		}
	}
	//#########################################################################
	void UTF8String::_utf32_to_utf8( code_point c, ustring& out ) const {
		size_t len = _predictBytes( c );
		_getBufferCStr( len );

		//stuff all of the lower bits
		for ( size_t i = len - 1;i > 0; i-- ) {
			m_buffer.mCStrBuffer[i] = ((( byte )c ) & _cont_mask ) | _cont;
			c >>= 6;
		}

		//now write the final bits
		switch ( len ) {
		case 6:
			m_buffer.mCStrBuffer[0] = ((( byte )c ) & _lead5_mask ) | _lead5;
			break;
		case 5:
			m_buffer.mCStrBuffer[0] = ((( byte )c ) & _lead4_mask ) | _lead4;
			break;
		case 4:
			m_buffer.mCStrBuffer[0] = ((( byte )c ) & _lead3_mask ) | _lead3;
			break;
		case 3:
			m_buffer.mCStrBuffer[0] = ((( byte )c ) & _lead2_mask ) | _lead2;
			break;
		case 2:
			m_buffer.mCStrBuffer[0] = ((( byte )c ) & _lead1_mask ) | _lead1;
			break;
		case 1:
		default:
			m_buffer.mCStrBuffer[0] = (( byte )c ) & 0x7F;
			break;
		}

		// and append the result to the given ustring
		out.append(( byte* )m_buffer.mCStrBuffer, len );
	}
	//#########################################################################
	/*! This function is completely unprotected against buffer overflows.
	So don't use it on data you don't trust. */
	UTF8String::code_point UTF8String::_utf8_to_utf32( const data_point* utf8_str ) {
		code_point v = 0;
		size_t len = _getSequenceLen( utf8_str[0] );
		v = utf8_str[0];
		switch ( len ) {
		case 6:
			v = utf8_str[0] & _lead5_mask;
			break;
		case 5:
			v = utf8_str[0] & _lead4_mask;
			break;
		case 4:
			v = utf8_str[0] & _lead3_mask;
			break;
		case 3:
			v = utf8_str[0] & _lead2_mask;
			break;
		case 2:
			v = utf8_str[0] & _lead1_mask;
			break;
		case 1:
		default:
			break; //do nothing
		}
		for ( size_t i = 1; i < len; i++ ) {
			v <<= 6;
			v |= ( utf8_str[i] & _cont_mask );
		}
		return v;
	}
	//#########################################################################
	size_t UTF8String::_getSequenceLen( const data_point& s ) {
		if ( !( s & 0x80 ) ) return 1;
		if (( byte )( s & ~_lead1_mask ) == _lead1 ) return 2;
		if (( byte )( s & ~_lead2_mask ) == _lead2 ) return 3;
		if (( byte )( s & ~_lead3_mask ) == _lead3 ) return 4;
		if (( byte )( s & ~_lead4_mask ) == _lead4 ) return 5;
		if (( byte )( s & ~_lead5_mask ) == _lead5 ) return 6;
		throw std::range_error( "invalid UTF-8 sequence header value" );
	}
	//#########################################################################
	size_t UTF8String::_predictBytes( const code_point& c ) {
		/*
		7 bit:  U-00000000 – U-0000007F: 0xxxxxxx
		11 bit: U-00000080 – U-000007FF: 110xxxxx 10xxxxxx
		16 bit: U-00000800 – U-0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx
		21 bit: U-00010000 – U-001FFFFF: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		26 bit: U-00200000 – U-03FFFFFF: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		31 bit: U-04000000 – U-7FFFFFFF: 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		*/
		if ( !( c & ~0x0000007F ) ) return 1;
		if ( !( c & ~0x000007FF ) ) return 2;
		if ( !( c & ~0x0000FFFF ) ) return 3;
		if ( !( c & ~0x001FFFFF ) ) return 4;
		if ( !( c & ~0x03FFFFFF ) ) return 5;
		if ( !( c & ~0x7FFFFFFF ) ) return 6;
		throw std::range_error( "invalid code_point value" );
	}
	//#########################################################################
	UTF8String::size_type UTF8String::_verifyUTF8( const ustring& str ) {
		ustring::const_iterator i, ie = str.end();
		i = str.begin();
		size_type length = 0;

		while ( i != ie ) {
			// characters pass until we find an extended sequence
			if (( *i ) & 0x80 ) {
				// Next step is to determine how many bytes are in the sequence and verify them all.
				// We perform these tests in the order of likelihood (the longer sequences are more rare than the shorter ones)
				byte c = ( *i );

				if (( c & ~_lead1_mask ) == _lead1 ) {
					// 1 additional byte
					if ( c == _lead1 ) throw invalid_data( "overlong UTF-8 sequence" );
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );

				} else if (( c & ~_lead2_mask ) == _lead2 ) {
					// 2 additional bytes
					if ( c == _lead2 ) { // possible overlong UTF-8 sequence
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
						if (( c & _lead2 ) == _cont ) throw invalid_data( "overlong UTF-8 sequence" );
					} else {
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
					}
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );

				} else if (( c & ~_lead3_mask ) == _lead3 ) {
					// 3 additional bytes
					if ( c == _lead3 ) { // possible overlong UTF-8 sequence
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
						if (( c & _lead3 ) == _cont ) throw invalid_data( "overlong UTF-8 sequence" );
					} else {
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
					}
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );

				} else if (( c & ~_lead4_mask ) == _lead4 ) {
					// 4 additional bytes
					if ( c == _lead4 ) { // possible overlong UTF-8 sequence
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
						if (( c & _lead4 ) == _cont ) throw invalid_data( "overlong UTF-8 sequence" );
					} else {
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
					}
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );

				} else if (( c & ~_lead5_mask ) == _lead5 ) {
					// 5 additional bytes
					if ( c == _lead5 ) { // possible overlong UTF-8 sequence
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
						if (( c & _lead5 ) == _cont ) throw invalid_data( "overlong UTF-8 sequence" );
					} else {
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
					}
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );

				} else {
					// error condition, invalid lead byte signature
					throw invalid_data( "invalid lead byte signature" );
				}
			}
			length++;
			i++;
		}
		return length;
	}
	//#########################################################################
	UTF8String::size_type UTF8String::_verifyUTF8( const std::string& str ) {
		std::string::const_iterator i, ie = str.end();
		i = str.begin();
		size_type length = 0;

		while ( i != ie ) {
			// characters pass until we find an extended sequence
			if (( *i ) & 0x80 ) {
				// Next step is to determine how many bytes are in the sequence and verify them all.
				// We perform these tests in the order of likelihood (the longer sequences are more rare than the shorter ones)
				byte c = ( *i );

				if (( c & ~_lead1_mask ) == _lead1 ) {
					// 1 additional byte
					if ( c == _lead1 ) throw invalid_data( "overlong UTF-8 sequence" );
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );

				} else if (( c & ~_lead2_mask ) == _lead2 ) {
					// 2 additional bytes
					if ( c == _lead2 ) { // possible overlong UTF-8 sequence
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
						if (( c & _lead2 ) == _cont ) throw invalid_data( "overlong UTF-8 sequence" );
					} else {
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
					}
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );

				} else if (( c & ~_lead3_mask ) == _lead3 ) {
					// 3 additional bytes
					if ( c == _lead3 ) { // possible overlong UTF-8 sequence
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
						if (( c & _lead3 ) == _cont ) throw invalid_data( "overlong UTF-8 sequence" );
					} else {
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
					}
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );

				} else if (( c & ~_lead4_mask ) == _lead4 ) {
					// 4 additional bytes
					if ( c == _lead4 ) { // possible overlong UTF-8 sequence
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
						if (( c & _lead4 ) == _cont ) throw invalid_data( "overlong UTF-8 sequence" );
					} else {
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
					}
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );

				} else if (( c & ~_lead5_mask ) == _lead5 ) {
					// 5 additional bytes
					if ( c == _lead5 ) { // possible overlong UTF-8 sequence
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
						if (( c & _lead5 ) == _cont ) throw invalid_data( "overlong UTF-8 sequence" );
					} else {
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
					}
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) throw invalid_data( "bad continuation sequence header" );

				} else {
					// error condition, invalid lead byte signature
					throw invalid_data( "invalid lead byte signature" );
				}
			}
			length++;
			i++;
		}
		return length;
	}
	//#########################################################################
	UTF8String::size_type UTF8String::_loadWString( const std::wstring& in_wstr, ustring& out_ustr ) const {
		std::wstring::const_iterator i, ie = in_wstr.end();
		out_ustr.reserve( out_ustr.length() + in_wstr.length() ); // reserve a logical guess worth of space
		size_type length = 0;
		i = in_wstr.begin();
		while ( i != ie ) {
			wchar_t w;
			w = ( *i );
			code_point cp;
			if ( 0xD800 <= w && w <= 0xDBFF ) {
				// surrogate pair
				cp = w << 16;
				i++;
				w = ( *i );
				cp |= w;
			} else {
				// just a single character
				cp = w;
			}
			code_point cp2;
			_utf16_to_utf32( cp, cp2 );
			_utf32_to_utf8( cp2, out_ustr );
			length++;
			i++;
		}
		return length;
	}
	//#########################################################################
	bool UTF8String::_isContByte( const data_point& s ) {
		return ( s & ~_cont_mask ) == _cont;
	}
	//#########################################################################
} // namespace OpenGUI{
