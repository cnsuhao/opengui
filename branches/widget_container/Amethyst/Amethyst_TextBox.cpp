#include "Amethyst_TextBox.h"

namespace OpenGUI {
	namespace Amethyst {

		//! Constructor
		TextBox::TextBox() {
//			if(gTextBox_ObjectAccessorList.getParent() == NULL)
//				gTextBox_ObjectAccessorList.setParent(Widget::getAccessors());

			mText = "";
			m_alignh = TextAlignment::ALIGN_LEFT;
			m_alignv = TextAlignment::ALIGN_CENTER;
			mFont = Font( "pecot", 10 );


		}

		//! virtual Destructor
		TextBox::~TextBox() {
		}

		//! Sets the normal button imagery.
		void TextBox::setImagery( std::string imageryName ) {
			invalidate();
			mImageryPtr = ImageryManager::getSingleton().getImagery( imageryName );
		}

		//! Gets the normal button imagery.
		std::string TextBox::getImagery() {
			if ( !mImageryPtr.isNull() )
				return mImageryPtr->getName();

			return "";
		}

		//############################################################################
		void TextBox::setAlignment( TextAlignment::Alignment h, TextAlignment::Alignment v ) {
			m_alignh = h;
			m_alignv = v;
		}
		//############################################################################
		void TextBox::getAlignment( TextAlignment::Alignment &h, TextAlignment::Alignment &v ) {
			h = m_alignh;
			v = m_alignv;
		}
		//############################################################################
		void TextBox::setAlignment( IVector2 &align ) {
			TextAlignment::Alignment h = ( TextAlignment::Alignment ) align.x;
			TextAlignment::Alignment v = ( TextAlignment::Alignment ) align.y;
			setAlignment( h, v );
		}
		//############################################################################
		void TextBox::getAlignment( IVector2 &align ) {
			TextAlignment::Alignment h;
			TextAlignment::Alignment v;
			getAlignment( h, v );
			align.x = h;
			align.y = v;
		}
		//############################################################################

		void TextBox::onDraw( Object* sender, Draw_EventArgs& evtArgs ) {
			if ( !mImageryPtr.isNull() ) {
				Brush& b = evtArgs.brush;
				b.Image.drawImage( mImageryPtr, getRect() );
				b.Text.drawTextArea( mText, getRect(), mFont, true, TextAlignment(m_alignh, m_alignv) );
			}
		}




		Widget* TextBox::createTextBoxFactory() {
			return new TextBox;
		}

		//! Called when cursor was pressed and released within this Control
		void TextBox::onCursor_Click( Object* sender, Cursor_EventArgs& evtArgs ) {
			grabKeyFocus();
			OpenGUI::Control::onCursor_Click( sender, evtArgs );
		}
		//! Called when the cursor enters this Control
		void TextBox::onCursor_Enter( Object* sender, Cursor_EventArgs& evtArgs ) {
			OpenGUI::Control::onCursor_Enter( sender, evtArgs );
		}
		//! Called when the cursor leaves this Control
		void TextBox::onCursor_Leave( Object* sender, Cursor_EventArgs& evtArgs ) {
			OpenGUI::Control::onCursor_Leave( sender, evtArgs );
		}

		//! "Cursor_Press" event
		void TextBox::onCursor_Press( Object* sender, Cursor_EventArgs& evtArgs ) {
			grabKeyFocus();
			Control::onCursor_Press( sender, evtArgs );
		}
		//! "Cursor_Release" event
		void TextBox::onCursor_Release( Object* sender, Cursor_EventArgs& evtArgs ) {
			Control::onCursor_Release( sender, evtArgs );
		}

		//! "Key_Up" event
		void TextBox::onKey_Up( Object* sender, Key_EventArgs& evtArgs )
		{
			Control::onKey_Up( sender, evtArgs );
		}
		//! "Key_Down" event
		void TextBox::onKey_Down( Object* sender, Key_EventArgs& evtArgs )
		{
			Control::onKey_Down( sender, evtArgs );
		}
		//! "Key_Pressed" event
		void TextBox::onKey_Pressed( Object* sender, Key_EventArgs& evtArgs )
		{
			mText = mText + evtArgs.Character;
			evtArgs.eat();
			Control::onKey_Pressed( sender, evtArgs );
		}
		//! "Key_Focused" event
		void TextBox::onKey_Focused( Object* sender, Focus_EventArgs& evtArgs )
		{
			Control::onKey_Focused( sender, evtArgs );
		}
		//! "Key_FocusLost" event
		void TextBox::onKey_FocusLost( Object* sender, Focus_EventArgs& evtArgs )
		{
			Control::onKey_FocusLost( sender, evtArgs );
		}

		//! "Attached" event
		void TextBox::onAttached( Object* sender, Attach_EventArgs& evtArgs )
		{
			Widget::onAttached(sender, evtArgs );
			grabKeyFocus();
		}
		//! "Detached" event
		void TextBox::onDetached( Object* sender, Attach_EventArgs& evtArgs )
		{
			releaseKeyFocus();
			Widget::onDetached(sender, evtArgs );
		}

	} // namespace Amethyst{
} // namespace OpenGUI{
