#ifndef C08D1F7D_73BD_44f5_BBEA_5926A6C6E676
#define C08D1F7D_73BD_44f5_BBEA_5926A6C6E676

#include "OpenGUI_Exports.h"

#if OPENGUI_COMPILER == OPENGUI_COMPILER_MSVC
	// This warning can be disregarded
	#pragma warning (disable : 4251)
#endif

namespace OpenGUI{

	//! The only Exception class OpenGUI currently uses.
	class OPENGUI_API Exception
	{
	public:
		Exception(const std::string& msg) : mMsg(msg) {}
		~Exception() {}
		std::string getMessage() const {return(mMsg);}
	private:
		std::string mMsg;
	};
};
#endif
