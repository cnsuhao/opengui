// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Marshal_h__
#define Marshal_h__

using namespace System;
#include <vcclr.h>
#define THRU_THROW_BEGIN try{
#define THRU_THROW_END }catch(OpenGUI::Exception& e){ \
	String^ msg = Marshal::STRING(e.getFullMessage()); \
	throw gcnew ::System::Exception(msg); }

#include "Types.h"

namespace OpenGUI_Net {
	namespace Marshal {
		//############################################################################
		inline const std::string& STRING( ::System::String ^ managedString ) {
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
		inline ::System::String ^ STRING( const std::string& stdString ) {
			::System::String ^ out = gcnew ::System::String( stdString.c_str() );
			return out;
		}
		//############################################################################
		inline OpenGUI::IVector2 IVECTOR2( OpenGUI_Net::IVector2 source ) {
			OpenGUI::IVector2 out;
			out.x = source.x;
			out.y = source.y;
			return out;
		}
		//############################################################################
		inline OpenGUI_Net::IVector2 IVECTOR2( const OpenGUI::IVector2& source ) {
			OpenGUI_Net::IVector2 out;
			out.x = source.x;
			out.y = source.y;
			return out;
		}
		//############################################################################
		inline OpenGUI::FVector2 FVECTOR2( OpenGUI_Net::FVector2 source ) {
			OpenGUI::FVector2 out;
			out.x = source.x;
			out.y = source.y;
			return out;
		}
		//############################################################################
		inline OpenGUI_Net::FVector2 FVECTOR2( const OpenGUI::FVector2& source ) {
			OpenGUI_Net::FVector2 out;
			out.x = source.x;
			out.y = source.y;
			return out;
		}
		//############################################################################
		inline OpenGUI::IRect IRECT( OpenGUI_Net::IRect source ) {
			OpenGUI::IRect out;
			out.min.x = source.min.x;
			out.min.y = source.min.y;
			out.max.x = source.max.x;
			out.max.y = source.max.y;
			return out;
		}
		//############################################################################
		inline OpenGUI_Net::IRect IRECT( const OpenGUI::IRect& source ) {
			OpenGUI_Net::IRect out;
			out.min.x = source.min.x;
			out.min.y = source.min.y;
			out.max.x = source.max.x;
			out.max.y = source.max.y;
			return out;
		}
		//############################################################################
		inline OpenGUI::FRect FRECT( OpenGUI_Net::FRect source ) {
			OpenGUI::FRect out;
			out.min.x = source.min.x;
			out.min.y = source.min.y;
			out.max.x = source.max.x;
			out.max.y = source.max.y;
			return out;
		}
		//############################################################################
		inline OpenGUI_Net::FRect FRECT( const OpenGUI::FRect& source ) {
			OpenGUI_Net::FRect out;
			out.min.x = source.min.x;
			out.min.y = source.min.y;
			out.max.x = source.max.x;
			out.max.y = source.max.y;
			return out;
		}
		//############################################################################
		inline OpenGUI::TextAlignment TEXTALIGNMENT( OpenGUI_Net::TextAlignment source ) {
			OpenGUI::TextAlignment out;
			int h = ( int )source.horizontal;
			int v = ( int )source.vertical;
			out = OpenGUI::TextAlignment(( OpenGUI::TextAlignment::Alignment )h, ( OpenGUI::TextAlignment::Alignment )v );
			return out;
		}
		//############################################################################
		inline OpenGUI_Net::TextAlignment TEXTALIGNMENT( const OpenGUI::TextAlignment& source ) {
			OpenGUI_Net::TextAlignment out;
			int h = ( int )source.getHorizontal();
			int v = ( int )source.getVertical();
			out.horizontal = ( TextAlignment::Alignment ) h;
			out.vertical = ( TextAlignment::Alignment ) v;
			return out;
		}
	} // namespace Marshal{
} // namespace OpenGUINet {

#endif // Marshall_h__
