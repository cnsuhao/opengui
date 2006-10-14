#include "OpenGUI_Types.h"
#include "OpenGUI_Math.h"
#include "OpenGUI_BrushModifier.h"
//#include "OpenGUI_Brush.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	// BRUSHMODIFIER_MARKER IMPLEMENTATIONS
	//############################################################################
	//############################################################################
	void BrushModifier_Marker::apply( RenderOperation& in_out ) {
		/**/
	}
	//############################################################################

	// BRUSHMODIFIER_COLOR IMPLEMENTATIONS
	//############################################################################
	//############################################################################
	void BrushModifier_Color::apply( RenderOperation& in_out ) {
		for ( TriangleList::iterator iter = in_out.triangleList->begin();
				iter != in_out.triangleList->end(); iter++ ) {
			Triangle& tri = ( *iter );
			tri.vertex[0].color = mColor;
			tri.vertex[1].color = mColor;
			tri.vertex[2].color = mColor;
		}
	}
	//############################################################################


	// BRUSHMODIFIER_ALPHA IMPLEMENTATIONS
	//############################################################################
	//############################################################################
	void BrushModifier_Alpha::apply( RenderOperation& in_out ) {
		for ( TriangleList::iterator iter = in_out.triangleList->begin();
				iter != in_out.triangleList->end(); iter++ ) {
			Triangle& tri = ( *iter );
			tri.vertex[0].color.Alpha *= mAlpha;
			tri.vertex[1].color.Alpha *= mAlpha;
			tri.vertex[2].color.Alpha *= mAlpha;
		}
	}
	//############################################################################


	// BRUSHMODIFIER_ROTATION IMPLEMENTATIONS
	//############################################################################
	//############################################################################
	void BrushModifier_Rotation::apply( RenderOperation& in_out ) {
		/*
		We're performing the same rotation angle for all vertices,
		so we can reuse pre calculated Sin and Cos results
		*/
		const float preCos = Math::Cos( mRotationAngle.valueRadians() );
		const float preSin = Math::Sin( mRotationAngle.valueRadians() );

		for ( TriangleList::iterator iter = in_out.triangleList->begin();
				iter != in_out.triangleList->end(); iter++ ) {
			Triangle& tri = ( *iter );
			for ( int i = 0; i < 3; i++ ) {
				Vertex& vert = tri.vertex[i];
				float x = vert.position.x;
				float y = vert.position.y;
				vert.position.x = preCos * x - preSin * y;
				vert.position.y = preSin * x + preCos * y;
			}
		}
	}
	//############################################################################


	// BRUSHMODIFIER_POSITION IMPLEMENTATIONS
	//############################################################################
	//############################################################################
	void BrushModifier_Position::apply( RenderOperation& in_out ) {
		for ( TriangleList::iterator iter = in_out.triangleList->begin();
				iter != in_out.triangleList->end(); iter++ ) {
			Triangle& tri = ( *iter );
			for ( int i = 0; i < 3; i++ ) {
				Vertex& vert = tri.vertex[i];
				vert.position = mPosition + vert.position;
			}
		}
	}
	//############################################################################


	// BRUSHMODIFIER_MASK IMPLEMENTATIONS
	//############################################################################
	//############################################################################
	void BrushModifier_Mask::apply( RenderOperation& in_out ) {}
	//############################################################################


	// BRUSHMODIFIER_CLIPRECT IMPLEMENTATIONS
	//############################################################################
	//############################################################################
	void BrushModifier_ClipRect::apply( RenderOperation& in_out ) {}
	//############################################################################




	// BRUSHMODIFIERSTACK IMPLEMENTATIONS
	//############################################################################
	//############################################################################
	BrushModifierStack::BrushModifierStack() {
		mRotCacheValid = false; // rotation cache starts invalid
	}
	//############################################################################
	BrushModifierStack::~BrushModifierStack() {
		while ( size() > 0 )
			pop();
	}
	//############################################################################
	void BrushModifierStack::push( BrushModifier* modifier ) {
		mStack.push_front( modifier );
		if ( modifier->getType() == BrushModifier::ROTATION )
			mRotCacheValid = false;
	}
	//############################################################################
	void BrushModifierStack::push( const BrushModifier_Rotation& modifier ) {
		BrushModifier_Rotation* tmp = new BrushModifier_Rotation();
		( *tmp ) = modifier;
		push( tmp );
	}
	//############################################################################
	void BrushModifierStack::push( const BrushModifier_Position& modifier ) {
		BrushModifier_Position* tmp = new BrushModifier_Position();
		( *tmp ) = modifier;
		push( tmp );
	}
	//############################################################################
	void BrushModifierStack::push( const BrushModifier_Color& modifier ) {
		BrushModifier_Color* tmp = new BrushModifier_Color();
		( *tmp ) = modifier;
		push( tmp );
	}
	//############################################################################
	void BrushModifierStack::push( const BrushModifier_Alpha& modifier ) {
		BrushModifier_Alpha* tmp = new BrushModifier_Alpha();
		( *tmp ) = modifier;
		push( tmp );
	}
	//############################################################################
	void BrushModifierStack::push( const BrushModifier_ClipRect& modifier ) {
		BrushModifier_ClipRect* tmp = new BrushModifier_ClipRect();
		( *tmp ) = modifier;
		push( tmp );
	}
	//############################################################################
	void BrushModifierStack::push( const BrushModifier_Mask& modifier ) {
		BrushModifier_Mask* tmp = new BrushModifier_Mask();
		( *tmp ) = modifier;
		push( tmp );
	}
	//############################################################################
	void BrushModifierStack::pop() {
		BrushModifier* tmp = mStack.front();
		if ( tmp->getType() == BrushModifier::MARKER )
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "Cannot pop stack past marker", __FUNCTION__ );
		if ( tmp->getType() == BrushModifier::ROTATION )
			mRotCacheValid = false;
		mStack.pop_front();
		delete tmp;
	}
	//############################################################################
	size_t BrushModifierStack::size() const {
		return mStack.size();
	}
	//############################################################################
	void BrushModifierStack::applyStack( RenderOperation& in_out ) {
		//reset stickies
		mStickColor = false;
		mStickMask = false;

		for ( BrushModifierPtrStack::iterator iter = mStack.begin();
				iter != mStack.end(); iter++ ) {
			BrushModifier* mod = ( *iter );
			if ( mod->getType() == BrushModifier::COLOR ) {
				if ( ! mStickColor ) {
					mStickColor = true;
					mod->apply( in_out );
				}
			} else if ( mod->getType() == BrushModifier::MASK ) {
				if ( !mStickMask ) {
					mStickMask = true;
					mod->apply( in_out );
				}
			} else {
				mod->apply( in_out );
			}
		}
	}
	//############################################################################
	void BrushModifierStack::pushMarker( void* markerID ) {
		BrushModifier_Marker* tmp = new BrushModifier_Marker;
		tmp->mID = markerID;
		push( tmp );
	}
	//############################################################################
	void BrushModifierStack::popMarker( void* markerID ) {
		if ( mStack.size() == 0 )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Failed to find stack marker", __FUNCTION__ );

		if ( mStack.front()->getType() == BrushModifier::MARKER ) {
			BrushModifier_Marker* tmp = dynamic_cast<BrushModifier_Marker*>( mStack.front() );
			void* t = tmp->mID;
			if ( t == markerID ) {
				mStack.pop_front();
				delete tmp;
			} else
				OG_THROW( Exception::ERR_INTERNAL_ERROR, "Found non-matching stack marker", __FUNCTION__ );
		} else {
			pop();
			popMarker( markerID );
		}
	}
	//############################################################################
	const Radian& BrushModifierStack::getRotation() {
		// if the cache is valid, just return it
		if ( mRotCacheValid )
			return mRotCache;
		//otherwise we'll need to rebuild the cache before we return
		mRotCache = 0;
		for ( BrushModifierPtrStack::iterator iter = mStack.begin();
				iter != mStack.end(); iter++ ) {
			BrushModifier* mod = ( *iter );
			if ( mod->getType() == BrushModifier::ROTATION ) {
				BrushModifier_Rotation* rot = static_cast<BrushModifier_Rotation*>( mod );
				mRotCache = mRotCache + rot->mRotationAngle;
			}
		}
		mRotCacheValid = true;
		return mRotCache;
	}
	//############################################################################
}// namespace OpenGUI {
