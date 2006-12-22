// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "Stdafx.h"

#include "WidgetCollection.h"
#include "Widget.h"
#include "ObjectHandle.h"
#include "HandleSystem.h"

namespace OpenGUI_Net {

	//############################################################################
	WidgetCollection::WidgetCollection( OpenGUI::WidgetCollection* c ) {
		mCollection = c;
	}
	//############################################################################
	void WidgetCollection::sanityTest() {
		if ( mCollection == 0 )
			throw gcnew ::System::Exception( "Invalid OpenGUI::WidgetCollection handle." );
	}
	//############################################################################
	void WidgetCollection::add_front( Widget ^ widget ) {
		add_front( widget, false );
	}
	//############################################################################
	void WidgetCollection::add_front( Widget ^ widget, bool takeOwnership ) {
		sanityTest();
		OpenGUI::Widget* w = static_cast<OpenGUI::Widget*>( widget->getHandle()->getObject() );
		THRU_THROW_BEGIN
		mCollection->add_front( w, takeOwnership );
		THRU_THROW_END
	}
	//############################################################################
	void WidgetCollection::add_back( Widget ^ widget ) {
		add_back( widget, false );
	}
	//############################################################################
	void WidgetCollection::add_back( Widget ^ widget, bool takeOwnership ) {
		sanityTest();
		OpenGUI::Widget* w = static_cast<OpenGUI::Widget*>( widget->getHandle()->getObject() );
		THRU_THROW_BEGIN
		mCollection->add_back( w, takeOwnership );
		THRU_THROW_END
	}
	//############################################################################
	void WidgetCollection::remove( Widget ^ widget ) {
		sanityTest();
		OpenGUI::Widget* w = static_cast<OpenGUI::Widget*>( widget->getHandle()->getObject() );
		THRU_THROW_BEGIN
		mCollection->remove( w );
		THRU_THROW_END
	}
	//############################################################################
	void WidgetCollection::moveToFront( Widget ^ widget ) {
		sanityTest();
		OpenGUI::Widget* w = static_cast<OpenGUI::Widget*>( widget->getHandle()->getObject() );
		THRU_THROW_BEGIN
		mCollection->moveToFront( w );
		THRU_THROW_END
	}
	//############################################################################
	void WidgetCollection::moveToBack( Widget ^ widget ) {
		sanityTest();
		OpenGUI::Widget* w = static_cast<OpenGUI::Widget*>( widget->getHandle()->getObject() );
		THRU_THROW_BEGIN
		mCollection->moveToBack( w );
		THRU_THROW_END
	}
	//############################################################################
	Widget ^ WidgetCollection::getWidget( String ^ widgetName ) {
		sanityTest();
		OpenGUI::Widget* w;
		THRU_THROW_BEGIN
		w = mCollection->getWidget( Marshal::STRING( widgetName ) );
		THRU_THROW_END
		return static_cast < Widget ^ >( HandleSystem::getManaged( w ) );
	}
	//############################################################################
	bool WidgetCollection::hasWidget( Widget ^ widget ) {
		sanityTest();
		OpenGUI::Widget* w = static_cast<OpenGUI::Widget*>( widget->getHandle()->getObject() );
		THRU_THROW_BEGIN
		return mCollection->hasWidget( w );
		THRU_THROW_END
	}
	//############################################################################
	Widget ^ WidgetCollection::operator[]( String^ widgetName ) {
		Widget ^ w = getWidget( widgetName );
		if ( w == nullptr )
			throw gcnew ::System::Exception( "Widget is not part of this collection: " + widgetName );
		return w;
	}
	//############################################################################
} // namespace OpenGUI_Net {
