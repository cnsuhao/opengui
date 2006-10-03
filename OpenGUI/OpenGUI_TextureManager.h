#ifndef E7C6D975_96DE_4E7B_BC8B_15FA981B1FEF
#define E7C6D975_96DE_4E7B_BC8B_15FA981B1FEF

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_Exports.h"

#include "OpenGUI_Texture.h"
#include "OpenGUI_RenderTexture.h"

#include "OpenGUI_Iterators.h"

namespace OpenGUI {
	class Renderer; //forward declaration
	class System; //forward declaration
	class TextureData; //forward declaration

	/*! \brief
	Provides a common interface for creating textures from various sources.
	\n \b [Singleton]
	*/
	class OPENGUI_API TextureManager : public Singleton<TextureManager> {
		friend class System;
		friend class Texture;
	public:
		typedef std::list<Texture*> TextureCPtrList;
		typedef ListIterator<TextureCPtrList, TextureCPtrList::iterator> iterator;
		typedef ListIterator<TextureCPtrList, TextureCPtrList::const_iterator> const_iterator;

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static TextureManager& getSingleton( void );

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static TextureManager* getSingletonPtr( void );

		//! create a new texture. \c filename will be used at the texture name
		TexturePtr createTextureFromFile( const std::string& filename );
		//! create a new texture from memory
		TexturePtr createTextureFromTextureData( const std::string& name, TextureData* textureData );
		//! Replace the given texture's contents with the contents of the given TextureData
		void updateTextureFromTextureData( TexturePtr texturePtr, TextureData* textureData );

		//! returns an iterator to walk the current list of Textures
		iterator getIterator() {
			return iterator( mTextureCPtrList.begin(), mTextureCPtrList.end() );
		}
	protected:
		//only allow creation and destruction by System
		TextureManager( Renderer* renderer );
		~TextureManager();

		//! Free the given texture from the TextureManager and call Renderer->destroyTexture
		/*! Called automatically by Texture objects when they have no further handles pointing to them */
		void destroyTexture( Texture* texturePtr );
	private:
		// destroys all textures
		void destroyAllTextures();
		Renderer* mRenderer;


		TextureCPtrList mTextureCPtrList;
	};

} //namespace OpenGUI {

#endif // E7C6D975_96DE_4E7B_BC8B_15FA981B1FEF
