// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#ifndef BC21A4C5_FCD1_4d8c_9263_4AC39140B970
#define BC21A4C5_FCD1_4d8c_9263_4AC39140B970

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Texture.h"

namespace OpenGUI {

	//! It's a vertex. A Triangle consists of 3 of these.
	class OPENGUI_API Vertex {
	public:
		FVector2 position; //!< The X,Y position of this vertex
		Color color; //!< The color of this vertex
		FVector2 textureUV; //!< The UV coordinate for the texture of this vertex (if any)
		FVector2 maskUV; //!< The UV coordinate for the mask texture of this vertex (if any)
	};


	//! Triangle. Wow.
	class OPENGUI_API Triangle {
	public:
		//! Array of three vertices
		Vertex vertex[3];
	};
	//! TriangleList. More Wow.
	typedef std::list<Triangle> TriangleList;



	/*! \brief
	These are the representations of render operations that are sent to the renderer for
	drawing.

	\note
	Though the Renderer implementation really should \b not care, it is highly
	advised that you use counter clockwise vertex windings. All brush methods generate
	CCW windings, so you can be assured that any Renderer implementation that is performing
	winding culling will appear to absolutely not work correctly if it is culling CCW
	wound polygons.

	\note
	At the current implementation, the system can only guarantee that renderers will
	receive render operations in a back to front order per rendering surface.

	*/
	class OPENGUI_API RenderOperation {
	public:
		//! constructor
		RenderOperation() : triangleList ( 0 ), texture( 0 ), mask( 0 ) {}
		~RenderOperation() {
			if ( triangleList != 0 )
				delete triangleList;
		}

		//! pointer to a TriangleList that describes this render operation
		TriangleList* triangleList;

		TexturePtr texture; //!< Pointer to the color texture, or 0 for none
		TexturePtr mask; //!< Pointer to the mask texture, or 0 for none
	};

	typedef std::list<RenderOperation> RenderOperationList;

} // namespace OpenGUI {
#endif


