// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Viewport_h__
#define Viewport_h__

using namespace System;

namespace OpenGUI_Net {

	public ref class Viewport abstract {
	public:
		virtual OpenGUI::Viewport* getNativeViewport() = 0;
	};

} // namespace OpenGUI_Net {

#endif // Viewport_h__
