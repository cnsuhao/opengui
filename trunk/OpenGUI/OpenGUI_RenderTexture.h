#ifndef A71D801F_7E09_4AF0_ADAE_DAD481AC5450
#define A71D801F_7E09_4AF0_ADAE_DAD481AC5450

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Texture.h"

namespace OpenGUI {
	//! This is a base class for render textures (textures that are valid render targets)
	class OPENGUI_API RenderTexture: public Texture {
	public:
		RenderTexture() {}
		virtual ~RenderTexture() {}
		virtual bool isRenderTexture();

		//! Populates the given floats with the UV bounds of this RenderTexture
		/*! The default return values are 1.0f,1.0f. This function exists so that if
		the render texture implementation requires different UV ranges, it can be
		provided by the subclass. An example of this is rectangle textures, which
		map the UVs directly to the width and height of the texture. */
		virtual void getUVs( float& max_u, float& max_v );
	protected:

	private:
		virtual void finalize(); //finalizer from RefObject
		FVector2 mMaxUVs;
	};

	typedef RefObjHandle<RenderTexture> RenderTexturePtr;
} //namespace OpenGUI {

#endif
