
#define OPENGUI_WIDGET_EXPORTS
#include "Tachometer.h"

namespace OpenGUI{
	namespace Widgets{
		//############################################################################
		Tachometer::Tachometer()
		{
			float mCurrentValue = 0.0f;
			float mMinValue = 0.0f;
			float mMinValueAngle = 0.0f;
			float mMaxValue = 0.0f;
			float mMaxValueAngle = 0.0f;

			PropertySet_BindProperty("BGImagery", OpenGUI::PT_STRING, &Tachometer::_prop_SetBGImagery, &Tachometer::_prop_GetBGImagery );
			PropertySet_BindProperty("NeedleImagery", OpenGUI::PT_STRING, &Tachometer::_prop_SetNeedleImagery, &Tachometer::_prop_GetNeedleImagery );
			PropertySet_BindProperty("NeedlePivot", OpenGUI::PT_FVECTOR2, &Tachometer::_prop_SetNeedlePivot, &Tachometer::_prop_GetNeedlePivot );
			PropertySet_BindProperty("NeedleAnchor", OpenGUI::PT_FVECTOR2, &Tachometer::_prop_SetNeedleAnchor, &Tachometer::_prop_GetNeedleAnchor );

			PropertySet_BindProperty("NeedleMinValue", OpenGUI::PT_FLOAT, &Tachometer::_prop_SetNeedleMinValue, &Tachometer::_prop_GetNeedleMinValue );
			PropertySet_BindProperty("NeedleMaxValue", OpenGUI::PT_FLOAT, &Tachometer::_prop_SetNeedleMaxValue, &Tachometer::_prop_GetNeedleMaxValue );
			PropertySet_BindProperty("NeedleMinAngle", OpenGUI::PT_FLOAT, &Tachometer::_prop_SetNeedleMinAngle, &Tachometer::_prop_GetNeedleMinAngle );
			PropertySet_BindProperty("NeedleMaxAngle", OpenGUI::PT_FLOAT, &Tachometer::_prop_SetNeedleMaxAngle, &Tachometer::_prop_GetNeedleMaxAngle );

			PropertySet_BindProperty("NeedleValue", OpenGUI::PT_FLOAT, &Tachometer::_prop_SetNeedleValue, &Tachometer::_prop_GetNeedleValue );
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
		bool Tachometer::defaultMessageHandler(const Msg::Message &message)
		{
			return true;
		}
		//############################################################################
		void Tachometer::setBackgroundImagery(std::string imageryName)
		{
			dirtyCache();
			mBGImageryPtr = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//############################################################################
		void Tachometer::setNeedlePivot(const FVector2& pivotLocation)
		{
			dirtyCache();
			mNeedlePivot = pivotLocation;
		}
		//############################################################################
		void Tachometer::setNeedleImagery(std::string imageryName)
		{
			dirtyCache();
			mNeedleImageryPtr = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//############################################################################
		void Tachometer::setNeedleAnchor(const FVector2& anchorLocation)
		{
			dirtyCache();
			mNeedleAnchor = anchorLocation;
		}
		//############################################################################
		void Tachometer::setNeedleScale(float minValue, float minValueAngle, float maxValue, float maxValueAngle)
		{
			dirtyCache();
			mMinValue = minValue;
			mMinValueAngle = minValueAngle;
			mMaxValue = maxValue;
			mMaxValueAngle = maxValueAngle;
		}
		//############################################################################
		void Tachometer::setNeedleValue(float currentValue)
		{
			dirtyCache();
			mCurrentValue = currentValue;
		}
		//############################################################################




		//############################################################################
		bool Tachometer::_prop_SetBGImagery(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			Tachometer* w = static_cast<Tachometer*>(widget);
			w->setBackgroundImagery(newValueStr);
			return true;
		}
		//############################################################################
		bool Tachometer::_prop_GetBGImagery(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			Tachometer* w = static_cast<Tachometer*>(widget);
			curValue = w->mBGImageryPtr ? w->mBGImageryPtr->getName() : "";
			return true;
		}
		//############################################################################
		bool Tachometer::_prop_SetNeedleImagery(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			Tachometer* w = static_cast<Tachometer*>(widget);
			w->setNeedleImagery(newValueStr);
			return true;
		}
		//############################################################################
		bool Tachometer::_prop_GetNeedleImagery(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			Tachometer* w = static_cast<Tachometer*>(widget);
			curValue = w->mNeedleImageryPtr ? w->mNeedleImageryPtr->getName() : "";
			return true;
		}
		//############################################################################

		bool Tachometer::_prop_SetNeedleAnchor(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			if(!newValuePtr) return false;
			FVector2* newValue = (FVector2*)newValuePtr;
			Tachometer* w = static_cast<Tachometer*>(widget);
			w->setNeedleAnchor(*newValue);
			return true;
		}
		//############################################################################
		bool Tachometer::_prop_GetNeedleAnchor(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			Tachometer* w = static_cast<Tachometer*>(widget);
			PropertyParser::toStrFVector2(w->mNeedleAnchor, curValue);
			return true;
		}
		//############################################################################
		bool Tachometer::_prop_SetNeedlePivot(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			if(!newValuePtr) return false;
			FVector2* newValue = (FVector2*)newValuePtr;
			Tachometer* w = static_cast<Tachometer*>(widget);
			w->setNeedlePivot(*newValue);
			return true;
		}
		//############################################################################
		bool Tachometer::_prop_GetNeedlePivot(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			Tachometer* w = static_cast<Tachometer*>(widget);
			PropertyParser::toStrFVector2(w->mNeedlePivot, curValue);
			return true;
		}
		//############################################################################
		bool Tachometer::_prop_SetNeedleValue(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			if(!newValuePtr) return false;
			float* newValue = (float*)newValuePtr;
			Tachometer* w = static_cast<Tachometer*>(widget);
			w->setNeedleValue(*newValue);
			return true;
		}
		//############################################################################
		bool Tachometer::_prop_GetNeedleValue(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			Tachometer* w = static_cast<Tachometer*>(widget);
			PropertyParser::toStrFloat(w->mCurrentValue, curValue);
			return true;
		}
		//############################################################################
		bool Tachometer::_prop_SetNeedleMinValue(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			if(!newValuePtr) return false;
			float* newValue = (float*)newValuePtr;
			Tachometer* w = static_cast<Tachometer*>(widget);
			w->setNeedleScale(*newValue, w->mMinValueAngle, w->mMaxValue, w->mMaxValueAngle);
			return true;
		}
		//############################################################################
		bool Tachometer::_prop_GetNeedleMinValue(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			Tachometer* w = static_cast<Tachometer*>(widget);
			PropertyParser::toStrFloat(w->mMinValue, curValue);
			return true;
		}
		//############################################################################
		bool Tachometer::_prop_SetNeedleMaxValue(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			if(!newValuePtr) return false;
			float* newValue = (float*)newValuePtr;
			Tachometer* w = static_cast<Tachometer*>(widget);
			w->setNeedleScale(w->mMinValue, w->mMinValueAngle, *newValue, w->mMaxValueAngle);
			return true;
		}
		//############################################################################
		bool Tachometer::_prop_GetNeedleMaxValue(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			Tachometer* w = static_cast<Tachometer*>(widget);
			PropertyParser::toStrFloat(w->mMaxValue, curValue);
			return true;
		}
		//############################################################################
		bool Tachometer::_prop_SetNeedleMinAngle(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			if(!newValuePtr) return false;
			float* newValue = (float*)newValuePtr;
			Tachometer* w = static_cast<Tachometer*>(widget);
			w->setNeedleScale(w->mMinValue, *newValue, w->mMaxValue, w->mMaxValueAngle);
			return true;
		}
		//############################################################################
		bool Tachometer::_prop_GetNeedleMinAngle(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			Tachometer* w = static_cast<Tachometer*>(widget);
			PropertyParser::toStrFloat(w->mMinValueAngle, curValue);
			return true;
		}
		//############################################################################
		bool Tachometer::_prop_SetNeedleMaxAngle(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			if(!newValuePtr) return false;
			float* newValue = (float*)newValuePtr;
			Tachometer* w = static_cast<Tachometer*>(widget);
			w->setNeedleScale(w->mMinValue, w->mMinValueAngle, w->mMaxValue, *newValue);
			return true;
		}
		//############################################################################
		bool Tachometer::_prop_GetNeedleMaxAngle(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			Tachometer* w = static_cast<Tachometer*>(widget);
			PropertyParser::toStrFloat(w->mMaxValueAngle, curValue);
			return true;
		}
		//############################################################################

	};//namespace Widgets{
};//namespace OpenGUI{