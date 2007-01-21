// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_WidgetCollection.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Widget.h"


namespace OpenGUI {
	//############################################################################
	WidgetCollection::WidgetCollection() {
		mParent = 0;
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
	void WidgetCollection::appendWidgetPtrList( WidgetPtrList& l ) const {
		WidgetCollectionItemPtrList::const_iterator i, ie = mCollectionObjects.end();
		for ( i = mCollectionObjects.begin(); i != ie; i++ ) {
			WidgetCollectionItem* item = ( *i );
			l.push_back( item->widgetPtr );
		}
	}
	//############################################################################
	/*! \warning Do not take this operation lightly. Stealing ownership of WidgetCollections
	can lead to very unpredictable results. The general rule of thumb is, if you didn't
	create it, then you shouldn't be claiming ownership of it.
	\deprecated May move this functionality into the constructor to ultimately eliminate
	the potential for misuse. */
	void WidgetCollection::setParent( Object* object ) {
		mParent = object;
	}
	//############################################################################
	Object* WidgetCollection::getParent() {
		return mParent;
	}
	//############################################################################
	void WidgetCollection::attachListener( WidgetCollectionListener* listener ) {
		ListenerSet::iterator iter = mListeners.find( listener );
		if ( iter != mListeners.end() )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM, "The given WidgetCollectionListener is already attached to this WidgetCollection", __FUNCTION__ );
		mListeners.insert( listener );
	}
	//############################################################################
	void WidgetCollection::detachListener( WidgetCollectionListener* listener ) {
		ListenerSet::iterator iter = mListeners.find( listener );
		if ( iter == mListeners.end() )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM, "The given WidgetCollectionListener is not attached to this WidgetCollection", __FUNCTION__ );
		mListeners.erase( listener );
	}
	//############################################################################
	void WidgetCollection::_fireWidgetAdded( Widget* widget ) {
		widget->eventAttached( this, widget );
		ListenerSet::iterator iter, iterend = mListeners.end();
		for ( iter = mListeners.begin();iter != iterend; iter++ ) {
			WidgetCollectionListener* l = ( *iter );
			l->eventChildAttached( this, widget );
		}
	}
	//############################################################################
	void WidgetCollection::_fireWidgetRemoved( Widget* widget ) {
		widget->eventDetached( this, widget );
		ListenerSet::iterator iter, iterend = mListeners.end();
		for ( iter = mListeners.begin();iter != iterend; iter++ ) {
			WidgetCollectionListener* l = ( *iter );
			l->eventChildDetached( this, widget );
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
		if ( widget->mContainer )
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "Cannot add a widget to more than 1 WidgetCollection", __FUNCTION__ );
		const String wName = widget->getName();
		if ( wName != "" ) {
			Widget* w = getWidget( wName );
			if ( w )
				OG_THROW( Exception::ERR_DUPLICATE_ITEM, "Cannot have more than 1 widget with same name per container: " + wName, __FUNCTION__ );
		}
		_add_front( widget, takeOwnership );
		_fireWidgetAdded( widget );
	}
	//############################################################################
	void WidgetCollection::add_back( Widget* widget, bool takeOwnership ) {
		if ( !widget )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Invalid Widget pointer: 0", __FUNCTION__ );
		if ( widget->mContainer )
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "Cannot add a widget to more than 1 WidgetCollection", __FUNCTION__ );
		const String wName = widget->getName();
		if ( wName != "" ) {
			Widget* w = getWidget( wName );
			if ( w )
				OG_THROW( Exception::ERR_DUPLICATE_ITEM, "Cannot have more than 1 widget with same name per container: " + wName, __FUNCTION__ );
		}
		_add_back( widget, takeOwnership );
		_fireWidgetAdded( widget );
	}
	//############################################################################
	/*! If the collection was told to take ownership of the requested widget,
	this operation removes that ownership. The collection will no longer
	delete the removed widget on destruction.

	\throw Exception if the widget is not part of this collection
	*/
	void WidgetCollection::remove( Widget* widget ) {
		_remove( widget );
		_fireWidgetRemoved( widget );
	}
	//############################################################################
	void WidgetCollection::_add_front( Widget* widget, bool takeOwnership ) {
		WidgetCollectionItem* ptr = new WidgetCollectionItem;
		ptr->own = takeOwnership;
		ptr->widgetPtr = widget;
		widget->mContainer = this;
		mCollectionObjects.push_front( ptr );
	}
	//############################################################################
	void WidgetCollection::_add_back( Widget* widget, bool takeOwnership ) {
		WidgetCollectionItem* ptr = new WidgetCollectionItem;
		ptr->own = takeOwnership;
		ptr->widgetPtr = widget;
		widget->mContainer = this;
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
	void WidgetCollection::_remove( Widget* widget ) {
		for ( WidgetCollectionItemPtrList::iterator iter = mCollectionObjects.begin();
				iter != mCollectionObjects.end(); iter++ ) {
			WidgetCollectionItem* ptr = ( *iter );
			if ( widget == ptr->widgetPtr ) {
				widget->mContainer = 0;
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
	Widget* WidgetCollection::getWidget( const String& widgetName ) const {
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
	Widget& WidgetCollection::operator[]( const String& widgetName ) {
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
