#ifndef Amethyst_Label_h__
#define Amethyst_Label_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"

namespace OpenGUI {
	namespace Amethyst {

		//! Non interactive text label
		/*! Labels have no borders or backgrounds. They simply draw text where they are
		located. They will clip the text glyphs within their bounds, so you must use an
		appropriately sized Label if you want all of your text to be visible.
		*/
		class AMETHYST_API Label: public Control {
		public:
			Label();
			virtual ~Label();

			//! Set the text contents
			void setText( const std::string& text );
			//! Retrieve the current text contents
			const std::string& getText() const;

			//! Set the font used for this label
			void setFont( const Font& fnt );
			//! Get the font used for this label
			const Font& getFont() const;

			//! Sets the color of the font
			void setFontColor( const Color& color );
			//! Gets the color of the font
			const Color& getFontColor() const;

			//! Sets the alignment of the text within the label
			void setAlignment( const TextAlignment& alignment );
			//! Gets the current text alignment
			const TextAlignment&  getAlignment() const;

			//! Sets text wrapping
			void setWrap( bool wrap );
			//! Gets the current text wrapping
			bool getWrap() const;

			static Widget* createLabelFactory();
			virtual ObjectAccessorList* getAccessors();

		protected:
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );

		private:
			std::string mText;
			Font mFont;
			TextAlignment mAlignment;
			bool mWrap;
			Color mColor;
		};

	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_Label_h__
