// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_CONFIG.h"
#include "OpenGUI_Brush.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Font.h"
#include "OpenGUI_FontManager.h"

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
		if ( !isActive() ) {
			ActiveBrush = this;
			onActivate();
		}
	}
	//############################################################################
	bool Brush::isActive() {
		return this == ActiveBrush;
	}
	//############################################################################
	void Brush::_clear() {
		markActive();
		onClear();
	}
	//############################################################################
	void Brush::addRenderOperation( RenderOperation& renderOp ) {
		mModifierStack.applyStack( renderOp );
		markActive();
		appendRenderOperation( renderOp );
	}
	//############################################################################
	void Brush::_addRenderOperation( RenderOperation& renderOp ) {
		addRenderOperation( renderOp );
	}
	//############################################################################
	void Brush::pushPixelAlignment() {
		FVector2 origin = mModifierStack.getOrigin();
		const FVector2& PPU = getPPU();

		float tmp = fmodf( origin.x, ( 1.0f ) );
		origin.x = tmp;
		tmp = fmodf( origin.y, ( 1.0f ) );
		origin.y = tmp;

		pushPosition( origin );
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

		All angles in between perform a circular interpolation between the two values
		based on the current angle.
		*/
		float rad = getRotation().valueRadians();
		//const float abssin = Math::FAbs( Math::Sin( rad ) );
		//const float abscos = Math::FAbs( Math::Cos( rad ) );
		const float dev = ( Math::Cos( rad * 2.0f ) / 2.0f ) + 0.5f;
		const float invdev = 1.0f - dev;

		FVector2 tmp;

		tmp = getPPU_Raw();
		m_PPUcache.x = ( tmp.x * dev ) + ( tmp.y * invdev );
		m_PPUcache.y = ( tmp.y * dev ) + ( tmp.x * invdev );
		// This is technically the right way, but produces jittery results with motion (sweeping rotation)
		//m_PPUcache.x = ( tmp.x * abscos ) + ( tmp.y * abssin );
		//m_PPUcache.y = ( tmp.y * abssin ) + ( tmp.x * abscos );

		tmp = getUPI_Raw();
		m_UPIcache.x = ( tmp.x * dev ) + ( tmp.y * invdev );
		m_UPIcache.y = ( tmp.y * dev ) + ( tmp.x * invdev );

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
		drawRect( FRect( 0.0f, -thickness / 2.0f, len, thickness / 2.0f ) );

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
		drawRect( FRect( 0.0f, -float_thick / 2.0f, len, float_thick / 2.0f ) );

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
		if ( thickness == 0.0f ) return; // 0? wtf?
		float fthickx = Math::FAbs( thickness );
		float fthicky = Math::FAbs( thickness );
		FRect drect; // used for drawing the component rects
		bool drawOutside = true;
		if ( thickness < 0.0f ) drawOutside = false;

		// ### draw horizontal lines ###
		drect = rect;
		drect.setHeight( fthicky );
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

		if ( drawOutside ) {
			drect.setHeight( drect.getHeight() + ( fthicky * 2 ) );
			drect.offset( FVector2( 0.0f, -fthicky ) );
		} else {
			drect.setHeight( drect.getHeight() - ( fthicky * 2 ) );
			drect.offset( FVector2( 0.0f, fthicky ) );
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
		float fthickx = Math::FAbs((( float )thickness ) * mParentBrush->getPPU().x );
		float fthicky = Math::FAbs((( float )thickness ) * mParentBrush->getPPU().y );
		FRect drect; // used for drawing the component rects
		bool drawOutside = true;
		if ( thickness < 0 ) drawOutside = false;

		// ### draw horizontal lines ###
		drect = rect;
		drect.setHeight( fthicky );
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

		if ( drawOutside ) {
			drect.setHeight( drect.getHeight() + ( fthicky * 2 ) );
			drect.offset( FVector2( 0.0f, -fthicky ) );
		} else {
			drect.setHeight( drect.getHeight() - ( fthicky * 2 ) );
			drect.offset( FVector2( 0.0f, fthicky ) );
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
	void BrushImagery::drawImage( const ImageryPtr& imageryPtr, const FRect& rect ) {
		RenderOperation renderOp;
		renderOp.triangleList = new TriangleList;
		renderOp.texture = imageryPtr->getTexture();
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
	void BrushImagery::drawImage( const ImageryPtr& imageryPtr, const FVector2& position, const FVector2& size ) {
		FRect rect( position, position + size );
		drawImage( imageryPtr, rect );
	}
	//############################################################################
	void BrushImagery::drawImageUnscaled( const ImageryPtr& imageryPtr, const FVector2& position ) {
		const FVector2& PPU = mParentBrush->getPPU();
		IVector2 size = imageryPtr->getImagesetRect().getSize();
		FVector2 fsize;
		fsize.x = (( float )size.x ) / PPU.x;
		fsize.y = (( float )size.y ) / PPU.y;
		drawImage( imageryPtr, position, fsize );
	}
	//############################################################################
	void BrushImagery::drawImageTiled( const ImageryPtr& imageryPtr, const FRect& rect, float x_tiles, float y_tiles ) {
		if ( x_tiles <= 0.0f || y_tiles <= 0.0f )
			return; // we cannot run with garbage input
		FVector2 rect_size = rect.getSize();
		const FVector2 tilesize( rect_size.x / x_tiles, rect_size.y / y_tiles );
		IVector2 tilecount(( int )( rect_size.x / tilesize.x ), ( int )( rect_size.y / tilesize.y ) );

		FVector2 pos;
		FVector2 size = tilesize;

		mParentBrush->pushClippingRect( rect );
		for ( int y = 0; y <= tilecount.y; y++ ) {
			pos.y = rect.getPosition().y + ((( float )y ) * tilesize.y );
			if ( y == tilecount.y ) {
				if ( pos.y >= rect.max.y )
					break;
			}
			for ( int x = 0; x <= tilecount.x; x++ ) {
				pos.x = rect.getPosition().x + ((( float )x ) * tilesize.x );
				if ( pos.x >= rect.max.x )
					break;
				drawImage( imageryPtr, pos, size );
			}
		}
		mParentBrush->pop();
	}
	//############################################################################
	void BrushImagery::drawImageUnscaledAndTiled( const ImageryPtr& imageryPtr, const FRect& rect ) {
		const FVector2& PPU = mParentBrush->getPPU();
		FVector2 size = rect.getSize();
		IVector2 imgsize = imageryPtr->getImagesetRect().getSize();
		float xtiles, ytiles;
		xtiles = size.x / ((( float )imgsize.x ) / PPU.x );
		ytiles = size.y / ((( float )imgsize.y ) / PPU.y );
		drawImageTiled( imageryPtr, rect, xtiles, ytiles );
	}
	//############################################################################
	void BrushImagery::drawFace( const FacePtr& facePtr, const FRect& rect ) {
		const FVector2& PPU = mParentBrush->getPPU();
		const Face& face = *( facePtr.get() );

		//get total available consumable area
		FVector2 totalArea = rect.getSize();

		// translate coverage area into pixels if we're supposed to
		// and store the query result for later (we'll need it)
		bool inPixels = false;
		if ( facePtr->Metric == Face::FM_PIXELS )
			inPixels = true;
		if ( inPixels )
			totalArea *= PPU;

		FaceDimArray cols, rows;
		const SliceList& sliceList = facePtr->getSlices();
		facePtr->getColumnWidths( totalArea.x, cols );
		facePtr->getRowHeights( totalArea.y, rows );


		//Iterate over all slices and draw them
		FRect sliceRect;
		FVector2 pos;
		FVector2 sizes;
		SliceList::const_iterator iter, iterend = sliceList.end();
		for ( iter = sliceList.begin(); iter != iterend; iter++ ) {
			const Slice& slice = ( *iter );
			if ( slice.Imagery ) { // not all slices have imagery to draw, so we can skip the ones that don't
				// determine starting x position
				pos.x = 0.0f;
				for ( size_t i = 0; i < slice.CellCol; i++ )
					pos.x += cols[i];

				// determine starting y position
				pos.y = 0.0f;
				for ( size_t i = 0; i < slice.CellRow; i++ )
					pos.y += rows[i];

				//determine width
				sizes.x = 0.0f;
				for ( size_t i = 0; i <= slice.ColSpan; i++ )
					sizes.x += cols[slice.CellCol + i];

				//determine height
				sizes.y = 0.0f;
				for ( size_t i = 0; i <= slice.RowSpan; i++ )
					sizes.y += rows[slice.CellRow + i];

				if ( inPixels ) {
					//convert back to units if necessary
					pos /= PPU;
					sizes /= PPU;
				}

				sliceRect.setPosition( pos );
				sliceRect.setSize( sizes );
				sliceRect.offset( rect.getPosition() );

				//draw according to tiling
				if ( slice.Tiled ) {
					drawImageUnscaledAndTiled( slice.Imagery, sliceRect );
				} else {
					drawImage( slice.Imagery, sliceRect );
				}
			}
		}
	}
	//############################################################################
	void BrushImagery::drawFace( const FacePtr& facePtr, const FVector2& position, const FVector2& size ) {
		FRect rect( position.x, position.y, position.x + size.x, position.y + size.y );
		drawFace( facePtr, rect );
	}
	//############################################################################
	//############################################################################


	// BRUSHTEXT IMPLEMENTATIONS
	//############################################################################
	//############################################################################
	void BrushText::_WordWrapText( StringList& strList_in_out, unsigned int charWidth,
								   unsigned int wrapWidth ) {
		if ( charWidth > wrapWidth ) return; // We're not going to split on every character. That's insane.
		const unsigned int maxChars = ( wrapWidth / charWidth ); // number of characters that fully fit into the wrapWidth (drops remainder)

		StringList out; // output buffer, used to temporarily store the output data. We swap() it at the end

		// For each line we check line length to see if we need to wrap.
		// If we do need to wrap, we try to wrap to the last space ' '.
		// If there are no spaces, we fall back to just splitting at the maximum character count
		StringList::iterator iter, iterend = strList_in_out.end();
		iter = strList_in_out.begin();
		while ( iter != iterend ) {
			String& line = ( *iter );
			const String::size_type strLength = line.length_Characters();
			if ( strLength <= maxChars ) { // does the line already fit?
				// if so, then move the whole line into the buffer
				// NB: we do the move this way to avoid unnecessary copying during constructors
				out.push_back( String() ); // add an empty string to the end of the buffer
				StringList::iterator tmpIter = --( out.end() ); // iterator to the newly created entry
				tmpIter->swap( line ); // swap the values of our new entry with the current line of the input buffer
				++iter; // next pass processes next line

			} else { // line doesn't fit, needs to be wrapped
				// no matter what happens we're adding a line to the output, so prep the out buffer
				out.push_back( String() ); // add an empty string to the end of the buffer
				StringList::iterator tmpIter = --( out.end() ); // iterator to the newly created entry

				// search for the best possible split location
				String::size_type splitPos;
				String::iterator maxIter = line.begin();
				for ( size_t c = 0; c < maxChars; ++c ) maxIter.moveNext(); // get an iterator at the mandatory wrap point
				const String::size_type maxPos = maxIter - line.begin();
				splitPos = line.find_last_of( ' ', maxPos );

				if ( String::npos == splitPos ) { // there are no spaces available, we have to forcefully split
					splitPos = maxPos;
					String tmpStr = line.substr( 0, splitPos ); // grab the portion of the line we're keeping
					tmpIter->swap( tmpStr ); // constant time data swap
					line.erase( 0, splitPos ); // erase what we copied from the source line

				} else { // found a space where we should split
					String tmpStr = line.substr( 0, splitPos ); // grab the portion of the line we're keeping
					tmpIter->swap( tmpStr ); // constant time data swap
					line.erase( 0, splitPos + 1 ); // this erase includes the found ' ' code point
				}
				// only increment to next line if current line is now perfectly empty (highly unlikely)
				if ( line.length() == 0 )
					++iter; // we won the lotto... nifty
			} // if ( strLength <= maxChars ) {
		} // while ( iter != iterend ) {

		// and now we swap the data (constant time)
		strList_in_out.swap( out );
		// scope can clean up any left over garbage
	}
	//############################################################################
	void BrushText::drawText( const String& text, const FVector2& position,
							  Font& font, float spacing_adjust ) {
		font.bind();
		PenPosition = position;

		String::const_iterator iter,iterend=text.end();
		for(iter=text.begin(); iter!=iterend; iter.moveNext()){
			Char character = iter.getCharacter();
			if(character == '\n'){
				PenPosition.x = position.x;
				unsigned int lineSpace = font->getLineSpacing( pointsToPixels( font.getSize() ).y );
				PenPosition.y += (( float )lineSpace ) / mParentBrush->getPPU().y;
			}else{
				drawCharacter( character, font );
				PenPosition.x += spacing_adjust;
			}
		}
	}
	//############################################################################
	void BrushText::drawTextArea( const String& text, const FRect& area, Font& font,
								  bool wrap, const TextAlignment alignment ) {
		font.bind();
		const FVector2& PPU = mParentBrush->getPPU();
		IVector2 glyphSize = pointsToPixels( font.getSize() );
		const FVector2 rect_size = area.getSize();
		const float lineAdvance = (( float )font->getLineSpacing( glyphSize.y ) ) / PPU.y;
		float lineSpaceAdjust = 0.0f; // this is applied after each line advance
		FVector2 myPen;

		StringList strList;
		StrConv::tokenize( text, strList, '\n' );

		if ( wrap ) {
			const unsigned int ma = font->getMaxAdvance( glyphSize.x );
			const unsigned int mw = static_cast<unsigned int>( rect_size.x * PPU.x );
			_WordWrapText( strList, ma, mw );
		}

		if ( strList.size() == 0 ) return; //just in case...

		//set up vertical alignment
		if ( alignment.getVertical() == TextAlignment::ALIGN_TOP ) {
			const float descender = (( float )font->getDescender( glyphSize.y ) ) / PPU.y;
			const float ascender = (( float )font->getAscender( glyphSize.y ) ) / PPU.y;
			myPen.y = area.getPosition().y + lineAdvance + descender;
		} else if ( alignment.getVertical() == TextAlignment::ALIGN_BOTTOM ) {
			const float descender = (( float )font->getDescender( glyphSize.y ) ) / PPU.y;
			myPen.y = area.max.y - ((( strList.size() - 1 ) * lineAdvance ) - descender ); // descender is negative, so we subtract to add
		} else if ( alignment.getVertical() == TextAlignment::ALIGN_CENTER ) {
			const float ascender = (( float )font->getAscender( glyphSize.y ) ) / PPU.y;
			const float descender = (( float )font->getDescender( glyphSize.y ) ) / PPU.y;
			float totalheight;
			float extraSpace = lineAdvance - ( ascender - descender ) ;
			totalheight = (( strList.size() ) * lineAdvance );
			totalheight -= ascender;
			totalheight += descender;
			myPen.y = area.getPosition().y + ( rect_size.y / 2.0f ); // move to center
			myPen.y -= totalheight / 2.0f; // retract half of the total height
			myPen.y += (( ascender + descender ) / 2.0f ) + extraSpace;
		} else if ( alignment.getVertical() == TextAlignment::ALIGN_JUSTIFIED ) {
			const float ascender = (( float )font->getAscender( glyphSize.y ) ) / PPU.y;
			const float descender = (( float )font->getDescender( glyphSize.y ) ) / PPU.y;
			float totalheight;
			totalheight = (( strList.size() - 1 ) * lineAdvance );
			totalheight += lineAdvance - descender;
			//totalheight -= descender; // descender is negative, so we subtract to add
			if ( totalheight > rect_size.y ) {
				//fall back to ALIGN_TOP if we can't justify correctly
				myPen.y = area.getPosition().y + lineAdvance;
			} else {
				myPen.y = area.getPosition().y + lineAdvance;
				//lineSpaceAdjust = (rect_size.y - totalheight) / (float)(strList.size() -1.0f);
				lineSpaceAdjust = ( float )( rect_size.y - totalheight ) / ( float )strList.size();
			}
		}


		//for each line of text, we will render as necessary according to horizontal alignment
		StringList::iterator iter = strList.begin();
		while ( iter != strList.end() ) {
			String& text = ( *iter );
			if ( alignment.getHorizontal() == TextAlignment::ALIGN_LEFT ) {
				myPen.x = area.getPosition().x;
				drawText( text, myPen, font );
			} else if ( alignment.getHorizontal() == TextAlignment::ALIGN_CENTER ) {
				int w = font->getTextWidth( glyphSize, text );
				float fw = (( float )w ) / PPU.x;
				myPen.x = (( area.max.x + area.min.x ) / 2.0f ) - ( fw / 2.0f );
				drawText( text, myPen, font );
			} else if ( alignment.getHorizontal() == TextAlignment::ALIGN_RIGHT ) {
				int w = font->getTextWidth( glyphSize, text );
				float fw = (( float )w ) / PPU.x;
				myPen.x = area.max.x - fw;
				drawText( text, myPen, font );
			} else if ( alignment.getHorizontal() == TextAlignment::ALIGN_JUSTIFIED ) {
				int w = font->getTextWidth( glyphSize, text );
				float fw = (( float )w ) / PPU.x;
				myPen.x = area.getPosition().x;
				float adjust;
				if ( fw < rect_size.x && fw > rect_size.x * 0.65f )
					adjust = ( rect_size.x - fw ) / text.length();
				else
					adjust = 0.0f;
				drawText( text, myPen, font, adjust );
			}

			myPen.y += lineAdvance;
			myPen.y += lineSpaceAdjust;
			iter++;
		}

	}
	//############################################################################
	void BrushText::drawCharacter( const Char character, Font& font ) {
		font.bind();
		const FVector2& PPU = mParentBrush->getPPU();

		IVector2 glyphSize = pointsToPixels( font.getSize() );

		if ( glyphSize.x == 0 || glyphSize.y == 0 )
			return; // abort if we have nothing worth drawing

		FontGlyph glyph;
		font->getGlyph( character, glyphSize, glyph );

		FVector2 glyphSizeU;
		glyphSizeU.x = glyph.metrics.width / PPU.x;
		glyphSizeU.y = glyph.metrics.height / PPU.y;

		FVector2 glyphPosition = PenPosition;

		// We need to do our best to provide pixel alignment, so here we fix the glyph position according to PPU.
		// This will cause proper pixel alignment when it is available.
		// (Drawing context is translated a pixel aligned amount
		float tmp = fmodf( PenPosition.x, ( 1.0f / PPU.x ) );
		glyphPosition.x -= tmp;
		tmp = fmodf( PenPosition.y, ( 1.0f / PPU.y ) );
		glyphPosition.y -= tmp;

		glyphPosition.y -= (( float )glyph.metrics.horiBearingY ) / PPU.y;
		glyphPosition.x += (( float )glyph.metrics.horiBearingX ) / PPU.x;

		mParentBrush->Image.drawImage( glyph.imageryPtr, glyphPosition, glyphSizeU );
		PenPosition.x += (( float )glyph.metrics.horiAdvance ) / PPU.x;
	}
	//############################################################################
	IVector2 BrushText::pointsToPixels( float pointSize ) {
		const FVector2& PPU = mParentBrush->getPPU();
		const FVector2& UPI = mParentBrush->getUPI();

		float inchSize = pointSize / 72; // points are 1/72 of an inch

		FVector2 glyphUnitSize; // unit size = units per inch * inch size
		glyphUnitSize.x = inchSize * UPI.x;
		glyphUnitSize.y = inchSize * UPI.y;

		// pixel size = unit size * pixels per unit
		IVector2 glyphSize(
			(( int )( glyphUnitSize.x * PPU.x ) ),
			(( int )( glyphUnitSize.y * PPU.y ) )
		);

		return glyphSize;
	}
	//############################################################################
	//############################################################################
}
