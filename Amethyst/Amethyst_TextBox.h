// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Amethyst_TextBox_h__
#define Amethyst_TextBox_h__
#include "OpenGUI.h"
#include "Amethyst_Exports.h"

namespace OpenGUI {
	namespace Amethyst {

		//! encapsulates the basic GUI Keyboard input interaction
		class AMETHYST_API TextBox : public Control {
		public:
			TextBox() ;
			virtual ~TextBox() ;

			//! Sets the BG imagery.
			void setImagery( std::string imageryName );
			//! Gets the BG imagery.
			std::string getImagery();

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

			static Widget* createTextBoxFactory();

		protected:
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );

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

			//! "Attached" event
			virtual void onAttached( Object* sender, Attach_EventArgs& evtArgs );
			//! "Detached" event
			virtual void onDetached( Object* sender, Attach_EventArgs& evtArgs );

			//! "Key_Up" event
			virtual void onKey_Up( Object* sender, Key_EventArgs& evtArgs );
			//! "Key_Down" event
			virtual void onKey_Down( Object* sender, Key_EventArgs& evtArgs );
			//! "Key_Pressed" event
			virtual void onKey_Pressed( Object* sender, Key_EventArgs& evtArgs );
			//! "Key_Focused" event
			virtual void onKey_Focused( Object* sender, Focus_EventArgs& evtArgs );
			//! "Key_FocusLost" event
			virtual void onKey_FocusLost( Object* sender, Focus_EventArgs& evtArgs );


			ImageryPtr mImageryPtr;

			std::string mText;
			Font mFont;
			TextAlignment::Alignment m_alignh;
			TextAlignment::Alignment m_alignv;
		};
	} // namespace Amethyst{
} // namespace OpenGUI{



#endif // Amethyst_TextBox_h__
