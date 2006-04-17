#ifndef DC3E54A4_1432_4fa1_A635_D76797D7ED89
#define DC3E54A4_1432_4fa1_A635_D76797D7ED89

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_MouseButton.h"
#include "OpenGUI_Event.h"
#include "OpenGUI_Message.h"
#include "OpenGUI_Element.h"

//! The base namespace contains the classes that applications will deal with the most.
namespace OpenGUI{
	//forward declarations
	namespace Widgets{ class Widget; }
	class GUISheet;
	class WidgetFactoryManager;
	class WidgetTemplateManager;
	class TimerManager;
	class LogManager;
	class LogListener;
	class LogListenerToFile;
	class CursorManager;
	class ResourceProvider;
	class FontManager;
	class PluginManager;
	class Renderer;
	class ImageryManager;

	/*!
		\brief
		The System object is the base of the OpenGUI project.
		It is responsible for distributing events, accepting input, managing the
		cursor, and managing the GUI sheets. \n \b [Singleton]

		This class is implemented using the Singleton system. There can only be one System
		object instantiated at any point in time.

		\todo implement me
	*/
	class OPENGUI_API System : public Singleton<System>
	{
		friend class Element;
	public:
		
		
		//! The constructor for the System object.
		/*! Firstly, the System object is a singleton, so only one can exist
			in an application at any given point in time.
			
			In order to create an instance of the System object, you must
			provide a pointer to a valid Renderer. The resourceProvider pointer
			is optional, as a generic implementation of that comes pre-built
			with the library.

			\param renderer pointer to a valid Renderer object
			\param resourceProvider pointer to a valid ResourceProvider object, or 0
				to use the built in generic ResourceProvider
			\param logFile name of the log file to write log message to. If "" is used,
				no log file will be created
		*/
		System(Renderer* renderer, ResourceProvider* resourceProvider=NULL, std::string logFile="OpenGUI.log");
		/*! As the other constructor except a log listener is passed in place of a log filename.
			\param renderer pointer to a valid Renderer object
			\param resourceProvider pointer to a valid ResourceProvider object, or 0
				to use the built in generic ResourceProvider
			\param logListener A valid pointer to a LogListener, or 0 for no logging.
		*/
		System(Renderer* renderer, ResourceProvider* resourceProvider, LogListener* logListener);
		//System(Renderer* renderer);

		~System();

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static System& getSingleton(void);

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static System* getSingletonPtr(void);

		//! loads a plugin by filename
		void loadPlugin(std::string filename);
		//! unloads a plugin by filename
		void unloadPlugin(std::string filename);

		/*! \brief Renders the GUI using the current render system.	*/
		void renderGUI();

		//! Searches the entire system for the Element of name, and returns a pointer.
		/*!
			The search is performed across all GUISheets, consisting of all attached Elements
			withing those GUI sheets. If an Element exists but is not currently in the heirarchy,
			either never has been or has been removed, then it will not be found by this search.
			\param name The name of the Element that you are searching for.
			\return The pointer to the found Element on success, 0 otherwise.
		*/
		Element* getElementByName(std::string name);


		

		//! Returns a pointer to the Element that is at the given position.
		/*!
			\param screenLoc The location within the GUISheet that you wish to test
			\param sheet The GUISheet you are testing, or 0 for the current active GUISheet
			\param activeOnly If true, only active Elements are tested, otherwise all are tested
			\return The pointer to the Element at the screenLoc, or 0 if none was found.
			\note It is assumed that screenLoc is in the same coordinate scale as the GUISheet
				that is being tested. If you never changed the GUISheet's coordinate scale
				or offset (via GUISheet::setSize, GUISheet::setPos, or GUISheet::setRect)
				then the default scale will still be in effect.\n
				0.0 x 0.0 == upper left\n
				1.0 x 1.0 == lower right
		*/
		Element* getElementAt(FVector2 screenLoc, GUISheet* sheet=0, bool activeOnly=true);
		Element* getElementAt(const float& xPos, const float& yPos, GUISheet* sheet=0, bool activeOnly=true)
		{
			return System::getElementAt(FVector2(xPos,yPos),sheet,activeOnly);
		}			

		/*! \brief
			Returns the cursor position in an FVector2.

			Cursor position will \b always be in world coordinates.
			(between 0.0x0.0 and 1.0x1.0)
		*/
		FVector2 getCursorPos();

		//! Shows the cursor on the screen if it has been hidden.
		/*! \note The cursor is set visible by default.
		*/
		void showCursor();

		//! Hides the cursor
		/*! \note This does not prevent the cursor from moving due to
			calls to injectMousePosition or injectMouseMovement.
			It merely prevents the cursor from being rendered.
		*/
		void hideCursor();

		//! Sets the name of the default cursor.
		/*! The default cursor is the cursor used whenever the current
			Element does not specify its own cursor.
		
			The given name is used to look up the cursor
			in the CursorManager. If a cursor with the given
			name cannot be found, then no cursor is displayed.

			\note the initial value of this is "DefaultCursor",
				however until a cursor is registered with that
				name, there will be no cursor displayed
		*/
		void setDefaultCursor(std::string defaultCursorName);
		
		//! Injects a key up event to the system. \todo implement
		void injectKeyUp(char keycode);
		//! Injects a key down event to the system. \todo implement
		void injectKeyDown(char keycode);

		//!Injects absolute positioning mouse movement into the GUI.
		/*!
		\param x_pos New absolute pixel position of the cursor on the x axis.
		\param y_pos New absolute pixel position of the cursor on the y axis.
		\note This GUI system expects mouse positions to range from 0.0 to 1.0 on each axis.
				0.0 on the x axis represents the leftmost position
				of the screen, on the y axis it represents the topmost
				position of the screen. Values outside of this range are
				clamped.
		\note This method of input injection will only generate mouse movement
				events if the given cursor position is different from the
				current cursor position.
		*/
		void injectMousePosition(float x_pos, float y_pos);

		//!Injects relative mouse movement into the GUI
		/*!
		\param x_delta The relative mouse movement on the x axis from the last known position.
		\param y_delta The relative mouse movement on the y axis from the last known position.
		\note Since the GUI expects mouse positions to range between 0.0 and 1.0,
				any final mouse positions after applying the given relative
				movement are clamped to fall within that range.
		\note The method of input injection will generate mouse movement
				events every time it is called with either parameter nonzero.
		*/
		void injectMouseMovement(float x_delta, float y_delta);

		//! Injects mouse button down events.
		void injectMouseButtonDown(MouseButton buttonId);

		//! Injects mouse button up events.
		void injectMouseButtonUp(MouseButton buttonId);

		//! Injects a tick event into the active GUISheet, using the given time delta.
		/*! \warning Applications \b must be sure to call System::setAutoTick(false)
			if they plan on providing their own timing. Failure to do so will cause
			both the application, as well as the system, injecting time deltas
			simultaneously, which will make all timing run twice as fast.
		*/
		void injectTick(unsigned int timeDeltaInMilliseconds);
		
		//! Sets the click rate requirement for double clicks
		/*! This setting changes the click rate required for 2 consecutive
			mouse clicks to generate \c ME_MouseDblClick.
			\remark Default is 500
			\param millisecondDelay The time the clicks must be under, in milliseconds.
			\warning This delay is calculated from the injectTick time deltas if the
			application is providing its own timing.
		*/
		void setUserDblClickRate(unsigned int millisecondDelay);

		//! Sets the click & double click accuracy.
		/*! This setting is used to set the distance the cursor can move from the
			first button down event before the \c ME_MouseClick and \c ME_MouseDblClick
			events are not issued. In other words, the cursor is required to stay within
			the given radius size in order for mouse clicks to generate click events.
			This does not affect the button up and button down events, they are guaranteed
			to occur regardless of this setting.
			\remark Default is 0.05f
			\param radius The max distance (world space coordinates) from the point of first button down that the cursor can move without canceling the click effect
		*/
		void setUserClickAccuracy(float radius);

		//! Tells the system if it needs to generate its own Ticks, or if the application would rather supply them.
		/*! The default is TRUE
		*/
		void setAutoTick(bool useAutoTick);

		//! This allows an application to specify a filename to which the input log will be stored.
		/*! Input logging is a functionality supported to provide a level of testbed
			scripting support for applications. When this function is given a filename,
			each subsequent call to the input injection routines will be stored within that file,
			in the exact order in which they were called.
			For consistency purposes, frame dividers will be placed to separate events into
			groups that occurred within the same gui render frame. This will prevent frame rate
			fluctuations from causing inaccurate playbacks of the stored input log.
			\param filename The file to which you would like to store the input log. This file will be
					truncated if it already exists. Passing "" to this function will disable any currently
					active input logging.
		*/
		void enableInputLogging(std::string filename="");

		//! Enables playback of a previously created input log file.
		/*! \param filename The filename of the input log file to play back. Passing "" to this function
				will disable playback of any currently running log file.
			\see enableInputLogging()
		*/
		void enableInputLogPlayback(std::string filename="");


		//! Creates a new GUISheet. If no name is provided, then one will be created for you.
		GUISheet* createGUISheet(std::string name="");

		//! Destroys a GUISheet, as well as all elements that are attached to its heirarchy. If you want to spare an Element from this fate, remove it from the hierarchy before you call this.
		void destroyGUISheet(GUISheet* guiSheetPtr);

		//! Returns a pointer to the GUISheet with the given name, or 0 if none can be found.
		GUISheet* getGUISheetByName(std::string name);

		//! Sets the active GUISheet. The active GUI Sheet is the only sheet that will be drawn, and is the only sheet that will recieve events. You can set the active GUISheet to 'none' by passing 0 as the parameter.
		void setGUISheet(GUISheet* guiSheetPtr);

		//! Create a widget by name
		/*! The widget is created by referencing the WidgetTemplateManager and the WidgetFactoryManager.
			If a \c widgetGroup is provided, the widget is assumed to be held in the WidgetFactoryManager,
			otherwise the widget name is considered to be a template name, and WidgetTemplateManager is
			used to create the widget.
		*/
		Widgets::Widget* createWidget(const std::string& widgetType, const std::string& widgetGroup="");

		//! Returns an FVector2 containing the necessary floats to correct for aspect for either axis.
		/*! To be more clear, if the resolution is 640x480, this will return FVector(480/640, 640/480)
			The purpose being that if you want to ensure proper presentation of a square object,
			you will need to multiply one of the axis sizes by the appropriate axis corrector.
			(Multiply X axis by the returned x, or Y by the return y.)
			Works best if you multiply the axis that you care about the least, as you cannot be
			sure if it will grow or shrink (though fullscreen apps can mostly assume that the X
			will consistently grow, and the Y axis will consistently shrink).

			Do \b not use both multipliers, as the results will likely not be what you are intending.
			Use one of the two, and throw the other one away.
		*/
		FVector2 getAspectCorrection();

		ResourceProvider* _getResourceProvider() { return mResourceProvider; }
		Renderer* _getRenderer() { return mRenderer; }

		//! Notify the System that the dimensions of the viewport it is drawing to have changed.
		/*! This \b should be automatically called by the Renderer implementation via calling
			Renderer::alertViewportDimensionsChanged(), however, if for some unknown reason
			the renderer cannot be relied upon to make the call, the application can call
			this function to inform the System of the dimension change instead.
		*/
		void notifyViewportDimensionsChanged();


		//! Notify the System that the dimensions of the screen have changed.
		/*! This \b should be automatically called by the Renderer implementation via calling
			Renderer::alertScreenDimensionsChanged(), however, if for some unknown reason
			the renderer cannot be relied upon to make the call, the application can call
			this function to inform the System of the dimension change instead.
		*/
		void notifyScreenDimensionsChanged();

		//! Returns the current viewport resolution
		IVector2 getViewportResolution();
		//! Returns the current screen resolution
		IVector2 getScreenResolution();

		//! Returns a pointer to the Element that currently captures the mouse events, or 0 if none is set.
		Element* getCaptureMouse();

		//! Returns a pointer to the Element that currently captures the keyboard events, or 0 if none is set.
		Element* getCaptureKeyboard();

		//! Sets the capture Element for mouse events.
		/*! All mouse events are directed toward this Element until the capture
			is released or changed. Only one Element can capture the mouse at
			any time. Subsequent calls overwrite the current capturer.
			Call using \c capturingElement = 0 to unset a capture.
		*/
		void setCaptureMouse(Element* capturingElement);

		//! Sets the capture Element for keyboard events.
		/*! All keyboard events are directed toward this Element until the capture
			is released or changed. Only one Element can capture the keyboard at
			any time. Subsequent calls overwrite the current capturer.
			Call using \c capturingElement = 0 to unset a capture.
		*/
		void setCaptureKeyboard(Element* capturingElement);

		//! Via this function, Elements can request a special event notification when the cursor leaves their area.
		/*! This function informs the system that an Element would like receive the
			\c ME_MouseLeave event. An Element can only request this notification
			when it would not immediately generate a \c ME_MouseLeave event. If an
			Element requests this notification, when doing so would indeed cause an
			immediate \c ME_MouseLeave event, this function will return \c FALSE, and
			the Element will not be added to the internal notify list.

			\see \link EventME_MouseLeave ME_MouseLeave \endlink
			\param elementToTrack A pointer to the Element that is requesting the notification.
			\returns \c TRUE on success, in which case the Element will receive notification;
				\c FALSE otherwise
			\note During GUISheet changes, all Elements that have registered
				for notification will receive their \c ME_MouseLeave events, and they
				will be issued in the reverse order they were requested. (Children will
				generally receive them before their parents, but this isn't guaranteed
				as it entirely depends on when the parent decided they wanted notification.)
				In this situation, the \c ME_MouseLeave events will come after the current sheet's
				\c ME_GUISheetDeactivate, but before the new sheet's \c ME_GUISheetActivate.
				During this time, all attempts to request mouse tracking are denied.
		*/
		//\see EventME_MouseLeave \todo implement me \note in order for this to succeed, an element cannot meet the event criteria at time of this call (can cause infinite event loop otherwise)
		bool setTrackMouseLeave(Element* elementToTrack);

		//! Generates, and returns a random Element name that is guaranteed to be unique for any 1 execution. \note If you can manage to call this over 4 billion times in 1 second, I am not responsible for your crash.
		std::string generateRandomElementName();

		//! Returns the current size of the render cache in bytes.
		size_t statRenderCacheSize();
	protected:
		//! Injects the given message into the system.
		/*!
			\param message The fully populated Message struct you wish to send
		*/
		void injectEvent(Msg::Message message);

		//!\internal determines the current cursor name, based on cursor visibility, where the mouse is, and the default cursor
		std::string _getCurrentCursorName();
	private:
		// This is the actual constructor, the other 2 both call this one after getting the logs up and running.
		void doConstructor(Renderer* renderer, ResourceProvider* resourceProvider);

	//Generic
		/*	this is a counter that is used to ensure that generateRandomElementName()
			actually does create random names */
		unsigned int mRandomElementNameGeneratorIndex;

	//Logging Facilities
		LogManager* m_LogManager;
		LogListenerToFile* mDefaultLogListener;

	//Font Manager
		FontManager* mFontManager;

	//Plugin Manager
		PluginManager* m_PluginManager;
		
	//GUISheet Related Members
		typedef GUISheet* GUISheetListItem;
		typedef std::list<GUISheetListItem> GUISheetList;
		GUISheet* mActiveGUISheet; //pointer to the active gui sheet, or 0 if none
		GUISheetList mGUISheetList; //a list of all created gui sheets
		void _destroyAllGUISheets(); //a shutdown function used to clean up any existing gui sheets
		

	//WidgetFactoryManager
		WidgetFactoryManager* mWidgetFactoryManager;
		WidgetTemplateManager* mWidgetTemplateManager;

	//TimerManager
		TimerManager* mTimerManager;
		bool m_PerformAutoTicks;

	//Resource Provider Related Members
		ResourceProvider* mResourceProvider; //pointer to the resource provider
		bool mUsingGenericResourceProvider; //if we're using the generic resource provider, we are responsible for the delete
		
	//Renderer Related Members
		Renderer* mRenderer;
		IVector2 mScreenResolution; //resolution of the entire screen (used for auto font scaling)
		IVector2 mWindowResolution; //resolution of the viewport that we are rendering to (used for pixel alignment)

	//ImageryManager Related Members
		ImageryManager* mImageryManager; //root pointer to the created ImageryManager singleton.



	//Mouse Related Members
		CursorManager* mCursorManager;
		FVector2 mCursorPosition;
		bool mCursorVisible;
		std::string mDefaultCursor;
		float mUserClickAccuracy;
		unsigned int mUserDblClickRate;

		//TrackMouse Members
			ElementList mTrackMouseList;
			bool m_tmPurging; //while true, deny all track requests
			void _tmAddElement(Element* trackedElement); //adds the given element to the track list
			void _tmRemoveElement(Element* trackedElement); //removes the given element from the track list
			void _tmPurgeTracks(); //purges the track list, sending ME_MouseLeave to all current entries before clearing
			bool _tmPerformMouseTrackTests(Element* elementUnderMouse=0); //checks each element in the track list and issues a mouse leave event if needed. returns true if an event was sent, will only perform 1 event per run
			bool _tmMeetsTrackCriteria(Element* elementToTest, Element* elementUnderMouse=0); //returns true if the elementToTest meets the mouse tracking criteria

	//Event Generation Related Members
		Element* mCapturerMouse;
		Element* mCapturerKeyboard;
		void _issueMouseMoveEvent(); //issues the mouse move event
		void _issueMouseEnterEvent(Element* elementEntered);
		void _issueMouseLeaveEvent(Element* elementLeft);
		void _issueMouseButtonUpEvent(MouseButton buttonId);
		void _issueMouseButtonDownEvent(MouseButton buttonId);
		void _issueMouseButtonClickEvent(MouseButton buttonId);
		void _issueMouseButtonDblClickEvent(MouseButton buttonId);
		void _issueTickEvent(unsigned long timeDelta); //issues the tick event if time passed > 0
		
		 /* returns an element pointer that is the correct destination of mouse events 
			based on the current capturer and mouse position. (can possibly return 0) */
		Element* _getMouseEventDestination();

		void _issueGUISheetActivate();
		void _issueGUISheetDeactivate();


	//Situation Handlers
		
		Element* m_CurrentMouseElement; //this holds a pointer to the element at the last mouse position. it is used to detect mouse over changes
		void _handleMouseMovement();
		void _handleMouseButtonDown(MouseButton buttonId);
		void _handleMouseButtonUp(MouseButton buttonId);
		void _handleDblClickWashout(); //this resets the press marker if the timer goes over on a button, call me with every tick injection
		unsigned int m_MouseButtonDownTime[3];
		bool m_MouseButtonFirstPress[3];
		FVector2 m_MouseButtonDownPosition[3];
		Element* m_MouseButtonClickElement[3];

	};
};

#endif
