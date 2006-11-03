#ifndef Amethyst_Button_h__
#define Amethyst_Button_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"

namespace OpenGUI {
	namespace Amethyst {

		enum {
			BS_NORMAL,
			BS_PRESSED,
			BS_HOVER,
			BS_DISABLED
		};
		class AMETHYST_API SimpleButton : public Control {
		public:
			//! Constructor
			SimpleButton();
			//! virtual Destructor
			virtual ~SimpleButton();
			//! Sets the normal button imagery.
			void setImagery( std::string imageryName );
			//! Sets the pressed button imagery. If none specified, uses the Normal imagery.
			void setImageryPressed( std::string imageryName );
			//! Sets the mouse over button imagery. If none specified, uses the Normal imagery.
			void setImageryMouseOver( std::string imageryName );
			//! Sets the disabled button imagery. If none specified, uses the Normal imagery.
			void setImageryDisabled( std::string imageryName );

			//! Gets the normal button imagery.
			std::string getImagery();
			//! Gets the pressed button imagery.
			std::string getImageryPressed();
			//! Gets the mouse over button imagery.
			std::string getImageryMouseOver();
			//! Gets the disabled button imagery.
			std::string getImageryDisabled();


			static Widget* createSimpleButtonFactory();

		protected:
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );
			virtual void onResized( Object* sender, Resized_EventArgs& evtArgs );

			// events we care about

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

			ImageryPtr mImageryPtr;
			ImageryPtr mImageryPtrPressed;
			ImageryPtr mImageryPtrMouseOver;
			ImageryPtr mImageryPtrDisabled;

			bool m_bMouseButtonState;
			int mButtonState;

		};


	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_Button_h__
