// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#ifndef E65861C2_92D6_4345_8B3B_5B65D114F3C1
#define E65861C2_92D6_4345_8B3B_5B65D114F3C1

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"

namespace OpenGUI {
	class Widget; // forward declaration
	class WidgetCollection; // forward declaration

	//! Interface for objects that contain collections of children Widget objects
	/*!
	*/
	class OPENGUI_API WidgetCollectionListener {
	public:
		WidgetCollectionListener() {}
		virtual ~WidgetCollectionListener() {}

		//! Container had a child attached
		virtual void eventChildAttached( WidgetCollection* container, Widget* newChild ) = 0;
		//! Container had a child detached
		virtual void eventChildDetached( WidgetCollection* container, Widget* prevChild ) = 0;
	};

}

#endif // E65861C2_92D6_4345_8B3B_5B65D114F3C1