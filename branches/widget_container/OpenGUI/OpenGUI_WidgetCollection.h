#ifndef C6C1B1C7_126F_4e60_BF34_47158D1B0043
#define C6C1B1C7_126F_4e60_BF34_47158D1B0043

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Widget.h"

namespace OpenGUI {
	class I_WidgetContainer;

	//! Ordered collection of Widget objects.
	/*! Maintains an ordered list of Widget pointers. Also provides the option to take
	ownership of heap allocated memory, and delete the given widget pointer on
	destruction.
	*/
	class OPENGUI_API WidgetCollection {
		friend class I_WidgetContainer;
	private:
		struct OPENGUI_API WidgetCollectionItem {
			WidgetCollectionItem()
				: widgetPtr( 0 ), own( false ) {}
			Widget* widgetPtr;
			bool own;
		};

		// These are the actual functions that perform the adds/removes
		// They are an additional level deep so we can reuse them without triggering Widget events
		void _add_front( Widget* widget, bool takeOwnership = false );
		void _add_back( Widget* widget, bool takeOwnership = false );
		void _remove( Widget* widget );

		typedef std::list<WidgetCollectionItem*> WidgetCollectionItemPtrList;
		WidgetCollectionItemPtrList mCollectionObjects;
		WidgetCollectionItem* getWidgetHolder( Widget* widget );
		I_WidgetContainer* mIContainer; //pointer to the I_WidgetContainer that owns this WidgetCollection
	protected:
		//! Protects us from being created by anyone but an I_WidgetContainer
		WidgetCollection() {}
	public:
		~WidgetCollection();
		//! Adds given widget pointer to the front of the collection
		void add_front( Widget* widget, bool takeOwnership = false );
		//! Adds given widget pointer to the back of the collection
		void add_back( Widget* widget, bool takeOwnership = false );
		//! Remove the given widget pointer from the collection
		void remove( Widget* widget );

		//! Move the given widget pointer to the front of the collection
		void moveToFront( Widget* widget );
		//! Move the given widget to the back of the collection
		void moveToBack( Widget* widget );

		//! returns a pointer to the requested widget or 0 if not found
		Widget* getWidget( const std::string& widgetName ) const;
		//! returns a reference to the requested widget or throws an exception if not found
		Widget& operator[]( const std::string& widgetName );

		//! returns true if the given widget pointer is in the collection
		bool hasWidget( Widget* widget );

		//! Template class providing iterator encapsulation
		template <typename IterType>
		class collection_iterator {
			friend class WidgetCollection;
		public:
			collection_iterator() {}
			collection_iterator( const collection_iterator& copy ) {
				mIter = copy.mIter;
			}
			//! Equality comparison. Iterators are equal when they point to the same object
			bool operator==( const collection_iterator& right ) {
				return mIter == right.mIter;
			}
			//! Not Equal comparison
			bool operator!=( const collection_iterator& right ) {
				return mIter != right.mIter;
			}
			//! Assign the iterator value from another iterator
			collection_iterator& operator=( const collection_iterator& right ) {
				mIter = right.mIter;
				return *this;
			}
			//! Move to next
			collection_iterator operator++( int ) {
				collection_iterator t( *this );
				++mIter;
				return t;
			}
			//! Move to previous
			collection_iterator operator--( int ) {
				collection_iterator t( *this );
				--mIter;
				return t;
			}
			//! Move to next
			collection_iterator& operator++() {
				++mIter;
				return *this;
			}
			//! Move to previous
			collection_iterator& operator--() {
				--mIter;
				return *this;
			}
			//! Returns the widget at iterator by reference
			Widget& operator*() {
				return *(( *mIter )->widgetPtr );
			}
			//! Returns a pointer to the widget at iterator
			Widget* operator->() {
				return (( *mIter )->widgetPtr );
			}
			//! Returns a pointer to the widget at iterator
			Widget* get() {
				return (( *mIter )->widgetPtr );
			}

		private:
			IterType mIter;
		};

		//! WidgetCollection iterator
		typedef collection_iterator<WidgetCollectionItemPtrList::iterator> iterator;

		//! WidgetCollection reverse_iterator
		typedef collection_iterator<WidgetCollectionItemPtrList::reverse_iterator> reverse_iterator;

		iterator begin(); //!< returns an iterator for the collection starting at the beginning
		iterator end(); //!< returns an iterator for the collection starting off the end
		reverse_iterator rbegin(); //!< returns an iterator for the collection starting at the end
		reverse_iterator rend(); //!< returns an iterator for the collection starting off the beginning
	};

} // namespace OpenGUI {
#endif
