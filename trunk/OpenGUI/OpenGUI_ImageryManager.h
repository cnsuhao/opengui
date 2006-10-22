#ifndef A7EB8CEB_DF02_4714_AD1E_53FDCDD6C2E2
#define A7EB8CEB_DF02_4714_AD1E_53FDCDD6C2E2

#include "OpenGUI_PreRequisites.h"

#include "OpenGUI_Exports.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_Imageset.h"

namespace OpenGUI {

	class ResourceProvider; //forward declaration

	/*! \brief
		Provides management services for loading, unloading, keeping track of,
		and searching for Imageset and the children Image objects.\n \b [Singleton]
	*/
	class OPENGUI_API ImageryManager : public Singleton<ImageryManager> {
		friend class XMLParser;
		friend class Imageset;
	public:
		ImageryManager( ResourceProvider* resourceProvider );
		~ImageryManager();

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static ImageryManager& getSingleton( void );

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static ImageryManager* getSingletonPtr( void );


		//! Create a new Imageset.
		/*! This will create a new Imageset based on the image file specified. If an Imageset
			already exists based on the provided filename, then the existing Imageset is returned
			instead of creating a new one.

			\param imageFilename The filename of the source image file. This name
				can also be used to later retrieve the Imageset pointer via getImageset()
			\return pointer to the newly created imageset, or 0 on failure.
		*/
		Imageset* createImageset( std::string imageFilename );
		//! Static pass through function to createImageset()
		static Imageset* createImagesetEx( std::string imageFilename ) {
			return ImageryManager::getSingleton().createImageset( imageFilename );
		}

		//! Create a new Imageset from an existing texture.
		/*! This acts much like the file-based \c createImageset() function, with the
			exception that it does not attempt to load the texture from a file on disk.
			Instead, it uses the already existing texture that is given. The \c imageFilename
			parameter is only used for future lookups by \c getImageset(), and must therefore
			be unique, but is otherwise meaningless. If no \c imageFilename is given, one is
			automatically generated for you.

			Any single \c texture or \c imageFilename can only be used once to create an Imageset,
			so future calls to this function with the same \c texture or \c imageFilename will
			result in varying functionality.

			If the given \c imageFilename ever matches an existing filename, the Imageset is updated
			to use the new texture and the updated existing Imageset is returned. (If the new \c texture
			and old \c texture are different, then the old texture is destroyed. Otherwise, if they are
			the same, there is no logical change to make, so no action is taken.)

			If the given \c imageFilename does not match any existing Imageset filenames, but a duplicate
			\c texture is found, an exception is thrown. If you really want to back two or more separate
			Imagesets with the same texture, you will have to load the texture again for every time that
			it is used in an Imageset.

			\warning The ImageryManager system assumes responsibility for all textures that it uses. This
				means that once you give a texture to this system, it will be destroyed automatically when
				the Imageset it belongs to is destroyed.

			\note If you use this function to replace the texture of an existing Imageset, the new texture
				should match the dimensions of the old texture. If the dimensions do not match, the
				affect on the contained imagery is undefined.

			\returns On success the return value is the pointer to the Imageset created or updated.
				On failure the return value is 0, and the given \c texture does not become the
				property of the Imageset.
		*/
		Imageset* createImagesetFromTexture( TexturePtr texture, std::string imageFilename = "" );

		//! Returns a pointer to the Imageset that was created using the given filename, or 0 on failure.
		Imageset* getImageset( std::string imageFilename );

		//! Returns a pointer to the Imageset that is based on the given \c texture, or 0 on failure.
		Imageset* getImagesetByTexture( TexturePtr texture );

		//! Destroys an Imageset.
		void destroyImageset( Imageset* pImageset );
		//! Destroys an Imageset.
		void destroyImageset( std::string imageFilename );
		//! Destroys all Imagesets
		void destroyAllImagesets();

		//! Searches all Imagesets for imagery of the given name and returns the first instance found.
		/*! \returns ImageryPtr(0) on failure, otherwise a RefPtr to the found Imagery */
		ImageryPtr getImagery( std::string imageryName );

		//! Loads Imagesets from an XML document.
		/*! Any conflicting Imagesets will be overwritten, any non-imageset related
			XML entities are silently ignored (only processes \<Imageset\> and enclosed \<Imagery\> tags).
		*/
		void LoadImagesetsFromXML( std::string xmlFilename );

		//! A string list used by ImageryManager::getImagesetList()
		typedef std::list<std::string> ImagesetList;

		//! Returns an ImagesetList of all imagesets that are currently loaded. Items can be fed back into getImageset()
		ImagesetList getImagesetList();

	private:
		ImagesetCPtrList mImagesetList;

		Imageset* _loadImagesetFromTinyXMLElement( void* tXelementPtr );

		static std::string _generateRandomName();//Generates unique names for Imagesets/Imagery

		ResourceProvider* mResourceProvider;
	};

}
;//namespace OpenGUI{

#endif

