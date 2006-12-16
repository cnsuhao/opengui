// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

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
#include "OpenGUI_TextureManager.h"

#include "OpenGUI_FontAtlas.h"

namespace OpenGUI {

	struct SortFontAtlasRowListByHeightAsc {
		bool operator()( const FontAtlasRow lhs, const FontAtlasRow rhs ) const {
			return lhs.Height < rhs.Height;
		}
	};

	/* Returns true if LHS is < (less than) RHS,
		otherwise false (which will cause a swap to occur).

		We define an IRect as less than another by first comparing
		height, and then comparing width if heights are equal.
	*/
	struct SortFreeIRectList {
		bool operator()( const IRect lhs, const IRect rhs ) const {
			//Is lhs < rhs ?
			if ( lhs.getHeight() < rhs.getHeight() )
				return true;
			else if ( lhs.getHeight() == rhs.getHeight() ) {
				if ( lhs.getWidth() < rhs.getWidth() ) return true;
			}
			return false;
		}
	};
	//############################################################################
	FontAtlas::FontAtlas( IVector2 dimensions ) {
		mOpenRowStartPos = 0;

		// -- I think this only used to create full white textures to aid in debugging, but will need to do some tests (10/28/06 EMS)
		unsigned char initdata = 255; //! \todo DEBUG: Fix me.
		mTextureData.createNewData( dimensions.x, dimensions.y, 1, &initdata );

		mFreeRectList.push_back( IRect( 0, 0, dimensions.x, dimensions.y ) );

		//generate a "meaningful" imageset name
		std::stringstream ss;
		ss << "__FontAtlas:" << ( unsigned int ) this;

		TexturePtr tex = TextureManager::getSingleton().createTextureFromTextureData( ss.str(), &mTextureData );

		mImageset = ImageryManager::getSingleton().createImagesetFromTexture( tex, ss.str() );

		if ( !mImageset ) {
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "Error creating Imageset from manual texture", "FontAtlas::FontAtlas" );
		}

		ss << ":" << "Full";
		mFullImagery = mImageset->createImagery( ss.str() );
	}
	//############################################################################
	FontAtlas::~FontAtlas() {
		mFullImagery = 0;
		if ( mImageset )
			ImageryManager::getSingleton().destroyImageset( mImageset );
	}
	//############################################################################
	FontAtlas::IRectPair FontAtlas::_splitIRect( const IRect& sourceIRect, const IVector2& subtractSpace ) {
		/* This operation is fairly simple. We just remove the subtractSpace from the given sourceIRect
			which will result in 2 remaining (and smaller) IRects. One for the space left at the bottom,
			and one for the space left to the right.
			If the subtractSpace doesn't fit into the sourceIRect, then we just throw an exception.
			(This should never happen, as we expect the input to be pre-validated.)
		*/
		if ( subtractSpace.x <= 0 || subtractSpace.y <= 0 ) {
			OG_THROW( Exception::ERR_INVALIDPARAMS, "(subtractSpace.x <=0 || subtractSpace.y <= 0) == TRUE", "FontAtlas::_splitIRect" );
		}
		if ( sourceIRect.getWidth() < subtractSpace.x ||
				sourceIRect.getHeight() < subtractSpace.y ) {
			OG_THROW( Exception::ERR_INVALIDPARAMS, "subtractSpace is too large to fit into given sourceIRect", "FontAtlas::_splitIRect" );
		}

		IRectPair retval;
		IRect tmpRect;
		bool methodWideBottom;

		//evaluate the requested operation to determine the best split method to use

		if (( sourceIRect.getWidth() - subtractSpace.x ) > ( sourceIRect.getHeight() - subtractSpace.y ) )
			methodWideBottom = false;
		else
			methodWideBottom = true;

		//perform the rect split based on the chosen algorithm
		if ( methodWideBottom ) {
			//calculate the bottom rect
			tmpRect = sourceIRect;
			tmpRect.offset( IVector2( 0, subtractSpace.y ) );
			tmpRect.setHeight( sourceIRect.getHeight() - subtractSpace.y );
			retval.first = tmpRect;

			//calculate the right rect
			tmpRect = sourceIRect;
			tmpRect.setHeight( subtractSpace.y );
			tmpRect.setWidth( sourceIRect.getWidth() - subtractSpace.x );
			tmpRect.offset( IVector2( subtractSpace.x, 0 ) );
			retval.second = tmpRect;
		} else {
			//calculate the bottom rect
			tmpRect = sourceIRect;
			tmpRect.offset( IVector2( 0, subtractSpace.y ) );
			tmpRect.setHeight( sourceIRect.getHeight() - subtractSpace.y );
			tmpRect.setWidth( subtractSpace.x );
			retval.first = tmpRect;

			//calculate the right rect
			tmpRect = sourceIRect;
			tmpRect.setWidth( sourceIRect.getWidth() - subtractSpace.x );
			tmpRect.offset( IVector2( subtractSpace.x, 0 ) );
			retval.second = tmpRect;
		}

		return retval;
	}
	//############################################################################
	unsigned int FontAtlas::statUsedArea() const {
		return statTotalArea() - statAvailableArea();
	}
	//############################################################################
	unsigned int FontAtlas::statAvailableArea() const {
		unsigned int availArea = 0;
		IRectList::const_iterator iter = mFreeRectList.begin();
		while ( iter != mFreeRectList.end() ) {
			availArea += ( *iter ).getArea();
			iter++;
		}
		return availArea;
	}
	//############################################################################
	unsigned int FontAtlas::statTotalArea() const {
		return mTextureData.getWidth() * mTextureData.getHeight();
	}
	//############################################################################
	bool FontAtlas::GetAvailableChunk( IVector2 sizeNeeded, IRect& returnedChunk, bool reserveSpaceFound ) {
		if ( sizeNeeded.x <= 0 || sizeNeeded.y <= 0 )
			return false; //cannot work with garbage input

		//quick check if the sizeNeeded even fits within the entire texture
		if ( mTextureData.getHeight() < sizeNeeded.y || mTextureData.getWidth() < sizeNeeded.x )
			return false; //size needed is larger than this entire texture, so it won't fit anywhere

		//find the smallest existing free IRect that can hold the requested size (height is more important than width)
		IRectList::iterator iter = mFreeRectList.begin();
		while ( iter != mFreeRectList.end() ) {
			IRect debugRect = ( *iter );
			if (( *iter ).getHeight() >= sizeNeeded.y &&
					( *iter ).getWidth() >= sizeNeeded.x ) {
				//it will fit in here, so let's make a chunk to return
				returnedChunk.setPosition(( *iter ).getPosition() );
				returnedChunk.setSize( sizeNeeded );

				//if we are supposed to actually reserve this chunk, do so now
				if ( reserveSpaceFound ) {
					IRectPair rectPair;
					rectPair = _splitIRect(( *iter ), sizeNeeded );
					mFreeRectList.erase( iter ); //remove the old rect

					//push in any valid leftovers
					if ( rectPair.first.getWidth() > 0 && rectPair.first.getHeight() > 0 )
						mFreeRectList.push_front( rectPair.first );
					if ( rectPair.second.getWidth() > 0 && rectPair.second.getHeight() > 0 )
						mFreeRectList.push_front( rectPair.second );

					mFreeRectList.sort( SortFreeIRectList() ); // keep the list sorted when we make changes to it
				}

				return true;
			}
			iter++;
		}


		return false;
	}
	//############################################################################
	bool FontAtlas::WriteChunk( TextureDataRect* chunkToWrite, IRect& returnedChunk ) {
		IRect destRect;

		//apply padding so fonts don't touch (2 pixel border all around)
		IVector2 sizeNeeded = chunkToWrite->getSize();
		sizeNeeded.x += 4;
		sizeNeeded.y += 4;

		//try to find a spot for the data in this atlas, reserving anything we find
		if ( FontAtlas::GetAvailableChunk( sizeNeeded, destRect, true ) ) {
			//it will fit in here, so write it, update the texture, and return true

			//first write a solid background
			TextureDataRect BGMaker( sizeNeeded, TDRColor( 0, 0, 0, 0 ) );
			BGMaker.paste( &mTextureData, destRect.getPosition() );

			//shrink out the padding we added earlier
			destRect.max = destRect.max + IVector2( -4, -4 );
			destRect.offset( IVector2( 2, 2 ) );

			chunkToWrite->paste( &mTextureData, destRect.getPosition() );
			FontAtlas::_UpdateTexture( destRect );
			returnedChunk = destRect;
			return true;
		}
		//this chunk won't fit here, return false
		return false;
	}
	//############################################################################
	void FontAtlas::_UpdateTexture( const IRect& updateRect ) {
		//for now, we'll ignore the updateRect
		TextureManager::getSingleton().updateTextureFromTextureData( mImageset->getTexture(), &mTextureData );
	}
	//############################################################################

}
;//namespace OpenGUI{

