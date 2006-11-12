// -----------------------------------------------------------------------------
// Renderer_Ogre_Texture.h
// -----------------------------------------------------------------------------

#ifndef	_H_OGR_OGRE_TEXTURE
#define _H_OGR_OGRE_TEXTURE

#include "Renderer_Ogre_Exports.h"

#include "OpenGUI.h"

#include <OgreTextureManager.h>

namespace OpenGUI {
	//! An OpenGUI::Texture implementation used by OgreRenderer to load and represent Ogre textures.
	class OGR_OGRE_API OgreTexture : public Texture {
		friend class OgreRenderer;
	public:
		OgreTexture(): mNotOwner( false ) {}
		virtual ~OgreTexture() {
			freeOgreTexture();
		}
	protected:
		//! loads a new texture from a file
		void loadFile( const std::string& filename, const std::string& resourceGroup );
		//! assigns an existing Ogre texture to this object
		void loadOgreTexture( Ogre::TexturePtr ogreTexture );
		//! load a texture with the contents of an OpenGUI TextureData object (aka: from memory)
		void loadFromTextureData( const TextureData* textureData, const std::string& groupName );
		//! frees the attached Ogre texture. Infinitely recallable
		void freeOgreTexture();
		//! Returns the name of this texture as held by Ogre
		const Ogre::String& getOgreTextureName() const;
		//! Returns true if this texture object is currently representing an Ogre texture.
		bool validOgreTexture() {
			return !mOgreTexturePtr.isNull();
		}
	private:
		bool mNotOwner; // true if we do not own the ogre texture we're reference, so we won't destroy it
		Ogre::TexturePtr mOgreTexturePtr; //TexturePtr from Ogre
	};
}
;//namespace OpenGUI{


#endif // _H_OGR_OGRE_TEXTURE
