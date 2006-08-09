#include "OpenGUI.h"
#include "OpenGUI_FrameButton.h"


namespace OpenGUI{
	namespace Widgets{
		//#####################################################################
		FrameButton::FrameButton()
		{
			m_MouseOver=false;
			m_ButtonDown=false;

			PropertySet_BindProperty("Text", OpenGUI::PT_STRING, &FrameButton::_prop_SetText, &FrameButton::_prop_GetText);
			PropertySet_BindProperty("Font", OpenGUI::PT_STRING, &FrameButton::_prop_SetFont, &FrameButton::_prop_GetFont);
			PropertySet_BindProperty("FontSize", OpenGUI::PT_INTEGER, &FrameButton::_prop_SetFontSize, &FrameButton::_prop_GetFontSize);
			PropertySet_BindProperty("Alignment_H", OpenGUI::PT_ENUM, &m_hAlignEnum, &FrameButton::_prop_SetHAlign, &FrameButton::_prop_GetHAlign);
			PropertySet_BindProperty("Alignment_V", OpenGUI::PT_ENUM, &m_vAlignEnum, &FrameButton::_prop_SetVAlign, &FrameButton::_prop_GetVAlign);
			PropertySet_BindProperty("AutoWrap", OpenGUI::PT_BOOL, &FrameButton::_prop_SetWrap, &FrameButton::_prop_GetWrap);

			//Normal Imagery
			PropertySet_BindProperty("ImageryNormal_UL", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryNormal_UM", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryNormal_UR", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryNormal_ML", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryNormal_MM", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryNormal_MR", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryNormal_LL", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryNormal_LM", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryNormal_LR", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			//Over Imagery
			PropertySet_BindProperty("ImageryOver_UL", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryOver_UM", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryOver_UR", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryOver_ML", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryOver_MM", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryOver_MR", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryOver_LL", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryOver_LM", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryOver_LR", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			//Press Imagery
			PropertySet_BindProperty("ImageryPress_UL", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryPress_UM", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryPress_UR", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryPress_ML", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryPress_MM", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryPress_MR", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryPress_LL", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryPress_LM", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryPress_LR", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			//Disabled Imagery
			PropertySet_BindProperty("ImageryDisabled_UL", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryDisabled_UM", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryDisabled_UR", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryDisabled_ML", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryDisabled_MM", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryDisabled_MR", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryDisabled_LL", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryDisabled_LM", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
			PropertySet_BindProperty("ImageryDisabled_LR", OpenGUI::PT_STRING, &FrameButton::_prop_SetImagery, &FrameButton::_prop_GetImagery);
		}
		//#####################################################################
		FrameButton::~FrameButton()
		{
			//
		}
		//#####################################################################
		Widget* FrameButton::createFrameButtonFactory()
		{
			return new FrameButton;
		}
		//#####################################################################
		bool FrameButton::defaultMessageHandler(const Msg::Message &message)
		{
			if(message.messageType==message.MT_EVENT){

				if(message.event.destination!=this)
					return true;

				//handle mouse just entered
				if (message.event.type==message.event.ME_MouseEnter)
				{
					if(System::getSingleton().setTrackMouseLeave(this)){
						dirtyCache();
						m_MouseOver=true;
					}
					return true;
				}

				if (message.event.type==message.event.ME_MouseClick){
					return true;
				}
				if (message.event.type==message.event.ME_MouseDblClick){
					return true;
				}

				if (message.event.type==message.event.ME_MouseLeave)
				{
					dirtyCache();
					m_MouseOver=false;
				}

				if (message.event.type==message.event.ME_MouseButtonDown)
				{
					dirtyCache();
					System::getSingleton().setCaptureMouse(this);
					m_ButtonDown = true;
				}
				if (message.event.type==message.event.ME_MouseButtonUp)
				{
					dirtyCache();
					System::getSingleton().setCaptureMouse(0);
					m_ButtonDown = false;
					if(this != System::getSingleton().getElementAt(System::getSingleton().getCursorPos())){
						m_MouseOver=false; //fix the mouse over value if needed
					}else{
						//hey, we just got pressed!
					}
				}

				if (message.event.type==message.event.ME_MouseMove && m_MouseOver==false)
				{
					FVector2 mpos = ((Msg::EventData::MouseMoveEvent*)message.event.eventData)->mousePosition;
					mpos = convCoordWorldToLocal(mpos);
					if(pointIsInside(mpos)){
						if(System::getSingleton().setTrackMouseLeave(this)){
							dirtyCache();
							m_MouseOver=true;
						}
					}
				}
			}
			return true;
		}
		//#####################################################################
		Render::RenderOperationList FrameButton::buildWidgetRenderOpList()
		{
			Render::RenderOperationList outList; //something to draw to

			enum{ //we'll use this to select imagery to use
				IS_NORMAL,
				IS_OVER,
				IS_PRESS,
				IS_DISABLED
			}SelectedImagerySet;

		// DETERMINE IMAGE STATE TO DRAW
			SelectedImagerySet = IS_NORMAL; //this is the default
			if(isDisabled()){
				SelectedImagerySet = IS_DISABLED;
			}else{
				if(m_MouseOver){
					if(m_ButtonDown){
						SelectedImagerySet = IS_PRESS;
					}else{
						SelectedImagerySet = IS_OVER;
					}
				}else{
					SelectedImagerySet = IS_NORMAL;
				}
			}
			
			//since the 9 zone imagery system is a little complex, we're going to
			//simplify it's usage by using generic ImageryPtrs that we'll just fill in
			//with an existing stored ImageryPtr depending on our immediate needs
			ImageryPtr mImageryPtr_UL;
			ImageryPtr mImageryPtr_UM;
			ImageryPtr mImageryPtr_UR;
			ImageryPtr mImageryPtr_ML;
			ImageryPtr mImageryPtr_MM;
			ImageryPtr mImageryPtr_MR;
			ImageryPtr mImageryPtr_LL;
			ImageryPtr mImageryPtr_LM;
			ImageryPtr mImageryPtr_LR;
			
			//first we'll set up the default that can be used if no imagery is entered for a zone (which is IS_NORMAL)
			mImageryPtr_UL = mImageryNormalPtr_UL;
			mImageryPtr_UM = mImageryNormalPtr_UM;
			mImageryPtr_UR = mImageryNormalPtr_UR;
			mImageryPtr_ML = mImageryNormalPtr_ML;
			mImageryPtr_MM = mImageryNormalPtr_MM;
			mImageryPtr_MR = mImageryNormalPtr_MR;
			mImageryPtr_LL = mImageryNormalPtr_LL;
			mImageryPtr_LM = mImageryNormalPtr_LM;
			mImageryPtr_LR = mImageryNormalPtr_LR;
			if( SelectedImagerySet == IS_DISABLED ){
				if(mImageryDisabledPtr_UL) mImageryPtr_UL = mImageryDisabledPtr_UL;
				if(mImageryDisabledPtr_UM) mImageryPtr_UM = mImageryDisabledPtr_UM;
				if(mImageryDisabledPtr_UR) mImageryPtr_UR = mImageryDisabledPtr_UR;
				if(mImageryDisabledPtr_ML) mImageryPtr_ML = mImageryDisabledPtr_ML;
				if(mImageryDisabledPtr_MM) mImageryPtr_MM = mImageryDisabledPtr_MM;
				if(mImageryDisabledPtr_MR) mImageryPtr_MR = mImageryDisabledPtr_MR;
				if(mImageryDisabledPtr_LL) mImageryPtr_LL = mImageryDisabledPtr_LL;
				if(mImageryDisabledPtr_LM) mImageryPtr_LM = mImageryDisabledPtr_LM;
				if(mImageryDisabledPtr_LR) mImageryPtr_LR = mImageryDisabledPtr_LR;
			}
			if( SelectedImagerySet == IS_OVER ){
				// only use an imagery if it is valid
				if(mImageryOverPtr_UL) mImageryPtr_UL = mImageryOverPtr_UL;
				if(mImageryOverPtr_UM) mImageryPtr_UM = mImageryOverPtr_UM;
				if(mImageryOverPtr_UR) mImageryPtr_UR = mImageryOverPtr_UR;
				if(mImageryOverPtr_ML) mImageryPtr_ML = mImageryOverPtr_ML;
				if(mImageryOverPtr_MM) mImageryPtr_MM = mImageryOverPtr_MM;
				if(mImageryOverPtr_MR) mImageryPtr_MR = mImageryOverPtr_MR;
				if(mImageryOverPtr_LL) mImageryPtr_LL = mImageryOverPtr_LL;
				if(mImageryOverPtr_LM) mImageryPtr_LM = mImageryOverPtr_LM;
				if(mImageryOverPtr_LR) mImageryPtr_LR = mImageryOverPtr_LR;
			}
			if( SelectedImagerySet == IS_PRESS ){
				// only use an imagery if it is valid
				if(mImageryPressPtr_UL) mImageryPtr_UL = mImageryPressPtr_UL;
				if(mImageryPressPtr_UM) mImageryPtr_UM = mImageryPressPtr_UM;
				if(mImageryPressPtr_UR) mImageryPtr_UR = mImageryPressPtr_UR;
				if(mImageryPressPtr_ML) mImageryPtr_ML = mImageryPressPtr_ML;
				if(mImageryPressPtr_MM) mImageryPtr_MM = mImageryPressPtr_MM;
				if(mImageryPressPtr_MR) mImageryPtr_MR = mImageryPressPtr_MR;
				if(mImageryPressPtr_LL) mImageryPtr_LL = mImageryPressPtr_LL;
				if(mImageryPressPtr_LM) mImageryPtr_LM = mImageryPressPtr_LM;
				if(mImageryPressPtr_LR) mImageryPtr_LR = mImageryPressPtr_LR;
			}


			

		// BACKGROUND IMAGERY DRAWING

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


		// FOREGROUND TEXT DRAWING
			if(mText == "") //take the quick way out if there is nothing to do
				return outList;

			Render::PrimitiveTextBox text;
			text.setRect(getRect());
			text.setContext(this);
			text.setFont(mFontName,mFontSize);
			text.setText(mText);
			text.setAutoWrap(mAutoWrap);
			text.setAlignment_Vert(mAlignVert);
			text.setAlignment_Horiz(mAlignHoriz);

			Render::AppendRenderOperationList(outList, text.getRenderOperationList());

			return outList;
		}
		//#####################################################################
		bool FrameButton::_prop_SetImagery(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			FrameButton* w = static_cast<FrameButton*>(widget);
			assert(w);
			// Normal Imagery
			if(propertyName == "imagerynormal_ul")
				w->setImageryNormal_UL(newValueStr);
			else if(propertyName == "imagerynormal_um")
				w->setImageryNormal_UM(newValueStr);
			else if(propertyName == "imagerynormal_ur")
				w->setImageryNormal_UR(newValueStr);
			else if(propertyName == "imagerynormal_ml")
				w->setImageryNormal_ML(newValueStr);
			else if(propertyName == "imagerynormal_mm")
				w->setImageryNormal_MM(newValueStr);
			else if(propertyName == "imagerynormal_mr")
				w->setImageryNormal_MR(newValueStr);
			else if(propertyName == "imagerynormal_ll")
				w->setImageryNormal_LL(newValueStr);
			else if(propertyName == "imagerynormal_lm")
				w->setImageryNormal_LM(newValueStr);
			else if(propertyName == "imagerynormal_lr")
				w->setImageryNormal_LR(newValueStr);
			// Over Imagery
			else if(propertyName == "imageryover_ul")
				w->setImageryOver_UL(newValueStr);
			else if(propertyName == "imageryover_um")
				w->setImageryOver_UM(newValueStr);
			else if(propertyName == "imageryover_ur")
				w->setImageryOver_UR(newValueStr);
			else if(propertyName == "imageryover_ml")
				w->setImageryOver_ML(newValueStr);
			else if(propertyName == "imageryover_mm")
				w->setImageryOver_MM(newValueStr);
			else if(propertyName == "imageryover_mr")
				w->setImageryOver_MR(newValueStr);
			else if(propertyName == "imageryover_ll")
				w->setImageryOver_LL(newValueStr);
			else if(propertyName == "imageryover_lm")
				w->setImageryOver_LM(newValueStr);
			else if(propertyName == "imageryover_lr")
				w->setImageryOver_LR(newValueStr);
			// Press Imagery
			else if(propertyName == "imagerypress_ul")
				w->setImageryPress_UL(newValueStr);
			else if(propertyName == "imagerypress_um")
				w->setImageryPress_UM(newValueStr);
			else if(propertyName == "imagerypress_ur")
				w->setImageryPress_UR(newValueStr);
			else if(propertyName == "imagerypress_ml")
				w->setImageryPress_ML(newValueStr);
			else if(propertyName == "imagerypress_mm")
				w->setImageryPress_MM(newValueStr);
			else if(propertyName == "imagerypress_mr")
				w->setImageryPress_MR(newValueStr);
			else if(propertyName == "imagerypress_ll")
				w->setImageryPress_LL(newValueStr);
			else if(propertyName == "imagerypress_lm")
				w->setImageryPress_LM(newValueStr);
			else if(propertyName == "imagerypress_lr")
				w->setImageryPress_LR(newValueStr);
			// Disabled Imagery
			else if(propertyName == "imagerydisabled_ul")
				w->setImageryDisabled_UL(newValueStr);
			else if(propertyName == "imagerydisabled_um")
				w->setImageryDisabled_UM(newValueStr);
			else if(propertyName == "imagerydisabled_ur")
				w->setImageryDisabled_UR(newValueStr);
			else if(propertyName == "imagerydisabled_ml")
				w->setImageryDisabled_ML(newValueStr);
			else if(propertyName == "imagerydisabled_mm")
				w->setImageryDisabled_MM(newValueStr);
			else if(propertyName == "imagerydisabled_mr")
				w->setImageryDisabled_MR(newValueStr);
			else if(propertyName == "imagerydisabled_ll")
				w->setImageryDisabled_LL(newValueStr);
			else if(propertyName == "imagerydisabled_lm")
				w->setImageryDisabled_LM(newValueStr);
			else if(propertyName == "imagerydisabled_lr")
				w->setImageryDisabled_LR(newValueStr);
			else
				//default action (unknown property, don't know how/why we got it here)
				return false;
			return true;
		}
		//#####################################################################
		bool FrameButton::_prop_GetImagery(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			FrameButton* w = static_cast<FrameButton*>(widget);
			assert(w);
			//Normal Imagery
			if(propertyName == "imagerynormal_ul")
				curValue = w->mImageryNormalPtr_UL ? w->mImageryNormalPtr_UL->getName() : "";
			else if(propertyName == "imagerynormal_um")
				curValue = w->mImageryNormalPtr_UM ? w->mImageryNormalPtr_UM->getName() : "";
			else if(propertyName == "imagerynormal_ur")
				curValue = w->mImageryNormalPtr_UR ? w->mImageryNormalPtr_UR->getName() : "";
			else if(propertyName == "imagerynormal_ml")
				curValue = w->mImageryNormalPtr_ML ? w->mImageryNormalPtr_ML->getName() : "";
			else if(propertyName == "imagerynormal_mm")
				curValue = w->mImageryNormalPtr_MM ? w->mImageryNormalPtr_MM->getName() : "";
			else if(propertyName == "imagerynormal_mr")
				curValue = w->mImageryNormalPtr_MR ? w->mImageryNormalPtr_MR->getName() : "";
			else if(propertyName == "imagerynormal_ll")
				curValue = w->mImageryNormalPtr_LL ? w->mImageryNormalPtr_LL->getName() : "";
			else if(propertyName == "imagerynormal_lm")
				curValue = w->mImageryNormalPtr_LM ? w->mImageryNormalPtr_LM->getName() : "";
			else if(propertyName == "imagerynormal_lr")
				curValue = w->mImageryNormalPtr_LR ? w->mImageryNormalPtr_LR->getName() : "";
			//Over Imagery
			else if(propertyName == "imageryover_ul")
				curValue = w->mImageryOverPtr_UL ? w->mImageryOverPtr_UL->getName() : "";
			else if(propertyName == "imageryover_um")
				curValue = w->mImageryOverPtr_UM ? w->mImageryOverPtr_UM->getName() : "";
			else if(propertyName == "imageryover_ur")
				curValue = w->mImageryOverPtr_UR ? w->mImageryOverPtr_UR->getName() : "";
			else if(propertyName == "imageryover_ml")
				curValue = w->mImageryOverPtr_ML ? w->mImageryOverPtr_ML->getName() : "";
			else if(propertyName == "imageryover_mm")
				curValue = w->mImageryOverPtr_MM ? w->mImageryOverPtr_MM->getName() : "";
			else if(propertyName == "imageryover_mr")
				curValue = w->mImageryOverPtr_MR ? w->mImageryOverPtr_MR->getName() : "";
			else if(propertyName == "imageryover_ll")
				curValue = w->mImageryOverPtr_LL ? w->mImageryOverPtr_LL->getName() : "";
			else if(propertyName == "imageryover_lm")
				curValue = w->mImageryOverPtr_LM ? w->mImageryOverPtr_LM->getName() : "";
			else if(propertyName == "imageryover_lr")
				curValue = w->mImageryOverPtr_LR ? w->mImageryOverPtr_LR->getName() : "";
			//Press Imagery
			else if(propertyName == "imagerypress_ul")
				curValue = w->mImageryPressPtr_UL ? w->mImageryPressPtr_UL->getName() : "";
			else if(propertyName == "imagerypress_um")
				curValue = w->mImageryPressPtr_UM ? w->mImageryPressPtr_UM->getName() : "";
			else if(propertyName == "imagerypress_ur")
				curValue = w->mImageryPressPtr_UR ? w->mImageryPressPtr_UR->getName() : "";
			else if(propertyName == "imagerypress_ml")
				curValue = w->mImageryPressPtr_ML ? w->mImageryPressPtr_ML->getName() : "";
			else if(propertyName == "imagerypress_mm")
				curValue = w->mImageryPressPtr_MM ? w->mImageryPressPtr_MM->getName() : "";
			else if(propertyName == "imagerypress_mr")
				curValue = w->mImageryPressPtr_MR ? w->mImageryPressPtr_MR->getName() : "";
			else if(propertyName == "imagerypress_ll")
				curValue = w->mImageryPressPtr_LL ? w->mImageryPressPtr_LL->getName() : "";
			else if(propertyName == "imagerypress_lm")
				curValue = w->mImageryPressPtr_LM ? w->mImageryPressPtr_LM->getName() : "";
			else if(propertyName == "imagerypress_lr")
				curValue = w->mImageryPressPtr_LR ? w->mImageryPressPtr_LR->getName() : "";
			//Disabled Imagery
			else if(propertyName == "imagerydisabled_ul")
				curValue = w->mImageryDisabledPtr_UL ? w->mImageryDisabledPtr_UL->getName() : "";
			else if(propertyName == "imagerydisabled_um")
				curValue = w->mImageryDisabledPtr_UM ? w->mImageryDisabledPtr_UM->getName() : "";
			else if(propertyName == "imagerydisabled_ur")
				curValue = w->mImageryDisabledPtr_UR ? w->mImageryDisabledPtr_UR->getName() : "";
			else if(propertyName == "imagerydisabled_ml")
				curValue = w->mImageryDisabledPtr_ML ? w->mImageryDisabledPtr_ML->getName() : "";
			else if(propertyName == "imagerydisabled_mm")
				curValue = w->mImageryDisabledPtr_MM ? w->mImageryDisabledPtr_MM->getName() : "";
			else if(propertyName == "imagerydisabled_mr")
				curValue = w->mImageryDisabledPtr_MR ? w->mImageryDisabledPtr_MR->getName() : "";
			else if(propertyName == "imagerydisabled_ll")
				curValue = w->mImageryDisabledPtr_LL ? w->mImageryDisabledPtr_LL->getName() : "";
			else if(propertyName == "imagerydisabled_lm")
				curValue = w->mImageryDisabledPtr_LM ? w->mImageryDisabledPtr_LM->getName() : "";
			else if(propertyName == "imagerydisabled_lr")
				curValue = w->mImageryDisabledPtr_LR ? w->mImageryDisabledPtr_LR->getName() : "";
			else
				//default action (unknown property, don't know how/why we got it here)
				return false;
			return true;
		}
		//#####################################################################




		//Below this point are a lot of function that just handle setting imagery and text attributes
		//#####################################################################
		//#####################################################################
		// Normal Imagery
		//#####################################################################
		//#####################################################################
		void FrameButton::setImageryNormal_UL(std::string imageryName)
		{
			dirtyCache();
			mImageryNormalPtr_UL = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryNormal_UM(std::string imageryName)
		{
			dirtyCache();
			mImageryNormalPtr_UM = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryNormal_UR(std::string imageryName)
		{
			dirtyCache();
			mImageryNormalPtr_UR = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryNormal_ML(std::string imageryName)
		{
			dirtyCache();
			mImageryNormalPtr_ML = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryNormal_MM(std::string imageryName)
		{
			dirtyCache();
			mImageryNormalPtr_MM = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryNormal_MR(std::string imageryName)
		{
			dirtyCache();
			mImageryNormalPtr_MR = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryNormal_LL(std::string imageryName)
		{
			dirtyCache();
			mImageryNormalPtr_LL = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryNormal_LM(std::string imageryName)
		{
			dirtyCache();
			mImageryNormalPtr_LM = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryNormal_LR(std::string imageryName)
		{
			dirtyCache();
			mImageryNormalPtr_LR = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################




		//#####################################################################
		//#####################################################################
		// Over Imagery
		//#####################################################################
		//#####################################################################
		void FrameButton::setImageryOver_UL(std::string imageryName)
		{
			dirtyCache();
			mImageryOverPtr_UL = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryOver_UM(std::string imageryName)
		{
			dirtyCache();
			mImageryOverPtr_UM = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryOver_UR(std::string imageryName)
		{
			dirtyCache();
			mImageryOverPtr_UR = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryOver_ML(std::string imageryName)
		{
			dirtyCache();
			mImageryOverPtr_ML = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryOver_MM(std::string imageryName)
		{
			dirtyCache();
			mImageryOverPtr_MM = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryOver_MR(std::string imageryName)
		{
			dirtyCache();
			mImageryOverPtr_MR = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryOver_LL(std::string imageryName)
		{
			dirtyCache();
			mImageryOverPtr_LL = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryOver_LM(std::string imageryName)
		{
			dirtyCache();
			mImageryOverPtr_LM = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryOver_LR(std::string imageryName)
		{
			dirtyCache();
			mImageryOverPtr_LR = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################


		//#####################################################################
		//#####################################################################
		// Press Imagery
		//#####################################################################
		//#####################################################################
		void FrameButton::setImageryPress_UL(std::string imageryName)
		{
			dirtyCache();
			mImageryPressPtr_UL = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryPress_UM(std::string imageryName)
		{
			dirtyCache();
			mImageryPressPtr_UM = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryPress_UR(std::string imageryName)
		{
			dirtyCache();
			mImageryPressPtr_UR = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryPress_ML(std::string imageryName)
		{
			dirtyCache();
			mImageryPressPtr_ML = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryPress_MM(std::string imageryName)
		{
			dirtyCache();
			mImageryPressPtr_MM = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryPress_MR(std::string imageryName)
		{
			dirtyCache();
			mImageryPressPtr_MR = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryPress_LL(std::string imageryName)
		{
			dirtyCache();
			mImageryPressPtr_LL = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryPress_LM(std::string imageryName)
		{
			dirtyCache();
			mImageryPressPtr_LM = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryPress_LR(std::string imageryName)
		{
			dirtyCache();
			mImageryPressPtr_LR = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################






		
		//#####################################################################
		//#####################################################################
		// Disabled Imagery
		//#####################################################################
		//#####################################################################
		void FrameButton::setImageryDisabled_UL(std::string imageryName)
		{
			dirtyCache();
			mImageryDisabledPtr_UL = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryDisabled_UM(std::string imageryName)
		{
			dirtyCache();
			mImageryDisabledPtr_UM = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryDisabled_UR(std::string imageryName)
		{
			dirtyCache();
			mImageryDisabledPtr_UR = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryDisabled_ML(std::string imageryName)
		{
			dirtyCache();
			mImageryDisabledPtr_ML = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryDisabled_MM(std::string imageryName)
		{
			dirtyCache();
			mImageryDisabledPtr_MM = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryDisabled_MR(std::string imageryName)
		{
			dirtyCache();
			mImageryDisabledPtr_MR = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryDisabled_LL(std::string imageryName)
		{
			dirtyCache();
			mImageryDisabledPtr_LL = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryDisabled_LM(std::string imageryName)
		{
			dirtyCache();
			mImageryDisabledPtr_LM = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void FrameButton::setImageryDisabled_LR(std::string imageryName)
		{
			dirtyCache();
			mImageryDisabledPtr_LR = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################







		//#####################################################################
		//#####################################################################
		// Text Property Methods
		//#####################################################################
		//#####################################################################
		void FrameButton::setText(const std::string& newText)
		{
			dirtyCache();
			mText = newText;
		}
		//#####################################################################
		std::string FrameButton::getText()
		{
			return mText;
		}
		//#####################################################################
		void FrameButton::setFont(const std::string& fontName)
		{
			dirtyCache();
			mFontName = fontName;
		}
		//#####################################################################
		std::string FrameButton::getFont()
		{
			return mFontName;
		}
		//#####################################################################
		void FrameButton::setFontSize(unsigned int fontSize_points)
		{
			dirtyCache();
			mFontSize = fontSize_points;
		}
		//#####################################################################
		unsigned int FrameButton::getFontSize()
		{
			return mFontSize;
		}
		//#####################################################################
		void FrameButton::setAlignment_Horiz(TextAlignment alignment)
		{
			dirtyCache();
			mAlignHoriz = alignment;
		}
		//#####################################################################
		TextAlignment FrameButton::getAlignment_Horiz()
		{
			return mAlignHoriz;
		}
		//#####################################################################
		void FrameButton::setAlignment_Vert(TextAlignment alignment)
		{
			dirtyCache();
			mAlignVert = alignment;
		}
		//#####################################################################
		TextAlignment FrameButton::getAlignment_Vert()
		{
			return mAlignVert;
		}
		//#####################################################################
		void FrameButton::setAutoWrap(bool wrap)
		{
			dirtyCache();
			mAutoWrap = wrap;
		}
		//#####################################################################
		bool FrameButton::getAutoWrap()
		{
			return mAutoWrap;
		}
		//#####################################################################

		bool FrameButton::_prop_SetText(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			FrameButton* w = static_cast<FrameButton*>(widget);
			w->setText(newValueStr);
			return true;
		}
		//#####################################################################
		bool FrameButton::_prop_GetText(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			FrameButton* w = static_cast<FrameButton*>(widget);
			curValue = w->getText();
			return true;
		}
		//#####################################################################
		bool FrameButton::_prop_SetFont(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			FrameButton* w = static_cast<FrameButton*>(widget);
			w->setFont(newValueStr);
			return true;
		}
		//#####################################################################
		bool FrameButton::_prop_GetFont(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			FrameButton* w = static_cast<FrameButton*>(widget);
			curValue = w->getFont();
			return true;
		}
		//#####################################################################
		bool FrameButton::_prop_SetFontSize(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			if(!newValuePtr) return false;
			int *t = (int*)newValuePtr;
			FrameButton* w = static_cast<FrameButton*>(widget);
			w->setFontSize((unsigned int)*t);
			return true;
		}
		//#####################################################################
		bool FrameButton::_prop_GetFontSize(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			std::string outval;
			FrameButton* w = static_cast<FrameButton*>(widget);
			return PropertyParser::toStrInt(w->getFontSize(), outval);
		}
		//#####################################################################
		bool FrameButton::_prop_SetHAlign(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			FrameButton* w = static_cast<FrameButton*>(widget);
			if(!w) return false;
			if(newValueStr == "align_left")
				w->setAlignment_Horiz(TextAlignment::ALIGN_LEFT);
			else if(newValueStr == "align_right")
				w->setAlignment_Horiz(TextAlignment::ALIGN_RIGHT);
			else if(newValueStr == "align_center")
				w->setAlignment_Horiz(TextAlignment::ALIGN_CENTER);
			else if(newValueStr == "align_justified")
				w->setAlignment_Horiz(TextAlignment::ALIGN_JUSTIFIED);
			else
				return false;
			return true;
		}
		//#####################################################################
		bool FrameButton::_prop_GetHAlign(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			FrameButton* w = static_cast<FrameButton*>(widget);
			if(!w) return false;
			switch(w->getAlignment_Horiz()){
				case TextAlignment::ALIGN_LEFT:
					curValue = "align_left"; break;
				case TextAlignment::ALIGN_RIGHT:
					curValue = "align_right"; break;
				case TextAlignment::ALIGN_CENTER:
					curValue = "align_center"; break;
				case TextAlignment::ALIGN_JUSTIFIED:
					curValue = "align_justified"; break;
				default:
					return false;
			}
			return true;
		}
		//#####################################################################
		bool FrameButton::_prop_SetVAlign(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			FrameButton* w = static_cast<FrameButton*>(widget);
			if(!w) return false;
			if(newValueStr == "align_top")
				w->setAlignment_Vert(TextAlignment::ALIGN_TOP);
			else if(newValueStr == "align_bottom")
				w->setAlignment_Vert(TextAlignment::ALIGN_BOTTOM);
			else if(newValueStr == "align_center")
				w->setAlignment_Vert(TextAlignment::ALIGN_CENTER);
			else if(newValueStr == "align_justified")
				w->setAlignment_Vert(TextAlignment::ALIGN_JUSTIFIED);
			else
				return false;
			return true;
		}
		//#####################################################################
		bool FrameButton::_prop_GetVAlign(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			FrameButton* w = static_cast<FrameButton*>(widget);
			if(!w) return false;
			switch(w->getAlignment_Vert()){
				case TextAlignment::ALIGN_TOP:
					curValue = "align_top"; break;
				case TextAlignment::ALIGN_BOTTOM:
					curValue = "align_bottom"; break;
				case TextAlignment::ALIGN_CENTER:
					curValue = "align_center"; break;
				case TextAlignment::ALIGN_JUSTIFIED:
					curValue = "align_justified"; break;
				default:
					return false;
			}
			return true;
		}
		//#####################################################################
		bool FrameButton::_prop_SetWrap(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			if(!newValuePtr) return false;
			bool* t = (bool*)newValuePtr;
			FrameButton* w = static_cast<FrameButton*>(widget);
			w->setAutoWrap(*t);
			return true;
		}
		//#####################################################################
		bool FrameButton::_prop_GetWrap(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			std::string outval;
			FrameButton* w = static_cast<FrameButton*>(widget);
			return PropertyParser::toStrBool(w->mAutoWrap, curValue);
		}
		//#####################################################################
	}//namespace Widgets{
}//namespace OpenGUI{
