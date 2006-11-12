#include "OpenGUI.h" // we obviously need this

using namespace OpenGUI; // bring OpenGUI into this scope

class MyWidget : public Control {
public:
	MyWidget();
	virtual ~MyWidget();

	// Property: MyBool
	void setMyBool( bool value ); // set mMyBool
	bool getMyBool();             // get mMyBool

	// Event: MyEvent
	void eventMyEvent(); // event processor for MyEvent
	virtual void onMyEvent(Object* sender, EventArgs& args); // event handler for MyEvent

	virtual void onDraw(Object* sender, Draw_EventArgs& args); // override onDraw event
private:
	bool mMyBool;
};
