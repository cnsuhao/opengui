#ifndef E7C6D975_96DE_4E7B_BC8B_15FA981B1FEF
#define E7C6D975_96DE_4E7B_BC8B_15FA981B1FEF

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_Exports.h"

namespace OpenGUI {
	class OPENGUI_API TextureManager : public Singleton<TextureManager> {
	public:
		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static TextureManager& getSingleton( void );

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static TextureManager* getSingletonPtr( void );

		TextureManager();
		~TextureManager();
	};
		
} //namespace OpenGUI {

#endif // E7C6D975_96DE_4E7B_BC8B_15FA981B1FEF
