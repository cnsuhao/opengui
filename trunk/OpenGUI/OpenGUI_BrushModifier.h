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
	class OPENGUI_API A_BrushModifier {
	public:
		A_BrushModifier() {}
		virtual ~A_BrushModifier() {}
		enum ModifierType{
			POSITION,
			ROTATION,
			COLOR,
			MASK,
			CLIPRECT
		};
		virtual ModifierType getType() = 0;
		virtual void apply(RenderOperationList& in_out)=0;
	};
	//############################################################################
	//! \internal Color modifier stored by modifier stack
	class OPENGUI_API BrushModifier_Color : public A_BrushModifier {
	public:
		virtual ModifierType getType() {
			return COLOR;
		}
		Color mColor;
		virtual void apply(RenderOperationList& in_out);
	};
	//############################################################################
	//! \internal Rotation modifier stored by modifier stack
	class OPENGUI_API BrushModifier_Rotation : public A_BrushModifier {
	public:
		virtual ModifierType getType() {
			return ROTATION;
		}
		Radian mRotationAngle;
		virtual void apply(RenderOperationList& in_out);
	};
	//############################################################################
	//! \internal Position modifier stored by modifier stack
	class OPENGUI_API BrushModifier_Position : public A_BrushModifier {
	public:
		virtual ModifierType getType() {
			return POSITION;
		}
		FVector2 mPosition;
		virtual void apply(RenderOperationList& in_out);
	};
	//############################################################################
	//! \internal Mask modifier stored by modifier stack
	class OPENGUI_API BrushModifier_Mask : public A_BrushModifier {
	public:
		virtual ModifierType getType() {
			return MASK;
		}
		ImageryPtr mImagery;
		FRect mRect;
		virtual void apply(RenderOperationList& in_out);
	};
	//############################################################################
	//! \internal ClipRect modifier stored by modifier stack
	class OPENGUI_API BrushModifier_ClipRect : public A_BrushModifier {
	public:
		virtual ModifierType getType() {
			return CLIPRECT;
		}
		FRect mRect;
		virtual void apply(RenderOperationList& in_out);
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
		void push( const BrushModifier_Mask& modifier );
		//! push a copy of the given modifier onto the stack
		void push( const BrushModifier_ClipRect& modifier );
		//! push a copy of the given modifier onto the stack
		void push( A_BrushModifier* modifier );

		//! pop the top modifier off the stack
		void pop();
		//! return the stack size
		size_t size() const;

		void applyStack(RenderOperationList& in_out);
	private:
		typedef std::list<A_BrushModifier*> BrushModifierPtrStack;
		BrushModifierPtrStack mStack;
	};


} // namespace OpenGUI{

#endif // BD2BBBC1_8162_4B02_A871_4AEAC49BAC26

