#include "Amethyst_Frame.h"

namespace OpenGUI {
	namespace Amethyst {

		Frame::Frame()
		{
			mBGRect = getRect();
		}

		Frame::~Frame()
		{
		}


		Widget* Frame::CreateFrameFactory()
		{
			return new Frame();
		}

		//! Sets the various frame imagery.
		void Frame::setImagery( std::string imageryName, eFrameImageIndex indx)
		{
			invalidate();
			mFramePieces[indx] = ImageryManager::getSingleton().getImagery( imageryName );

			if ( indx == UL && !mFramePieces[UL].isNull() ) {
				mBGRect.min.x = getRect().min.x + mFramePieces[UL]->getImagesetRect().getWidth();
				mBGRect.min.y = getRect().min.y + mFramePieces[UL]->getImagesetRect().getHeight();
			}

			if ( indx == LR && !mFramePieces[LR].isNull() ) {
				mBGRect.max.x = getRect().max.x - mFramePieces[LR]->getImagesetRect().getWidth();
				mBGRect.max.y = getRect().max.y - mFramePieces[LR]->getImagesetRect().getHeight();
			}
		}

		//! Gets the various frame imagery.
		std::string Frame::getImagery(eFrameImageIndex indx)
		{
			if(mFramePieces[indx].isNull())
				return "";

			return mFramePieces[indx]->getName();
		}

		void Frame::onDraw( Object* sender, Draw_EventArgs& evtArgs )
		{
			ContainerControl::onDraw(sender, evtArgs);

			Brush& b = evtArgs.brush;

			mBGRect = FRect(0,0,0,0);

			// first do the corners and build the rect
			if ( !mFramePieces[UL].isNull() ) {
				mBGRect.min.x = getRect().min.x + mFramePieces[UL]->getImagesetRect().getWidth();
				mBGRect.min.y = getRect().min.y + mFramePieces[UL]->getImagesetRect().getHeight();
				b.Image.drawImageUnscaled(mFramePieces[UL], getRect().min);
			}

			if ( !mFramePieces[LR].isNull() ) {
				mBGRect.max.x = getRect().max.x - mFramePieces[LR]->getImagesetRect().getWidth();
				mBGRect.max.y = getRect().max.y - mFramePieces[LR]->getImagesetRect().getHeight();
				b.Image.drawImageUnscaled(mFramePieces[LR], mBGRect.max);
			}

			if ( !mFramePieces[UR].isNull() ) {
				b.Image.drawImageUnscaled(mFramePieces[UR], FVector2(mBGRect.max.x, getRect().min.y));
			}

			if ( !mFramePieces[LL].isNull() ) {
				b.Image.drawImageUnscaled(mFramePieces[LL], FVector2(getRect().min.x, mBGRect.max.y));
			}

			if ( !mFramePieces[UM].isNull() ) {
				b.Image.drawImageUnscaledAndTiled( mFramePieces[UM], FRect(mBGRect.min.x, getRect().min.y, mBGRect.max.x, mBGRect.min.y) );
			}
			if ( !mFramePieces[LM].isNull() ) {
				b.Image.drawImageUnscaledAndTiled( mFramePieces[LM], FRect(mBGRect.min.x, mBGRect.max.y, mBGRect.max.x, getRect().max.y) );
			}

			if ( !mFramePieces[ML].isNull() ) {
				b.Image.drawImageUnscaledAndTiled( mFramePieces[ML], FRect(getRect().min.x, mBGRect.min.y, mBGRect.min.x, mBGRect.max.y) );
			}
			
			if ( !mFramePieces[MR].isNull() ) {
				b.Image.drawImageUnscaledAndTiled( mFramePieces[MR], FRect(mBGRect.max.x, mBGRect.min.y, getRect().max.x, mBGRect.max.y) );
			}

			if ( !mFramePieces[MM].isNull() ) {
				// might have to force pixel alignment here.
				b.Image.drawImageUnscaledAndTiled( mFramePieces[MM], mBGRect);
			}


		}


		const FRect& Frame::getBGRect() const
		{
			return mBGRect;
		}

	} // namespace Amethyst{
} // namespace OpenGUI{

