// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Amethyst_ButtonBase_h__
#define Amethyst_ButtonBase_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"

namespace OpenGUI {
	namespace Amethyst {


		//! Encapsulates the basic mouse/button interaction for all button variants
		/*! This class does the grunt work of acting like a button. It will manipulate
		the mButtonState variable as circumstances change, and will invalidate the
		object to ensure the derived class has an opportunity to redraw using the new
		state information.

		Cursor focus is managed automatically, grabbing focus on initial press, and releasing
		it when the cursor released. If the cursor is released within the inside of the "button",
		then the virtual function _buttonActivate() is called, which allows subclasses to
		perform whatever function they determine is appropriate.
		*/
		class AMETHYST_API ButtonBase : public Control {
		public:
			ButtonBase();
			virtual ~ButtonBase();

		protected:
			// These are all events that we overload in order to perform necessary actions
			virtual void onCursorEnter( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursorLeave( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursorPress( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursorRelease( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursorFocused( Object* sender, Focus_EventArgs& evtArgs );
			virtual void onCursorFocusLost( Object* sender, Focus_EventArgs& evtArgs );
			virtual void onEnabled( Object* sender, EventArgs& evtArgs );
			virtual void onDisabled( Object* sender, EventArgs& evtArgs );

			//! This function is called when ButtonBase determines that a button activating circumstance has occurred
			virtual void _buttonActivate() = 0;

			//! List of possible button states
			enum {
				BS_NORMAL,
				BS_PRESSED,
				BS_OVER,
				BS_DISABLED
			};

			//! Holds the current button state
			int mButtonState;

		private:
			bool m_Inside;
			bool m_bMouseButtonState;
			bool m_Focused;
			void updateButtonState();
		};

	} // namespace Amethyst {
} // namespace OpenGUI {

#endif // Amethyst_ButtonBase_h__