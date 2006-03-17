
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
			OG_THROW(Exception::OP_FAILED, "Could not load library " + mName, "DynamicLib::load");
		}
	}
	//############################################################################
	void DynamicLib::unload()
	{
		if(!DYNAMICLIB_UNLOAD(mHandle)){
			OG_THROW(Exception::OP_FAILED, "Could not unload library " + mName, "DynamicLib::unload");
		}
	}
	//############################################################################
	void* DynamicLib::getSymbol(const std::string& symbolName) const
	{
		return (void*) DYNAMICLIB_GETSYMBOL(mHandle,symbolName.c_str());
	}
	//############################################################################
};//namespace OpenGUI{


