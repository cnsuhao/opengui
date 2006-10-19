#ifndef DC3E54A4_1432_4fa1_A635_D76797D7ED89
#define DC3E54A4_1432_4fa1_A635_D76797D7ED89

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_Exports.h"

#include "OpenGUI_Exports.h"
#include "OpenGUI_LogSystem.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Math.h"
#include "OpenGUI_Types.h"

//#include "OpenGUI_Event.h"

//! All %OpenGUI classes are contained under the "OpenGUI" namespace
namespace OpenGUI {
	//forward declarations

	//class WidgetFactoryManager;
	//class WidgetTemplateManager;

	class TimerManager;
	class LogManager;
	class LogListener;
	class LogListenerToFile;
	class CursorManager;
	class ResourceProvider;
	class FontManager;
	class PluginManager;
	class Renderer;
	class TextureManager;
	class ImageryManager;
	class ScreenManager;

	/*!
		\brief
		The System object is the base of the OpenGUI project.
		It is responsible for distributing events, accepting input, managing the
		cursor, and managing the GUI sheets. \n \b [Singleton]

		This class is implemented using the Singleton system. There can only be one System
		object instantiated at any point in time.
	*/
	class OPENGUI_API System : public Singleton<System> {
	public:
		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static System& getSingleton( void );

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static System* getSingletonPtr( void );

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
		System( Renderer* renderer, ResourceProvider* resourceProvider = NULL, std::string logFile = "OpenGUI.log" );
		/*! As the other constructor except a log listener is passed in place of a log filename.
			\param renderer pointer to a valid Renderer object
			\param resourceProvider pointer to a valid ResourceProvider object, or 0
				to use the built in generic ResourceProvider
			\param logListener A valid pointer to a LogListener, or 0 for no logging.
		*/
		System( Renderer* renderer, ResourceProvider* resourceProvider, LogListener* logListener );

		~System();

		//! loads a plugin by filename
		void loadPlugin( std::string filename );
		//! unloads a plugin by filename
		void unloadPlugin( std::string filename );

		//! Updates all screens that need it via ScreenManager::updateScreens()
		/*! This function also takes care of calling _preUpdate() and _postUpdate().
			If you plan on updating Screens individually, or by calling
			ScreenManager::updateScreens() yourself, you will need to call _preUpdate()
			before you begin updating Screens, and _postUpdate() when you are done
			updating Screens this pass. */
		void updateScreens();

		//! Called before any rendering takes place
		void _preUpdate();
		//! Called after all rendering has taken place
		void _postUpdate();

		//! Returns a pointer to the registered ResourceProvider. Apps really shouldn't need, or use, this.
		/*! \deprecated Ideally, no part of %OpenGUI should need this. */
		ResourceProvider* _getResourceProvider() {
			return mResourceProvider;
		}

		//! Notify the System that the dimensions of the viewport it is drawing to have changed.
		/*! This \b should be automatically called by the Renderer implementation, however if
		for some unknown reason the renderer cannot be relied upon to make the call, the
		application can call this function to inform the System of the dimension change instead.
		*/
		void notifyViewportDimensionsChanged();

		//! Returns the current FPS
		/*! The FPS value returned is an average over the last 5 frames. If less than
			5 frames have been rendered, then the average is based on as many frames
			as available. If no frames have been rendered, the returned value will be 0.0f.
			\note A "frame" is defined as a single call to System::renderGUI(). Since most
			applications will call this function once per scene frame, this is an adequate
			metric.
		*/
		float statRenderFPS();

	protected:

	private:
		// This is the actual constructor, the other 2 both call this one after getting the logs up and running.
		void doConstructor( Renderer* renderer, ResourceProvider* resourceProvider );

		//Generic


		//Statistics
		void _stat_UpdateFPS();


		//Logging Facilities
		LogManager* m_LogManager;
		LogListenerToFile* mDefaultLogListener;

		//Font Manager
		FontManager* mFontManager;

		//Plugin Manager
		PluginManager* m_PluginManager;


		//TimerManager
		TimerManager* mTimerManager;
		bool m_PerformAutoTicks;

		//Resource Provider Related Members
		ResourceProvider* mResourceProvider; //pointer to the resource provider
		bool mUsingGenericResourceProvider; //if we're using the generic resource provider, we are responsible for the delete

		//Renderer Related Members
		Renderer* mRenderer;

		//TextureManager Related Members
		TextureManager* mTextureManager;

		//ImageryManager Related Members
		ImageryManager* mImageryManager; //root pointer to the created ImageryManager singleton.

		//ScreenManager
		ScreenManager* mScreenManager;
	};
};

#endif
