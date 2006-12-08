#include "Amethyst_RadioButton.h"

namespace OpenGUI {
	namespace Amethyst {

		std::list<RadioButton *> RadioButton::mRadioList;

		//############################################################################
		class RadioButton_Group_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "Group";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					RadioButton& b = dynamic_cast<RadioButton&>( objectRef );
					valueOut.setValue( b.getGroup() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					RadioButton& b = dynamic_cast<RadioButton&>( objectRef );
					b.setGroup( valueIn.getValueAsString() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_STRING;
			}
		}
		gRadioButton_Group_ObjectProperty;
		//############################################################################

		class RadioButton_ObjectAccessorList : public ObjectAccessorList {
		public:
			RadioButton_ObjectAccessorList() {
				addAccessor( &gRadioButton_Group_ObjectProperty );
			}
			~RadioButton_ObjectAccessorList() {}
		}
		gRadioButton_ObjectAccessorList;

		RadioButton::RadioButton()
		{
			mGroupName = "Default";
			mRadioList.push_back(this);
			if ( gRadioButton_ObjectAccessorList.getParent() == 0 ) 
				gRadioButton_ObjectAccessorList.setParent( Widget::getAccessors() ); 
		}

		RadioButton::~RadioButton()
		{
			/* remove this radio button from our list */
			std::list<RadioButton *>::iterator it = mRadioList.begin();
			bool bFound = false;
			while(!bFound && (it != mRadioList.end()))
			{
				if((*it) == this)
				{
					mRadioList.erase(it);
					bFound = true;
				}
				else
					++it;
			}
		}


	}
}
