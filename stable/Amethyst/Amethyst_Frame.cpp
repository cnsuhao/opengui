#include "Amethyst_Frame.h"

namespace OpenGUI {
	namespace Amethyst {

		Frame::Frame()
		{
			mFrameWidth = 5;
			mFrameHeight = 5;
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
			Brush& b = evtArgs.brush;

			if ( !mFramePieces[UL].isNull() ) {
				FRect myRect = getRect();
				myRect.setWidth(mFrameWidth);
				myRect.setHeight(mFrameHeight);
				b.Image.drawImage( mFramePieces[UL], myRect );
			}
			if ( !mFramePieces[UM].isNull() ) {
				FRect myRect = getRect();
				myRect.setPosition(myRect.getPosition() + FVector2(mFrameWidth, 0));
				myRect.setWidth(getRect().getWidth() - (mFrameWidth*2));
				myRect.setHeight(mFrameHeight);
				b.Image.drawImageUnscaledAndTiled( mFramePieces[UM], myRect );
			}
			if ( !mFramePieces[UR].isNull() ) {
				FRect myRect = getRect();
				myRect.setPosition(myRect.getPosition() + FVector2(getRect().getWidth() - mFrameWidth, 0));
				myRect.setWidth(mFrameWidth);
				myRect.setHeight(mFrameHeight);
				b.Image.drawImage( mFramePieces[UR], myRect );
			}

			if ( !mFramePieces[ML].isNull() ) {
				FRect myRect = getRect();
				myRect.setPosition(myRect.getPosition() + FVector2(0, mFrameHeight));
				myRect.setWidth(mFrameWidth);
				myRect.setHeight(getRect().getHeight() - (2*mFrameHeight));
				b.Image.drawImageUnscaledAndTiled( mFramePieces[ML], myRect );
			}
			if ( !mFramePieces[MM].isNull() ) {
				FRect myRect = getRect();
				myRect.setPosition(myRect.getPosition() + FVector2(mFrameWidth, mFrameHeight));
				myRect.setWidth(getRect().getWidth() - (mFrameWidth*2));
				myRect.setHeight(getRect().getHeight() - (2*mFrameHeight));

				// might have to force pixel alignment here.
				b.Image.drawImageUnscaledAndTiled( mFramePieces[MM], myRect);
			}
			if ( !mFramePieces[MR].isNull() ) {
				FRect myRect = getRect();
				myRect.setPosition(myRect.getPosition() + FVector2(getRect().getWidth() - mFrameWidth, mFrameHeight));
				myRect.setWidth(mFrameWidth);
				myRect.setHeight(getRect().getHeight() - (2*mFrameHeight));
				b.Image.drawImageUnscaledAndTiled( mFramePieces[MR], myRect );
			}

			if ( !mFramePieces[LL].isNull() ) {
				FRect myRect = getRect();
				myRect.setPosition(myRect.getPosition() + FVector2(0, getRect().getHeight() - mFrameHeight));
				myRect.setWidth(mFrameWidth);
				myRect.setHeight(mFrameHeight);
				b.Image.drawImage( mFramePieces[LL], myRect );
			}
			if ( !mFramePieces[LM].isNull() ) {
				FRect myRect = getRect();
				myRect.setPosition(myRect.getPosition() + FVector2(mFrameWidth, getRect().getHeight() - mFrameHeight));
				myRect.setWidth(getRect().getWidth() - (mFrameWidth*2));
				myRect.setHeight(mFrameHeight);
				b.Image.drawImageUnscaledAndTiled( mFramePieces[LM], myRect );
			}
			if ( !mFramePieces[LR].isNull() ) {
				FRect myRect = getRect();
				myRect.setPosition(myRect.getPosition() + FVector2(getRect().getWidth() - mFrameWidth, getRect().getHeight() - mFrameHeight));
				myRect.setWidth(mFrameWidth);
				myRect.setHeight(mFrameHeight);
				b.Image.drawImage( mFramePieces[LR], myRect );
			}
		}


	} // namespace Amethyst{
} // namespace OpenGUI{

