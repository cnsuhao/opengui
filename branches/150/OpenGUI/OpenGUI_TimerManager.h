// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#ifndef F85EFDFC_7B31_49c3_AD76_CA4D85284590
#define F85EFDFC_7B31_49c3_AD76_CA4D85284590

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_Timer.h"

namespace OpenGUI {

	/*! \brief
	Provides timing services for %OpenGUI widgets and applications.
	\n \b [Singleton]

	\warning This subsystem will provide its own time injections unless
		System::setAutoTick(false) is called.
	\note It is worth noting that many time dependant statistics within %OpenGUI,
		for example System::statRenderFPS(), utilize this subsystem as their timing
		mechanism. Manually providing inaccurate time deltas via System::injectTick()
		will cause these statistics to generate inaccurate results.
	*/
	class OPENGUI_API TimerManager : public Singleton<TimerManager> {
		friend class System;
	public:
		TimerManager();
		~TimerManager();

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static TimerManager& getSingleton( void );

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static TimerManager* getSingletonPtr( void );

		//! Returns a RefPtr to a Timer object that is ready for immediate use. The returned Timer is pre-synced to the current time.
		TimerPtr getTimer();

		//! Returns the total time since start in milliseconds. ( 1/1000th of a second )
		/*! \warning This should NOT be directly used to represent total application running time,
			as overflow will cause the timer to loop back to 0 after approx 49.7 days.
		*/
		unsigned long getMillisecondsSinceStart();

		//! Adds the given amount of time, in milliseconds
		void addTime( unsigned int amount_milliseconds );

		//! Sets the total time passed since application start, in milliseconds
		void setTime( unsigned long timefromstart_milliseconds );

	protected:
		unsigned long m_timeSinceStart; // the central time variable
		// Auto advances time. Should only be called from System once per frame, and only if the application is not providing its own timing
		void _AutoAdvance();

	private:
		// The following should NEVER be called outside of TimerManager
		void _init_timePassedSinceLastCall();//Resets _timePassedSinceLastCall
		unsigned long _timePassedSinceLastCall(); //Simply returns the time passed in ms since the last call
		unsigned long m_last_timePassedSinceLastCall; // storage for _timePassedSinceLastCall()
		unsigned long _timeCurrent(); // gets the current time from the OS
	};

}
;//namespace OpenGUI{

#endif
