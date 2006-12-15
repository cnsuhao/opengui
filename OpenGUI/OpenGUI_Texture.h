// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef C4152441_F250_46dd_958F_D1007688400A
#define C4152441_F250_46dd_958F_D1007688400A

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_RefObject.h"

namespace OpenGUI {
	class TextureManager; //forward declaration

	/*! \brief
		This is a base class for custom Texture implementations. Custom Renderer
		implementations will also quite likely include a custom Texture
		implementation to deal with API specific texture handling.

		\note All Rendered implementations will need to create a subclass of this
			in order to access the protected data members. Setting the values of
			these protected members is a required function of Renderer implementations.
	*/
	class OPENGUI_API Texture: public RefObject {
		friend class TextureManager;
	public:
		//! Textures should only be created by Renderer implementations.
		Texture() {}
		//! Textures should only be destroyed by Renderer implementations.
		virtual ~Texture() {}

		//! Returns the name of the texture.
		/*! This will be the texture source filename if the texture was loaded from a file.
			Otherwise its value is undefined.
			\deprecated
			This function is hardly used in OpenGUI, seemingly only for a few logging operations.
			It may be later decided that tracking the source filename for a texture is the
			complete responsibility of the Renderer, in which case this function would either be
			altered or removed. This would affect _setName() as well.
		*/
		const std::string& getName() const;

		//! Returns the size of the texture, in pixels
		/*! The returned size is the same value as set by the Renderer during texture creation via _setSize() */
		const IVector2& getSize() const {
			return mTextureSize;
		}

		//! Populates the given floats with the UV bounds of this RenderTexture
		/*! The default return values are 1.0f,1.0f. This function exists so that if
		the a texture implementation requires different UV ranges, it can be
		provided by the subclass. An example of this is rectangle textures, which
		map the UVs directly to the width and height of the texture.
		\note OpenGUI currently does \b not use this function when calculating UVs.
		All UVs are assumed to scale from 0.0f to 1.0f across the range defined by
		getSize(). This function is currently just presented for internal tracking
		for Renderer implementations.
		\deprecated
		Because this function is not used internally within %OpenGUI, it will likely
		either be removed in the future, or its value will begin being used.
		*/
		virtual void getUVs( float& max_u, float& max_v );

		//! returns \c true if this object is a RenderTexture, \c false otherwise
		virtual bool isRenderTexture();
	protected:
		//! It is required that this be set to the source filename by custom Renderers
		/*! This sets what is mostly a symbolic name for a texture that is only used
		currently by a few logging functions. See getName() for more information.
		\deprecated
		This function would be removed if Texture::getName() is removed. */
		void _setName( const std::string& name ) {
			mTextureName = name;
		}
		//! It is required that this be set to the texture dimensions by custom Renderers
		/*! It is important to note that this does \b not have to be the true size of the
		texture. In fact, there are specific cases where it is beneficial (and required)
		to provide inaccurate information to this function. Specifically, the instance may occur
		where a loaded texture or render texture cannot be properly created at the desired size as
		a result of lack of support for non power of 2 textures in the underlying hardware. For these
		cases the recommended action is to either fully scale the texture so that it becomes a PO2
		(power of 2) size, or alternatively to load the texture contents at the desired NPO2 size but
		place the actual content into a PO2 texture (leaving the rest of the texture area unused).
		For both solutions, the size provided to this function should be the original size requested
		even though it is technically inaccurate. This is necessary for both textures from files as
		well as textures from memory and render textures because the embedded texture size is used
		to calculate information within &OpenGUI, such as imagery UVs from pixel rects and pixel
		alignment calculations. */
		void _setSize( const IVector2& size ) {
			mTextureSize = size;
		}


	private:
		virtual void finalize(); //finalizer from RefObject
		std::string mTextureName;
		IVector2 mTextureSize;
	};

	//! A self deleting reference counted pointer for Texture objects
	typedef RefObjHandle<Texture> TexturePtr;
}
;//namespace OpenGUI{
#endif
