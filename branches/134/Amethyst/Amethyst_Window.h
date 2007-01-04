// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Amethyst_Window_h__
#define Amethyst_Window_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"


namespace OpenGUI {
	namespace Amethyst {

		//! A window providing built in resizing functionality
		/*! This is an extension of the OpenGUI::Window class. It's purpose
		is to provide a slightly less generic implementation of a window by
		providing built in functionality for background imagery and location
		sensitive resizing with cursor replacement to signify these "hot spots".

		\par Properties
		- FaceBG
		- CursorUL
		- CursorUR
		- CursorLL
		- CursorLR
		*/
		class AMETHYST_API Window : public OpenGUI::Window {
		public:
			Window();
			virtual ~Window();

			//! Sets the background Face used to fill the Window rect
			void setFaceBG( FacePtr faceBG );
			//! Gets the background Face used to fill the Window rect
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
			virtual void onCursorMove( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursorEnter( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursorLeave( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursorPress( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursorRelease( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursorFocused( Object* sender, Focus_EventArgs& evtArgs );
			virtual void onCursorFocusLost( Object* sender, Focus_EventArgs& evtArgs );
		private:
			typedef enum {
				NORMAL = 0,
				UL     = 1,
				UR     = 2,
				LL     = 3,
				LR     = 4,
			}
			CursorState;
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
