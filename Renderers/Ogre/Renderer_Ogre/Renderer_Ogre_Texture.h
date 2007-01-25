// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

// -----------------------------------------------------------------------------
// Renderer_Ogre_Texture.h
// -----------------------------------------------------------------------------

#ifndef	_H_OGR_OGRE_TEXTURE
#define _H_OGR_OGRE_TEXTURE

#include "Renderer_Ogre_Exports.h"

#include "OpenGUI.h"

#include <OgreTextureManager.h>

namespace OpenGUI {
	//! Base class for Ogre textures used by OpenGUI
	class OGR_OGRE_API OgreTexture {
	public:
		OgreTexture() {}
		virtual ~OgreTexture() {}
		//! Pass through to OpenGUI::Texture::getUVs
		virtual void getOgreUVScale( float& u, float& v ) = 0;
		//! Returns the name of this texture as held by Ogre
		virtual const Ogre::String& getOgreTextureName() const = 0;
	};

	//! An OpenGUI::Texture implementation used by OgreRenderer to load and represent Ogre textures.
	class OGR_OGRE_API OgreStaticTexture: public OgreTexture, public Texture {
	public:
		OgreStaticTexture(): mNotOwner( false ) {}
		virtual ~OgreStaticTexture() {
			freeOgreTexture();
		}
		//! Returns the name of this texture as held by Ogre
		virtual const Ogre::String& getOgreTextureName() const;
		//! loads a new texture from a file
		void loadFile( const String& filename, const String& resourceGroup );
		//! assigns an existing Ogre texture to this object
		void loadOgreTexture( Ogre::TexturePtr ogreTexture );
		//! load a texture with the contents of an OpenGUI TextureData object (aka: from memory)
		void loadFromTextureData( const TextureData* textureData, const String& groupName );

		virtual void getOgreUVScale( float& u, float& v ) {
			getUVs( u, v );
		}

	protected:
		//! frees the attached Ogre texture. Infinitely recallable
		void freeOgreTexture();
		//! Returns true if this texture object is currently representing an Ogre texture.
		bool validOgreTexture() {
			return !mOgreTexturePtr.isNull();
		}
	private:
		bool mNotOwner; // true if we do not own the ogre texture we're reference, so we won't destroy it
		Ogre::TexturePtr mOgreTexturePtr; //TexturePtr from Ogre
	};

	//! An OpenGUI::RenderTexture implementation used by OgreRenderer to load and represent Ogre render textures.
	class OGR_OGRE_API OgreRenderTexture: public OgreTexture, public RenderTexture {
	public:
		OgreRenderTexture( const IVector2& size );
		virtual ~OgreRenderTexture();
		//! Returns the name of this texture as held by Ogre
		virtual const Ogre::String& getOgreTextureName() const;
		//! Returns the Ogre::Viewport for this render texture
		Ogre::Viewport* getOgreViewport() const;

		virtual void getUVs( float& max_u, float& max_v ) {
			max_u = mMaxUVs.x;
			max_v = mMaxUVs.y;
		}

		virtual void getOgreUVScale( float& u, float& v ) {
			getUVs( u, v );
		}

	private:
		Ogre::TexturePtr mOgreTexturePtr; //TexturePtr from Ogre
		Ogre::Viewport* mOgreViewport;
		FVector2 mMaxUVs;
	};
} // namespace OpenGUI{


#endif // _H_OGR_OGRE_TEXTURE
