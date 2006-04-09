#ifndef F9886B51_FC3E_44a6_B438_7F80FB4A9629
#define F9886B51_FC3E_44a6_B438_7F80FB4A9629
#include "OpenGUI_PreRequisites.h"
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
		virtual void setData(unsigned char* newData, size_t newSize)
			{
				release();
				mData = newData;
				mSize = newSize;
			}
		unsigned char* getData() { return mData; }
		size_t getSize() { return mSize; }
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

	//! The same as Resource, except it provides access to the data as a C String.
	class OPENGUI_API Resource_CStr : public Resource
	{
	public:
		virtual void setData(unsigned char* newData, size_t newSize)
			{
				release();
				if(newData && newSize)
				{
					mData = new unsigned char[newSize + 1];
					mData[newSize] = 0;
					memcpy(mData, newData, newSize);
					delete[] newData;
					mSize = newSize;
				}
			}

		char* getString()
			{
				if(!mData) return 0;
				return (char*)mData;
			}
	};
};//namespace OpenGUI{
#endif

