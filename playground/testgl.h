#include "OpenGLBase.h"
#include <gl\glaux.h>

#include <iostream>
#include <time.h>

#include <OpenGUI.h>
#include <OpenGUI_BaseWidgets.h>
#include <OpenGUI_OGLRenderer.h>

class testgl : public OpenGLBase
{
	bool buttons[3];
	OpenGUI::OGLRenderer *renderer;
	OpenGUI::System *sys;
	OpenGUI::Texture* texture;
	OpenGUI::Texture* texture2;
	OpenGUI::GenericCursor* mCursor;
	bool last;
	GLuint texid;
	void CustomShutdown(){
		delete sys;
		delete renderer;
	}
	void CustomInit()
	{

		renderer = new OpenGUI::OGLRenderer();
		sys = new OpenGUI::System(renderer);

		OpenGUI::ImageryManager::getSingleton().LoadImagesetsFromXML("test.xml");

//		OpenGUI::ImageryManager::getSingleton().createImageset("SilverClean.png");
// 		OpenGUI::ImageryManager::getSingleton().getImageset("SilverClean.png")->createImagery("Button",OpenGUI::IRect(69,2,69+50,2+15));
// 
// 		OpenGUI::ImageryManager::getSingleton().getImageset("SilverClean.png")->createImagery("ButtonDisabled",OpenGUI::IRect(2,103,2+40,103+15));
// 		OpenGUI::ImageryManager::getSingleton().getImageset("SilverClean.png")->createImagery("ButtonDown",OpenGUI::IRect(69,53,69+50,53+15));
// 		OpenGUI::ImageryManager::getSingleton().getImageset("SilverClean.png")->createImagery("ButtonHover",OpenGUI::IRect(69,19,69+50,19+15));
// 		OpenGUI::ImageryManager::getSingleton().getImageset("SilverClean.png")->createImagery("DefaultCursor",OpenGUI::IRect(224,1,224+31,1+32));

		mCursor = new OpenGUI::GenericCursor();
		OpenGUI::CursorManager::getSingleton().addCursor(mCursor,"DefaultCursor");
		mCursor->setImagery("DefaultCursor",OpenGUI::FVector2(0.0f,0.0f));
		
		sys->setGUISheet(sys->createGUISheet("root"));

		
// 		OpenGUI::Widgets::StaticImage* w = new OpenGUI::Widgets::StaticImage();
// 		w->setRect(OpenGUI::FRect(0.25f,0.05f,0.5f,0.10f));
// 		w->setImagery("Button");
// 		sys->getGUISheetByName("root")->addChildElement(w);
// 
// 		w = new OpenGUI::Widgets::StaticImage();
// 		w->setRect(OpenGUI::FRect(0.25f,0.15f,0.5f,0.20f));
// 		w->setImagery("Button");
// 		sys->getGUISheetByName("root")->addChildElement(w);

		
		OpenGUI::Widgets::SimpleButton* button = static_cast<OpenGUI::Widgets::SimpleButton* >(OpenGUI::WidgetFactoryManager::getSingleton().createWidget("OpenGUI", "SimpleButton"));
		//OpenGUI::Widgets::SimpleButton* button = new OpenGUI::Widgets::SimpleButton();
		OpenGUI::Widgets::SimpleButton* button2 = new OpenGUI::Widgets::SimpleButton();

		button->setImagery("Button");
		button->setImageryDisabled("ButtonDisabled");
		button->setImageryPressed("ButtonDown");
		button->setImageryMouseOver("ButtonHover");
		button->setRect(OpenGUI::FRect(0.25f,0.25f,0.45f,0.45f));
		*button2 = *button;
		button2->setRect(OpenGUI::FRect(0.35f,0.15f,0.55f,0.55f));

		button->setClientAreaScaleType(OpenGUI::Element::CAS_Absolute);
		//button->setClipsChildren(false);
		sys->getGUISheetByName("root")->addChildElement(button);
		sys->getGUISheetByName("root")->setClipsChildren(false);
		button->addChildElement(button2);
		button2->setClipsChildren(false);

		last=true;
		//////////////////////////////////////////////////////////////
		
		glEnable(GL_TEXTURE_2D);
		glShadeModel(GL_SMOOTH);
	}

	void CustomDrawOperations()
	{
		static unsigned int fps=0;
		static unsigned int mLastTimerTick = 0;

		unsigned int t = (unsigned long)((float)(clock()-mLastTimerTick) / ((float)CLOCKS_PER_SEC/1000.0));
		if(t>=1000){
			std::cout<<"FPS: " << fps<< "\n";
			mLastTimerTick=clock();
			fps=0;
		}else{
			fps++;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		sys->renderGUI();


		//perform mouse capturing
		RECT wRect;
		WINDOWINFO winfo;winfo.cbSize=sizeof(WINDOWINFO);
		GetWindowInfo(GetHWND(),&winfo);
		wRect = winfo.rcClient;
		POINT point;
		GetCursorPos(&point);
		
		if(	point.x >= wRect.left &&
			point.x < wRect.right &&
			point.y >= wRect.top &&
			point.y < wRect.bottom)
		{
			float x,y;
			x = (float)(point.x-wRect.left) / (float)(wRect.right - wRect.left);
			y = (float)(point.y-wRect.top) / (float)(wRect.bottom - wRect.top);
			sys->injectMousePosition(x,y);
		}
		if(buttons[0] != mouseButtons[0]){
			buttons[0] = mouseButtons[0];
			if(buttons[0])
				sys->injectMouseButtonDown(OpenGUI::MouseButtonLeft);
			else
				sys->injectMouseButtonUp(OpenGUI::MouseButtonLeft);
		}
		if(buttons[1] != mouseButtons[1]){
			buttons[1] = mouseButtons[1];
			if(buttons[1])
				sys->injectMouseButtonDown(OpenGUI::MouseButtonRight);
			else
				sys->injectMouseButtonUp(OpenGUI::MouseButtonRight);
		}
		if(buttons[2] != mouseButtons[2]){
			buttons[2] = mouseButtons[2];
			if(buttons[2])
				sys->injectMouseButtonDown(OpenGUI::MouseButtonMiddle);
			else
				sys->injectMouseButtonUp(OpenGUI::MouseButtonMiddle);
		}
		//
	}
};








