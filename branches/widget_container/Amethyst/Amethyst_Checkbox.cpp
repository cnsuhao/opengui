#include "Amethyst_Checkbox.h"
#include "OpenGUI_Macros.h"

namespace OpenGUI {
	namespace Amethyst {
		//############################################################################
		SimpleProperty_Face( CheckBoxProperty_FaceNormal, "Face_Normal", CheckBox, getFaceNormal, setFaceNormal );
		SimpleProperty_Face( CheckBoxProperty_FaceOver, "Face_Over", CheckBox, getFaceOver, setFaceOver );
		SimpleProperty_Face( CheckBoxProperty_FacePresseed, "Face_Pressed", CheckBox, getFacePressed, setFacePressed );
		SimpleProperty_Face( CheckBoxProperty_FaceDisabled, "Face_Disabled", CheckBox, getFaceDisabled, setFaceDisabled );
		SimpleProperty_Face( CheckBoxProperty_FaceSelNormal, "Face_SelNormal", CheckBox, getFaceSelNormal, setFaceSelNormal );
		SimpleProperty_Face( CheckBoxProperty_FaceSelOver, "Face_SelOver", CheckBox, getFaceSelOver, setFaceSelOver );
		SimpleProperty_Face( CheckBoxProperty_FaceSelPresseed, "Face_SelPressed", CheckBox, getFaceSelPressed, setFaceSelPressed );
		SimpleProperty_Face( CheckBoxProperty_FaceSelDisabled, "Face_SelDisabled", CheckBox, getFaceSelDisabled, setFaceSelDisabled );
		SimpleProperty_Bool( CheckBoxProperty_Checked, "Selected", CheckBox, getSelected, setSelected );
		//############################################################################
		class CheckBox_ObjectAccessorList : public ObjectAccessorList {
		public:
			CheckBox_ObjectAccessorList() {
				addAccessor( &CheckBoxProperty_FaceNormal );
				addAccessor( &CheckBoxProperty_FaceOver );
				addAccessor( &CheckBoxProperty_FacePresseed );
				addAccessor( &CheckBoxProperty_FaceDisabled );
				addAccessor( &CheckBoxProperty_FaceSelNormal );
				addAccessor( &CheckBoxProperty_FaceSelOver );
				addAccessor( &CheckBoxProperty_FaceSelPresseed );
				addAccessor( &CheckBoxProperty_FaceSelDisabled );
				addAccessor( &CheckBoxProperty_Checked );
			}
			~CheckBox_ObjectAccessorList() {}
		}
		gCheckBox_ObjectAccessorList;
		//############################################################################
		//############################################################################
		Widget* CheckBox::createCheckBoxFactory() {
			return new CheckBox;
		}
		//############################################################################
		ObjectAccessorList* CheckBox::getAccessors() {
			return &gCheckBox_ObjectAccessorList;
		}
		//############################################################################
		CheckBox::CheckBox() {
			if ( gCheckBox_ObjectAccessorList.getParent() == NULL )
				gCheckBox_ObjectAccessorList.setParent( Control::getAccessors() );
			mSelected = false;

			getEvents().createEvent( "Activate" );
			getEvents()["Activate"].add( new EventDelegate( this, &CheckBox::onActivate ) );
			getEvents().createEvent( "ToggledOn" );
			getEvents().createEvent( "ToggledOff" );
			getEvents()["ToggledOn"].add( new EventDelegate( this, &CheckBox::onToggledOn ) );
			getEvents()["ToggledOff"].add( new EventDelegate( this, &CheckBox::onToggledOff ) );
		}
		//############################################################################
		CheckBox::~CheckBox() {
			/**/
		}
		//############################################################################
		void CheckBox::setFaceNormal( FacePtr normalFace ) {
			mFace_Normal = normalFace;
		}
		//############################################################################
		FacePtr CheckBox::getFaceNormal() const {
			return mFace_Normal;
		}
		//############################################################################
		void CheckBox::setFaceOver( FacePtr overFace ) {
			mFace_Over = overFace;
		}
		//############################################################################
		FacePtr CheckBox::getFaceOver() const {
			return mFace_Over;
		}
		//############################################################################
		void CheckBox::setFacePressed( FacePtr pressedFace ) {
			mFace_Pressed = pressedFace;
		}
		//############################################################################
		FacePtr CheckBox::getFacePressed() const {
			return mFace_Pressed;
		}
		//############################################################################
		void CheckBox::setFaceDisabled( FacePtr disabledFace ) {
			mFace_Disabled = disabledFace;
		}
		//############################################################################
		FacePtr CheckBox::getFaceDisabled() const {
			return mFace_Disabled;
		}
		//############################################################################
		void CheckBox::setFaceSelNormal( FacePtr normalFace ) {
			mFace_SelNormal = normalFace;
		}
		//############################################################################
		FacePtr CheckBox::getFaceSelNormal() const {
			return mFace_SelNormal;
		}
		//############################################################################
		void CheckBox::setFaceSelOver( FacePtr overFace ) {
			mFace_SelOver = overFace;
		}
		//############################################################################
		FacePtr CheckBox::getFaceSelOver() const {
			return mFace_SelOver;
		}
		//############################################################################
		void CheckBox::setFaceSelPressed( FacePtr pressedFace ) {
			mFace_SelPressed = pressedFace;
		}
		//############################################################################
		FacePtr CheckBox::getFaceSelPressed() const {
			return mFace_SelPressed;
		}
		//############################################################################
		void CheckBox::setFaceSelDisabled( FacePtr disabledFace ) {
			mFace_SelDisabled = disabledFace;
		}
		//############################################################################
		FacePtr CheckBox::getFaceSelDisabled() const {
			return mFace_SelDisabled;
		}
		//############################################################################
		bool CheckBox::getSelected() const {
			return mSelected;
		}
		//############################################################################
		void CheckBox::setSelected( bool selected ) {
			if ( mSelected == selected ) return;
			mSelected = selected;
			if ( mSelected )
				eventToggledOn();
			else
				eventToggledOff();
		}
		//############################################################################
		void CheckBox::eventActivate() {
			EventArgs args;
			getEvents().sendEvent( "Activate", args );
		}
		//############################################################################
		void CheckBox::eventToggledOn() {
			EventArgs args;
			getEvents().sendEvent( "ToggledOn", args );
		}
		//############################################################################
		void CheckBox::eventToggledOff() {
			EventArgs args;
			getEvents().sendEvent( "ToggledOff", args );
		}
		//############################################################################
		void CheckBox::onActivate( Object* sender, EventArgs& evtArgs ) {
			setSelected( !getSelected() );
		}
		//############################################################################
		void CheckBox::onToggledOn( Object* sender, EventArgs& evtArgs ) {
			/* default action is to do nothing */
		}
		//############################################################################
		void CheckBox::onToggledOff( Object* sender, EventArgs& evtArgs ) {
			/* default action is to do nothing */
		}
		//############################################################################
		void CheckBox::_buttonActivate() {
			eventActivate();
		}
		//############################################################################
		//############################################################################
		void CheckBox::onDraw( Object* sender, Draw_EventArgs& evtArgs ) {
			Brush& b = evtArgs.brush;
			FacePtr drawFace = mFace_Normal;
			// if we're in the selected state, we should switch to the selected Normal Face if available
			if ( mSelected && mFace_SelNormal )
				drawFace = mFace_SelNormal;

			if ( mSelected ) {
				// selected state
				if ( mFace_SelOver && mButtonState == BS_OVER ) {
					drawFace = mFace_SelOver;
				}

				if ( mFace_SelPressed && mButtonState == BS_PRESSED ) {
					drawFace = mFace_SelPressed;
				}

				if ( mFace_SelDisabled && mButtonState == BS_DISABLED ) {
					drawFace = mFace_SelDisabled;
				}
			} else {
				// unselected state
				if ( mFace_Over && mButtonState == BS_OVER ) {
					drawFace = mFace_Over;
				}

				if ( mFace_Pressed && mButtonState == BS_PRESSED ) {
					drawFace = mFace_Pressed;
				}

				if ( mFace_Disabled && mButtonState == BS_DISABLED ) {
					drawFace = mFace_Disabled;
				}
			}

			if ( drawFace )
				b.Image.drawFace( drawFace, getRect() );
		}
		//############################################################################
	} // namespace Amethyst {
} // namespace OpenGUI {
