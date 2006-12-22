// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "Stdafx.h"
#include "WidgetManager.h"
#include "Widget.h"
#include "HandleSystem.h"
#include "ObjectHandle.h"

using namespace System;

namespace OpenGUI_Net {
	//############################################################################
	//############################################################################
	WidgetManager ^ WidgetManager::getHandle() {
		if ( gHandle == nullptr )
			throw gcnew ::System::Exception( "Need to initialize System before getting a handle." );
		return gHandle;
	}
	//############################################################################
	void WidgetManager::sanityTest() {
		if ( mWidgetManager == 0 || gHandle != this )
			throw gcnew ::System::Exception( "Expired OpenGUI::WidgetManager handle." );
	}
	//############################################################################
	WidgetManager::WidgetManager( OpenGUI::WidgetManager* widgetManagerPtr ) {
		mWidgetManager = widgetManagerPtr;
		gHandle = this;
	}
	//############################################################################
	Widget ^ WidgetManager::CreateRawWidget( String ^ Name ) {
		return CreateRawWidget( Name, "" );
	}
	//############################################################################
	Widget ^ WidgetManager::CreateRawWidget( String ^ Name, String ^ Library ) {
		OpenGUI::Widget* w;
		sanityTest();
		THRU_THROW_BEGIN
		w = mWidgetManager->CreateRawWidget( Marshal::STRING( Name ), Marshal::STRING( Library ) );
		THRU_THROW_END
		return static_cast < Widget ^ >( HandleSystem::getManaged( w ) );
	}
	//############################################################################
	Widget ^ WidgetManager::CreateDefinedWidget( String ^ Name ) {
		OpenGUI::Widget* w;
		sanityTest();
		THRU_THROW_BEGIN
		w = mWidgetManager->CreateDefinedWidget( Marshal::STRING( Name ) );
		THRU_THROW_END
		return static_cast < Widget ^ >( HandleSystem::getManaged( w ) );
	}
	//############################################################################
	//void DefineWidget( String^ Name, const ValueList& propertyList, String^ BaseName, String^ BaseLibrary );
	//############################################################################
	void WidgetManager::UndefineWidget( String ^ Name ) {
		sanityTest();
		THRU_THROW_BEGIN
		mWidgetManager->UndefineWidget( Marshal::STRING( Name ) );
		THRU_THROW_END
	}
	//############################################################################
	//WidgetRegPairList GetRegisteredWidgets();
	//############################################################################
	//WidgetDefList GetDefinedWidgets();
	//############################################################################
	unsigned int WidgetManager::getStat_RegWidgets() {
		unsigned int ret;
		size_t RegWidgets, RegLibs, DefWidgets;
		sanityTest();
		THRU_THROW_BEGIN
		mWidgetManager->getStats( RegWidgets, RegLibs, DefWidgets );
		THRU_THROW_END
		ret = ( unsigned int ) RegWidgets;
		return ret;
	}
	//############################################################################
	unsigned int WidgetManager::getStat_RegLibs() {
		unsigned int ret;
		size_t RegWidgets, RegLibs, DefWidgets;
		sanityTest();
		THRU_THROW_BEGIN
		mWidgetManager->getStats( RegWidgets, RegLibs, DefWidgets );
		THRU_THROW_END
		ret = ( unsigned int ) RegLibs;
		return ret;
	}
	//############################################################################
	unsigned int WidgetManager::getStat_DefWidgets() {
		unsigned int ret;
		size_t RegWidgets, RegLibs, DefWidgets;
		sanityTest();
		THRU_THROW_BEGIN
		mWidgetManager->getStats( RegWidgets, RegLibs, DefWidgets );
		THRU_THROW_END
		ret = ( unsigned int ) DefWidgets;
		return ret;
	}
	//############################################################################
} // namespace OpenGUI_Net {
