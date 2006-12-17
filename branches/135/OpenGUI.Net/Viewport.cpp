// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "Stdafx.h"

#include "Viewport.h"

namespace OpenGUI_Net {
	//############################################################################
	const OpenGUI::IVector2& ViewportExchange::getSize() {
		static OpenGUI::IVector2 out; // need to keep this available indefinitely
		IVector2 t = m_Viewport->getSize();
		out = Marshal::IVECTOR2( t );
		return out;
	}
	//############################################################################
	void ViewportExchange::preUpdate( OpenGUI::Screen* updatingScreen ) {
		m_Viewport->preUpdate( nullptr );
	}
	//############################################################################
	void ViewportExchange::postUpdate( OpenGUI::Screen* updatingScreen ) {
		m_Viewport->postUpdate( nullptr );
	}
	//############################################################################
	void ViewportExchange::screenAttached( OpenGUI::Screen* attachingScreen ) {
		m_Viewport->screenAttached( nullptr );
	}
	//############################################################################
	void ViewportExchange::screenDetached( OpenGUI::Screen* detachingScreen ) {
		m_Viewport->screenDetached( nullptr );
	}
	//############################################################################
} // namespace OpenGUI_Net {
