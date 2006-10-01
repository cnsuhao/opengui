
#include "OpenGUI_EventHandler.h"
#include "OpenGUI_Object.h"

namespace OpenGUI {
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
		for ( EventHandlerSet::iterator iter = mEventHandlerSet.begin();
				iter != mEventHandlerSet.end();
				iter++ ) {
			EventHandler* handler = ( *iter );
			handler->onEvent( sender, args );
		}
	}
	//############################################################################
}// namespace OpenGUI {
