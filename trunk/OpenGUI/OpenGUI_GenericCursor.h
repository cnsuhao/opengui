#ifndef F93374BF_C480_4851_B4ED_F057EBE6621C
#define F93374BF_C480_4851_B4ED_F057EBE6621C
#include "OpenGUI_Cursor.h"

namespace OpenGUI {

	/*! \brief
		The default implementation of the Cursor class.

		This Cursor class is a very generic implementation of
		your average GUI cursor. It simply renders the provided
		imagery in the proper place on the screen.

		Most applications will find this to be a sufficient Cursor
		implementation and will not need to change it.
	*/
	class OPENGUI_API GenericCursor : public Cursor {
	public:
		GenericCursor();
		virtual ~GenericCursor() {}

		/*! \brief Sets the imagery to use for this cursor, offset specifies the
			point within the imagery that should signify the point of the cursor.

			\param imageryName The name of the imagery that this cursor is supposed
					to use.
			\param offset The offset of the imagery. Offsets range from 0.0x0.0 to 1.0x1.0,
					and are calculated using the inner area of the given imagery.
			\exception Will throw an exception if the imageryName given does not
			reference an existing imagery.
		*/
		void setImagery( std::string imageryName, FVector2 offset );

		virtual void show();
		virtual void hide();
		Render::RenderOperationList getCursorRenderOpList();

	private:
		ImageryPtr mImagery;
		FVector2 mOffset;
	};

}
;//namespace OpenGUI{

#endif


