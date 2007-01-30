// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#ifndef E79A4AB7_6B23_4903_AB1E_FA5D21DF1AEA
#define E79A4AB7_6B23_4903_AB1E_FA5D21DF1AEA

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_RefPtr.h"

namespace OpenGUI {

	//! Timers provide a simple method of retrieving time deltas from the TimerManager.
	class OPENGUI_API Timer {
	public:
		//! Re-Syncs this Timer's internal time point marker with the TimerManager's current time.
		void reset();
		//! Returns the number of milliseconds passed since object creation, or the last reset, whichever occurred last.
		/*! (Milliseconds are 1/1000th of a second) */
		unsigned int getMilliseconds();

		//! Returns the time passed since object creation or last reset in seconds, as a float to support fractions of a second.
		float getSeconds();
	private:
		unsigned int m_TimePoint;
	};
	//! Reference counted, auto deleting Timer pointer
	typedef RefPtr<Timer> TimerPtr;
};

#endif


