// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Amethyst_RadioButton_h__
#define Amethyst_RadioButton_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"
#include "Amethyst_CheckBox.h"

namespace OpenGUI {
	namespace Amethyst {
		//! A CheckBox variant that provides grouping with peers so only 1 is Selected at any point in time
		/*! Aside from the addition of the grouping mechanism, a RadioButton behaves
		exactly like a CheckBox, sharing the same properties and events.

		\par Properties
		- Group
		*/
		class AMETHYST_API RadioButton : public CheckBox {
		public:
			RadioButton();
			virtual ~RadioButton();
			//! Sets the Group name of the radio button
			void setGroup( const std::string& groupName );
			//! Gets the radio button Group name
			const std::string& getGroup();

			static Widget* createRadioButtonFactory();
			virtual ObjectAccessorList* getAccessors();
		protected:
			//! Inherited from CheckBox, used to unselect all peers in the same Group
			virtual void onToggledOn( Object* sender, EventArgs& evtArgs );
			//! Inherited from CheckBox, sets the current Selected state to TRUE
			virtual void onActivate( Object* sender, EventArgs& evtArgs );
		private:
			// this is the function used to unselect all peers when we are selected
			void unselectPeers();
			std::string mGroupName;
		};
	} // namespace Amethyst {
} // namespace OpenGUI {

#endif // Amethyst_RadioButton_h__
