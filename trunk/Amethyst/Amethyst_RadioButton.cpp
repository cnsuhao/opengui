#include "Amethyst_RadioButton.h"
#include "OpenGUI_Macros.h"

namespace OpenGUI {
	namespace Amethyst {
		//############################################################################
		SimpleProperty_String( RadioButtonProperty_Group, "Group", RadioButton, getGroup, setGroup );
		//############################################################################
		class RadioButton_ObjectAccessorList : public ObjectAccessorList {
		public:
			RadioButton_ObjectAccessorList() {
				addAccessor( &RadioButtonProperty_Group );
			}
		}
		gRadioButton_ObjectAccessorList;
		//############################################################################
		//############################################################################
		Widget* RadioButton::createRadioButtonFactory() {
			return new RadioButton;
		}
		//############################################################################
		ObjectAccessorList* RadioButton::getAccessors() {
			return &gRadioButton_ObjectAccessorList;
		}
		//############################################################################
		RadioButton::RadioButton() {
			mGroupName = "";
			if ( gRadioButton_ObjectAccessorList.getParent() == 0 )
				gRadioButton_ObjectAccessorList.setParent( CheckBox::getAccessors() );
		}
		//############################################################################
		RadioButton::~RadioButton() {
			/**/
		}//############################################################################
		/*! To maintain the single selected per group criteria, if you move a selected
		radio button into an existing group it will automatically un-select its new peers.
		(This will cause ToggledOff events as necessary.)
		*/
		void RadioButton::setGroup( const std::string& groupName ) {
			mGroupName = groupName;
			if ( getSelected() )
				unselectPeers();
		}
		//############################################################################
		const std::string& RadioButton::getGroup() {
			return mGroupName;
		}
		//############################################################################
		void RadioButton::unselectPeers() {
			WidgetCollection* p = getContainer();
			if(p){
				WidgetCollection::iterator iter, iterend = p->end();
				for ( iter = p->begin(); iter != iterend; iter++ ) {
					Widget* w = iter.get();
					RadioButton* rb = dynamic_cast<RadioButton*>( w );
					if ( rb ) {
						if ( rb != this && rb->getGroup() == mGroupName ) {
							rb->setSelected( false );
						}
					}
				}
			}
		}
		//############################################################################
		void RadioButton::onToggledOn( Object* sender, EventArgs& evtArgs ) {
			unselectPeers();
		}
		//############################################################################
		void RadioButton::onActivate( Object* sender, EventArgs& evtArgs ) {
			setSelected( true );
		}
		//############################################################################
	} // namespace Amethyst {
} // namespace OpenGUI {
