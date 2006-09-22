#include "OpenGUI_Types.h"
#include "OpenGUI_Math.h"
#include "OpenGUI_BrushModifier.h"
//#include "OpenGUI_Brush.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
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
					float y = vert.position.x;
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
	BrushModifierStack::BrushModifierStack() {}
	//############################################################################
	BrushModifierStack::~BrushModifierStack() {
		while ( size() > 0 )
			pop();
	}
	//############################################################################
	void BrushModifierStack::push( A_BrushModifier* modifier ) {
		mStack.push_back( modifier );
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
		A_BrushModifier* tmp = mStack.back();
		mStack.pop_back();
		delete tmp;
	}
	//############################################################################
	size_t BrushModifierStack::size() const {
		return mStack.size();
	}
	//############################################################################
	void BrushModifierStack::applyStack(RenderOperation& in_out){
		for( BrushModifierPtrStack::iterator iter = mStack.begin();
			iter != mStack.end(); iter++ ){
				A_BrushModifier* mod = (*iter);
				mod->apply( in_out );
		}
	}

}// namespace OpenGUI {
