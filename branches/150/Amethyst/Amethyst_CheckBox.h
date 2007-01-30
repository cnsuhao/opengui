// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#ifndef Amethyst_CheckBox_h__
#define Amethyst_CheckBox_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"
#include "Amethyst_ButtonBase.h"

namespace OpenGUI {
	namespace Amethyst {
		//! Its a Check Box
		/*! Performs the usual barrage of checkbox-like activity.
		Fires the "Activate" event when the Selected value changes.
		Fires "ToggledOn" event when the Selected value changes becomes TRUE.
		Fires "ToggledOff" event when the Selected value changes becomes FALSE.

		\par Properties
		- Selected
		- Face_Normal
		- Face_Over
		- Face_Pressed
		- Face_Disabled
		- Face_SelNormal
		- Face_SelOver
		- Face_SelPressed
		- Face_SelDisabled
		*/
		class AMETHYST_API CheckBox : public ButtonBase {
		public:
			CheckBox();
			virtual ~CheckBox();

			//! Called when the check box is pressed, fires "Activate" event
			void eventActivate();
			//! Called when the Selected state changes to TRUE, fires "ToggledOn" event
			void eventToggledOn();
			//! Called when the Selected state changes to TRUE, fires "ToggledOff" event
			void eventToggledOff();

			//! Sets the Face used to draw the button in the Normal state
			void setFaceNormal( FacePtr normalFace );
			//! Gets the Face used to draw the button in the Normal state
			FacePtr getFaceNormal() const;
			//! Sets the Face used to draw the button in the Over state
			void setFaceOver( FacePtr overFace );
			//! Gets the Face used to draw the button in the Over state
			FacePtr getFaceOver() const;
			//! Sets the Face used to draw the button in the Pressed state
			void setFacePressed( FacePtr pressedFace );
			//! Gets the Face used to draw the button in the Pressed state
			FacePtr getFacePressed() const;
			//! Sets the Face used to draw the button in the Disabled state
			void setFaceDisabled( FacePtr disabledFace );
			//! Gets the Face used to draw the button in the Disabled state
			FacePtr getFaceDisabled() const;

			//! Sets the Face used to draw the button in the Normal selected state
			void setFaceSelNormal( FacePtr normalFace );
			//! Gets the Face used to draw the button in the Normal selected state
			FacePtr getFaceSelNormal() const;
			//! Sets the Face used to draw the button in the Over selected state
			void setFaceSelOver( FacePtr overFace );
			//! Gets the Face used to draw the button in the Over selected state
			FacePtr getFaceSelOver() const;
			//! Sets the Face used to draw the button in the Pressed selected state
			void setFaceSelPressed( FacePtr pressedFace );
			//! Gets the Face used to draw the button in the Pressed selected state
			FacePtr getFaceSelPressed() const;
			//! Sets the Face used to draw the button in the Disabled selected state
			void setFaceSelDisabled( FacePtr disabledFace );
			//! Gets the Face used to draw the button in the Disabled selected state
			FacePtr getFaceSelDisabled() const;

			//! Gets the current selected state of the CheckBox
			bool getSelected() const;
			//! Sets the selected state of the CheckBox
			void setSelected( bool selected );

			static Widget* createCheckBoxFactory();
			virtual ObjectAccessorList* getAccessors();

		protected:
			//! "Activate" event, default action inverts the Selected state
			virtual void onActivate( Object* sender, EventArgs& evtArgs );
			//! "ToggledOn" event, fired whenever the Selected value changes to TRUE
			virtual void onToggledOn( Object* sender, EventArgs& evtArgs );
			//! "ToggledOff" event, fired whenever the Selected value changes to FALSE
			virtual void onToggledOff( Object* sender, EventArgs& evtArgs );
			// inherited from ButtonBase
			virtual void _buttonActivate();

			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );
			bool mSelected;
			FacePtr mFace_Normal;
			FacePtr mFace_Over;
			FacePtr mFace_Pressed;
			FacePtr mFace_Disabled;
			FacePtr mFace_SelNormal;
			FacePtr mFace_SelOver;
			FacePtr mFace_SelPressed;
			FacePtr mFace_SelDisabled;
		};

	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_CheckBox_h__
