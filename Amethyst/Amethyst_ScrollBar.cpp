#include "Amethyst_ScrollBar.h"
#include "OpenGUI_Macros.h"

namespace OpenGUI {
	namespace Amethyst {
		//############################################################################
		SimpleProperty_Float( ScrollBarP_Value, "Value", ScrollBar, getValue, setValue );
		SimpleProperty_Float( ScrollBarP_Maximum, "Maximum", ScrollBar, getMaximum, setMaximum );
		SimpleProperty_Float( ScrollBarP_Coverage, "Coverage", ScrollBar, getCoverage, setCoverage );
		SimpleProperty_Face( ScrollBarP_FaceBG, "FaceBG", ScrollBar, getFaceBG, setFaceBG );
		SimpleProperty_Face( ScrollBarP_FaceThumb, "FaceThumb", ScrollBar, getFaceThumb, setFaceThumb );
		SimpleProperty_Bool( ScrollBarP_Vertical, "Vertical", ScrollBar, getVertical, setVertical );
		//############################################################################
		class Scroll_ObjectAccessorList : public ObjectAccessorList {
		public:
			Scroll_ObjectAccessorList() {
				addAccessor( &ScrollBarP_Value );
				addAccessor( &ScrollBarP_Maximum );
				addAccessor( &ScrollBarP_Coverage );
				addAccessor( &ScrollBarP_FaceBG );
				addAccessor( &ScrollBarP_FaceThumb );
				addAccessor( &ScrollBarP_Vertical );
			}
			~Scroll_ObjectAccessorList() {}
		}
		gScrollBar_ObjectAccessorList;
		//############################################################################
		ObjectAccessorList* ScrollBar::getAccessors() {
			return &gScrollBar_ObjectAccessorList;
		}
		//############################################################################
		Widget* ScrollBar::createScrollBarFactory() {
			return new ScrollBar;
		}
		//############################################################################
		//############################################################################
		ScrollBar::ScrollBar() {
			if ( gScrollBar_ObjectAccessorList.getParent() == 0 )
				gScrollBar_ObjectAccessorList.setParent( Control::getAccessors() );

			mCoverage = 10.0f;
			mMaximum = 100.0f;
			mValue = 0.0f;
			mVertical = false;

			getEvents().createEvent( "ValueChanged" );
			getEvents()["ValueChanged"].add( new EventDelegate( this, &ScrollBar::onValueChanged ) );
		}
		//############################################################################
		ScrollBar::~ScrollBar() {
			/**/
		}
		//############################################################################
		void ScrollBar::setFaceBG( FacePtr faceBG ) {
			mFaceBG = faceBG;
			invalidate();
		}
		//############################################################################
		FacePtr ScrollBar::getFaceBG() const {
			return mFaceBG;
		}
		//############################################################################
		void ScrollBar::setFaceThumb( FacePtr faceThumb ) {
			mFaceFG = faceThumb;
			invalidate();
		}
		//############################################################################
		FacePtr ScrollBar::getFaceThumb() const {
			return mFaceFG;
		}
		//############################################################################
		void ScrollBar::setValue( float value ) {
			if ( value == mValue ) return;
			mValue = value;
			if ( mMaximum < mValue ) mValue = mMaximum;
			if ( mValue < 0 ) mValue = 0;
			invalidate();
			updateThumbRect();
			eventValueChanged();
		}
		//############################################################################
		float ScrollBar::getValue() const {
			return mValue;
		}
		//############################################################################
		void ScrollBar::setMaximum( float maximum ) {
			mMaximum = maximum;
			if ( mMaximum < mValue ) mValue = mMaximum;
			invalidate();
			updateThumbRect();
		}
		//############################################################################
		float ScrollBar::getMaximum() const {
			return mMaximum;
		}
		//############################################################################
		void ScrollBar::setCoverage( float coverage ) {
			mCoverage = coverage;
			invalidate();
			updateThumbRect();
		}
		//############################################################################
		float ScrollBar::getCoverage() const {
			return mCoverage;
		}
		//############################################################################
		void ScrollBar::setVertical( bool vertical ) {
			mVertical = vertical;
			invalidate();
			updateThumbRect();
		}
		//############################################################################
		bool ScrollBar::getVertical() const {
			return mVertical;
		}
		//############################################################################
		void ScrollBar::onCursor_Enter( Object* sender, Cursor_EventArgs& evtArgs ) {
			/**/
		}
		//############################################################################
		void ScrollBar::onCursor_Leave( Object* sender, Cursor_EventArgs& evtArgs ) {
			/**/
		}
		//############################################################################
		void ScrollBar::onCursor_Press( Object* sender, Cursor_EventArgs& evtArgs ) {
			if ( isInsideThumb( evtArgs.Position ) ) {
				mThumbDownPt = evtArgs.Position;
				mThumbDownValue = mValue;
				grabCursorFocus();
			}
		}
		//############################################################################
		void ScrollBar::onCursor_Release( Object* sender, Cursor_EventArgs& evtArgs ) {
			if ( hasCursorFocus() ) {
				releaseCursorFocus();
			}
		}
		//############################################################################
		void ScrollBar::onCursor_Focused( Object* sender, Focus_EventArgs& evtArgs ) {
			/**/
		}
		//############################################################################
		void ScrollBar::onCursor_FocusLost( Object* sender, Focus_EventArgs& evtArgs ) {
			/**/
		}
		//############################################################################
		void ScrollBar::onCursor_Move( Object* sender, Cursor_EventArgs& evtArgs ) {
			if ( hasCursorFocus() ) {
				FVector2 pos = pointFromScreen( evtArgs.Position );
				pos -= mThumbDownPt;
				float thumbCoveragePercent = mCoverage / mMaximum;
				float travel;
				float space = 1.0f - thumbCoveragePercent;
				float valuePerUnit;
				if ( mVertical ) {
					space = getHeight() * space;
					valuePerUnit = mMaximum / space;
					travel = pos.y;
				} else {
					space = getWidth() * space;
					valuePerUnit = mMaximum / space;
					travel = pos.x;
				}
				setValue( mThumbDownValue + ( valuePerUnit*travel ) );
			}
		}
		//############################################################################
		void ScrollBar::onDraw( Object* sender, Draw_EventArgs& evtArgs ) {
			Brush& b = evtArgs.brush;
			if ( mFaceBG ) {
				b.Image.drawFace( mFaceBG, getRect() );
			}

			updateThumbRect();

			if ( mFaceFG ) {
				b.Image.drawFace( mFaceFG, mThumbRect );
			}
		}
		//############################################################################
		void ScrollBar::onTick( Object* sender, Tick_EventArgs& evtArgs ) {
			/**/
		}
		//############################################################################
		void ScrollBar::updateThumbRect() {
			mThumbRect = getRect();
			if ( mCoverage < mMaximum ) {
				float thumbCoverage = mCoverage / mMaximum;
				if ( mVertical ) {
					mThumbRect.setHeight( mThumbRect.getHeight()* thumbCoverage );
					float remainingSize = getRect().getHeight() - mThumbRect.getHeight();
					float offset = ( mValue / mMaximum ) * remainingSize;
					mThumbRect.offset( FVector2( 0.0f, offset ) );
				} else {
					mThumbRect.setWidth( mThumbRect.getWidth()* thumbCoverage );
					float remainingSize = getRect().getWidth() - mThumbRect.getWidth();
					float offset = ( mValue / mMaximum ) * remainingSize;
					mThumbRect.offset( FVector2( offset, 0.0f ) );
				}
			}
		}
		//############################################################################
		bool ScrollBar::isInsideThumb( const FVector2& point ) const {
			return mThumbRect.isInside( point );
		}
		//############################################################################
		void ScrollBar::eventValueChanged() {
			EventArgs args;
			triggerEvent( "ValueChanged", args );
		}
		//############################################################################
		void ScrollBar::onValueChanged( Object* sender, EventArgs& evtArgs ) {
			/**/
		}
		//############################################################################
	} // namespace Amethyst{
} // namespace OpenGUI{
