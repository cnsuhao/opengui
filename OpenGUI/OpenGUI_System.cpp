
#include "corona.h"
#include "OpenGUI.h"
#include "OpenGUI_BaseWidgets.h"

namespace OpenGUI{
	//############################################################################
	template<> System* Singleton<System>::mptr_Singleton = 0;
	//############################################################################
	System& System::getSingleton(void)
	{
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	System* System::getSingletonPtr(void)
	{
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	//############################################################################
	//! \internal Just a little function to register all compiled in Widgets with the WidgetFactoryManager
	void RegisterAllBaseWidgets()
	{
		WidgetFactoryManager::getSingleton().registerWidgetFactory("OpenGUI", "StaticImage", WidgetFactoryCallback(&Widgets::StaticImage::createStaticImageFactory));
		WidgetFactoryManager::getSingleton().registerWidgetFactory("OpenGUI", "SimpleButton", WidgetFactoryCallback(&Widgets::SimpleButton::createSimpleButtonFactory));
	}
	//############################################################################
	System::System(Renderer* renderer, ResourceProvider* resourceProvider)
	{
		mTimerManager = new TimerManager; //get this up asap

		m_PerformAutoTicks = true;
		mRandomElementNameGeneratorIndex=0;
		mActiveGUISheet=0;
		m_CurrentMouseElement=0;
		mCapturerMouse=0;
		mCapturerKeyboard=0;
		mUserDblClickRate=500;
		mUserClickAccuracy=0.05f;
			
		assert(renderer);
		mRenderer = renderer;
		mRenderer->getViewportDimensions(mScreenResolution); //get the viewport resolution

		mWidgetFactoryManager = new WidgetFactoryManager();
		RegisterAllBaseWidgets(); //register base widget factories

		if(resourceProvider){
			mResourceProvider=resourceProvider;
			mUsingGenericResourceProvider=false;
		}
		else{
			mResourceProvider = new GenericResourceProvider();
			mUsingGenericResourceProvider=true;
		}

		mImageryManager = new ImageryManager(); //create the imagery manager
		mCursorManager = new CursorManager(); //create the cursor manager

		//Cursor MUST be done AFTER renderer and CursorManager is set up
		mDefaultCursor="DefaultCursor"; //default cursor starts as DefaultCursor
		mCursorPosition = FVector2(0.5f,0.5f); //cursor starts in middle of screen
		mCursorVisible=true; //cursor starts visible
		mCursorManager->setCursor(mDefaultCursor);
	}
	//############################################################################
	System::~System()
	{
		System::_destroyAllGUISheets();

		if(mCursorManager )
			delete mCursorManager;

		if(mImageryManager)
			delete mImageryManager;

		if(mUsingGenericResourceProvider)
			delete mResourceProvider;

		if(mWidgetFactoryManager)
			delete mWidgetFactoryManager;

		if(mTimerManager)
			delete mTimerManager; //delete this last
	}
	//############################################################################
	FVector2 System::getAspectCorrection()
	{
		return FVector2(
			(float)mScreenResolution.y / (float)mScreenResolution.x,
			(float)mScreenResolution.x / (float)mScreenResolution.y
		);
	}
	//############################################################################
	std::string System::generateRandomElementName()
	{
		std::stringstream ss;
		std::string retval;
		time_t timer;
		time(&timer); //NOTE: This function call will break after 19:14:07, January 18, 2038, UTC
		ss << "__OPENGUI_RANDOM__:" << (unsigned int)timer << ":" << mRandomElementNameGeneratorIndex;
		retval = ss.str();
		mRandomElementNameGeneratorIndex++;
		//now test the result, and only issue it if we are sure it is not used
		if(getElementByName(retval))
			return System::generateRandomElementName();
		return retval;
	}
	//############################################################################
	Element* System::getElementByName(std::string name)
	{
		Element* retval=0;
		//first test the active gui sheet, as we have a better chance of finding it there
		if(mActiveGUISheet){
			retval = mActiveGUISheet->getChildElement(name);
		}
		if(retval)
			return retval;
		//if we didn't find it, then we need to search all the other gui sheets
		GUISheetList::iterator gsi = mGUISheetList.begin();
		while(gsi != mGUISheetList.end()){
			if((*gsi) != mActiveGUISheet){
				retval = (*gsi)->getChildElement(name);
				if(retval)
					return retval;
			}
			gsi++;
		}
		return retval;
	}
	//############################################################################
	void System::injectEvent(Msg::Message message)
	{
		//! \todo try to do more to make this exception safe
		if(message.messageType==message.MT_EVENT){
			if(message.event.destination == 0){
				//!\todo don't forget that when we add modal gui sheets we will need to fix this
				//send event as global down active sheet
				if(mActiveGUISheet){
					mActiveGUISheet->_propogateGlobalEvent(message);
				}
			}else{
				//!\todo don't forget that when we add modal gui sheets we will need to fix this too
				//send event as directed down active sheet
				ElementAncestryList destAncestryList;
				message.event.destination->buildElementAncestry(destAncestryList);
				if((destAncestryList.front()) == mActiveGUISheet){
					mActiveGUISheet->_propogateEvent(message,destAncestryList);
				}
			}
		}else if(message.messageType=message.MT_ALERT){
			//!\todo we will eventually need to do something here
		}
	}
	//############################################################################
	GUISheet* System::createGUISheet(std::string name)
	{
		std::string sheetName;
		if(name=="")
			sheetName = generateRandomElementName();
		else
			sheetName=name;
		GUISheet* retval = new GUISheet(sheetName);
		if(retval){
			mGUISheetList.push_back(retval);
		}
		return retval;
	}
	//############################################################################
	void System::destroyGUISheet(GUISheet* guiSheetPtr)
	{
		//can't have an active sheet that doesn't exist
		if(guiSheetPtr == mActiveGUISheet)
			System::setGUISheet(0);

		GUISheetList::iterator gsi = mGUISheetList.begin();
		while(gsi != mGUISheetList.end()){
			if((*gsi) == guiSheetPtr){
				delete (*gsi);
				mGUISheetList.erase(gsi);
				return;
			}
		}
		throw Exception("System::destroyGUISheet():GUISheet not found");
	}
	//############################################################################
	GUISheet* System::getGUISheetByName(std::string name)
	{
		GUISheetList::iterator gsi = mGUISheetList.begin();
		while(gsi != mGUISheetList.end()){
			if((*gsi)->getName() == name)
				return (*gsi);
		}
		return 0;
	}
	//############################################################################
	void System::setGUISheet(GUISheet* guiSheetPtr)
	{
		if(mActiveGUISheet)
			_issueGUISheetDeactivate();
		_tmPurgeTracks();
		mActiveGUISheet = guiSheetPtr;
		if(guiSheetPtr)
			_issueGUISheetActivate();
	}
	//############################################################################
	void System::_destroyAllGUISheets()
	{
		setGUISheet(0);
		GUISheetList::iterator gsi = mGUISheetList.begin();
		while(gsi != mGUISheetList.end()){
			delete (*gsi);
			gsi++;
		}
		mGUISheetList.clear();
	}
	//############################################################################
	Element* System::getElementAt(FVector2 screenLoc, GUISheet* sheet, bool activeOnly)
	{
		if(!sheet){
			if(mActiveGUISheet)
				sheet = mActiveGUISheet;
			else
				return 0; //no sheet and no mActiveGUISheet means no results
		}
		return sheet->_getDecendantElementAt(screenLoc, activeOnly);
	}
	//############################################################################
	void System::notifyViewportDimensionsChanged()
	{
		//!\todo make sure this is all that needs to be done to properly handle viewport dimension changes
		mRenderer->getViewportDimensions(mScreenResolution);
	}
	//############################################################################
	void System::renderGUI()
	{
		if(m_PerformAutoTicks) //only do this if we aren't getting time injections from the app
			mTimerManager->_DoAutoTickInject();

		if(mActiveGUISheet){
			Render::RenderOperationList renderOpList;
			mActiveGUISheet->__buildRenderOperationList(renderOpList);

			mRenderer->preRenderSetup();
			Render::RenderOperationList::iterator iter = renderOpList.begin();
			while(iter != renderOpList.end()){
				mRenderer->doRenderOperation((*iter));
				iter++;
			}

			
			Render::RenderOperationList renderOpList_Cursor;
			renderOpList_Cursor = mCursorManager->getCursorRenderOpList();

			Render::RenderOperationList::iterator iterC = renderOpList_Cursor.begin();
			while(iterC != renderOpList_Cursor.end()){
				mRenderer->doRenderOperation((*iterC));
				iterC++;
			}
			

			mRenderer->postRenderCleanup();
		}
	}
	//############################################################################
	void System::_issueTickEvent(unsigned long timeDelta)
	{
		if(timeDelta>0){		
			Msg::Message msg;
			msg.messageType=msg.MT_EVENT;
			msg.event.destination=0;
			msg.event.type=msg.event.ME_Tick;
			Msg::EventData::TickEvent tickEvt;
			msg.event.eventData=(void*)&tickEvt;
			tickEvt.timeDelta=timeDelta;

			injectEvent(msg);
		}
		_handleDblClickWashout(); //test & clean mouse button click states
	}
	//############################################################################
	FVector2 System::getCursorPos()
	{
		return mCursorPosition;
	}
	//############################################################################
	void System::showCursor()
	{
		mCursorVisible = true;
	}
	//############################################################################
	void System::hideCursor()
	{
		mCursorVisible = false;
	}
	//############################################################################
	void System::setDefaultCursor(std::string defaultCursorName)
	{
		mDefaultCursor = defaultCursorName;
	}
	//############################################################################
	std::string System::_getCurrentCursorName()
	{
		return mDefaultCursor;
	}
	//############################################################################
	void System::injectTick(unsigned int timeDeltaInMilliseconds)
	{
		mTimerManager->_addTime(timeDeltaInMilliseconds);
		_issueTickEvent(timeDeltaInMilliseconds);
	}
	//############################################################################
	void System::injectMousePosition(float x_pos, float y_pos)
	{
		FVector2 newPos = FVector2(x_pos,y_pos);

		//clamp the position values
		if(newPos.x < 0.0f) newPos.x = 0.0f;
		if(newPos.x > 1.0f) newPos.x = 1.0f;
		if(newPos.y < 0.0f) newPos.y = 0.0f;
		if(newPos.y > 1.0f) newPos.y = 1.0f;

		if(mCursorPosition != newPos){
			mCursorPosition = newPos;
			_handleMouseMovement();
		}
	}
	//############################################################################
	void System::injectMouseMovement(float x_delta, float y_delta)
	{
		mCursorPosition.x += x_delta;
		mCursorPosition.y += y_delta;

		//clamp the position values
		if(mCursorPosition.x < 0.0f) mCursorPosition.x = 0.0f;
		if(mCursorPosition.x > 1.0f) mCursorPosition.x = 1.0f;
		if(mCursorPosition.y < 0.0f) mCursorPosition.y = 0.0f;
		if(mCursorPosition.y > 1.0f) mCursorPosition.y = 1.0f;

		if(x_delta!= 0.0f || y_delta != 0.0f){
			_handleMouseMovement();
		}
	}
	//############################################################################
	void System::injectMouseButtonDown(MouseButton buttonId)
	{
		_handleMouseButtonDown(buttonId);
	}
	//############################################################################
	void System::injectMouseButtonUp(MouseButton buttonId)
	{
		_handleMouseButtonUp(buttonId);
	}
	//############################################################################
	void System::setUserDblClickRate(unsigned int millisecondDelay)
	{
		mUserDblClickRate=millisecondDelay;
	}
	//############################################################################
	void System::setUserClickAccuracy(float radius)
	{
		mUserClickAccuracy=radius;
	}
	//############################################################################
	void System::setAutoTick(bool useAutoTick)
	{
		m_PerformAutoTicks = useAutoTick;
	}
	//############################################################################
	Element* System::getCaptureMouse()
	{
		return mCapturerMouse;
	}
	//############################################################################
	Element* System::getCaptureKeyboard()
	{
		return mCapturerKeyboard;
	}
	//############################################################################
	void System::setCaptureMouse(Element* capturingElement)
	{
		mCapturerMouse=capturingElement;
	}
	//############################################################################
	void System::setCaptureKeyboard(Element* capturingElement)
	{
		mCapturerKeyboard=capturingElement;
	}
	//############################################################################
	Element* System::_getMouseEventDestination()
	{
		if(mCapturerMouse)
			return mCapturerMouse; //return current capturer if one exists
		return getElementAt(getCursorPos(),0,true); //otherwise just return element under mouse
	}
	//############################################################################
	bool System::setTrackMouseLeave(Element* elementToTrack)
	{
		//do not register null, or anything while we are purging
		if(m_tmPurging || !elementToTrack) return false;

		//it passes all the tests, add it to the track list
		if(_tmMeetsTrackCriteria(elementToTrack)){
			_tmAddElement(elementToTrack);
			return true;
		}
		return false;	
	}
	//############################################################################
	bool System::_tmMeetsTrackCriteria(Element* elementToTest, Element* elementUnderMouse)
	{
		//anything null fails
		if(!elementToTest) return false;
		if(!elementUnderMouse) elementUnderMouse = m_CurrentMouseElement;

		//perform tests
		//mouse is currently in element rect?
		FVector2 mousePos = getCursorPos();
		mousePos = elementToTest->convCoordWorldToLocal(mousePos);
		if(!elementToTest->pointIsInside(mousePos))
			return false; //mouse is already not inside the element

		//mouse is over the requesting element, or a child?
		if(elementUnderMouse != elementToTest){
			if(!elementToTest->isDescendant(elementUnderMouse))
				return false;
		}

		//it passes all the tests, add it to the track list
		return true;
	}
	//############################################################################
	void System::_tmAddElement(Element* trackedElement)
	{
		if(trackedElement==0) return;
		_tmRemoveElement(trackedElement);
		mTrackMouseList.push_front(trackedElement);
	}
	//############################################################################
	void System::_tmRemoveElement(Element* trackedElement)
	{
		ElementList::iterator iter = mTrackMouseList.begin();
		while(iter != mTrackMouseList.end()){
			if((*iter)==trackedElement){
				mTrackMouseList.erase(iter);
				return;
			}
			iter++;
		}
	}
	//############################################################################
	void System::_tmPurgeTracks()
	{
		m_tmPurging=true;
		ElementList::iterator iter = mTrackMouseList.begin();
		while(iter != mTrackMouseList.end()){
			_issueMouseLeaveEvent((*iter));
			iter++;
		}
		mTrackMouseList.clear();
		m_tmPurging=false;
	}
	//############################################################################
	bool System::_tmPerformMouseTrackTests(Element* elementUnderMouse)
	{
		ElementList tmpList = mTrackMouseList; //we need to work with a copy of the track list, or we risk weird STL crashes
		ElementList::iterator iter = tmpList.begin();
		while(iter != tmpList.end()){
			if(!_tmMeetsTrackCriteria((*iter),elementUnderMouse)){
				Element* tmp = (*iter);
				_tmRemoveElement(tmp);
				_issueMouseLeaveEvent(tmp);
				return true;
			}
			iter++;
		}
		return false;
	}
	//############################################################################
	void System::_issueGUISheetActivate()
	{
		Msg::Message msg;
		msg.messageType=msg.MT_EVENT;
		msg.event.destination=0;
		msg.event.type=msg.event.ME_GUISheetActivate;
		msg.event.eventData=0;
		injectEvent(msg);
	}
	//############################################################################
	void System::_issueGUISheetDeactivate()
	{
		Msg::Message msg;
		msg.messageType=msg.MT_EVENT;
		msg.event.destination=0;
		msg.event.type=msg.event.ME_GUISheetDeactivate;
		msg.event.eventData=0;
		injectEvent(msg);
	}
	//############################################################################
	void System::_issueMouseMoveEvent()
	{
		Msg::Message msg;
		msg.messageType=msg.MT_EVENT;
		msg.event.destination=_getMouseEventDestination();
		msg.event.type=msg.event.ME_MouseMove;
		Msg::EventData::MouseMoveEvent moveEvt;
		msg.event.eventData=(void*)&moveEvt;
		moveEvt.mousePosition=mCursorPosition;
		injectEvent(msg);
	}
	//############################################################################
	void System::_issueMouseEnterEvent(Element* elementEntered)
	{
		Msg::Message msg;
		msg.messageType=msg.MT_EVENT;
		msg.event.destination=elementEntered;
		msg.event.type=msg.event.ME_MouseEnter;
		msg.event.eventData=0;
		injectEvent(msg);
	}
	//############################################################################
	void System::_issueMouseLeaveEvent(Element* elementLeft)
	{
		Msg::Message msg;
		msg.messageType=msg.MT_EVENT;
		msg.event.destination=elementLeft;
		msg.event.type=msg.event.ME_MouseLeave;
		msg.event.eventData=0;
		injectEvent(msg);
	}
	//############################################################################
	void System::_issueMouseButtonUpEvent(MouseButton buttonId)
	{
		Msg::Message msg;
		msg.messageType=msg.MT_EVENT;
		msg.event.destination=_getMouseEventDestination();
		msg.event.type=msg.event.ME_MouseButtonUp;
		Msg::EventData::MouseButtonEvent buttonEvt;
		msg.event.eventData=(void*)&buttonEvt;
		buttonEvt.mouseButtonID = buttonId;
		injectEvent(msg);
	}
	//############################################################################
	void System::_issueMouseButtonDownEvent(MouseButton buttonId)
	{
		Msg::Message msg;
		msg.messageType=msg.MT_EVENT;
		msg.event.destination=_getMouseEventDestination();
		msg.event.type=msg.event.ME_MouseButtonDown;
		Msg::EventData::MouseButtonEvent buttonEvt;
		msg.event.eventData=(void*)&buttonEvt;
		buttonEvt.mouseButtonID = buttonId;
		injectEvent(msg);
	}
	//############################################################################
	void System::_issueMouseButtonClickEvent(MouseButton buttonId)
	{
		Msg::Message msg;
		msg.messageType=msg.MT_EVENT;
		msg.event.destination=_getMouseEventDestination();
		msg.event.type=msg.event.ME_MouseClick;
		Msg::EventData::MouseButtonEvent buttonEvt;
		msg.event.eventData=(void*)&buttonEvt;
		buttonEvt.mouseButtonID = buttonId;
		injectEvent(msg);
	}
	//############################################################################
	void System::_issueMouseButtonDblClickEvent(MouseButton buttonId)
	{
		Msg::Message msg;
		msg.messageType=msg.MT_EVENT;
		msg.event.destination=_getMouseEventDestination();
		msg.event.type=msg.event.ME_MouseDblClick;
		Msg::EventData::MouseButtonEvent buttonEvt;
		msg.event.eventData=(void*)&buttonEvt;
		buttonEvt.mouseButtonID = buttonId;
		injectEvent(msg);
	}
	//############################################################################
	void System::_handleMouseMovement()
	{
		Element* elementMouseEvtDest = _getMouseEventDestination();
		//if(m_CurrentMouseElement != elementMouseEvtDest){
			if(_tmPerformMouseTrackTests(elementMouseEvtDest)){
				//we processed a track event, we need to retest the event target!
				elementMouseEvtDest = _getMouseEventDestination();
			}
			if(m_CurrentMouseElement != elementMouseEvtDest){
				//the event destination still needs to change
				m_CurrentMouseElement = elementMouseEvtDest; //save the new CurrentMouseElement
				if(elementMouseEvtDest!=0) //can't enter null Element
					_issueMouseEnterEvent(elementMouseEvtDest); //issue the enter event
			}
			_issueMouseMoveEvent();//issue movement
		//}else{
			//mouse event receiver has not changed, simply send the message
			//note: if m_CurrentMouseElement == 0, then it will be a global event, but that's okay for now
		//	_issueMouseMoveEvent();
		//}
	}
	//############################################################################
	void System::_handleDblClickWashout()
	{	//reset mouse button press flags if they overflow their timers
		//(This fixes the "only every other click can ever BE a DblClick" problem)
		for(unsigned int c=0; c<3; c++){
			if(m_MouseButtonFirstPress[c])
				if(mTimerManager->getMillisecondsSinceStart() - m_MouseButtonDownTime[c] > mUserDblClickRate)
					m_MouseButtonFirstPress[c]=false;
		}
	}
	//############################################################################
	void System::_handleMouseButtonDown(MouseButton buttonId)
	{
		_issueMouseButtonDownEvent(buttonId);

		if(m_MouseButtonFirstPress[buttonId] == false){
			//on first time down, save the position and time
			m_MouseButtonFirstPress[buttonId] = true;
			m_MouseButtonDownPosition[buttonId] = mCursorPosition;
			m_MouseButtonDownTime[buttonId] = mTimerManager->getMillisecondsSinceStart();
			m_MouseButtonClickElement[buttonId] = getElementAt(mCursorPosition);
		}else{
			//this is the 2nd time down, should we generate a DblClick?
			if(	mTimerManager->getMillisecondsSinceStart() - m_MouseButtonDownTime[buttonId] <= mUserDblClickRate && //clicked in time
			(m_MouseButtonDownPosition[buttonId] - mCursorPosition).length() <= mUserClickAccuracy) //within the accuracy radius
			{
				_issueMouseButtonDblClickEvent(buttonId);
			}
			m_MouseButtonFirstPress[buttonId] = false; //always reset
			m_MouseButtonClickElement[buttonId] = 0; //reset this too
		}
	}
	//############################################################################
	void System::_handleMouseButtonUp(MouseButton buttonId)
	{
		_issueMouseButtonUpEvent(buttonId);

		//is this the first time we were down?
		if(m_MouseButtonClickElement[buttonId]){
			if(	getElementAt(mCursorPosition) == m_MouseButtonClickElement[buttonId] && //still over the same element
				(m_MouseButtonDownPosition[buttonId] - mCursorPosition).length() <= mUserClickAccuracy) //and within the accuracy radius
			{
				_issueMouseButtonClickEvent(buttonId);
				m_MouseButtonClickElement[buttonId]=0;
			}
		}
	}
	//############################################################################
};//namespace OpenGUI{


