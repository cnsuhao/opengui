// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_TextureData.h"
#include "OpenGUI_System.h"
#include "OpenGUI_Resource.h"
#include "OpenGUI_ResourceProvider.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	//#####################################################
	TextureData::TextureData() {
		mPixelData = 0;
		mHeight = 0;
		mWidth = 0;
		mBPP = 0;
	}
	//#####################################################
	TextureData::~TextureData() {
		if ( mPixelData )
			delete[] mPixelData;
	}
	//#####################################################
	void TextureData::setData( int width, int height, int bpp, void* dataSource ) {
		if ( mPixelData )
			delete[] mPixelData;
		mWidth = width;
		mHeight = height;
		mBPP = bpp;

		size_t dataSize = mBPP * mHeight * mWidth;
		mPixelData = new unsigned char[dataSize];
		memcpy( mPixelData, dataSource, dataSize );
	}
	//#####################################################
	void TextureData::createNewData( int width, int height, int bpp, unsigned char* initData ) {
		if ( mPixelData )
			delete[] mPixelData;
		mWidth = width;
		mHeight = height;
		mBPP = bpp;

		size_t dataSize = mBPP * mHeight * mWidth;
		mPixelData = new unsigned char[dataSize];

		if ( !initData ) {
			memset( mPixelData, 0, dataSize );
		} else {
			for ( unsigned int i = 0; i < dataSize; ) {
				for ( int j = 0; j < bpp && i < dataSize; j++, i++ ) {
					mPixelData[i] = initData[j];
				}
			}
		}
	}
	//#####################################################
	unsigned char* TextureData::getPixelData() const {
		return mPixelData;
	}
	//#####################################################
	int TextureData::getWidth() const {
		return mWidth;
	}
	//#####################################################
	int TextureData::getHeight() const {
		return mHeight;
	}
	//#####################################################
	int TextureData::getBPP() const {
		return mBPP;
	}
	//#####################################################
};















