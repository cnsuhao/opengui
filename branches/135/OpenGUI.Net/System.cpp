// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "Stdafx.h"
#include "System.h"
#include "Renderer.h"
#include "HandleSystem.h"

using namespace System;

namespace OpenGUI_Net {
	//############################################################################
	//OpenGUI::System* System::gSystem = 0;
	//############################################################################
	//############################################################################
	System ^ System::getHandle() {
		if ( gHandle == nullptr )
			throw gcnew ::System::Exception( "Need to initialize System before getting a handle." );
		return gHandle;
	}
	//############################################################################
	System ^ System::initialize( Renderer ^ renderer ) {
		if ( gHandle != nullptr )
			throw gcnew ::System::Exception( "Cannot initialize OpenGUI::System because it is already initialized." );

		HandleSystem* handleSystem = new HandleSystem;

		OpenGUI::System* tmp;
		THRU_THROW_BEGIN
		OpenGUI::Renderer* rPtr = renderer->getNativeRenderer();
		tmp = new OpenGUI::System( rPtr);
		THRU_THROW_END
		gHandle = gcnew System( tmp, handleSystem  );
		return gHandle;
	}
	//############################################################################
	void System::shutdown() {
		sanityTest();
		THRU_THROW_BEGIN
		delete gSystem;
		THRU_THROW_END
		gSystem = 0;

		delete mHandleSystem;
	}
	//############################################################################
	void System::sanityTest() {
		if ( gSystem == 0 || gHandle != this )
			throw gcnew ::System::Exception( "Expired OpenGUI::System handle." );
	}
	//############################################################################
	System::System( OpenGUI::System* systemPtr, HandleSystem* handleSystem ) {
		gSystem = systemPtr;
		mHandleSystem = handleSystem;
	}
	//############################################################################
	void System::loadPlugin( String ^ fileName ) {
		sanityTest();
		THRU_THROW_BEGIN
		gSystem->loadPlugin( Marshal::STRING( fileName ) );
		THRU_THROW_END
	}
	//############################################################################
	void System::unloadPlugin( String ^ fileName ) {
		sanityTest();
		THRU_THROW_BEGIN
		gSystem->unloadPlugin( Marshal::STRING( fileName ) );
		THRU_THROW_END
	}
	//############################################################################
	void System::update() {
		sanityTest();
		THRU_THROW_BEGIN
		gSystem->update();
		THRU_THROW_END
	}
	//############################################################################
	void System::updateScreens() {
		sanityTest();
		THRU_THROW_BEGIN
		gSystem->updateScreens();
		THRU_THROW_END
	}
	//############################################################################
	void System::updateTime() {
		sanityTest();
		THRU_THROW_BEGIN
		gSystem->updateTime();
		THRU_THROW_END
	}
	//############################################################################
} // namespace OpenGUINet {
