#ifndef Amethyst_Button_h__
#define Amethyst_Button_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"
#include "Amethyst_ButtonBase.h"

namespace OpenGUI {
	namespace Amethyst {

		//! Button
		class AMETHYST_API Button : public ButtonBase {
		public:
			//! Constructor
			Button();
			//! virtual Destructor
			virtual ~Button();

			//! Sets the Face used to draw the button in the Normal state
			void setFaceNormal( FacePtr normalFace );
			//! Gets the Face used to draw the button in the Normal state
			FacePtr getFaceNormal();
			//! Sets the Face used to draw the button in the Over state
			void setFaceOver( FacePtr overFace );
			//! Gets the Face used to draw the button in the Over state
			FacePtr getFaceOver();
			//! Sets the Face used to draw the button in the Pressed state
			void setFacePressed( FacePtr pressedFace );
			//! Gets the Face used to draw the button in the Pressed state
			FacePtr getFacePressed();
			//! Sets the Face used to draw the button in the Disabled state
			void setFaceDisabled( FacePtr disabledFace );
			//! Gets the Face used to draw the button in the Disabled state
			FacePtr getFaceDisabled();

			//! Sets the text that is displayed on this button
			void setText( const std::string& nText );
			//! Gets the text that is displayed on this button
			const std::string& getText( void ) const;
			//! Sets the Font used to draw the text on this button
			void setFont( const Font& fnt );
			//! Gets the Font used to draw the text on this button
			const Font& getFont() const;
			//! Sets the text alignment used when drawing the button text
			void setAlignment( const TextAlignment& alignment );
			//! Gets the text alignment used when drawing the button text
			const TextAlignment& getAlignment();


			static Widget* createButtonFactory();
			virtual ObjectAccessorList* getAccessors();

		protected:
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );

			std::string mText;
			Font mFont;
			TextAlignment m_TextAlignment;
			FacePtr mFace_Normal;
			FacePtr mFace_Over;
			FacePtr mFace_Pressed;
			FacePtr mFace_Disabled;

			// internal notification of button "Active" event about to be sent
			virtual void preActivate() {}
		};


	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_Button_h__
