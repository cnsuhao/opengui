#ifndef E79A4AB7_6B23_4903_AB1E_FA5D21DF1AEA
#define E79A4AB7_6B23_4903_AB1E_FA5D21DF1AEA

namespace OpenGUI{

	//! Timers provide a simple method of retrieving time deltas from the
	class OPENGUI_API Timer{
	public:
		void reset();
		unsigned int getMilliseconds();
	private:
		unsigned int m_TimePoint;
	};
	typedef RefPtr<Timer> TimerPtr;
};

#endif


