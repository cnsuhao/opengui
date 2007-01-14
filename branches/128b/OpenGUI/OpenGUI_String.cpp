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
} // namespace OpenGUI{
