#include "OpenGUI_Cursor.h"

namespace OpenGUI {

	//############################################################################
	class Cursor_Size_ObjectProperty : public ObjectProperty {
	public:
		virtual const char* getAccessorName() {
			return "Size";
		}
		//############################################################################
		virtual void get( Object& objectRef, Value& valueOut ) {
			try {
				Cursor& c = dynamic_cast<Cursor&>( objectRef );
				valueOut.setValue( c.getSize() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual void set( Object& objectRef, Value& valueIn ) {
			try {
				Cursor& c = dynamic_cast<Cursor&>( objectRef );
				c.setSize( valueIn.getValueAsFVector2() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual Value::ValueType getPropertyType() {
			return Value::T_FVECTOR2;
		}
	}
	gCursor_Size_ObjectProperty;
	//############################################################################
	class Cursor_ObjectAccessorList : public ObjectAccessorList {
	public:
		Cursor_ObjectAccessorList() {
			addAccessor( &gCursor_Size_ObjectProperty );
		}
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
		if ( gCursor_ObjectAccessorList.getParent() == 0 )
			gCursor_ObjectAccessorList.setParent( Object::getAccessors() );

		// initialize defaults for properties
		mSize = FVector2( 20.0f, 20.0f );

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
