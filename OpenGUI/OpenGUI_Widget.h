#ifndef B2B428BD_BA97_41F4_AF2E_EF32498FC240
#define B2B428BD_BA97_41F4_AF2E_EF32498FC240

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Object.h"
#include "OpenGUI_ObjectAccessor.h"

namespace OpenGUI {

	//! Base class for all visibly drawn GUI objects
	class OPENGUI_API Widget : public Object {
	public:
		Widget();
		virtual ~Widget();
		void render();

		const std::string& getName();
		void setName( const std::string& name );

		virtual ObjectAccessorList* getAccessors();
		virtual char* getClassName();
	protected:
	private:
		std::string mWidgetName;
	};

} //namespace OpenGUI{

#endif // B2B428BD_BA97_41F4_AF2E_EF32498FC240
