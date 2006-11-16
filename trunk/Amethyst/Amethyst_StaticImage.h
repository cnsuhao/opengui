#ifndef Amethyst_StaticImage_h__
#define Amethyst_StaticImage_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"

namespace OpenGUI {
	namespace Amethyst {

		class AMETHYST_API StaticImage: public Control {
		public:
			StaticImage();
			virtual ~StaticImage();

			//! Sets the imagery.
			void setImagery( std::string imageryName );
			//! Gets the imagery.
			std::string getImagery();


			static Widget* CreateStaticImageFactory();

		protected:
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );

			ImageryPtr mImageryPtr;
		};

	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_StaticImage_h__
