// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#ifndef Amethyst_ProgressBar_h__
#define Amethyst_ProgressBar_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"

namespace OpenGUI {
	namespace Amethyst {
		//! A progress bar
		/*! The progress bar can be drawn to fill either horizontally or vertically, both
		supporting direction reversal (filling from the other side).

		\par Properties
		- BGFace
		- FillFace
		- Step_Size
		- Total
		- Value
		- Vertical
		- Inverted
		- FillColor
		- BGColor
		- BarPadVert
		- BarPadHoriz
		*/
		class AMETHYST_API ProgressBar : public Control {
		public:
			ProgressBar();
			virtual ~ProgressBar();

			//! Sets the total range of the progress bar (default is 100.0f)
			void setTotal( float total );
			//! Gets the total range
			float getTotal();

			//! Sets the amount to increment value when performing a step (default is 1.0f)
			void setStepSize( float stepSize );
			//! Gets the current step size
			float getStepSize() const;

			//! increments the value by the step size
			void doStep();

			//! Sets the completed value of the progress bar
			void setValue( float newValue );
			//! Gets the current completed value
			float getValue() const;

			//! Sets the color to use when drawing the background
			void setBGColor( const Color &color );
			//! Gets the color used when drawing the background
			const Color& getBGColor() const;

			//! Sets the color to use when drawing filled area
			void setFillColor( const Color &color );
			//! Gets the color used when drawing filled area
			const Color& getFillColor() const;

			//! Sets the Face used to draw the background
			void setBGFace( FacePtr facePtr );
			//! Gets the Face used to draw the background
			FacePtr getBGFace() const;
			//! Sets the Face used to draw the filled area
			void setFillFace( FacePtr facePtr );
			//! Gets the Face used to draw the filled area
			FacePtr getFillFace() const;

			//! Toggles filling from bottom to top instead of left to right
			void setVertical( bool vertical );
			//! Returns the current vertical filling selection
			bool getVertical() const;
			//! Toggles reversing of the fill direction
			void setInverted( bool inverted );
			//! Gets the current fill direction reversal setting
			bool getInverted() const;

			//! Sets the bar padding from the control edge in the horizontal directions
			void setBarPadHoriz( float padding );
			//! Gets the current bar padding from the control edge in the horizontal directions
			float getBarPadHoriz() const;
			//! Sets the bar padding from the control edge in the vertical directions
			void setBarPadVert( float padding );
			//! Gets the current bar padding from the control edge in the vertical directions
			float getBarPadVert() const;

			static Widget* createProgressBarFactory();
			virtual ObjectAccessorList* getAccessors();

		protected:
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );

			float mTotal;
			float mValue;
			float mStepSize;

			FacePtr mFaceBG;
			FacePtr mFaceFG;

			Color mColorBG;
			Color mColorFG;

			bool mVertical;
			bool mInverted;

			float mPadHoriz;
			float mPadVert;
		};
	}
}

#endif // Amethyst_ProgressBar_h__
