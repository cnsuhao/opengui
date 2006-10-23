#include "OpenGUI_Cursor.h"

namespace OpenGUI {

	//############################################################################
	// The base Cursor class has no properties, so there are no Accessors
	class Cursor_ObjectAccessorList : public ObjectAccessorList {
	public:
		Cursor_ObjectAccessorList() {}
		~Cursor_ObjectAccessorList() {}
	}
	gCursor_ObjectAccessorList;
	//############################################################################
	//############################################################################

	//############################################################################
	ObjectAccessorList* Cursor::getAccessors() {
		return &gCursor_ObjectAccessorList;
	}
	//############################################################################
	char* Cursor::getClassName() {
		return "OpenGUI::Cursor";
	}
	//############################################################################
	//############################################################################
	Cursor::Cursor() {
		// initialize defaults for properties
		mSize = FVector2( 10.0f, 10.0f );

		// set up events
		getEvents().createEvent( "Draw" );
		getEvents()["Draw"].add( new EventDelegate( this, &Cursor::onDraw ) );
		getEvents().createEvent( "Cursor_Move" );
		getEvents().createEvent( "Cursor_Press" );
		getEvents().createEvent( "Cursor_Release" );
		getEvents().createEvent( "Cursor_Hidden" );
		getEvents().createEvent( "Cursor_Shown" );
		getEvents()["Cursor_Move"].add( new EventDelegate( this, &Cursor::onCursor_Move ) );
		getEvents()["Cursor_Press"].add( new EventDelegate( this, &Cursor::onCursor_Press ) );
		getEvents()["Cursor_Release"].add( new EventDelegate( this, &Cursor::onCursor_Release ) );
		getEvents()["Cursor_Hidden"].add( new EventDelegate( this, &Cursor::onCursor_Hidden ) );
		getEvents()["Cursor_Shown"].add( new EventDelegate( this, &Cursor::onCursor_Shown ) );
	}
	//############################################################################
	Cursor::~Cursor() {
		/**/
	}
	//############################################################################
	void Cursor::onDraw( Object* sender, DrawCursor_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Cursor::onCursor_Move( Object* sender, Cursor_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Cursor::onCursor_Press( Object* sender, Cursor_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Cursor::onCursor_Release( Object* sender, Cursor_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Cursor::onCursor_Hidden( Object* sender, EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Cursor::onCursor_Shown( Object* sender, Cursor_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Cursor::eventDraw( float xPos, float yPos, Brush& brush ) {
		DrawCursor_EventArgs event( xPos, yPos, brush );
		triggerEvent( "Draw", event );
	}
	//############################################################################
	void Cursor::eventCursor_Move( float xPos, float yPos ) {
		Cursor_EventArgs event( xPos, yPos );
		triggerEvent( "Cursor_Move", event );
	}
	//############################################################################
	void Cursor::eventCursor_Press( float xPos, float yPos ) {
		Cursor_EventArgs event( xPos, yPos );
		triggerEvent( "Cursor_Press", event );
	}
	//############################################################################
	void Cursor::eventCursor_Release( float xPos, float yPos ) {
		Cursor_EventArgs event( xPos, yPos );
		triggerEvent( "Cursor_Release", event );
	}
	//############################################################################
	void Cursor::eventCursor_Hidden() {
		EventArgs event;
		triggerEvent( "Cursor_Hidden", event );
	}
	//############################################################################
	void Cursor::eventCursor_Shown( float xPos, float yPos ) {
		Cursor_EventArgs event( xPos, yPos );
		triggerEvent( "Cursor_Shown", event );
	}
	//############################################################################
}//namespace OpenGUI{
