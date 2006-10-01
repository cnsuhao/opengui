#ifndef A71D801F_7E09_4AF0_ADAE_DAD481AC5450
#define A71D801F_7E09_4AF0_ADAE_DAD481AC5450

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_RefPtr.h"

#include "OpenGUI_Texture.h"

namespace OpenGUI {
	//! This is a base class for render textures (textures that are valid render targets)
	class OPENGUI_API RenderTexture: public Texture {
	public:
		RenderTexture( Renderer* renderer ): Texture( renderer ) {}
		virtual ~RenderTexture() {}

	protected:
	private:
	};

	typedef RefPtr<RenderTexture> RenderTexturePtr;
}

#endif
