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

			//
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
		FacePtr Button::getFaceNormal() {
			return mFace_Normal;
		}
		//############################################################################
		void Button::setFaceOver( FacePtr overFace ) {
			mFace_Over = overFace;
		}
		//############################################################################
		FacePtr Button::getFaceOver() {
			return mFace_Over;
		}
		//############################################################################
		void Button::setFacePressed( FacePtr pressedFace ) {
			mFace_Pressed = pressedFace;
		}
		//############################################################################
		FacePtr Button::getFacePressed() {
			return mFace_Pressed;
		}
		//############################################################################
		void Button::setFaceDisabled( FacePtr disabledFace ) {
			mFace_Disabled = disabledFace;
		}
		//############################################################################
		FacePtr Button::getFaceDisabled() {
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
		//############################################################################
		//############################################################################
		//############################################################################
		//############################################################################
		void Button::onDraw( Object* sender, Draw_EventArgs& evtArgs ) {
			Brush& b = evtArgs.brush;
			switch ( mButtonState ) {
			case BS_NORMAL:
				b.Image.drawFace( mFace_Normal, getRect() );
				break;
			case BS_PRESSED:
				b.Image.drawFace( mFace_Pressed, getRect() );
				break;
			case BS_HOVER:
				b.Image.drawFace( mFace_Over, getRect() );
				break;
			case BS_DISABLED:
				b.Image.drawFace( mFace_Disabled, getRect() );
				break;

			default:
				//todo:: throw exception
				break;
			}

			//b.Image.drawImage( pCurrentImage, getRect() );
			if ( mText != "" )
				b.Text.drawTextArea( mText, getRect(), mFont, true, m_TextAlignment );
		}


	} // namespace Amethyst{
} // namespace OpenGUI{
