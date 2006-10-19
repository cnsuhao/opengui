#ifndef E43C75DC_6765_4fd8_844E_94EA5CB3D410
#define E43C75DC_6765_4fd8_844E_94EA5CB3D410

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_TextureData.h"
#include "OpenGUI_TextureDataRect.h"

namespace OpenGUI {

	class Imageset;

	typedef struct _FontAtlasRow {
		unsigned int Row; //The Y position this row starts at
		unsigned int Height; //the height of the row
		unsigned int RowWidth; //the width of area used in this row
	}
	FontAtlasRow;

	//! \internal A FontAtlas is a Texture containing several rendered font glyphs, this implementation provides additional space management functionality, and is used internally by the Font system.
	class FontAtlas {
	public:
		FontAtlas( IVector2 dimensions );
		~FontAtlas();

		bool GetAvailableChunk( IVector2 sizeNeeded, IRect& returnedChunk, bool reserveSpaceFound = false );
		bool WriteChunk( TextureDataRect* chunkToWrite, IRect& returnedChunk );
		Imageset* GetImageset() {
			return mImageset;
		}
		const ImageryPtr& GetFullImagery() {
			return mFullImagery;
		}

		unsigned int statUsedArea() const;
		unsigned int statAvailableArea() const;
		unsigned int statTotalArea() const;
	private:
		typedef std::list<IRect> IRectList;
		typedef std::pair<IRect, IRect> IRectPair;

		void _UpdateTexture( const IRect& updateRect );

		IRectPair _splitIRect( const IRect& sourceIRect, const IVector2& subtractSpace );


		typedef std::list<FontAtlasRow> FontAtlasRowList;
		FontAtlasRowList mRowList;

		// This marks the starting row of open space, it naturally initializes to 0
		unsigned int mOpenRowStartPos;

		TextureData mTextureData;
		Imageset* mImageset; //pointer to out imageset
		ImageryPtr mFullImagery; //handle to an imagery that covers the full area of the imageset


		IRectList mFreeRectList;
	};

}
;//namespace OpenGUI{
#endif

