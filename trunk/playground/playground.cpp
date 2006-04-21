// playground.cpp : Defines the entry point for the console application.
//
#include <windows.h>
#include <iostream>

#include <time.h>

#include "OpenGLBase.h"
#include "testgl.h"

#include <OpenGUI.h>



using namespace std;
using namespace OpenGUI;
int main(int argc, char* argv[])
{
	

	testgl* oglb = new testgl();
	oglb->WinMain(GetModuleHandle(0), 0, "", 0);
	return 0;

	
/*
	Foo foo;
	OpenGUI::System *sys = new System();
	Resource res;
	sys->_getResourceProvider()->loadResource("BuildLog.htm",res);

	GUISheet* sheet;
	sys->setGUISheet(sheet = sys->createGUISheet());

	Element* e1 = new Element();
	Element* e2 = new Element();
	e1->setPos(0.5f,0.5f);
	e1->setSize(0.5f,0.5f);
	e2->setPos(0.0f,0.0f);
	e2->setSize(0.5f,0.5f);
	e1->addChildElement(e2,"E2");
	sheet->addChildElement(e1,"E1");

	cout << "test: " << (e2->convCoordInnerToWorld(FVector2(0.5f,0.5f)).toStr()) << "\n";
	cout << "test2: " << (e2->convCoordWorldToInner(FVector2(0.7f,0.7f)).toStr()) << "\n";

	Element* test;
	test = sys->getElementAt(0.6f,0.6f);
	test = sys->getElementAt(0.0f,0.0f);
	test = sys->getElementAt(1.0f,1.0f);
	test = sys->getElementAt(0.25f,0.25f);
	test = sys->getElementAt(0.75f,0.75f);
	test = sys->getElementAt(0.70f,0.70f);
	test = sys->getElementAt(0.80f,0.80f);

	e1->attachEventSubscriber(Subscriber(&testFunc));
	e2->attachEventSubscriber(Subscriber(&testFunc));
	e2->attachEventSubscriber(Subscriber(&foo,&Foo::Bar));
	Event evt;
	evt.EventID=evt.KeyPress; evt.EventData.CustomEvent.CustomEventTypeID=3;
	sys->issueEvent(evt,e1);
	sys->issueEvent(evt,e2);
	e1->detachEventSubscriber(Subscriber(&testFunc));
	e2->detachEventSubscriber(Subscriber(&testFunc));


	e1->setRect(FRect(0.0f,0.0f,1.0f,1.0f));

	e2->setRect(FRect(0.5f,0.5f,1.0f,1.0f));

	sys->destroyGUISheet(sheet);
	delete sys;
	*/
	return 0;
}






