
#include "OpenGUI.h"
#include "OpenGUI_RenderCache.h"


namespace OpenGUI{
	//#####################################################################
	GUISheet::GUISheet(std::string name)
	{
		mObjectName=name;
		mElementRect.min = FVector2(0.0f,0.0f);
		mElementRect.max = FVector2(1.0f,1.0f);
	}
	//#####################################################################
	void GUISheet::renderGUISheet(Renderer* rendererPtr)
	{
		if(mRenderCache){
			Render::RenderOperationList::iterator iter = mRenderCache->getCacheLiteral().begin();
			while(iter != mRenderCache->getCacheLiteral().end()){
				rendererPtr->doRenderOperation((*iter));
				iter++;
			}
		}else{
			Render::RenderOperationList renderOpList;
			__getRenderOperationList_Children(renderOpList);
			__getRenderOperationList_This(renderOpList);

			Render::RenderOperationList::iterator iter = renderOpList.begin();
			while(iter != renderOpList.end()){
				rendererPtr->doRenderOperation((*iter));
				iter++;
			}
		}
	}
	//#####################################################################
};//namespace OpenGUI{

