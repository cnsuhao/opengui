#include "OpenGUI_WidgetCollection.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Widget.h"
#include "OpenGUI_I_WidgetContainer.h"

namespace OpenGUI {
	//############################################################################
	WidgetCollection::WidgetCollection(){
		/**/
	}
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
	void WidgetCollection::_notifyChildDelete( Widget* widgetToRemove ) {
		remove( widgetToRemove );
	}
	//############################################################################
	void WidgetCollection::add_front( Widget* widget, bool takeOwnership ) {
		if ( !widget )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Invalid Widget pointer: 0", __FUNCTION__ );
		const std::string wName = widget->getName();
		if ( wName != "" ) {
			Widget* w = getWidget( wName );
			if ( w )
				OG_THROW( Exception::ERR_DUPLICATE_ITEM, "Cannot have more than 1 widget with same name per container: " + wName, __FUNCTION__ );
		}
		_add_front( widget, takeOwnership );
		mIContainer->_notifyChildAdded(this, widget );
	}
	//############################################################################
	void WidgetCollection::add_back( Widget* widget, bool takeOwnership ) {
		if ( !widget )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Invalid Widget pointer: 0", __FUNCTION__ );
		const std::string wName = widget->getName();
		if ( wName != "" ) {
			Widget* w = getWidget( wName );
			if ( w )
				OG_THROW( Exception::ERR_DUPLICATE_ITEM, "Cannot have more than 1 widget with same name per container: " + wName, __FUNCTION__ );
		}
		_add_back( widget, takeOwnership );
		mIContainer->_notifyChildAdded(this, widget );
	}
	//############################################################################
	void WidgetCollection::remove( Widget* widget ) {
		_remove( widget );
		mIContainer->_notifyChildRemoved(this, widget );
	}
	//############################################################################
	void WidgetCollection::_add_front( Widget* widget, bool takeOwnership ) {
		WidgetCollectionItem* ptr = new WidgetCollectionItem;
		ptr->own = takeOwnership;
		ptr->widgetPtr = widget;
		mCollectionObjects.push_front( ptr );
	}
	//############################################################################
	void WidgetCollection::_add_back( Widget* widget, bool takeOwnership ) {
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
	Widget* WidgetCollection::getWidget( const std::string& widgetName ) const {
		for ( WidgetCollectionItemPtrList::const_iterator iter = mCollectionObjects.begin();
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
} // namespace OpenGUI {
