#ifndef F9886B51_FC3E_44a6_B438_7F80FB4A9629
#define F9886B51_FC3E_44a6_B438_7F80FB4A9629
#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
namespace OpenGUI {
	//! The generic resource container.
	/*! This version simply maintains a byte array of dynamic memory.
		If you need something fancier, just subclass this.
	*/
	class OPENGUI_API Resource {
	public:
		//! constructor
		Resource() : mData( 0 ), mSize( 0 ) {}
		//! virtual destructor
		virtual ~Resource() {
			release();
		}
		//! Sets this object's stored data to the given memory.
		/*! \param newData pointer to the data to store
			\param newSize the size of the data given in bytes
			\note The Resource objects takes ownership of the given memory
				so you no longer need to worry about freeing the buffer.
				(Read: Do not free the memory you pass to this function,
					or you \b will cause a crash when this object is
					destroyed. If you don't have the ability to ensure
					this buffer is never deallocated, make a copy of it
					and provide that instead.)
		*/
		virtual void setData( unsigned char* newData, size_t newSize ) {
			release();
			mData = newData;
			mSize = newSize;
		}
		//! Returns a pointer to the held data, or 0 if there is no stored data.
		unsigned char* getData() {
			return mData;
		}
		//! Sets the size of the data buffer. The current contents will be lost.
		virtual void setSize( size_t size ) {
			release();
			if ( size ) {
				mSize = size;
				mData = new unsigned char[ mSize ];
			}
		}
		//! Returns the size of the held data in bytes.
		size_t getSize() {
			return mSize;
		}
		//! frees the data held
		void release() {
			if ( mData ) {
				delete[] mData;
				mSize = 0;
				mData = 0;
			}
		}

	protected:
		unsigned char* mData;
		size_t mSize;
	};

	//! The same as Resource, except it provides access to the data as a C String.
	class OPENGUI_API Resource_CStr : public Resource {
	public:
		//! just as Resource::setData(), but allocates 1 additional byte for holding the '\\0' cstring terminator
		virtual void setData( unsigned char* newData, size_t newSize ) {
			release();
			if ( newData && newSize ) {
				mData = new unsigned char[newSize + 1];
				mData[newSize] = 0;
				memcpy( mData, newData, newSize );
				delete[] newData;
				mSize = newSize;
			}
		}

		//! get the contents of the buffer as a cstring
		char* getString() {
			if ( !mData ) return 0;
			return ( char* )mData;
		}
		//! again, allocates the requested buffer size, destroys existing data. Allocates 1 additional byte for cstring terminator
		virtual void setSize( size_t size ) {
			release();
			if ( size ) {
				mSize = size;
				mData = new unsigned char[ mSize + 1 ];
				mData[ mSize ] = 0;
			}
		}
	};
}
;//namespace OpenGUI{
#endif

