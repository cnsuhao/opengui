#ifndef F9497A73_9AD4_4241_8A38_7566DBC752BE
#define F9497A73_9AD4_4241_8A38_7566DBC752BE

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Widget.h"
#include "OpenGUI_I_WidgetContainer.h"

namespace OpenGUI {

	//! Base class for all GUI objects that have position and size
	class OPENGUI_API Control : public Widget {
	public:
		//! public constructor
		Control();
		//! public destructor
		virtual ~Control();


		//! Sets the alpha transparency of this Widget
		void setAlpha( float alpha );
		//! Returns the alpha transparency of this Widget
		float getAlpha();



		//Object Functions
		virtual ObjectAccessorList* getAccessors();
		virtual char* getClassName();

	protected:
	private:
		float mAlpha;
	};

} // namespace OpenGUI{

#endif // F9497A73_9AD4_4241_8A38_7566DBC752BE
