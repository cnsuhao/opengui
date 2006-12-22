// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Widget_h__
#define Widget_h__

#include "Object.h"
#include "WidgetCollection.h"

using namespace System;
using namespace System::Collections::Generic;

namespace OpenGUI_Net {

	ref class Widget;
	typedef List < Widget ^ > WidgetList;

	public ref class Widget: OpenGUI_Net::Object {
	public:
		Widget() {}

		// returns the name of this Widget
		String ^ getName();
		// sets the name of this Widget
		void setName( String ^ name );
		// returns the enabled/disabled state of this Widget
		bool getEnabled();
		// sets the enabled/disabled state of this Widget
		void setEnabled( bool value );
		// invalidate any caches of this Widget's render output
		void invalidate();
		// invalidate this Widget, as well as any and all potential children
		void flush();
		// returns the collection this widget is held within
		WidgetCollection ^ getContainer();
		// Fills the given \c outList with pointers to all child Widgets that are under the given \c position
		WidgetList ^ getChildrenAt( FVector2 position );
		WidgetList ^ getChildrenAt( FVector2 position, bool recursive );
		// Returns a pointer to the top-most child at the given \c position. Returns 0 if no child is found at the position.
		Widget ^ getChildAt( FVector2 position );
		Widget ^ getChildAt( FVector2 position, bool recursive );
		// Returns a pointer to the widget at the given path, 0 if no widget is found
		Widget ^ getPath( String ^ path );
		// Translates the given point from coordinates local to this Widget into Screen level coordinates
		FVector2 pointToScreen( FVector2 local_point );
		// Translates the given point from Screen level coordinates into coordinates local to this Widget
		FVector2 pointFromScreen( FVector2 screen_point );
		// Returns \c true if this Widget has cursor focus within its Screen
		bool hasCursorFocus();
		// Returns \c true if this Widget has key focus within its Screen
		bool hasKeyFocus();

		//Object Functions
		//virtual ObjectAccessorList* getAccessors();
		//virtual unsigned int getObjectType() const;

		/*
				// Widget was attached to a container
				void eventAttached( WidgetCollection* newContainer, Widget* widget );
				// Widget was removed from a container
				void eventDetached( WidgetCollection* prevContainer, Widget* widget );

				// Draw this object's foreground using the given brush
				void eventDraw( Brush& brush );
				// Widget was invalidated and will need to be redrawn next Screen::update()
				void eventInvalidated();

				// Widget's state has changed to Enabled
				void eventEnabled();
				// Widget's state has changed to Disabled
				void eventDisabled();

				// Called for cursor movement, giving the X,Y position of the cursor
				bool eventCursor_Move( float xPos, float yPos );
				// Called when the cursor button is pressed
				bool eventCursor_Press( float xPos, float yPos );
				// Called when the cursor button is released
				bool eventCursor_Release( float xPos, float yPos );
				// Called when the cursor is disabled
				void eventCursor_Disabled();
				// Called when the cursor is enabled.
				void eventCursor_Enabled( float xPos, float yPos );
				// Called then this widget receives cursor focus
				void eventCursor_Focused( Widget* cur, Widget* prev );
				// Called then this widget loses cursor focus
				void eventCursor_FocusLost( Widget* cur, Widget* prev );

				// Called when the given \c character is released
				bool eventKey_Up( char character );
				// Called when the given \c character is pressed down
				bool eventKey_Down( char character );
				// Called when the given \c character is entered
				bool eventKey_Pressed( char character );
				// Called then this widget receives key focus
				void eventKey_Focused( Widget* cur, Widget* prev );
				// Called then this widget loses key focus
				void eventKey_FocusLost( Widget* cur, Widget* prev );

				// Called when the passage of time has been measured
				void eventTick( float seconds );
		*/
	};
} // namespace OpenGUI_Net {

#endif // Widget_h__
