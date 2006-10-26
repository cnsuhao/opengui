#ifndef B3FEF87E_3BE5_4c98_9E93_C8CDFFA7504C
#define B3FEF87E_3BE5_4c98_9E93_C8CDFFA7504C

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"

namespace OpenGUI{
	//! String Converter providing conversions back and forth between strings and common types
	class OPENGUI_API StrConv{
	public:
		//! Turn a string into an int
		static void toInt(const std::string& in, int& out);
		//! Turn a string into an unsigned int
		static void toUInt(const std::string& in, unsigned int& out);
		//! Turn an int into a string
		static void fromInt(int in, std::string& out);
		//! Turn an unsigned int into a string
		static void fromUInt(unsigned int in, std::string& out);
		//! Turn a string into a float
		static void toFloat(const std::string& in, float& out);
		//! Turn a float into a string
		static void fromFloat(float in, std::string& out);
	};
}

#endif // B3FEF87E_3BE5_4c98_9E93_C8CDFFA7504C
