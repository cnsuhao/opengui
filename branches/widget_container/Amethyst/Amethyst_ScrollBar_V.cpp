#include "Amethyst_ScrollBar_V.h"

namespace OpenGUI {
	namespace Amethyst {

		class ScrollBar_V_BaseImage_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "Imagery";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ScrollBar_V& b = dynamic_cast<ScrollBar_V&>( objectRef );
					valueOut.setValue( b.getImagery() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ScrollBar_V& b = dynamic_cast<ScrollBar_V&>( objectRef );
					b.setImagery( valueIn.getValueAsString() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_STRING;
			}
		}
		gScrollBar_V_BaseImage_ObjectProperty;


		class ScrollBar_V_BaseThumb_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "Thumb Imagery";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ScrollBar_V& b = dynamic_cast<ScrollBar_V&>( objectRef );
					valueOut.setValue( b.getThumbImagery() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ScrollBar_V& b = dynamic_cast<ScrollBar_V&>( objectRef );
					b.setThumbImagery( valueIn.getValueAsString() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_STRING;
			}
		}
		gScrollBar_V_ThumbImage_ObjectProperty;

		class ScrollBar_V_ThumbPos_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "ThumbPosition";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ScrollBar_V& b = dynamic_cast<ScrollBar_V&>( objectRef );
					valueOut.setValue( b.getThumbPos() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ScrollBar_V& b = dynamic_cast<ScrollBar_V&>( objectRef );
					b.setThumbPos( valueIn.getValueAsFloat() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_FLOAT;
			}
		}
		gScrollBar_V_ThumbPos_ObjectProperty;

		class ScrollBar_V_CanvasSize_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "CanvasSize";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ScrollBar_V& b = dynamic_cast<ScrollBar_V&>( objectRef );
					valueOut.setValue( b.getCanvasSize() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ScrollBar_V& b = dynamic_cast<ScrollBar_V&>( objectRef );
					b.setCanvasSize( valueIn.getValueAsFloat() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_FLOAT;
			}
		}
		gScrollBar_V_CanvasSize_ObjectProperty;

		class ScrollBar_V_PageSize_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "PageSize";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ScrollBar_V& b = dynamic_cast<ScrollBar_V&>( objectRef );
					valueOut.setValue( b.getPageSize() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ScrollBar_V& b = dynamic_cast<ScrollBar_V&>( objectRef );
					b.setPageSize( valueIn.getValueAsFloat() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_FLOAT;
			}
		}
		gScrollBar_V_PageSize_ObjectProperty;


		class ScrollBar_V_LineSize_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "LineSize";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ScrollBar_V& b = dynamic_cast<ScrollBar_V&>( objectRef );
					valueOut.setValue( b.getLineSize() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ScrollBar_V& b = dynamic_cast<ScrollBar_V&>( objectRef );
					b.setLineSize( valueIn.getValueAsFloat() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_FLOAT;
			}
		}
		gScrollBar_V_LineSize_ObjectProperty;

		class ScrollBar_V_InitialScrollTime_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "InitialScrollTime";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ScrollBar_V& b = dynamic_cast<ScrollBar_V&>( objectRef );
					valueOut.setValue( b.getInitialScrollTime() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ScrollBar_V& b = dynamic_cast<ScrollBar_V&>( objectRef );
					b.setInitialScrollTime( valueIn.getValueAsFloat() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_FLOAT;
			}
		}
		gScrollBar_V_InitialScrollTime_ObjectProperty;

		class ScrollBar_V_ScrollRepeatTime_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "ScrollRepeatTime";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ScrollBar_V& b = dynamic_cast<ScrollBar_V&>( objectRef );
					valueOut.setValue( b.getScrollRepeatTime() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ScrollBar_V& b = dynamic_cast<ScrollBar_V&>( objectRef );
					b.setScrollRepeatTime( valueIn.getValueAsFloat() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_FLOAT;
			}
		}
		gScrollBar_V_ScrollRepeatTime_ObjectProperty;


		class ScrollH_ObjectAccessorList : public ObjectAccessorList {
		public:
			ScrollH_ObjectAccessorList() {
				addAccessor( &gScrollBar_V_BaseImage_ObjectProperty );
				addAccessor( &gScrollBar_V_ThumbImage_ObjectProperty );
				addAccessor( &gScrollBar_V_ThumbPos_ObjectProperty );
				addAccessor( &gScrollBar_V_CanvasSize_ObjectProperty );
				addAccessor( &gScrollBar_V_PageSize_ObjectProperty );
				addAccessor( &gScrollBar_V_LineSize_ObjectProperty );
				addAccessor( &gScrollBar_V_InitialScrollTime_ObjectProperty );
				addAccessor( &gScrollBar_V_ScrollRepeatTime_ObjectProperty );
			}
			~ScrollH_ObjectAccessorList() {}
		}
		gScrollBar_V_ObjectAccessorList;

		//! Called when cursor was pressed and released within this Control
		void ScrollBar_V::onCursor_Click( Object* sender, Cursor_EventArgs& evtArgs ) {
			// check for above/below the thumb
			if(!m_rThumbRect.isInside(evtArgs.Position))
			{
				// click is not on the thumb, so we check for pageup/pagedown click
				if(evtArgs.Position.y < m_rThumbRect.min.y)
				{
					// left of the thumb, page up
					pageUp();
				}
				if(evtArgs.Position.y > m_rThumbRect.max.y)
				{
					// right of the thumb, page down
					pageDown();
				}
			}

			OpenGUI::Control::onCursor_Click( sender, evtArgs );
		}
		//! Called when the cursor enters this Control
		void ScrollBar_V::onCursor_Enter( Object* sender, Cursor_EventArgs& evtArgs ) {
			OpenGUI::Control::onCursor_Enter( sender, evtArgs );
		}
		//! Called when the cursor leaves this Control
		void ScrollBar_V::onCursor_Leave( Object* sender, Cursor_EventArgs& evtArgs ) {
			OpenGUI::Control::onCursor_Leave( sender, evtArgs );
		}

		//! "Cursor_Press" event
		void ScrollBar_V::onCursor_Press( Object* sender, Cursor_EventArgs& evtArgs ) {
			if ( _isInside( evtArgs.Position ) ){
				// its inside the control's space. check what is effected.

				// is it on the thumb?
				if(m_rThumbRect.isInside(evtArgs.Position))
				{
					//set offset and flag
					m_vMosueOffset = evtArgs.Position - m_rThumbRect.min; 
					m_bMouseDraggingThumb = true;
					invalidate();
					grabCursorFocus();
				}
				else
				{
					// check for above/below the thumb
					if(!m_rThumbRect.isInside(evtArgs.Position))
					{
						// click is not on the thumb, so we check for pageup/pagedown click
						if(evtArgs.Position.y < m_rThumbRect.min.y)
						{
							// below the thumb, page down
							pageDown();
							m_bMousePaging = true;
							// need to set a timer for more paging on held mouse
						}
						if(evtArgs.Position.y > m_rThumbRect.max.y)
						{
							// above the thumb, page up
							pageUp();
							m_bMousePaging = true;
							// need to set a timer for more paging on held mouse
						}
						m_fCountdownTime = m_fInitialScrollTime;
						m_vMousePosition = evtArgs.Position;
					}
				}
			}

			Widget::onCursor_Press(sender, evtArgs);
		}
		//! "Cursor_Release" event
		void ScrollBar_V::onCursor_Release( Object* sender, Cursor_EventArgs& evtArgs ) {
			//get the local coord of the release
			FVector2 translatedPoint = pointFromScreen(evtArgs.Position);
			if ( m_bMouseDraggingThumb ) {
				invalidate();
			}
			releaseCursorFocus();
			m_bMouseDraggingThumb = false;
			m_bMousePaging = false;

			Widget::onCursor_Release(sender, evtArgs);
		}

		void ScrollBar_V::onCursor_Move( Object* sender, Cursor_EventArgs& evtArgs )
		{
			// call base class to preserve functionality
			Control::onCursor_Move( sender, evtArgs );

			// now if we are dragging the thumb, we need to check it out
			if(m_bMouseDraggingThumb)
			{
				// gerenate the new "top" location
				float x = evtArgs.Position.y - m_vMosueOffset.y; // y pos is offset by the mouse offest set on mouse down
				x -= getRect().min.y;
				if(x>0)
				{
					//now scale the position based on the width of the control
					mThumbPosValue = x / getRect().getHeight();
				}
				else 
					mThumbPosValue = 0;

				invalidate();
			}

			m_vMousePosition = evtArgs.Position;
		}

		//! "Tick" event
		void ScrollBar_V::onTick( Object* sender, Tick_EventArgs& evtArgs )
		{
			if(m_bMousePaging)
			{
				// advance and check timer
				m_fCountdownTime -= evtArgs.Seconds;
				if(m_fCountdownTime <= 0.0f)
				{
					m_fCountdownTime = m_fScrollRepeatTime;
					// check if we should move again, only if still not in thumb
					if ( _isInside( m_vMousePosition ) && !m_rThumbRect.isInside(m_vMousePosition))
					{
						// mouse is not on the thumb, so we check for pageup/pagedown click
						if(m_vMousePosition.y < m_rThumbRect.min.y)
						{
							// left of the thumb, page down
							pageDown();
							m_bMousePaging = true;
							// need to set a timer for more paging on held mouse
						}
						if(m_vMousePosition.y > m_rThumbRect.max.y)
						{
							// right of the thumb, page up
							pageUp();
							m_bMousePaging = true;
							// need to set a timer for more paging on held mouse
						}
					}
				}
			}
			Widget::onTick( sender, evtArgs );
		}

		ScrollBar_V::ScrollBar_V()
		{
			if(gScrollBar_V_ObjectAccessorList.getParent() == NULL)
				gScrollBar_V_ObjectAccessorList.setParent(Widget::getAccessors());

			mThumbPosValue = 0.1;
			mCanvasSize = 800.0f;
			mPageSize = 100.0f;
			mLineSize = 12.0f;
			mThumbImageOffsets = FRect(5,5,12,12);

			m_bMouseDraggingThumb = false;
			m_bMousePaging = false;
			m_fCountdownTime = 0;
			m_fInitialScrollTime = 0.5f;
			m_fScrollRepeatTime = 0.2f;
		}

		ScrollBar_V::~ScrollBar_V()
		{
		}

		//! Sets the imagery for the BG.
		void ScrollBar_V::setImagery( std::string imageryName)
		{
			invalidate();
			mBGImage = ImageryManager::getSingleton().getImagery( imageryName );
		}

		//! Gets the imagery of the BG.
		std::string ScrollBar_V::getImagery()
		{
			if(!mBGImage.isNull())
				return mBGImage->getName();
			return "";
		}

		//! Sets the imagery for the thumb.
		void ScrollBar_V::setThumbImagery( std::string imageryName)
		{
			invalidate();
			mThumbImage = ImageryManager::getSingleton().getImagery( imageryName );
		}
		//! Gets the imagery for the thumb.
		std::string ScrollBar_V::getThumbImagery()
		{
			if(mThumbImage)
				return mThumbImage->getName();
			return "";
		}

		Widget* ScrollBar_V::CreateScrollBar_VFactory()
		{
			return new ScrollBar_V();
		}

		void ScrollBar_V::pageUp()
		{
			invalidate();
			mThumbPosValue += (mPageSize / mCanvasSize);
			_positionThumb();
		}
		void ScrollBar_V::pageDown()
		{
			invalidate();
			mThumbPosValue -= (mPageSize / mCanvasSize);
			_positionThumb();
		}
		void ScrollBar_V::lineUp()
		{
			invalidate();
			mThumbPosValue += mLineSize;
			_positionThumb();
		}
		void ScrollBar_V::lineDown()
		{
			invalidate();
			mThumbPosValue -= mLineSize;
			_positionThumb();
		}

		void ScrollBar_V::_positionThumb()
		{
			FRect thumbTrackRect = getRect();
			thumbTrackRect.min += mThumbImageOffsets.min;
			thumbTrackRect.max -= mThumbImageOffsets.max;

			m_rThumbRect = thumbTrackRect;
			FVector2 widgetSize = thumbTrackRect.max - thumbTrackRect.min;
			m_rThumbRect.min.y += (widgetSize.y * mThumbPosValue);

			float thumbWidthFactor = widgetSize.y / mCanvasSize;
			m_rThumbRect.max.y = m_rThumbRect.min.y + (widgetSize.y * thumbWidthFactor);
			// thumb is positioned, not check to see if it is off the end and fix
			float backCheck = m_rThumbRect.max.y - thumbTrackRect.max.y;
			if(backCheck > 0.0f)
			{
				m_rThumbRect.min.y -= backCheck;
				m_rThumbRect.max.y -= backCheck;
			}
		}

		void ScrollBar_V::onDraw( Object* sender, Draw_EventArgs& evtArgs )
		{
			// now position and draw out stuff
			_positionThumb();

			if ( !mBGImage.isNull() ) {
				evtArgs.brush.Image.drawImage( mBGImage, getRect() );
			}
			if ( !mThumbImage.isNull() ) {
				evtArgs.brush.Image.drawImage( mThumbImage, m_rThumbRect );
			}
		}

	} // namespace Amethyst{
} // namespace OpenGUI{
