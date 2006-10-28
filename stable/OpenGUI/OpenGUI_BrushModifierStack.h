#ifndef C04D4338_3C85_4fc0_9267_FC07CF33F197
#define C04D4338_3C85_4fc0_9267_FC07CF33F197

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_BrushModifier_Rotation.h"
#include "OpenGUI_BrushModifier_Position.h"
#include "OpenGUI_BrushModifier_Color.h"
#include "OpenGUI_BrushModifier_Alpha.h"
#include "OpenGUI_BrushModifier_Mask.h"
#include "OpenGUI_BrushModifier_ClipRect.h"

namespace OpenGUI {

	//! \internal Modifier stack used by Brush class
	class OPENGUI_API BrushModifierStack {
	public:
		BrushModifierStack();
		~BrushModifierStack();

		//! push a copy of the given modifier onto the stack
		void push( const BrushModifier_Rotation& modifier );
		//! push a copy of the given modifier onto the stack
		void push( const BrushModifier_Position& modifier );
		//! push a copy of the given modifier onto the stack
		void push( const BrushModifier_Color& modifier );
		//! push a copy of the given modifier onto the stack
		void push( const BrushModifier_Alpha& modifier );
		//! push a copy of the given modifier onto the stack
		void push( const BrushModifier_Mask& modifier );
		//! push a copy of the given modifier onto the stack
		void push( const BrushModifier_ClipRect& modifier );
		//! push the given modifier onto the stack
		/*! Takes ownership of the memory (will delete internally) */
		void push( BrushModifier* modifier );

		//! push a stack marker
		void pushMarker( void* markerID );
		//! pop back to the stack marker
		void popMarker( void* markerID );

		//! pop the top modifier off the stack
		void pop();
		//! return the stack size
		size_t size() const;

		//! Returns the total of all pushed rotations
		const Radian& getRotation();

		void applyStack( RenderOperation& in_out );
	private:
		typedef std::list<BrushModifier*> BrushModifierPtrStack;
		BrushModifierPtrStack mStack;

		bool mStickColor; // state variable for holding if sticky color has already been applied
		bool mStickMask;  // state variable for holding if sticky mask has already been applied
		bool mRotCacheValid; // state variable, holds if rotation cache is still valid
		Radian mRotCache; // rotation cache
	};

} // namespace OpenGUI {


#endif // C04D4338_3C85_4fc0_9267_FC07CF33F197
