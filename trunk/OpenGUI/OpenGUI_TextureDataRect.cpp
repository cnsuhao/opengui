
#include "OpenGUI_Exception.h"

#include "OpenGUI_TextureDataRect.h"
#include "OpenGUI_TextureData.h"

namespace OpenGUI{

	//############################################################################
	TextureDataRect::~TextureDataRect()
	{
		_reset();
	}
	//############################################################################
	TextureDataRect::TextureDataRect( const IVector2& size, const TDRColor& color )
	{
		if(size.x > 0 && size.y > 0){
			mSize = size;
			mData = new TDRColor[ size.x * size.y ];
			TDRColor* tmpPtr = mData;
			for(unsigned int i=0; i < (unsigned int)(mSize.x * mSize.y); i++){
				tmpPtr[i] = color;
			}
		}else{
			// invalid size means we initialize with no data at all
			mSize = IVector2(0,0);
			mData = 0;
		}
	}
	//############################################################################
	TextureDataRect::TextureDataRect( const TextureData* srcTextureData, const IRect& srcRect )
	{
		mSize = IVector2(0,0);
		mData = 0;
		TextureDataRect::copy(srcTextureData, srcRect);
	}
	//############################################################################
	TextureDataRect::TextureDataRect( const TextureDataRect* srcTextureDataRect, const IRect& srcRect )
	{
		mSize = IVector2(0,0);
		mData = 0;
		TextureDataRect::copy(srcTextureDataRect, srcRect);
	}
	//############################################################################
	IVector2 TextureDataRect::getSize()
	{
		return mSize;
	}
	//############################################################################
	void TextureDataRect::setSize(const IVector2& newSize, const TDRColor& color)
	{
		// this is a little evil =)
		TextureDataRect tmpTDR( newSize, color );
		TextureDataRect::paste(&tmpTDR, IVector2(0,0));
		TDRColor* tmpData = mData;
		IVector2 tmpSize = mSize;
		mData = tmpTDR.mData;
		mSize = tmpTDR.mSize;
		tmpTDR.mData = tmpData;
		tmpTDR.mSize = tmpSize;
	}
	//############################################################################
	void TextureDataRect::fill(const TDRColor& color)
	{
		if(mData){
			TDRColor* tmpPtr = (TDRColor*) mData;
			for(unsigned int i=0; i < (unsigned int)(mSize.x * mSize.y); i++){
				tmpPtr[i] = color;
			}
		}
	}
	//############################################################################
	void TextureDataRect::copy(const TextureData* srcTextureData, IRect srcRect)
	{
		//clear any existing data
		_reset();

		//clamp the source rect extents
		if( srcRect.max.x > srcTextureData->getWidth() )
			srcRect.max.x = srcTextureData->getWidth();
		if( srcRect.max.y > srcTextureData->getHeight() )
			srcRect.max.y = srcTextureData->getHeight();
		if( srcRect.min.x < 0 ) srcRect.min.x = 0;
		if( srcRect.min.y < 0 ) srcRect.min.y = 0;

		//abort if there is nothing left to copy
		if( srcRect.getHeight() <= 0 || srcRect.getWidth() <= 0 )
			return;

		//build a new buffer capable of holding the data
		TextureDataRect::_buildBuffer( srcRect.getSize() );

		//perform the copy
		unsigned char* srcData = srcTextureData->getPixelData();
		int srcBPP = srcTextureData->getBPP();
		int srcWidth = srcTextureData->getWidth() * srcBPP;
		int sX,sY, dX,dY;
		TDRColor pixelColor = TDRColor(0,0,0,0); //init with pure black no alpha, and let the loop deal with it
		for(dY = 0, sY = srcRect.min.y; sY < srcRect.max.y; dY++, sY++){
			for(dX = 0, sX = srcRect.min.x; sX < srcRect.max.x; dX++, sX++){
				unsigned char* pixelData = &srcData[ ( sY * srcWidth ) + ( sX * srcBPP ) ];
				if(srcBPP == 1){
					pixelColor.Alpha = *pixelData;
					TextureDataRect::write( IVector2(dX, dY), pixelColor );
				}
				if(srcBPP == 3){
					pixelColor.Red = *pixelData;
					pixelColor.Green = *(pixelData + 1);
					pixelColor.Blue = *(pixelData + 2);
					TextureDataRect::write( IVector2(dX, dY), pixelColor );
				}
				if(srcBPP == 4){
					pixelColor.Red = *pixelData;
					pixelColor.Green = *(pixelData + 1);
					pixelColor.Blue = *(pixelData + 2);
					pixelColor.Alpha = *(pixelData + 3);
					TextureDataRect::write( IVector2(dX, dY), pixelColor );
				}
			}
		}
	}
	//############################################################################
	void TextureDataRect::copy(const TextureDataRect* srcTextureDataRect, IRect srcRect)
	{
		//clear any existing data
		_reset();

		//clamp the source rect extents
		if( srcRect.max.x > srcTextureDataRect->mSize.x )
			srcRect.max.x = srcTextureDataRect->mSize.x;
		if( srcRect.max.y > srcTextureDataRect->mSize.y )
			srcRect.max.y = srcTextureDataRect->mSize.y;
		if( srcRect.min.x < 0 ) srcRect.min.x = 0;
		if( srcRect.min.y < 0 ) srcRect.min.y = 0;

		//abort if there is nothing left to copy
		if( srcRect.getHeight() <= 0 || srcRect.getWidth() <= 0 )
			return;

		//build a new buffer capable of holding the data
		TextureDataRect::_buildBuffer( srcRect.getSize() );

		//perform the copy
		TDRColor* srcData = srcTextureDataRect->mData;
		int srcWidth = srcTextureDataRect->mSize.y;
		int sX,sY, dX,dY;
		TDRColor pixelColor = TDRColor(0,0,0,0); //init with pure black no alpha, and let the loop deal with it
		for(dY = 0, sY = srcRect.min.y; sY < srcRect.max.y; dY++, sY++){
			for(dX = 0, sX = srcRect.min.x; sX < srcRect.max.x; dX++, sX++){
				TDRColor* pixelData = &srcData[ ( sY * srcWidth ) + ( sX ) ];
				TextureDataRect::write( IVector2(dX, dY), *pixelData );
			}
		}
	}
	//############################################################################
	void TextureDataRect::paste(TextureData* dstTextureData, const IVector2& dstOffset) const
	{
		IRect dstRect;
		dstRect.setSize( mSize );
		dstRect.setPosition( dstOffset );

		//perform the copy
		unsigned char* dstData = dstTextureData->getPixelData();
		int dstBPP = dstTextureData->getBPP();
		int dstWidth = dstTextureData->getWidth() * dstBPP;
		int sX,sY, dX,dY;

		for(sY = 0, dY = dstRect.min.y; dY < dstRect.max.y; sY++, dY++){
			if( dY >= 0 && dY < dstTextureData->getHeight() ){
				for(sX = 0, dX = dstRect.min.x; dX < dstRect.max.x; sX++, dX++){
					if( dX >= 0 && dX < dstTextureData->getWidth() ){
						unsigned char* pixelData = &dstData[ ( dY * dstWidth ) + ( dX * dstBPP ) ];
						TDRColor srcData = TextureDataRect::read( IVector2(sX,sY) );

						if(dstBPP == 1){
							*pixelData = srcData.Alpha;
						}
						if(dstBPP == 3){
							*pixelData = srcData.Red;
							*(pixelData + 1) = srcData.Green;
							*(pixelData + 2) = srcData.Blue;
						}
						if(dstBPP == 4){
							*pixelData = srcData.Red;
							*(pixelData + 1) = srcData.Green;
							*(pixelData + 2) = srcData.Blue;
							*(pixelData + 3) = srcData.Alpha;
						}
					}
				}
			}
		}
	}
	//############################################################################
	void TextureDataRect::paste(TextureDataRect* dstTextureDataRect, const IVector2& dstOffset) const
	{
		IRect dstRect;
		dstRect.setSize( mSize );
		dstRect.setPosition( dstOffset );

		//perform the copy
		TDRColor* dstData = dstTextureDataRect->mData;
		
		int dstWidth = dstTextureDataRect->mSize.x;
		int sX,sY, dX,dY;

		for(sY = 0, dY = dstRect.min.y; dY < dstRect.max.y; sY++, dY++){
			for(sX = 0, dX = dstRect.min.x; dX < dstRect.max.x; sX++, dX++){
				TDRColor srcData = TextureDataRect::read( IVector2(sX,sY) );
				dstTextureDataRect->write( IVector2(dX, dY), srcData);
			}
		}
	}
	//############################################################################
/*	
	THESE FUNCTIONS HAVE BEEN INLINED

	void TextureDataRect::write(const IVector2& position, const TDRColor& color)
	{
		//only allow writes within the available data range
		if( position.x < 0 || position.y < 0 ||
			position.x >= mSize.x || position.y >= mSize.y )
			return;
		mData[ (mSize.x * position.y) + position.x ] = color;
	}
	//############################################################################
	TDRColor TextureDataRect::read(const IVector2& position) const
	{
		//only allow reads within the available data range
		if( position.x < 0 || position.y < 0 ||
			position.x >= mSize.x || position.y >= mSize.y )
			return TDRColor();
		return mData[ (mSize.x * position.y) + position.x ];
	}
*/	//############################################################################
	void TextureDataRect::_reset()
	{
		if(mData)
			delete[] mData;
		mData = 0;
		mSize = IVector2(0,0);
	}
	//############################################################################
	void TextureDataRect::_buildBuffer(const IVector2& size)
	{
		_reset(); //can't hurt
		mSize = size;
		if(size.x <= 0 || size.y <= 0){
			OG_THROW(Exception::ERR_INVALIDPARAMS, "'size' cannot contain a dimension <= 0. : " + size.toStr(), "TextureDataRect::_buildBuffer");
		}
		mData = new TDRColor[ size.x * size.y ];
	}
	//############################################################################

};//namespace OpenGUI{