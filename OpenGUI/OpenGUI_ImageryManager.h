#ifndef A7EB8CEB_DF02_4714_AD1E_53FDCDD6C2E2
#define A7EB8CEB_DF02_4714_AD1E_53FDCDD6C2E2

#include "OpenGUI_Exports.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_Imageset.h"

namespace OpenGUI{

	/*! \brief
		Provides management services for loading, unloading, keeping track of,
		and searching for Imageset and the children Image objects.\n \b [Singleton]
	*/
	class OPENGUI_API ImageryManager : public Singleton<ImageryManager>{
	public:
		ImageryManager();
		~ImageryManager();

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static ImageryManager& getSingleton(void);

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static ImageryManager* getSingletonPtr(void);


		//! Create a new Imageset.
		/*! This will create a new Imageset based on the image file specified. If an Imageset
			already exists based on the provided filename, then the existing Imageset is returned
			instead of creating a new one.

			\param imageFilename The filename of the source image file. This name
				can also be used to later retrieve the Imageset pointer via getImageset()
			\return pointer to the newly created imageset, or 0 on failure.
		*/
		Imageset* createImageset(std::string imageFilename);
		//! Returns a pointer to the Imageset that was created using the given filename, or 0 on failure.
		Imageset* getImageset(std::string imageFilename);
		//! Destroys an Imageset.
		void destroyImageset(Imageset* pImageset);
		//! Destroys an Imageset.
		void destroyImageset(std::string imageFilename);
		//! Destroys all Imagesets
		void destroyAllImagesets();

		//! Searches all Imagesets for imagery of the given name and returns the first instance found.
		/*! \returns ImageryPtr(0) on failure, otherwise a RefPtr to the found Imagery */
		ImageryPtr getImagery(std::string imageryName);

		//! Loads Imagesets from an XML document.
		/*! Any conflicting Imagesets will be overwritten, any non-imageset related
			XML entities are silently ignored.
		*/
		void LoadImagesetsFromXML(std::string xmlFilename);

		//Internal use only
		Imageset* __getDefaultImageset();
	private:
		ImagesetCPtrList mImagesetList;
		Imageset* mDefaultImageset;
		void __buildDefaultImageset();
		void __destroyDefaultImageset();
		Imageset* _loadImagesetFromTinyXMLElement(void* tXelementPtr);
	};

};//namespace OpenGUI{

#endif

