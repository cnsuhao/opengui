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
			mValue = value;
			invalidate();
		}
		//############################################################################
		float ScrollBar::getValue() const {
			return mValue;
		}
		//############################################################################
		void ScrollBar::setMaximum( float maximum ) {
			mMaximum = maximum;
			invalidate();
		}
		//############################################################################
		float ScrollBar::getMaximum() const {
			return mMaximum;
		}
		//############################################################################
		void ScrollBar::setCoverage( float coverage ) {
			mCoverage = coverage;
			invalidate();
		}
		//############################################################################
		float ScrollBar::getCoverage() const {
			return mCoverage;
		}
		//############################################################################
		void ScrollBar::setVertical( bool vertical ) {
			mVertical = vertical;
			invalidate();
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
			/**/
		}
		//############################################################################
		void ScrollBar::onCursor_Release( Object* sender, Cursor_EventArgs& evtArgs ) {
			/**/
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
		void ScrollBar::onDraw( Object* sender, Draw_EventArgs& evtArgs ) {
			Brush& b = evtArgs.brush;
			if ( mFaceBG ) {
				b.Image.drawFace( mFaceBG, getRect() );
			}

			float thumbCoverage = mCoverage / mMaximum;

			if ( mFaceFG ) {
				FRect thumbRect = getRect();
				if ( mCoverage < mMaximum ) {
					if ( mVertical ) {
						thumbRect.setHeight( thumbRect.getHeight()* thumbCoverage );
						float remainingSize = getRect().getHeight() - thumbRect.getHeight();
						float offset = ( mValue / mMaximum ) * remainingSize;
						thumbRect.offset( FVector2( 0.0f, offset ) );
					} else {
						thumbRect.setWidth( thumbRect.getWidth()* thumbCoverage );
						float remainingSize = getRect().getWidth() - thumbRect.getWidth();
						float offset = ( mValue / mMaximum ) * remainingSize;
						thumbRect.offset( FVector2( offset, 0.0f ) );
					}
				}
				b.Image.drawFace( mFaceFG, thumbRect );
			}
		}
		//############################################################################
		void ScrollBar::onTick( Object* sender, Tick_EventArgs& evtArgs ) {
			/**/
		}
		//############################################################################
	} // namespace Amethyst{
} // namespace OpenGUI{
