#ifndef CC4E0032_8B26_4a68_B39D_93E31ECC8435
#define CC4E0032_8B26_4a68_B39D_93E31ECC8435

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Cursor.h"
#include "OpenGUI_CursorManager.h"
#include "OpenGUI_Imagery.h"

namespace OpenGUI {
	//! A generic Cursor implementation based on static Imagery
	/*! Static Imagery based cursors are one of the most common cursor types across all
	GUIs, so this implementation is built directly into %OpenGUI for production use, as
	well as being an example of how to make your own cursors. */
	class OPENGUI_API GenericCursor: public Cursor {
	public:
		GenericCursor();
		virtual ~GenericCursor();
		//! sets the imagery for this cursor
		void setImagery( ImageryPtr imagery );
		//! returns a pointer to the imagery of this cursor
		ImageryPtr getImagery();
		//! sets the pointer location offset within the imagery for this cursor
		void setOffset( const IVector2& offset );
		//! returns the pointer location offset within the imagery for this cursor
		const IVector2& getOffset();

		//! factory callback for creating GenericCursor
		static CursorPtr GenericCursorFactory();

		//Object Functions
		virtual ObjectAccessorList* getAccessors();
		virtual char* getClassName();

	protected:
		//! draws this cursor
		virtual void onDraw( Object* sender, DrawCursor_EventArgs& evtArgs );

	private:
		void _updateOffsetCache();

		ImageryPtr mImagery;
		IVector2 mOffset;
		FVector2 mOffsetCache;
	};

}//namespace OpenGUI{

#endif // CC4E0032_8B26_4a68_B39D_93E31ECC8435