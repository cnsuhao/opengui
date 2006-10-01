#ifndef B2B428BD_BA97_41F4_AF2E_EF32498FC240
#define B2B428BD_BA97_41F4_AF2E_EF32498FC240

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Object.h"
#include "OpenGUI_ObjectAccessor.h"
#include "OpenGUI_Brush.h"

namespace OpenGUI {

	class Renderer; //forward declaration
	class I_WidgetContainer; //forward declaration

	//! Base class for all visibly drawn GUI objects
	class OPENGUI_API Widget : public Object {
		friend class I_WidgetContainer; //we'll need this so containers can manage our handle to them
	public:
		Widget();
		virtual ~Widget();
		
		//! returns the name of this Widget
		const std::string& getName();
		//! sets the name of this Widget
		void setName( const std::string& name );

		//! Called whenever this widget needs to redraw itself.
		virtual void onDraw( Brush& brushRef );

		//! returns the container this widget is held within
		I_WidgetContainer* getContainer();

		// inherited from Object
		virtual ObjectAccessorList* getAccessors(); 
		virtual char* getClassName(); 
	protected:

		//!
		virtual void _render(Renderer* rendererPtr, FVector2 offset);
	private:
		std::string mWidgetName;
		I_WidgetContainer* mContainer;		
	};

} //namespace OpenGUI{

#endif // B2B428BD_BA97_41F4_AF2E_EF32498FC240