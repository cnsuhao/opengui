// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_EventHandler.h"
#include "OpenGUI_Object.h"

namespace OpenGUI {
	//############################################################################
	EventHandlerList::~EventHandlerList() {
		for ( EventHandlerSet::iterator iter = mEventHandlerSet.begin();
				iter != mEventHandlerSet.end();
				iter++ ) {
			EventHandler* handler = ( *iter );
			handler->onEventDestruction();
		}
	}
	//############################################################################
	void EventHandlerList::add( EventHandler* handler ) {
		mEventHandlerSet.insert( handler );
	}
	//############################################################################
	void EventHandlerList::remove( EventHandler* handler ) {
		EventHandlerSet::iterator iter = mEventHandlerSet.find( handler );
		mEventHandlerSet.erase( iter );
	}
	//############################################################################
	void EventHandlerList::invoke( Object* sender, EventArgs& args ) {
		EventHandlerSet::iterator iter, iterend = mEventHandlerSet.end();
		for ( iter = mEventHandlerSet.begin(); iter != iterend; iter++ ) {
			EventHandler* handler = ( *iter );
			handler->onEvent( sender, args );
		}
	}
	//############################################################################
}// namespace OpenGUI {
