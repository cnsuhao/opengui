// -----------------------------------------------------------------------------
// OgreFusion_Texture.cpp
// -----------------------------------------------------------------------------

#include "OgreFusion_Texture.h"

#include <OgreException.h>

namespace OpenGUI{
	//#####################################################################
	void OgreTexture::loadFile(const std::string& filename, const std::string& resourceGroup){
		using namespace Ogre;
		freeOgreTexture(); //dump any existing texture
		TextureManager* textureManager = TextureManager::getSingletonPtr();

		Ogre::TexturePtr tmpTexture = (Ogre::TexturePtr)textureManager->getByName(filename.c_str());
		try{
			if(!tmpTexture.isNull()){ //check if texture already exists
				mOgreTexturePtr = tmpTexture;
				mNotOwner = true; //we need to make sure we don't destroy it, since we didn't create it
			}else{
				tmpTexture = textureManager->load(filename.c_str(),
					resourceGroup.c_str(), //only look in the resource group we were given
					TEX_TYPE_2D, //we only deal with 2D textures in this neck of the woods
					0, //mipmaps are for Ninnies
					1.0f); //default gamma
				mNotOwner = false; //we own it
			}
		}catch(Ogre::Exception e){
			OG_THROW(Exception::ERR_INTERNAL_ERROR,
				std::string("Error loading texture from file: ") + filename +
				" (Ogre exception caught during load)",
				"OgreTexture::loadFile");
		}

		if(!tmpTexture.isNull()){
			mTextureSize = IVector2( tmpTexture->getWidth(), tmpTexture->getHeight());
			mTextureName = filename;
			mOgreTexturePtr = tmpTexture;
		}else{
			//looks like it didn't load after all
			OG_THROW(Exception::ERR_INTERNAL_ERROR,
				std::string("Error loading texture from file: ") + filename +
				" (Ogre returned a dead texture handle)",
				"OgreTexture::loadFile");
		}
	}
	//#####################################################################
	void OgreTexture::freeOgreTexture(){
		if(!mOgreTexturePtr.isNull()){
			if(!mNotOwner)
				Ogre::TextureManager::getSingleton().remove(mOgreTexturePtr->getHandle());
			mOgreTexturePtr.setNull();
			mNotOwner = false;
			mTextureName = "";
			mTextureSize = IVector2(0,0);
		}
	}
	//#####################################################################
	void OgreTexture::loadOgreTexture(Ogre::TexturePtr ogreTexture){
		using namespace Ogre;
		freeOgreTexture(); //dump any existing texture
		if(!ogreTexture.isNull()){
			mTextureName = ogreTexture->getName(); //best we can do
			mTextureSize = IVector2( ogreTexture->getWidth(), ogreTexture->getWidth());
			mOgreTexturePtr = ogreTexture;
			mNotOwner = true; //we obviously don't own this
		}
	}
	//#####################################################################
	void OgreTexture::loadFromTextureData(TextureData* textureData, const std::string& groupName){
		using namespace Ogre;
		
		freeOgreTexture(); //dump any existing texture
		if(!textureData) return; //stop here if there is no data

		//we're going to cheat on this one
		Image tmpImg;
		PixelFormat pFmt;
		switch(textureData->getBPP()){
			case 3: //RGB
				pFmt = PF_BYTE_RGB; break;
			case 4: //RGBA
				pFmt = PF_BYTE_RGBA; break;
			case 1: // greyscale
				pFmt = PF_A8; break;
		}

		//if we are given a bitmap with only an alpha channel, we need to convert it to RBGA
		unsigned char* pixelData = 0;
		bool autoDelete;
		if(pFmt == PF_A8){
			size_t newSize = textureData->getWidth() * textureData->getHeight() * 4;
			unsigned char* origData = textureData->getPixelData();
			unsigned char* newData = new unsigned char[newSize];
			unsigned char* newPtr; //we use this later
			for(	int i = 0; 
					i < textureData->getWidth() * textureData->getHeight(); 
					i++)
			{
				
				newPtr = &(newData[i * 4]);
				newPtr[0] = 255; //new R
				newPtr[1] = 255; //new G
				newPtr[2] = 255; //new B
				newPtr[3] = origData[i]; //keep the old A channel
			}
			
			pFmt = PF_BYTE_RGBA; //and we are now RBGA (yay)
			pixelData = newData; //here's our new data
			autoDelete = true; //and ogre can delete it when it's done with it
		}else{
			pixelData = textureData->getPixelData();
			autoDelete = false; //we'd like to keep our data, thank you
		}

		try{
			tmpImg.loadDynamicImage(pixelData, //pointer to pixel buffer
									textureData->getWidth(), //width
									textureData->getHeight(), //height
									1, // depth = 1 (2D texture)
									pFmt, // pixel format of input
									autoDelete, // autoDelete (signifies if Ogre now owns that memory)
									1, // 1 face (just a 2D texture, cubemaps need not apply)
									0); //mipmaps are still for Ninnies
		}catch(Ogre::Exception e){
			OG_THROW(Exception::ERR_INTERNAL_ERROR,
				std::string("Error loading texture from TextureData") +
				" (Ogre::Image failed to load the pixel buffer)",
				"OgreTexture::loadFromTextureData");
		}

		std::string tmpName = System::getSingleton().generateRandomElementName();

		TexturePtr tmpTexture;
		try{
			tmpTexture = TextureManager::getSingleton().loadImage(	tmpName, //I dub thee...
																	groupName, //whatever resource group we were told
																	tmpImg, //have an image
																	TEX_TYPE_2D, //yep, 2D texture
																	0, //mipmap hasn't changed (they are still for Ninnies)
																	1.0f, //i'm allergic to gamma
																	false);
																	//pFmt==PF_A8?true:false); //i knew i should have put that info somewhere more accessible ;)
		}catch(Ogre::Exception e){
			OG_THROW(Exception::ERR_INTERNAL_ERROR,
				std::string("Error loading texture from TextureData") +
				" (Ogre::TextureManager::loadImage failed to load the Image)",
				"OgreTexture::loadFromTextureData");
		}

		if(!tmpTexture.isNull()){
			mOgreTexturePtr = tmpTexture;
			mOgreTexturePtr->setFormat(PF_BYTE_RGBA );
			mTextureSize = IVector2( mOgreTexturePtr->getWidth(), mOgreTexturePtr->getHeight() );
			mTextureName = mOgreTexturePtr->getName();;
			mNotOwner = false; //you build it, you own it
		}
	}
	//#####################################################################
	const Ogre::String& OgreTexture::getOgreTextureName() const{
		return mOgreTexturePtr->getName();
	}
	//#####################################################################
}//namespace OpenGUI{


