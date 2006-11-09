#ifndef Amethyst_Button_h__
#define Amethyst_Button_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"

namespace OpenGUI {
	namespace Amethyst {

		enum {
			BS_NORMAL,
			BS_PRESSED,
			BS_HOVER,
			BS_DISABLED
		};

		// encapsulates the basic mouse/button interaction for all button variants

		class AMETHYST_API ButtonBase : public Control {
		public:
			ButtonBase() : m_bMouseButtonState(false), mButtonState(BS_NORMAL) {}
			virtual ~ButtonBase() {}

		protected:
			// events we care about

			//! "Cursor_Click" event
			virtual void onCursor_Click( Object* sender, Cursor_EventArgs& evtArgs );
			//! "Cursor_Enter" event; invokes Targeted
			virtual void onCursor_Enter( Object* sender, Cursor_EventArgs& evtArgs );
			//! "Cursor_Leave" event; invokes UnTargeted
			virtual void onCursor_Leave( Object* sender, Cursor_EventArgs& evtArgs );

			//! "Cursor_Press" event
			virtual void onCursor_Press( Object* sender, Cursor_EventArgs& evtArgs );
			//! "Cursor_Release" event
			virtual void onCursor_Release( Object* sender, Cursor_EventArgs& evtArgs );

			bool m_bMouseButtonState;
			int mButtonState;

			virtual void preActivate()=0;
		};

		class AMETHYST_API SimpleButton : public ButtonBase {
		public:
			//! Constructor
			SimpleButton();
			//! virtual Destructor
			virtual ~SimpleButton();
			//! Sets the normal button imagery.
			void setImagery( std::string imageryName );
			//! Sets the pressed button imagery. If none specified, uses the Normal imagery.
			void setImageryPressed( std::string imageryName );
			//! Sets the mouse over button imagery. If none specified, uses the Normal imagery.
			void setImageryMouseOver( std::string imageryName );
			//! Sets the disabled button imagery. If none specified, uses the Normal imagery.
			void setImageryDisabled( std::string imageryName );

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
			void setText( const char *p )				{
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

			static Widget* createSimpleButtonFactory();

		protected:
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );
			virtual void onResized( Object* sender, Resized_EventArgs& evtArgs );

			ImageryPtr mImageryPtr;
			ImageryPtr mImageryPtrPressed;
			ImageryPtr mImageryPtrMouseOver;
			ImageryPtr mImageryPtrDisabled;

			std::string mText;
			Font mFont;
			TextAlignment::Alignment m_alignh;
			TextAlignment::Alignment m_alignv;

			// internal notification of button "Active" event about to be sent
			virtual void preActivate() {}
		};


	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_Button_h__
