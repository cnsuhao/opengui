#include "OpenGUI_TextureManager.h"
#include "OpenGUI_Renderer.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_LogSystem.h"

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
		LogManager::SlogMsg( "INIT", OGLL_INFO2 ) << "Creating TextureManager" << Log::endlog;
		mRenderer = renderer;
	}
	//############################################################################
	TextureManager::~TextureManager() {
		LogManager::SlogMsg( "SHUTDOWN", OGLL_INFO2 ) << "Destroying TextureManager" << Log::endlog;
		destroyAllTextures();
	}
	//############################################################################
	TexturePtr TextureManager::createTextureFromFile( const std::string& filename ) {
		LogManager::SlogMsg( "TextureManager", OGLL_INFO2 ) << "Create Texture from File: " << filename << Log::endlog;
		Texture* tex = mRenderer->createTextureFromFile( filename );
		mTextureCPtrList.push_front( tex );
		return TexturePtr( tex );
	}
	//############################################################################
	TexturePtr TextureManager::createTextureFromTextureData( const std::string& name, TextureData* textureData ) {
		LogManager::SlogMsg( "TextureManager", OGLL_INFO2 ) << "Create Texture from TextureData: "
		<< name
		<< " (0x" << ( unsigned int ) textureData << ")"
		<< Log::endlog;
		Texture* tex = mRenderer->createTextureFromTextureData( textureData );
		tex->_setName( name );
		mTextureCPtrList.push_front( tex );
		return TexturePtr( tex );
	}
	//############################################################################
	void TextureManager::updateTextureFromTextureData( TexturePtr texturePtr, TextureData* textureData ) {
		LogManager::SlogMsg( "TextureManager", OGLL_INFO2 ) << "Update Texture from TextureData: "
		<< texturePtr->getName()
		<< " (0x" << ( unsigned int ) textureData << ")"
		<< Log::endlog;

		Texture* tex;
		tex = texturePtr.get();
		mRenderer->updateTextureFromTextureData( tex, textureData );
	}
	//############################################################################
	void TextureManager::destroyTexture( Texture* texturePtr ) {
		LogManager::SlogMsg( "TextureManager", OGLL_INFO2 ) << "DestroyTexture: " << texturePtr->getName() << Log::endlog;
		mTextureCPtrList.remove( texturePtr );
		mRenderer->destroyTexture( texturePtr );
	}
	//############################################################################
	void TextureManager::destroyAllTextures() {
		LogManager::SlogMsg( "TextureManager", OGLL_INFO2 ) << "DestroyAllTextures..." << Log::endlog;
		Texture* tex;
		while ( mTextureCPtrList.size() > 0 ) {
			tex = mTextureCPtrList.front();
			mTextureCPtrList.pop_front();
			mRenderer->destroyTexture( tex );
		}
	}
	//############################################################################
}//namespace OpenGUI{