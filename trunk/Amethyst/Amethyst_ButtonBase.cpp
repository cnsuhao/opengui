// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "Amethyst_ButtonBase.h"

namespace OpenGUI {
	namespace Amethyst {
		//############################################################################
		ButtonBase::ButtonBase() {
			m_Inside = false;
			m_bMouseButtonState = false;
			m_Focused = false;
			mButtonState = BS_NORMAL;
		}
		//############################################################################
		ButtonBase::~ButtonBase() {
			/**/
		}
		//############################################################################
		void ButtonBase::onCursor_Enter( Object* sender, Cursor_EventArgs& evtArgs ) {
			m_Inside = true;
			updateButtonState();
			invalidate();
			OpenGUI::Control::onCursor_Enter( sender, evtArgs );
		}
		//############################################################################
		void ButtonBase::onCursor_Leave( Object* sender, Cursor_EventArgs& evtArgs ) {
			m_Inside = false;
			updateButtonState();
			invalidate();
			OpenGUI::Control::onCursor_Leave( sender, evtArgs );
		}
		//############################################################################
		void ButtonBase::onCursor_Press( Object* sender, Cursor_EventArgs& evtArgs ) {
			if ( m_Inside ) {
				m_bMouseButtonState = true;
				updateButtonState();
				invalidate();
				grabCursorFocus();
			}
		}
		//############################################################################
		void ButtonBase::onCursor_Release( Object* sender, Cursor_EventArgs& evtArgs ) {
			if ( m_Inside && m_bMouseButtonState ) {
				_buttonActivate();
			}
			m_bMouseButtonState = false;
			updateButtonState();
			invalidate();
			releaseCursorFocus();
		}
		//############################################################################
		void ButtonBase::onCursor_Focused( Object* sender, Focus_EventArgs& evtArgs ) {
			m_Focused = true;
			Control::onCursor_Focused( sender, evtArgs );
		}
		//############################################################################
		void ButtonBase::onCursor_FocusLost( Object* sender, Focus_EventArgs& evtArgs ) {
			m_Focused = false;
			Control::onCursor_FocusLost( sender, evtArgs );
		}
		//############################################################################
		void ButtonBase::onEnabled( Object* sender, EventArgs& evtArgs ) {
			updateButtonState();
			invalidate();
			Control::onEnabled( sender, evtArgs );
		}
		//############################################################################
		void ButtonBase::onDisabled( Object* sender, EventArgs& evtArgs ) {
			updateButtonState();
			invalidate();
			Control::onDisabled( sender, evtArgs );
		}
		//############################################################################
		void ButtonBase::updateButtonState() {
			if ( !getEnabled() ) {
				mButtonState = BS_DISABLED;
				return;
			}
			mButtonState = BS_NORMAL;
			if ( m_Inside )
				mButtonState = BS_OVER;
			if ( m_bMouseButtonState && m_Inside )
				mButtonState = BS_PRESSED;
		}
		//############################################################################
	} // namespace Amethyst {
} // namespace OpenGUI {
