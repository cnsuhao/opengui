#ifndef F9886B51_FC3E_44a6_B438_7F80FB4A9629
#define F9886B51_FC3E_44a6_B438_7F80FB4A9629
#include "OpenGUI_Exports.h"
namespace OpenGUI{
	//! The generic resource container.
	/*! This version simply maintains a byte array of dynamic memory.
		If you need something fancier, just subclass this.
	*/
	class OPENGUI_API Resource
	{
	public:
		Resource() :mData(0),mSize(0) {}
		virtual ~Resource() { release(); }
		void setData(unsigned char* newData) { mData = newData; }
		unsigned char* getData() { return mData; }
		size_t getSize() { return mSize; }
		void setSize(size_t newSize) { mSize = newSize; }
		void release()
		{
			if(mData){
				delete[] mData;
				mSize=0;
				mData=0;
			}
		}
	protected:
		unsigned char* mData;
		size_t mSize;
	};
};//namespace OpenGUI{
#endif

