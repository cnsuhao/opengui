#ifndef E65861C2_92D6_4345_8B3B_5B65D114F3C1
#define E65861C2_92D6_4345_8B3B_5B65D114F3C1

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Widget.h"

namespace OpenGUI {

	class I_WidgetContainer; //forward declaration

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

		typedef std::list<WidgetCollectionItem*> WidgetCollectionItemPtrList;
		WidgetCollectionItemPtrList mCollectionObjects;
		WidgetCollectionItem* getWidgetHolder( Widget* widget );
		I_WidgetContainer* mIContainer;
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
		Widget* getWidget( const std::string& widgetName );
		//! returns a reference to the requested widget or throws an exception if not found
		Widget& operator[]( const std::string& widgetName );

		//! returns true if the given widget pointer is in the collection
		bool hasWidget( Widget* widget );

		//! returns a pointer to the containing widget, or 0 if this is a root level container
		Widget* getContainingWidget();

		//! Template class providing iterator encapsulation
		template <typename IterType>
		class collection_iterator {
			friend class WidgetCollection;
		public:
			collection_iterator() {}
			collection_iterator( const collection_iterator& copy ) {
				mIter = copy.mIter;
			}
			bool operator==( const collection_iterator& right ) {
				return mIter == right.mIter;
			}
			bool operator!=( const collection_iterator& right ) {
				return mIter != right.mIter;
			}
			collection_iterator& operator=( const collection_iterator& right ) {
				mIter = right.mIter;
				return *this;
			}
			collection_iterator& operator++() {
				++mIter;
				return *this;
			}
			collection_iterator& operator--() {
				--mIter;
				return *this;
			}
			Widget& operator*() {
				return &( mIter->widgetPtr );
			}
			Widget* operator->() {
				return ( mIter->widgetPtr );
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

	class OPENGUI_API I_WidgetContainer {
		friend class Widget; //need this for child widget destruction notifications
		friend class WidgetCollection; //need this for add/remove notifications
	public:
		I_WidgetContainer();
		virtual ~I_WidgetContainer() {}
		//! Collection of contained children Widget objects
		WidgetCollection Children;
	protected:

	private:
		//! automatically called by Widget during destruction to notify us so we can remove its entry
		void notifyChildDelete( Widget* widgetToRemove );
		//! automatically called by WidgetCollection before it adds a widget to the collection
		void notifyChildAdding( Widget* widgetPtr );
		//! automatically called by WidgetCollection before it removes a widget from the collection
		void notifyChildRemoving( Widget* widgetPtr );
	};

}

#endif // E65861C2_92D6_4345_8B3B_5B65D114F3C1