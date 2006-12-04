#include "Amethyst_ScrollBar_H.h"

namespace OpenGUI {
	namespace Amethyst {


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
		}

		ScrollBar_H::ScrollBar_H()
		{
			mThumbPosValue = 0.1;
			mCanvasSize = 800.0f;
			mPageSize = 100.0f;
			mLineSize = 12.0f;
			mThumbImageOffsets = FRect(5,5,12,12);

			m_bMouseDraggingThumb = false;
			m_bMousePaging = false;
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
