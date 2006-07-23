// -----------------------------------------------------------------------------
// OgreFusion_Renderer.cpp
// -----------------------------------------------------------------------------

#include "OgreFusion_Renderer.h"

#include "Ogre.h"

namespace OpenGUI{
	//#####################################################################
	OpenGUI_OgreRenderer::OpenGUI_OgreRenderer(){
	}
	//#####################################################################
	OpenGUI_OgreRenderer::~OpenGUI_OgreRenderer(){
	}
	//#####################################################################

	void OpenGUI_OgreRenderer::getViewportDimensions(IVector2& dims){
	}
	//#####################################################################
	void OpenGUI_OgreRenderer::getScreenDimensions(IVector2& dims){
	}
	//#####################################################################
	void OpenGUI_OgreRenderer::preRenderSetup(){
	}
	//#####################################################################
	void OpenGUI_OgreRenderer::doRenderOperation(Render::RenderOperation& renderOp){
	}
	//#####################################################################
	void OpenGUI_OgreRenderer::postRenderCleanup(){
	}
	//#####################################################################
	Texture* OpenGUI_OgreRenderer::createTextureFromFile(std::string filename){
		return 0;
	}
	//#####################################################################
	Texture* OpenGUI_OgreRenderer::createTextureFromTextureData(TextureData *textureData){
		return 0;
	}
	//#####################################################################
	void OpenGUI_OgreRenderer::updateTextureFromTextureData(Texture* texture, TextureData *textureData){
	}
	//#####################################################################
	void OpenGUI_OgreRenderer::destroyTexture(Texture* texturePtr){
	}
	//#####################################################################
}

