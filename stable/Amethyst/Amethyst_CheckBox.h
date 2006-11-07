#ifndef Amethyst_CheckBox_h__
#define Amethyst_CheckBox_h__

#include "Amethyst_Button.h"

namespace OpenGUI {
	namespace Amethyst {
		class AMETHYST_API CheckBox : public Control {
		public:
			CheckBox();
			virtual ~CheckBox();

			//! Sets the normal button imagery.
			void setImagery( std::string imageryName, std::string selImageryName);
			//! Sets the pressed button imagery. If none specified, uses the Normal imagery.
			void setImageryPressed( std::string imageryName, std::string selImageryName );
			//! Sets the mouse over button imagery. If none specified, uses the Normal imagery.
			void setImageryMouseOver( std::string imageryName, std::string selImageryName );
			//! Sets the disabled button imagery. If none specified, uses the Normal imagery.
			void setImageryDisabled( std::string imageryName, std::string selImageryName );

			//! Gets the normal button imagery.
			std::string getImagery();
			//! Gets the pressed button imagery.
			std::string getImageryPressed();
			//! Gets the mouse over button imagery.
			std::string getImageryMouseOver();
			//! Gets the disabled button imagery.
			std::string getImageryDisabled();

			void setText( std::string &nText )		{
				mText = nText;
			}
			void setText( const char *p )			{
				mText = p;
			}
			const std::string getText( void ) const	{
				return mText;
			}
			void setFont( const Font& fnt )			{
				mFont = fnt;
			}
			const Font& getFont() const				{
				return mFont;
			}

			void setAlignment( TextAlignment::Alignment h, TextAlignment::Alignment v );
			void getAlignment( TextAlignment::Alignment &h, TextAlignment::Alignment &v );
			void setAlignment( IVector2 &align );
			void getAlignment( IVector2 &align );
		private:
			SimpleButton *mSelectedButton;
			SimpleButton *mUnselectedButton;
			std::string mButtonText;

			std::string mText;
			Font mFont;
			TextAlignment::Alignment m_alignh;
			TextAlignment::Alignment m_alignv;
		};
	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_CheckBox_h__
