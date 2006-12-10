#ifndef DA3C55D9_F331_4cd8_9AAA_9354011F56C0
#define DA3C55D9_F331_4cd8_9AAA_9354011F56C0

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_RefPtr.h"
#include "OpenGUI_Texture.h"

namespace OpenGUI {
	class Texture; //forward declaration

	//! Defines a sub area of an Imageset.
	class OPENGUI_API Imagery {
		friend class __RefObj<Imagery>; //required for RefPtr to have access to destroy these objects
		friend class Imageset;
	public:
		//! Returns the FRect that defines the Texture UVs for this Imagery within the Imageset
		const FRect& getTextureUVRect() const;

		//! Returns the IRect that was used to define the Imagery within the Imageset
		/*!If the Imagery was created by defining UV coordinates, rather than a pixel based rect,
		then a pixel rect will be calculated based on the UVs. (This is mostly accurate, but not
		100% perfect, so some error may occur.)
		*/
		const IRect& getImagesetRect() const;

		//! Returns a pointer to the Texture object for this Imagery's parent Imageset.
		TexturePtr getTexture() const;

		//! Returns the name of this Imagery object
		const std::string& getName() const;

		//! Returns the fully qualified name of this Imagery object
		const std::string& getFQN() const;

	private:
		Imagery( const std::string ImagesetName, const std::string Name, FRect areaRect, IRect nativeRect, TexturePtr texture );
		~Imagery();
		std::string mFQN;
		std::string mName;
		FRect mAreaRect;
		IRect mNativeRect;
		TexturePtr mTexture;
	};
	//! Reference counted, auto deleting Imagery pointer
	typedef RefPtr<Imagery> ImageryPtr;
	//! list of ImageryPtrs
	typedef std::list<ImageryPtr> ImageryPtrList;
}
;//namespace OpenGUI{
#endif


