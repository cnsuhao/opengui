// -----------------------------------------------------------------------------
// OpenGUI_EventListener.cpp
// -----------------------------------------------------------------------------

#include "OpenGUI_EventListener.h"
#include "OpenGUI_Element.h"

namespace OpenGUI{
	//#####################################################################
	EventListener::EventListener(Element* elementToBind){
		mAttachedElement = 0;
		if(elementToBind)
			attach(elementToBind);
	}
	//#####################################################################
	EventListener::~EventListener(){
		if(isAttached())
			detach();
	}
	//#####################################################################
	void EventListener::attach(Element* elementToBind){
		detach();
		if(elementToBind){
			elementToBind->attachEventListener(this);
		}
	}
	//#####################################################################
	void EventListener::detach(){
		if(mAttachedElement){
			mAttachedElement->detachEventListener(this);
		}
	}
	//#####################################################################
	void EventListener::_setAttachedElement(Element* newElement){
		if(mAttachedElement) detach();
		mAttachedElement = newElement;
	}
	//#####################################################################
}//namespace OpenGUI{

