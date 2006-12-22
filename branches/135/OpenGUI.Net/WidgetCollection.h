// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef WidgetCollection_h__
#define WidgetCollection_h__

#include "Object.h"

using namespace System;
using namespace System::Collections::Generic;

namespace OpenGUI_Net {

	ref class Widget;

	public ref class WidgetCollection {
	public:
		WidgetCollection( OpenGUI::WidgetCollection* );

		// Adds given widget pointer to the front of the collection
		void add_front( Widget ^ widget );
		void add_front( Widget ^ widget, bool takeOwnership );
		// Adds given widget pointer to the back of the collection
		void add_back( Widget ^ widget );
		void add_back( Widget ^ widget, bool takeOwnership );
		// Remove the given widget pointer from the collection
		void remove( Widget ^ widget );

		// Move the given widget pointer to the front of the collection
		void moveToFront( Widget ^ widget );
		// Move the given widget to the back of the collection
		void moveToBack( Widget ^ widget );

		// returns a pointer to the requested widget or 0 if not found
		Widget ^ getWidget( String ^ widgetName );
		// returns a reference to the requested widget or throws an exception if not found
		Widget ^ operator[]( String^ widgetName );

		// returns true if the given widget pointer is in the collection
		bool hasWidget( Widget ^ widget );


	private:
		void sanityTest();
		OpenGUI::WidgetCollection* mCollection;
	};
} // namespace OpenGUI_Net {
#endif // WidgetCollection_h__
