// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "Stdafx.h"
#include "System.h"

using namespace System;

namespace OpenGUI_Net {
	//############################################################################
	//OpenGUI::System* System::gSystem = 0;
	//############################################################################
	//############################################################################
	System^ System::getHandle(){
		if(gHandle == nullptr)
			throw gcnew ::System::Exception("Need to initialize System before getting a handle.");
		return gHandle;
	}
	//############################################################################
	System^ System::initialize(){
		if(gHandle != nullptr)
			throw gcnew ::System::Exception("Cannot initialize OpenGUI::System because it is already initialized.");
		OpenGUI::System* tmp;
		THRU_THROW_BEGIN
			tmp = new OpenGUI::System(0);
		THRU_THROW_END
		gHandle = gcnew System(tmp);
		return gHandle;
	}
	//############################################################################
	void System::shutdown(){
		sanityTest();
		delete gSystem;
		gSystem = 0;
	}
	//############################################################################
	void System::sanityTest(){
		if(gSystem == 0 || gHandle != this)
			throw gcnew ::System::Exception("Expired OpenGUI::System handle.");
	}
	//############################################################################
	System::System(OpenGUI::System* systemPtr){
		gSystem = systemPtr;
	}
	//############################################################################
	void System::loadPlugin(String^ fileName){
		THRU_THROW_BEGIN
		gSystem->loadPlugin(Marshal::String(fileName));
		THRU_THROW_END
	}
	//############################################################################
	void System::unloadPlugin(String^ fileName){
		THRU_THROW_BEGIN
		gSystem->unloadPlugin(Marshal::String(fileName));
		THRU_THROW_END
	}
	//############################################################################
} // namespace OpenGUINet {
