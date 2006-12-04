#ifndef Amethyst_ScrollBar_V_h__
#define Amethyst_ScrollBar_V_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"
namespace OpenGUI {
	namespace Amethyst {

		class AMETHYST_API ScrollBar_V: public Control {
		public:
			ScrollBar_V();
			virtual ~ScrollBar_V();

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


			//! Sets the BG imagery. TEMP until face/themes get in 
			void setImagery( std::string imageryName);
			//! Sets the BG imagery. TEMP until face/themes get in 
			std::string getImagery();
			//! Sets the imagery for the thumb.
			void setThumbImagery( std::string imageryName);
			//! Gets the imagery for the thumb.
			std::string getThumbImagery();

			void setThumbPos(float p) {mThumbPosValue = p;}
			float getThumbPos() {return mThumbPosValue;}
			void setCanvasSize(float c) {mCanvasSize = c;}
			float getCanvasSize() {return mCanvasSize;}
			void setPageSize(float p) {mPageSize = p;}
			float getPageSize() {return mPageSize;}
			void setLineSize(float p) {mLineSize = p;}
			float getLineSize() {return mLineSize;}

			void setInitialScrollTime(float t) {m_fInitialScrollTime = t;}
			float getInitialScrollTime() {return m_fInitialScrollTime;}
			void setScrollRepeatTime(float t) {m_fScrollRepeatTime = t;}
			float getScrollRepeatTime() {return m_fScrollRepeatTime;}

			static Widget* CreateScrollBar_VFactory();

			void pageUp();
			void pageDown();
			void lineUp();
			void lineDown();

		protected:
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );
			//! "Tick" event
			virtual void onTick( Object* sender, Tick_EventArgs& evtArgs );

			float	m_fCountdownTime;
			float	m_fInitialScrollTime;
			float	m_fScrollRepeatTime;

			void _positionThumb();

			ImageryPtr mBGImage;
			ImageryPtr mThumbImage;

			FRect mThumbImageOffsets;
			float mThumbPosValue;
			float mCanvasSize;
			float mPageSize;
			float mLineSize;

			bool m_bMouseDraggingThumb;
			bool m_bMousePaging;
			FVector2 m_vMosueOffset;
			FRect m_rThumbRect;
			FVector2 m_vMousePosition;
		};
	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_ScrollBar_V_h__
