#ifndef A0225006_7C8D_45CC_9C07_5328679AD103
#define A0225006_7C8D_45CC_9C07_5328679AD103

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_Exports.h"

namespace OpenGUI {
	class OPENGUI_API ScreenManager: public Singleton<ScreenManager> {
	public:
		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static ScreenManager& getSingleton( void );

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static ScreenManager* getSingletonPtr( void );

		ScreenManager();
		~ScreenManager();
	};
} //namespace OpenGUI {

#endif // A0225006_7C8D_45CC_9C07_5328679AD103
