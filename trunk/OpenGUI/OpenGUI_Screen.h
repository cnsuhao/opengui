#ifndef C98B3B2E_E8CB_4091_BFE6_F66803F67963
#define C98B3B2E_E8CB_4091_BFE6_F66803F67963

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Widget.h"
#include "OpenGUI_I_WidgetContainer.h"

namespace OpenGUI{
	class ScreenManager;

	//! Every GUI is built into a screen.
	class OPENGUI_API Screen : public I_WidgetContainer{
		friend class ScreenManager;
	public:
		
		

		void update();
	protected:
		Screen(const std::string& screenName, const FVector2& initialSize);
		virtual ~Screen();
	private:
		std::string mName;
		FVector2 mSize;
	};

} //namespace OpenGUI{

#endif // C98B3B2E_E8CB_4091_BFE6_F66803F67963
