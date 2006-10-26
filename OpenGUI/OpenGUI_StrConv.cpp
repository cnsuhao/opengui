#include "OpenGUI_StrConv.h"

namespace OpenGUI{
	//######################################################################
	void _strTrim(std::string& str)
	{
		std::string::size_type pos = str.find_last_not_of(' ');
		if(pos != std::string::npos) {
			str.erase(pos + 1);
			pos = str.find_first_not_of(' ');
			if(pos != std::string::npos) str.erase(0, pos);
		}
		else str.erase(str.begin(), str.end());
	}
	//############################################################################
	void StrConv::toInt(const std::string& in, int& out) {
		std::string tmp = in;
		_strTrim(tmp);
		std::istringstream iss;
		iss.exceptions(std::ios_base::failbit | std::ios_base::badbit);
		iss.str(tmp);
		iss >> out;
	}
	//############################################################################
	void StrConv::toUInt(const std::string& in, unsigned int& out) {
		std::string tmp = in;
		_strTrim(tmp);
		std::istringstream iss;
		iss.exceptions(std::ios_base::failbit | std::ios_base::badbit);
		iss.str(tmp);
		iss >> out;
	}
	//############################################################################
	void StrConv::fromInt(int in, std::string& out) {
		std::stringstream ss;
		ss << in;
		out = ss.str();
	}
	//############################################################################
	void StrConv::fromUInt(unsigned int in, std::string& out) {
		std::stringstream ss;
		ss << in;
		out = ss.str();
	}
	//############################################################################
	void StrConv::toFloat(const std::string& in, float& out) {
		std::string tmp = in;
		_strTrim(tmp);
		std::istringstream iss;
		iss.exceptions(std::ios_base::failbit | std::ios_base::badbit);
		iss.str(tmp);
		iss >> out;
	}
	//############################################################################
	void StrConv::fromFloat(float in, std::string& out) {
		std::stringstream ss;
		ss << in;
		out = ss.str();
	}
	//############################################################################
}
