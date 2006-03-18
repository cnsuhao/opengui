
#include "tinyxml.h"
#include "UnknownImage.h"
#include "OpenGUI.h"

namespace OpenGUI{
	template<> ImageryManager* Singleton<ImageryManager>::mptr_Singleton = 0;
	ImageryManager& ImageryManager::getSingleton(void)
	{
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	ImageryManager* ImageryManager::getSingletonPtr(void)
	{
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	//############################################################################
	ImageryManager::ImageryManager()
	{
		LogManager::SlogMsg("INIT", OGLL_INFO2) << "Creating ImageryManager" << Log::endlog;
		mDefaultImageset=0;
		__buildDefaultImageset();
	}
	//############################################################################
	ImageryManager::~ImageryManager()
	{
		LogManager::SlogMsg("SHUTDOWN", OGLL_INFO2) << "Destroying ImageryManager" << Log::endlog;
		ImageryManager::destroyAllImagesets();
		__destroyDefaultImageset();
	}
	//############################################################################
	Imageset* ImageryManager::createImageset(std::string imageFilename)
	{
		Imageset* imgset;
		if( (imgset = getImageset(imageFilename)) ){
			return imgset;
		}

		LogManager::SlogMsg("ImageryManager", OGLL_INFO2) << "CreateImageset: " << imageFilename << Log::endlog;
		
		Texture* tex = System::getSingleton()._getRenderer()->createTextureFromFile(imageFilename);
		if(!tex) return 0;

		imgset = new Imageset(tex,imageFilename);
		if(!imgset){
			System::getSingleton()._getRenderer()->destroyTexture(tex);
			return 0;
		}

		mImagesetList.push_back(imgset);
		return imgset;
	}
	//############################################################################
	Imageset* ImageryManager::getImageset(std::string imageFilename)
	{
		ImagesetCPtrList::iterator iter = mImagesetList.begin();
		while(iter != mImagesetList.end())
		{
			if((*iter)->getName() == imageFilename){
				return (*iter);
			}
			iter++;
		}
		return 0;
	}
	//############################################################################
	void ImageryManager::destroyImageset(Imageset* pImageset)
	{
		ImagesetCPtrList::iterator iter = mImagesetList.begin();
		while(iter != mImagesetList.end())
		{
			if((*iter) == pImageset){
				LogManager::SlogMsg("ImageryManager", OGLL_INFO2) << "DestroyImageset: " << pImageset->getName() << Log::endlog;
				delete pImageset;
				mImagesetList.erase(iter);
				return;
			}
			iter++;
		}
	}
	//############################################################################
	void ImageryManager::destroyImageset(std::string imageFilename)
	{
		Imageset* imgset;
		imgset = ImageryManager::getImageset(imageFilename);
		if(imgset){
			ImageryManager::destroyImageset(imgset);
		}
	}
	//############################################################################
	void ImageryManager::destroyAllImagesets()
	{
		LogManager::SlogMsg("ImageryManager", OGLL_INFO2) << "DestroyAllImagesets..." << Log::endlog;
		ImagesetCPtrList::iterator iter = mImagesetList.begin();
		while(iter != mImagesetList.end()){
			delete (*iter);
			iter++;
		}
		mImagesetList.empty();
	}
	//############################################################################
	void ImageryManager::__buildDefaultImageset()
	{
		TextureData texdata;
		texdata.setData(::builtinDefaultImage.width,
						::builtinDefaultImage.height,
						::builtinDefaultImage.bytes_per_pixel,
						(void*)::builtinDefaultImage.pixel_data);

		Texture* texture =  System::getSingleton()._getRenderer()->createTextureFromTextureData(&texdata);
		mDefaultImageset = new Imageset(texture,"");
	}
	//############################################################################
	void ImageryManager::__destroyDefaultImageset()
	{
		if(mDefaultImageset)
			delete mDefaultImageset;
		mDefaultImageset = 0;
	}
	//############################################################################
	Imageset* ImageryManager::__getDefaultImageset()
	{
		return mDefaultImageset;
	}
	//############################################################################
	ImageryPtr ImageryManager::getImagery(std::string imageryName)
	{
		ImagesetCPtrList::iterator iter = mImagesetList.begin();
		while(iter != mImagesetList.end()){
			ImageryPtr retptr = (*iter)->getImagery(imageryName);
			if(retptr)
				return retptr;
			iter++;
		}
		return ImageryPtr(0);
	}
	//############################################################################
	void ImageryManager::LoadImagesetsFromXML(std::string xmlFilename)
	{
		LogManager::SlogMsg("ImageryManager", OGLL_INFO) << "LoadImagesetsFromXML: " << xmlFilename << Log::endlog;

		TiXmlDocument doc;
		doc.LoadFile(xmlFilename);
		TiXmlElement* root = doc.RootElement();
		TiXmlElement* section;
		section = root;
		if(section){
			do{
				//iterate through all of the root level elements and react to every "Imageset" found
				if(0 == strcmpi(section->Value(),"imageset")){
					ImageryManager::_loadImagesetFromTinyXMLElement(section);
				}
			}while( (section = section->NextSiblingElement()) );
		}
		
	}
	//############################################################################
	Imageset* ImageryManager::_loadImagesetFromTinyXMLElement(void* tXelementPtr)
	{
		TiXmlElement* tXelement = (TiXmlElement*)tXelementPtr;
		Imageset* resultImageset=0;
		const char* imgFilename = 0;
		TiXmlAttribute* attrib = tXelement->FirstAttribute();
		if(attrib){
			do{
				if(0 == strcmpi(attrib->Name(),"sourceimage")){
					imgFilename = attrib->Value();
					break;
				}
			}while( (attrib = attrib->Next()) );
		}

		if(imgFilename){
			resultImageset = createImageset(imgFilename);
			if(resultImageset)
				resultImageset->_loadImageryFromRootTinyXMLElement(tXelement);
		}
		return resultImageset;
	}
	//############################################################################
}; //namespace OpenGUI{





