#ifndef Amethyst_CheckBox_h__
#define Amethyst_CheckBox_h__

#include "Amethyst_Button.h"

namespace OpenGUI {
	namespace Amethyst {
		class AMETHYST_API CheckBox : public ButtonBase {
		public:
			CheckBox();
			virtual ~CheckBox();

			//! Sets the normal button imagery.
			void setImagery( std::string imageryName);
			//! Sets the pressed button imagery. If none specified, uses the Normal imagery.
			void setImageryPressed( std::string imageryName);
			//! Sets the mouse over button imagery. If none specified, uses the Normal imagery.
			void setImageryMouseOver( std::string imageryName);
			//! Sets the disabled button imagery. If none specified, uses the Normal imagery.
			void setImageryDisabled( std::string imageryName);

			//! Gets the normal button imagery.
			std::string getImagery();
			//! Gets the pressed button imagery.
			std::string getImageryPressed();
			//! Gets the mouse over button imagery.
			std::string getImageryMouseOver();
			//! Gets the disabled button imagery.
			std::string getImageryDisabled();

			//! Sets the selected/normal button imagery.
			void setSelImagery( std::string imageryName);
			//! Sets the selected/pressed button imagery. If none specified, uses the Normal imagery.
			void setSelImageryPressed( std::string imageryName);
			//! Sets the selected/mouse over button imagery. If none specified, uses the Normal imagery.
			void setSelImageryMouseOver( std::string imageryName);
			//! Sets the selected/disabled button imagery. If none specified, uses the Normal imagery.
			void setSelImageryDisabled( std::string imageryName);

			//! Gets the selected/normal button imagery.
			std::string getSelImagery();
			//! Gets the selected/pressed button imagery.
			std::string getSelImageryPressed();
			//! Gets the selected/mouse over button imagery.
			std::string getSelImageryMouseOver();
			//! Gets the selected/disabled button imagery.
			std::string getSelImageryDisabled();

			static Widget* createCheckBoxFactory();

			bool getCurrentState() {return mSelected;}
			void setCurrentState(bool s) {mSelected = s;}

		protected:
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );
			virtual void onResized( Object* sender, Resized_EventArgs& evtArgs );

			ImageryPtr mImageryPtr;
			ImageryPtr mImageryPtrPressed;
			ImageryPtr mImageryPtrMouseOver;
			ImageryPtr mImageryPtrDisabled;

			ImageryPtr mSelImageryPtr;
			ImageryPtr mSelImageryPtrPressed;
			ImageryPtr mSelImageryPtrMouseOver;
			ImageryPtr mSelImageryPtrDisabled;

			bool mSelected;

			virtual void preActivate();

		};
	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_CheckBox_h__
