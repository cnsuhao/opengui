#ifndef B955248E_7EDD_47CA_B588_BAA9C55E4380
#define B955248E_7EDD_47CA_B588_BAA9C55E4380

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Imagery.h"
#include "OpenGUI_Font.h"
#include "OpenGUI_BrushModifier.h"

namespace OpenGUI {

	//! \todo this needs to change to a referenced pointer!
	typedef Font* FontPtr;

	class Brush; //forward declaration

	//! Provides drawing methods for a few geometric primitives.
	class OPENGUI_API BrushPrimitive {
		friend class Brush;
	private:
		BrushPrimitive() {
			mParentBrush = 0;
		}
		void setBrush( Brush* brush ) {
			mParentBrush = brush;
		}
		Brush* mParentBrush;
	public:
		~BrushPrimitive() {}
		//! Draws a line between the given points at the given thickness.
		/*! \param start_point The beginning of the line
			\param end_point The end of the line
			\param thickness The thickness of the line (line width)
		*/
		void drawLine( const FVector2& start_point, const FVector2& end_point, float thickness );
		//! Draws a line between the given points at the given thickness.
		/*! \param start_point The beginning of the line
			\param end_point The end of the line
			\param thickness The thickness of the line in pixels (line width)
		*/
		void drawLine( const FVector2& start_point, const FVector2& end_point, int thickness = 1 );
		//! Draws a filled rect using the given \c rect for position as size
		void drawRect( const FRect& rect );
		//! Draws a rect outline using the given \c rect for position as size, and \c thickness for line width
		void drawOutlineRect( const FRect& rect, float thickness );
		//! Draws a rect outline using the given \c rect for position as size, and \c thickness for line width
		void drawOutlineRect( const FRect& rect, int thickness = 1 );
	};

	//! Provides methods for drawing Imagery covered rects
	class OPENGUI_API BrushImagery {
		friend class Brush;
	private:
		BrushImagery() {
			mParentBrush = 0;
		}
		void setBrush( Brush* brush ) {
			mParentBrush = brush;
		}
		Brush* mParentBrush;
	public:
		~BrushImagery() {}

		//! Draws the given imagery using the given rect
		void drawImage( ImageryPtr imageryPtr, const FRect& rect );
		//! Draws the given imagery at the given position and size
		void drawImage( ImageryPtr imageryPtr, const FVector2& position, const FVector2& size );
		//! Draws the given imagery at the given position at it's native pixel size
		void drawImageUnscaled( ImageryPtr imageryPtr, const FVector2& position );
		//! Draws the given imagery filling the given rect using the given number of tiles
		void drawImageTiled( ImageryPtr imageryPtr, const FRect& rect, float x_tiles, float y_tiles );
		//! Draws the given imagery at the given position at it's native pixel size, tiling or clipping it as necessary to fill the area
		void drawImageUnscaledAndTiled( ImageryPtr imageryPtr, const FRect& rect );
	};

	//! Provides methods for rendering text
	class BrushText {
		friend class Brush;
	private:
		BrushText() {
			mParentBrush = 0;
		}
		void setBrush( Brush* brush ) {
			mParentBrush = brush;
		}
		Brush* mParentBrush;
	public:
		~BrushText() {}
		//! draws the given string of characters at the given position, using the given font at the give size, and optionally adjusting the glyph spacing
		void drawText( const std::string& text, const FVector2& position, FontPtr font, float size, float spacing_adjust = 0.0f );
		//! draws the given string within the given rect, using the given font and size, while applying the given text alignments and performing any necessary word wrapping
		void drawTextArea( const std::string& text, const FRect& area, FontPtr font, float size, TextAlignment horizAlign = TextAlignment::ALIGN_LEFT, TextAlignment vertAlign = TextAlignment::ALIGN_TOP );
	};

	//! The base of all widget rendering operations
	/*! The Brush object is provided during widget onDraw events, and is used
		by the widget to draw itself. Functions that should use the Brush object
		will be provided one as a function parameter. Users should have no
		use for manually creating a Brush.


		\par Modifier Stack:
		Brushes implement stack modifiers that are applied to all output they generate.
		The available modifiers are color, clipping rects, output mask, position offsets,
		and rotations about the origin. These modifiers are \b not retroactive.
		For instance, changing the color modifier will not alter the color of operations
		you have already performed, it will only affect new operations.

		\par
		Each brush is created with a completely empty modifier stack.

		\par
		The stack is always unwound from bottom to top. (The last modifier you
		pushed is evaluated last.) This is important because certain modifiers are additive,
		while others are replacing. For instance, the color modifier is replacing.
		When the stack is unwound and a color modifier is found, it replaces the
		previously used color. However, once that new color modifier is popped, the
		previous color will once again be in effect. Conversely, the position modifier is
		additive. So multiple pushed position modifiers will result in an overall origin
		translation that equals their sum.

		\par
		Another important concept to understand is that stack operations are
		non-commutative. In other words, they affect each other in order dependent ways.
		What this means is that if you pushPosition and then pushRotation, the rotation
		will occur at the \b new origin, not the original origin. The same applies for
		clipping rects and masks. You can perform a rotation to an arbitrary angle, and then
		apply a clipping rect or mask, followed by the inverse of the previously used angle,
		and you will have created a non-axis aligned clipping rect or mask. Very powerful indeed.

		\par
		As much fun as these modifiers are, they come with a price tag. The more stack operations
		you add, the more operations must be applied to your output. We do our best to optimize
		the process, but nothing is perfect. Basically, if you're responsible, you'll never run
		into performance issues.

		\par Position Modifier:
		 - Type: Additive
		 - Function: pushPosition()

		\par
		Position modifiers are offsets that will be applied (added) to each
		operation you perform. This is effectively like translating the origin to
		the given position.

		\par Rotation Modifier:
		- Type: Additive
		- Function: pushRotation()

		\par
		Rotation modifiers are origin centered rotations that will be applied to each
		operation you perform.


		\par Color Modifier:
		- Type: Replacing
		- Function: pushColor()

		\par
		The last pushed color modifier will be used as the base color for all output.
		If no color has ever been pushed, the default color is Color(1.0, 1.0, 1.0, 1.0)

		\par Clipping Rect Modifier:
		- Type: Additive
		- Function: pushClippingRect()

		\par
		Clipping rects will perform geometric clipping to the operations performed.
		Position and rotation modifiers can be combined with clipping rects to perform
		non-axis aligned clips.


		\par Mask Modifier:
		- Type: Replacing
		- Function: pushMask(), pushMaskUnscaled()

		\par
		Masks are imagery that are used to determine alpha visibility on a texel level.
		You can create alpha masks of any shape and apply them using this modifier.
	*/
	class OPENGUI_API Brush {
		friend class BrushText;
		friend class BrushPrimitive;
		friend class BrushImagery;
	public:
		Brush( /*context*/ );
		~Brush();
		//! access to primitive drawing operations
		BrushPrimitive Primitive;
		//! access to imagery based drawing operations
		BrushImagery Image;
		//! access to text drawing operations
		BrushText Text;

		//! Pushes a position offset onto the stack
		void pushPosition( float x_offset, float y_offset );
		//! Pushes a position offset onto the stack
		void pushPosition( const FVector2& offset );
		//! Pushes a counter clockwise rotation offset onto the stack
		void pushRotation( const Radian& angle );
		//! Pushes a new color onto the stack
		void pushColor( const Color& color );
		//! Pushes a new clipping rect onto the stack
		void pushClippingRect( const FRect& rect );
		//! Pushes an imagery based mask onto the stack
		void pushMask( ImageryPtr mask_imagery, const FRect& mask_rect );
		//! Pushes an imagery based mask onto the stack
		void pushMaskUnscaled( ImageryPtr mask_imagery, const FVector2& mask_position );
		//! Pops the last modifier off the stack
		void pop();
		//! clears the offset stack
		void clearStack();
		//! returns the current size of the stack
		size_t stackSize();

		//! returns the drawing area that this brush
		const FRect& getDrawArea();
		//const IRect& getDrawArea_Pixels();

	private:
		BrushModifierStack mModifierStack;
	};


	
} // namespace OpenGUI{

#endif // B955248E_7EDD_47CA_B588_BAA9C55E4380

