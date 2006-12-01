#ifndef Amethyst_ScrollBar_H_h__
#define Amethyst_ScrollBar_H_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"
#include "Amethyst_Frame.h"
namespace OpenGUI {
	namespace Amethyst {

		class AMETHYST_API ScrollBar_H: public Frame {
		public:
			ScrollBar_H();
			virtual ~ScrollBar_H();

			//! "Cursor_Click" event
			virtual void onCursor_Click( Object* sender, Cursor_EventArgs& evtArgs );
			//! "Cursor_Enter" event; invokes Targeted
			virtual void onCursor_Enter( Object* sender, Cursor_EventArgs& evtArgs );
			//! "Cursor_Leave" event; invokes UnTargeted
			virtual void onCursor_Leave( Object* sender, Cursor_EventArgs& evtArgs );

			//! "Cursor_Press" event
			virtual void onCursor_Press( Object* sender, Cursor_EventArgs& evtArgs );
			//! "Cursor_Release" event
			virtual void onCursor_Release( Object* sender, Cursor_EventArgs& evtArgs );
			//! "Cursor_Move" event
			void onCursor_Move( Object* sender, Cursor_EventArgs& evtArgs );


			//! Sets the imagery for the thumb.
			void setThumbImagery( std::string imageryName);
			//! Gets the imagery for the thumb.
			std::string getThumbImagery();

			void setThumbPos(float p) {mThumbPosValue = p;}
			float getThumbPos() {return mThumbPosValue;}
			void setPageSize(float p) {mPageSize = p;}
			float getPageSize() {return mPageSize;}
			void setLineSize(float p) {mLineSize = p;}
			float getLineSize() {return mLineSize;}

			static Widget* CreateScrollBar_HFactory();

			void pageUp();
			void pageDown();
			void lineUp();
			void lineDown();

		protected:
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );

			void _positionThumb();

			ImageryPtr mThumbImage;

			FRect mThumbImageOffsets;
			float mThumbPosValue;
			float mPageSize;
			float mLineSize;

			bool m_bMouseDraggingThumb;
			FVector2 m_vMosueOffset;
			FRect m_rThumbRect;
		};
	} // namespace Amethyst{
} // namespace OpenGUI{


#endif // Amethyst_ScrollBar_H_h__
