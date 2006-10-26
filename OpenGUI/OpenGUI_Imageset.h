#ifndef ADDA6F72_2373_43e0_A282_A8E205CAA876
#define ADDA6F72_2373_43e0_A282_A8E205CAA876

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Texture.h"
#include "OpenGUI_Imagery.h"

namespace OpenGUI {

	//! Imagesets directly represent entire image files. They contain Imagery, which provide a usable window of the image file.
	class OPENGUI_API Imageset {
		friend class ImageryManager;
		friend class Imagery;
	public:
		//! Applications should use the ImageryManager to creation Imagesets
		Imageset( TexturePtr texturePtr, std::string sourceImageFilename );
		~Imageset();

		//! Creates a new Imagery object from this Imageset and returns a shared pointer to the new Imagery. The new Imagery will encompass the entire Imageset area.
		/*! \note Multiple calls to this function with the same \c imageryName result in the destruction and recreation of the Imagery. Effectively, a redefinition. */
		ImageryPtr createImagery( std::string imageryName );

		//! Creates a new Imagery object from this Imageset and returns a shared pointer to the new Imagery. The new Imagery will encompass the Imageset area defined by areaRect (which is in standard UV coordinates).
		/*! \note Multiple calls to this function with the same \c imageryName result in the destruction and recreation of the Imagery. Effectively, a redefinition. */
		ImageryPtr createImagery( std::string imageryName, FRect areaRect, IRect imagesetRect = IRect( 0, 0, 0, 0 ) );

		//! Creates a new Imagery object from this Imageset and returns a shared pointer to the new Imagery.  The new Imagery will encompass the Imageset area defined by areaRect (which is in pixels).
		/*! \note Multiple calls to this function with the same \c imageryName result in the destruction and recreation of the Imagery. Effectively, a redefinition. */
		ImageryPtr createImagery( std::string imageryName, IRect areaRect );

		//! Creates a new Imagery object from this Imageset and returns a shared pointer to the new Imagery.  The new Imagery will encompass the Imageset area defined by top,left,height,width
		ImageryPtr createImagery( const std::string imageryName, int top, int left, int height, int width ) {
			IRect rect( left, top, left + width, top + height );
			return createImagery( imageryName, rect );
		}

		//! Destroys an Imagery object.
		/*! This performs a "safe destruction" of the Imagery object. Since Imagery
			object references are handed out only by RefPtrs, the object will never
			truly destroy until all references to the Imagery object are deleted.
			This function \b does however disconnect the Imagery object from this
			Imageset. Before this Imageset releases its reference to the Imagery,
			the Imagery is pointed to the built in Default Imageset. This will
			prevent crashes if you "pull the Imagery rug out from under a Widget",
			while still providing obvious visual feedback that something is wrong.

			\todo fix this documentation. It's no longer complete accurate
		*/
		void destroyImagery( ImageryPtr imageryPtr );
		//! Destroys an Imagery object. \see void destroyImagery(ImageryPtr imageryPtr);
		void destroyImagery( Imagery* pImagery );
		//! Destroys an Imagery object. \see void destroyImagery(ImageryPtr imageryPtr);
		void destroyImagery( std::string name );

		//! Destroys all Imagery within this Imageset. \note Preserves the "safe destruction" of Imagery, as defined in destroyImagery().
		void destroyAllImagery();

		/*! \brief Returns a shared pointer to the Imagery object within this
			Imageset that has the given name. If the Imagery cannot be found,
			the returned Imagery pointer will be == 0.
		*/
		ImageryPtr getImagery( std::string imageryName );

		//! A string list used by Imageset::getImageryList()
		typedef std::list<std::string> ImageryList;

		//! Returns a list of all imagery currently defined within this imageset. Entries can be fed back into getImagery()
		ImageryList getImageryList();

		//! Returns the texture backing this Imageset
		TexturePtr getTexture();

		//! Returns the name of this Imageset
		const std::string& getName();

	private:
		std::string mFilename;
		TexturePtr mpTexture;
		ImageryPtrList mChildImageryList;
	};
	//! Reference counted, auto deleting Imageset pointer
	typedef RefPtr<Imageset> ImagesetPtr;
	typedef std::list<ImagesetPtr> ImagesetPtrList;
	typedef std::list<Imageset*> ImagesetCPtrList;
}
;//namespace OpenGUI{
#endif

