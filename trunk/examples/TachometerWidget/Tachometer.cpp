
#define OPENGUI_WIDGET_EXPORTS
#include "Tachometer.h"

namespace OpenGUI{
	//############################################################################
	Tachometer::Tachometer()
	{
		float mCurrentValue = 0.0f;
		float mMinValue = 0.0f;
		float mMinValueAngle = 0.0f;
		float mMaxValue = 0.0f;
		float mMaxValueAngle = 0.0f;

		//BGImagery
		//NeedleImagery
// 		NeedlePivot
// 		NeedleAnchor
// 
// 		NeedleMinValue
// 		NeedleMaxValue
// 		NeedleMinAngle
// 		NeedleMaxAngle
// 
// 		NeedleValue
	}
	//############################################################################
	Tachometer::~Tachometer()
	{
		//
	}
	//############################################################################
	Widget* Tachometer::createTachometerFactory()
	{
		return new Tachometer;
	}
	//############################################################################
	void Tachometer::onDraw(Object* sender, Draw_EventArgs& evtArgs){
		/**/
		float scale; // scale is the multiplier we apply to the imagery
		Brush& b = evtArgs.brush;
		b.Image.drawImage(mBGImageryPtr, getRect() );

		//calculate necessary rotation to represent current needle value
		float anglePerUnit;
		anglePerUnit = (mMaxValueAngle - mMinValueAngle) / (mMaxValue - mMinValue);
		float desiredAngle = (mCurrentValue * anglePerUnit) - mMinValueAngle;

		FVector2 anchorPos;
		FVector2 needleOffset;

		b.pushPosition(anchorPos);
		b.pushRotation(Degree(desiredAngle));
		b.pushPosition(needleOffset);
		// draw needle
		b.pop(); //b.pushPosition(needleOffset);
		b.pop(); //b.pushRotation(Degree(desiredAngle));
		b.pop(); //b.pushPosition(anchorPos);
	}
	/*
	Render::RenderOperationList Tachometer::buildWidgetRenderOpList()
	{
		if(!mBGImageryPtr || !mNeedleImageryPtr)
			return Render::RenderOperationList();

		Render::RenderOperationList outList;

		//render background image
		Render::PrimitiveBox box;
		box.setRect(this->getRect());
		box.setTextureImagery(mBGImageryPtr);
		Render::AppendRenderOperationList(outList, box.getRenderOperationList());


		//render needle to a temp buffer
		Render::RenderOperationList tmpList;
		FRect needleRect;
		needleRect.setWidth(
			(float)mNeedleImageryPtr->getImagesetRect().getWidth() / (float)mBGImageryPtr->getImagesetRect().getWidth()
			);
		needleRect.setHeight(
			(float)mNeedleImageryPtr->getImagesetRect().getHeight() / (float)mBGImageryPtr->getImagesetRect().getHeight()
			);
		FVector2 anchorOffset =	needleRect.getOuterCoord(mNeedleAnchor);
		needleRect.offset( -anchorOffset );
		needleRect.offset( mNeedlePivot );
		box.setRect(needleRect);
		box.setTextureImagery(mNeedleImageryPtr);
		tmpList = box.getRenderOperationList();

		//calculate necessary rotation to represent current needle value
		float anglePerUnit;
		anglePerUnit = (mMaxValueAngle - mMinValueAngle) / (mMaxValue - mMinValue);
		float desiredAngle = (mCurrentValue * anglePerUnit) - mMinValueAngle;

		//apply rotation to temp needle buffer
		Render::PrimitiveRotation rot;
		rot.addRenderOperation(tmpList);
		rot.setOrigin( mNeedlePivot );
		rot.setAngleDegrees( desiredAngle );
		tmpList = rot.getRenderOperationList();
		
		//transform needle render operations from the imaginary coord system to the necessary output coords
		Render::RenderOperationList::iterator iter = tmpList.begin();
		while(iter != tmpList.end()){
			iter->vertices[0].position = convCoordInnerToLocal(iter->vertices[0].position);
			iter->vertices[1].position = convCoordInnerToLocal(iter->vertices[1].position);
			iter->vertices[2].position = convCoordInnerToLocal(iter->vertices[2].position);
			iter++;
		}

		//write temp needle buffer to the output buffer
		Render::AppendRenderOperationList(outList, tmpList);

		return outList;
	}
	//############################################################################
	*/
	
	//############################################################################
	void Tachometer::setBackgroundImagery(std::string imageryName)
	{
		invalidate();
		mBGImageryPtr = ImageryManager::getSingleton().getImagery(imageryName);
	}
	//############################################################################
	void Tachometer::setNeedlePivot(const FVector2& pivotLocation)
	{
		invalidate();
		mNeedlePivot = pivotLocation;
	}
	//############################################################################
	void Tachometer::setNeedleImagery(std::string imageryName)
	{
		invalidate();
		mNeedleImageryPtr = ImageryManager::getSingleton().getImagery(imageryName);
	}
	//############################################################################
	void Tachometer::setNeedleAnchor(const FVector2& anchorLocation)
	{
		invalidate();
		mNeedleAnchor = anchorLocation;
	}
	//############################################################################
	void Tachometer::setNeedleScale(float minValue, float minValueAngle, float maxValue, float maxValueAngle)
	{
		invalidate();
		mMinValue = minValue;
		mMinValueAngle = minValueAngle;
		mMaxValue = maxValue;
		mMaxValueAngle = maxValueAngle;
	}
	//############################################################################
	void Tachometer::setNeedleValue(float currentValue)
	{
		invalidate();
		mCurrentValue = currentValue;
	}
	//############################################################################
};//namespace OpenGUI{