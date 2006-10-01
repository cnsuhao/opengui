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
		Texture(){}
		//! Textures should only be destroyed by Renderer implementations.
		virtual ~Texture(){}

		//! Returns the name of the texture.
		/*! This will be the texture source filename if the texture was loaded from a file.
			Otherwise its value is undefined.
		*/
		virtual const std::string& getName() const;

		//! Returns the size of the texture, in pixels
		const IVector2& getSize() const {
			return mTextureSize;
		}

		//! returns \c true if this object is a RenderTexture, \c false otherwise
		virtual bool isRenderTexture();
	protected:
		//! It is required that this be set to the source filename by custom Renderers
		void _setName(const std::string& name){mTextureName = name;}
		//! It is required that this be set to the texture dimensions by custom Renderers
		void _setSize(const IVector2& size){mTextureSize = size;}

		
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
