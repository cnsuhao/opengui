// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef RenderOperation_h__
#define RenderOperation_h__

using namespace System;

namespace OpenGUI_Net {
	ref class Texture; // forward declaration

	public value class Vertex {
	public:
		FVector2 position;
		Color color;
		FVector2 textureUV;
		FVector2 maskUV;
	};

	public ref class Triangle {
	public:
		Vertex vertex1;
		Vertex vertex2;
		Vertex vertex3;
	};

	public ref class RenderOperation {
	public:
		array<Triangle^>^ triangleList;
		Texture^ texture;
		Texture^ mask;
	};

} // namespace OpenGUI_Net {

#endif // RenderOperation_h__
