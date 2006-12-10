#ifndef Amethyst_Button_h__
#define Amethyst_Button_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"
#include "Amethyst_ButtonBase.h"

namespace OpenGUI {
	namespace Amethyst {

		//! Your average pushable button
		/*! Performs the usual barrage of button-like activity. Fires the "Activate" event when pressed.

		\par Properties
		- Face_Normal
		- Face_Over
		- Face_Pressed
		- Face_Disabled
		- Font
		- TextAlignment
		- Text
		- FontColor
		- FontColor_Over
		- FontColor_Pressed
		- FontColor_Disabled

		*/
		class AMETHYST_API Button : public ButtonBase {
		public:
			//! Constructor
			Button();
			//! virtual Destructor
			virtual ~Button();

			//! Called when the button is clicked
			void eventActivate();

			//! Sets the Face used to draw the button in the Normal state
			void setFaceNormal( FacePtr normalFace );
			//! Gets the Face used to draw the button in the Normal state
			FacePtr getFaceNormal()const;
			//! Sets the Face used to draw the button in the Over state
			void setFaceOver( FacePtr overFace );
			//! Gets the Face used to draw the button in the Over state
			FacePtr getFaceOver()const;
			//! Sets the Face used to draw the button in the Pressed state
			void setFacePressed( FacePtr pressedFace );
			//! Gets the Face used to draw the button in the Pressed state
			FacePtr getFacePressed()const;
			//! Sets the Face used to draw the button in the Disabled state
			void setFaceDisabled( FacePtr disabledFace );
			//! Gets the Face used to draw the button in the Disabled state
			FacePtr getFaceDisabled()const;

			//! Sets the text that is displayed on this button
			void setText( const std::string& nText );
			//! Gets the text that is displayed on this button
			const std::string& getText() const;
			//! Sets the Font used to draw the text on this button
			void setFont( const Font& fnt );
			//! Gets the Font used to draw the text on this button
			const Font& getFont() const;

			//! Sets the color of the font
			void setFontColor( const Color& color );
			//! Gets the color of the font
			const Color& getFontColor() const;

			//! Sets the color of the font in the Over state
			void setFontColorOver( const Color& color );
			//! Gets the color of the font in the Over state
			const Color& getFontColorOver() const;
			//! Sets the color of the font in the Pressed state
			void setFontColorPressed( const Color& color );
			//! Gets the color of the font in the Pressed state
			const Color& getFontColorPressed() const;
			//! Sets the color of the font in the Disabled state
			void setFontColorDisabled( const Color& color );
			//! Gets the color of the font in the Disabled state
			const Color& getFontColorDisabled() const;

			//! Sets the text alignment used when drawing the button text
			void setAlignment( const TextAlignment& alignment );
			//! Gets the text alignment used when drawing the button text
			const TextAlignment& getAlignment();


			static Widget* createButtonFactory();
			virtual ObjectAccessorList* getAccessors();

		protected:
			//! "Activate" event
			virtual void onActivate( Object* sender, EventArgs& evtArgs );
			// inherited from ButtonBase
			virtual void _buttonActivate();

			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );

			std::string mText;
			Font mFont;
			TextAlignment m_TextAlignment;
			FacePtr mFace_Normal;
			FacePtr mFace_Over;
			FacePtr mFace_Pressed;
			FacePtr mFace_Disabled;
			Color mColor_Normal;
			Color mColor_Over;
			Color mColor_Pressed;
			Color mColor_Disabled;

		};


	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_Button_h__
