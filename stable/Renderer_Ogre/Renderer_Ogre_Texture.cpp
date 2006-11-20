// -----------------------------------------------------------------------------
// Renderer_Ogre_Texture.cpp
// -----------------------------------------------------------------------------

#include "Renderer_Ogre_Texture.h"

#include <OgreException.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreRenderTexture.h>

//! The private Ogre resource group for OpenGUI
/*! OpenGUI uses this resource group to store its internal render textures
(when RTT functionality is available). Users should never, under any circumstances
need to manually modify the contents of this resource group.

You can, however, feel free to change the value of this #define in the (unlikely)
event that it conflicts with an existing resource group of your own. Doing so will
(obviously) require a recompile of this library.
*/
#define OPENGUI_PRIVATE_RESOURCEGROUP "OPENGUI_PRIVATE_RESOURCEGROUP"

namespace OpenGUI {
	//#####################################################################
	void OgreStaticTexture::loadFile( const std::string& filename, const std::string& resourceGroup ) {
		using namespace Ogre;
		freeOgreTexture(); //dump any existing texture
		Ogre::TextureManager* textureManager = Ogre::TextureManager::getSingletonPtr();

		Ogre::TexturePtr tmpTexture = ( Ogre::TexturePtr )textureManager->getByName( filename.c_str() );
		try {
			if ( !tmpTexture.isNull() ) { //check if texture already exists
				mOgreTexturePtr = tmpTexture;
				mNotOwner = true; //we need to make sure we don't destroy it, since we didn't create it
			} else {
				tmpTexture = textureManager->load( filename.c_str(),
												   resourceGroup.c_str(), //only look in the resource group we were given
												   TEX_TYPE_2D, //we only deal with 2D textures in this neck of the woods
												   -1, //mipmaps are for Ninnies
												   1.0f ); //default gamma
				mNotOwner = false; //we own it
			}
		} catch ( Ogre::Exception e ) {
			OG_THROW( Exception::ERR_INTERNAL_ERROR,
					  std::string( "Error loading texture from file: " ) + filename +
					  " (Ogre exception caught during load)",
					  "OgreTexture::loadFile" );
		}

		if ( !tmpTexture.isNull() ) {
			_setSize( IVector2( tmpTexture->getWidth(), tmpTexture->getHeight() ) );
			_setName( filename );
			mOgreTexturePtr = tmpTexture;
		} else {
			//looks like it didn't load after all
			OG_THROW( Exception::ERR_INTERNAL_ERROR,
					  std::string( "Error loading texture from file: " ) + filename +
					  " (Ogre returned a dead texture handle)",
					  "OgreTexture::loadFile" );
		}
	}
	//#####################################################################
	void OgreStaticTexture::freeOgreTexture() {
		if ( !mOgreTexturePtr.isNull() ) {
			if ( !mNotOwner )
				Ogre::TextureManager::getSingleton().remove( mOgreTexturePtr->getHandle() );
			mOgreTexturePtr.setNull();
			mNotOwner = false;
			_setName( "" );
			_setSize( IVector2( 0, 0 ) );
		}
	}
	//#####################################################################
	void OgreStaticTexture::loadOgreTexture( Ogre::TexturePtr ogreTexture ) {
		using namespace Ogre;
		freeOgreTexture(); //dump any existing texture
		if ( !ogreTexture.isNull() ) {
			_setName( ogreTexture->getName() ); //best we can do
			_setSize( IVector2( ogreTexture->getWidth(), ogreTexture->getWidth() ) );
			mOgreTexturePtr = ogreTexture;
			mNotOwner = true; //we obviously don't own this
		}
	}
	//#####################################################################
	void OgreStaticTexture::loadFromTextureData( const TextureData* textureData, const std::string& groupName ) {
		using namespace Ogre;

		freeOgreTexture(); //dump any existing texture
		if ( !textureData ) return; //stop here if there is no data

		//we're going to cheat on this one
		Image tmpImg;
		PixelFormat pFmt;
		switch ( textureData->getBPP() ) {
		case 3: //RGB
			pFmt = PF_BYTE_RGB;
			break;
		case 4: //RGBA
			pFmt = PF_BYTE_RGBA;
			break;
		case 1: // greyscale
			pFmt = PF_A8;
			break;
		}

		//if we are given a bitmap with only an alpha channel, we need to convert it to RBGA
		unsigned char* pixelData = 0;
		bool autoDelete;
		if ( pFmt == PF_A8 ) {
			size_t newSize = textureData->getWidth() * textureData->getHeight() * 4;
			unsigned char* origData = textureData->getPixelData();
			unsigned char* newData = new unsigned char[newSize];
			unsigned char* newPtr; //we use this later
			for (	int i = 0;
					i < textureData->getWidth() * textureData->getHeight();
					i++ ) {

				newPtr = &( newData[i * 4] );
				newPtr[0] = 255; //new R
				newPtr[1] = 255; //new G
				newPtr[2] = 255; //new B
				newPtr[3] = origData[i]; //keep the old A channel
			}

			pFmt = PF_BYTE_RGBA; //and we are now RBGA (yay)
			pixelData = newData; //here's our new data
			autoDelete = true; //and ogre can delete it when it's done with it
		} else {
			pixelData = textureData->getPixelData();
			autoDelete = false; //we'd like to keep our data, thank you
		}

		try {
			tmpImg.loadDynamicImage( pixelData, //pointer to pixel buffer
									 textureData->getWidth(), //width
									 textureData->getHeight(), //height
									 1, // depth = 1 (2D texture)
									 pFmt, // pixel format of input
									 autoDelete, // autoDelete (signifies if Ogre now owns that memory)
									 1, // 1 face (just a 2D texture, cubemaps need not apply)
									 0 ); //mipmaps are still for Ninnies
		} catch ( Ogre::Exception e ) {
			OG_THROW( Exception::ERR_INTERNAL_ERROR,
					  std::string( "Error loading texture from TextureData" ) +
					  " (Ogre::Image failed to load the pixel buffer)",
					  "OgreTexture::loadFromTextureData" );
		}

		std::stringstream ss;
		ss << "_Memory:";
		ss << ( void* )this;
		std::string tmpName = ss.str();

		Ogre::TexturePtr tmpTexture;
		try {
			tmpTexture = Ogre::TextureManager::getSingleton().loadImage( tmpName, //I dub thee...
						 groupName, //whatever resource group we were told
						 tmpImg, //have an image
						 TEX_TYPE_2D, //yep, 2D texture
						 0, //mipmap hasn't changed (they are still for Ninnies)
						 1.0f, //i'm allergic to gamma
						 false );
		} catch ( Ogre::Exception e ) {
			OG_THROW( Exception::ERR_INTERNAL_ERROR,
					  std::string( "Error loading texture from TextureData" ) +
					  " (Ogre::TextureManager::loadImage failed to load the Image)",
					  "OgreTexture::loadFromTextureData" );
		}

		if ( !tmpTexture.isNull() ) {
			mOgreTexturePtr = tmpTexture;
			mOgreTexturePtr->setFormat( pFmt );
			_setSize( IVector2( mOgreTexturePtr->getWidth(), mOgreTexturePtr->getHeight() ) );
			_setName( mOgreTexturePtr->getName() );
			mNotOwner = false; //you build it, you own it
		}
	}
	//#####################################################################
	const Ogre::String& OgreStaticTexture::getOgreTextureName() const {
		return mOgreTexturePtr->getName();
	}
	//#####################################################################


//////////////////////////////////////////////////////////////////////////
//## OgreRenderTexture
//////////////////////////////////////////////////////////////////////////
	const Ogre::String& OgreRenderTexture::getOgreTextureName() const {
		return mOgreTexturePtr->getName();
	}
	//#####################################################################
	OgreRenderTexture::OgreRenderTexture( const IVector2& size ) {
		mOgreViewport = 0;

		std::stringstream ss;
		ss << "_OGRTT:" << this;
		unsigned int width = size.x;
		unsigned int height = size.y;

		Ogre::TexturePtr tmpTexture;
		try {
			tmpTexture = Ogre::TextureManager::getSingleton().createManual(
							 ss.str().c_str(), // texture name
							 OPENGUI_PRIVATE_RESOURCEGROUP, // resource group
							 Ogre::TEX_TYPE_2D, // 2d texture
							 width, // texture width
							 height, // texture height
							 0, // no mipmaps for RenderTextures please
							 Ogre::PF_BYTE_RGBA, // we need full RGBA for render textures
							 Ogre::TU_RENDERTARGET | Ogre::TU_STATIC_WRITE_ONLY, // it's a render target, and we promise never to try to read it back
							 0 // no resource loader to fall back on
						 );
		} catch ( Ogre::Exception e ) {
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "Failed to create RenderTexture", __FUNCTION__ );
		}

		if ( !tmpTexture.isNull() ) {
			mOgreTexturePtr = tmpTexture;
			unsigned int trueWidth = tmpTexture->getWidth();
			unsigned int trueHeight = tmpTexture->getHeight();
			mMaxUVs.x = ( float )width / ( float )trueWidth;
			mMaxUVs.y = ( float )height / ( float )trueHeight;
			//create a viewport to the rendering area. We'll need it later
			Ogre::RenderTexture* rt = mOgreTexturePtr->getBuffer()->getRenderTarget();
			mOgreViewport = rt->addViewport( 0, // no cameras, please
											 0, // z-order 0 sounds good
											 0.0f, 0.0f, // upper left works
											 mMaxUVs.x, mMaxUVs.y ); // lower right works

			// store the size and name for OpenGUI to use later
			_setSize( size );
			_setName( mOgreTexturePtr->getName() );
		}
	}
	//#####################################################################
	OgreRenderTexture::~OgreRenderTexture() {
		if ( !mOgreTexturePtr.isNull() ) {
			Ogre::TextureManager::getSingleton().remove( mOgreTexturePtr->getHandle() );
			mOgreTexturePtr.setNull();
		}
	}
	//#####################################################################
	Ogre::Viewport* OgreRenderTexture::getOgreViewport() const {
		return mOgreViewport;
	}
	//#####################################################################
}//namespace OpenGUI{


