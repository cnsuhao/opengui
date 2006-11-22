#include "OpenGUI_BrushModifierStack.h"
#include "OpenGUI_BrushModifier_Marker.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
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

		BrushModifierPtrStack::iterator iter, iterend = mStack.end();
		for ( iter = mStack.begin(); iter != iterend; iter++ ) {
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
	FVector2 BrushModifierStack::getOrigin() {
		FVector2 origin( 0.0f, 0.0f );
		BrushModifierPtrStack::reverse_iterator iter, iterend = mStack.rend();
		for ( iter = mStack.rbegin(); iter != iterend; iter++ ) {
			BrushModifier* mod = ( *iter );
			if ( mod->getType() == BrushModifier::POSITION ) {
				BrushModifier_Position* pos = static_cast<BrushModifier_Position*>( mod );
				origin = origin - pos->mPosition;
			} else if ( mod->getType() == BrushModifier::ROTATION ) {
				BrushModifier_Rotation* rot = static_cast<BrushModifier_Rotation*>( mod );
				const float preCos = Math::Cos( -( rot->mRotationAngle.valueRadians() ) );
				const float preSin = Math::Sin( -( rot->mRotationAngle.valueRadians() ) );
				float x = origin.x;
				float y = origin.y;
				origin.x = preCos * x - preSin * y;
				origin.y = preSin * x + preCos * y;
			}
		}
		return origin;
	}
	//############################################################################
	const Radian& BrushModifierStack::getRotation() {
		// if the cache is valid, just return it
		if ( mRotCacheValid )
			return mRotCache;
		//otherwise we'll need to rebuild the cache before we return
		mRotCache = 0;
		BrushModifierPtrStack::iterator iter, iterend = mStack.end();
		for ( iter = mStack.begin(); iter != iterend; iter++ ) {
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
} // namespace OpenGUI{
