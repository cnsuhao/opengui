#include "OpenGUI_BrushModifier.h"
//#include "OpenGUI_Brush.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	// BRUSHMODIFIER IMPLEMENTATIONS
	//############################################################################
	//############################################################################



	// BRUSHTEXT IMPLEMENTATIONS
	//############################################################################
	//############################################################################



	// BRUSHMODIFIERSTACK IMPLEMENTATIONS
	//############################################################################
	//############################################################################
	BrushModifierStack::BrushModifierStack() {
	}
	//############################################################################
	BrushModifierStack::~BrushModifierStack() {
		while(size() > 0)
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
	void BrushModifierStack::push( const BrushModifier_ClipRect& modifier ){
		BrushModifier_ClipRect* tmp = new BrushModifier_ClipRect();
		( *tmp ) = modifier;
		push( tmp );
	}
	//############################################################################
	void BrushModifierStack::push( const BrushModifier_Mask& modifier ){
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

}// namespace OpenGUI {
