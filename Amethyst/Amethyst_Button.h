#ifndef Amethyst_Button_h__
#define Amethyst_Button_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"

namespace OpenGUI {
	namespace Amethyst {

		class AMETHYST_API SimpleButton : public Control {
		public:
			//! Constructor
			SimpleButton();
			//! virtual Destructor
			virtual ~SimpleButton();
			//! Sets the normal button imagery.
			void setImagery( std::string imageryName );
			//! Sets the pressed button imagery. If none specified, uses the Normal imagery.
			void setImageryPressed( std::string imageryName );
			//! Sets the mouse over button imagery. If none specified, uses the Normal imagery.
			void setImageryMouseOver( std::string imageryName );
			//! Sets the disabled button imagery. If none specified, uses the Normal imagery.
			void setImageryDisabled( std::string imageryName );

			//! Gets the normal button imagery.
			std::string getImagery();
			//! Gets the pressed button imagery.
			std::string getImageryPressed();
			//! Gets the mouse over button imagery.
			std::string getImageryMouseOver();
			//! Gets the disabled button imagery.
			std::string getImageryDisabled();


			static Widget* createSimpleButtonFactory();

		protected:
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );
			virtual void onResized( Object* sender, Resized_EventArgs& evtArgs );


			ImageryPtr mImageryPtr;
			ImageryPtr mImageryPtrPressed;
			ImageryPtr mImageryPtrMouseOver;
			ImageryPtr mImageryPtrDisabled;
			bool m_MouseOver;
			bool m_ButtonDown;
		};


	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_Button_h__
