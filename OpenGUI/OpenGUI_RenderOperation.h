#ifndef BC21A4C5_FCD1_4d8c_9263_4AC39140B970
#define BC21A4C5_FCD1_4d8c_9263_4AC39140B970

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Imagery.h"

namespace OpenGUI{
	class Texture; //forward declaration
	class Imagery; //forward declaration
	class Element; //forward declaration
	
	/*! \brief
		This namespace contains rendering specific objects and functions
		that are used by all widgets to tell the renderer how to draw them.
		If you want to make a widget from scratch (rather than encapsulating
		existing widgets), this is where you look to build the necessary render
		operations.
	*/
	namespace Render{

		//! Used to define the color of a vertex. The default color is White, with alpha=1.0f
		class OPENGUI_API VertexColor{
		public:
			VertexColor(float R=1.0f, float G=1.0f, float B=1.0f, float A=1.0f) : Red(R), Blue(B), Green(G), Alpha(A) {}

			float Red;//!<Red Channel
			float Blue;//!<Blue Channel
			float Green;//!<Green Channel
			float Alpha;//!<Alpha Channel

			//! Quickly generate a preset VertexColor that is Red
			static VertexColor PresetRed(){return VertexColor(1.0f,0.0f,0.0f,1.0f);}
			//! Quickly generate a preset VertexColor that is Green
			static VertexColor PresetGreen(){return VertexColor(0.0f,1.0f,0.0f,1.0f);}
			//! Quickly generate a preset VertexColor that is Blue
			static VertexColor PresetBlue(){return VertexColor(0.0f,0.0f,1.0f,1.0f);}
			//! Quickly generate a preset VertexColor that is White
			static VertexColor PresetWhite(){return VertexColor(1.0f,1.0f,1.0f,1.0f);}
			//! Quickly generate a preset VertexColor that is Black
			static VertexColor PresetBlack(){return VertexColor(0.0f,0.0f,0.0f,1.0f);}
		};

		//! It's a vertex. RenderOperations consist of 3 of these to make a polygon.
		class OPENGUI_API Vertex{
		public:
			FVector2 position; //!< The X,Y position of this vertex
			VertexColor color; //!< The color of this vertex
			FVector2 textureUV; //!< The UV coordinate for the texture of this vertex (if any)
			FVector2 maskUV; //!< The UV coordinate for the mask texture of this vertex (if any)
		};

		/*! \brief
			These are the representations of render operations that are sent to the renderer for
			drawing.

			\note
			Though the Renderer implementation really should \b not care, it is highly
			advised that you use counter clockwise vertex windings. All Primitive
			classes use CCW windings, so you can be assured that any Renderer implementation
			that is performing winding culling will appear to absolutely not work correctly
			if it is culling CCW wound polygons.

			\note
			At the current implementation, the system can only guaranty that renderers will
			receive render operations in a back to front order per widget. 
		*/
		class OPENGUI_API RenderOperation{
		public:
			RenderOperation() : texture(0), mask(0) {}
			Vertex vertices[3]; //!< Simple array of 3 Vertex objects to define a single polygon
			Texture* texture; //!< Pointer to the color texture, or 0 for none
			Texture* mask; //!< Pointer to the mask texture, or 0 for none
		};
		typedef std::list<RenderOperation> RenderOperationList;
		//! Appends the contents of inList to the end of outList. The contents of inList are preserved.
		void OPENGUI_API AppendRenderOperationList(RenderOperationList& outList, RenderOperationList& inList);

		//! Prepends the contents of inList to the beginning of outList. The contents of inList are preserved.
		void OPENGUI_API PrependRenderOperationList(RenderOperationList& outList, RenderOperationList& inList);

		/*! \brief
			This is a base class for the built in Primitive system. Using
			primitives allows widgets to easily create the most common types
			of render operations that are used in GUIs.

			A widget does not have to use primitives to generate render
			operations, it is merely a set of helper classes that make
			generating render operations much easier.
		*/
		class OPENGUI_API Primitive{
		public:
			Primitive() {}
			virtual ~Primitive() {}
			//! Return a RenderOperationList that correctly expresses this Primitive
			virtual RenderOperationList getRenderOperationList()=0;
		};

		/*! \brief
			A box primitive. Provides simple render operation generation
			for creating boxes of any dimension, location, and imagery.
			It provides automatic Texture* linking and UV generation for
			both textures and masks based on imagery.
		*/
		class OPENGUI_API PrimitiveBox : public Primitive{
		public:
			PrimitiveBox() : mRect(FRect(0.0f,0.0f,1.0f,1.0f)), mTextureImagery(0), mMaskImagery(0) {}
			virtual ~PrimitiveBox() {}
			//! Returns the RenderOperationList that is the result of this primitive
			RenderOperationList getRenderOperationList();
			//! Get the current position and size of the Box
			FRect getRect(){return mRect;}
			//! Sets the size and position of the Box to the given FRect
			void setRect(FRect rect){mRect=rect;}
			//! Sets the imagery that should be used for texturing the Box. 0 uses none (default)
			void setTextureImagery(ImageryPtr imagery) {mTextureImagery = imagery;}
			//! Sets the mask imagery that should be used for texturing the Box. 0 uses none (default)
			void setMaskImagery(ImageryPtr imagery) {mMaskImagery = imagery;}
		private:
			FRect mRect; //size and position of this Box
			ImageryPtr mTextureImagery;
			ImageryPtr mMaskImagery;
		};

		//! Provides a simple interface for generating text strings
		class OPENGUI_API PrimitiveText : public Primitive{
		public:
			PrimitiveText();
			virtual ~PrimitiveText();
			RenderOperationList getRenderOperationList();
			void setContext(Element* contextElement);
			void setText(std::string textString);
			void setFont(std::string fontName, unsigned int fontSize_points);
			void setPosition(const FVector2& baselinePosition);

			//! Returns the width of the current text string 
			/*! \note This function requires access to each of glyphs' metrics,
				and will hit the font cache to get them. This means that the glyphs
				will be loaded into the font cache. There is currently no way around this.
			*/
			float getTextWidth();
			//! Returns the height of the current text string
			float getTextHeight();
			//! Returns the combined width and height of the text string
			FVector2 getTextSize();

			//! Returns the width of the current text string in pixels
			/*! \note This function requires access to each of glyphs' metrics,
			and will hit the font cache to get them. This means that the glyphs
			will be loaded into the font cache. There is currently no way around this.
			*/
			int getTextPixelWidth();
			//! Returns the height of the current text string in pixels
			int getTextPixelHeight();
			//! Returns the combined width and height of the text string in pixels
			IVector2 getTextPixelSize();

			// renderText( Rect, text, font, color, align, scroll )

		private:
			std::string mTextContents;
			FVector2 mPosition;
			Element* mContext;

			std::string mFontName;
			unsigned int mFontSize;

			FVector2 _getPixelScale();
		};

		/*! \brief
			This primitive performs an axis aligned scissor rect operation
			on provided render operations.
			
			For compatibility reasons, %OpenGUI cannot perform scissor rects
			in hardware, so as a replacement it provides this object to perform
			geometrical	scissor rect functionality.

			The clipping performed will automatically adjust all render operation
			data to properly preserve the intended look of the original render
			operation. This includes vertex color, texture UV, and mask UV.

			Do not expect every render operation you put into this object
			to make it back out. Render operations that are completely outside
			of the specified rect are culled.
			
			Also, do not expect to get less render operations out than you put
			in. A side effect of geometric clipping is the potential for 3 sided
			polygons to become 4 sided polygons. Since RenderOperation objects
			only support 3 sided polygons, any 4 sided polygons that are produced
			by this object are automatically converted into 2 separate 3 sided
			polygons.

			\note The order in which render operations are received is preserved,
				so this Primitive can be trusted with RenderOperations that have
				a specific draw order.
		*/
		class OPENGUI_API PrimitiveScissorRect : public Primitive{
		public:
			PrimitiveScissorRect() : mRect(FRect(0.0f,0.0f,1.0f,1.0f)) {}
			virtual ~PrimitiveScissorRect() {}
			//! Returns the RenderOperationList that is the result of this primitive
			RenderOperationList getRenderOperationList();
			//! Get the current position and size of the ScissorRect 
			FRect getRect(){return mRect;}
			//! Sets the size and position of the ScissorRect to the given FRect
			void setRect(FRect rect){mRect=rect;}

			//! Adds a single RenderOperation to the input RenderOperationList
			void addRenderOperation(RenderOperation& renderOp);
			//! Adds an entire RenderOperationList to the input RenderOperationList
			void addRenderOperation(RenderOperationList& renderOpList);
			//! Clears the input RenderOperationList
			void clear();
		private:
			FRect mRect; //size and position of this ScissorRect
			RenderOperationList mInputRenderOps;

			void _SliceRenderOp_Vert_SaveLeft(RenderOperation& input, RenderOperationList& output, float cutPosition);
			void _SliceRenderOp_Vert_SaveRight(RenderOperation& input, RenderOperationList& output, float cutPosition);
			void _SliceRenderOp_Horiz_SaveTop(RenderOperation& input, RenderOperationList& output, float cutPosition);
			void _SliceRenderOp_Horiz_SaveBottom(RenderOperation& input, RenderOperationList& output, float cutPosition);
			static void sliceLineSegment(Vertex& vert1, Vertex& vert2, Vertex& resultVert, float cutPosition, bool cutHorizontal);
		};
	};//namespace Render{
};
#endif

