
#include "OpenGUI.h"

namespace OpenGUI{
	//############################################################################
	template<> CursorManager* Singleton<CursorManager>::mptr_Singleton = 0;
	//############################################################################
	CursorManager& CursorManager::getSingleton(void)
	{
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	CursorManager* CursorManager::getSingletonPtr(void)
	{
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	//############################################################################
	CursorManager::CursorManager()
	{
		LogManager::SlogMsg("INIT", OGLL_INFO2) << "Creating CursorManager" << Log::endlog;
		mCurrentCursorPtr=0;
		mCurrentCursorStr="";
		mCurrentCursorInvalid=false;
	}
	//############################################################################
	CursorManager::~CursorManager()
	{
		LogManager::SlogMsg("SHUTDOWN", OGLL_INFO2) << "Destroying CursorManager" << Log::endlog;
		destroyAllCursors();
	}
	//############################################################################
	void CursorManager::addCursor(Cursor* cursorPtr, std::string name)
	{
		LogManager::SlogMsg("CursorManager", OGLL_INFO) << "Add Cursor: "
			<< "\"" << name << "\" <" << ((void*)cursorPtr) << ">" << Log::endlog;
			

		Cursor* tmpCursor = CursorManager::getCursor(name);
		if(tmpCursor)
			CursorManager::destroyCursor(tmpCursor);
		mCursorMap[name]=cursorPtr;
	}
	//############################################################################
	Cursor* CursorManager::getCursor(std::string name)
	{
		CursorPtrMap::iterator cpmiter = mCursorMap.find(name);
		if(mCursorMap.end() != cpmiter){
			return cpmiter->second;
		}
		return 0;
	}
	//############################################################################
	void CursorManager::destroyCursor(std::string name)
	{
		LogManager::SlogMsg("CursorManager", OGLL_INFO) << "Destroy Cursor: "
			<< "\"" << name << "\"" << Log::endlog;

		CursorPtrMap::iterator iter = mCursorMap.find(name);
		if(iter != mCursorMap.end()){
			CursorManager::cursorUnregisterDraw(iter->second);
			delete iter->second;
			mCursorMap.erase(iter);
		}
	}
	//############################################################################
	void CursorManager::destroyCursor(Cursor* cursorPtr)
	{
		LogManager::SlogMsg("CursorManager", OGLL_INFO) << "Destroy Cursor: "
			<< "<" << ((void*)cursorPtr) << ">" << Log::endlog;

		CursorPtrMap::iterator iter = mCursorMap.begin();
		while(iter != mCursorMap.end()){
			if(iter->second == cursorPtr){
				CursorManager::cursorUnregisterDraw(iter->second);
				delete iter->second;
				mCursorMap.erase(iter);
				return;
			}
			iter++;
		}
	}
	//############################################################################
	void CursorManager::removeCursor(Cursor* cursorPtr)
	{
		LogManager::SlogMsg("CursorManager", OGLL_INFO) << "Remove Cursor: "
			<< "<" << ((void*)cursorPtr) << ">" << Log::endlog;

		CursorPtrMap::iterator iter = mCursorMap.begin();
		while(iter != mCursorMap.end()){
			if(iter->second == cursorPtr){
				if(isCursorDrawRegistered(cursorPtr))
					CursorManager::cursorUnregisterDraw(cursorPtr);
				mCursorMap.erase(iter);
				return;
			}
			iter++;
		}
	}
	//############################################################################
	void CursorManager::destroyAllCursors()
	{
		LogManager::SlogMsg("CursorManager", OGLL_INFO) << "Destroy All Cursors..." << Log::endlog;

		CursorPtrMap::iterator iter = mCursorMap.begin();
		while(iter != mCursorMap.end()){
			delete iter->second;
			iter++;
		}
		mCursorMap.clear();
		mCursorDrawList.clear();
	}
	//############################################################################
	void CursorManager::cursorRegisterDraw(Cursor* cursorPtr)
	{
		LogManager::SlogMsg("CursorManager", OGLL_INFO2) << "cursorRegisterDraw: "
			<< "<" << ((void*)cursorPtr) << ">" << Log::endlog;

		if(!cursorPtr) return; //don't register null
		if(!isCursorRegistered(cursorPtr)) return; //don't register something we don't know about

		if(CursorManager::isCursorDrawRegistered(cursorPtr)){
			LogManager::SlogMsg("CursorManager", OGLL_WARN) << "Removing duplicate cursorRegisterDraw entry: "
				<< "<" << ((void*)cursorPtr) << ">" << Log::endlog;
			CursorManager::cursorUnregisterDraw(cursorPtr); //first remove this ptr if we already have it
		}
		mCursorDrawList.push_back(cursorPtr); //new pointers go to the back of the list (last to draw, so on top)
	}
	//############################################################################
	void CursorManager::cursorUnregisterDraw(Cursor* cursorPtr)
	{
		LogManager::SlogMsg("CursorManager", OGLL_INFO2) << "cursorUnregisterDraw: "
			<< "<" << ((void*)cursorPtr) << ">" << Log::endlog;

		//for this we simply run the entire list and remove the first hit we find
		//(there will only ever be one hit, if any)
		CursorPtrList::iterator iter = mCursorDrawList.begin();
		while(iter != mCursorDrawList.end()){
			if(cursorPtr == (*iter)){
				mCursorDrawList.erase(iter);
				return;
			}
			iter++;
		}
		OG_THROW(Exception::ERR_ITEM_NOT_FOUND, "Cursor not found in Draw List", "CursorManager::cursorUnregisterDraw");
	}
	//############################################################################
	bool CursorManager::isCursorRegistered(Cursor* cursorPtr)
	{
		CursorPtrMap::iterator iter = mCursorMap.begin();
		while(iter != mCursorMap.end()){
			if(iter->second == cursorPtr){
				return true;
			}
			iter++;
		}
		return false;
	}
	//############################################################################
	bool CursorManager::isCursorDrawRegistered(Cursor* cursorPtr)
	{
		CursorPtrList::iterator iter = mCursorDrawList.begin();
		while(iter != mCursorDrawList.end()){
			if((*iter) == cursorPtr)
				return true;
			iter++;
		}
		return false;
	}
	//############################################################################
	Render::RenderOperationList CursorManager::getCursorRenderOpList()
	{
		//do this every time we generate a renderoplist, to make sure the proper cursor is loaded
        CursorManager::_updateCursor();

		Render::RenderOperationList ropList;
		Render::RenderOperationList ropList2;
		CursorPtrList::iterator iter = mCursorDrawList.begin();
		while(iter != mCursorDrawList.end()){
			Render::AppendRenderOperationList(ropList, ropList2 = (*iter)->getCursorRenderOpList());
			iter++;
		}
		return ropList;
	}
	//############################################################################
	void CursorManager::setCursor(std::string cursorName)
	{
		mCurrentCursorStr=cursorName;

		//special case when we purposefully set no cursor at all
		if(cursorName==""){
			CursorManager::_changeCursor(0);
			mCurrentCursorInvalid=false;
		}

		Cursor* tmpCursorPtr;
		tmpCursorPtr = CursorManager::getCursor(cursorName);

		if(tmpCursorPtr){
			CursorManager::_changeCursor(tmpCursorPtr);
			mCurrentCursorInvalid=false;
		}else{
			mCurrentCursorInvalid=true;
		}
	}
	//############################################################################
	void CursorManager::_changeCursor(Cursor* newCursor)
	{
		if(mCurrentCursorPtr)
			mCurrentCursorPtr->hide();

		mCurrentCursorPtr = newCursor;

		if(mCurrentCursorPtr)
			mCurrentCursorPtr->show();
	}
	//############################################################################
	void CursorManager::_updateCursor()
	{
		if(mCurrentCursorInvalid)
			CursorManager::setCursor(mCurrentCursorStr);
	}
	//############################################################################
};//namespace OpenGUI{

