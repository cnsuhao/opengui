// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_HandleManager.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	HandleManager::ListenerSet HandleManager::mListenerSet;
	//############################################################################
	//############################################################################
	void HandleManager::attachListener( HandleManagerListener* listener ) {
		ListenerSet::iterator iter = mListenerSet.find( listener );
		if ( iter != mListenerSet.end() )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM, "Given HandleManagerListener already attached", __FUNCTION__ );
		mListenerSet.insert( listener );
	}
	//############################################################################
	void HandleManager::detachListener( HandleManagerListener* listener ) {
		ListenerSet::iterator iter = mListenerSet.find( listener );
		if ( iter == mListenerSet.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Given HandleManagerListener not attached", __FUNCTION__ );
		mListenerSet.erase( listener );
	}
	//############################################################################
	void HandleManager::_Object_Created( HandledObject* object ) {
		/**/
	}
	//############################################################################
	void HandleManager::_Object_Destroyed( HandledObject* object ) {
		/**/
	}
	//############################################################################
} // namespace OpenGUI {
