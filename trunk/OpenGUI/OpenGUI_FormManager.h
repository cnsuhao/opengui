#ifndef EE1973FF_45A9_47ea_BBE1_A9DEFA47DF60
#define EE1973FF_45A9_47ea_BBE1_A9DEFA47DF60

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_XML.h"

namespace OpenGUI{

	class System; // forward declaration

	//! Defines a Form that can later be created at any location within a GUI
	class OPENGUI_API FormDefinition{
		/**/
	};

	//! Manages creating, destroying, and lookup of FormDefinition objects
	class OPENGUI_API FormManager: public Singleton<FormManager> {
		friend class System; // so System can create/destroy
	public:
		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static FormManager& getSingleton( void );

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static FormManager* getSingletonPtr( void );

	protected:
		FormManager();
		~FormManager();

	private:
		static bool _FormDef_XMLNode_Load( const XMLNode& node, const std::string& nodePath );
		static bool _FormDef_XMLNode_Unload( const XMLNode& node, const std::string& nodePath );
		//static void _Form_XMLNode_IntoContainer(const XMLNode& formNode, I_WidgetContainer& widgetContainer);
	};

}

#endif // EE1973FF_45A9_47ea_BBE1_A9DEFA47DF60
