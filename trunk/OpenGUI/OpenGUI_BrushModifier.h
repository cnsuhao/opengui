#ifndef BD2BBBC1_8162_4B02_A871_4AEAC49BAC26
#define BD2BBBC1_8162_4B02_A871_4AEAC49BAC26

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Imagery.h"


namespace OpenGUI {
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
	};
	//############################################################################
	//! \internal Color modifier stored by modifier stack
	class OPENGUI_API BrushModifier_Color : public A_BrushModifier {
	public:
		virtual ModifierType getType() {
			return COLOR;
		}
		Color mColor;
	};
	//############################################################################
	//! \internal Rotation modifier stored by modifier stack
	class OPENGUI_API BrushModifier_Rotation : public A_BrushModifier {
	public:
		virtual ModifierType getType() {
			return ROTATION;
		}
		Radian mRotationAngle;
	};
	//############################################################################
	//! \internal Position modifier stored by modifier stack
	class OPENGUI_API BrushModifier_Position : public A_BrushModifier {
	public:
		virtual ModifierType getType() {
			return POSITION;
		}
		FVector2 mPosition;
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
	};
	//############################################################################
	//! \internal ClipRect modifier stored by modifier stack
	class OPENGUI_API BrushModifier_ClipRect : public A_BrushModifier {
	public:
		virtual ModifierType getType() {
			return CLIPRECT;
		}
		FRect mRect;
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
	private:
		typedef std::list<A_BrushModifier*> BrushModifierPtrStack;
		BrushModifierPtrStack mStack;
	};


} // namespace OpenGUI{

#endif // BD2BBBC1_8162_4B02_A871_4AEAC49BAC26

