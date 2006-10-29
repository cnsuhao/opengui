#ifndef Amethyst_Label_h__
#define Amethyst_Label_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"

namespace OpenGUI {
	namespace Amethyst {

		//! Non interactive text box
		class AMETHYST_API Label: public Control {
		public:
			//Object Functions
			virtual ObjectAccessorList* getAccessors();
			virtual char* getClassName();

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

			static Widget* CreateLabelFactory();
		protected:
//!\name Event Handlers
//@{
			//! Handles the "Draw" event
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );
//@}
		private:
			std::string mText;
			Font mFont;
		};

	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_Label_h__
