#ifndef E066B8D8_F5B9_4e34_84C2_9BE53ACFA533
#define E066B8D8_F5B9_4e34_84C2_9BE53ACFA533

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Singleton.h"

namespace OpenGUI{
	//! Provides font loading and texture UV generation for glyphs loaded from fonts.
	class OPENGUI_API FontManager : public Singleton<FontManager>{
	public:
		FontManager();

		~FontManager();

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static FontManager& getSingleton(void);

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static FontManager* getSingletonPtr(void);
	};
}//namespace OpenGUI{
#endif
