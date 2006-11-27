#include "OpenGUI_Control.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_ContainerControl.h"

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
	class Control_Visible_ObjectProperty : public ObjectProperty {
	public:
		virtual const char* getAccessorName() {
			return "Visible";
		}
		//############################################################################
		virtual void get( Object& objectRef, Value& valueOut ) {
			try {
				Control& c = dynamic_cast<Control&>( objectRef );
				valueOut.setValue( c.getVisible() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual void set( Object& objectRef, Value& valueIn ) {
			try {
				Control& c = dynamic_cast<Control&>( objectRef );
				c.setVisible( valueIn.getValueAsBool() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual Value::ValueType getPropertyType() {
			return Value::T_BOOL;
		}
	}
	gControl_Visible_ObjectProperty;
	//############################################################################
	class Control_Alpha_ObjectProperty : public ObjectProperty {
	public:
		virtual const char* getAccessorName() {
			return "Alpha";
		}
		//############################################################################
		virtual void get( Object& objectRef, Value& valueOut ) {
			try {
				Control& w = dynamic_cast<Control&>( objectRef );
				valueOut.setValue( w.getAlpha() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual void set( Object& objectRef, Value& valueIn ) {
			try {
				Control& w = dynamic_cast<Control&>( objectRef );
				w.setAlpha( valueIn.getValueAsFloat() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual Value::ValueType getPropertyType() {
			return Value::T_FLOAT;
		}
	}
	gControl_Alpha_ObjectProperty;
	//############################################################################
	class Control_MaxSize_ObjectProperty : public ObjectProperty {
	public:
		virtual const char* getAccessorName() {
			return "MaximumSize";
		}
		//############################################################################
		virtual void get( Object& objectRef, Value& valueOut ) {
			try {
				Control& w = dynamic_cast<Control&>( objectRef );
				valueOut.setValue( w.getMaximumSize() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual void set( Object& objectRef, Value& valueIn ) {
			try {
				Control& w = dynamic_cast<Control&>( objectRef );
				w.setMaximumSize( valueIn.getValueAsFVector2() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual Value::ValueType getPropertyType() {
			return Value::T_FVECTOR2;
		}
	}
	gControl_MaxSize_ObjectProperty;
	//############################################################################
	class Control_MinSize_ObjectProperty : public ObjectProperty {
	public:
		virtual const char* getAccessorName() {
			return "MinimumSize";
		}
		//############################################################################
		virtual void get( Object& objectRef, Value& valueOut ) {
			try {
				Control& w = dynamic_cast<Control&>( objectRef );
				valueOut.setValue( w.getMinimumSize() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual void set( Object& objectRef, Value& valueIn ) {
			try {
				Control& w = dynamic_cast<Control&>( objectRef );
				w.setMinimumSize( valueIn.getValueAsFVector2() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual Value::ValueType getPropertyType() {
			return Value::T_FVECTOR2;
		}
	}
	gControl_MinSize_ObjectProperty;
	//############################################################################
	class Control_Margin_ObjectProperty : public ObjectProperty {
	public:
		virtual const char* getAccessorName() {
			return "Margin";
		}
		//############################################################################
		virtual void get( Object& objectRef, Value& valueOut ) {
			try {
				Control& c = dynamic_cast<Control&>( objectRef );
				valueOut.setValue( c.getMargin() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual void set( Object& objectRef, Value& valueIn ) {
			try {
				Control& c = dynamic_cast<Control&>( objectRef );
				c.setMargin( valueIn.getValueAsFloat() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual Value::ValueType getPropertyType() {
			return Value::T_FLOAT;
		}
	}
	gControl_Margin_ObjectProperty;
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

			addAccessor( &gControl_Visible_ObjectProperty );
			addAccessor( &gControl_Alpha_ObjectProperty );

			addAccessor( &gControl_MaxSize_ObjectProperty );
			addAccessor( &gControl_MinSize_ObjectProperty );

			addAccessor( &gControl_Margin_ObjectProperty );
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

		// initialize state variables
		mCursorInside = false; //cursor always starts "outside"
		m_InDockAnchor = false; // we're not in a dock/anchor operation, since we just instantiated
		m_InLayout = false; // we're not in a layout operation, since we just instantiated

		// set up defaults for properties
		mAlpha = 1.0f; //start with 100% alpha (fully opaque)
		mRect = FRect( 0.0f, 0.0f, 1.0f, 1.0f );
		mVisible = true;
		mMinSize = FVector2( 0, 0 );
		mMaxSize = FVector2( 0, 0 );
		mAnchors = Left | Top;
		mDock = None;
		mMargin = 0.0f;

		//Set up events and default bindings
		getEvents().createEvent( "Cursor_Click" );
		getEvents().createEvent( "Cursor_Enter" );
		getEvents().createEvent( "Cursor_Leave" );
		getEvents()["Cursor_Click"].add( new EventDelegate( this, &Control::onCursor_Click ) );
		getEvents()["Cursor_Enter"].add( new EventDelegate( this, &Control::onCursor_Enter ) );
		getEvents()["Cursor_Leave"].add( new EventDelegate( this, &Control::onCursor_Leave ) );
		getEvents().createEvent( "Targeted" );
		getEvents().createEvent( "UnTargeted" );
		getEvents()["Targeted"].add( new EventDelegate( this, &Control::onTargeted ) );
		getEvents()["UnTargeted"].add( new EventDelegate( this, &Control::onUnTargeted ) );
		getEvents().createEvent( "Moved" );
		getEvents().createEvent( "Resized" );
		getEvents()["Moved"].add( new EventDelegate( this, &Control::onMoved ) );
		getEvents()["Resized"].add( new EventDelegate( this, &Control::onResized ) );
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
	void Control::_draw( Brush& brush ) {
		if ( mVisible ) {
			brush.pushAlpha( mAlpha );
			Widget::_draw( brush );
			brush.pop();
		}
	}
	//############################################################################
	/*! Control implementation returns true if the point is within its rect,
	otherwise false.
	\note This function is \b not focus aware. The given \c position should already
	be in the correct coordinate space. */
	bool Control::_isInside( const FVector2& position ) {
		return mRect.isInside( position );
	}
	//############################################################################
	void Control::setLeft( float left ) {
		FVector2 oldPos = getPosition();
		if ( oldPos.x != left ) { // only bother with all this if the value is different
			mRect.setPosition( FVector2( left, oldPos.y ) );
			eventMoved( oldPos, getPosition() );
			if ( !m_InLayout ) { // only do this if we are not under control of the container during layouts
				if ( mDock ) { // if we aren't docking, no one will be depending on us for the layout
					// need to break docking because moving while docked is illegal
					_breakDocking(); // this will call _invalidateLayout() as a byproduct
				}
			}
			invalidate(); // need to invalidate caches for position change
		}
	}
	//############################################################################
	float Control::getLeft() {
		return mRect.min.x;
	}
	//############################################################################
	void Control::setTop( float top ) {
		FVector2 oldPos = getPosition();
		if ( oldPos.y != top ) { // only bother with all this if the value is different
			mRect.setPosition( FVector2( oldPos.x, top ) );
			eventMoved( oldPos, getPosition() );
			if ( !m_InLayout ) { // only do this if we are not under control of the container during layouts
				if ( mDock ) { // if we aren't docking, no one will be depending on us for the layout
					// need to break docking because moving while docked is illegal
					_breakDocking(); // this will call _invalidateLayout() as a byproduct
				}
			}
			invalidate(); // need to invalidate caches for position change
		}
	}
	//############################################################################
	float Control::getTop() {
		return mRect.min.y;
	}
	//############################################################################
	/*! Controls cannot have a width less than 0.0f, so negative values are clamped to 0.0f.

	This function obeys the MinimumSize and MaximumSize properties, and the given size
	will be adjusted to fit within the constraints if applicable.
	*/
	void Control::setWidth( float width ) {
		if ( width < 0.0f ) width = 0.0f;
		if ( mMinSize.x > 0 && width < mMinSize.x )
			width = mMinSize.x;
		if ( mMaxSize.x > 0 && width > mMaxSize.x )
			width = mMaxSize.x;

		FVector2 oldSize = getSize();
		if ( oldSize.x != width ) { // only bother with all this if the value is different
			mRect.setWidth( width );
			eventResized( oldSize, getSize() );
			if ( !m_InLayout ) { // only do this if we are not under control of the container during layouts
				if ( mDock ) { // if we aren't docking, no one will be depending on us for the layout
					if (( mDock & Top ) || ( mDock & Bottom ) ) { // (mDock & Full) is implied
						// need to break docking because we resized along a layout controlled axis
						_breakDocking(); // this will call _invalidateLayout() as a byproduct
					} else {
						// otherwise we just need to invalidate our layout
						_invalidateLayout();
					}
				}
			}
			invalidate(); // need to invalidate caches for size change
		}
	}
	//############################################################################
	float Control::getWidth() {
		return mRect.getWidth();
	}
	//############################################################################
	/*! Controls cannot have a height less than 0.0f, so negative values are clamped to 0.0f.

	This function obeys the MinimumSize and MaximumSize properties, and the given size
	will be adjusted to fit within the constraints if applicable.
	*/
	void Control::setHeight( float height ) {
		if ( height < 0.0f ) height = 0.0f;
		if ( mMinSize.y > 0 && height < mMinSize.y )
			height = mMinSize.y;
		if ( mMaxSize.y > 0 && height > mMaxSize.y )
			height = mMaxSize.y;

		FVector2 oldSize = getSize();
		if ( oldSize.y != height ) { // only bother with all this if the value is different
			mRect.setHeight( height );
			eventResized( oldSize, getSize() );
			if ( !m_InLayout ) { // only do this if we are not under control of the container during layouts
				if ( mDock ) { // if we aren't docking, no one will be depending on us for the layout
					if (( mDock & Left ) || ( mDock & Right ) ) { // (mDock & Full) is implied
						// need to break docking because we resized along a layout controlled axis
						_breakDocking(); // this will call _invalidateLayout() as a byproduct
					} else {
						// otherwise we just need to invalidate our layout
						_invalidateLayout();
					}
				}
			}
			invalidate(); // need to invalidate caches for size change
		}
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
	const FVector2& Control::getMinimumSize() {
		return mMinSize;
	}
	//############################################################################
	/*! During this call the current size is tested against the new minimum size
	and calls to setWidth and setHeight may be invoked to bring the Controls
	size back into the allowed constraints.

	If the the minimum size is set larger than the maximum size, the maximum size
	is adjusted to match the minimum size for any offending axis.

	If any axis == 0, that axis will be ignored in size tests. Negative values for
	an axis are illegal and are automatically assigned to 0.
	*/
	void Control::setMinimumSize( const FVector2& size ) {
		mMinSize = size;
		if ( mMinSize.x < 0 ) mMinSize.x = 0;
		if ( mMinSize.y < 0 ) mMinSize.y = 0;
		FVector2 curSize = getSize();
		if ( mMinSize.x > 0 ) {
			if ( mMaxSize.x > 0 && mMinSize.x > mMaxSize.x ) mMaxSize.x = mMinSize.x;
			if ( curSize.x < mMinSize.x ) setWidth( mMinSize.x );
		}
		if ( mMinSize.x > 0 ) {
			if ( mMaxSize.y > 0 && mMinSize.y > mMaxSize.y ) mMaxSize.y = mMinSize.y;
			if ( curSize.y < mMinSize.y ) setHeight( mMinSize.y );
		}
	}
	//############################################################################
	const FVector2& Control::getMaximumSize() {
		return mMaxSize;
	}
	//############################################################################
	/*! During this call the current size is tested against the new maximum size
	and calls to setWidth and setHeight may be invoked to bring the Controls
	size back into the allowed constraints.

	If the the maximum size is set smaller than the minimum size, the minimum size
	is adjusted to match the maximum size for any offending axis.

	If any axis == 0, that axis will be ignored in size tests. Negative values for
	an axis are illegal and are automatically assigned to 0.
	*/
	void Control::setMaximumSize( const FVector2& size ) {
		mMaxSize = size;
		if ( mMaxSize.x < 0 ) mMaxSize.x = 0;
		if ( mMaxSize.y < 0 ) mMaxSize.y = 0;
		FVector2 curSize = getSize();
		if ( mMaxSize.x > 0 ) {
			if ( mMinSize.x > 0 && mMinSize.x > mMaxSize.x ) mMinSize.x = mMaxSize.x;
			if ( curSize.x > mMaxSize.x ) setWidth( mMaxSize.x );
		}
		if ( mMaxSize.x > 0 ) {
			if ( mMinSize.y > 0 && mMinSize.y > mMaxSize.y ) mMinSize.y = mMaxSize.y;
			if ( curSize.y > mMaxSize.y ) setHeight( mMaxSize.y );
		}
	}
	//############################################################################
	void Control::setVisible( bool visible ) {
		mVisible = visible;
		invalidate(); // need to invalidate caches for visibility change
	}
	//############################################################################
	bool Control::getVisible() {
		return mVisible;
	}
	//############################################################################
	/*! Alpha is clamped to 0.0f through 1.0f. Passing values outside of this
	range will result in alpha being set to either 0.0f or 1.0f, whichever is
	closer.

	The local Alpha setting is a value that is not automatically enforced before
	onDraw(), meaning that if a Control is going to obey its Alpha setting, it
	should push that setting to the Brush before performing its draw routines.

	In the case of Controls that contain other Controls, Alpha of the parent is
	automatically applied to the children in a multiplicative fashion. In other words,
	if both the parent and child Controls are set to 50% alpha, at final output the 
	parent will draw at 50% alpha, and the child will draw at 25% alpha.
	\n (50% * 50% = 25%)
	*/
	void Control::setAlpha( float alpha ) {
		if ( alpha < 0.0f ) alpha = 0.0f;
		if ( alpha > 1.0f ) alpha = 1.0f;
		mAlpha = alpha;
		invalidate(); // need to invalidate caches for alpha change
	}
	//############################################################################
	float Control::getAlpha() {
		return mAlpha;
	}
	//############################################################################
	void Control::onCursor_Click( Object* sender, Cursor_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Control::onCursor_Enter( Object* sender, Cursor_EventArgs& evtArgs ) {
		eventTargeted(); // notify targeted
	}
	//############################################################################
	void Control::onCursor_Leave( Object* sender, Cursor_EventArgs& evtArgs ) {
		eventUnTargeted(); // notify untargeted
	}
	//############################################################################
	void Control::eventCursor_Click( Cursor_EventArgs& evtArgs ) {
		triggerEvent( "Cursor_Click", evtArgs );
	}
	//############################################################################
	void Control::eventCursor_Enter( Cursor_EventArgs& evtArgs ) {
		triggerEvent( "Cursor_Enter", evtArgs );
	}
	//############################################################################
	void Control::eventCursor_Leave( Cursor_EventArgs& evtArgs ) {
		triggerEvent( "Cursor_Leave", evtArgs );
	}
	//############################################################################
	/*! To preserve this functionality in future overrides, the base class
	version of this method will need to be called.

	Control implementation tracks cursor position and generates \c Cursor_Enter and
	\c Cursor_Leave as appropriate according to the result of _isInside().

	\note This function \b is cursor focus aware, and will do the "right thing"
	in order to ensure proper generation of Cursor_Enter/Cursor_Leave events.
	*/
	void Control::onCursor_Move( Object* sender, Cursor_EventArgs& evtArgs ) {
		FVector2 pos = evtArgs.Position;
		if ( hasCursorFocus() ) // translate point if necessary
			pos = pointFromScreen( pos );

		//mCursorEnterLeave_Sent
		if ( mCursorInside ) {
			// test if cursor is outside
			if ( !_isInside( pos ) ) {
				mCursorInside = false; // store the new state
				eventCursor_Leave( evtArgs ); // let everyone know
			}
		} else {
			// test if cursor is inside
			if ( _isInside( pos ) ) {
				mCursorInside = true; // store the new state
				eventCursor_Enter( evtArgs ); // let everyone know
			}
		}
	}
	//############################################################################
	void Control::onTargeted( Object* sender, EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Control::onUnTargeted( Object* sender, EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Control::eventTargeted() {
		EventArgs eventArgs;
		triggerEvent( "Targeted", eventArgs );
	}
	//############################################################################
	void Control::eventUnTargeted() {
		EventArgs eventArgs;
		triggerEvent( "UnTargeted", eventArgs );
	}
	//############################################################################
	void Control::onMoved( Object* sender, Moved_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Control::onResized( Object* sender, Resized_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void Control::eventMoved( const FVector2& oldPosition, const FVector2& newPosition ) {
		Moved_EventArgs event( oldPosition, newPosition );
		triggerEvent( "Moved", event );
	}
	//############################################################################
	void Control::eventResized( const FVector2& oldSize, const FVector2& newSize ) {
		Resized_EventArgs event( newSize, oldSize );
		triggerEvent( "Resized", event );
	}
	//############################################################################
	/*! Docking is a service provided by the container. It
	\note Docking and Anchoring are mutually exclusive. Defining new anchors will remove
	any docking preferences. Conversely, selecting dockings will reset anchoring to the
	default (Top/Left).
	*/
	void Control::setDocking( int dockStyle ) {
		dockStyle = dockStyle & Fill; //mask down to only relevant values
		int dockType = 0; // start with a clear setting in case we don't match anything

		// now only accept valid single values
		if ( dockStyle == Fill ) dockType = Fill;
		if ( dockStyle == Top ) dockType = Top;
		if ( dockStyle == Left ) dockType = Left;
		if ( dockStyle == Bottom ) dockType = Bottom;
		if ( dockStyle == Right ) dockType = Right;

		if ( dockType != mDock ) { // we only need to do this if we came up with a new result
			mDock = dockType;
			if ( !m_InDockAnchor ) {
				m_InDockAnchor = true;
				setAnchor( Top | Left );
				invalidate();
				_invalidateLayout();
				m_InDockAnchor = false;
			}
		}
	}
	//############################################################################
	/*! Return value will be a single value within ControlSides. */
	int Control::getDocking() {
		return mDock;
	}
	//############################################################################
	/*! Anchoring is a service provided by the container. During resizes the container
	will check all of its children for Anchor preference. The children can specify anchoring
	preference to any sides they wish, but at least one top/bottom and one left/right side
	must be specified at all times.\n
	For example, it is legal to anchor against:
	- Top/Left
	- Top/Right
	- Top/Left/Right
	- Bottom/Left
	- All (also known as Fill)
	It is not legal to anchor against:
	- Top
	- Right
	- Left
	- Bottom
	- None
	Failure to specify an axis' anchor preference will result in the default of Top or Left
	being assigned as necessary to fulfill the anchor requirements.
	\note Docking and Anchoring are mutually exclusive. Defining new anchors will remove
	any docking preferences. Conversely, selecting dockings will reset anchoring to the
	default (Top/Left).
	*/
	void Control::setAnchor( int anchoredSides ) {
		// ensure one of Left/Right is selected
		if (( anchoredSides & Left ) != Left
				&& ( anchoredSides & Right ) != Right )
			anchoredSides |= Left;

		// ensure one of Top/Bottom is selected
		if (( anchoredSides & Top ) != Top
				&& ( anchoredSides & Bottom ) != Bottom )
			anchoredSides |= Top;

		if ( mAnchors != anchoredSides ) { // we only need to do this if we came up with a new result
			mAnchors = anchoredSides;
			if ( !m_InDockAnchor ) {
				m_InDockAnchor = true;
				setDocking( None );
				invalidate();
				_invalidateLayout();
				m_InDockAnchor = false;
			}
		}
	}
	//############################################################################
	/*! Return value will be a bit mask comprised of values within ControlSides. */
	int Control::getAnchor() {
		return mAnchors;
	}
	//############################################################################
	void Control::_invalidateLayout() {
		if ( !m_InLayout ) {
			ContainerControl* c = dynamic_cast<ContainerControl*>( getContainer() );
			if ( c )
				c->invalidateLayout();
		}
	}
	//############################################################################
	void Control::_breakDocking() {
		if ( !m_InLayout )
			setDocking( None );
	}
	//############################################################################
	/*! The "margin" is the distance to stay away from sibling Controls' margins
	during automatic layouts. It is up to the control performing the layout
	operations to honor this value. 
	\param margin The margin size in Screen units. Negative values are clamped to 0.0f */
	void Control::setMargin( float margin ) {
		if ( margin < 0.0f ) margin = 0.0f;
		if ( margin == mMargin ) return;
		mMargin = margin;
		_invalidateLayout();
	}
	//############################################################################
	/*! \see See setMargin() for information on margins */
	float Control::getMargin() {
		return mMargin;
	}
	//############################################################################
} // namespace OpenGUI {
