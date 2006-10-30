#include "OpenGUI_Statistic.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	//############################################################################
	AverageStat::AverageStat( size_t maxRecords )
			: mMaxIndex( maxRecords ), mIndex( 0 ), mRecCount( 0 ) {
		if ( mMaxIndex == 0 )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "maxRecords must be > 0", __FUNCTION__ );
		mRecords = new float[mMaxIndex];
	}
	//############################################################################
	AverageStat::~AverageStat() {
		if ( mRecords )
			delete[] mRecords;
	}
	//############################################################################
	float AverageStat::getAverage() {
		if ( mRecCount == 0 ) return 0.0f;
		float ret = 0.0f;
		for ( size_t i = 0; i < mRecCount; i++ ) {
			ret += mRecords[i];
		}
		ret = ret / mRecCount;
		return ret;
	}
	//############################################################################
	void AverageStat::addRecord( float value ) {
		mRecords[mIndex] = value;
		_increment();
	}
	//############################################################################
	void AverageStat::_increment() {
		mIndex++;
		if ( mIndex >= mMaxIndex )
			mIndex = 0;
		if ( mRecCount < mMaxIndex )
			mRecCount++;
	}
	//############################################################################
	void AverageStat::reset() {
		mRecCount = 0;
		mIndex = 0;
	}
}
