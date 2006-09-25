#ifndef E65861C2_92D6_4345_8B3B_5B65D114F3C1
#define E65861C2_92D6_4345_8B3B_5B65D114F3C1

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Widget.h"

namespace OpenGUI{




	//! \internal Contains various classes and containers that have no reuse value for the end user
	namespace hidden{
		struct OPENGUI_API WidgetCollectionItem{
			WidgetCollectionItem()
				:widgetPtr(0), own(false){}
			Widget* widgetPtr;
			bool own;
		};
	}

	//! Ordered collection of Widget objects.
	/*! Maintains an ordered list of Widget pointers. Also provides the option to take
		ownership of heap allocated memory, and delete the given widget pointer on
		destruction.
	*/
	class OPENGUI_API WidgetCollection{
	private:
		typedef std::list<hidden::WidgetCollectionItem*> WidgetCollectionItemPtrList;
		WidgetCollectionItemPtrList mCollectionObjects;

		hidden::WidgetCollectionItem* getWidgetHolder(Widget* widget);
	public:
		WidgetCollection(){}
		~WidgetCollection();
		//! Adds given widget pointer to the front of the collection
		void add_front(Widget* widget, bool takeOwnership = true);
		//! Adds given widget pointer to the back of the collection
		void add_back(Widget* widget, bool takeOwnership = true);
		//! Remove the given widget pointer from the collection
		void remove(Widget* widget);

		//! Move the given widget pointer to the front of the collection
		void moveToFront(Widget* widget);
		//! Move the given widget to the back of the collection
		void moveToBack(Widget* widget);

		//! returns a pointer to the requested widget or 0 if not found
		Widget* getWidget(const std::string& widgetName);
		//! returns a reference to the requested widget or throws an exception if not found
		Widget& operator[](const std::string& widgetName);

		//! returns true if the given widget pointer is in the collection
		bool hasWidget(Widget* widget);


		//! WidgetCollection iterator
		class OPENGUI_API iterator{
			friend class WidgetCollection;
		public:
			iterator(); //!< iterator constructor
			iterator(const iterator& copy);  //!< iterator copy constructor
			bool operator==(const iterator& right); //!< iterator equality test
			bool operator!=(const iterator& right); //!< iterator non equality test
			iterator& operator=(const iterator& right); //!< iterator assignment
			iterator& operator++(); //!< iterator increment
			iterator& operator--(); //!< iterator decrement
			Widget* operator*(); //!< iterator dereferencing
		private:
			WidgetCollectionItemPtrList::iterator mIter;
		};

		iterator begin(); //!< returns an iterator for the collection starting at the beginning
		iterator end(); //!< returns an iterator for the collection starting at the end

	};

	class OPENGUI_API I_WidgetContainer{
	public:
		I_WidgetContainer(){}
		~I_WidgetContainer(){}
		WidgetCollection Children;
	protected:
	private:
	};

}

#endif // E65861C2_92D6_4345_8B3B_5B65D114F3C1