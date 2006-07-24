// -----------------------------------------------------------------------------
// OgreFusion_Texture.h
// -----------------------------------------------------------------------------

#ifndef	_H_OGREFUSION_TEXTURE
#define _H_OGREFUSION_TEXTURE

#include "OgreFusion_Exports.h"

#include "OpenGUI.h"

namespace OpenGUI{
	class OGREFUSION_API OgreTexture : public Texture
	{
		friend class OgreRenderer;
	public:
		OgreTexture() {}
		virtual ~OgreTexture() {}
	};
};//namespace OpenGUI{


#endif // _H_OGREFUSION_TEXTURE
