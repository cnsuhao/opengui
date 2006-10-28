#include "OpenGUI_I_WidgetContainer.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	//############################################################################
	WidgetCollection::~WidgetCollection() {
		while ( mCollectionObjects.size() > 0 ) {
			WidgetCollectionItem* ptr = mCollectionObjects.front();
			bool own = ptr->own;
			Widget* w = ptr->widgetPtr;
			remove( w );
			if ( own )
				delete w;
		}
	}
	//############################################################################
	void WidgetCollection::add_front( Widget* widget, bool takeOwnership ) {
		_add_front( widget, takeOwnership );
		mIContainer->notifyChildAdded( widget );
	}
	//############################################################################
	void WidgetCollection::add_back( Widget* widget, bool takeOwnership ) {
		_add_back( widget, takeOwnership );
		mIContainer->notifyChildAdded( widget );
	}
	//############################################################################
	void WidgetCollection::remove( Widget* widget ) {
		_remove( widget );
		mIContainer->notifyChildRemoved( widget );
	}
	//############################################################################
	void WidgetCollection::_add_front( Widget* widget, bool takeOwnership ) {
		mIContainer->notifyChildAdding( widget );
		WidgetCollectionItem* ptr = new WidgetCollectionItem;
		ptr->own = takeOwnership;
		ptr->widgetPtr = widget;
		mCollectionObjects.push_front( ptr );
	}
	//############################################################################
	void WidgetCollection::_add_back( Widget* widget, bool takeOwnership ) {
		mIContainer->notifyChildAdding( widget );
		WidgetCollectionItem* ptr = new WidgetCollectionItem;
		ptr->own = takeOwnership;
		ptr->widgetPtr = widget;
		mCollectionObjects.push_back( ptr );
	}
	//############################################################################
	bool WidgetCollection::hasWidget( Widget* widget ) {
		for ( WidgetCollectionItemPtrList::iterator iter = mCollectionObjects.begin();
				iter != mCollectionObjects.end(); iter++ ) {
			WidgetCollectionItem* ptr = ( *iter );
			if ( widget == ptr->widgetPtr )
				return true;
		}
		return false;
	}
	//############################################################################
	/*! If the collection was told to take ownership of the requested widget,
		this operation removes that ownership. The collection will no longer
		delete the removed widget on destruction.

		\throw Exception if the widget is not part of this collection
	*/
	void WidgetCollection::_remove( Widget* widget ) {
		mIContainer->notifyChildRemoving( widget );
		for ( WidgetCollectionItemPtrList::iterator iter = mCollectionObjects.begin();
				iter != mCollectionObjects.end(); iter++ ) {
			WidgetCollectionItem* ptr = ( *iter );
			if ( widget == ptr->widgetPtr ) {
				mCollectionObjects.erase( iter );
				return;
			}
		}
		OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Widget not found in WidgetCollection", __FUNCTION__ );
	}
	//############################################################################
	void WidgetCollection::moveToFront( Widget* widget ) {
		bool owner = getWidgetHolder( widget )->own;
		_remove( widget );
		_add_front( widget, owner );
	}
	//############################################################################
	void WidgetCollection::moveToBack( Widget* widget ) {
		bool owner = getWidgetHolder( widget )->own;
		_remove( widget );
		_add_back( widget, owner );
	}
	//############################################################################
	Widget* WidgetCollection::getWidget( const std::string& widgetName ) {
		for ( WidgetCollectionItemPtrList::iterator iter = mCollectionObjects.begin();
				iter != mCollectionObjects.end(); iter++ ) {
			WidgetCollectionItem* ptr = ( *iter );
			if ( ptr && ptr->widgetPtr && widgetName == ptr->widgetPtr->getName() ) {
				return ptr->widgetPtr;
			}
		}
		return 0;
	}
	//############################################################################
	Widget& WidgetCollection::operator[]( const std::string& widgetName ) {
		Widget* widget = getWidget( widgetName );
		if ( !widget ) {
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND,
					  "Widget not found in collection: " + widgetName, __FUNCTION__ );
		}
		return *widget;
	}
	//############################################################################
	WidgetCollection::WidgetCollectionItem* WidgetCollection::getWidgetHolder( Widget* widget ) {
		for ( WidgetCollectionItemPtrList::iterator iter = mCollectionObjects.begin();
				iter != mCollectionObjects.end(); iter++ ) {
			WidgetCollectionItem* ptr = ( *iter );
			if ( widget == ptr->widgetPtr ) {
				return ptr;
			}
		}
		OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Widget not found in WidgetCollection", __FUNCTION__ );
	}
	//############################################################################
	WidgetCollection::iterator WidgetCollection::begin() {
		WidgetCollection::iterator iter;
		iter.mIter = mCollectionObjects.begin();
		return iter;
	}
	//############################################################################
	WidgetCollection::iterator WidgetCollection::end() {
		WidgetCollection::iterator iter;
		iter.mIter = mCollectionObjects.end();
		return iter;
	}
	//############################################################################
	WidgetCollection::reverse_iterator WidgetCollection::rbegin() {
		WidgetCollection::reverse_iterator iter;
		iter.mIter = mCollectionObjects.rbegin();
		return iter;
	}
	//############################################################################
	WidgetCollection::reverse_iterator WidgetCollection::rend() {
		WidgetCollection::reverse_iterator iter;
		iter.mIter = mCollectionObjects.rend();
		return iter;
	}
	//############################################################################
	//############################################################################



	//############################################################################
	//############################################################################
	I_WidgetContainer::I_WidgetContainer() {
		Children.mIContainer = this;
	}
	//############################################################################
	void I_WidgetContainer::notifyChildDelete( Widget* widgetToRemove ) {
		Children.remove( widgetToRemove );
	}
	//############################################################################
	void I_WidgetContainer::notifyChildAdding( Widget* widgetPtr ) {
		if ( widgetPtr->mContainer != 0 )
			OG_THROW( Exception::ERR_INTERNAL_ERROR,
					  "Widget is already a child of another container!", __FUNCTION__ );
		widgetPtr->_attaching();
		widgetPtr->mContainer = this;
	}
	//############################################################################
	void I_WidgetContainer::notifyChildRemoving( Widget* widgetPtr ) {
		if ( widgetPtr->mContainer != this )
			OG_THROW( Exception::ERR_INTERNAL_ERROR,
					  "Widget is not a child of this container!", __FUNCTION__ );
		widgetPtr->_detaching();
		widgetPtr->mContainer = 0;
	}
	//############################################################################
	void I_WidgetContainer::notifyChildAdded( Widget* widgetPtr ) {
		eventChildAttached( this, widgetPtr );
		widgetPtr->eventAttached( this, widgetPtr );
	}
	//############################################################################
	void I_WidgetContainer::notifyChildRemoved( Widget* widgetPtr ) {
		eventChildDetached( this, widgetPtr );
		widgetPtr->eventDetached( this, widgetPtr );
	}
	//############################################################################
	void I_WidgetContainer::eventChildAttached( I_WidgetContainer* container, Widget* newChild ) {
		/*! Default is to do nothing */
	}
	//############################################################################
	void I_WidgetContainer::eventChildDetached( I_WidgetContainer* container, Widget* prevChild ) {
		/*! Default is to do nothing */
	}
	//############################################################################
}
