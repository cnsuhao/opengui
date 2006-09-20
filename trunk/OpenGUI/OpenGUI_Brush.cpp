#include "OpenGUI_Brush.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	// BRUSH IMPLEMENTATIONS
	//############################################################################
	Brush::Brush() {
		Text.setBrush( this );
		Primitive.setBrush( this );
		Image.setBrush( this );
	}
	//############################################################################
	Brush::~Brush() {
		OG_NYI;
	}
	//############################################################################
	void Brush::pushPosition( float x_offset, float y_offset ) {
		pushPosition( FVector2( x_offset, y_offset ) );
	}
	//############################################################################
	void Brush::pushPosition( const FVector2& offset ) {
		BrushModifier_Position pos;
		pos.mPosition = offset;
		mModifierStack.push( pos );
	}
	//############################################################################
	void Brush::pushRotation( const Radian& angle ) {
		BrushModifier_Rotation rot;
		rot.mRotationAngle = angle;
		mModifierStack.push( rot );
	}
	//############################################################################
	void Brush::pushColor( const Color& color ) {
		BrushModifier_Color colorOp;
		colorOp.mColor = color;
		mModifierStack.push( colorOp );
	}
	//############################################################################
	void Brush::pushClippingRect( const FRect& rect ) {
		BrushModifier_ClipRect modifier;
		modifier.mRect = rect;
		mModifierStack.push( modifier );
	}
	//############################################################################
	void Brush::pushMask( ImageryPtr mask_imagery, const FRect& mask_rect ) {
		BrushModifier_Mask modifier;
		modifier.mImagery = mask_imagery;
		modifier.mRect = mask_rect;
		mModifierStack.push( modifier );
	}
	//############################################################################
	void Brush::pushMaskUnscaled( ImageryPtr mask_imagery, const FVector2& mask_position ) {
		//needs to determine the unscaled rect according to pixels
		OG_NYI;
	}
	//############################################################################
	void Brush::pop() {
		mModifierStack.pop();
	}
	//############################################################################
	void Brush::clearStack() {
		while ( mModifierStack.size() > 0 )
			mModifierStack.pop();
	}
	//############################################################################
	size_t Brush::stackSize() {
		return mModifierStack.size();
	}
	//############################################################################
	const FRect& Brush::getDrawArea() {
		OG_NYI;
	}
	//############################################################################
	//############################################################################



	// BRUSHPRIMITIVE IMPLEMENTATIONS
	//############################################################################
	//############################################################################



	// BRUSHIMAGERY IMPLEMENTATIONS
	//############################################################################
	//############################################################################



	// BRUSHTEXT IMPLEMENTATIONS
	//############################################################################
	//############################################################################

}
