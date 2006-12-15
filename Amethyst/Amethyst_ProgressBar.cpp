// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "Amethyst_ProgressBar.h"
#include "OpenGUI_Macros.h"

namespace OpenGUI {
	namespace Amethyst {
		//############################################################################
		SimpleProperty_Face( PBProp_BGFace, "BGFace", ProgressBar, getBGFace, setBGFace );
		SimpleProperty_Face( PBProp_FillFace, "FillFace", ProgressBar, getFillFace, setFillFace );
		SimpleProperty_Float( PBProp_StepSize, "Step_Size", ProgressBar, getStepSize, setStepSize );
		SimpleProperty_Float( PBProp_Total, "Total", ProgressBar, getTotal, setTotal );
		SimpleProperty_Float( PBProp_Value, "Value", ProgressBar, getValue, setValue );
		SimpleProperty_Bool( PBProp_Vertical, "Vertical", ProgressBar, getVertical, setVertical );
		SimpleProperty_Bool( PBProp_Inverted, "Inverted", ProgressBar, getInverted, setInverted );
		SimpleProperty_Color( PBProp_FillColor, "FillColor", ProgressBar, getFillColor, setFillColor );
		SimpleProperty_Color( PBProp_BGColor, "BGColor", ProgressBar, getBGColor, setBGColor );
		SimpleProperty_Float( PBProp_BarPadVert, "BarPadVert", ProgressBar, getBarPadVert, setBarPadVert );
		SimpleProperty_Float( PBProp_BarPadHoriz, "BarPadHoriz", ProgressBar, getBarPadHoriz, setBarPadHoriz );
		//############################################################################
		class PBMethod_doStep: public ObjectMethod {
		public:
			~PBMethod_doStep() {}
			virtual const char* getAccessorName() {
				return "doStep";
			}
			virtual void invoke( Object& objectRef, ValueList& paramIn, ValueList& returnOut ) {
				try {
					ProgressBar& pb = dynamic_cast<ProgressBar&>( objectRef );
					pb.doStep();
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
		}
		gPBMethod_doStep;
		//############################################################################
		class ProgressBar_ObjectAccessorList : public ObjectAccessorList {
		public:
			ProgressBar_ObjectAccessorList() {
				addAccessor( &PBProp_BGFace );
				addAccessor( &PBProp_FillFace );
				addAccessor( &PBProp_StepSize );
				addAccessor( &PBProp_Total );
				addAccessor( &PBProp_Value );
				addAccessor( &PBProp_Vertical );
				addAccessor( &PBProp_Inverted );
				addAccessor( &PBProp_FillColor );
				addAccessor( &PBProp_BGColor );
				addAccessor( &PBProp_BarPadVert );
				addAccessor( &PBProp_BarPadHoriz );
				addAccessor( &gPBMethod_doStep );
			}
			~ProgressBar_ObjectAccessorList() {}
		}
		gProgressBar_ObjectAccessorList;
		//############################################################################
		//############################################################################
		ObjectAccessorList* ProgressBar::getAccessors() {
			return &gProgressBar_ObjectAccessorList;
		}
		//############################################################################
		Widget* ProgressBar::createProgressBarFactory() {
			return new ProgressBar;
		}
		//############################################################################
		ProgressBar::ProgressBar() {
			if ( gProgressBar_ObjectAccessorList.getParent() == NULL )
				gProgressBar_ObjectAccessorList.setParent( Control::getAccessors() );

			// initialize the defaults
			mTotal = 100.0f;
			mValue = 0.0f;
			mStepSize = 1.0f;
			mVertical = false;
			mInverted = false;
			mPadHoriz = 0.0f;
			mPadVert = 0.0f;
		}
		//############################################################################
		ProgressBar::~ProgressBar() {
			/**/
		}
		//############################################################################
		void ProgressBar::setTotal( float total ) {
			mTotal = total;
			invalidate();
		}
		//############################################################################
		float ProgressBar::getTotal() {
			return mTotal;
		}
		//############################################################################
		void ProgressBar::setStepSize( float stepSize ) {
			mStepSize = stepSize;
			invalidate();
		}
		//############################################################################
		float ProgressBar::getStepSize() const {
			return mStepSize;
		}
		//############################################################################
		void ProgressBar::doStep() {
			OG_NYI;
		}
		//############################################################################
		void ProgressBar::setValue( float newValue ) {
			mValue = newValue;
			invalidate();
		}
		//############################################################################
		float ProgressBar::getValue() const {
			return mValue;
		}
		//############################################################################
		void ProgressBar::setBGColor( const Color &color ) {
			mColorBG = color;
			invalidate();
		}
		//############################################################################
		const Color& ProgressBar::getBGColor() const {
			return mColorBG;
		}
		//############################################################################
		void ProgressBar::setFillColor( const Color &color ) {
			mColorFG = color;
			invalidate();
		}
		//############################################################################
		const Color& ProgressBar::getFillColor() const {
			return mColorFG;
		}
		//############################################################################
		void ProgressBar::setBGFace( FacePtr facePtr ) {
			mFaceBG = facePtr;
			invalidate();
		}
		//############################################################################
		FacePtr ProgressBar::getBGFace() const {
			return mFaceBG;
		}
		//############################################################################
		void ProgressBar::setFillFace( FacePtr facePtr ) {
			mFaceFG = facePtr;
			invalidate();
		}
		//############################################################################
		FacePtr ProgressBar::getFillFace() const {
			return mFaceFG;
		}
		//############################################################################
		void ProgressBar::setVertical( bool vertical ) {
			mVertical = vertical;
			invalidate();
		}
		//############################################################################
		bool ProgressBar::getVertical() const {
			return mVertical;
		}
		//############################################################################
		void ProgressBar::setInverted( bool inverted ) {
			mInverted = inverted;
			invalidate();
		}
		//############################################################################
		bool ProgressBar::getInverted() const {
			return mInverted;
		}
		//############################################################################
		void ProgressBar::setBarPadHoriz( float padding ) {
			mPadHoriz = padding;
			invalidate();
		}
		//############################################################################
		float ProgressBar::getBarPadHoriz() const {
			return mPadHoriz;
		}
		//############################################################################
		void ProgressBar::setBarPadVert( float padding ) {
			mPadVert = padding;
			invalidate();
		}
		//############################################################################
		float ProgressBar::getBarPadVert() const {
			return mPadVert;
		}
		//############################################################################
		void ProgressBar::onDraw( Object* sender, Draw_EventArgs& evtArgs ) {
			Brush& b = evtArgs.brush;
			// draw the background
			b.pushColor( mColorBG );
			if ( mFaceBG )
				b.Image.drawFace( mFaceBG, getRect() );
			else
				b.Primitive.drawRect( getRect() );
			b.pop(); // pop BG color

			// calculate the available bar area based on the padding
			FRect barArea = getRect();
			barArea.setWidth( barArea.getWidth() - ( mPadHoriz * 2.0f ) );
			barArea.setHeight( barArea.getHeight() - ( mPadVert * 2.0f ) );
			barArea.offset( FVector2( mPadHoriz, mPadVert ) );

			// get fill coverage
			float fillPerc = mValue / mTotal;
			if ( fillPerc > 1.0f ) fillPerc = 1.0f; // clamp to 1.0f max
			if ( fillPerc < 0.0f ) fillPerc = 0.0f; // clamp to 0.0f min
			if ( fillPerc <= 0.0f ) return; // abort here if there is nothing worth drawing
			if ( mVertical ) {
				if ( mInverted ) {
					barArea.setHeight( barArea.getHeight() * fillPerc );
				} else {
					barArea.offset( FVector2( 0.0f, barArea.getHeight() ) );
					barArea.setHeight( barArea.getHeight() * fillPerc );
					barArea.offset( FVector2( 0.0f, -barArea.getHeight() ) );
				}
			} else {
				if ( mInverted ) {
					barArea.offset( FVector2( barArea.getWidth(), 0.0f ) );
					barArea.setWidth( barArea.getWidth() * fillPerc );
					barArea.offset( FVector2( -barArea.getWidth(), 0.0f ) );
				} else {
					barArea.setWidth( barArea.getWidth() * fillPerc );
				}
			}

			// draw the fill bar
			b.pushColor( mColorFG );
			if ( mFaceFG )
				b.Image.drawFace( mFaceFG, barArea );
			else
				b.Primitive.drawRect( barArea );
			b.pop(); // pop FG color
		}
		//############################################################################
	} //namespace Amethyst {
} // namespace OpenGUI {
