#ifndef AE47F373_7EBC_406d_A732_BF5F07CA261C
#define AE47F373_7EBC_406d_A732_BF5F07CA261C

#include "OpenGUI_BaseWidgets.h"

namespace OpenGUI {
	namespace Widgets {
		/*! \brief This widget is a very simple sub-classing of Widget,
			just so that applications can create container widgets easily via
			an abstracted method.


		\see \ref BW_Container "Container widget documentation"
		*/
		class OPENGUI_API Container : public Widget {
		public:
			//! Constructor
			Container();
			//! virtual Destructor
			virtual ~Container();
			//! This is just a factory interface.
			static Widget* createContainerFactory();
		protected:
			virtual Render::RenderOperationList buildWidgetRenderOpList();
		};

	}//namespace Widgets{
}//namespace OpenGUI{


#endif