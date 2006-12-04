#include "Amethyst_ScrollBar_H.h"

namespace OpenGUI {
	namespace Amethyst {

		class ScrollBar_H_BaseImage_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "Imagery";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ScrollBar_H& b = dynamic_cast<ScrollBar_H&>( objectRef );
					valueOut.setValue( b.getImagery() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ScrollBar_H& b = dynamic_cast<ScrollBar_H&>( objectRef );
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
		gScrollBar_H_BaseImage_ObjectProperty;


		class ScrollBar_H_BaseThumb_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "Thumb Imagery";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ScrollBar_H& b = dynamic_cast<ScrollBar_H&>( objectRef );
					valueOut.setValue( b.getThumbImagery() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ScrollBar_H& b = dynamic_cast<ScrollBar_H&>( objectRef );
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
		gScrollBar_H_ThumbImage_ObjectProperty;

		class ScrollBar_H_ThumbPos_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "ThumbPosition";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ScrollBar_H& b = dynamic_cast<ScrollBar_H&>( objectRef );
					valueOut.setValue( b.getThumbPos() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ScrollBar_H& b = dynamic_cast<ScrollBar_H&>( objectRef );
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
		gScrollBar_H_ThumbPos_ObjectProperty;

		class ScrollBar_H_CanvasSize_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "CanvasSize";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ScrollBar_H& b = dynamic_cast<ScrollBar_H&>( objectRef );
					valueOut.setValue( b.getCanvasSize() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ScrollBar_H& b = dynamic_cast<ScrollBar_H&>( objectRef );
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
		gScrollBar_H_CanvasSize_ObjectProperty;

		class ScrollBar_H_PageSize_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "PageSize";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ScrollBar_H& b = dynamic_cast<ScrollBar_H&>( objectRef );
					valueOut.setValue( b.getPageSize() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ScrollBar_H& b = dynamic_cast<ScrollBar_H&>( objectRef );
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
		gScrollBar_H_PageSize_ObjectProperty;


		class ScrollBar_H_LineSize_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "LineSize";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ScrollBar_H& b = dynamic_cast<ScrollBar_H&>( objectRef );
					valueOut.setValue( b.getLineSize() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ScrollBar_H& b = dynamic_cast<ScrollBar_H&>( objectRef );
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
		gScrollBar_H_LineSize_ObjectProperty;

		class ScrollBar_H_InitialScrollTime_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "InitialScrollTime";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ScrollBar_H& b = dynamic_cast<ScrollBar_H&>( objectRef );
					valueOut.setValue( b.getInitialScrollTime() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ScrollBar_H& b = dynamic_cast<ScrollBar_H&>( objectRef );
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
		gScrollBar_H_InitialScrollTime_ObjectProperty;

		class ScrollBar_H_ScrollRepeatTime_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "ScrollRepeatTime";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ScrollBar_H& b = dynamic_cast<ScrollBar_H&>( objectRef );
					valueOut.setValue( b.getScrollRepeatTime() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ScrollBar_H& b = dynamic_cast<ScrollBar_H&>( objectRef );
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
		gScrollBar_H_ScrollRepeatTime_ObjectProperty;


		class ScrollH_ObjectAccessorList : public ObjectAccessorList {
		public:
			ScrollH_ObjectAccessorList() {
				addAccessor( &gScrollBar_H_BaseImage_ObjectProperty );
				addAccessor( &gScrollBar_H_ThumbImage_ObjectProperty );
				addAccessor( &gScrollBar_H_ThumbPos_ObjectProperty );
				addAccessor( &gScrollBar_H_CanvasSize_ObjectProperty );
				addAccessor( &gScrollBar_H_PageSize_ObjectProperty );
				addAccessor( &gScrollBar_H_LineSize_ObjectProperty );
				addAccessor( &gScrollBar_H_InitialScrollTime_ObjectProperty );
				addAccessor( &gScrollBar_H_ScrollRepeatTime_ObjectProperty );
			}
			~ScrollH_ObjectAccessorList() {}
		}
		gScrollBar_H_ObjectAccessorList;

		//! Called when cursor was pressed and released within this Control
		void ScrollBar_H::onCursor_Click( Object* sender, Cursor_EventArgs& evtArgs ) {
			// check for above/below the thumb
			if(!m_rThumbRect.isInside(evtArgs.Position))
			{
				// click is not on the thumb, so we check for pageup/pagedown click
				if(evtArgs.Position.x < m_rThumbRect.min.x)
				{
					// left of the thumb, page up
					pageUp();
				}
				if(evtArgs.Position.x > m_rThumbRect.max.x)
				{
					// right of the thumb, page down
					pageDown();
				}
			}

			OpenGUI::Control::onCursor_Click( sender, evtArgs );
		}
		//! Called when the cursor enters this Control
		void ScrollBar_H::onCursor_Enter( Object* sender, Cursor_EventArgs& evtArgs ) {
			OpenGUI::Control::onCursor_Enter( sender, evtArgs );
		}
		//! Called when the cursor leaves this Control
		void ScrollBar_H::onCursor_Leave( Object* sender, Cursor_EventArgs& evtArgs ) {
			OpenGUI::Control::onCursor_Leave( sender, evtArgs );
		}

		//! "Cursor_Press" event
		void ScrollBar_H::onCursor_Press( Object* sender, Cursor_EventArgs& evtArgs ) {
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
						if(evtArgs.Position.x < m_rThumbRect.min.x)
						{
							// left of the thumb, page down
							pageDown();
							m_bMousePaging = true;
							// need to set a timer for more paging on held mouse
						}
						if(evtArgs.Position.x > m_rThumbRect.max.x)
						{
							// right of the thumb, page up
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
		void ScrollBar_H::onCursor_Release( Object* sender, Cursor_EventArgs& evtArgs ) {
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

		void ScrollBar_H::onCursor_Move( Object* sender, Cursor_EventArgs& evtArgs )
		{
			// call base class to preserve functionality
			Control::onCursor_Move( sender, evtArgs );

			// now if we are dragging the thumb, we need to check it out
			if(m_bMouseDraggingThumb)
			{
				// gerenate the new "top" location
				float x = evtArgs.Position.x - m_vMosueOffset.x; // x pos is offset by the mouse offest set on mouse down
				x -= getRect().min.x;
				if(x>0)
				{
					//now scale the position based on the width of the control
					mThumbPosValue = x / getRect().getWidth();
				}
				else 
					mThumbPosValue = 0;

				invalidate();
			}

			m_vMousePosition = evtArgs.Position;
		}

		//! "Tick" event
		void ScrollBar_H::onTick( Object* sender, Tick_EventArgs& evtArgs )
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
						if(m_vMousePosition.x < m_rThumbRect.min.x)
						{
							// left of the thumb, page down
							pageDown();
							m_bMousePaging = true;
							// need to set a timer for more paging on held mouse
						}
						if(m_vMousePosition.x > m_rThumbRect.max.x)
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

		ScrollBar_H::ScrollBar_H()
		{
			if(gScrollBar_H_ObjectAccessorList.getParent() == NULL)
				gScrollBar_H_ObjectAccessorList.setParent(Widget::getAccessors());

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

		ScrollBar_H::~ScrollBar_H()
		{
		}

		//! Sets the imagery for the BG.
		void ScrollBar_H::setImagery( std::string imageryName)
		{
			invalidate();
			mBGImage = ImageryManager::getSingleton().getImagery( imageryName );
		}

		//! Gets the imagery of the BG.
		std::string ScrollBar_H::getImagery()
		{
			if(!mBGImage.isNull())
				return mBGImage->getName();
			return "";
		}

		//! Sets the imagery for the thumb.
		void ScrollBar_H::setThumbImagery( std::string imageryName)
		{
			invalidate();
			mThumbImage = ImageryManager::getSingleton().getImagery( imageryName );
		}
		//! Gets the imagery for the thumb.
		std::string ScrollBar_H::getThumbImagery()
		{
			if(mThumbImage)
				return mThumbImage->getName();
			return "";
		}

		Widget* ScrollBar_H::CreateScrollBar_HFactory()
		{
			return new ScrollBar_H();
		}

		void ScrollBar_H::pageUp()
		{
			invalidate();
			mThumbPosValue += (mPageSize / mCanvasSize);
			_positionThumb();
		}
		void ScrollBar_H::pageDown()
		{
			invalidate();
			mThumbPosValue -= (mPageSize / mCanvasSize);
			_positionThumb();
		}
		void ScrollBar_H::lineUp()
		{
			invalidate();
			mThumbPosValue += mLineSize;
			_positionThumb();
		}
		void ScrollBar_H::lineDown()
		{
			invalidate();
			mThumbPosValue -= mLineSize;
			_positionThumb();
		}

		void ScrollBar_H::_positionThumb()
		{
			FRect thumbTrackRect = getRect();
			thumbTrackRect.min += mThumbImageOffsets.min;
			thumbTrackRect.max -= mThumbImageOffsets.max;

			m_rThumbRect = thumbTrackRect;
			FVector2 widgetSize = thumbTrackRect.max - thumbTrackRect.min;
			m_rThumbRect.min.x += (widgetSize.x * mThumbPosValue);

			float thumbWidthFactor = widgetSize.x / mCanvasSize;
			m_rThumbRect.max.x = m_rThumbRect.min.x + (widgetSize.x * thumbWidthFactor);
			// thumb is positioned, not check to see if it is off the end and fix
			float backCheck = m_rThumbRect.max.x - thumbTrackRect.max.x;
			if(backCheck > 0.0f)
			{
				m_rThumbRect.min.x -= backCheck;
				m_rThumbRect.max.x -= backCheck;
			}
		}

		void ScrollBar_H::onDraw( Object* sender, Draw_EventArgs& evtArgs )
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
