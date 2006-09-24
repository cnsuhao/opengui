#include "OpenGUI_I_WidgetContainer.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	//############################################################################
	WidgetCollection::~WidgetCollection() {
		for ( WidgetCollectionItemPtrList::iterator iter = mCollectionObjects.begin();
				iter != mCollectionObjects.end(); iter++ ) {
			hidden::WidgetCollectionItem* ptr = ( *iter );
			if ( ptr ) {
				if ( ptr->own && ptr->widgetPtr )
					delete ptr->widgetPtr;
				delete ptr;
			}
		}
	}
	//############################################################################
	void WidgetCollection::add_front(Widget* widget, bool takeOwnership){
		hidden::WidgetCollectionItem* ptr = new hidden::WidgetCollectionItem;
		ptr->own = takeOwnership;
		ptr->widgetPtr = widget;
	}
	//############################################################################
	void WidgetCollection::add_back(Widget* widget, bool takeOwnership){

	}
	//############################################################################
	bool WidgetCollection::hasWidget(Widget* widget){
		for(WidgetCollectionItemPtrList::iterator iter = mCollectionObjects.begin();
			iter != mCollectionObjects.end(); iter++){
				hidden::WidgetCollectionItem* ptr = (*iter);
				if( widget == ptr->widgetPtr )
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
	void WidgetCollection::remove(Widget* widget){
		for(WidgetCollectionItemPtrList::iterator iter = mCollectionObjects.begin();
			iter != mCollectionObjects.end(); iter++){
				hidden::WidgetCollectionItem* ptr = (*iter);
				if( widget == ptr->widgetPtr ){
					mCollectionObjects.erase(iter);
					return;
				}
		}
		OG_THROW(Exception::ERR_ITEM_NOT_FOUND,"Widget not found in WidgetCollection",__FUNCTION__);
	}
	//############################################################################
	void WidgetCollection::moveToFront(Widget* widget){
		bool owner = getWidgetHolder(widget)->own;
		remove(widget);
		add_front(widget,owner);
	}
	//############################################################################
	void WidgetCollection::moveToBack(Widget* widget){
		bool owner = getWidgetHolder(widget)->own;
		remove(widget);
		add_back(widget,owner);
	}
	//############################################################################
	Widget* WidgetCollection::getWidget(const std::string& widgetName){
		for(WidgetCollectionItemPtrList::iterator iter = mCollectionObjects.begin();
			iter != mCollectionObjects.end(); iter++){
				hidden::WidgetCollectionItem* ptr = (*iter);
				if( ptr && ptr->widgetPtr && widgetName == ptr->widgetPtr->getName() ){
					return ptr->widgetPtr;
				}
		}
		return 0;
	}
	//############################################################################
	Widget& WidgetCollection::operator[](const std::string& widgetName){
		Widget* widget = getWidget( widgetName );
		if(!widget){
			OG_THROW(Exception::ERR_ITEM_NOT_FOUND,
				"Widget not found in collection: " + widgetName,__FUNCTION__);
		}
		return *widget;
	}
	//############################################################################
	hidden::WidgetCollectionItem* WidgetCollection::getWidgetHolder(Widget* widget){
		for(WidgetCollectionItemPtrList::iterator iter = mCollectionObjects.begin();
			iter != mCollectionObjects.end(); iter++){
				hidden::WidgetCollectionItem* ptr = (*iter);
				if( widget == ptr->widgetPtr ){
					return ptr;
				}
		}
		OG_THROW(Exception::ERR_ITEM_NOT_FOUND,"Widget not found in WidgetCollection",__FUNCTION__);
	}
	//############################################################################
	Widget* WidgetCollection::iterator::operator*(){
		return 0;
	}
	//############################################################################
	WidgetCollection::iterator WidgetCollection::begin(){
		WidgetCollection::iterator iter;
		iter.mIter = mCollectionObjects.begin();
		return iter;
	}
	//############################################################################
	WidgetCollection::iterator WidgetCollection::end(){
		WidgetCollection::iterator iter;
		iter.mIter = mCollectionObjects.end();
		return iter;
	}
	//############################################################################
	WidgetCollection::iterator::iterator(){}
	//############################################################################
	WidgetCollection::iterator::iterator( const WidgetCollection::iterator& copy ) {
		mIter = copy.mIter;
	}
	//############################################################################
	bool WidgetCollection::iterator::operator==( const WidgetCollection::iterator& right ) {
		return mIter == right.mIter;
	}
	//############################################################################
	bool WidgetCollection::iterator::operator!=( const WidgetCollection::iterator& right ) {
		return mIter != right.mIter;
	}
	//############################################################################
	WidgetCollection::iterator& WidgetCollection::iterator::operator=( const WidgetCollection::iterator& right ) {
		mIter = right.mIter;
		return *this;
	}
	//############################################################################
	WidgetCollection::iterator& WidgetCollection::iterator::operator++() {
		++mIter;
		return *this;
	}
	//############################################################################
	WidgetCollection::iterator& WidgetCollection::iterator::operator--() {
		--mIter;
		return *this;
	}
	//############################################################################
}
