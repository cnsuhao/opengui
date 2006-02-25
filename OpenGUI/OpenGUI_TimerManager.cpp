#include "OpenGUI.h"
#include <time.h>
#include <windows.h>

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
		timeBeginPeriod(1);
		m_timeSinceStart=0;
		TimerManager::_init_timePassedSinceLastCall();
	}
	//############################################################################
	TimerManager::~TimerManager()
	{
		timeEndPeriod(1);
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
		return (unsigned long)((float)(clock()) / ((float)CLOCKS_PER_SEC/1000.0));
	}
	//############################################################################
};//namespace OpenGUI{



