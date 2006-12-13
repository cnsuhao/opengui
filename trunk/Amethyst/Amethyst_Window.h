#ifndef Amethyst_Window_h__
#define Amethyst_Window_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"


namespace OpenGUI {
	namespace Amethyst {

		//! encapsulates the basic mouse/button interaction for all button variants
		class AMETHYST_API Window : public OpenGUI::Window {
		public:
			Window();
			virtual ~Window();

			//! Sets the background Face used to fill the ScrollBar rect
			void setFaceBG( FacePtr faceBG );
			//! Gets the background Face used to fill the ScrollBar rect
			FacePtr getFaceBG() const;

			virtual void onCursor_Move( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursor_Enter( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursor_Leave( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursor_Press( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursor_Release( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursor_Focused( Object* sender, Focus_EventArgs& evtArgs );
			virtual void onCursor_FocusLost( Object* sender, Focus_EventArgs& evtArgs );

			static Widget* createWindowFactory();
			virtual ObjectAccessorList* getAccessors();
		protected:
			virtual void onDrawBG( Object* sender, Draw_EventArgs& evtArgs );
		private:
			FacePtr mFaceBG;
		};

	} //namespace Amethyst {
} // namespace OpenGUI {
#endif // Amethyst_Window_h__
