#ifndef Amethyst_RadioButton_h__
#define Amethyst_RadioButton_h__

#include "Amethyst_CheckBox.h"

namespace OpenGUI {
	namespace Amethyst {
		//! radio button
		class AMETHYST_API RadioButton : public CheckBox {
		public:
			RadioButton();
			virtual ~RadioButton();
			void setGroup(std::string g) {mGroupName = g;}
			std::string getGroup( ) {return mGroupName;}

		protected:
			std::string mGroupName;

		private:
			static std::list<RadioButton *> mRadioList;
		};
	}
}

#endif // Amethyst_RadioButton_h__
