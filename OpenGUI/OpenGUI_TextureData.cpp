#include "corona.h"
#include "OpenGUI.h"
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
	TextureData* TextureData::LoadTextureData( std::string filename ) {
		//we can't load anything until the system is up
		//but we should try to play nice
		if ( !System::getSingletonPtr() )
			return 0;
		ResourceProvider* rp = System::getSingletonPtr()->_getResourceProvider();
		if ( rp == 0 ) return 0;

		//load the resource into memory via the registered resource provider
		Resource resource;
		try {
			rp->loadResource( filename, resource );
		} catch ( Exception e ) {
			return 0;
		};

		//pass the data to corona
		corona::File* cf = corona::CreateMemoryFile( resource.getData(), ( int )resource.getSize() );
		resource.release(); //at this point, we don't need the resource loaded any longer
		if ( !cf ) {
			return 0;
		}
		corona::Image* img = corona::OpenImage( cf, corona::PF_DONTCARE );
		delete cf;
		cf = 0; //at this point, we don't need the memory file any longer

		TextureData* retval = new TextureData();
		retval->mHeight = img->getHeight();
		retval->mWidth = img->getWidth();

		//perform data format enumeration and
		switch ( img->getFormat() ) {
		case corona::PF_I8:
			retval->mBPP = 1;
			break;

		case corona::PF_B8G8R8A8:
			img = corona::ConvertImage( img, corona::PF_R8G8B8A8 );
			if ( img == 0 ) {//we failed to convert, bail out
				delete retval;
				return 0;
			}
		case corona::PF_R8G8B8A8:
			retval->mBPP = 4;
			break;

		case corona::PF_B8G8R8:
			img = corona::ConvertImage( img, corona::PF_R8G8B8 );
			if ( img == 0 ) {//we failed to convert, bail out
				delete retval;
				return 0;
			}
		case corona::PF_R8G8B8:
			retval->mBPP = 3;
			break;

		default:
			delete retval;
			delete img;
			return 0;
			break;//<- habit
		}

		/*	At this point, the data should now be completely loaded into a known format.
			All we need to do is copy the img buffer contents and we're done
		*/

		size_t dataSize = retval->mBPP * retval->mHeight * retval->mWidth;
		retval->mPixelData = new unsigned char[dataSize];
		memcpy( retval->mPixelData, img->getPixels(), dataSize );

		delete img; //and delete this or we leak
		return retval;
	}
	//#####################################################




};















