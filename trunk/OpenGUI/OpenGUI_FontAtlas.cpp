
#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"

#include "OpenGUI_Exception.h"

#include "OpenGUI_Texture.h"
#include "OpenGUI_TextureData.h"
#include "OpenGUI_TextureDataRect.h"
#include "OpenGUI_Renderer.h"
#include "OpenGUI_System.h"

#include "OpenGUI_ImageryManager.h"

#include "OpenGUI_FontAtlas.h"

namespace OpenGUI{

	struct SortFontAtlasRowListByHeightAsc{
		bool operator()( const FontAtlasRow lhs, const FontAtlasRow rhs ) const	{
			return lhs.Height < rhs.Height;
		}
	};
	//############################################################################
	FontAtlas::FontAtlas(IVector2 dimensions)
	{
		mOpenRowStartPos = 0;

		unsigned char initdata = 255; //! \todo DEBUG: Fix me
		mTextureData.createNewData(dimensions.x, dimensions.y, 1, &initdata);

		Texture* tex = System::getSingleton()._getRenderer()->createTextureFromTextureData(&mTextureData);

		//generate a "meaningful" imageset name
		std::stringstream ss;
		ss << "__FontAtlas:" << (unsigned int) this;
		mImageset = ImageryManager::getSingleton().createImagesetFromTexture(tex, ss.str());

		if(!mImageset){
			System::getSingleton()._getRenderer()->destroyTexture(tex);
			OG_THROW(Exception::ERR_INTERNAL_ERROR, "Error creating Imageset from manual texture", "FontAtlas::FontAtlas");
		}
	}
	//############################################################################
	FontAtlas::~FontAtlas()
	{
		if(mImageset)
			ImageryManager::getSingleton().destroyImageset(mImageset);
	}
	//############################################################################
	bool FontAtlas::GetAvailableChunk(IVector2 sizeNeeded, IRect& returnedChunk, bool reserveSpaceFound)
	{
		if(sizeNeeded.x <=0 || sizeNeeded.y <= 0)
			return false; //cannot work with garbage input

		//quick check if the sizeNeeded even fits within the entire texture
		if(mTextureData.getHeight() < sizeNeeded.y || mTextureData.getWidth() < sizeNeeded.x)
			return false; //size needed is larger than this entire texture, so it won't fit anywhere

		//find the smallest existing row capable of holding the desired size
		mRowList.sort(SortFontAtlasRowListByHeightAsc());
		FontAtlasRowList::iterator iter = mRowList.begin();
		while(iter != mRowList.end()){
			if((unsigned int)sizeNeeded.y <= (*iter).Height){
				//potential hit, test for available X space
				if((unsigned int)sizeNeeded.x <= (mTextureData.getWidth() - (*iter).RowWidth) ){
					//this is our solution, update the returnedChunk
					returnedChunk.setSize(sizeNeeded);
					returnedChunk.setPosition( IVector2((*iter).RowWidth, (*iter).Row) );
					if(reserveSpaceFound)//reserve the found space if requested
						(*iter).RowWidth += sizeNeeded.x;
					return true;
				}
			}
			iter++;
		}

		//looks like we ran off the end of the existing list with no reasonable results, try to make a new row
		if( (mTextureData.getHeight() - mOpenRowStartPos) >= (unsigned int)sizeNeeded.y ){
			//we have enough room
			returnedChunk.setSize(sizeNeeded);
			returnedChunk.setPosition(IVector2(0, mOpenRowStartPos));
			if(reserveSpaceFound){//reserve the found space if requested
				//that means we need to create a new row
				FontAtlasRow newRow;
				newRow.Height = returnedChunk.getHeight();
				newRow.Row = mOpenRowStartPos;
				mOpenRowStartPos += newRow.Height;
				newRow.RowWidth = returnedChunk.getWidth();
				mRowList.push_back(newRow);
			}
			return true;
		}

		//not enough room for a new row of this size
		return false;
	}
	//############################################################################
	bool FontAtlas::WriteChunk(TextureDataRect* chunkToWrite, IRect& returnedChunk)
	{
		IRect destRect;
		
		//apply padding so fonts don't touch (2 pixel border all around)
		IVector2 sizeNeeded = chunkToWrite->getSize();
		sizeNeeded.x += 4; sizeNeeded.y += 4;

		//try to find a spot for the data in this atlas, reserving anything we find
		if(FontAtlas::GetAvailableChunk(sizeNeeded, destRect, true)){
			//it will fit in here, so write it, update the texture, and return true

			//first write a solid background
			TextureDataRect BGMaker(sizeNeeded, TDRColor(0,0,0,0));
			BGMaker.paste(&mTextureData, destRect.getPosition());

			//shrink out the padding we added earlier
			destRect.max = destRect.max + IVector2(-4,-4);
			destRect.offset(IVector2(2,2));

			chunkToWrite->paste(&mTextureData, destRect.getPosition());
			FontAtlas::_UpdateTexture(destRect);
			returnedChunk = destRect;
			return true;
		}
		//this chunk won't fit here, return false
		return false;
	}
	//############################################################################
	void FontAtlas::_UpdateTexture(const IRect& updateRect)
	{
		//for now, we'll ignore the updateRect
		System::getSingleton()._getRenderer()->updateTextureFromTextureData(mImageset->getTexture(), &mTextureData);
	}
	//############################################################################

};//namespace OpenGUI{

