#include "OpenGUI_BaseWidgets.h"
#include <iostream>
namespace OpenGUI{
	namespace Widgets{
		//#####################################################################
		SimpleButton::SimpleButton()
		{
			m_MouseOver=false;
			m_ButtonDown=false;
		}
		//#####################################################################
		SimpleButton::~SimpleButton() {

		}
		//#####################################################################
		Render::RenderOperationList SimpleButton::buildWidgetRenderOpList()
		{
			Render::PrimitiveBox box;
			box.setRect(mElementRect);
			box.setTextureImagery(mImageryPtr);
			if(mDisabled){
				if(mImageryPtrDisabled)
					box.setTextureImagery(mImageryPtrDisabled);
			}else{
				if(m_MouseOver){
					if(m_ButtonDown){
						if(mImageryPtrPressed)
							box.setTextureImagery(mImageryPtrPressed);
					}else{
						if(mImageryPtrMouseOver)
							box.setTextureImagery(mImageryPtrMouseOver);
					}
				}else{
					box.setTextureImagery(mImageryPtr);
				}
			}
			return box.getRenderOperationList();
		}
		//#####################################################################
		void SimpleButton::setImagery(std::string imageryName)
		{
			mImageryPtr = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void SimpleButton::setImageryPressed(std::string imageryName)
		{
			mImageryPtrPressed = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void SimpleButton::setImageryMouseOver(std::string imageryName)
		{
			mImageryPtrMouseOver = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		void SimpleButton::setImageryDisabled(std::string imageryName)
		{
			mImageryPtrDisabled = ImageryManager::getSingleton().getImagery(imageryName);
		}
		//#####################################################################
		bool SimpleButton::defaultMessageHandler(const Msg::Message &message)
		{
			if(message.messageType==message.MT_EVENT){
				
				if(message.event.destination!=this)
					return true;

				//handle mouse just entered
				if (message.event.type==message.event.ME_MouseEnter)
				{
					if(System::getSingleton().setTrackMouseLeave(this)){
						m_MouseOver=true;
					}
					return true;
				}

				if (message.event.type==message.event.ME_MouseClick){
					std::cout << "! CLICK!\n";
					return true;
				}
				if (message.event.type==message.event.ME_MouseDblClick){
					std::cout << "## DBLCLICK!\n";
					return true;
				}

				if (message.event.type==message.event.ME_MouseLeave)
				{
					m_MouseOver=false;
				}

				if (message.event.type==message.event.ME_MouseButtonDown)
				{
					System::getSingleton().setCaptureMouse(this);
					m_ButtonDown = true;
				}
				if (message.event.type==message.event.ME_MouseButtonUp)
				{
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
							m_MouseOver=true;
						}
					}
				}
			}
			return true;
		}
		//#####################################################################
	};
};