// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "Stdafx.h"
#include "ScreenManager.h"
#include "Viewport.h"
#include "Screen.h"
#include "HandleSystem.h"

using namespace System;

namespace OpenGUI_Net {
	//############################################################################
	//OpenGUI::System* System::gSystem = 0;
	//############################################################################
	//############################################################################
	ScreenManager ^ ScreenManager::getHandle() {
		if ( gHandle == nullptr )
			throw gcnew ::System::Exception( "Need to initialize System before getting a handle." );
		return gHandle;
	}
	//############################################################################
	void ScreenManager::sanityTest() {
		if ( mScreenManager == 0 || gHandle != this )
			throw gcnew ::System::Exception( "Expired OpenGUI::System handle." );
	}
	//############################################################################
	ScreenManager::ScreenManager( OpenGUI::ScreenManager* screenManagerPtr ) {
		mScreenManager = screenManagerPtr;
		gHandle = this;
	}
	//############################################################################
	Screen ^ ScreenManager::createScreen( String ^ screenName, FVector2 initialSize ) {
		std::string name = Marshal::STRING( screenName );
		OpenGUI::FVector2 size = Marshal::FVECTOR2( initialSize );
		OpenGUI::Screen* s;
		sanityTest();
		THRU_THROW_BEGIN
		s = mScreenManager->createScreen( name, size );
		THRU_THROW_END
		Screen ^ screen = dynamic_cast < Screen ^ >( HandleSystem::getManaged( s ) );
		return screen;
	}
	//############################################################################
	void ScreenManager::destroyScreen( Screen ^ screenRef ){
		OpenGUI::Screen* s;
		s = static_cast<OpenGUI::Screen*>(screenRef->getHandle()->getObject());
		sanityTest();
		THRU_THROW_BEGIN
		mScreenManager->destroyScreen( s );
		THRU_THROW_END
	}
	//############################################################################
	void ScreenManager::updateScreens() {}
	//############################################################################
	void ScreenManager::updateTime() {}
	//############################################################################
	float ScreenManager::statGetFPS() {
		sanityTest();
		THRU_THROW_BEGIN
		return mScreenManager->statGetFPS();
		THRU_THROW_END
	}
	//############################################################################
} // namespace OpenGUINet {
