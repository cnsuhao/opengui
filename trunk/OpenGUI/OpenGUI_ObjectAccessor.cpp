// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_ObjectAccessor.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {

	//############################################################################
	const char* ObjectAccessor::getAccessorGroup() {
		return "General";
	}
	//############################################################################
	bool ObjectProperty::getPermSettable() {
		return true;
	}
	//############################################################################
	ObjectAccessorList::ObjectAccessorList() {
		mParent = 0;
	}
	//############################################################################
	ObjectAccessorList::~ObjectAccessorList() {}
	//############################################################################
	/*! If the requested ObjectAccessor cannot be found in this ObjectAccessorList,
	then the parent ObjectAccessorList will be queried. If no parent is available
	then an exception is thrown.
	\note Throws an exception whenever the requested \c accessorName cannot
	be found, and there is no available parent in which to defer the call. */
	ObjectAccessor* ObjectAccessorList::getAccessor( const std::string& accessorName, bool recursive ) {
		//try to find locally
		ObjectAccessorMap::iterator iter = mObjectAccessorMap.find( accessorName );
		if ( iter != mObjectAccessorMap.end() )
			return iter->second;

		//if not found then recurse if appropriate
		if ( recursive && mParent )
			return mParent->getAccessor( accessorName, true );

		//throw on resolve failure
		OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Failed to resolve Accessor name: " + accessorName, "ObjectAccessorList::getAccessor" );

		//if they throw back, just hand them an empty pointer
		return 0;
	}
	//############################################################################
	void ObjectAccessorList::addAccessor( ObjectAccessor* accessor ) {
		mObjectAccessorMap[accessor->getAccessorName()] = accessor;
	}
	//############################################################################
	void ObjectAccessorList::setParent( ObjectAccessorList* parent ) {
		mParent = parent;
	}
	//############################################################################
	ObjectAccessorList* ObjectAccessorList::getParent() {
		return mParent;
	}
	//############################################################################

}// namespace OpenGUI {