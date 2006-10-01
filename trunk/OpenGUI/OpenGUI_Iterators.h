#ifndef E2065C4F_6D55_4128_A384_76A97010B375
#define E2065C4F_6D55_4128_A384_76A97010B375

#include "OpenGUI_PreRequisites.h"

namespace OpenGUI {

	//! This is a generic vector iterator encapsulation class.
	template<class T, typename I>
	class VectorIterator {
	private:
		VectorIterator() {};
	public:
		typedef I _Iterator;
		typedef typename T::value_type ValueType;

		VectorIterator( _Iterator begin, _Iterator end ): mCur( begin ), mEnd( end ) {}
		~VectorIterator() {}

		//! Moves to next item
		void moveNext() {
			mCur++;
		}
		//! Moves to previous item
		void movePrev() {
			mCur--;
		}

		//! Returns current item and moves to next item
		ValueType getNext() {
			return *mCur++;
		}

		//! Returns the value of the current item
		ValueType getValue() {
			return *mCur;
		}

		//! Returns true if there are more items
		bool hasMore() {
			return !isEnd();
		}
		//! Returns true if there are no more items
		bool isEnd() {
			return mCur == mEnd;
		}
	private:
		_Iterator mCur;
		_Iterator mEnd;
	};

	//! This is a generic map iterator encapsulation class.
	template<class T, typename I>
	class MapIterator {
	private:
		MapIterator() {};
	public:
		typedef I _Iterator;
		typedef typename T::key_type KeyType;
		typedef typename T::mapped_type MappedType;

		MapIterator( _Iterator begin, _Iterator end ): mCur( begin ), mEnd( end ) {}
		~MapIterator() {}

		//! Moves to next item
		void moveNext() {
			mCur++;
		}
		//! Moves to previous item
		void movePrev() {
			mCur--;
		}

		//! Returns current item and moves to next item
		MappedType getNext() {
			return ( mCur++ )->second;
		}

		//! Returns the value half of the current item
		MappedType getValue() {
			return mCur->second;
		}
		//! Returns the key half of the current item
		KeyType getKey() {
			return mCur->first;
		}

		//! Returns true if there are more items
		bool hasMore() {
			return !isEnd();
		}
		//! Returns true if there are no more items
		bool isEnd() {
			return mCur == mEnd;
		}
	private:
		_Iterator mCur;
		_Iterator mEnd;
	};

	//! This is a generic list iterator encapsulation class.
	template<class T, typename I>
	class ListIterator {
	private:
		ListIterator() {};
	public:
		typedef I _Iterator;
		typedef typename T::value_type ValueType;

		ListIterator( _Iterator begin, _Iterator end ): mCur( begin ), mEnd( end ) {}
		~ListIterator() {}

		//! Moves to next item
		void moveNext() {
			mCur++;
		}
		//! Moves to previous item
		void movePrev() {
			mCur--;
		}

		//! Returns current item and moves to next item
		ValueType getNext() {
			return *mCur++;
		}

		//! Returns the value of the current item
		ValueType getValue() {
			return *mCur;
		}

		//! Returns true if there are more items
		bool hasMore() {
			return !isEnd();
		}
		//! Returns true if there are no more items
		bool isEnd() {
			return mCur == mEnd;
		}
	private:
		_Iterator mCur;
		_Iterator mEnd;
	};

} //namespace OpenGUI{

#endif // E2065C4F_6D55_4128_A384_76A97010B375
