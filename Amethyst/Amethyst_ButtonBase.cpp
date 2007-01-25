// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
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
		void ButtonBase::onCursorEnter( Object* sender, EventArgs& evtArgs ) {
			m_Inside = true;
			updateButtonState();
			invalidate();
			OpenGUI::Control::onCursorEnter( sender, evtArgs );
		}
		//############################################################################
		void ButtonBase::onCursorLeave( Object* sender, EventArgs& evtArgs ) {
			m_Inside = false;
			updateButtonState();
			invalidate();
			OpenGUI::Control::onCursorLeave( sender, evtArgs );
		}
		//############################################################################
		void ButtonBase::onCursorPress( Object* sender, Cursor_EventArgs& evtArgs ) {
			if ( m_Inside ) {
				m_bMouseButtonState = true;
				updateButtonState();
				invalidate();
				grabCursorFocus();
			}
		}
		//############################################################################
		void ButtonBase::onCursorRelease( Object* sender, Cursor_EventArgs& evtArgs ) {
			if ( m_Inside && m_bMouseButtonState ) {
				_buttonActivate();
			}
			m_bMouseButtonState = false;
			updateButtonState();
			invalidate();
			releaseCursorFocus();
		}
		//############################################################################
		void ButtonBase::onCursorFocused( Object* sender, Focus_EventArgs& evtArgs ) {
			m_Focused = true;
			Control::onCursorFocused( sender, evtArgs );
		}
		//############################################################################
		void ButtonBase::onCursorFocusLost( Object* sender, Focus_EventArgs& evtArgs ) {
			m_Focused = false;
			Control::onCursorFocusLost( sender, evtArgs );
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
