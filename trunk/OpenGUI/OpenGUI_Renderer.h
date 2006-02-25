#ifndef C7BE5683_7863_41b9_A158_EF352D2B90C4
#define C7BE5683_7863_41b9_A158_EF352D2B90C4
#include "OpenGUI_RenderOperation.h"
#include "OpenGUI_Texture.h"

namespace OpenGUI{
	class TextureData;//forward declaration

	//! Base class for all renderers. Any custom Renderer should inherit this base class.
	class OPENGUI_API Renderer
	{
	public:
		Renderer() {}
		virtual ~Renderer() {}

		//! The renderer implementation must be able to properly supply %OpenGUI with viewport dimensions via this function.
		/*! %OpenGUI requires the viewport dimensions for certain functionality
			to work correctly. This function must fill the given IRect with the
			current dimensions every time it is called, or things \b will break.
			This function is guaranteed to be called during creation of the System object.

			\note In addition, it is highly advisable that renderers call
			alertViewportDimensionsChanged() whenever the viewport dimensions
			change during operation.
		*/
		virtual void getViewportDimensions(IVector2& dims)=0;

		//! Signal the system object that the viewport dimensions have changed so that it may take appropriate action.
		void alertViewportDimensionsChanged();

		//! This is always called by the System exactly once every frame before the calls to doRenderOperation() begin.
		/*! The primary purpose of this is to provide the renderer an opportunity to 
			configure the projection matrix as it feels necessary, as well as set any
			graphics api options that will be used on all (or most) render operations.
		*/
		virtual void preRenderSetup()=0;
		//! This will be called for every render operation that needs to be performed.
		/*! This function is passed a RenderOperation object, by reference, for every
			render operation that needs to take place to properly draw the gui.

			The render operations provided to this function are guaranteed to be:\n
			- Ordered back to front (painter's algorithm).
			- Necessary: all 100% alpha'ed out operations will not make it this far. (Don't bother to validate the data, it has been done for you already)
			- Fully populated as the RenderOperation documentation requires.

			\note Expect this function to be called a LOT. Keep it small, keep it fast.
		*/
		virtual void doRenderOperation(Render::RenderOperation& renderOp)=0;
		//! This is always called by the System exactly once every frame after all of the calls to doRenderOperation() have been completed.
		/*! Much like preRenderSetup(), this gives the renderer an oportunity to perform
			whatever tasks it feels are necessary to return the render system back to a
			usable state for the application.
		*/
		virtual void postRenderCleanup()=0;

		//! This is called whenever a texture needs to be created from a file.
		/*!
			Custom renderers are required to implement this function to provide
			the system a generalized method of referencing a texture. Basically,
			this function is given a file name, and through any amount of smoke
			and magic, the system expects to recieve back a pointer to a Texture
			object that can be later referenced within RenderOperation objects
			that are passed to doRenderOperation(). Most implementations simply
			load the data as necessary for their graphics API and store their
			graphics API specific texture handles in customized Texture objects.
			
			The short explanation is: Texture objects are almost entirely
			for Renderer use only, and as such you can do nearly whatever you want
			with them, so long as they can be used later to signify which texture
			we want drawn on a set of polygons.

			\param filename The filename of the source image data.
			\return A valid pointer to a Texture object on success, or 0 on fail.

			\note Renderer is responsible for managing the memory commited for the
			Texture object. The Renderer must ensure that until destroyTexture()
			is called with the given Texture object, the pointer remains valid.
		*/
		virtual Texture* createTextureFromFile(std::string filename)=0;

		//! Create a texture from a TextureData object (memory)
		/*! The passed in TextureData object does not become the sole property of
			the createTextureFromTextureData() function. So it must not attempt
			to delete it. It is the responsibility of the TextureData creator 
			to clean up the TextureData object when it is no longer needed.
			\b However, the caller \b must guarantee that the given TextureData
			object is valid for the entire lifetime of the texture. Meaning that
			it cannot be deleted until after destroyTexture() has been called to
			destroy the texture that is based upon the TextureData.

		*/
		virtual Texture* createTextureFromTextureData(TextureData *textureData)=0;

		//! Destroy a previously created Texture object.
		/*! Whatever needs to happen to properly destroy a Texture object,
			custom Renderers need to implement that functionality here.

			\note Renderer is responsible for managing the memory commited for the
			Texture object.  If	Texture objects are allocated via the new operator,
			then they should be deleted by this function.
		*/
		virtual void destroyTexture(Texture* texturePtr)=0;
	};
};//namespace OpenGUI{
#endif

