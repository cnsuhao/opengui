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
	/*UTFString::UTFString( const char* cstr ) {
		_init();
		assign( cstr );
	}*/
	//#########################################################################
	/*UTFString::UTFString( const std::string& str ) {
		_init();
		assign( str );
	}*/
	//#########################################################################
	UTFString::iterator UTFString::begin() {
		return iterator( mData.begin() );
	}
	//#########################################################################
	UTFString::const_iterator UTFString::begin() const {
		dstring& tmp = const_cast<dstring&>( mData );
		return const_iterator( tmp.begin() );
	}
	//#########################################################################
	UTFString::iterator UTFString::end() {
		return iterator( mData.end() );
	}
	//#########################################################################
	UTFString::const_iterator UTFString::end() const {
		dstring& tmp = const_cast<dstring&>( mData );
		return const_iterator( tmp.end() );
	}
	//#########################################################################
	UTFString::reverse_iterator UTFString::rbegin() {
		return reverse_iterator( mData.rbegin() );
	}
	//#########################################################################
	UTFString::const_reverse_iterator UTFString::rbegin() const {
		dstring& tmp = const_cast<dstring&>( mData );
		return reverse_iterator( tmp.rbegin() );
	}
	//#########################################################################
	UTFString::reverse_iterator UTFString::rend() {
		return const_reverse_iterator( mData.rend() );
	}
	//#########################################################################
	UTFString::const_reverse_iterator UTFString::rend() const {
		dstring& tmp = const_cast<dstring&>( mData );
		return const_reverse_iterator( tmp.rend() );
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
	void UTFString::resize( size_type num, const code_point& val ) {
		mData.resize( num, val );
	}
	//#########################################################################
	void UTFString::swap( UTFString& from ) {
		mData.swap( from.mData );
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
	/*UTFString& UTFString::assign( const std::string& str ){
		throw 0;
	}
	UTFString& UTFString::assign( const char* c_str ){
		throw 0;
	}
	UTFString& UTFString::assign( const char* c_str, size_type num ){
		throw 0;
	}*/

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
	bool UTFString::_utf16_start_char( code_point cp ) {
		if ( 0xDC00 <= cp && cp <= 0xDFFF ) // tests if the cp is within the 2nd word of a surrogate pair
			return false; // if it is a 2nd word, then we're not a starting character
		return true; // everything else is a starting character
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
} // namespace OpenGUI{
