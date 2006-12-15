// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Amethyst_Window_h__
#define Amethyst_Window_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"


namespace OpenGUI {
	namespace Amethyst {

		//! encapsulates the basic mouse/button interaction for all button variants
		class AMETHYST_API Window : public OpenGUI::Window {
		public:
			Window();
			virtual ~Window();

			//! Sets the background Face used to fill the ScrollBar rect
			void setFaceBG( FacePtr faceBG );
			//! Gets the background Face used to fill the ScrollBar rect
			FacePtr getFaceBG() const;

			//! Sets the resize cursor for the lower left
			void setCursorLL( CursorPtr cursorPtr );
			//! Gets the resize cursor for the lower left
			CursorPtr getCursorLL() const;
			//! Sets the resize cursor for the lower right
			void setCursorLR( CursorPtr cursorPtr );
			//! Gets the resize cursor for the lower right
			CursorPtr getCursorLR() const;
			//! Sets the resize cursor for the upper left
			void setCursorUL( CursorPtr cursorPtr );
			//! Gets the resize cursor for the upper left
			CursorPtr getCursorUL() const;
			//! Sets the resize cursor for the upper right
			void setCursorUR( CursorPtr cursorPtr );
			//! Gets the resize cursor for the upper right
			CursorPtr getCursorUR() const;

			static Widget* createWindowFactory();
			virtual ObjectAccessorList* getAccessors();
		protected:
			virtual void onDrawBG( Object* sender, Draw_EventArgs& evtArgs );
			virtual void onCursor_Move( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursor_Enter( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursor_Leave( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursor_Press( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursor_Release( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursor_Focused( Object* sender, Focus_EventArgs& evtArgs );
			virtual void onCursor_FocusLost( Object* sender, Focus_EventArgs& evtArgs );
		private:
			typedef enum{
				NORMAL = 0,
				UL     = 1,
				UR     = 2,
				LL     = 3,
				LR     = 4,
			} CursorState;
			CursorState mCursorState;
			FacePtr mFaceBG;
			CursorPtr mCursorLL;
			CursorPtr mCursorLR;
			CursorPtr mCursorUL;
			CursorPtr mCursorUR;
			void updateCursor(); // sets the cursor according to mCursorState
		};

	} //namespace Amethyst {
} // namespace OpenGUI {
#endif // Amethyst_Window_h__
