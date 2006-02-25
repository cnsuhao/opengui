#ifndef D978A3F2_DDCF_4181_935B_650180024456
#define D978A3F2_DDCF_4181_935B_650180024456
#include "OpenGUI_RenderOperation.h"

namespace OpenGUI{

		/*! \brief
			The cursor class is the base class for all Cursors.

			Cursors in %OpenGUI are a little different from other
			GUI systems. For starters, they are entirely customizable.
			The Cursor class itself is an abstract interface class
			that defines the methods that all cursors must implement.

			\see For a simple implementation of a cursor that will cover
				the needs of most applications, see GenericCursor.
		*/
		class OPENGUI_API Cursor
		{
		public:
			Cursor() {}
			virtual ~Cursor() {}

			//! Called when the cursor should be shown.
			/*! All cursors start non-visible, and should not
				register to draw until this function is called. */
			virtual void show()=0;

			//! Called when the cursor should hide.
			/*! Cursors should hide themselves when this is called
				by unregistering themselves from the cursor draw queue.
				You can optionally perform a fade out or similar effect
				by delaying the unregistration of the draw until you are
				finished fading.
			*/
			virtual void hide()=0;


			/*! \brief Generate a RenderOperationList to draw the cursor

			This function will be called by the system whenever it needs the cursor to redraw
			itself. (Which, FYI, is every frame for cursors registered to draw.)
			Returned list should be depth ordered using a painters algorithm (back to front).
			Cursors are \b always the last render operation performed in a frame, and their
			render operations are \b never cached.
			\note The returned RenderOperations are expected to be in world coordinates.
				A cursor implementation can get retrieve the current mouse location from the system
				via System::getSingleton().getCursorPos(), and should do so every frame
				to ensure they are drawing in the correct location.
			*/
			virtual Render::RenderOperationList getCursorRenderOpList()=0;
			
		protected:
			/*!\brief This built in function allows the cursor to register itself for
				drawing with the CursorManager.

				Cursors should not register for drawing until they are asked to be shown,
				as it causes getCursorRenderOpList() to be called every frame.
				The CursorManager will automatically call the cursor's show() and hide()
				to inform it if it should be visible or not.

				This function is implemented in the Cursor base class so that subclasses
				can use it to register for drawing with the CursorManager.

				Multiple calls to this function have no ill effect, and calling it
				when the cursor has never registered with the CursorManager will do
				nothing.
			*/
			void RegisterForDraw();

			/*!\brief This built in function allows the cursor to unregister itself from
			drawing with the CursorManager.

			Cursors should not unregister for drawing until they are asked to be hidden,
			as it causes getCursorRenderOpList() to no longer be called every frame.
			The CursorManager will automatically call the cursor's show() and hide()
			to inform it if it should be visible or not.

			This function is implemented in the Cursor base class so that subclasses
			can use it to unregister from drawing with the CursorManager.

			Multiple calls to this function have no ill effect, and calling it
			when the cursor has never registered with the CursorManager will do
			nothing.
			*/
			void UnRegisterForDraw();
		};

};//namespace OpenGUI{
#endif
