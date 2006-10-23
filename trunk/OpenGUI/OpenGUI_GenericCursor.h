#ifndef CC4E0032_8B26_4a68_B39D_93E31ECC8435
#define CC4E0032_8B26_4a68_B39D_93E31ECC8435

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Cursor.h"
#include "OpenGUI_CursorManager.h"

namespace OpenGUI {

	class OPENGUI_API GenericCursor: public Cursor {
	public:
		GenericCursor();
		virtual ~GenericCursor();
		//! sets the imagery for this cursor
		void setImagery( ImageryPtr imagery );
		//! returns a pointer to the imagery of this cursor
		ImageryPtr getImagery();
		//! sets the pointer location offset within the imagery for this cursor
		void setOffset( const FVector2& offset );
		//! returns the pointer location offset within the imagery for this cursor
		const FVector2& getOffset();

		//! factory callback for creating GenericCursor
		static CursorPtr GenericCursorFactory();
	protected:
		//! draws this cursor
		virtual void onDraw( Object* sender, DrawCursor_EventArgs& evtArgs );

	private:
		ImageryPtr mImagery;
		FVector2 mOffset;
	};

}//namespace OpenGUI{

#endif // CC4E0032_8B26_4a68_B39D_93E31ECC8435