#include "Amethyst_Panel.h"

namespace OpenGUI {
	namespace Amethyst {

		class Panel_HSCROLL_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "Horiz Scroll";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					Panel & l = dynamic_cast<Panel&>( objectRef );
					FVector2 h = l.GetHPct();
					valueOut.setValue( h );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					Panel& l = dynamic_cast<Panel&>( objectRef );
					FVector2 v = l.GetVPct();
					FVector2 h = valueIn.getValueAsFVector2();
					l.SetViewPosition( FVector2(h.x, v.x) );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_FVECTOR2;
			}
		}
		gPanel_HSCROLL_ObjectProperty;

		class Panel_VSCROLL_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "Vert Scroll";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					Panel & l = dynamic_cast<Panel&>( objectRef );
					FVector2 v = l.GetVPct();
					valueOut.setValue( v );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					Panel& l = dynamic_cast<Panel&>( objectRef );
					FVector2 h = l.GetVPct();
					FVector2 v = valueIn.getValueAsFVector2();
					l.SetViewPosition( FVector2(h.x, v.x) );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_FVECTOR2;
			}
		}
		gPanel_VSCROLL_ObjectProperty;

		class Panel_ObjectAccessorList : public ObjectAccessorList {
		public:
			Panel_ObjectAccessorList() {
				addAccessor( &gPanel_HSCROLL_ObjectProperty );
				addAccessor( &gPanel_VSCROLL_ObjectProperty );
			}
			~Panel_ObjectAccessorList() {}
		}
		gPanel_ObjectAccessorList;

		Panel::Panel()
		{
			if(gPanel_ObjectAccessorList.getParent() == NULL)
				gPanel_ObjectAccessorList.setParent(Widget::getAccessors());

			mScrollingOffset = FVector2(0,0);
			mCanvasSize = FVector2(0,0);
		}

		Panel::~Panel()
		{
		}


		Widget* Panel::CreatePanelFactory()
		{
			return new Panel;
		}

		void Panel::onDraw( Object* sender, Draw_EventArgs& evtArgs )
		{
			Control::onDraw( sender, evtArgs );
		}

		void Panel::Scroll(const FVector2 &s) 
		{
			// No "+=" for FVector2???
			mScrollingOffset = mScrollingOffset + s;

			FVector2 size = getSize();

			if(-mScrollingOffset.x > size.x)
				mScrollingOffset.x = -size.x;
			if(-mScrollingOffset.y > size.y)
				mScrollingOffset.y = -size.y;

			// going to need a redraw
			dirtyCache();


			// going to need a redraw
			dirtyCache();
		}


		//############################################################################
		void Panel::_draw( Brush& brush ) {
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

					// now scroll the panel contents
					cacheBrush.pushPosition(mScrollingOffset);

					//draw children
					if ( m_ClipChildren ) // setup the client area clip if we have one
						cacheBrush.pushClippingRect( getClientArea() );
					for ( WidgetCollection::reverse_iterator iter = Children.rbegin();
						iter != Children.rend(); iter++ ) {
							iter->_draw( cacheBrush );
					}
					if ( m_ClipChildren ) // pop the client area clip if we had one
						cacheBrush.pop();

					// remove the scroll coords
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
		
		// Generates the canvas size. Mainly for the attach/detach child function
		void Panel::_genCanvasSize()
		{
			// walk the children and get the minmax rectangle
			FVector2 minPos = FVector2(0,0);
			FVector2 maxPos = FVector2(0,0);

			for ( WidgetCollection::reverse_iterator iter = Children.rbegin(); iter != Children.rend(); iter++ ) {
				Control *pControl = dynamic_cast<Control*>( iter.get() );

				FVector2 s = pControl->getSize();
				FVector2 p = pControl->getPosition();

				// assumes no neg sized members and canvas min is always at least zero
				if(p.x < minPos.x)
					minPos.x = p.x;
				if(p.y < minPos.y)
					minPos.y = p.y;

				if((s.x + p.x) > maxPos.x)
					maxPos.x = s.x+p.x;
				if((s.y + p.y) > maxPos.y)
					maxPos.y = s.y+p.y;
			}
			mCanvasSize = maxPos - minPos;
		}
		
		void Panel::onChildAttached( Object* sender, Attach_EventArgs& evtArgs )
		{
			_genCanvasSize();
			ContainerControl::onChildAttached(sender, evtArgs);
		}
		
		void Panel::onChildDetached( Object* sender, Attach_EventArgs& evtArgs )
		{
			_genCanvasSize();
			ContainerControl::onChildDetached(sender, evtArgs);
		}

		FVector2 Panel::GetHPct(void)
		{
			FVector2 ret = FVector2(0,1);
			FVector2 size = getSize();

			// test for canvas completely visible
			if(mCanvasSize.x > size.x)
			{
				// if we are scrolled down from the top, the scroll offset will be less than zero
				if(mScrollingOffset.x < 0.0f)
				{
					ret.x = (-mScrollingOffset.x) / mCanvasSize.x;
				}

				float bottomOfVisible = (-mScrollingOffset.x) + size.x;

				ret.y = bottomOfVisible / mCanvasSize.x;
			}

			return ret;
		}

		FVector2 Panel::GetVPct(void)
		{
			FVector2 ret = FVector2(0,1);
			FVector2 size = getSize();

			// test for canvas completely visible
			if(mCanvasSize.y > size.y)
			{
				// if we are scrolled down from the top, the scroll offset will be less than zero
				if(mScrollingOffset.y < 0.0f)
				{
					ret.x = (-mScrollingOffset.y) / mCanvasSize.y;
				}

				float bottomOfVisible = (-mScrollingOffset.y) + size.y;

				ret.y = bottomOfVisible / mCanvasSize.y;
			}

			return ret;
		}

		void Panel::SetViewPosition(const FVector2 &hv)
		{
			FVector2 size = getSize();

			mScrollingOffset.x = -(mCanvasSize.x * hv.x);
			if(-mScrollingOffset.x > size.x)
				mScrollingOffset.x = -size.x;
			mScrollingOffset.y = -(mCanvasSize.y * hv.y);
			if(-mScrollingOffset.y > size.y)
				mScrollingOffset.y = -size.y;

			// going to need a redraw
			dirtyCache();

		}

	} // namespace Amethyst

}  //namespace OpenGUI
