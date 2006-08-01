

#include "OpenGUI_TimerManager.h"
#include "OpenGUI_System.h"


namespace OpenGUI{
	template<> TimerManager* Singleton<TimerManager>::mptr_Singleton = 0;
	TimerManager& TimerManager::getSingleton(void)
	{
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	TimerManager* TimerManager::getSingletonPtr(void)
	{
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	//############################################################################
	TimerManager::TimerManager()
	{
	#if OPENGUI_PLATFORM == OPENGUI_PLATFORM_WIN32
		timeBeginPeriod(1);
	#endif
		m_timeSinceStart=0;
		TimerManager::_init_timePassedSinceLastCall();
	}
	//############################################################################
	TimerManager::~TimerManager()
	{
	#if OPENGUI_PLATFORM == OPENGUI_PLATFORM_WIN32
		timeEndPeriod(1);
	#endif
	}
	//############################################################################
	TimerPtr TimerManager::getTimer()
	{
		Timer* timer = new Timer;
		timer->reset();
		return TimerPtr(timer);
	}
	//############################################################################
	unsigned long TimerManager::getMillisecondsSinceStart()
	{
		return m_timeSinceStart;
	}
	//############################################################################
	void TimerManager::_addTime(unsigned int amount)
	{
		m_timeSinceStart+=amount;
	}
	//############################################################################
	void TimerManager::_DoAutoTickInject()
	{
		System::getSingleton().injectTick(_timePassedSinceLastCall());
	}
	//############################################################################
	//############################################################################
	void TimerManager::_init_timePassedSinceLastCall()
	{
		m_last_timePassedSinceLastCall = _timeCurrent();
	}
	//############################################################################
	unsigned long TimerManager::_timePassedSinceLastCall()
	{
		unsigned long cur = _timeCurrent();
		unsigned long delta = cur - m_last_timePassedSinceLastCall;
		m_last_timePassedSinceLastCall = cur;
		return delta;
	}
	//############################################################################
	unsigned long TimerManager::_timeCurrent()
	{
	#if OPENGUI_PLATFORM == OPENGUI_PLATFORM_WIN32
		/*
		We do this because clock() is not affected by timeBeginPeriod on Win32.
		QueryPerformanceCounter is a little overkill for the amount of precision that
		I consider acceptable. If someone submits a patch that replaces this code
		with QueryPerformanceCounter, I wouldn't complain. Until then, timeGetTime
		gets the results I'm after. -EMS

		See: http://www.geisswerks.com/ryan/FAQS/timing.html
		And: http://support.microsoft.com/default.aspx?scid=KB;EN-US;Q274323&
		*/
		return timeGetTime();
	#else
		return (unsigned long)((float)(clock()) / ((float)CLOCKS_PER_SEC/1000.0));
	#endif
	}
	//############################################################################
};//namespace OpenGUI{


