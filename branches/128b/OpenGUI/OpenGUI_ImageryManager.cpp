// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_ImageryManager.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_ResourceProvider.h"
#include "OpenGUI_LogSystem.h"
#include "OpenGUI_TextureManager.h"
#include "OpenGUI_XMLParser.h"
#include "OpenGUI_StrConv.h"
#include "OpenGUI_FaceDef.h"

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
		XMLParser::getSingleton().RegisterLoadHandler( "Face", &ImageryManager::_Face_XMLNode_Load );
		XMLParser::getSingleton().RegisterUnloadHandler( "Face", &ImageryManager::_Face_XMLNode_Unload );
	}
	//############################################################################
	ImageryManager::~ImageryManager() {
		LogManager::SlogMsg( "SHUTDOWN", OGLL_INFO2 ) << "Destroying ImageryManager" << Log::endlog;
		XMLParser::getSingleton().UnregisterLoadHandler( "Imageset", &ImageryManager::_Imageset_XMLNode_Load );
		XMLParser::getSingleton().UnregisterUnloadHandler( "Imageset", &ImageryManager::_Imageset_XMLNode_Unload );
		XMLParser::getSingleton().UnregisterLoadHandler( "Face", &ImageryManager::_Face_XMLNode_Load );
		XMLParser::getSingleton().UnregisterUnloadHandler( "Face", &ImageryManager::_Face_XMLNode_Unload );

		ImageryManager::destroyAllImagesets();
	}
	//############################################################################
	ImagesetPtr ImageryManager::createImageset( const String& imageFilename ) {
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
	ImagesetPtr ImageryManager::createImagesetFromTexture( TexturePtr texture, const String& imageFilename ) {
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

		String newImageFileName = imageFilename;

		if ( imageFilename == "" ) {
			//generate a new filename
			newImageFileName = ImageryManager::_generateRandomName();
		} else {
			newImageFileName = imageFilename;
		}

		LogManager::SlogMsg( "ImageryManager", OGLL_INFO2 )
		<< "CreateImagesetFromTexture: (new) "
		<< newImageFileName << " 0x" << (( unsigned int ) texture.get() ) << Log::endlog;

		imgset = new Imageset( texture, newImageFileName );
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
	ImagesetPtr ImageryManager::getImageset( const String& imageFilename ) {
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
	void ImageryManager::destroyImageset( const String& imageFilename ) {
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
	ImageryPtr ImageryManager::getImagery( const String& imageryName ) {
		// test for fully qualified name lookups
		size_t splitLoc = imageryName.find( ':' );
		if ( splitLoc != String::npos ) {
			// yep, we can do a FQN lookup, so let's do it
			const String setName = imageryName.substr( 0, splitLoc );
			const String imgName = imageryName.substr( splitLoc + 1 );
			ImagesetPtr imgSet = getImageset( setName );
			if ( imgSet ) {
				return imgSet->getImagery( imgName );
			}
			return ImageryPtr( 0 ); // these aren't the droids you're looking for
		}

		// look up by brute force
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
	String ImageryManager::_generateRandomName() {
		static unsigned int mRandomNameGeneratorIndex = 0;
		std::stringstream ss;
		String retval;
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
	bool ImageryManager::_Imageset_XMLNode_Load( const XMLNode& node, const String& nodePath ) {
		ImageryManager& manager = ImageryManager::getSingleton();
		// we only handle these tags within <OpenGUI>
		if ( nodePath != "/OpenGUI/" )
			return false;

		const String filename = node.getAttribute( "File" );
		ImagesetPtr imgset = manager.createImageset( filename );

		XMLNodeList imageryNodes = node.getChildren( "Imagery" );
		for ( XMLNodeList::iterator iter = imageryNodes.begin(); iter != imageryNodes.end(); iter++ ) {
			XMLNode* child = ( *iter );
			const String name = child->getAttribute( "Name" );
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
	bool ImageryManager::_Imageset_XMLNode_Unload( const XMLNode& node, const String& nodePath ) {
		ImageryManager& manager = ImageryManager::getSingleton();
		// we only handle these tags within <OpenGUI>
		if ( nodePath != "/OpenGUI/" )
			return false;

		const String filename = node.getAttribute( "File" );
		ImagesetPtr imgset = manager.getImageset( filename );

		if ( imgset ) {
			XMLNodeList imageryNodes = node.getChildren( "Imagery" );
			for ( XMLNodeList::iterator iter = imageryNodes.begin(); iter != imageryNodes.end(); iter++ ) {
				XMLNode* child = ( *iter );
				const String name = child->getAttribute( "Name" );
				imgset->destroyImagery( name );
			}
			if ( imgset->getImageryCount() == 0 )
				manager.destroyImageset( imgset );
		}
		return true;
	}
	//############################################################################
	void ImageryManager::addFace( FacePtr facePtr ) {
		const String& faceName = facePtr->getName();
		FacePtrMap::iterator iter = mFacePtrMap.find( faceName );
		if ( iter != mFacePtrMap.end() )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM, "Face already registered with name: " + faceName, __FUNCTION__ );
		mFacePtrMap[faceName] = facePtr;
		LogManager::SlogMsg( "ImageryManager", OGLL_INFO2 ) << "AddFace: " << facePtr->getName() << Log::endlog;
	}
	//############################################################################
	FacePtr ImageryManager::getFace( const String& faceName ) {
		FacePtrMap::iterator iter = mFacePtrMap.find( faceName );
		if ( iter == mFacePtrMap.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Face not found: " + faceName, __FUNCTION__ );
		return iter->second;
	}
	//############################################################################
	void ImageryManager::removeFace( const String& faceName ) {
		FacePtrMap::iterator iter = mFacePtrMap.find( faceName );
		if ( iter == mFacePtrMap.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Face not found: " + faceName, __FUNCTION__ );
		mFacePtrMap.erase( iter );
		LogManager::SlogMsg( "ImageryManager", OGLL_INFO2 ) << "RemoveFace: " << faceName << Log::endlog;
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
	bool ImageryManager::_Face_XMLNode_Load( const XMLNode& node, const String& nodePath ) {
		ImageryManager& manager = ImageryManager::getSingleton();
		// we only handle these tags within <OpenGUI>
		if ( nodePath != "/OpenGUI/" )
			return false;

		FaceDef faceDef;
		const String faceNameStr = node.getAttribute( "Name" );
		const String faceMetricStr = node.getAttribute( "Metric" );
		if ( faceMetricStr == "Units" )
			faceDef.Metric = Face::FM_UNITS;
		else if ( faceMetricStr == "Pixels" )
			faceDef.Metric = Face::FM_PIXELS;
		else {
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Face Metric must be either \"Units\" or \"Pixels\", found: " + faceMetricStr, __FUNCTION__ );
		}

		XMLNodeList rowNodes = node.getChildren( "Row" );
		XMLNodeList::iterator iter, iterend = rowNodes.end();
		size_t curRow, curCol;
		for ( curRow = 0, iter = rowNodes.begin(); iter != iterend; curRow++, iter++ ) {
			const XMLNode* rowNode = ( *iter );
			XMLNodeList sliceNodes = rowNode->getChildren( "Slice" );
			XMLNodeList::iterator siter, siterend = sliceNodes.end();
			for ( curCol = 0, siter = sliceNodes.begin(); siter != siterend; curCol++, siter++ ) {
				const XMLNode* sliceNode = ( *siter );
				SliceDef sliceDef;
				//get dimensions, if available
				if ( sliceNode->hasAttribute( "Width" ) ) {
					float dim;
					StrConv::toFloat( sliceNode->getAttribute( "Width" ), dim );
					sliceDef.Width = dim;
				}
				if ( sliceNode->hasAttribute( "Height" ) ) {
					float dim;
					StrConv::toFloat( sliceNode->getAttribute( "Height" ), dim );
					sliceDef.Height = dim;
				}

				//get dim growth, if specified (otherwise the default well remain)
				if ( sliceNode->hasAttribute( "GrowWidth" ) ) {
					bool grow;
					StrConv::toBool( sliceNode->getAttribute( "GrowWidth" ), grow );
					sliceDef.GrowWidth = grow;
				}
				if ( sliceNode->hasAttribute( "GrowHeight" ) ) {
					bool grow;
					StrConv::toBool( sliceNode->getAttribute( "GrowHeight" ), grow );
					sliceDef.GrowHeight = grow;
				}

				//get spans if available
				if ( sliceNode->hasAttribute( "ColSpan" ) ) {
					int span;
					StrConv::toInt( sliceNode->getAttribute( "ColSpan" ), span );
					sliceDef.ColSpan = ( unsigned short ) span;
				}
				if ( sliceNode->hasAttribute( "RowSpan" ) ) {
					int span;
					StrConv::toInt( sliceNode->getAttribute( "RowSpan" ), span );
					sliceDef.RowSpan = ( unsigned short ) span;
				}

				//get tile setting, if specified (otherwise the default well remain)
				if ( sliceNode->hasAttribute( "Tile" ) ) {
					bool tile;
					StrConv::toBool( sliceNode->getAttribute( "Tile" ), tile );
					sliceDef.Tile = tile;
				}

				//get Imagery setting, if specified (otherwise there won't be any)
				if ( sliceNode->hasAttribute( "Imagery" ) ) {
					const String imageryStr = sliceNode->getAttribute( "Imagery" );
					sliceDef.Imagery = manager.getImagery( imageryStr );
				}

				// store the sliceDef into the faceDef
				faceDef.getSlice( curCol, curRow ) = sliceDef;
			}
		}

		// create the face and store it for later
		FacePtr face = Face::Create( faceNameStr, faceDef );
		manager.addFace( face );

		return true;
	}
	//############################################################################
	bool ImageryManager::_Face_XMLNode_Unload( const XMLNode& node, const String& nodePath ) {
		ImageryManager& manager = ImageryManager::getSingleton();
		// we only handle these tags within <OpenGUI>
		if ( nodePath != "/OpenGUI/" )
			return false;

		const String faceName = node.getAttribute( "Name" );
		manager.removeFace( faceName );
		return true;
	}
	//############################################################################
}
; //namespace OpenGUI{





