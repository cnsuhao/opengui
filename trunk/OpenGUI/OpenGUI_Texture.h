#ifndef C4152441_F250_46dd_958F_D1007688400A
#define C4152441_F250_46dd_958F_D1007688400A

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_RefPtr.h"

namespace OpenGUI {
	class Renderer; //forward declaration

	/*! \brief
		This is a base class for custom Texture implementations. Custom Renderer
		implementations will also quite likely include a custom Texture
		implementation to deal with API specific texture handling.

		\note All Rendered implementations will need to create a subclass of this
			in order to access the protected data members. Setting the values of
			these protected members is a required function of Renderer implementations.
	*/
	class OPENGUI_API Texture {
	public:
		//! Textures should only be created by Renderer implementations.
		/*! The \c owner is a pointer to the renderer that created the texture.
			It is later used to call renderer->destroyTexture()
		*/
		Texture( Renderer* renderer );
		//! Textures automatically call Renderer::destroyTexture() during destruction if necessary
		virtual ~Texture();

		//! Returns the name of the texture.
		/*! This will be the texture source filename if the texture was loaded from a file.
			Otherwise its value is undefined.
		*/
		virtual std::string getName();
		//! Returns the size of the texture, in pixels
		IVector2 getSize() {
			return mTextureSize;
		}
	protected:
		std::string mTextureName;//!<It is required that this be set to the source filename by custom Renderers
		IVector2 mTextureSize;//!<It is required that this be set to the texture dimensions by custom Renderers
	private:
		bool mValid;
		Renderer* mRenderer;
	};

	//! A self deleting reference counted pointer for Texture objects
	typedef RefPtr<Texture> TexturePtr;
}
;//namespace OpenGUI{
#endif
