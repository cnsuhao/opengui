#include "Amethyst_Button.h"
#include "OpenGUI_Macros.h"

namespace OpenGUI {
	namespace Amethyst {
		//############################################################################
		SimpleProperty_String( ButtonProperty_Text, "Text", Button, getText, setText );
		SimpleProperty_Font( ButtonProperty_Font, "Font", Button, getFont, setFont );
		SimpleProperty_TextAlignment( ButtonProperty_TextAlignment, "TextAlignment", Button, getAlignment, setAlignment );
		SimpleProperty_Face( ButtonProperty_FaceNormal, "Face_Normal", Button, getFaceNormal, setFaceNormal );
		SimpleProperty_Face( ButtonProperty_FaceOver, "Face_Over", Button, getFaceOver, setFaceOver );
		SimpleProperty_Face( ButtonProperty_FacePresseed, "Face_Pressed", Button, getFacePressed, setFacePressed );
		SimpleProperty_Face( ButtonProperty_FaceDisabled, "Face_Disabled", Button, getFaceDisabled, setFaceDisabled );
		SimpleProperty_Color( ButtonProperty_FontColor, "FontColor", Button, getFontColor, setFontColor );
		SimpleProperty_Color( ButtonProperty_FontColor_Over, "FontColor_Over", Button, getFontColorOver, setFontColorOver );
		SimpleProperty_Color( ButtonProperty_FontColor_Pressed, "FontColor_Pressed", Button, getFontColorPressed, setFontColorPressed );
		SimpleProperty_Color( ButtonProperty_FontColor_Disabled, "FontColor_Disabled", Button, getFontColorDisabled, setFontColorDisabled );
		//############################################################################
		class Button_ObjectAccessorList : public ObjectAccessorList {
		public:
			Button_ObjectAccessorList() {
				addAccessor( &ButtonProperty_Text );
				addAccessor( &ButtonProperty_Font );
				addAccessor( &ButtonProperty_TextAlignment );
				addAccessor( &ButtonProperty_FaceNormal );
				addAccessor( &ButtonProperty_FaceOver );
				addAccessor( &ButtonProperty_FacePresseed );
				addAccessor( &ButtonProperty_FaceDisabled );
				addAccessor( &ButtonProperty_FontColor );
				addAccessor( &ButtonProperty_FontColor_Over );
				addAccessor( &ButtonProperty_FontColor_Pressed );
				addAccessor( &ButtonProperty_FontColor_Disabled );
			}
			~Button_ObjectAccessorList() {}
		}
		gButton_ObjectAccessorList;
		//############################################################################
		//############################################################################
		Widget* Button::createButtonFactory() {
			return new Button;
		}
		//############################################################################
		ObjectAccessorList* Button::getAccessors() {
			return &gButton_ObjectAccessorList;
		}
		//############################################################################
		Button::Button() {
			if ( gButton_ObjectAccessorList.getParent() == NULL )
				gButton_ObjectAccessorList.setParent( Control::getAccessors() );

			getEvents().createEvent( "Activate" );
			getEvents()["Activate"].add( new EventDelegate( this, &Button::onActivate ) );
		}
		//############################################################################
		Button::~Button() {
			/**/
		}
		//############################################################################
		void Button::setFaceNormal( FacePtr normalFace ) {
			mFace_Normal = normalFace;
		}
		//############################################################################
		FacePtr Button::getFaceNormal() const {
			return mFace_Normal;
		}
		//############################################################################
		void Button::setFaceOver( FacePtr overFace ) {
			mFace_Over = overFace;
		}
		//############################################################################
		FacePtr Button::getFaceOver() const {
			return mFace_Over;
		}
		//############################################################################
		void Button::setFacePressed( FacePtr pressedFace ) {
			mFace_Pressed = pressedFace;
		}
		//############################################################################
		FacePtr Button::getFacePressed() const {
			return mFace_Pressed;
		}
		//############################################################################
		void Button::setFaceDisabled( FacePtr disabledFace ) {
			mFace_Disabled = disabledFace;
		}
		//############################################################################
		FacePtr Button::getFaceDisabled() const {
			return mFace_Disabled;
		}
		//############################################################################
		void Button::setText( const std::string& nText ) {
			mText = nText;
			invalidate();
		}
		//############################################################################
		const std::string& Button::getText( void ) const {
			return mText;
		}
		//############################################################################
		void Button::setFont( const Font& fnt ) {
			mFont = fnt;
			invalidate();
		}
		//############################################################################
		const Font& Button::getFont() const {
			return mFont;
		}
		//############################################################################
		void Button::setAlignment( const TextAlignment& alignment ) {
			m_TextAlignment = alignment;
			invalidate();
		}
		//############################################################################
		const TextAlignment& Button::getAlignment() {
			return m_TextAlignment;
		}
		//############################################################################
		void Button::setFontColor( const Color& color ) {
			mColor_Normal = color;
		}
		//############################################################################
		const Color& Button::getFontColor() const {
			return mColor_Normal;
		}
		//############################################################################
		void Button::setFontColorOver( const Color& color ) {
			mColor_Over = color;
		}
		//############################################################################
		const Color& Button::getFontColorOver() const {
			return mColor_Over;
		}
		//############################################################################
		void Button::setFontColorPressed( const Color& color ) {
			mColor_Pressed = color;
		}
		//############################################################################
		const Color& Button::getFontColorPressed() const {
			return mColor_Pressed;
		}
		//############################################################################
		void Button::setFontColorDisabled( const Color& color ) {
			mColor_Disabled = color;
		}
		//############################################################################
		const Color& Button::getFontColorDisabled() const {
			return mColor_Disabled;
		}
		//############################################################################
		void Button::eventActivate() {
			EventArgs args;
			getEvents().sendEvent( "Activate", args );
		}
		//############################################################################
		void Button::onActivate( Object* sender, EventArgs& evtArgs ) {
			/* default does nothing */
		}
		//############################################################################
		void Button::_buttonActivate(){
			eventActivate();
		}
		//############################################################################
		void Button::onDraw( Object* sender, Draw_EventArgs& evtArgs ) {
			Brush& b = evtArgs.brush;
			FacePtr drawFace = mFace_Normal;
			Color fontColor = mColor_Normal;

			if ( mFace_Over && mButtonState == BS_OVER ) {
				drawFace = mFace_Over;
				fontColor = mColor_Over;
			}

			if ( mFace_Pressed && mButtonState == BS_PRESSED ) {
				drawFace = mFace_Pressed;
				fontColor = mColor_Pressed;
			}

			if ( mFace_Disabled && mButtonState == BS_DISABLED ) {
				drawFace = mFace_Disabled;
				fontColor = mColor_Disabled;
			}

			if ( drawFace )
				b.Image.drawFace( drawFace, getRect() );

			if ( mText != "" ) {
				b.pushColor( fontColor );
				b.Text.drawTextArea( mText, getRect(), mFont, true, m_TextAlignment );
				b.pop();
			}
		}
		//############################################################################


	} // namespace Amethyst{
} // namespace OpenGUI{
