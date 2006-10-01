#include "OpenGUI_TextureManager.h"
#include "OpenGUI_Renderer.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	//############################################################################
	template<> TextureManager* Singleton<TextureManager>::mptr_Singleton = 0;
	//############################################################################
	TextureManager& TextureManager::getSingleton( void ) {
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	TextureManager* TextureManager::getSingletonPtr( void ) {
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	//############################################################################
	TextureManager::TextureManager( Renderer* renderer ) {
		mRenderer = renderer;
	}
	//############################################################################
	TextureManager::~TextureManager() {
		destroyAllTextures();
	}
	//############################################################################
	TexturePtr TextureManager::createTextureFromFile( const std::string& filename ) {
		Texture* tex = mRenderer->createTextureFromFile( filename );
		mTextureCPtrList.push_front( tex );
		return TexturePtr( tex );
	}
	//############################################################################
	TexturePtr TextureManager::createTextureFromTextureData( const std::string& name, TextureData* textureData ) {
		Texture* tex = mRenderer->createTextureFromTextureData( textureData );
		tex->_setName( name );
		mTextureCPtrList.push_front( tex );
		return TexturePtr( tex );
	}
	//############################################################################
	void TextureManager::updateTextureFromTextureData( TexturePtr texturePtr, TextureData* textureData ) {
		Texture* tex;
		tex = texturePtr.get();
		mRenderer->updateTextureFromTextureData( tex, textureData );
	}
	//############################################################################
	void TextureManager::destroyTexture( Texture* texturePtr ) {
		mTextureCPtrList.remove( texturePtr );
		mRenderer->destroyTexture( texturePtr );
	}
	//############################################################################
	void TextureManager::destroyAllTextures() {
		Texture* tex;
		while ( mTextureCPtrList.size() > 0 ) {
			tex = mTextureCPtrList.front();
			mTextureCPtrList.pop_front();
			mRenderer->destroyTexture( tex );
		}
	}
	//############################################################################
}//namespace OpenGUI{