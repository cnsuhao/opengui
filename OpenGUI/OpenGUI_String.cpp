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
	void UTF8String::_init() {
		m_buffer.mVoidBuffer = 0;
		m_bufferType = none;
	}
	//#########################################################################
	void UTF8String::_cleanBuffer() {
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
				delete m_buffer.mCStrBuffer;
				break;
				// under the worse of circumstances, this is all we can really do
			case none:
			default:
				delete m_buffer.mVoidBuffer;
				break;
			}
			m_buffer.mVoidBuffer = 0;
		}
	}
	//#########################################################################
	void UTF8String::_append( const std::string& str ) {
		mData.append( str );
	}
	//#########################################################################
	void UTF8String::_assign( const std::string& str ) {
		mData = str;
	}
	//#########################################################################
	bool UTF8String::_verifyUTF8( const std::string& str ) {
		std::string::const_iterator i, ie = str.end();
		i = str.begin();

		while ( i != ie ) {
			// characters pass until we find an extended sequence
			if (( *i ) & 0x80 ) {
				// Next step is to determine how many bytes are in the sequence and verify them all.
				// We perform these tests in the order of likelihood (the longer sequences are more rare than the shorter ones)
				byte c = ( *i );

				if (( c & ~_lead1_mask ) == _lead1 ) {
					// 1 additional byte
					if ( c == _lead1 ) return false; // overlong UTF-8 sequence
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) return false; // bad continuation sequence header

				} else if (( c & ~_lead2_mask ) == _lead2 ) {
					// 2 additional bytes
					if ( c == _lead2 ) { // possible overlong UTF-8 sequence
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) return false; // bad continuation sequence header
						if (( c & _lead2 ) == _cont ) return false; // overlong UTF-8 sequence
					} else {
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) return false; // bad continuation sequence header
					}
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) return false; // bad continuation sequence header

				} else if (( c & ~_lead3_mask ) == _lead3 ) {
					// 3 additional bytes
					if ( c == _lead3 ) { // possible overlong UTF-8 sequence
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) return false; // bad continuation sequence header
						if (( c & _lead3 ) == _cont ) return false; // overlong UTF-8 sequence
					} else {
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) return false; // bad continuation sequence header
					}
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) return false; // bad continuation sequence header
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) return false; // bad continuation sequence header

				} else if (( c & ~_lead4_mask ) == _lead4 ) {
					// 4 additional bytes
					if ( c == _lead4 ) { // possible overlong UTF-8 sequence
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) return false; // bad continuation sequence header
						if (( c & _lead4 ) == _cont ) return false; // overlong UTF-8 sequence
					} else {
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) return false; // bad continuation sequence header
					}
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) return false; // bad continuation sequence header
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) return false; // bad continuation sequence header
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) return false; // bad continuation sequence header

				} else if (( c & ~_lead5_mask ) == _lead5 ) {
					// 5 additional bytes
					if ( c == _lead5 ) { // possible overlong UTF-8 sequence
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) return false; // bad continuation sequence header
						if (( c & _lead5 ) == _cont ) return false; // overlong UTF-8 sequence
					} else {
						c = ( *( ++i ) ); // get next byte in sequence
						if (( c & ~_cont_mask ) != _cont ) return false; // bad continuation sequence header
					}
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) return false; // bad continuation sequence header
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) return false; // bad continuation sequence header
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) return false; // bad continuation sequence header
					c = ( *( ++i ) ); // get next byte in sequence
					if (( c & ~_cont_mask ) != _cont ) return false; // bad continuation sequence header

				} else {
					// error condition, invalid lead byte signature
					return false;
				}
			}
			i++;
		}
		return true;
	}
} // namespace OpenGUI{
