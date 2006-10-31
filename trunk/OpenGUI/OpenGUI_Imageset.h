#ifndef ADDA6F72_2373_43e0_A282_A8E205CAA876
#define ADDA6F72_2373_43e0_A282_A8E205CAA876

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Texture.h"
#include "OpenGUI_Imagery.h"

namespace OpenGUI {

	//! Imagesets directly represent entire image files. They contain Imagery, which provide a usable window of the image file.
	class OPENGUI_API Imageset: public RefObject {
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
			Imageset. Since Imagery objects contain the RefPtr to the texture they
			use, the Imagery will be valid until all handles are destroyed.
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

		//! returns the total number of Imagery defined under this Imageset
		size_t getImageryCount() const;

	private:
		virtual void finalize(); //finalizer from RefObject
		std::string mFilename;
		TexturePtr mpTexture;
		ImageryPtrList mChildImageryList;
	};
	//! Handle to the reference counted, auto deleting Imageset object
	typedef RefObjHandle<Imageset> ImagesetPtr; // we use RefObject because it holds the ref count inside the object referenced
	//! List of ImagesetPtr
	typedef std::list<ImagesetPtr> ImagesetPtrList;
}
;//namespace OpenGUI{
#endif

