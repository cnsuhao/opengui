#ifndef BD2BBBC1_8162_4B02_A871_4AEAC49BAC26
#define BD2BBBC1_8162_4B02_A871_4AEAC49BAC26

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Imagery.h"
#include "OpenGUI_RenderOperation.h"

namespace OpenGUI {
	class Vertex; //forward declaration

	//############################################################################
	//! \internal Base class for brush modifiers stored by modifier stack
	class OPENGUI_API BrushModifier {
	public:
		BrushModifier() {}
		virtual ~BrushModifier() {}
		enum ModifierType{
			POSITION,
			ROTATION,
			COLOR,
			ALPHA,
			MASK,
			CLIPRECT,
			MARKER
		};
		virtual ModifierType getType() = 0;
		virtual void apply( RenderOperation& in_out ) = 0;
	};
	//############################################################################
	//! \internal Marker modifier used to mark the stack size for guaranteed pop-backs
	class OPENGUI_API BrushModifier_Marker : public BrushModifier {
	public:
		virtual ModifierType getType() {
			return MARKER;
		}
		void* mID;
		virtual void apply( RenderOperation& in_out );
	};
	//############################################################################
	//! \internal Color modifier stored by modifier stack
	class OPENGUI_API BrushModifier_Color : public BrushModifier {
	public:
		virtual ModifierType getType() {
			return COLOR;
		}
		Color mColor;
		virtual void apply( RenderOperation& in_out );
	};
	//############################################################################
	//! \internal Color modifier stored by modifier stack
	class OPENGUI_API BrushModifier_Alpha : public BrushModifier {
	public:
		virtual ModifierType getType() {
			return ALPHA;
		}
		float mAlpha;
		virtual void apply( RenderOperation& in_out );
	};
	//############################################################################
	//! \internal Rotation modifier stored by modifier stack
	class OPENGUI_API BrushModifier_Rotation : public BrushModifier {
	public:
		virtual ModifierType getType() {
			return ROTATION;
		}
		Radian mRotationAngle;
		virtual void apply( RenderOperation& in_out );
	};
	//############################################################################
	//! \internal Position modifier stored by modifier stack
	class OPENGUI_API BrushModifier_Position : public BrushModifier {
	public:
		virtual ModifierType getType() {
			return POSITION;
		}
		FVector2 mPosition;
		virtual void apply( RenderOperation& in_out );
	};
	//############################################################################
	//! \internal Mask modifier stored by modifier stack
	class OPENGUI_API BrushModifier_Mask : public BrushModifier {
	public:
		virtual ModifierType getType() {
			return MASK;
		}
		ImageryPtr mImagery;
		FRect mRect;
		virtual void apply( RenderOperation& in_out );
	};
	//############################################################################
	//! \internal ClipRect modifier stored by modifier stack
	class OPENGUI_API BrushModifier_ClipRect : public BrushModifier {
	public:
		virtual ModifierType getType() {
			return CLIPRECT;
		}
		FRect mRect;
		virtual void apply( RenderOperation& in_out );
	};
	//############################################################################
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

		void applyStack( RenderOperation& in_out );
	private:
		typedef std::list<BrushModifier*> BrushModifierPtrStack;
		BrushModifierPtrStack mStack;

		bool mStickColor; // state variable for holding if sticky color has already been applied
		bool mStickMask;  // state variable for holding if sticky mask has already been applied
	};


} // namespace OpenGUI{

#endif // BD2BBBC1_8162_4B02_A871_4AEAC49BAC26

