
#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_DynamicLib.h"


namespace OpenGUI{
	//############################################################################
	DynamicLib::DynamicLib(const std::string& filename)
	{
		mName = filename;
	}
	//############################################################################
	DynamicLib::~DynamicLib()
	{
	}
	//############################################################################
	void DynamicLib::load()
	{
		mHandle = DYNAMICLIB_LOAD(mName.c_str());
		if(!mHandle){
			throw Exception("Could not load library " + mName + "\n");
		}
	}
	//############################################################################
	void DynamicLib::unload()
	{
		if(!DYNAMICLIB_UNLOAD(mHandle)){
			throw Exception("Could not unload library " + mName + "\n");
		}
	}
	//############################################################################
	void* DynamicLib::getSymbol(const std::string& symbolName) const
	{
		return (void*) DYNAMICLIB_GETSYMBOL(mHandle,symbolName.c_str());
	}
	//############################################################################
};//namespace OpenGUI{


