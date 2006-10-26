#ifndef B3FEF87E_3BE5_4c98_9E93_C8CDFFA7504C
#define B3FEF87E_3BE5_4c98_9E93_C8CDFFA7504C

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"

namespace OpenGUI{
	//! String Converter providing conversions back and forth between strings and both common and %OpenGUI specific types
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
		//! Turn an IVector2 into a string
		static void fromIVector2(const IVector2& in, std::string& out);
		//! Turn a string into an IVector2
		static void toIVector2(const std::string& in, IVector2& out);
		//! Turn an IRect into a string
		static void fromIRect(const IRect& in, std::string& out);
		//! Turn a string into an IRect
		static void toIRect(const std::string& in, IRect& out);
		//! Turn an FVector2 into a string
		static void fromFVector2(const FVector2& in, std::string& out);
		//! Turn a string into an FVector2
		static void toFVector2(const std::string& in, FVector2& out);
		//! Turn an FRect into a string
		static void fromFRect(const FRect& in, std::string& out);
		//! Turn a string into an FRect
		static void toFRect(const std::string& in, FRect& out);
		//! Turn a Color into a string
		static void fromColor(const Color& in, std::string& out);
		//! Turn a string into a Color
		static void toColor(const std::string& in, Color& out);
		//! Turn a bool into a string
		static void fromBool(bool in, std::string& out);
		//! Turn a string into a bool
		static void toBool(const std::string& in, bool& out);
	};
}

#endif // B3FEF87E_3BE5_4c98_9E93_C8CDFFA7504C
