#ifndef F85EFDFC_7B31_49c3_AD76_CA4D85284590
#define F85EFDFC_7B31_49c3_AD76_CA4D85284590

#include "OpenGUI_Exports.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_Timer.h"

namespace OpenGUI{

	/*! \brief
	Provides management services for loading, unloading, keeping track of,
	and searching for Imageset and the children Image objects.\n \b [Singleton]
	*/
	class OPENGUI_API TimerManager : public Singleton<TimerManager> {
		friend class System;
	public:
		TimerManager();
		~TimerManager();

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static TimerManager& getSingleton(void);

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static TimerManager* getSingletonPtr(void);

		//! Returns a RefPtr to a Timer object that is ready for immediate use. The returned Timer is pre-synced to the current time.
		TimerPtr getTimer();

		//! Returns the total time since start in milliseconds.
		/*! \warning This should NOT be directly used to represent total application running time,
			as overflow will cause the timer to loop back to 0 after approx 49.7 days.
		*/
		unsigned long getMillisecondsSinceStart();

	protected:
		void _addTime(unsigned int amount);
		unsigned long m_timeSinceStart;

		//This performs an injection of ticks into the system. Only call this if the app is NOT supplying its own ticks
		void _DoAutoTickInject();

		//Resets _timePassedSinceLastCall
		void _init_timePassedSinceLastCall();
		//Simply returns the time passed in ms since the last call
		unsigned long _timePassedSinceLastCall();
		unsigned long m_last_timePassedSinceLastCall;
		unsigned long _timeCurrent();

		/*
		//Timing Related Members
		//!\todo alter this to use a timer class, or at least fix it to provide better timer resolution on windows boxes
		void _updateTimer();
		unsigned long _getTimer();
		clock_t mLastTimerTick;


		//############################################################################
		void System::_updateTimer()
		{
		mLastTimerTick = clock();
		}
		//############################################################################
		unsigned long System::_getTimer()
		{
		return (unsigned long)((float)(clock()-mLastTimerTick) / ((float)CLOCKS_PER_SEC/1000.0));
		}

		*/
	};

};//namespace OpenGUI{

#endif
