#ifndef B7ECC58F_8C71_487e_8507_A0EEA7E38C25
#define B7ECC58F_8C71_487e_8507_A0EEA7E38C25
#include "OpenGUI.h"
#include "OpenGUI_PropertySet.h"

namespace OpenGUI{

	/*! \brief
		All basic widgets are contained within this namespace. If you want to 
		create a custom widget, your widget should be a subclass of something
		from in here.
	*/
	namespace Widgets{

		//! The widget class is the base class for all Widgets.
		class OPENGUI_API Widget : public OpenGUI::Element, public OpenGUI::PropertySet
		{
		public:
			//! constructor
			Widget();
			//! virtual destructor
			virtual ~Widget() {}
		protected:
			//! This function will be called by the system whenever it needs the widget to redraw itself. Returned list should be depth ordered using a painters algorithm (back to front)
			/*! This function should be overridden by custom widgets. The default implementation within
				the Widget class draws a single white quad that fills the entire defined widget area.

				\note All render operations are expected to be drawn using Local coordinates.
				That means you are using the same coordinate system that is used to define the
				Element's rect. ( See \c Element::getRect() )
			*/
			virtual Render::RenderOperationList buildWidgetRenderOpList();

		private:
			static bool _prop_SetPos(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetPos(PropertySet* widget, const std::string& propertyName, std::string& curValue);
			static bool _prop_SetSize(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetSize(PropertySet* widget, const std::string& propertyName, std::string& curValue);

			static bool _prop_SetEnabled(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetEnabled(PropertySet* widget, const std::string& propertyName, std::string& curValue);

		};
	};//namespace Widgets{
};//namespace OpenGUI{
#endif

