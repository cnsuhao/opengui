#ifndef B955248E_7EDD_47CA_B588_BAA9C55E4380
#define B955248E_7EDD_47CA_B588_BAA9C55E4380

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"

namespace OpenGUI {

	class OPENGUI_API Primitive{
	public:
		void draw(){}
	};

	class OPENGUI_API Brush {
	public:
		Brush( /*context*/ );
		~Brush();
		Primitive Primitive;
	private:
	};
} // namespace OpenGUI{

#endif // B955248E_7EDD_47CA_B588_BAA9C55E4380

