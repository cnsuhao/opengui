
#include "OpenGUI_Primitives_Geometric.h"
#include "OpenGUI_System.h"
#include "OpenGUI_Element.h"

namespace OpenGUI{
namespace Render{
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
			ropA.vertices[0].maskUV = ropA.vertices[0].textureUV = FVector2(0.0f, 0.0f);
			ropA.vertices[1].maskUV = ropA.vertices[1].textureUV = FVector2(0.0f, 1.0f);
			ropA.vertices[2].maskUV = ropA.vertices[2].textureUV = FVector2(1.0f, 1.0f);
			ropA.texture = 0;
			ropB.vertices[0].maskUV = ropB.vertices[0].textureUV = FVector2(0.0f, 0.0f);
			ropB.vertices[1].maskUV = ropB.vertices[1].textureUV = FVector2(1.0f, 1.0f);
			ropB.vertices[2].maskUV = ropB.vertices[2].textureUV = FVector2(1.0f, 0.0f);

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
	//############################################################################
	//############################################################################

	//############################################################################
	//############################################################################
	//############################################################################
	RenderOperationList PrimitiveBoxOutline::getRenderOperationList()
	{
		//this is the ultra dirty/quick implementation. The corners of the outline will overlap
		FVector2 pixelScale = PrimitiveBoxOutline::_getPixelScale();
		RenderOperationList retList;
		PrimitiveBox box;
		FRect rect;

		//Top line
		rect = mRect;
		rect.setHeight( pixelScale.y * mThickness );
		box.setRect(rect);
		AppendRenderOperationList(retList, box.getRenderOperationList());

		//Bottom line
		rect.offset( FVector2(0.0f, mRect.getHeight() - rect.getHeight()) );
		box.setRect(rect);
		AppendRenderOperationList(retList, box.getRenderOperationList());

		//Left line
		rect = mRect;
		rect.setWidth( pixelScale.x * mThickness );
		box.setRect(rect);
		AppendRenderOperationList(retList, box.getRenderOperationList());

		//Right line
		rect.offset( FVector2(mRect.getWidth() - rect.getWidth(), 0.0f) );
		box.setRect(rect);
		AppendRenderOperationList(retList, box.getRenderOperationList());

		return retList;
	}
	//############################################################################
	FVector2 PrimitiveBoxOutline::_getPixelScale()
	{
		FVector2 floatDims;
		IRect pixelRect;
		if(mContext){
			//get the pixel space available as this level
			pixelRect = mContext->getPixelRect();
			floatDims = mContext->getRect().getSize();
		}else{
			//best we can do here is assume that we are drawing directly to the viewport
			pixelRect.setSize(System::getSingleton().getViewportResolution());
			floatDims = FVector2(1.0f,1.0f);
		}

		FVector2 pixelScale = FVector2( floatDims.x / pixelRect.getWidth(), floatDims.y / pixelRect.getHeight() ); 
		return pixelScale;
	}
	//############################################################################
	//############################################################################
};//namespace Render{
};//namespace OpenGUI{

