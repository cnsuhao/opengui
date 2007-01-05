// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

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
	unsigned int Cursor::getObjectType() const {
		return OT_CURSOR;
	}
	//############################################################################
	Cursor::Cursor() {
		if ( gCursor_ObjectAccessorList.getParent() == 0 )
			gCursor_ObjectAccessorList.setParent( Object::getAccessors() );

		// initialize defaults for properties
		mSize = FVector2( 20.0f, 20.0f );

		// set up events
		getEvents().createEvent( "Draw" );
		getEvents()["Draw"].add( new EventDelegate( this, &Cursor::onDraw ) );
		getEvents().createEvent( "CursorMove" );
		getEvents().createEvent( "CursorPress" );
		getEvents().createEvent( "CursorRelease" );
		getEvents().createEvent( "CursorHidden" );
		getEvents().createEvent( "CursorShown" );
		getEvents()["CursorMove"].add( new EventDelegate( this, &Cursor::onCursorMove ) );
		getEvents()["CursorPress"].add( new EventDelegate( this, &Cursor::onCursorPress ) );
		getEvents()["CursorRelease"].add( new EventDelegate( this, &Cursor::onCursorRelease ) );
		getEvents()["CursorHidden"].add( new EventDelegate( this, &Cursor::onCursorHidden ) );
		getEvents()["CursorShown"].add( new EventDelegate( this, &Cursor::onCursorShown ) );
	}
	//############################################################################
	Cursor::~Cursor() {
		/**/
	}
	//############################################################################
	void Cursor::onDraw( Object* sender, DrawCursor_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Cursor::onCursorMove( Object* sender, Cursor_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Cursor::onCursorPress( Object* sender, Cursor_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Cursor::onCursorRelease( Object* sender, Cursor_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Cursor::onCursorHidden( Object* sender, EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Cursor::onCursorShown( Object* sender, Cursor_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Cursor::eventDraw( float xPos, float yPos, Brush& brush ) {
		DrawCursor_EventArgs event( xPos, yPos, brush );
		triggerEvent( "Draw", event );
	}
	//############################################################################
	void Cursor::eventCursorMove( float xPos, float yPos ) {
		Cursor_EventArgs event( xPos, yPos );
		triggerEvent( "CursorMove", event );
	}
	//############################################################################
	void Cursor::eventCursorPress( float xPos, float yPos ) {
		Cursor_EventArgs event( xPos, yPos );
		triggerEvent( "CursorPress", event );
	}
	//############################################################################
	void Cursor::eventCursorRelease( float xPos, float yPos ) {
		Cursor_EventArgs event( xPos, yPos );
		triggerEvent( "CursorRelease", event );
	}
	//############################################################################
	void Cursor::eventCursorHidden() {
		EventArgs event;
		triggerEvent( "CursorHidden", event );
	}
	//############################################################################
	void Cursor::eventCursorShown( float xPos, float yPos ) {
		Cursor_EventArgs event( xPos, yPos );
		triggerEvent( "CursorShown", event );
	}
	//############################################################################
}//namespace OpenGUI{
