// -----------------------------------------------------------------------------
// OgreFusion_Renderer.h
// -----------------------------------------------------------------------------

#ifndef	_H_OGREFUSION_RENDERER
#define _H_OGREFUSION_RENDERER

#include "OgreFusion_Exports.h"

#include "OpenGUI.h"

namespace OpenGUI{
	class OGREFUSION_API OpenGUI_OgreRenderer: public Renderer
	{
	public:
		OpenGUI_OgreRenderer();
		virtual ~OpenGUI_OgreRenderer();
		virtual void getViewportDimensions(IVector2& dims);
		virtual void getScreenDimensions(IVector2& dims);
		//void alertViewportDimensionsChanged();
		//void alertScreenDimensionsChanged();
		virtual void preRenderSetup();
		virtual void doRenderOperation(Render::RenderOperation& renderOp);
		virtual void postRenderCleanup()=0;
		virtual Texture* createTextureFromFile(std::string filename);
		virtual Texture* createTextureFromTextureData(TextureData *textureData);
		virtual void updateTextureFromTextureData(Texture* texture, TextureData *textureData);
		virtual void destroyTexture(Texture* texturePtr);
	};
}//namespace OpenGUI{

#endif // _H_OGREFUSION_RENDERER
