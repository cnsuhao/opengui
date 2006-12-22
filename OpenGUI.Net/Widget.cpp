// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "Stdafx.h"

#include "Widget.h"
#include "ObjectHandle.h"
#include "HandleSystem.h"

namespace OpenGUI_Net {

	//############################################################################
	String ^ Widget::getName() {
		sanityTest();
		OpenGUI::Widget* w = dynamic_cast<OpenGUI::Widget*>( getHandle()->getObject() );
		String ^ str;
		THRU_THROW_BEGIN
		str = Marshal::STRING( w->getName() );
		THRU_THROW_END
		return str;
	}
	//############################################################################
	void Widget::setName( String ^ name ) {
		sanityTest();
		OpenGUI::Widget* w = dynamic_cast<OpenGUI::Widget*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		w->setName( Marshal::STRING( name ) );
		THRU_THROW_END
	}
	//############################################################################
	bool Widget::getEnabled() {
		sanityTest();
		OpenGUI::Widget* w = dynamic_cast<OpenGUI::Widget*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		return w->getEnabled();
		THRU_THROW_END
	}
	//############################################################################
	void Widget::setEnabled( bool value ) {
		sanityTest();
		OpenGUI::Widget* w = dynamic_cast<OpenGUI::Widget*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		w->setEnabled( value );
		THRU_THROW_END
	}
	//############################################################################
	void Widget::invalidate() {
		sanityTest();
		OpenGUI::Widget* w = dynamic_cast<OpenGUI::Widget*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		w->invalidate();
		THRU_THROW_END
	}
	//############################################################################
	void Widget::flush() {
		sanityTest();
		OpenGUI::Widget* w = dynamic_cast<OpenGUI::Widget*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		w->flush();
		THRU_THROW_END
	}
	//############################################################################
	WidgetCollection ^ Widget::getContainer() {
		sanityTest();
		OpenGUI::Widget* w = dynamic_cast<OpenGUI::Widget*>( getHandle()->getObject() );
		OpenGUI::WidgetCollection* wc;
		THRU_THROW_BEGIN
		wc = w->getContainer();
		THRU_THROW_END
		if ( !wc ) return nullptr;
		WidgetCollection ^ mwc = gcnew WidgetCollection( wc );
		return mwc;
	}
	//############################################################################
	WidgetList ^ Widget::getChildrenAt( FVector2 position ) {
		return Widget::getChildrenAt( position, false );
	}
	//############################################################################
	WidgetList ^ Widget::getChildrenAt( FVector2 position, bool recursive ) {
		sanityTest();
		OpenGUI::Widget* w = dynamic_cast<OpenGUI::Widget*>( getHandle()->getObject() );
		OpenGUI::FVector2 pos = Marshal::FVECTOR2( position );
		OpenGUI::WidgetPtrList ptrList; // something to hold the results

		//do the function call
		THRU_THROW_BEGIN
		w->getChildrenAt( pos, ptrList, recursive );
		THRU_THROW_END

		// now build the managed list from the native result
		WidgetList ^ out = gcnew WidgetList();
		OpenGUI::WidgetPtrList::iterator iter, iterend = ptrList.end();
		for ( iter = ptrList.begin(); iter != iterend; iter++ ) {
			OpenGUI::Widget* nchild = ( *iter ); // native child
			Widget ^ mchild = dynamic_cast < Widget ^ >( HandleSystem::getManaged( nchild ) ); // managed child
			out->Add( mchild ); // add the managed child reference to the list
		}
		// and out goes the final list (that was "fun")
		return out;
	}
	//############################################################################
	Widget ^ Widget::getChildAt( FVector2 position ) {
		return getChildAt( position, false );
	}
	//############################################################################
	Widget ^ Widget::getChildAt( FVector2 position, bool recursive ) {
		sanityTest();
		OpenGUI::Widget* w = dynamic_cast<OpenGUI::Widget*>( getHandle()->getObject() );
		OpenGUI::Widget* wout;
		THRU_THROW_BEGIN
		wout = w->getChildAt( Marshal::FVECTOR2( position ), recursive );
		THRU_THROW_END
		return dynamic_cast < Widget ^ >( HandleSystem::getManaged( wout ) );
	}
	//############################################################################
	Widget ^ Widget::getPath( String ^ path ) {
		sanityTest();
		OpenGUI::Widget* w = dynamic_cast<OpenGUI::Widget*>( getHandle()->getObject() );
		OpenGUI::Widget* wout;
		THRU_THROW_BEGIN
		wout = w->getPath( Marshal::STRING( path ) );
		THRU_THROW_END
		return dynamic_cast < Widget ^ >( HandleSystem::getManaged( wout ) );
	}
	//############################################################################
	FVector2 Widget::pointToScreen( FVector2 local_point ) {
		sanityTest();
		OpenGUI::Widget* w = dynamic_cast<OpenGUI::Widget*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		return Marshal::FVECTOR2( w->pointToScreen( Marshal::FVECTOR2( local_point ) ) );
		THRU_THROW_END
	}
	//############################################################################
	FVector2 Widget::pointFromScreen( FVector2 screen_point ) {
		sanityTest();
		OpenGUI::Widget* w = dynamic_cast<OpenGUI::Widget*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		return Marshal::FVECTOR2( w->pointFromScreen( Marshal::FVECTOR2( screen_point ) ) );
		THRU_THROW_END
	}
	//############################################################################
	bool Widget::hasCursorFocus() {
		sanityTest();
		OpenGUI::Widget* w = dynamic_cast<OpenGUI::Widget*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		return w->hasCursorFocus();
		THRU_THROW_END
	}
	//############################################################################
	bool Widget::hasKeyFocus() {
		sanityTest();
		OpenGUI::Widget* w = dynamic_cast<OpenGUI::Widget*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		return w->hasKeyFocus();
		THRU_THROW_END
	}
	//############################################################################

} // namespace OpenGUI_Net {
