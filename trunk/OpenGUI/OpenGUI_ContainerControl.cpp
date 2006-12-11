#include "OpenGUI_ContainerControl.h"
#include "OpenGUI_Brush_Caching.h"
#include "OpenGUI_Macros.h"

namespace OpenGUI {

	SimpleProperty_Float( property_Padding, "Padding", ContainerControl, getPadding, setPadding );

	//############################################################################
	class ContainerControl_ObjectAccessorList : public ObjectAccessorList {
	public:
		ContainerControl_ObjectAccessorList() {
			addAccessor( &property_Padding );
		}
		~ContainerControl_ObjectAccessorList() {}
	}
	gContainerControl_ObjectAccessorList;

	//############################################################################
	//############################################################################


	//############################################################################
	ContainerControl::ContainerControl() {
		if ( gContainerControl_ObjectAccessorList.getParent() == 0 )
			gContainerControl_ObjectAccessorList.setParent( Control::getAccessors() );

		// initialize state variables
		Children.setParent( this );
		Children.attachListener( this );
		mCacheBrush = 0;
		m_LayoutSuspended = false; // layouts are instantaneous by default
		m_LayoutValid = true; // layout begins valid (as there are no controls to update, it does not matter)
		m_InUpdateLayout = false; // we are not in updateLayout() quite yet
		m_ClipChildren = false;

		// set up defaults for properties

		//Set up events and default bindings
		getEvents().createEvent( "DrawBG" );
		getEvents()["DrawBG"].add( new EventDelegate( this, &ContainerControl::onDrawBG ) );
		getEvents().createEvent( "ChildAttached" );
		getEvents().createEvent( "ChildDetached" );
		getEvents()["ChildAttached"].add( new EventDelegate( this, &ContainerControl::onChildAttached ) );
		getEvents()["ChildDetached"].add( new EventDelegate( this, &ContainerControl::onChildDetached ) );
		getEvents().createEvent( "InvalidatedChild" );
		getEvents()["InvalidatedChild"].add( new EventDelegate( this, &ContainerControl::onInvalidatedChild ) );

		//additional (unblockable) event bindings
		getEvents()["Detached"].add( new EventDelegate( this, &ContainerControl::onDetached_BrushCache ) );
	}
	//############################################################################
	ContainerControl::~ContainerControl() {
		/**/
		if ( mCacheBrush )
			delete mCacheBrush;
		mCacheBrush = 0;
	}
	//############################################################################
	ObjectAccessorList* ContainerControl::getAccessors() {
		return &gContainerControl_ObjectAccessorList;
	}
	//############################################################################
	char* ContainerControl::getClassName() {
		return "OpenGUI::ContainerControl";
	}
	//############################################################################
	void ContainerControl::eventDrawBG( Brush& brush ) {
		Draw_EventArgs event( brush );
		triggerEvent( "DrawBG", event );
	}
	//############################################################################
	void ContainerControl::onDrawBG( Object* sender, Draw_EventArgs& evtArgs ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void ContainerControl::onChildAttached( Object* sender, Attach_EventArgs& evtArgs ) {
		invalidate(); // need to invalidate caches for hierarchy change
	}
	//############################################################################
	void ContainerControl::onChildDetached( Object* sender, Attach_EventArgs& evtArgs ) {
		invalidate(); // need to invalidate caches for hierarchy change
	}
	//############################################################################
	void ContainerControl::eventChildAttached( WidgetCollection* container, Widget* newChild ) {
		Attach_EventArgs event( container, newChild );
		triggerEvent( "ChildAttached", event );
	}
	//############################################################################
	void ContainerControl::eventChildDetached( WidgetCollection* container, Widget* prevChild ) {
		Attach_EventArgs event( container, prevChild );
		triggerEvent( "ChildDetached", event );
	}
	//############################################################################
	/*! The \c Cursor_Move event is only re-issued to children if the cursor is
	currently inside the container, or if the cursor just left the container.
	This function is cursor focus aware, and will provide the correct information
	to children as necessary
	*/
	void ContainerControl::onCursor_Move( Object* sender, Cursor_EventArgs& evtArgs ) {
		Control::onCursor_Move( sender, evtArgs );

		FVector2 pos = evtArgs.Position;
		if ( hasCursorFocus() ) // translate point if necessary
			pos = pointFromScreen( pos );

		static bool lastInside = false;
		bool reissue = lastInside;
		if ( _isInside( pos ) )
			lastInside = reissue = true;
		else
			lastInside = false;

		if ( reissue ) {
			FVector2 newPos;
			newPos = pos - getPosition();
			newPos.x -= m_ClientAreaOffset_UL.x;
			newPos.y -= m_ClientAreaOffset_UL.y;
			WidgetCollection::reverse_iterator iter, iterend = Children.rend();
			for ( iter = Children.rbegin(); iter != iterend; iter++ ) {
				if ( iter->eventCursor_Move( newPos.x, newPos.y ) )
					evtArgs.eat();
			}
		}
	}
	//############################################################################
	/*! This function is cursor focus aware, and will provide the correct cursor information
	to children as necessary. */
	void ContainerControl::onCursor_Press( Object* sender, Cursor_EventArgs& evtArgs ) {
		Control::onCursor_Press( sender, evtArgs );

		FVector2 pos = evtArgs.Position;
		if ( hasCursorFocus() ) // translate point if necessary
			pos = pointFromScreen( pos );

		if ( _isInside( evtArgs.Position ) ) {
			FVector2 newPos;
			newPos = pos - getPosition();
			newPos.x -= m_ClientAreaOffset_UL.x;
			newPos.y -= m_ClientAreaOffset_UL.y;
			WidgetCollection::reverse_iterator iter, iterend = Children.rend();
			for ( iter = Children.rbegin(); iter != iterend; iter++ ) {
				if ( iter->eventCursor_Press( newPos.x, newPos.y ) )
					evtArgs.eat();
			}
		}
	}
	//############################################################################
	/*! This function is cursor focus aware, and will provide the correct cursor information
	to children as necessary. */
	void ContainerControl::onCursor_Release( Object* sender, Cursor_EventArgs& evtArgs ) {
		Control::onCursor_Release( sender, evtArgs );

		FVector2 pos = evtArgs.Position;
		if ( hasCursorFocus() ) // translate point if necessary
			pos = pointFromScreen( pos );

		if ( _isInside( pos ) ) {
			FVector2 newPos;
			newPos = pos - getPosition();
			newPos.x -= m_ClientAreaOffset_UL.x;
			newPos.y -= m_ClientAreaOffset_UL.y;
			WidgetCollection::reverse_iterator iter, iterend = Children.rend();
			for ( iter = Children.rbegin(); iter != iterend; iter++ ) {
				if ( iter->eventCursor_Release( newPos.x, newPos.y ) )
					evtArgs.eat();
			}
		}
	}
	//############################################################################
	void ContainerControl::_draw( Brush& brush ) {
		if ( getVisible() ) {

			Brush_Caching& cacheBrush = _getCacheBrush();

			// do we need to rebuild the cache brush?
			if ( isCacheDirty() ) {
				cacheBrush.pushPosition( -getPosition() ); //offset to parent coords for Container drawing
				//draw background
				cacheBrush._pushMarker( this );
				eventDrawBG( cacheBrush );
				cacheBrush._popMarker( this );
				cacheBrush.pop(); // pop the parent coords offset

				//draw children
				if ( m_ClipChildren ) // setup the client area clip if we have one
					cacheBrush.pushClippingRect( getClientArea() );
				WidgetCollection::reverse_iterator iter, iterend = Children.rend();
				for ( iter = Children.rbegin(); iter != iterend; iter++ ) {
					iter->_draw( cacheBrush );
				}
				if ( m_ClipChildren ) // pop the client area clip if we had one
					cacheBrush.pop();

				cacheBrush.pushPosition( -getPosition() ); //offset to parent coords for Container drawing
				//draw foreground
				cacheBrush._pushMarker( this );
				eventDraw( cacheBrush );
				cacheBrush._popMarker( this );
				cacheBrush.pop(); // pop the parent coords offset
			}

			//push cache into output stream
			brush.pushAlpha( getAlpha() );
			brush.pushPosition( getPosition() );
			cacheBrush.emerge( brush );
			brush.pop(); // pop position offset
			brush.pop(); // pop alpha
		}
	}
	//############################################################################
	/*! If layout is not suspended, this triggers an immediate update of the layout.
	This function is protected from re-entry when a layout operation is currently
	under way. */
	void ContainerControl::invalidateLayout() {
		if ( !m_InUpdateLayout ) {
			m_LayoutValid = false;
			if ( !m_LayoutSuspended )
				updateLayout();
		}
	}
	//############################################################################
	void ContainerControl::suspendLayout() {
		m_LayoutSuspended = true;
	}
	//############################################################################
	void ContainerControl::resumeLayout() {
		m_LayoutSuspended = false;
		if ( !layoutValid() )
			updateLayout();
	}
	//############################################################################
	bool ContainerControl::layoutValid() {
		return m_LayoutValid;
	}
	//############################################################################
	/*! This is a convenience function that calculates the client area into a rect
	from the defined offsets \c m_ClientAreaOffset_UL and \c m_ClientAreaOffset_LR.
	*/
	const FRect& ContainerControl::getClientArea() {
		static FRect retval;
		FVector2 size = getSize();
		retval.min.x = m_ClientAreaOffset_UL.x;
		retval.min.y = m_ClientAreaOffset_UL.y;
		retval.max.x = size.x + m_ClientAreaOffset_LR.x;
		retval.max.y = size.y + m_ClientAreaOffset_LR.y;
		return retval;
	}
	//############################################################################
	/*! The update is performed regardless of layout being currently suspended,
	so only call this if you really want the update to occur. Layout validity,
	however, is still honored and layouts will not occur unless needed. */
	void ContainerControl::updateLayout() {
		m_InUpdateLayout = true;
		if ( !layoutValid() ) {
			_setChildControlLayoutState( true );
			_doUpdateLayout();
			m_LayoutValid = true;
			_setChildControlLayoutState( false );
		}
		m_InUpdateLayout = false;
	}
	//############################################################################
	void ContainerControl::_setChildControlLayoutState( bool state ) {
		WidgetCollection::iterator iter, iterend = Children.end();
		for ( iter = Children.begin(); iter != iterend; iter++ ) {
			Control* c = dynamic_cast<Control*>( iter.get() );
			if ( c )
				c->m_InLayout = state;
		}
	}
	//############################################################################
	/*! This is virtual in the case that a subclass wishes to perform their own layout logic.
	Toolbars and other specialty containers would likely need this functionality. */
	void ContainerControl::_doUpdateLayout() {
		static FRect oldClntArea = getClientArea();
		FRect clntArea = getClientArea();

		//update clntArea to respect Padding
		clntArea.setWidth( clntArea.getWidth() - ( mPadding * 2.0f ) );
		clntArea.setHeight( clntArea.getHeight() - ( mPadding * 2.0f ) );
		if ( clntArea.getHeight() < 0.0f ) clntArea.setHeight( 0.0f );
		if ( clntArea.getWidth() < 0.0f ) clntArea.setWidth( 0.0f );
		clntArea.offset( FVector2( mPadding, mPadding ) );

		//update all docked controls
		WidgetCollection::iterator iter, iterend = Children.end();
		for ( iter = Children.begin(); iter != iterend; iter++ ) {
			Control* ctrl = dynamic_cast<Control*>( iter.get() );
			if ( ctrl ) {
				int dock = ctrl->getDocking();
				float margin = ctrl->getMargin();
				if ( dock ) {

					//Next two IF's cover position and height for 'Fill' as well
					if (( dock & Control::Left ) || ( dock & Control::Right ) ) {
						ctrl->setTop( clntArea.getPosition().y + margin );
						ctrl->setHeight( clntArea.getHeight() - ( margin*2.0f ) );
					}
					if (( dock & Control::Top ) || ( dock & Control::Bottom ) ) {
						ctrl->setLeft( clntArea.getPosition().x  + margin );
						ctrl->setWidth( clntArea.getWidth() - ( margin*2.0f ) );
					}

					if ( dock == Control::Left ) {
						ctrl->setLeft( clntArea.getPosition().x + margin );
						float newwidth = clntArea.getWidth() - ( ctrl->getWidth() + ( margin * 2.0f ) );
						clntArea.setWidth( newwidth > 0.0f ? newwidth : 0.0f ); // width can't be less than 0.0f
						clntArea.offset( FVector2( ctrl->getWidth() + ( margin*2.0f ), 0.0f ) );
					}
					if ( dock == Control::Right ) {
						float newpos = clntArea.getPosition().x + clntArea.getWidth();
						newpos = newpos - ( ctrl->getWidth() + margin );
						ctrl->setLeft( newpos );
						float newwidth = newpos - margin;
						newwidth = newwidth - clntArea.getPosition().x;
						clntArea.setWidth( newwidth > 0.0f ? newwidth : 0.0f ); // width can't be less than 0.0f
					}

					if ( dock == Control::Top ) {
						ctrl->setTop( clntArea.getPosition().y + margin );
						float newheight = clntArea.getHeight() - ( ctrl->getHeight() + ( margin * 2.0f ) );
						clntArea.setHeight( newheight > 0.0f ? newheight : 0.0f ); // height can't be less than 0.0f
						clntArea.offset( FVector2( 0.0f, ctrl->getHeight() + ( margin*2.0f ) ) );
					}
					if ( dock == Control::Bottom ) {
						float newtop = clntArea.getPosition().y + clntArea.getHeight();
						newtop = newtop - ( ctrl->getHeight() + margin );
						ctrl->setTop( newtop );
						float newheight = clntArea.getHeight() - ( ctrl->getHeight() + margin * 2.0f );
						clntArea.setHeight( newheight > 0.0f ? newheight : 0.0f ); // height can't be less than 0.0f
					}
				}
			}
		}

		//use difference of new and previous client area space to update anchored controls
		float deltaLeft = clntArea.getPosition().x - oldClntArea.getPosition().x;
		float deltaTop = clntArea.getPosition().y - oldClntArea.getPosition().y ;
		float deltaRight = ( clntArea.getPosition().x + clntArea.getWidth() ) - ( oldClntArea.getPosition().x + oldClntArea.getWidth() ) ;
		float deltaBottom = ( clntArea.getPosition().y + clntArea.getHeight() ) - ( oldClntArea.getPosition().y + oldClntArea.getHeight() ) ;

		//WidgetCollection::iterator iter, iterend = Children.end(); // done earlier
		for ( iter = Children.begin(); iter != iterend; iter++ ) {
			Control* ctrl = dynamic_cast<Control*>( iter.get() );
			if ( ctrl ) {
				int dock = ctrl->getDocking();
				if ( dock == Control::None ) {
					int anchor = ctrl->getAnchor();
					if ( anchor & Control::Left ) {
						ctrl->setLeft( ctrl->getLeft() + deltaLeft );
						if ( anchor & Control::Right )
							ctrl->setWidth(( ctrl->getWidth() - deltaLeft ) + deltaRight );
					}
					if (( anchor & Control::Left ) == 0 && ( anchor & Control::Right ) ) {
						ctrl->setLeft( ctrl->getLeft() + deltaRight );
					}

					if ( anchor & Control::Top ) {
						ctrl->setTop( ctrl->getTop() + deltaTop );
						if ( anchor & Control::Bottom )
							ctrl->setHeight(( ctrl->getHeight() - deltaTop ) + deltaBottom );
					}
					if (( anchor & Control::Top ) == 0 && ( anchor & Control::Bottom ) ) {
						ctrl->setTop( ctrl->getTop() + deltaBottom );
					}
				}
			}
		}
		oldClntArea = getClientArea(); // update oldClntArea for next pass
	}
	//############################################################################
	void ContainerControl::_getChildrenAt( const FVector2& position, WidgetPtrList& outList, bool recursive ) {
		FVector2 pos = position;
		_translatePointIn( pos );

		WidgetCollection::iterator iter, iterend = Children.end();
		for ( iter = Children.begin(); iter != iterend; iter++ ) {
			Widget* child = iter.get();
			if ( child->_isInside( pos ) ) {
				if ( recursive ) {
					child->getChildrenAt( pos, outList, true );
				}
				outList.push_back( child );
			}
		}
	}
	//############################################################################
	Widget* ContainerControl::_getChildAt( const FVector2& position, bool recursive ) {
		FVector2 pos = position;
		_translatePointIn( pos );

		WidgetCollection::iterator iter, iterend = Children.end();
		for ( iter = Children.begin(); iter != iterend; iter++ ) {
			Widget* child = iter.get();
			if ( child->_isInside( pos ) ) {
				Widget* ret = child;
				if ( recursive ) {
					child = child->getChildAt( pos, true );
					if ( child )
						ret = child;
				}
				return ret;
			}
		}
		return 0;
	}
	//############################################################################
	void ContainerControl::_invalidatedChild() {
		eventInvalidatedChild();
	}
	//############################################################################
	void ContainerControl::dirtyCache() {
		if ( mCacheBrush ) {
			delete mCacheBrush;
			mCacheBrush = 0;
		}
	}
	//############################################################################
	bool ContainerControl::isCacheDirty() const {
		if ( !mCacheBrush )
			return true;
		return !mCacheBrush->hasContent();
	}
	//############################################################################
	Brush_Caching& ContainerControl::_getCacheBrush() {
		if ( !mCacheBrush ) {
			mCacheBrush = new Brush_Caching( getScreen(), getSize() );
		}
		return *mCacheBrush;
	}
	//############################################################################
	void ContainerControl::_tick( float seconds ) {
		Control::_tick( seconds );
		WidgetCollection::iterator iter, iterend = Children.end();
		for ( iter = Children.begin(); iter != iterend; iter++ ) {
			Widget* child = iter.get();
			child->_tick( seconds );
		}
	}
	//############################################################################
	void ContainerControl::eventInvalidatedChild() {
		EventArgs event;
		triggerEvent( "InvalidatedChild", event );
	}
	//############################################################################
	void ContainerControl::onInvalidated( Object* sender, EventArgs& evtArgs ) {
		dirtyCache();
		Control::onInvalidated( sender, evtArgs );
	}
	//############################################################################
	void ContainerControl::onInvalidatedChild( Object* sender, EventArgs& evtArgs ) {
		invalidate();
	}
	//############################################################################
	void ContainerControl::onDetached_BrushCache( Object* sender, Attach_EventArgs& evtArgs ) {
		dirtyCache();
	}
	//############################################################################
	void ContainerControl::onResized( Object* sender, Resized_EventArgs& evtArgs ) {
		invalidate();
		Control::onResized( sender, evtArgs );
	}
	//############################################################################
	Widget* ContainerControl::_getChildByName( const std::string& childName ) const {
		return Children.getWidget( childName );
	}
	//############################################################################
	void ContainerControl::_translatePointIn( FVector2& point ) {
		const FVector2& pos = getPosition();
		point -= pos;
		point -= m_ClientAreaOffset_UL;
	}
	//############################################################################
	void ContainerControl::_translatePointOut( FVector2& point ) {
		const FVector2& pos = getPosition();
		point += m_ClientAreaOffset_UL;
		point += pos;
	}
	//############################################################################
	/*! Padding is the distance within the inside of this container to keep children away from the client area edges during auto layout.

		The given \c padding cannot be negative, and is clamped to 0.0f if a negative value is given.
	*/
	void ContainerControl::setPadding( float padding ) {
		if ( padding < 0.0f ) padding = 0.0f;
		if ( mPadding == padding ) return;
		mPadding = padding;
		invalidateLayout();
	}
	//############################################################################
	/*! \see setPadding() for description of Padding */
	float ContainerControl::getPadding() {
		return mPadding;
	}
	//############################################################################
	void ContainerControl::_doflush(){
		eventInvalidated();
		WidgetCollection::iterator iter, iterend = Children.end();
		for ( iter = Children.begin(); iter != iterend; iter++ ) {
			Widget* child = iter.get();
			child->_doflush();
		}
	}
	//############################################################################
} // namespace OpenGUI {
