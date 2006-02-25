
#include "OpenGUI.h"

namespace OpenGUI{

	//###############################################################
	void Timer::reset()
	{
		m_TimePoint = TimerManager::getSingleton().getMillisecondsSinceStart();
	}
	//###############################################################
	unsigned int Timer::getMilliseconds()
	{
		return TimerManager::getSingleton().getMillisecondsSinceStart() - m_TimePoint;
	}
	//###############################################################
};

