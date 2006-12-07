#ifndef Amethyst_ButtonBase_h__
#define Amethyst_ButtonBase_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"

namespace OpenGUI {
	namespace Amethyst {


		//! encapsulates the basic mouse/button interaction for all button variants
		/*! All objects that derive from ButtonBase will emit the "Activate" event when they
		are pressed.
		*/
		class AMETHYST_API ButtonBase : public Control {
		public:
			ButtonBase();
			virtual ~ButtonBase();

			//! Called when this Control is activated (usually clicked)
			void eventActivate();
		protected:
			//! "Activate" event
			virtual void onActivate( Object* sender, EventArgs& evtArgs );

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

			virtual void onCursor_Focused( Object* sender, Focus_EventArgs& evtArgs );
			virtual void onCursor_FocusLost( Object* sender, Focus_EventArgs& evtArgs );
			virtual void onEnabled( Object* sender, EventArgs& evtArgs );
			virtual void onDisabled( Object* sender, EventArgs& evtArgs );

			enum {
				BS_NORMAL,
				BS_PRESSED,
				BS_OVER,
				BS_DISABLED
			};

			int mButtonState;
			virtual void preActivate() = 0;
		private:
			bool m_Inside;
			bool m_bMouseButtonState;
			bool m_Focused;
			void updateButtonState();
		};

	} // namespace Amethyst {
} // namespace OpenGUI {

#endif // Amethyst_ButtonBase_h__