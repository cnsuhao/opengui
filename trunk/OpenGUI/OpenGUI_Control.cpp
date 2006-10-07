#include "OpenGUI_Control.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	//############################################################################
	class Control_Left_ObjectProperty : public ObjectProperty {
	public:
		virtual const char* getAccessorName() {
			return "Left";
		}
		//############################################################################
		virtual void get( Object& objectRef, Value& valueOut ) {
			try {
				Control& c = dynamic_cast<Control&>( objectRef );
				valueOut.setValue( c.getLeft() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual void set( Object& objectRef, Value& valueIn ) {
			try {
				Control& c = dynamic_cast<Control&>( objectRef );
				c.setLeft( valueIn.getValueAsFloat() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual Value::ValueType getPropertyType() {
			return Value::T_FLOAT;
		}
	}
	gControl_Left_ObjectProperty;
	//############################################################################
	class Control_Top_ObjectProperty : public ObjectProperty {
	public:
		virtual const char* getAccessorName() {
			return "Top";
		}
		//############################################################################
		virtual void get( Object& objectRef, Value& valueOut ) {
			try {
				Control& c = dynamic_cast<Control&>( objectRef );
				valueOut.setValue( c.getTop() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual void set( Object& objectRef, Value& valueIn ) {
			try {
				Control& c = dynamic_cast<Control&>( objectRef );
				c.setTop( valueIn.getValueAsFloat() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual Value::ValueType getPropertyType() {
			return Value::T_FLOAT;
		}
	}
	gControl_Top_ObjectProperty;
	//############################################################################
	class Control_Width_ObjectProperty : public ObjectProperty {
	public:
		virtual const char* getAccessorName() {
			return "Width";
		}
		//############################################################################
		virtual void get( Object& objectRef, Value& valueOut ) {
			try {
				Control& c = dynamic_cast<Control&>( objectRef );
				valueOut.setValue( c.getWidth() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual void set( Object& objectRef, Value& valueIn ) {
			try {
				Control& c = dynamic_cast<Control&>( objectRef );
				c.setWidth( valueIn.getValueAsFloat() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual Value::ValueType getPropertyType() {
			return Value::T_FLOAT;
		}
	}
	gControl_Width_ObjectProperty;
	//############################################################################
	class Control_Height_ObjectProperty : public ObjectProperty {
	public:
		virtual const char* getAccessorName() {
			return "Height";
		}
		//############################################################################
		virtual void get( Object& objectRef, Value& valueOut ) {
			try {
				Control& c = dynamic_cast<Control&>( objectRef );
				valueOut.setValue( c.getHeight() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual void set( Object& objectRef, Value& valueIn ) {
			try {
				Control& c = dynamic_cast<Control&>( objectRef );
				c.setHeight( valueIn.getValueAsFloat() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual Value::ValueType getPropertyType() {
			return Value::T_FLOAT;
		}
	}
	gControl_Height_ObjectProperty;
	//############################################################################
	//############################################################################
	class Control_Position_ObjectProperty : public ObjectProperty {
	public:
		virtual const char* getAccessorName() {
			return "Position";
		}
		//############################################################################
		virtual void get( Object& objectRef, Value& valueOut ) {
			try {
				Control& c = dynamic_cast<Control&>( objectRef );
				valueOut.setValue( c.getPosition() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual void set( Object& objectRef, Value& valueIn ) {
			/* read-only property */
		}
		//############################################################################
		virtual Value::ValueType getPropertyType() {
			return Value::T_FVECTOR2;
		}
		//############################################################################
		virtual bool getPermSettable() {
			return false; //read-only property
		}
	}
	gControl_Position_ObjectProperty;
	//############################################################################
	class Control_Size_ObjectProperty : public ObjectProperty {
	public:
		virtual const char* getAccessorName() {
			return "Size";
		}
		//############################################################################
		virtual void get( Object& objectRef, Value& valueOut ) {
			try {
				Control& c = dynamic_cast<Control&>( objectRef );
				valueOut.setValue( c.getSize() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual void set( Object& objectRef, Value& valueIn ) {
			/* read-only property */
		}
		//############################################################################
		virtual Value::ValueType getPropertyType() {
			return Value::T_FVECTOR2;
		}
		//############################################################################
		virtual bool getPermSettable() {
			return false; //read-only property
		}
	}
	gControl_Size_ObjectProperty;
	//############################################################################
	class Control_Rect_ObjectProperty : public ObjectProperty {
	public:
		virtual const char* getAccessorName() {
			return "Rect";
		}
		//############################################################################
		virtual void get( Object& objectRef, Value& valueOut ) {
			try {
				Control& c = dynamic_cast<Control&>( objectRef );
				valueOut.setValue( c.getRect() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual void set( Object& objectRef, Value& valueIn ) {
			/* read-only property */
		}
		//############################################################################
		virtual Value::ValueType getPropertyType() {
			return Value::T_FRECT;
		}
		//############################################################################
		virtual bool getPermSettable() {
			return false; //read-only property
		}
	}
	gControl_Rect_ObjectProperty;
	//############################################################################
	//############################################################################
	class Control_ObjectAccessorList : public ObjectAccessorList {
	public:
		Control_ObjectAccessorList() {
			addAccessor( &gControl_Left_ObjectProperty );
			addAccessor( &gControl_Top_ObjectProperty );
			addAccessor( &gControl_Width_ObjectProperty );
			addAccessor( &gControl_Height_ObjectProperty );

			addAccessor( &gControl_Position_ObjectProperty );
			addAccessor( &gControl_Size_ObjectProperty );
			addAccessor( &gControl_Rect_ObjectProperty );
		}
		~Control_ObjectAccessorList() {}
	}
	gControl_ObjectAccessorList;
	//############################################################################
	//############################################################################


	//############################################################################
	Control::Control() {
		if ( gControl_ObjectAccessorList.getParent() == 0 )
			gControl_ObjectAccessorList.setParent( Widget::getAccessors() );

		mCursorInside = false; //cursor always starts "outside"

		// set up defaults for properties
		mRect = FRect( 0.0f, 0.0f, 1.0f, 1.0f );

		//Set up events and default bindings
		getEvents().createEvent( "Cursor_Click" );
		getEvents().createEvent( "Cursor_Enter" );
		getEvents().createEvent( "Cursor_Leave" );
		getEvents()["Cursor_Click"].add( new EventDelegate( this, &Control::onCursor_Click ) );
		getEvents()["Cursor_Enter"].add( new EventDelegate( this, &Control::onCursor_Enter ) );
		getEvents()["Cursor_Leave"].add( new EventDelegate( this, &Control::onCursor_Leave ) );
	}
	//############################################################################
	Control::~Control() {
		/**/
	}
	//############################################################################
	ObjectAccessorList* Control::getAccessors() {
		return &gControl_ObjectAccessorList;
	}
	//############################################################################
	char* Control::getClassName() {
		return "OpenGUI::Control";
	}
	//############################################################################
	void Control::setLeft( float left ) {
		mRect.setPosition( FVector2( left, mRect.min.y ) );
	}
	//############################################################################
	float Control::getLeft() {
		return mRect.min.x;
	}
	//############################################################################
	void Control::setTop( float top ) {
		mRect.setPosition( FVector2( mRect.min.x, top ) );
	}
	//############################################################################
	float Control::getTop() {
		return mRect.min.y;
	}
	//############################################################################
	/*! Controls cannot have a width less than 0.0f, so negative values are clamped to 0.0f */
	void Control::setWidth( float width ) {
		if ( width < 0.0f ) width = 0.0f;
		mRect.setWidth( width );
	}
	//############################################################################
	float Control::getWidth() {
		return mRect.getWidth();
	}
	//############################################################################
	/*! Controls cannot have a height less than 0.0f, so negative values are clamped to 0.0f */
	void Control::setHeight( float height ) {
		if ( height < 0.0f ) height = 0.0f;
		mRect.setHeight( height );
	}
	//############################################################################
	float Control::getHeight() {
		return mRect.getHeight();
	}
	//############################################################################
	const FVector2& Control::getPosition() {
		return mRect.min;
	}
	//############################################################################
	FVector2 Control::getSize() {
		return mRect.getSize();
	}
	//############################################################################
	const FRect& Control::getRect() {
		return mRect;
	}
	//############################################################################
	void Control::onCursor_Click( Object* sender, Cursor_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Control::onCursor_Enter( Object* sender, Cursor_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Control::onCursor_Leave( Object* sender, Cursor_EventArgs& evtArgs ) {
		/* Default is to do nothing */
	}
	//############################################################################
	void Control::eventCursor_Click( Cursor_EventArgs& evtArgs ) {
		getEvents()["Cursor_Click"].invoke( this, evtArgs );
	}
	//############################################################################
	void Control::eventCursor_Enter( Cursor_EventArgs& evtArgs ) {
		getEvents()["Cursor_Enter"].invoke( this, evtArgs );
	}
	//############################################################################
	void Control::eventCursor_Leave( Cursor_EventArgs& evtArgs ) {
		getEvents()["Cursor_Leave"].invoke( this, evtArgs );
	}
	//############################################################################
	/*! To preserve this functionality in future overrides, the base class
	version of this method will need to be called. */
	void Control::onCursor_Move( Object* sender, Cursor_EventArgs& evtArgs ) {
		//mCursorEnterLeave_Sent
		if ( mCursorInside ) {
			// test if cursor is outside
			if ( mRect.isInside( evtArgs.Position ) ) {
				mCursorInside = false; // store the new state
				eventCursor_Leave( evtArgs ); // let everyone know
			}
		} else {
			// test if cursor is inside
			if ( mRect.isInside( evtArgs.Position ) ) {
				mCursorInside = true; // store the new state
				eventCursor_Enter( evtArgs ); // let everyone know
			}
		}
	}
	//############################################################################
} // namespace OpenGUI {
