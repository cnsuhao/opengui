// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "Amethyst_Label.h"
#include "OpenGUI_Macros.h"

namespace OpenGUI {
	namespace Amethyst {
		//############################################################################
		SimpleProperty_Bool( LabelP_Wrap, "Wrap", Label, getWrap, setWrap );
		SimpleProperty_String( LabelP_Text, "Text", Label, getText, setText );
		SimpleProperty_Font( LabelP_Font, "Font", Label, getFont, setFont );
		SimpleProperty_TextAlignment( LabelP_Alignment, "Alignment", Label, getAlignment, setAlignment );
		SimpleProperty_Color( LabelP_FontColor, "FontColor", Label, getFontColor, setFontColor );
		//############################################################################
		class Label_ObjectAccessorList : public ObjectAccessorList {
		public:
			Label_ObjectAccessorList() {
				addAccessor( &LabelP_Wrap );
				addAccessor( &LabelP_Text );
				addAccessor( &LabelP_Font );
				addAccessor( &LabelP_Alignment );
				addAccessor( &LabelP_FontColor );
			}
			~Label_ObjectAccessorList() {}
		}
		gLabel_ObjectAccessorList;
		//############################################################################
		//############################################################################
		ObjectAccessorList* Label::getAccessors() {
			return &gLabel_ObjectAccessorList;
		}
		//############################################################################
		Widget* Label::createLabelFactory() {
			return new Label();
		}
		//############################################################################
		Label::Label() {
			if ( gLabel_ObjectAccessorList.getParent() == 0 )
				gLabel_ObjectAccessorList.setParent( Control::getAccessors() );

			//setup defaults for properties
			mText = "";
			mAlignment = TextAlignment( TextAlignment::ALIGN_LEFT, TextAlignment::ALIGN_TOP );
			mWrap = false;
		}
		//############################################################################
		Label::~Label() {
			/**/
		}
		//############################################################################
		void Label::setText( const String& text ) {
			mText = text;
			invalidate();
		}
		//############################################################################
		const String& Label::getText() const {
			return mText;
		}
		//############################################################################
		void Label::setFont( const Font& fnt ) {
			mFont = fnt;
			invalidate();
		}
		//############################################################################
		const Font& Label::getFont() const {
			return mFont;
		}
		//############################################################################
		void Label::setFontColor( const Color& color ) {
			mColor = color;
		}
		//############################################################################
		const Color& Label::getFontColor() const {
			return mColor;
		}
		//############################################################################
		void Label::setAlignment( const TextAlignment& alignment ) {
			mAlignment = alignment;
			invalidate();
		}
		//############################################################################
		const TextAlignment&  Label::getAlignment() const {
			return mAlignment;
		}
		//############################################################################
		void Label::setWrap( bool wrap ) {
			mWrap = wrap;
			invalidate();
		}
		//############################################################################
		bool Label::getWrap() const {
			return mWrap;
		}
		//############################################################################
		void Label::onDraw( Object* sender, Draw_EventArgs& evtArgs ) {
			if ( mText.length() > 0 ) {
				Brush& b = evtArgs.brush;
				b.pushColor( mColor );
				b.pushClippingRect( getRect() );
				b.Text.drawTextArea( mText, getRect(), mFont, mWrap, mAlignment );
				b.pop(); //pop clipping rect
				b.pop(); // pop color
			}
		}
		//############################################################################
	} // namespace Amethyst{
} // namespace OpenGUI{
