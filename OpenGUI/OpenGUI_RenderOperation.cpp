#include "OpenGUI.h"

namespace OpenGUI{
	namespace Render{
		//############################################################################
		void AppendRenderOperationList(RenderOperationList& outList, RenderOperationList& inList)
		{
			RenderOperationList::iterator roli = inList.begin();
			while(roli != inList.end()){
				outList.push_back((*roli));
				roli++;
			}
		}
		//############################################################################
		void PrependRenderOperationList(RenderOperationList& outList, RenderOperationList& inList)
		{
			if(inList.size() == 0) return;			
			RenderOperationList::reverse_iterator roli = inList.rbegin();
			while(roli != inList.rend()){
				outList.push_front((*roli));
				roli++;
			}
		}
		//############################################################################
		RenderOperationList PrimitiveBox::getRenderOperationList()
		{
		/*	------
			|\  B|   0\0  2
			| \  |     \ B
			|  \ |    A \
			| A \|   1  2\1
			------
		*/
			RenderOperation ropA,ropB;
			
			ropA.vertices[0].position=mRect.min;
			ropA.vertices[1].position=FVector2(mRect.min.x,mRect.max.y);
			ropA.vertices[2].position=mRect.max;

			ropB.vertices[0].position=mRect.min;
			ropB.vertices[1].position=mRect.max;
			ropB.vertices[2].position=FVector2(mRect.max.x,mRect.min.y);
			
			if(mTextureImagery){
				FRect tRect;
				tRect = mTextureImagery->getTextureUVRect();
				ropA.texture = mTextureImagery->getTexture();
				ropB.texture = mTextureImagery->getTexture();

				ropA.vertices[0].textureUV=tRect.min;
				ropA.vertices[1].textureUV=FVector2(tRect.min.x,tRect.max.y);
				ropA.vertices[2].textureUV=tRect.max;

				ropB.vertices[0].textureUV=tRect.min;
				ropB.vertices[1].textureUV=tRect.max;
				ropB.vertices[2].textureUV=FVector2(tRect.max.x,tRect.min.y);
			}else{
				ropA.texture = 0;
				ropB.texture = 0;
			}

			if(mMaskImagery){
				FRect tRect;
				tRect = mMaskImagery->getTextureUVRect();
				ropA.mask = mMaskImagery->getTexture();
				ropB.mask = mMaskImagery->getTexture();

				ropA.vertices[0].maskUV=tRect.min;
				ropA.vertices[1].maskUV=FVector2(tRect.min.x,tRect.max.y);
				ropA.vertices[2].maskUV=tRect.max;

				ropB.vertices[0].maskUV=tRect.min;
				ropB.vertices[1].maskUV=tRect.max;
				ropB.vertices[2].maskUV=FVector2(tRect.max.x,tRect.min.y);
			}else{
				ropA.mask = 0;
				ropB.mask = 0;
			}

			RenderOperationList ropList;
			ropList.push_back(ropA);
			ropList.push_back(ropB);
			return ropList;
		}
		//############################################################################
	

		RenderOperationList PrimitiveScissorRect::getRenderOperationList()
		{
			return RenderOperationList();
		}
		//############################################################################
	};//namespace Render{
};