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
	void Brush::pushAlpha( float alpha ) {
		BrushModifier_Alpha alphaOp;
		alphaOp.mAlpha = alpha;
		mModifierStack.push( alphaOp );
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
	const FRect& Brush::getDrawArea() {
		OG_NYI;
	}
	//############################################################################
	void Brush::addRenderOperation( RenderOperation& renderOp ) {
		mModifierStack.applyStack( renderOp );
		OG_NYI;
	}
	//############################################################################
	void Brush::processRenderOperation( RenderOperation& renderOp ) {
		/**/
	}
	//############################################################################
	//############################################################################



	// BRUSHPRIMITIVE IMPLEMENTATIONS
	//############################################################################
	//############################################################################
	void BrushPrimitive::drawLine( const FVector2& start_point, const FVector2& end_point, float thickness ) {
		OG_NYI;
	}
	//############################################################################
	void BrushPrimitive::drawLine( const FVector2& start_point, const FVector2& end_point, int thickness ) {
		OG_NYI;
	}
	//############################################################################
	void BrushPrimitive::drawRect( const FRect& rect ) {
		RenderOperation renderOp;
		renderOp.triangleList = new TriangleList;
		TriangleList& tl = *renderOp.triangleList;

		FVector2 ul = rect.min;
		FVector2 ur = FVector2( rect.max.x, rect.min.y );
		FVector2 ll = FVector2( rect.min.x, rect.max.y );
		FVector2 lr = rect.max;

		Triangle tri;
		tri.vertex[0].position = ul;
		tri.vertex[1].position = ll;
		tri.vertex[2].position = lr;
		tl.push_back( tri );

		tri.vertex[0].position = lr;
		tri.vertex[1].position = ur;
		tri.vertex[2].position = ul;
		tl.push_back( tri );

		mParentBrush->addRenderOperation( renderOp );
	}
	//############################################################################
	void BrushPrimitive::drawOutlineRect( const FRect& rect, float thickness ) {
		OG_NYI;
	}
	//############################################################################
	void BrushPrimitive::drawOutlineRect( const FRect& rect, int thickness ) {
		OG_NYI;
	}
	//############################################################################
	//############################################################################


	// BRUSHIMAGERY IMPLEMENTATIONS
	//############################################################################
	//############################################################################
	void BrushImagery::drawImage( ImageryPtr imageryPtr, const FRect& rect ) {
		RenderOperation renderOp;
		renderOp.triangleList = new TriangleList;
		TriangleList& tl = *renderOp.triangleList;

		FVector2 ul = rect.min;
		FVector2 ur = FVector2( rect.max.x, rect.min.y );
		FVector2 ll = FVector2( rect.min.x, rect.max.y );
		FVector2 lr = rect.max;

		FRect UVRect = imageryPtr->getTextureUVRect();
		FVector2 uv_ul = UVRect.min;
		FVector2 uv_ur = FVector2( UVRect.max.x, UVRect.min.y );
		FVector2 uv_ll = FVector2( UVRect.min.x, UVRect.max.y );
		FVector2 uv_lr = UVRect.max;

		Triangle tri;
		tri.vertex[0].position = ul;
		tri.vertex[0].textureUV = uv_ul;
		tri.vertex[1].position = ll;
		tri.vertex[1].textureUV = uv_ll;
		tri.vertex[2].position = lr;
		tri.vertex[2].textureUV = uv_lr;
		tl.push_back( tri );

		tri.vertex[0].position = lr;
		tri.vertex[0].textureUV = uv_lr;
		tri.vertex[1].position = ur;
		tri.vertex[1].textureUV = uv_ur;
		tri.vertex[2].position = ul;
		tri.vertex[2].textureUV = uv_ul;
		tl.push_back( tri );

		mParentBrush->addRenderOperation( renderOp );
	}
	//############################################################################
	void BrushImagery::drawImage( ImageryPtr imageryPtr, const FVector2& position, const FVector2& size ) {
		FRect rect = FRect( position, position + size );
		drawImage( imageryPtr, rect );
	}
	//############################################################################
	void BrushImagery::drawImageUnscaled( ImageryPtr imageryPtr, const FVector2& position ) {
		OG_NYI;
	}
	//############################################################################
	void BrushImagery::drawImageTiled( ImageryPtr imageryPtr, const FRect& rect, float x_tiles, float y_tiles ) {
		OG_NYI;
	}
	//############################################################################
	void BrushImagery::drawImageUnscaledAndTiled( ImageryPtr imageryPtr, const FRect& rect ) {
		OG_NYI;
	}
	//############################################################################
	//############################################################################


	// BRUSHTEXT IMPLEMENTATIONS
	//############################################################################
	//############################################################################
	void BrushText::drawText( const std::string& text, const FVector2& position,
							  FontPtr font, float size, float spacing_adjust ) {
		OG_NYI;
	}
	//############################################################################
	void BrushText::drawTextArea( const std::string& text, const FRect& area, FontPtr font,
								  float size, TextAlignment horizAlign, TextAlignment vertAlign ) {
		OG_NYI;
	}
	//############################################################################
	//############################################################################
}
