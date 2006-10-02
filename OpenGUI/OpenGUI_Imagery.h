#ifndef DA3C55D9_F331_4cd8_9AAA_9354011F56C0
#define DA3C55D9_F331_4cd8_9AAA_9354011F56C0

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_RefPtr.h"
#include "OpenGUI_Texture.h"

namespace OpenGUI {
	class Texture; //forward declaration
	class Imageset; //forward declaration

	//! Defines a sub area of an Imageset.
	class OPENGUI_API Imagery {
		friend class __RefObj<Imagery>; //required for RefPtr to have access to destroy these objects
		friend class Imageset;
	public:
		//! Returns the FRect that defines the Texture UVs for this Imagery within the Imageset
		FRect getTextureUVRect();
		//! Returns the IRect that was used to define the Imagery within the Imageset
		/*! %OpenGUI will do its best to preserve this information, but due to the different ways
			that Imagery can be defined, this value may not always be accurate. It is guaranteed to
			be wrong for Imagery created in Imagesets that have no texture assigned. In which case,
			the value will be a rect equal to IRect(0,0,0,0). If the Imagery was created by defining
			UV coordinates, rather than a pixel based rect, then a pixel rect will be calculated based
			on the UVs. (This is mostly accurate, but not 100% perfect, so some error may occur.)

			\note This value is always available (and accurate) for Imagery that was created from
			an XML file, as the XML loader always creates Imagery using pixel based rects.
		*/
		IRect getImagesetRect();

		//! Returns a pointer to the Texture object for this Imagery's parent Imageset.
		/*! \warning Widget writers: Do <b>not</b>, under any circumstances, cache this value within
			your Widget. It absolutely \b must be retrieved every time you build a RenderOperation,
			as it's value can change. Though the system caches render operations, it also guarantees
			that it will rebuild that cache in the event that a texture pointer becomes invalid.
		*/
		TexturePtr getTexture();

		//! Returns the name of this Imagery object
		std::string getName();

	private:
		Imagery() : mName( "" ), mParentImageset( 0 ) { }
		~Imagery() { }
		std::string mName;
		FRect mAreaRect;
		IRect mNativeRect;
		Imageset* mParentImageset;
	};
	typedef RefPtr<Imagery> ImageryPtr;
	typedef std::list<ImageryPtr> ImageryPtrList;
}
;//namespace OpenGUI{
#endif


