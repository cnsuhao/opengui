
#include "OpenGUI.h"

namespace OpenGUI{

	//Many of the simpler implementation are not performed as inline to ensure proper DLL linking

	//#####################################################################

	//! This is used as a sort predicate for sorting Element children by Z Order
	struct ChildElementListZOrderSortDescending{
		//return true when the order is correct from left to right
		bool operator()(ChildElementListItem& left,ChildElementListItem& right){
			if(!left || !right){
				OG_THROW(Exception::ERR_INTERNAL_ERROR, "Bad ChildElementList data", "ChildElementListZOrderSortDescending");
			}
			if(left->getAlwaysOnTop() && (!right->getAlwaysOnTop()))
				return true;
			return(left->getZOrder() >= right->getZOrder());
		}
	};

	//#####################################################################
	Element::Element()
	{
		mObjectName="";
		mParentElement=0;
		mZOrder = 0;
		mAlpha = 1.0f;
		mVisible = true;
		mDisabled = false;
		mAlwaysOnTop = false;
		mClientAreaScaleType = CAS_Scaled;
		mClipsChildren = true;
		mClientRectCustomScale = FVector2(1.0f,1.0f);
	}
	//#####################################################################
	Element::~Element()
	{
		Element::destroyAllChildElements();
	}
	//#####################################################################
	std::string Element::getName()
	{
		return mObjectName;
	}
	//#####################################################################
	Element* Element::getChildElement(const std::string& name)
	{
		ChildElementList::iterator i = mChildrenElements.begin();
		while(i != mChildrenElements.end()){
			if((*i)->getName() == name){
				return (*i);
			}
			i++;
		}
		return 0;
	}
	//#####################################################################
	Element* Element::getChildElementRecursive(const std::string& name)
	{	//Walking the entire tree is probably the fastest way to do this.
		ChildElementList::iterator i = mChildrenElements.begin();
		while(i != mChildrenElements.end()){
			if((*i)->getName() == name){
				return (*i); //if we found it, then return it
			}else{
				//otherwise ask this child to search for it as well
				Element* element = (*i)->getChildElementRecursive(name);
				if(element)
					return element; //if they found it, return it
			}
			i++;
		}
		return 0; //it isn't here, return 0
	}
	//#####################################################################
	void Element::addChildElement(Element* child, std::string name)
	{
		if(name==""){
			name = System::getSingleton().generateRandomElementName();
		}else{
			//test to ensure that the new element has no children with that name already
			if(child->getChildElement(name)){
				OG_THROW(Exception::ERR_DUPLICATE_ITEM, "Element with name already exists:" + name, "Element::addChildElement");
			}
			//test the name to ensure it is unique within the system
			if(System::getSingleton().getElementByName(name)){
				OG_THROW(Exception::ERR_DUPLICATE_ITEM, "Element with name already exists:" + name, "Element::addChildElement");
			}
		}
		child->_setElementName(name);  //give the child a name
		ChildElementList::iterator i = mChildrenElements.begin();
		while(i != mChildrenElements.end()){
			//if the new child's zOrder is higher or equal to the current
			if(
				//If both are AlwaysOnTop or both aren't, then ZOrder is all that matters
				( (*i)->getAlwaysOnTop() == child->getAlwaysOnTop() && (*i)->getZOrder() <= child->getZOrder() ) ||
				( child->getAlwaysOnTop() && (!(*i)->getAlwaysOnTop()) ) //also check if new child is set OnTop and this element isn't
			){
				//then add it directly before this entry, and return
				mChildrenElements.insert(i, child);
				child->_setElementParent(this); //add ourself to the child
				//!\TODO: perform attach operations here
				return;
			}
			i++;
		}
		//the new child has the lowest zOrder, so we need to push it to the back of the child list
		mChildrenElements.push_back(child);
		child->_setElementParent(this); //add ourself to the child
	}
	//#####################################################################
	void Element::destroyChildElement(Element* child)
	{
		ChildElementList::iterator i = mChildrenElements.begin();
		while(i != mChildrenElements.end()){
			if((*i) == child){
				(*i)->_setElementParent(0); //remove ourself from the child
				delete (*i);
				mChildrenElements.erase(i);
				return;
			}
			i++;
		}
	}
	//#####################################################################
	void Element::destroyChildElement(std::string name)
	{
		//get the child by name and call destroyChildElement(Element* child)
		Element* element;
		element = Element::getChildElement(name);
		Element::destroyChildElement(element);
	}
	//#####################################################################
	void Element::removeChildElement(Element* child)
	{
		ChildElementList::iterator i = mChildrenElements.begin();
		while(i != mChildrenElements.end()){
			if((*i) == child){
				(*i)->_setElementParent(0); //remove ourself from the child
				mChildrenElements.erase(i);
				return;
			}
			i++;
		}
	}
	//#####################################################################
	void Element::destroyAllChildElements()
	{
		ChildElementList::iterator i = mChildrenElements.begin();
		while(i != mChildrenElements.end()){
			(*i)->_setElementParent(0); //remove ourself from the child
			delete (*i);
			i++;
		}
		mChildrenElements.clear();
	}
	//#####################################################################
	void Element::sortChildElements()
	{
		mChildrenElements.sort(ChildElementListZOrderSortDescending());
	}
	//#####################################################################
	ChildElementList Element::getChildElementList()
	{
		ChildElementList retval;
		retval = mChildrenElements;
		return retval;
	}
	//#####################################################################
	void Element::getChildElementZOrderExtents(int& upperZ, int& lowerZ)
	{
		/*
			Even though mChildrenElements is always sorted by draw order,
			we cannot assume that to correctly represent the ZOrder extents
			because Element.mAlwaysOnTop will affect the draw order sorting
			as well, and we only want to get ZOrder extents without AlwaysOnTop
			being taken into consideration.
		*/
		ChildElementList::iterator i = mChildrenElements.begin();
		if(i == mChildrenElements.end()){
			upperZ = 0; //parent has no children, so set both to 0 and return
			lowerZ = 0;
			return;
		}
		bool foundOne=false;
		while(i != mChildrenElements.end()){
			if(foundOne){
				if(upperZ < (*i)->getZOrder())
					upperZ = (*i)->getZOrder();
				if(lowerZ > (*i)->getZOrder())
					lowerZ = (*i)->getZOrder();
			}else{
				foundOne=true;
				upperZ = lowerZ = (*i)->getZOrder();
			}
			i++;
		}
	}
	//#####################################################################
	void Element::buildElementAncestry(ElementAncestryList& ancestryList)
	{
		ancestryList.push_front(this);
		if(mParentElement)
			mParentElement->buildElementAncestry(ancestryList);
	}
	//#####################################################################

	/*! \todo Should we bother to check to ensure the callee is in the child list?
				Logically it is guaranteed in the list unless a previous event 
				handler/subscriber removed it while we made the climb to this point.
				Perhaps it makes sense to guarantee atomic event propagation,
				though that can cause a bad pointer situation if an Element
				was destroyed by an event handler/subscriber for some reason.
				This needs to be addressed. -ES
		*/
	void Element::_propogateEvent(Msg::Message& message, ElementAncestryList& propagationList)
	{
		//due to boolean optimizations, we have to combine these as such or risk not running something
		bool contProp = _fireMessageSubscribers(message);
		contProp = defaultMessageHandler(message) && contProp;
		if(!contProp) return; //if someone said stop, then stop!
		//otherwise pop ourself off the list and call the next guy in line
		propagationList.pop_front();
		if(propagationList.size() > 0)
			propagationList.front()->_propogateEvent(message, propagationList);
	}
	//#####################################################################
	void Element::_propogateGlobalEvent(const Msg::Message& message)
	{
		_fireMessageSubscribers(message);
		defaultMessageHandler(message);
		ChildElementList::iterator i = mChildrenElements.begin();
		while(i != mChildrenElements.end()){
			(*i)->_propogateGlobalEvent(message);
			i++;
		}
	}
	//#####################################################################
	bool Element::defaultMessageHandler(const Msg::Message& message)
	{
		//The base default event handler is to do nothing.
		//We return true so that event propagation can continue onward if necessary.
		return true;
	}
	//#####################################################################
	void Element::attachEventSubscriber(Subscriber sub)
	{
		Element::detachEventSubscriber(sub);
		mSubscriberList.push_back(sub);
	}
	//#####################################################################
	void Element::detachEventSubscriber(Subscriber sub)
	{
		SubscriberList::iterator sli = mSubscriberList.begin();
		while(sli != mSubscriberList.end()){
			if((*sli) == sub){
				mSubscriberList.erase(sli);
				return;
			}
			sli++;
		}
	}
	//#####################################################################
	bool Element::_fireMessageSubscribers(const Msg::Message& message)
	{
		bool continuePropagation=true;
		SubscriberList::iterator sli = mSubscriberList.begin();
		while(sli != mSubscriberList.end()){
			Subscriber f = (*sli);
			continuePropagation = (*f)(this,message) && continuePropagation;
			sli++;
		}
		return continuePropagation;
	}
	//#####################################################################
	void Element::setRect(FRect& newRect)
	{
		mElementRect = newRect;
	}
	//#####################################################################
	FRect Element::getRect()
	{
		return mElementRect;
	}
	//#####################################################################
	void Element::setPos(FVector2& newPosition)
	{
		//!\todo should we add an event for widget position changes?
		mElementRect.setPosition(newPosition);
	}
	//#####################################################################
	void Element::setPos(const float& xPos, const float& yPos)
	{
		mElementRect.setPosition(FVector2(xPos,yPos));
	}
	//#####################################################################
	void Element::setSize(FVector2& newSize)
	{
		//!\todo should we add an event for widget size changes?
		mElementRect.setSize(newSize);
	}
	//#####################################################################
	void Element::setSize(const float& width, const float& height)
	{
		mElementRect.setSize(FVector2(width,height));
	}
	//#####################################################################
	int Element::getZOrder()
	{
		return mZOrder;
	}
	//#####################################################################
	void Element::setZOrder(int newZOrder)
	{
		mZOrder = newZOrder;
		Element::notifyElementParentZChange();
	}
	//#####################################################################
	void Element::_setElementName(std::string newName)
	{
		mObjectName = newName;
	}
	//#####################################################################
	void Element::_setElementParent(Element* newParent)
	{
		mParentElement = newParent;
	}
	//#####################################################################
	void Element::notifyElementParentZChange()
	{
		if(mParentElement)
			mParentElement->sortChildElements();
	}
	//#####################################################################
	bool Element::getAlwaysOnTop() const
	{
		return mAlwaysOnTop;
	}
	//#####################################################################
	void Element::setAlwaysOnTop(bool newAlwaysOnTop)
	{
		mAlwaysOnTop = newAlwaysOnTop;
		Element::notifyElementParentZChange();
	}
	//#####################################################################
	void Element::sendToBack()
	{
		if(!mParentElement){ //for some reason i feel that we should catch this
			OG_THROW(Exception::ERR_INTERNAL_ERROR, "Cannot perform, I have no parent", "Element::sendToBack");
		}
		int upper, lower;
		mParentElement->getChildElementZOrderExtents(upper,lower);
		setZOrder(lower-1);
	}
	//#####################################################################
	void Element::bringToFront()
	{
		if(!mParentElement){ //for some reason i feel that we should catch this
			OG_THROW(Exception::ERR_INTERNAL_ERROR, "Cannot perform, I have no parent", "Element::bringToFront");
		}
		int upper, lower;
		mParentElement->getChildElementZOrderExtents(upper,lower);
		setZOrder(upper+1);
	}
	//#####################################################################
	FVector2 Element::convCoordLocalToWorld(FVector2 localCoord)
	{
		if(mParentElement){
			return mParentElement->convCoordInnerToWorld(localCoord);
		}else{
			return localCoord;
		}
	}
	//#####################################################################
	FVector2 Element::convCoordInnerToWorld(FVector2 innerCoord)
	{
		innerCoord=convCoordInnerToLocal(innerCoord);
		if(mParentElement){
			return mParentElement->convCoordInnerToWorld(innerCoord);
		}else{
			return innerCoord;
		}
	}
	//#####################################################################
	FVector2 Element::convCoordWorldToLocal(FVector2 worldCoord)
	{
		if(mParentElement){
			return mParentElement->convCoordWorldToInner(worldCoord);
		}else{
			return worldCoord;
		}
	}
	//#####################################################################
	FVector2 Element::convCoordWorldToInner(FVector2 worldCoord)
	{
		if(mParentElement){
			worldCoord=mParentElement->convCoordWorldToInner(worldCoord);
			return convCoordLocalToInner(worldCoord);
		}else{
			return convCoordLocalToInner(worldCoord);
		}
	}
	//#####################################################################
	FVector2 Element::convCoordInnerToLocal(FVector2 innerCoord)
	{
		switch(mClientAreaScaleType){
			case CAS_Custom:
				return performCustomScaleOperation_Inner2Local(innerCoord);
			case CAS_Inherit:
				return innerCoord = innerCoord + mClientRectOffset;
			case CAS_Absolute:
				return convCoordWorldToLocal(innerCoord + mClientRectOffset);
			case CAS_Scaled:
			default:
				return mElementRect.getOuterCoord(innerCoord + mClientRectOffset);
		};
	}
	//#####################################################################
	FVector2 Element::convCoordLocalToInner(FVector2 localCoord)
	{
		switch(mClientAreaScaleType){
			case CAS_Custom:
				return performCustomScaleOperation_Local2Inner(localCoord);
			case CAS_Inherit:
				return localCoord = localCoord - mClientRectOffset;
			case CAS_Absolute:
				return convCoordLocalToWorld(localCoord) - mClientRectOffset;
			case CAS_Scaled:
			default:
				return mElementRect.getInnerCoord(localCoord) - mClientRectOffset;
		};
	}
	//#####################################################################
	bool Element::pointIsInside(const FVector2& localPoint)
	{
		if(localPoint.x >= mElementRect.min.x &&
			localPoint.y >= mElementRect.min.y &&
			localPoint.x < mElementRect.max.x &&
			localPoint.y < mElementRect.max.y)
			return true;
		return false;
	}
	//#####################################################################
	bool Element::isDescendant(Element* elementPtr)
	{
		ChildElementList::iterator i = mChildrenElements.begin();
		while(i != mChildrenElements.end()){
			if((*i) == elementPtr){
				return true; //if we found it, then return true
			}else{
				//otherwise ask this child to search for it as well
				bool hasDescendant = (*i)->isDescendant(elementPtr);
				if(hasDescendant)
					return true; //if they found it, return true
			}
			i++;
		}
		return false; //it isn't here, return false
	}
	//#####################################################################
	bool Element::isDescendant(std::string elementName)
	{
		ChildElementList::iterator i = mChildrenElements.begin();
		while(i != mChildrenElements.end()){
			if((*i)->getName() == elementName){
				return true; //if we found it, then return true
			}else{
				//otherwise ask this child to search for it as well
				bool hasDescendant = (*i)->isDescendant(elementName);
				if(hasDescendant)
					return true; //if they found it, return true
			}
			i++;
		}
		return false; //it isn't here, return false
	}
	//#####################################################################
	Element* Element::_getDecendantElementAt(FVector2 innerPoint, const bool activeOnly)
	{
		ChildElementList::iterator i = mChildrenElements.begin();
		while(i != mChildrenElements.end()){
			
			if( (!activeOnly || (*i)->isEnabled()) && //only test isActive if we need
				( !(*i)->mClipsChildren || (*i)->pointIsInside(innerPoint) ) //and only test hit if we don't need active or we are active, and only if it is clipping children
			){
				Element* decendantHit;
				decendantHit = (*i)->_getDecendantElementAt( (*i)->convCoordLocalToInner(innerPoint) , activeOnly);
				if(decendantHit) //if this child has a hitting descendant, then return it
					return decendantHit;

				/* If the child does not clip children, we need to perform the hit
					test for JUST the child at this point. Boolean algebra would have
					culled out the previous call to this function, so there is no performance
					loss. This will be the first time the function was actually called, we
					just simply delayed it.
				*/
				if(!(*i)->mClipsChildren){ //if we didn't test the child for hit test before, do it now
					if((*i)->pointIsInside(innerPoint))
						return (*i); //return the child
				}else
					return (*i); //otherwise just return the child
			}
			i++;
		}
		return 0;
	}
	//#####################################################################
	Render::RenderOperationList Element::buildWidgetRenderOpList()
	{
		return Render::RenderOperationList();
	}
	//#####################################################################
	FVector2 Element::performCustomScaleOperation_Local2Inner(FVector2 localCoord)
	{
		FRect tmpRect;
		tmpRect.setPosition(FVector2(0.0f,0.0f));
		tmpRect.setSize(mClientRectCustomScale);

		return tmpRect.getInnerCoord(mElementRect.getInnerCoord(localCoord)) - mClientRectOffset;
	}
	//#####################################################################
	FVector2 Element::performCustomScaleOperation_Inner2Local(FVector2 innerCoord)
	{
		FRect tmpRect;
		tmpRect.setPosition(FVector2(0.0f,0.0f));
		tmpRect.setSize(mClientRectCustomScale);

		return mElementRect.getOuterCoord(tmpRect.getOuterCoord(innerCoord + mClientRectOffset));
	}
	//#####################################################################
	void Element::__buildRenderOperationList(Render::RenderOperationList& renderOpList)
	{
		//to ensure back to front ordering
		//first have all children add their render op lists using this same function
		//(in order of front to back visibility)
		ChildElementList::iterator iter = mChildrenElements.begin();
		while(iter != mChildrenElements.end()){
			Render::RenderOperationList childROList;
			(*iter)->__buildRenderOperationList(childROList);
			__transformChildrenRenderOperationList(childROList);
			if(mClipsChildren){
				Render::PrimitiveScissorRect srect;
				srect.setRect(mElementRect);
				srect.addRenderOperation(childROList);
				childROList = srect.getRenderOperationList();
			}
			Render::PrependRenderOperationList(renderOpList,childROList);
			childROList.clear();
			iter++;
		}
		

		//build our own widget render ops
		Render::RenderOperationList myROlist = buildWidgetRenderOpList();

		//and then push our ops to the front
		Render::PrependRenderOperationList(renderOpList,myROlist);
	}
	//#####################################################################
	void Element::__transformChildrenRenderOperationList(Render::RenderOperationList& renderOpList)
	{
		Render::RenderOperationList::iterator iter = renderOpList.begin();
		while(iter != renderOpList.end()){
			iter->vertices[0].position = convCoordInnerToLocal(iter->vertices[0].position);
			iter->vertices[1].position = convCoordInnerToLocal(iter->vertices[1].position);
			iter->vertices[2].position = convCoordInnerToLocal(iter->vertices[2].position);
			iter++;
		}
	}
	//#####################################################################
};

