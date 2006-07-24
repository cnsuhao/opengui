// -----------------------------------------------------------------------------
// OgreFusion_Texture.h
// -----------------------------------------------------------------------------

#ifndef	_H_OGREFUSION_TEXTURE
#define _H_OGREFUSION_TEXTURE

#include "OgreFusion_Exports.h"

#include "OpenGUI.h"

#include <OgreTextureManager.h>

namespace OpenGUI{
	class OGREFUSION_API OgreTexture : public Texture
	{
		friend class OgreRenderer;
	public:
		OgreTexture():mNotOwner(false) {}
		virtual ~OgreTexture() {freeOgreTexture();}
	protected:
		//! loads a new texture from a file
		void loadFile(const std::string& filename, const std::string& resourceGroup);
		//! assigns an existing Ogre texture to this object
		void loadOgreTexture(Ogre::TexturePtr ogreTexture);
		//! load a texture with the contents of an OpenGUI TextureData object (aka: from memory)
		void loadFromTextureData(TextureData* textureData, const std::string& groupName);
		//! frees the attached Ogre texture. Infinitely recallable
		void freeOgreTexture();
		const Ogre::String& getOgreTextureName() const;
		bool validOgreTexture(){return !mOgreTexturePtr.isNull();}
	private:
		bool mNotOwner; // true if we do not own the ogre texture we're reference, so we won't destroy it
		Ogre::TexturePtr mOgreTexturePtr; //TexturePtr from Ogre
	};
};//namespace OpenGUI{


#endif // _H_OGREFUSION_TEXTURE
