// -----------------------------------------------------------------------------
// OgreFusion_Renderer.cpp
// -----------------------------------------------------------------------------

#include "OgreFusion_Renderer.h"
#include "OgreFusion_Texture.h"

#include "Ogre.h"

namespace OpenGUI{
	//#####################################################################
	OgreRenderer::OgreRenderer(){
	}
	//#####################################################################
	OgreRenderer::~OgreRenderer(){
	}
	//#####################################################################

	void OgreRenderer::getViewportDimensions(IVector2& dims){
	}
	//#####################################################################
	void OgreRenderer::getScreenDimensions(IVector2& dims){
	}
	//#####################################################################
	void OgreRenderer::preRenderSetup(){
	}
	//#####################################################################
	void OgreRenderer::doRenderOperation(Render::RenderOperation& renderOp){
	}
	//#####################################################################
	void OgreRenderer::postRenderCleanup(){
	}
	//#####################################################################
	Texture* OgreRenderer::createTextureFromFile(std::string filename){
		OgreTexture* tex = new OgreTexture();
		tex->mTextureName = filename;
		tex->mTextureSize = IVector2(0,0);
		return tex;
	}
	//#####################################################################
	Texture* OgreRenderer::createTextureFromTextureData(TextureData *textureData){
		OgreTexture* tex = new OgreTexture();
		tex->mTextureName = "#TextureFromMemory#";
		tex->mTextureSize = IVector2(0,0);
		return tex;
	}
	//#####################################################################
	void OgreRenderer::updateTextureFromTextureData(Texture* texture, TextureData *textureData){
	}
	//#####################################################################
	void OgreRenderer::destroyTexture(Texture* texturePtr){
		delete texturePtr;
	}
	//#####################################################################
}

