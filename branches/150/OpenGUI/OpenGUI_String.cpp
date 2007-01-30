// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_String.h"

namespace OpenGUI {
	//############################################################################
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
	//############################################################################
	void UTFString::_getBufferStr() const {
		if ( m_bufferType != bt_string ) {
			_cleanBuffer();
			m_buffer.mStrBuffer = new std::string();
			m_bufferType = bt_string;
		}
		m_buffer.mStrBuffer->clear();
	}
	//############################################################################
	void UTFString::_getBufferWStr() const {
		if ( m_bufferType != bt_wstring ) {
			_cleanBuffer();
			m_buffer.mWStrBuffer = new std::wstring();
			m_bufferType = bt_wstring;
		}
		m_buffer.mWStrBuffer->clear();
	}
	//############################################################################
	void UTFString::_getBufferUTF32Str() const {
		if ( m_bufferType != bt_utf32string ) {
			_cleanBuffer();
			m_buffer.mUTF32StrBuffer = new utf32string();
			m_bufferType = bt_utf32string;
		}
		m_buffer.mUTF32StrBuffer->clear();
	}
	//############################################################################
} // namespace OpenGUI {
