#ifndef Amethyst_CheckBox_h__
#define Amethyst_CheckBox_h__

#include "Amethyst_ButtonBase.h"

namespace OpenGUI {
	namespace Amethyst {
		//! checkbox
		class AMETHYST_API CheckBox : public ButtonBase {
		public:
			CheckBox();
			virtual ~CheckBox();

			//! Called when the CheckBox is toggled
			void eventToggled();

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
			bool getSelected();
			//! Sets the selected state of the CheckBox
			void setSelected( bool selected );

			static Widget* createCheckBoxFactory();
			virtual ObjectAccessorList* getAccessors();

		protected:
			//! "Activate" event, captured to toggle the checked value, which fires "Toggled" event
			virtual void onActivate( Object* sender, EventArgs& evtArgs );
			//! "Toggled" event, fired whenever the selected value changes
			virtual void onToggled( Object* sender, EventArgs& evtArgs );

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
