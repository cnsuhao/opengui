#include "custom_widget.h" // using namespace OpenGUI is performed within header

// local ObjectProperty to handle MyBool
class MyWidget_MyBool_ObjectProperty : public ObjectProperty {
public:
	virtual const char* getAccessorName() {
		return "MyBool";
	}

	virtual void get( Object& objectRef, Value& valueOut ) {
		try {
			MyWidget& w = dynamic_cast<MyWidget&>( objectRef );
			valueOut.setValue( w.getMyBool() );
		} catch ( std::bad_cast e ) {
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
		}
	}

	virtual void set( Object& objectRef, Value& valueIn ) {
		try {
			MyWidget& w = dynamic_cast<MyWidget&>( objectRef );
			w.setMyBool( valueIn.getValueAsBool() );
		} catch ( std::bad_cast e ) {
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
		}
	}

	virtual Value::ValueType getPropertyType() {
		return Value::T_BOOL;
	}
}
gMyWidget_MyBool_ObjectProperty;


// local ObjectAccessorList
class MyWidget_ObjectAccessorList : public ObjectAccessorList {
public:
	MyWidget_ObjectAccessorList() {
		addAccessor( &gMyWidget_MyBool_ObjectProperty );
	}
	~MyWidget_ObjectAccessorList() {}
}
gMyWidget_ObjectAccessorList;



//####################################################
// MyWidget class implementation begins here

// constructor
MyWidget::MyWidget(){
	// ensure our static property handler is ready to go
	if( gMyWidget_ObjectAccessorList.getParent() == 0 )
		gMyWidget_ObjectAccessorList.setParent( Control::getAccessors() );

	// create the event
	getEvents().createEvent( "MyEvent" );

	// and then bind the default handler
	getEvents()["MyEvent"].add( new EventDelegate( this, &MyWidget::onMyEvent ) );
}

// destructor
MyWidget::~MyWidget() {
	/* nothing special necessary here */
}


// native access functions for MyBool property
void MyWidget::setMyBool( bool value ){
	mMyBool = value;
}
bool MyWidget::getMyBool(){
	return mMyBool;
}


// event processor
void MyWidget::eventMyEvent(){
	EventArgs myArgs;
	triggerEvent( "MyEvent", myArgs );
}

// default event handler
void MyWidget::onMyEvent(Object* sender, EventArgs& args){
	/* do something important */
}

// new onDraw implementation
void MyWidget::onDraw(Object* sender, Draw_EventArgs& args){
	//call base first so we draw over top of it
	Control::onDraw(sender, args);

	Brush& b = args.brush; // get a new reference to brush so it's easier to use
	b.pushColor( Color::PresetRed() ); // set the brush color to red
	b.Primitive.drawRect( getRect() ); // draw a rectangle using our position and size
	b.pop(); // pop off our previous color push, because pop'ing what you push is neighborly
}