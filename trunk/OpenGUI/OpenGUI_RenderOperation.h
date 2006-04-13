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
		inline void OPENGUI_API AppendRenderOperationList(RenderOperationList& outList, RenderOperationList& inList);

		//! Prepends the contents of inList to the beginning of outList. The contents of inList are preserved.
		inline void OPENGUI_API PrependRenderOperationList(RenderOperationList& outList, RenderOperationList& inList);

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

		
	};//namespace Render{
};
#endif

