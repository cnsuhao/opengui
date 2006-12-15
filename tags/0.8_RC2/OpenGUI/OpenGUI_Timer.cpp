// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details



#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_RefPtr.h"
#include "OpenGUI_TimerManager.h"
#include "OpenGUI_Timer.h"

namespace OpenGUI {

	//###############################################################
	void Timer::reset() {
		m_TimePoint = TimerManager::getSingleton().getMillisecondsSinceStart();
	}
	//###############################################################
	unsigned int Timer::getMilliseconds() {
		return TimerManager::getSingleton().getMillisecondsSinceStart() - m_TimePoint;
	}
	//###############################################################
	float Timer::getSeconds() {
		return (( float )getMilliseconds() ) / 1000.0f;
	}
};

