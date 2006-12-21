// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Screen_h__
#define Screen_h__

#include "Object.h"

using namespace System;

namespace OpenGUI_Net {

	ref class Viewport;

	public ref class Screen: OpenGUI_Net::Object {
	public:
		Screen() {}

		// Injects cursor movement by providing the relative movement from the last position
		bool injectCursorMovement( float x_rel, float y_rel );
		// Injects cursor movement by providing the absolute cursor position on the screen
		bool injectCursorPosition( float x_pos, float y_pos );
		// Injects cursor movement by providing the absolute cursor position as a percentage of the screen
		bool injectCursorPosition_Percent( float x_perc, float y_perc );
		// Injects cursor press at the last known cursor position
		bool injectCursorPress();
		// Injects cursor release at the last known cursor position
		bool injectCursorRelease();
		// Injects cursor press/release at the last known cursor position using built in state logic
		bool injectCursorPress_State( bool pressed );

		// gets the current cursor position
		FVector2 getCursorPos();
		// gets the current cursor position as a percentage of the screen
		FVector2 getCursorPos_Percent();

		// sets the default Cursor for this Screen.
//void setCursor( Cursor cursor );

		// Enables the cursor if it is currently disabled
		void enableCursor();
		// Disables the cursor if it is currently enabled
		void disableCursor();
		// Returns \c true if the cursor is enabled, \c false otherwise
		bool cursorEnabled();

		// Shows the cursor if it is currently hidden
		void showCursor();
		// Hides the cursor if it is currently shown
		void hideCursor();
		// Returns \c true if the cursor is shown, \c false if it is hidden.
		bool cursorVisible();
		// Returns a pointer to the current Widget that has cursor focus, or 0 if none
//Widget* getCursorFocusedWidget();
		//###########################################################################
		// Injects the given \c character as text input from the user
		bool injectCharacter( char character );
		// Returns a pointer to the current Widget that has key focus, or 0 if none
//Widget* getKeyFocusedWidget();
		//###########################################################################
		// Returns \c true if this Screen gets its timing from System
		bool isAutoTiming();
		// Sets if this Screen should receive its timing from System
		void setAutoTiming( bool doAutoTime );
		// Injects time into this Screen, in milliseconds ( 1/1000th of a second )
		void injectTime( unsigned int milliseconds );
		// Injects time into this Screen as a float value of a whole second
		void injectTime( float seconds );
		//###########################################################################

		// Returns a pointer to the topmost Widget at the given location, or 0 (NULL) if no match found
//Widget* getWidgetAt( const FVector2& position, bool recursive = false );
		//! Returns a list of all widgets at the given location, sorted by depth from top to bottom
//void getWidgetsAt( const FVector2& position, WidgetPtrList& outList, bool recursive = false );

		// Returns a pointer to the widget at the given path, 0 if no widget is found
//Widget* getPath( const std::string& path ) const;

		// returns the name of this Screen
		String ^ getName();
		// returns the size/resolution of this Screen
		FVector2 getSize();
		// changes the size/resolution of this Screen
		void setSize( FVector2 newSize );

		// returns the PPU (pixels per unit) of this Screen
		FVector2 getPPU();

		// Returns the UPI (units per inch) of this Screen. \see setUPI()
		FVector2 getUPI();
		// Changes the UPI (units per inch) of this Screen.
		void setUPI( FVector2 newUPI );

		// renders this Screen to it's Viewport, if possible
		void update();
		// returns true if this screen is automatically updated
		bool isAutoUpdating();
		// sets if this screen is automatically updated
		void setAutoUpdating( bool autoUpdate );

		// bind this Screen to draw to the given \c viewport
		void setViewport( Viewport ^ viewport );
		// returns the Viewport this Screen renders into
		Viewport ^ getViewport();

		// Invalidates all contained Widgets, causing a complete redraw on next update()
		void invalidateAll();

		// Returns the time spent performing Screen::update(), averaged over the past 5 frames.
		float statsGetUpdateTime();
		// Resets the UpdateTime statistic
		void statsResetUpdateTime();

		// Sets this screen active or disabled according to the given \c active flag
		void setActive( bool active );
		// returns the active status for this Screen
		bool isActive();


		//! The public collection of child widgets
//WidgetCollection Children;

		// inherited from Object, used to provide properties
		//virtual ObjectAccessorList* getAccessors();
		//virtual unsigned int getObjectType() const;

	};

} // namespace OpenGUI_Net {

#endif // Screen_h__
