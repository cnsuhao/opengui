
#include "tinyxml.h"
#include "OpenGUI.h"

namespace OpenGUI{

	//############################################################################
	Imageset::~Imageset()
	{
		Imageset::destroyAllImagery();
		_unloadTexture();
	}
	//############################################################################
	bool Imageset::_loadTexture()
	{
		mpTexture = System::getSingleton()._getRenderer()->createTextureFromFile(mFilename);
		if(mpTexture) return true;
		return false;
	}
	//############################################################################
	void Imageset::_unloadTexture()
	{
		if(mpTexture){
			System::getSingleton()._getRenderer()->destroyTexture(mpTexture);
			mpTexture=0;
		}
	}
	//############################################################################
	std::string Imageset::getName()
	{
		return mFilename;
	}
	//############################################################################
	ImageryPtr Imageset::createImagery(std::string imageryName)
	{
		return Imageset::createImagery(imageryName, FRect(0.0f,0.0f,1.0f,1.0f));
	}
	//############################################################################
	ImageryPtr Imageset::createImagery(std::string imageryName, FRect areaRect)
	{
		if(Imageset::getImagery(imageryName)){
			//this function redefines existing imagery with clashing names
			destroyImagery(imageryName);
		}

		ImageryPtr imgptr = new Imagery();
		imgptr->mParentImageset = this;
		imgptr->mAreaRect = areaRect;
		imgptr->mName = imageryName;
		mChildImageryList.push_back(imgptr);
		return imgptr;
	}
	//############################################################################
	ImageryPtr Imageset::createImagery(std::string imageryName, IRect areaRect)
	{
		if(!mpTexture) //if this imageset has no texture, then use the default createImage (which uses full image extents for UVs)
			return Imageset::createImagery(imageryName);

		//convert the IRect pixels into UV addresses and pass it along
		IVector2 texSize = mpTexture->getSize();
		FRect frect;
		frect.min.x = ((float)areaRect.min.x) / ((float)texSize.x);
		frect.min.y = ((float)areaRect.min.y) / ((float)texSize.y);
		frect.max.x = ((float)areaRect.max.x) / ((float)texSize.x);
		frect.max.y = ((float)areaRect.max.y) / ((float)texSize.y);
		return Imageset::createImagery(imageryName,frect);
	}
	//############################################################################
	void Imageset::destroyImagery(ImageryPtr imageryPtr)
	{
		Imageset::destroyImagery(imageryPtr.get());
	}
	//############################################################################
	void Imageset::destroyImagery(Imagery* pImagery)
	{
		ImageryPtrList::iterator iter = mChildImageryList.begin();
		while(mChildImageryList.end() != iter){
			if((*iter).get() == pImagery){
// 				if(this != ImageryManager::getSingleton().__getDefaultImageset()){
// 					pImagery->mParentImageset=ImageryManager::getSingleton().__getDefaultImageset();
// 					pImagery->mParentImageset->mChildImageryList.push_back(pImagery);
// 					pImagery->mAreaRect=FRect(0.0f,0.0f,1.0f,1.0f);
// 					mChildImageryList.erase(iter);
// 					return;
// 				}else{
					mChildImageryList.erase(iter);
					return;
//				}
			}
			iter++;
		}
	}
	//############################################################################
	void Imageset::destroyImagery(std::string name)
	{
		Imageset::destroyImagery(Imageset::getImagery(name).get());
	}
	//############################################################################
	ImageryPtr Imageset::getImagery(std::string imageryName)
	{
		ImageryPtrList::iterator iter = mChildImageryList.begin();
		while(mChildImageryList.end() != iter){
			if((*iter)->mName == imageryName){
				return ImageryPtr((*iter));
			}
			iter++;
		}
		return ImageryPtr(0);
	}
	//############################################################################
	void Imageset::destroyAllImagery()
	{
		ImageryPtrList tmpList = mChildImageryList;
		ImageryPtrList::iterator iter = tmpList.begin();
		while(tmpList.end() != iter){
			Imageset::destroyImagery((*iter).get());
			iter++;
		}
		mChildImageryList.clear();
	}
	//############################################################################
	void Imageset::_loadImageryFromRootTinyXMLElement(void* tXrootElementPtr)
	{
		TiXmlElement* tXelement = (TiXmlElement*)tXrootElementPtr;
		TiXmlElement* section = tXelement->FirstChildElement();
		if(section){
			do{ //for each <imagery>: test input validity, if everything is good create an imagery from it
				if(0 == strcmpi(section->Value(),"imagery")){
					const char* iname=0;

					const char* xpos=0;
					int xpos_i;

					const char* ypos=0;
					int ypos_i;

					const char* height=0;
					int height_i;

					const char* width=0;
					int width_i;

					TiXmlAttribute* attrib = section->FirstAttribute();
					if(attrib){
						do{ //scan all attributes and keep the ones we actually care about
							if(0 == strcmpi(attrib->Name(),"name"))
								iname = attrib->Value();
							if(0 == strcmpi(attrib->Name(),"xpos") &&
							attrib->QueryIntValue(&xpos_i) == TIXML_SUCCESS )
								xpos = attrib->Value();
							if(0 == strcmpi(attrib->Name(),"ypos") &&
							attrib->QueryIntValue(&ypos_i) == TIXML_SUCCESS )
								ypos = attrib->Value();
							if(0 == strcmpi(attrib->Name(),"width") &&
							attrib->QueryIntValue(&width_i) == TIXML_SUCCESS )
								width = attrib->Value();
							if(0 == strcmpi(attrib->Name(),"height") &&
							attrib->QueryIntValue(&height_i) == TIXML_SUCCESS )
								height = attrib->Value();
						}while(attrib = attrib->Next());
						if(iname && xpos && ypos && width && height){
							//if we manager to acquire all the necessary data, create the imagery object
							IRect irect;
							irect.setPosition(IVector2(xpos_i,ypos_i));
							irect.setSize(IVector2(width_i,height_i));
							createImagery(iname,irect);
						}
					}
				}
			}while(section = section->NextSiblingElement());
		}
	}
	//############################################################################
};//namespace OpenGUI{







