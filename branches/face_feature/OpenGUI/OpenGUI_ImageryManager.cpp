#include "OpenGUI_ImageryManager.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_ResourceProvider.h"
#include "OpenGUI_LogSystem.h"
#include "OpenGUI_TextureManager.h"
#include "OpenGUI_XMLParser.h"
#include "OpenGUI_StrConv.h"

namespace OpenGUI {
	template<> ImageryManager* Singleton<ImageryManager>::mptr_Singleton = 0;
	ImageryManager& ImageryManager::getSingleton( void ) {
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	ImageryManager* ImageryManager::getSingletonPtr( void ) {
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	//############################################################################
	ImageryManager::ImageryManager( ResourceProvider* resourceProvider ): mResourceProvider( resourceProvider ) {
		LogManager::SlogMsg( "INIT", OGLL_INFO2 ) << "Creating ImageryManager" << Log::endlog;
		XMLParser::getSingleton().RegisterLoadHandler( "Imageset", &ImageryManager::_Imageset_XMLNode_Load );
		XMLParser::getSingleton().RegisterUnloadHandler( "Imageset", &ImageryManager::_Imageset_XMLNode_Unload );
	}
	//############################################################################
	ImageryManager::~ImageryManager() {
		LogManager::SlogMsg( "SHUTDOWN", OGLL_INFO2 ) << "Destroying ImageryManager" << Log::endlog;
		XMLParser::getSingleton().UnregisterLoadHandler( "Imageset", &ImageryManager::_Imageset_XMLNode_Load );
		XMLParser::getSingleton().UnregisterUnloadHandler( "Imageset", &ImageryManager::_Imageset_XMLNode_Unload );
		ImageryManager::destroyAllImagesets();
	}
	//############################################################################
	ImagesetPtr ImageryManager::createImageset( std::string imageFilename ) {
		ImagesetPtr imgset = getImageset( imageFilename );
		if ( imgset ) {
			return imgset;
		}

		LogManager::SlogMsg( "ImageryManager", OGLL_INFO2 ) << "CreateImageset: " << imageFilename << Log::endlog;

		TexturePtr tex = TextureManager::getSingleton().createTextureFromFile( imageFilename );

		if ( !tex ) return 0;

		imgset = new Imageset( tex, imageFilename );
		if ( !imgset ) {
			return 0;
		}

		mImagesetList.push_back( imgset );
		return imgset;
	}
	//############################################################################
	ImagesetPtr ImageryManager::createImagesetFromTexture( TexturePtr texture, std::string imageFilename ) {
		if ( texture.isNull() ) {
			OG_THROW( Exception::ERR_INVALIDPARAMS, "texture parameter must be a valid texture", "ImageryManager::createImagesetFromTexture" );
		}

		ImagesetPtr imgset;

		if ( imageFilename != "" ) {
			imgset = getImageset( imageFilename );
			if ( imgset ) {
				OG_THROW( Exception::ERR_DUPLICATE_ITEM, "Already an Imageset named: " + imageFilename, "ImageryManager::createImagesetFromTexture" );
			}
		}

		if ( imageFilename == "" ) {
			//generate a new filename
			imageFilename = ImageryManager::_generateRandomName();
		}

		LogManager::SlogMsg( "ImageryManager", OGLL_INFO2 )
		<< "CreateImagesetFromTexture: (new) "
		<< imageFilename << " 0x" << (( unsigned int ) texture.get() ) << Log::endlog;

		imgset = new Imageset( texture, imageFilename );
		if ( !imgset ) {
			return 0;
		}

		mImagesetList.push_back( imgset );
		return imgset;
	}
	//############################################################################
	ImagesetPtr ImageryManager::getImagesetByTexture( TexturePtr texture ) {
		ImagesetPtrList::iterator iter = mImagesetList.begin();
		while ( iter != mImagesetList.end() ) {
			if (( *iter )->getTexture() == texture ) {
				return ( *iter );
			}
			iter++;
		}
		return 0;
	}

	//############################################################################
	ImagesetPtr ImageryManager::getImageset( std::string imageFilename ) {
		ImagesetPtrList::iterator iter = mImagesetList.begin();
		while ( iter != mImagesetList.end() ) {
			if (( *iter )->getName() == imageFilename ) {
				return ( *iter );
			}
			iter++;
		}
		return 0;
	}
	//############################################################################
	void ImageryManager::destroyImageset( ImagesetPtr pImageset ) {
		ImagesetPtrList::iterator iter = mImagesetList.begin();
		while ( iter != mImagesetList.end() ) {
			if (( *iter ) == pImageset ) {
				LogManager::SlogMsg( "ImageryManager", OGLL_INFO2 ) << "DestroyImageset: " << pImageset->getName() << Log::endlog;
				mImagesetList.erase( iter );
				return;
			}
			iter++;
		}
	}
	//############################################################################
	void ImageryManager::destroyImageset( std::string imageFilename ) {
		ImagesetPtr imgset;
		imgset = ImageryManager::getImageset( imageFilename );
		if ( imgset ) {
			ImageryManager::destroyImageset( imgset );
		}
	}
	//############################################################################
	void ImageryManager::destroyAllImagesets() {
		LogManager::SlogMsg( "ImageryManager", OGLL_INFO2 ) << "DestroyAllImagesets..." << Log::endlog;
		ImagesetPtrList::iterator iter = mImagesetList.begin();
		mImagesetList.clear();
	}
	//############################################################################
	ImageryPtr ImageryManager::getImagery( std::string imageryName ) {
		ImagesetPtrList::iterator iter = mImagesetList.begin();
		while ( iter != mImagesetList.end() ) {
			ImageryPtr retptr = ( *iter )->getImagery( imageryName );
			if ( retptr )
				return retptr;
			iter++;
		}
		return ImageryPtr( 0 );
	}
	//############################################################################
	std::string ImageryManager::_generateRandomName() {
		static unsigned int mRandomNameGeneratorIndex = 0;
		std::stringstream ss;
		std::string retval;
		time_t timer;
		time( &timer ); //NOTE: This function call will break after 19:14:07, January 18, 2038, UTC
		ss << "__OPENGUI_RANDOM__:" << ( unsigned int )timer << ":" << mRandomNameGeneratorIndex;
		retval = ss.str();
		mRandomNameGeneratorIndex++;
		//now test the result, and only issue it if we are sure it is not used
		if ( ImageryManager::getSingleton().getImagery( retval ) || ImageryManager::getSingleton().getImageset( retval ) )
			return ImageryManager::_generateRandomName();
		return retval;
	}
	//############################################################################
	ImageryManager::ImagesetList ImageryManager::getImagesetList() {
		ImagesetList retval;
		for ( ImagesetPtrList::iterator iter = mImagesetList.begin(); iter != mImagesetList.end(); iter++ ) {
			retval.push_back(( *iter )->getName() );
		}
		retval.sort();
		return retval;
	}
	//############################################################################
	bool ImageryManager::_Imageset_XMLNode_Load( const XMLNode& node, const std::string& nodePath ) {
		ImageryManager& manager = ImageryManager::getSingleton();

		// we only handle these tags within <OpenGUI>
		if ( nodePath != "/OpenGUI/" )
			return false;

		const std::string filename = node.getAttribute( "File" );
		ImagesetPtr imgset = manager.createImageset( filename );

		XMLNodeList imageryNodes = node.getChildren( "Imagery" );
		for ( XMLNodeList::iterator iter = imageryNodes.begin(); iter != imageryNodes.end(); iter++ ) {
			XMLNode* child = ( *iter );
			const std::string name = child->getAttribute( "Name" );
			int t, l, w, h;
			StrConv::toInt( child->getAttribute( "Top" ), t );
			StrConv::toInt( child->getAttribute( "Left" ), l );
			StrConv::toInt( child->getAttribute( "Width" ), w );
			StrConv::toInt( child->getAttribute( "Height" ), h );
			imgset->createImagery( name, t, l, h, w );
		}
		return true;
	}
	//############################################################################
	bool ImageryManager::_Imageset_XMLNode_Unload( const XMLNode& node, const std::string& nodePath ) {
		ImageryManager& manager = ImageryManager::getSingleton();
		// we only handle these tags within <OpenGUI>
		if ( nodePath != "/OpenGUI/" )
			return false;

		const std::string filename = node.getAttribute( "File" );
		ImagesetPtr imgset = manager.getImageset( filename );

		if ( imgset ) {
			XMLNodeList imageryNodes = node.getChildren( "Imagery" );
			for ( XMLNodeList::iterator iter = imageryNodes.begin(); iter != imageryNodes.end(); iter++ ) {
				XMLNode* child = ( *iter );
				const std::string name = child->getAttribute( "Name" );
				imgset->destroyImagery( name );
			}
			if ( imgset->getImageryCount() == 0 )
				manager.destroyImageset( imgset );
		}
		return true;
	}
	//############################################################################
	void ImageryManager::addFace( const std::string& faceName, FacePtr facePtr ) {
		FacePtrMap::iterator iter = mFacePtrMap.find( faceName );
		if ( iter != mFacePtrMap.end() )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM, "Face already registered with name: " + faceName, __FUNCTION__ );
		mFacePtrMap[faceName] = facePtr;
	}
	//############################################################################
	FacePtr ImageryManager::getFace( const std::string& faceName ) {
		FacePtrMap::iterator iter = mFacePtrMap.find( faceName );
		if ( iter == mFacePtrMap.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Face not found: " + faceName, __FUNCTION__ );
		return iter->second;
	}
	//############################################################################
	void ImageryManager::removeFace( const std::string& faceName ) {
		FacePtrMap::iterator iter = mFacePtrMap.find( faceName );
		if ( iter == mFacePtrMap.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Face not found: " + faceName, __FUNCTION__ );
		mFacePtrMap.erase( iter );
	}
	//############################################################################
	StringList ImageryManager::getFaceList() {
		StringList out;
		FacePtrMap::iterator iter, iterend = mFacePtrMap.end();
		for ( iter = mFacePtrMap.begin(); iter != iterend; iter++ ) {
			out.push_back( iter->first );
		}
		return out;
	}
	//############################################################################
}
; //namespace OpenGUI{





