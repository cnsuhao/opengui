
#include "OpenGUI.h"
#include "OpenGUI_ScalingImage.h"


namespace OpenGUI{
	namespace Widgets{

		//#####################################################################
		Widget* ScalingImage::createScalingImageFactory()
		{
			return new ScalingImage;
		}
		//#####################################################################
		ScalingImage::ScalingImage()
		{
			PropertySet_BindProperty("Imagery_UL", OpenGUI::PT_STRING, &ScalingImage::_prop_SetImagery, &ScalingImage::_prop_GetImagery);
			PropertySet_BindProperty("Imagery_UM", OpenGUI::PT_STRING, &ScalingImage::_prop_SetImagery, &ScalingImage::_prop_GetImagery);
			PropertySet_BindProperty("Imagery_UR", OpenGUI::PT_STRING, &ScalingImage::_prop_SetImagery, &ScalingImage::_prop_GetImagery);

			PropertySet_BindProperty("Imagery_ML", OpenGUI::PT_STRING, &ScalingImage::_prop_SetImagery, &ScalingImage::_prop_GetImagery);
			PropertySet_BindProperty("Imagery_MM", OpenGUI::PT_STRING, &ScalingImage::_prop_SetImagery, &ScalingImage::_prop_GetImagery);
			PropertySet_BindProperty("Imagery_MR", OpenGUI::PT_STRING, &ScalingImage::_prop_SetImagery, &ScalingImage::_prop_GetImagery);

			PropertySet_BindProperty("Imagery_LL", OpenGUI::PT_STRING, &ScalingImage::_prop_SetImagery, &ScalingImage::_prop_GetImagery);
			PropertySet_BindProperty("Imagery_LM", OpenGUI::PT_STRING, &ScalingImage::_prop_SetImagery, &ScalingImage::_prop_GetImagery);
			PropertySet_BindProperty("Imagery_LR", OpenGUI::PT_STRING, &ScalingImage::_prop_SetImagery, &ScalingImage::_prop_GetImagery);
		}
		//#####################################################################
		ScalingImage::~ScalingImage()
		{
			//
		}
		//#####################################################################
		Render::RenderOperationList ScalingImage::buildWidgetRenderOpList()
		{
			Render::RenderOperationList outList; //something to draw to

			//first we need to know native pixel size of the display at our location
			FVector2 nativePixelSize;
			nativePixelSize = getNativePixelSize_Local();

			//we need to know the minimum sizes to display
			//to determine that we'll test each side and use the largest value found
			int minSizeLeft=0;
			int minSizeRight=0;
			int minSizeUpper=0;
			int minSizeLower=0;
			// get left
			if(!mImageryPtr_UL.isNull())
				if(mImageryPtr_UL->getImagesetRect().getWidth() > minSizeLeft)
					minSizeLeft = mImageryPtr_UL->getImagesetRect().getWidth();
			if(!mImageryPtr_ML.isNull())
				if(mImageryPtr_ML->getImagesetRect().getWidth() > minSizeLeft)
					minSizeLeft = mImageryPtr_ML->getImagesetRect().getWidth();
			if(!mImageryPtr_LL.isNull())
				if(mImageryPtr_LL->getImagesetRect().getWidth() > minSizeLeft)
					minSizeLeft = mImageryPtr_LL->getImagesetRect().getWidth();
			//get right
			if(!mImageryPtr_UR.isNull())
				if(mImageryPtr_UR->getImagesetRect().getWidth() > minSizeRight)
					minSizeRight = mImageryPtr_UR->getImagesetRect().getWidth();
			if(!mImageryPtr_MR.isNull())
				if(mImageryPtr_MR->getImagesetRect().getWidth() > minSizeRight)
					minSizeRight = mImageryPtr_MR->getImagesetRect().getWidth();
			if(!mImageryPtr_LR.isNull())
				if(mImageryPtr_LR->getImagesetRect().getWidth() > minSizeRight)
					minSizeRight = mImageryPtr_LR->getImagesetRect().getWidth();
			//get top
			if(!mImageryPtr_UL.isNull())
				if(mImageryPtr_UL->getImagesetRect().getHeight() > minSizeUpper)
					minSizeUpper = mImageryPtr_UL->getImagesetRect().getWidth();
			if(!mImageryPtr_UM.isNull())
				if(mImageryPtr_UM->getImagesetRect().getHeight() > minSizeUpper)
					minSizeUpper = mImageryPtr_UM->getImagesetRect().getWidth();
			if(!mImageryPtr_UR.isNull())
				if(mImageryPtr_UR->getImagesetRect().getHeight() > minSizeUpper)
					minSizeUpper = mImageryPtr_UR->getImagesetRect().getWidth();
			//get bottom
			if(!mImageryPtr_LL.isNull())
				if(mImageryPtr_LL->getImagesetRect().getHeight() > minSizeLower)
					minSizeLower = mImageryPtr_LL->getImagesetRect().getWidth();
			if(!mImageryPtr_LM.isNull())
				if(mImageryPtr_LM->getImagesetRect().getHeight() > minSizeLower)
					minSizeLower = mImageryPtr_LM->getImagesetRect().getWidth();
			if(!mImageryPtr_LR.isNull())
				if(mImageryPtr_LR->getImagesetRect().getHeight() > minSizeLower)
					minSizeLower = mImageryPtr_LR->getImagesetRect().getWidth();
			//and we don't care about middle


			//these will hold our final output sizes
			float leftWidth,rightWidth,upperHeight,lowerHeight, middleHeight, middleWidth;
			leftWidth = nativePixelSize.x * minSizeLeft;
			rightWidth = nativePixelSize.x * minSizeRight;
			upperHeight = nativePixelSize.y * minSizeUpper;
			lowerHeight = nativePixelSize.y * minSizeLower;
			middleHeight = getRect().getHeight() - (upperHeight + lowerHeight);
			middleWidth = getRect().getWidth() - (leftWidth + rightWidth);

			//now we just need to draw everything out
			Render::PrimitiveBox box; //box primitive, because we're lazy, and primitives are fun
			FRect boxSize; //we'll use this a lot ;)

			//we'll do corners first, since they are easy and draw order really doesn't matter for us since nothing overlaps
			if(mImageryPtr_UL){//upper left
				boxSize.setPosition(getRect().getPosition());
				boxSize.setHeight(upperHeight);
				boxSize.setWidth(leftWidth);
				box.setRect(boxSize);
				box.setTextureImagery(mImageryPtr_UL);
				Render::AppendRenderOperationList(outList, box.getRenderOperationList());
			}
			if(mImageryPtr_UR){ //upper right
				boxSize.setPosition(getRect().getPosition());
				boxSize.offset( FVector2( getRect().getWidth() - rightWidth, 0) );
				boxSize.setHeight(upperHeight);
				boxSize.setWidth(rightWidth);
				box.setRect(boxSize);
				box.setTextureImagery(mImageryPtr_UR);
				Render::AppendRenderOperationList(outList, box.getRenderOperationList());
			}
			if(mImageryPtr_LL){ //lower left
				boxSize.setPosition(getRect().getPosition());
				boxSize.offset( FVector2( 0, getRect().getHeight() - lowerHeight) );
				boxSize.setHeight(lowerHeight);
				boxSize.setWidth(leftWidth);
				box.setRect(boxSize);
				box.setTextureImagery(mImageryPtr_LL);
				Render::AppendRenderOperationList(outList, box.getRenderOperationList());
			}
			if(mImageryPtr_LR){ //lower right
				boxSize.setPosition(getRect().getPosition());
				boxSize.offset( FVector2( getRect().getWidth() - rightWidth, getRect().getHeight() - lowerHeight) );
				boxSize.setHeight(lowerHeight);
				boxSize.setWidth(rightWidth);
				box.setRect(boxSize);
				box.setTextureImagery(mImageryPtr_LR);
				Render::AppendRenderOperationList(outList, box.getRenderOperationList());
			}

			//now we'll do the sides
			if(middleHeight > 0.0f && mImageryPtr_ML){ //left side
				boxSize.setPosition(getRect().getPosition());
				boxSize.offset( FVector2( 0, upperHeight) );
				boxSize.setHeight(middleHeight);
				boxSize.setWidth(leftWidth);
				box.setRect(boxSize);
				box.setTextureImagery(mImageryPtr_ML);
				Render::AppendRenderOperationList(outList, box.getRenderOperationList());
			}
			if(middleHeight > 0.0f && mImageryPtr_MR){ //right side
				boxSize.setPosition(getRect().getPosition());
				boxSize.offset( FVector2( getRect().getWidth() - rightWidth, upperHeight) );
				boxSize.setHeight(middleHeight);
				boxSize.setWidth(rightWidth);
				box.setRect(boxSize);
				box.setTextureImagery(mImageryPtr_MR);
				Render::AppendRenderOperationList(outList, box.getRenderOperationList());
			}
			if(middleWidth > 0.0f && mImageryPtr_UM){ //upper side
				boxSize.setPosition(getRect().getPosition());
				boxSize.offset( FVector2( leftWidth, 0) );
				boxSize.setHeight(upperHeight);
				boxSize.setWidth(middleWidth);
				box.setRect(boxSize);
				box.setTextureImagery(mImageryPtr_UM);
				Render::AppendRenderOperationList(outList, box.getRenderOperationList());
			}
			if(middleWidth > 0.0f && mImageryPtr_LM){ //lower side
				boxSize.setPosition(getRect().getPosition());
				boxSize.offset( FVector2( leftWidth, getRect().getHeight() - lowerHeight) );
				boxSize.setHeight(lowerHeight);
				boxSize.setWidth(middleWidth);
				box.setRect(boxSize);
				box.setTextureImagery(mImageryPtr_LM);
				Render::AppendRenderOperationList(outList, box.getRenderOperationList());
			}

			//and finally we'll do the middle, but only if there's something to actually draw
			if(middleWidth > 0.0f && middleHeight > 0.0f && mImageryPtr_MM){
				boxSize.setPosition(getRect().getPosition());
				boxSize.offset( FVector2( leftWidth, upperHeight) );
				boxSize.setHeight(middleHeight);
				boxSize.setWidth(middleWidth);
				box.setRect(boxSize);
				box.setTextureImagery(mImageryPtr_MM);
				Render::AppendRenderOperationList(outList, box.getRenderOperationList());
			}

			//and we're done. seems like a lot of code, but when you consider that we're drawing 9 areas, it isn't that bad
			// (plus it's cached, so this won't get called very often!)
			return outList;
		}
		//#####################################################################
		bool ScalingImage::_prop_SetImagery(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			/*	This is a good example of combining several similar property
				operations into a single callback.

				Some people might say that this method isn't optimal, as these
				string comparisons are performed multiple times.
				
				Keep in mind that property changes for Imagery settings don't
				occur very often, and are often in areas of code that are not
				time critical. So it is in our best interest to write this
				code in a manner that is easy to manage, rather than trying
				to make it extremely fast. If quickly changing this property
				was truly a concern of an application, they could easily
				subclass ScalingImage and overload the property handlers to
				run their own code instead of this, while leaving the rest
				of the class untouched.
			*/
			ScalingImage* w = static_cast<ScalingImage*>(widget);
			assert(w);
			if(propertyName == "imagery_ul")
				w->setImagery_UL(newValueStr);
			else if(propertyName == "imagery_um")
				w->setImagery_UM(newValueStr);
			else if(propertyName == "imagery_ur")
				w->setImagery_UR(newValueStr);
			else if(propertyName == "imagery_ml")
				w->setImagery_ML(newValueStr);
			else if(propertyName == "imagery_mm")
				w->setImagery_MM(newValueStr);
			else if(propertyName == "imagery_mr")
				w->setImagery_MR(newValueStr);
			else if(propertyName == "imagery_ll")
				w->setImagery_LL(newValueStr);
			else if(propertyName == "imagery_lm")
				w->setImagery_LM(newValueStr);
			else if(propertyName == "imagery_lr")
				w->setImagery_LR(newValueStr);
			else
				return false;
			return true;
		}
		//#####################################################################
		bool ScalingImage::_prop_GetImagery(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			ScalingImage* w = static_cast<ScalingImage*>(widget);
			assert(w);
			if(propertyName == "imagery_ul")
				curValue = w->mImageryPtr_UL ? w->mImageryPtr_UL->getName() : "";
			else if(propertyName == "imagery_um")
				curValue = w->mImageryPtr_UM ? w->mImageryPtr_UL->getName() : "";
			else if(propertyName == "imagery_ur")
				curValue = w->mImageryPtr_UR ? w->mImageryPtr_UL->getName() : "";
			else if(propertyName == "imagery_ml")
				curValue = w->mImageryPtr_ML ? w->mImageryPtr_UL->getName() : "";
			else if(propertyName == "imagery_mm")
				curValue = w->mImageryPtr_MM ? w->mImageryPtr_UL->getName() : "";
			else if(propertyName == "imagery_mr")
				curValue = w->mImageryPtr_MR ? w->mImageryPtr_UL->getName() : "";
			else if(propertyName == "imagery_ll")
				curValue = w->mImageryPtr_LL ? w->mImageryPtr_UL->getName() : "";
			else if(propertyName == "imagery_lm")
				curValue = w->mImageryPtr_LM ? w->mImageryPtr_UL->getName() : "";
			else if(propertyName == "imagery_lr")
				curValue = w->mImageryPtr_LR ? w->mImageryPtr_UL->getName() : "";
			else
				return false;
			return true;
		}
		//#####################################################################
		void ScalingImage::setImagery_UL(std::string imageryName)
		{
			dirtyCache();
			mImageryPtr_UL = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void ScalingImage::setImagery_UM(std::string imageryName)
		{
			dirtyCache();
			mImageryPtr_UM = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void ScalingImage::setImagery_UR(std::string imageryName)
		{
			dirtyCache();
			mImageryPtr_UR = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void ScalingImage::setImagery_ML(std::string imageryName)
		{
			dirtyCache();
			mImageryPtr_ML = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void ScalingImage::setImagery_MM(std::string imageryName)
		{
			dirtyCache();
			mImageryPtr_MM = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void ScalingImage::setImagery_MR(std::string imageryName)
		{
			dirtyCache();
			mImageryPtr_MR = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void ScalingImage::setImagery_LL(std::string imageryName)
		{
			dirtyCache();
			mImageryPtr_LL = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void ScalingImage::setImagery_LM(std::string imageryName)
		{
			dirtyCache();
			mImageryPtr_LM = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void ScalingImage::setImagery_LR(std::string imageryName)
		{
			dirtyCache();
			mImageryPtr_LR = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
	}//namespace Widgets{
}//namespace OpenGUI{
