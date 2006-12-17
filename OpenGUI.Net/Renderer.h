// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Renderer_h__
#define Renderer_h__

using namespace System;

namespace OpenGUI_Net {
	ref class Texture;
	ref class Viewport;
	ref class RenderOperation;
	ref class TextureData;

	public ref class Renderer abstract {
	public:
		virtual void selectViewport( Viewport ^ activeViewport ) = 0;
		virtual void preRenderSetup() = 0;
		virtual void doRenderOperation( RenderOperation ^ renderOp ) = 0;
		virtual void postRenderCleanup() = 0;
		virtual Texture ^ createTextureFromFile( String ^ fileName ) = 0;
		virtual Texture ^ createTextureFromTextureData( const TextureData ^ textureData ) = 0;
		virtual void updateTextureFromTextureData( Texture ^ texture, const TextureData ^ textureData ) = 0;
		virtual void destroyTexture( Texture ^ texturePtr ) = 0;

	};
} // namespace OpenGUI_Net {

#endif // Renderer_h__