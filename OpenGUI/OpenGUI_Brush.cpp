#include "OpenGUI_Brush.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Font.h"

namespace OpenGUI {
	//initialize static variable
	Brush* Brush::ActiveBrush = 0;

	// BRUSH IMPLEMENTATIONS
	//############################################################################
	Brush::Brush() {
		Text.setBrush( this );
		Primitive.setBrush( this );
		Image.setBrush( this );
		m_RotationCacheValid = false;
	}
	//############################################################################
	Brush::~Brush() {
		if ( this == ActiveBrush )
			ActiveBrush = 0;
	}
	//############################################################################
	/*! \see _popMarker() */
	void Brush::_pushMarker( void* markerID ) {
		mModifierStack.pushMarker( markerID );
	}
	//############################################################################
	/*! \warning pushMarker and popMarker are \b dangerous. They are used internally
	within %OpenGUI and really should not be required by any Widgets for drawing.

	When popping back to a marker, if the given marker cannot be found the
	entire stack will be popped as a result of looking for it. If a marker is
	found while popping that is not the marker given, an exception will be thrown.
	*/
	void Brush::_popMarker( void* markerID ) {
		mModifierStack.popMarker( markerID );
		m_RotationCacheValid = false; // we don't know what was popped, so we have to assume the worst
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
		m_RotationCacheValid = false; // need to invalidate rotation dependent cache on all rotation changes
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
		m_RotationCacheValid = false; // we don't know what was popped, so we have to assume the worst
	}
	//############################################################################
	void Brush::markActive() {
		ActiveBrush = this;
	}
	//############################################################################
	bool Brush::isActive() {
		return this == ActiveBrush;
	}
	//############################################################################
	void Brush::addRenderOperation( RenderOperation& renderOp ) {
		mModifierStack.applyStack( renderOp );
		appendRenderOperation( renderOp );
	}
	//############################################################################
	void Brush::appendRenderOperation( RenderOperation& renderOp ) {
		/* This is overridden by more specific brush classes */
	}
	//############################################################################
	const Radian& Brush::getRotation() {
		return mModifierStack.getRotation();
	}
	//############################################################################
	const FVector2& Brush::getPPU() {
		if ( m_RotationCacheValid )
			return m_PPUcache;
		_UpdateRotationCache();
		return m_PPUcache;
	}
	//############################################################################
	const FVector2& Brush::getUPI() {
		if ( m_RotationCacheValid )
			return m_UPIcache;
		_UpdateRotationCache();
		return m_UPIcache;
	}
	//############################################################################
	void Brush::_UpdateRotationCache() {
		/*
		This works by adding angle dependent weights from each of the two axis for
		both UPI and PPU.

		When at 0/180 degree rotation, the values are returned unmodified.
		When at 90/270 degree rotation, the values are fully swapped.

		All angles in between perform a linear interpolation between the two values
		based on the current angle. The result of sin/cos is reused since the angle
		is constant per function execution, and is absoluted to remove the quadrant
		logic that sin/cos normally come with, since we can't have negative scales.
		*/
		float rad = getRotation().valueRadians();
		const float abssin = Math::FAbs( Math::Sin( rad ) );
		const float abscos = Math::FAbs( Math::Cos( rad ) );
		FVector2 tmp;

		tmp = getPPU_Raw();
		m_PPUcache.x = ( tmp.x * abscos ) + ( tmp.y * abssin );
		m_PPUcache.y = ( tmp.x * abssin ) + ( tmp.y * abscos );

		tmp = getUPI_Raw();
		m_UPIcache.x = ( tmp.x * abscos ) + ( tmp.y * abssin );
		m_UPIcache.y = ( tmp.x * abssin ) + ( tmp.y * abscos );

		m_RotationCacheValid = true;
	}
	//############################################################################
	//############################################################################



	// BRUSHPRIMITIVE IMPLEMENTATIONS
	//############################################################################
	//############################################################################
	void BrushPrimitive::drawLine( const FVector2& start_point, const FVector2& end_point, float thickness ) {
		//translate to the start position
		mParentBrush->pushPosition( start_point );
		FVector2 newEnd = end_point - start_point;

		//rotate to needed angle and transform end point into a line length
		float len = newEnd.length();
		Radian angle( Math::AngleOfPoint( newEnd.x, newEnd.y ) );
		mParentBrush->pushRotation( angle );

		//draw a rect of thickness height and length width, centered on the current origin
		drawRect( FRect( 0.0f, -thickness / 2, len, thickness / 2 ) );

		//pop rotation & translation
		mParentBrush->pop();
		mParentBrush->pop();
	}
	//############################################################################
	void BrushPrimitive::drawLine( const FVector2& start_point, const FVector2& end_point, int thickness ) {
		/*
		Just like our float based thickness counterpart, except we transform the thickness
		from true pixels into the equivalent (rotation aware) thickness according to the
		rendering context's Pixels Per Unit (PPU)
		*/

		//translate to the start position
		mParentBrush->pushPosition( start_point );
		FVector2 newEnd = end_point - start_point;

		//rotate to needed angle and transform end point into a line length
		float len = newEnd.length();
		Radian angle( Math::AngleOfPoint( newEnd.x, newEnd.y ) );
		mParentBrush->pushRotation( angle );

		//generate float_thick based on current PPU map
		float float_thick = (( float )thickness ) * mParentBrush->getPPU().y;

		//draw a rect of thickness height and length width, centered on the current origin
		drawRect( FRect( 0.0f, -float_thick / 2, len, float_thick / 2 ) );

		//pop rotation & translation
		mParentBrush->pop();
		mParentBrush->pop();
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
	/*! Positive \c thickness places the line around the outside of the \c rect.
		Negative \c thickness places the line around the inside of the \c rect.
	*/
	void BrushPrimitive::drawOutlineRect( const FRect& rect, float thickness ) {
		if ( thickness == 0 ) return; // 0? wtf?
		float fthickx = thickness;
		float fthicky = thickness;
		FRect drect; // used for drawing the component rects
		bool drawOutside = true;
		if ( thickness < 0.0f ) drawOutside = false;

		// ### draw horizontal lines ###
		drect = rect;
		drect.setHeight( Math::FAbs( fthicky ) );
		// top first
		if ( drawOutside ) {
			drect.offset( FVector2( 0.0f, -fthicky ) );
			drawRect( drect );
			drect.offset( FVector2( 0.0f, fthicky ) );
		} else { // draw inside
			drawRect( drect );
		}
		// then draw the bottom line
		drect.offset( FVector2( 0.0f, rect.getHeight() ) );
		if ( drawOutside ) {
			drawRect( drect );
		} else { // draw inside
			drect.offset( FVector2( 0.0f, -fthicky ) );
			drawRect( drect );
		}

		// ### draw vertical lines ###
		drect = rect;
		drect.setWidth( Math::FAbs( fthickx ) );
		if ( thickness < 0 ) {
			drect.setHeight( drect.getHeight() - ( Math::FAbs( fthicky ) * 2 ) );
		}
		// first left side
		if ( drawOutside ) {
			drect.offset( FVector2( -fthickx, 0.0f ) );
			drawRect( drect );
			drect.offset( FVector2( fthickx, 0.0f ) );
		} else { // draw inside
			drawRect( drect );
		}
		// then right side
		drect.offset( FVector2( rect.getWidth(), 0.0f ) );
		if ( drawOutside ) {
			drawRect( drect );
		} else { // draw inside
			drect.offset( FVector2( -fthickx, 0.0f ) );
			drawRect( drect );
		}
	}
	//############################################################################
	/*! Positive \c thickness places the line around the outside of the \c rect.
		Negative \c thickness places the line around the inside of the \c rect.
	*/
	void BrushPrimitive::drawOutlineRect( const FRect& rect, int thickness ) {
		if ( thickness == 0 ) return; // 0? wtf?
		float fthickx = (( float )thickness ) * mParentBrush->getPPU().x;
		float fthicky = (( float )thickness ) * mParentBrush->getPPU().y;
		FRect drect; // used for drawing the component rects
		bool drawOutside = true;
		if ( thickness < 0 ) drawOutside = false;

		// ### draw horizontal lines ###
		drect = rect;
		drect.setHeight( Math::FAbs( fthicky ) );
		// top first
		if ( drawOutside ) {
			drect.offset( FVector2( 0.0f, -fthicky ) );
			drawRect( drect );
			drect.offset( FVector2( 0.0f, fthicky ) );
		} else { // draw inside
			drawRect( drect );
		}
		// then draw the bottom line
		drect.offset( FVector2( 0.0f, rect.getHeight() ) );
		if ( drawOutside ) {
			drawRect( drect );
		} else { // draw inside
			drect.offset( FVector2( 0.0f, -fthicky ) );
			drawRect( drect );
		}

		// ### draw vertical lines ###
		drect = rect;
		drect.setWidth( Math::FAbs( fthickx ) );
		if ( thickness < 0 ) {
			drect.setHeight( drect.getHeight() - ( Math::FAbs( fthicky ) * 2 ) );
		}
		// first left side
		if ( drawOutside ) {
			drect.offset( FVector2( -fthickx, 0.0f ) );
			drawRect( drect );
			drect.offset( FVector2( fthickx, 0.0f ) );
		} else { // draw inside
			drawRect( drect );
		}
		// then right side
		drect.offset( FVector2( rect.getWidth(), 0.0f ) );
		if ( drawOutside ) {
			drawRect( drect );
		} else { // draw inside
			drect.offset( FVector2( -fthickx, 0.0f ) );
			drawRect( drect );
		}
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
							  Font& font, float spacing_adjust ) {
		//OG_NYI;
	}
	//############################################################################
	void BrushText::drawTextArea( const std::string& text, const FRect& area, Font& font,
								  TextAlignment horizAlign, TextAlignment vertAlign ) {
		OG_NYI;
	}
	//############################################################################
	//############################################################################
}
