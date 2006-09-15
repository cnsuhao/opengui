
#include "OpenGUI_Event.h"
#include "OpenGUI_Object.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	namespace Event {
		//############################################################################
		EventReceiver::EventReceiver() {
			mParent = 0;
		}
		//############################################################################
		EventReceiver::~EventReceiver() {
			for ( EventHandlerListMap::iterator iter = mEventHandlerListMap.begin();
					iter != mEventHandlerListMap.end();
					iter++ ) {
				EventHandlerList* evt = iter->second;
				delete evt;
			}
		}
		//############################################################################
		void EventReceiver::sendEvent( const std::string& name, EventArgs& args ) {
			EventHandlerList* events = getEventHandlers( name );
			if ( events ) {
				events->invoke( mParent, args );
			} else {
				OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Event does not exist: " + name, __FUNCTION__ );
			}
		}
		//############################################################################
		void EventReceiver::createEvent( const std::string& name ) {
			EventHandlerListMap::iterator iter = mEventHandlerListMap.find( name );
			if ( mEventHandlerListMap.end() != iter ) {
				OG_THROW( Exception::ERR_DUPLICATE_ITEM, "Event already exists: " + name, __FUNCTION__ );
			}
			EventHandlerList* evtList = new EventHandlerList();
			mEventHandlerListMap[name] = evtList;
		}
		//############################################################################
		/*! Returns 0 (NULL) if the event requested does not exist.
		\see Too create new events see createEvent()	*/
		EventHandlerList* EventReceiver::getEventHandlers( const std::string& name ) {
			EventHandlerListMap::iterator iter = mEventHandlerListMap.find( name );
			if ( mEventHandlerListMap.end() != iter ) {
				return iter->second;
			}
			return 0;
		}
		//############################################################################
		EventHandlerList& EventReceiver::operator[]( const std::string& name ) {
			EventHandlerList* retobj = getEventHandlers( name );
			if(retobj == 0){
				OG_THROW(Exception::ERR_ITEM_NOT_FOUND,"Event does not exist: " + name, __FUNCTION__);
			}
			return *retobj;
		}
		//############################################################################
	}//namespace Event {
}// namespace OpenGUI {

