// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Viewport_h__
#define Viewport_h__

using namespace System;

namespace OpenGUI_Net {

	ref class Screen; // forward declaration

	public ref class Viewport abstract{
	public:
		virtual void preUpdate(Screen^ updatingScreen)=0;
		virtual void postUpdate(Screen^ updatingScreen)=0;
		virtual void screenAttached(Screen^ attachingScreen)=0;
		virtual void screenDetached(Screen^ detachingScreen)=0;
		//const ScreenSet &  getScreenSet()=0;
	};

} // namespace OpenGUI_Net {

#endif // Viewport_h__
