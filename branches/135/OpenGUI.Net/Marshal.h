// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Marshal_h__
#define Marshal_h__

using namespace System;
#include <vcclr.h>
#define THRU_THROW_BEGIN try{
#define THRU_THROW_END }catch(OpenGUI::Exception& e){ \
	String^ msg = Marshal::String(e.getFullMessage()); \
	throw gcnew ::System::Exception(msg); }

namespace OpenGUI_Net {
	namespace Marshal {
		//############################################################################
		inline const std::string& String( ::System::String ^ managedString ) {
			static std::string out;
			pin_ptr<const wchar_t> wch = PtrToStringChars( managedString );
			int len = (( managedString->Length + 1 ) * 2 );
			char *ch = new char[ len ];
			bool result = wcstombs( ch, wch, len ) != -1;
			if ( !result )
				throw gcnew ::System::Exception( "Failed to marshal managed String to std::string" );
			out = ch;
			delete[] ch;
			return out;
		}
		//############################################################################
		inline ::System::String ^ String( const std::string& stdString ) {
			::System::String ^ out = gcnew ::System::String( stdString.c_str() );
			return out;
		}
		//############################################################################
	} // namespace Marshal{
} // namespace OpenGUINet {

#endif // Marshall_h__
