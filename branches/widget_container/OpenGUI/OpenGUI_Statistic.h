#ifndef B282CF2A_5526_4dbc_AD6C_AB76DB437B26
#define B282CF2A_5526_4dbc_AD6C_AB76DB437B26

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"

namespace OpenGUI {
	//!\internal Average statistic gathering and reporting class
	class OPENGUI_API AverageStat {
	public:
		AverageStat( size_t maxRecords = 5 );
		~AverageStat();
		void addRecord( float value );
		float getAverage();
		void reset();
	private:
		void _increment();
		const size_t mMaxIndex;
		size_t mIndex;
		size_t mRecCount;
		float* mRecords;
	};
}

#endif // B282CF2A_5526_4dbc_AD6C_AB76DB437B26
