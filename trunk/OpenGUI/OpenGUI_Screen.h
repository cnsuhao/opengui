#ifndef C98B3B2E_E8CB_4091_BFE6_F66803F67963
#define C98B3B2E_E8CB_4091_BFE6_F66803F67963

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Widget.h"
#include "OpenGUI_I_WidgetContainer.h"
#include "OpenGUI_RenderTexture.h"
#include "OpenGUI_Cursor.h"
#include "OpenGUI_Statistic.h"
#include "OpenGUI_Timer.h"

namespace OpenGUI {
	class ScreenManager;

	//! Every GUI is built into a screen.
	/*! Screens are the base of every GUI display, and it's often best to think
		of them as a sort of virtual monitor. They contain widgets and windows,
		they accept input on an individual basis, and they can draw their output
		either to the main viewport (the default) or to a RenderTexture via
		bindRenderTexture().

		Each Screen has it's own cursor, which can be shown or hidden and enabled
		or disabled individually from all other screens. While the cursor is disabled
		it is not rendered, all cursor based input injections are skipped (no state
		updates, no input consumption), and the cursor is considered non-existent
		so it will not interact with the GUI in any way.
	*/
	class OPENGUI_API Screen : public I_WidgetContainer {
		friend class ScreenManager; //Allow ScreenManager to create and destroy us
	public:
//!\name Cursor Functions (Input Injection & Utility)
//@{
		//! Injects cursor movement by providing the relative movement from the last position
		bool injectCursorMovement( float x_rel, float y_rel );
		//! Injects cursor movement by providing the absolute cursor position on the screen
		bool injectCursorPosition( float x_pos, float y_pos );
		//! Injects cursor movement by providing the absolute cursor position as a percentage of the screen
		bool injectCursorPosition_Percent( float x_perc, float y_perc );
		//! Injects cursor press at the last known cursor position
		bool injectCursorPress();
		//! Injects cursor release at the last known cursor position
		bool injectCursorRelease();
		//! Injects cursor press/release at the last known cursor position using built in state logic
		bool injectCursorPress_State( bool pressed );

		//! sets the default Cursor for this Screen.
		void setCursor( CursorPtr cursor );

		//! Enables the cursor if it is currently disabled
		void enableCursor();
		//! Disables the cursor if it is currently enabled
		void disableCursor();
		//! Returns \c true if the cursor is enabled, \c false otherwise
		bool cursorEnabled();

		//! Shows the cursor if it is currently hidden
		void showCursor();
		//! Hides the cursor if it is currently shown
		void hideCursor();
		//! Returns \c true if the cursor is shown, \c false if it is hidden.
		bool cursorVisible();
		//! Returns a pointer to the current Widget that has cursor focus, or 0 if none
		Widget* getCursorFocusedWidget();

		//! \internal Sets cursor focus to the given Widget. Called by the widget via Widget::grabCursorFocus() or Widget::releaseCursorFocus()
		void _setCursorFocus( Widget* widget );
//@} Cursor Functions

//!\name Keyboard Input Injection
//@{
		//! Injects the given \c character as text input from the user
		bool injectCharacter( char character );

		//\todo bool injectKeyDown(); OG_NYI;
		//\todo bool injectKeyUp(); OG_NYI;

		//! Returns a pointer to the current Widget that has key focus, or 0 if none
		Widget* getKeyFocusedWidget();

		//! \internal Sets key focus to the given Widget. Called by the widget via Widget::grabKeyFocus() or Widget::releaseKeyFocus()
		void _setKeyFocus( Widget* widget );
//@} Text Input
//!\name Time Functions
//@{
		//! Returns \c true if this Screen gets its timing from System
		bool isAutoTiming()const {
			return mAutoTiming;
		}
		//! Sets if this Screen should receive its timing from System
		/*! All new Screens are auto timing by default, and must be individually set not to be if that is
		not desired. All time injections from System occur directly before Screen::update() would be called. */
		void setAutoTiming( bool doAutoTime = true ) {
			mAutoTiming = doAutoTime;
		}
		//! Injects time into this Screen, in milliseconds ( 1/1000th of a second )
		void injectTime( unsigned int milliseconds );
		//! Injects time into this Screen as a float value of a whole second
		void injectTime( float seconds );
//@}

		//! Returns a pointer to the topmost Widget at the given location, or 0 (NULL) if no match found
		Widget* getWidgetAt( const FVector2& position, bool recursive = false );
		//! Returns a list of all widgets at the given location, sorted by depth from top to bottom
		void getWidgetsAt( const FVector2& position, WidgetPtrList& outList, bool recursive = false );

		//! Returns a pointer to the widget at the given path, 0 if no widget is found
		Widget* getPath( const std::string& path ) const;
		//! \internal follows the given \c pathList, returning the ending location. The \c pathList is modified along the way
		Widget* _getPath( StringList& pathList ) const;


		//! returns the name of this Screen
		const std::string& getName() const;
		//! returns the size/resolution of this Screen
		const FVector2& getSize() const;
		//! changes the size/resolution of this Screen
		void setSize( const FVector2& newSize );

		//! returns the PPU (pixels per unit) of this Screen
		/*! PPU is different from DPI. PPU is the number of pixels per Screen size unit,
		and is calculated from the Screen size divided by the pixel size of the Screen's
		render target.
		\n Basically: PPU_Axis = ScreenSize_Axis / TargetSize_Axis
		\n (where Axis is uniformly replaced with the X and Y axis) */
		const FVector2& getPPU() const {
			if ( _ValidPPUcache() ) {
				return mPPUcache;
			}
			_UpdatePPU();
			return mPPUcache;
		}

		//! Returns the UPI (units per inch) of this Screen. \see setUPI()
		const FVector2& getUPI() const {
			return mUPI;
		}
		//! Changes the UPI (units per inch) of this Screen.
		/*! UPI is used to determine font scaling. The default of 96x96 is a copy
		of the standard used under common operating systems. What this does is cause your
		Screen to behave much like your desktop display when doing common tasks like word
		processing, etc. This means that unless you change the UPI of your Screen, you should
		really use a Screen resolution that is common, such as 800x600 or similar. Smaller
		Screen resolutions makes fonts look bigger and larger Screen resolutions make them look
		smaller, just like your computer already does.

		This system (combined with getPPU) allows us to render Screens with consistent font sizes
		and consistent Widget sizes (basically uniformly scaling everything), while still preserving
		pixel alignment where requested. */
		void setUPI( const FVector2& newUPI );

		//! renders this Screen to it's current render target
		void update();
		//! returns true if this screen is automatically updated
		bool isAutoUpdating() const {
			return mAutoUpdating;
		}
		//! sets if this screen is automatically updated
		/*! All new Screens are auto updating by default, and must be individually set not to be if that is not desired. */
		void setAutoUpdating( bool autoUpdate = true ) {
			mAutoUpdating = autoUpdate;
		}

		//! binds the given RenderTexture as the new render target for this Screen
		void bindRenderTexture( RenderTexturePtr renderTexture );
		//! unbinds the current RenderTexture from this Screen, resetting the render target to the main window
		void unbindRenderTexture();
		//! returns true if this screen is bound to a RenderTexture
		bool isBound() const;

		//! Invalidates all contained Widgets, causing a complete redraw on next update()
		void invalidateAll();

		//! Returns the time spent performing Screen::update(), averaged over the past 5 frames.
		float statsGetUpdateTime();
		//! Resets the UpdateTime statistic
		void statsResetUpdateTime();

	protected:
		// We aren't for creation outside of ScreenManager
		Screen( const std::string& screenName, const FVector2& initialSize );
		// Not for deletion either
		virtual ~Screen();

		//! \internal If this Screen renders to the main viewport, this matters. Otherwise it doesn't.
		void _notifyViewportDimensionsChanged();

		//! \internal private implementation of injectCursorPosition(), post sanity checks
		bool _injectCursorPosition( float x_rel, float y_rel );

	private:
		//! returns the size of the render target of this Screen
		const IVector2& getRenderTargetSize() const;

		bool mAutoUpdating; // updated by System::updateScreens or not
		bool mAutoTiming; // times injected by System:: or not
		std::string mName;
		FVector2 mSize;
		FVector2 mUPI;
		mutable FVector2 mPPUcache; //mutable because overall it is state unrelated
		mutable bool mPPUcache_valid; //mutable because overall it is state unrelated
		const bool _ValidPPUcache() const {
			return mPPUcache_valid;
		}
		void _DirtyPPUcache() {
			mPPUcache_valid = false;
		}
		void _UpdatePPU() const; //updates the PPU cache
		RenderTexturePtr renderTarget;

		//input state variables
		FVector2 mCursorPos; // last known cursor position, used for relative cursor input injection
		bool mCursorPressed; // last known cursor press state

		//cursor variables
		bool m_CursorEnabled; // cursor enabled/disabled
		bool m_CursorVisible; // cursor show/hide
		CursorPtr mDefaultCursor; // the default cursor for this Screen
		CursorPtr mPrevCursor; // the cursor drawn in the previous render

		//Focus variables
		Widget* m_CursorFocus; // pointer to current widget with cursor focus, 0 if none
		Widget* m_KeyFocus; // pointer to current widget with keyboard focus, 0 if none

		// Stats
		TimerPtr mStatUpdateTimer;
		AverageStat mStatUpdate;
		void _updateStats_UpdateTime( float newTime ); // inserts a new update time data point
	};

} //namespace OpenGUI{

#endif // C98B3B2E_E8CB_4091_BFE6_F66803F67963
