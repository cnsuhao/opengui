// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Amethyst_ScrollBar_h__
#define Amethyst_ScrollBar_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"
namespace OpenGUI {
	namespace Amethyst {

		//! A scroll bar with scaling thumb size based on Maximum value and Coverage area
		/*! This scroll bar automatically sizes the movable thumb based on the coverage / maximum ratio.
		As coverage becomes closer to maximum, the thumb will automatically increase in size to consume the
		appropriate amount of scroll bar area.

		It also fires the "ValueChanged" event whenever the Value property is altered, allowing you to
		hook into the updates to perform automatic scrolling of text fields, etc.

		\par Properties
				- Value
				- Maximum
				- Coverage
				- FaceBG
				- FaceThumb
				- Vertical
		*/
		class AMETHYST_API ScrollBar: public Control {
		public:
			ScrollBar();
			virtual ~ScrollBar();

			//! Sets the background Face used to fill the ScrollBar rect
			void setFaceBG( FacePtr faceBG );
			//! Gets the background Face used to fill the ScrollBar rect
			FacePtr getFaceBG() const;

			//! Sets the Face used to draw the scroll thumb (the movable part of the scrollbar)
			void setFaceThumb( FacePtr faceThumb );
			//! Gets the Face used to draw the scroll thumb
			FacePtr getFaceThumb() const;

			//! Sets the current scroll value
			void setValue( float value );
			//! Gets the current scroll value
			float getValue() const;

			//! Sets the maximum scroll value
			void setMaximum( float maximum );
			//! Gets the maximum scroll value
			float getMaximum() const;

			//! Sets the scroll coverage (the amount of scrollable area that is viewable at once)
			void setCoverage( float coverage );
			//! Gets the scroll coverage
			float getCoverage() const;

			//! Toggles filling from bottom to top instead of left to right
			void setVertical( bool vertical );
			//! Returns the current vertical filling selection
			bool getVertical() const;

			//! Called whenever the scroll Value changes, firing the "ValueChanged" event
			void eventValueChanged();

			static Widget* createScrollBarFactory();
			virtual ObjectAccessorList* getAccessors();

		protected:
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );
			virtual void onTick( Object* sender, Tick_EventArgs& evtArgs );
			virtual void onCursor_Move( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursor_Enter( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursor_Leave( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursor_PressInside( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursor_Release( Object* sender, Cursor_EventArgs& evtArgs );
			virtual void onCursor_Focused( Object* sender, Focus_EventArgs& evtArgs );
			virtual void onCursor_FocusLost( Object* sender, Focus_EventArgs& evtArgs );

			//! Default handler for "ValueChanged" event
			virtual void onValueChanged( Object* sender, EventArgs& evtArgs );
		private:
			FacePtr mFaceBG;
			FacePtr mFaceFG;
			float mValue;
			float mMaximum;
			float mCoverage;
			bool mVertical;

			float mThumbDownValue;
			FVector2 mThumbDownPt;
			FRect mThumbRect;
			void updateThumbRect();
			bool isInsideThumb( const FVector2& point ) const;
		};
	} // namespace Amethyst{
} // namespace OpenGUI{


#endif // Amethyst_ScrollBar_H_h__
