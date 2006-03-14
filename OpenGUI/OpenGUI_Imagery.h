#ifndef DA3C55D9_F331_4cd8_9AAA_9354011F56C0
#define DA3C55D9_F331_4cd8_9AAA_9354011F56C0

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"

namespace OpenGUI{
	
	class Imageset; //forward declaration

	//! Defines a sub area of an Imageset.
	class OPENGUI_API Imagery
	{
		friend class __RefObj<Imagery>; //required for RefPtr to have access to destroy these objects
		friend class Imageset;
	public:
		//! Returns the FRect that defines the Texture UVs for this Imagery within the Imageset
		FRect getTextureUVRect();
		//! Returns a pointer to the Texture object for this Imagery's parent Imageset.
		/*! \warning Widget writers: Do <b>not</b>, under any circumstances, cache this value within
			your Widget. It absolutely \b must be retrieved every time you build a RenderOperation,
			as it's value can change. Though the system caches render operations, it also guarantees
			that it will rebuild that cache in the event that a texture pointer becomes invalid.
		*/
		Texture* getTexture();

		//! Returns the name of this Imagery object
		std::string getName();

	private:
		Imagery() : mName(""),mParentImageset(0) { }
		~Imagery() { }
		std::string mName;
		FRect mAreaRect;
		Imageset* mParentImageset;
	};
	typedef RefPtr<Imagery> ImageryPtr;
	typedef std::list<ImageryPtr> ImageryPtrList;
};//namespace OpenGUI{
#endif


