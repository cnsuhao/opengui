#include "Amethyst_ScrollBar_H.h"

namespace OpenGUI {
	namespace Amethyst {


		ScrollBar_H::ScrollBar_H()
		{
			mThumbPosValue = 0;
			mPageSize = 600.0f;
			mLineSize = 12.0f;
			mThumbImageOffsets = FRect(5,5,5,5);
		}

		ScrollBar_H::~ScrollBar_H()
		{
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
			mThumbPosValue += mPageSize;
		}
		void ScrollBar_H::pageDown()
		{
			invalidate();
			mThumbPosValue -= mPageSize;
		}
		void ScrollBar_H::lineUp()
		{
			invalidate();
			mThumbPosValue += mLineSize;
		}
		void ScrollBar_H::lineDown()
		{
			invalidate();
			mThumbPosValue -= mLineSize;
		}

		void ScrollBar_H::onDraw( Object* sender, Draw_EventArgs& evtArgs )
		{
			Frame::onDraw(sender, evtArgs);

			// now position and draw out stuff

			if ( !mThumbImage.isNull() ) {
				Brush& b = evtArgs.brush;
				FRect thumbTrackRect = getRect();
				thumbTrackRect.min += mThumbImageOffsets.min;
				thumbTrackRect.max -= mThumbImageOffsets.max;

				FRect thumbPos = thumbTrackRect;
				FVector2 widgetSize = thumbTrackRect.max - thumbTrackRect.min;
				thumbPos.min.x += (widgetSize.x * mThumbPosValue);

				float thumbWidthFactor = widgetSize.x / mPageSize;
				thumbPos.max.x = thumbPos.min.x + (widgetSize.x * thumbWidthFactor);
				// thumb is positioned, not check to see if it is off the end and fix
				float backCheck = thumbPos.max.x - thumbTrackRect.max.x;
				if(backCheck > 0.0f)
				{
					thumbPos.min.x -= backCheck;
					thumbPos.max.x -= backCheck;
				}

				b.Image.drawImage( mThumbImage, thumbPos );
			}
		}

	} // namespace Amethyst{
} // namespace OpenGUI{
