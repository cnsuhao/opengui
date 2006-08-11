

#include "OpenGUI_PreRequisites.h"

#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Element.h"
#include "OpenGUI_RenderOperation.h"
#include "OpenGUI_RenderCache.h"




namespace OpenGUI{

	//############################################################################
	void RenderCache::markDirty()
	{
		mDirty = true;
		mMyCache.clear();
	}
	//############################################################################
	bool RenderCache::isDirty()
	{
		return mDirty;
	}
	//############################################################################
	size_t RenderCache::statCacheSize()
	{
		return sizeof(Render::RenderOperation) * mMyCache.size();
	}
	//############################################################################
	void RenderCache::getCache(Render::RenderOperationList& renderOpList)
	{
		if(mDirty){
			//rebuild cache
			RenderCache::buildCache();
		}
		Render::PrependRenderOperationList(renderOpList,mMyCache);
	}
	//############################################################################
	void RenderCache::buildCache()
	{
		RenderCache::markDirty();

		mParent->__getRenderOperationList_Children(mMyCache);
		mParent->__getRenderOperationList_This(mMyCache);

		mDirty = false;
	}
	//############################################################################
	Render::RenderOperationList& RenderCache::getCacheLiteral()
	{
		if(mDirty){
			//rebuild cache
			RenderCache::buildCache();
		}
		return mMyCache;
	}
	//############################################################################
}
