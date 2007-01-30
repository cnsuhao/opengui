// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#ifndef BA1CEEE2_F04D_4c9e_9CAA_4DEE68E17D77
#define BA1CEEE2_F04D_4c9e_9CAA_4DEE68E17D77
#include <OpenGUI.h>
#include "OpenGUI_Viewport.h"

namespace OpenGUI {
	class Renderer_OpenGL;
	class OGLRTexture;

	//###########################################################
	class OGL_Viewport: public Viewport {
		friend class Renderer_OpenGL;
	public:
		virtual OGLRTexture* getRenderTexture()const = 0;
	protected:
		OGL_Viewport() {}
		virtual ~OGL_Viewport() {}
		virtual void preUpdate( Screen *updatingScreen ) {}
		virtual void  postUpdate( Screen *updatingScreen ) {}
	};
	//###########################################################
	class OGL_Default_Viewport: public OGL_Viewport {
		friend class Renderer_OpenGL;
	public:
		OGL_Default_Viewport() {}
		virtual ~OGL_Default_Viewport() {}
		virtual const IVector2& getSize() {
			return mSize;
		}
		virtual OGLRTexture* getRenderTexture()const {
			return 0;
		}
	protected:
		void setSize( const IVector2& size ) {
			mSize = size;
		}

	private:
		IVector2 mSize;
	};
	//###########################################################
	class OGL_RTT_Viewport: public OGL_Viewport {
		friend class Renderer_OpenGL;
	public:
		virtual OGLRTexture* getRenderTexture()const {
			return mRenderTexture;
		}
	protected:
		OGL_RTT_Viewport( const IVector2& size );
		virtual ~OGL_RTT_Viewport() {}
		virtual const IVector2& getSize();

		virtual void preUpdate( Screen *updatingScreen ) {}
		virtual void  postUpdate( Screen *updatingScreen ) {}
	private:
		OGLRTexture* mRenderTexture;
		RenderTexturePtr mRenderTexturePtr; //same as mRenderTexture, just held in a RefObjectPtr to prevent premature destruction
	};
	//###########################################################
}

#endif // BA1CEEE2_F04D_4c9e_9CAA_4DEE68E17D77
