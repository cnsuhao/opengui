#ifndef C7BE5683_7863_41b9_A158_EF352D2B90C4
#define C7BE5683_7863_41b9_A158_EF352D2B90C4

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Exception.h"

#include "OpenGUI_RenderOperation.h"
#include "OpenGUI_Texture.h"
#include "OpenGUI_RenderTexture.h"

namespace OpenGUI {
	class TextureData;//forward declaration

	//! Base class for all renderers. Any custom Renderer should inherit this base class.
	/*!
		\par "Rendering call order"
		Here's a quick ordered list of what calls you can usually expect to receive during
		rendering loops.
		\code
		- preRenderSetup()
		- selectRenderContext()
		- clearContents()
		- doRenderOperation() (repeats as necessary)
		- selectRenderContext()
		- clearContents()
		- doRenderOperation() (repeats as necessary)
		- postRenderCleanup()
		\endcode

	*/
	class OPENGUI_API Renderer {
	public:
		//! Constructor
		Renderer() {}
		//! virtual Destructor
		virtual ~Renderer() {}

//!\name Required
//@{
		//! The renderer implementation must be able to properly supply %OpenGUI with viewport dimensions via this function.
		/*! %OpenGUI requires the viewport dimensions for certain functionality
			to work correctly. This function must fill the given IVector2 with the
			current dimensions every time it is called, or things \b will break.

			Additionally, renderer implementations should call
			System::notifyViewportDimensionsChanged() to inform %OpenGUI of
			viewport size changes when they occur.
		*/
		virtual void getViewportDimensions( IVector2& dims ) = 0;

		//! This is always called by the System exactly once every frame before the calls to doRenderOperation() begin.
		/*! The primary purpose of this is to provide the renderer an opportunity to
			configure the projection matrix as it feels necessary, as well as set any
			graphics API options that will be used on all (or most) render operations.

			Whether the renderer provides multiple rendering contexts (render to texture)
			or not, the active context after this call should always be the "default context"
			(ie. the whole viewport).
		*/
		virtual void preRenderSetup() = 0;

		//! This will be called for every render operation that needs to be performed.
		/*! This function is passed a RenderOperation object, by reference, for every
			render operation that needs to take place to properly draw the gui.

			The render operations provided to this function are guaranteed to be:\n
			- Ordered back to front (painter's algorithm).
			- Necessary: all 100% alpha'ed out operations will not make it this far. (Don't bother to validate the data, it has been done for you already)
			- Fully populated as the RenderOperation documentation requires.

			\note Expect this function to be called a LOT. Keep it small, keep it fast.
		*/
		virtual void doRenderOperation( RenderOperation& renderOp ) = 0;

		//! This is always called by the System exactly once every frame after all of the calls to doRenderOperation() have been completed.
		/*! Much like preRenderSetup(), this gives the renderer an opportunity to perform
			whatever tasks it feels are necessary to return the render system back to a
			usable state for the application.
		*/
		virtual void postRenderCleanup() = 0;

		//! This is called whenever a texture needs to be created from a file.
		/*! Custom renderers are required to implement this function to provide
			the system a generalized method of creating a texture. Basically,
			this function is given a file name, and through any amount of smoke
			and magic, the system expects to receive back a pointer to a Texture
			object that can be later referenced within RenderOperation objects
			that are passed to doRenderOperation(). Most implementations simply
			load the data as necessary for their graphics API and store their
			graphics API specific texture handles in customized Texture objects.
			
			The short explanation is: Texture objects are almost entirely
			for Renderer use only, and as such you can do nearly whatever you want
			with them, so long as they can be used later to signify which texture
			we want drawn on a set of polygons.

			\param filename The filename of the source image data.
			\return A TexturePtr to a Texture object on success, or TexturePtr(0) on fail.

			\note
			It is expected that all textures are available for use by all rendering contexts.
		*/
		virtual Texture* createTextureFromFile( const std::string& filename ) = 0;

		//! Create a texture from a TextureData object (memory)
		/*! The passed in TextureData object does not become the sole property of
			the createTextureFromTextureData() function. So it must not attempt
			to delete it. It is the responsibility of the TextureData creator 
			to clean up the TextureData object when it is no longer needed.
			The caller \b must guarantee that the given TextureData object
			is valid for the entire lifetime of the texture. Meaning that
			it cannot be deleted until after destroyTexture() has been called to
			destroy the texture that is based upon the TextureData.

			\note
			It is expected that all textures are available for use by all rendering contexts.
		*/
		virtual Texture* createTextureFromTextureData( const TextureData* textureData ) = 0;

		//! Replaces an existing texture with the given TextureData
		/*! This should cause a Renderer implementation to completely replace the
			contents of a texture with the newly provided data. 
			The given \c texture pointer must remain valid, but other than that it doesn't
			matter how this is achieved internally. Renderer implementations can feel
			free to discard their hardware textures and rebuild from scratch if they
			choose.
		*/
		virtual void updateTextureFromTextureData( Texture* texture, const TextureData* textureData ) = 0;

		//! Destroy a previously created Texture object.
		/*! Whatever needs to happen to properly destroy a Texture or RenderTexture object,
			custom Renderers need to implement that functionality here.

			\note This function is called automatically by the TextureManager to destroy
			Texture objects. Since the Renderer created the Texture object (via \c new),
			it is also responsible for performing the \c delete of that Texture. This
			function is called after %OpenGUI is assured that no remaining handles to
			the texture remain, so if the Renderer does not delete the memory here, it
			will leak.

			\attention
			This function is called for both Texture and RenderTexture objects, so if the
			Renderer implementation cares, you will need to determine the difference via
			Texture::isRenderTexture().
		*/
		virtual void destroyTexture( Texture* texturePtr ) = 0;

//@}
//!\name RenderToTexture Support (optional)
//@{
		//! Renderer implementations that do support Render to Texture contexts should \return \c true. The default is to return \c false;
		/*! \attention
		This virtual function has a default implementation.
		This allows renderer implementations that do not support render to texture
		to simply ignore the existence of this function and the correct functionality
		will take place.
		*/
		virtual bool supportsRenderToTexture() {
			return false;
		}

		//! This is called to set the current rendering context.
		/*! Calls to doRenderOperation() that occur after this function is called
		should draw to the RenderTexture that was last sent via this function.

		\attention
		This virtual function has a default implementation.
		This allows renderer implementations that do not support render to texture
		to simply ignore the existence of this function and the correct functionality
		will take place.

		\param
		context A pointer to the render texture that is to become the new context,
		or 0 (NULL) to set the context to the default (viewport) context.

		\note This is not guaranteed to be called every frame. It is only called
		when a context change is absolutely necessary.
		*/
		virtual void selectRenderContext( RenderTexture* context ) {}

		//! Should clear the contents of the current rendering context as appropriate.
		/*! When called, this function should clear the contents of the current
		rendering context.

		\note
		This function is called at the beginning of rendering for each context,
		\b including the default (viewport) context. You probably don't want
		to clear the default context here, as it will erase your previously
		rendered scene. So make sure you check your current context to ensure
		that you really do want to clear it before you actually do!

		\attention
		This virtual function has a default implementation.
		This allows renderer implementations that do not support render to texture
		to simply ignore the existence of this function and the correct functionality
		will take place.
		*/
		virtual void clearContents() {}

		//! Creates a render texture at the given size
		/*! If your renderer implementation supports render to texture, this is where those
		render textures will be created.

		\note
		It is expected that all render textures are available for use by all other 
		rendering contexts. In other words, it must be usable in render operations
		for every context, only excluding itself.

		\attention
		This virtual function has a default implementation.
		This allows renderer implementations that do not support render to texture
		to simply ignore the existence of this function and the correct functionality
		will take place.
		*/
		virtual RenderTexture* createRenderTexture( const IVector2& size ) {
			return 0;
		}
//@}
	};
}
;//namespace OpenGUI{
#endif

