
#include "OpenGUI.h"

namespace OpenGUI{

	//######################################################################
	PropertySet::PropertyList PropertySet::propertyList()
	{
		PropertySet::PropertyList retval;
		PropertyMap::iterator iter =_mPropertySubscriberList.begin();
		while(iter != _mPropertySubscriberList.end()){
			PropertySet::PropertyListItem item;
			item.propertyName =  iter->first;
			item.propertyType = iter->second.type;
			retval.push_back(item);
			iter++;
		}
		return retval;
	}
	//######################################################################
	bool PropertySet::propertySet(const std::string& propertyName, const std::string& newValue)
	{
		PropertyMap::iterator iter = _mPropertySubscriberList.find(propertyName);
		//if the property doesn't exist, return false
		if(iter == _mPropertySubscriberList.end())
			return false;
		//if the property setter doesn't exist, return false
		if(iter->second.propertySetter == PropertySetter())
			return false;

		//waste of stack space. =(
		bool boolHolder;
		float floatHolder;
		FVector2 fv2Holder;
		FRect frHolder;
		int intHolder;
		IVector2 iv2Holder;
		IRect irHolder;

		switch(iter->second.type){
			case PT_STRING:
				return iter->second.propertySetter.Call(propertyName, newValue, 0);
			case PT_BOOL:
				if(PropertyParser::fromStrBool(newValue,boolHolder))
					return iter->second.propertySetter.Call(propertyName, newValue, &boolHolder);
				else
					return iter->second.propertySetter.Call(propertyName, newValue, 0);
			case PT_FLOAT:
				if(PropertyParser::fromStrFloat(newValue,floatHolder))
					return iter->second.propertySetter.Call(propertyName, newValue, &floatHolder);
				else
					return iter->second.propertySetter.Call(propertyName, newValue, 0);
			case PT_FVECTOR2:
				if(PropertyParser::fromStrFVector2(newValue,fv2Holder))
					return iter->second.propertySetter.Call(propertyName, newValue, &fv2Holder);
				else
					return iter->second.propertySetter.Call(propertyName, newValue, 0);
			case PT_FRECT:
				if(PropertyParser::fromStrFRect(newValue,frHolder))
					return iter->second.propertySetter.Call(propertyName, newValue, &frHolder);
				else
					return iter->second.propertySetter.Call(propertyName, newValue, 0);
			case PT_INTEGER:
				if(PropertyParser::fromStrInt(newValue,intHolder))
					return iter->second.propertySetter.Call(propertyName, newValue, &intHolder);
				else
					return iter->second.propertySetter.Call(propertyName, newValue, 0);
			case PT_IVECTOR2:
				if(PropertyParser::fromStrIVector2(newValue,iv2Holder))
					return iter->second.propertySetter.Call(propertyName, newValue, &iv2Holder);
				else
					return iter->second.propertySetter.Call(propertyName, newValue, 0);
			case PT_IRECT:
				if(PropertyParser::fromStrIRect(newValue,irHolder))
					return iter->second.propertySetter.Call(propertyName, newValue, &irHolder);
				else
					return iter->second.propertySetter.Call(propertyName, newValue, 0);

			default: // unhandled type, return false
				return false;
		}

		return false;
	}
	//######################################################################
	bool PropertySet::propertyGet(const std::string& propertyName, std::string& curValue)
	{
		PropertyMap::iterator iter = _mPropertySubscriberList.find(propertyName);
		//if the property doesn't exist, return false
		if(iter == _mPropertySubscriberList.end())
			return false;
		//if the property setter doesn't exist, return false
		if(iter->second.propertyGetter == PropertyGetter())
			return false;

		return iter->second.propertyGetter.Call(propertyName,curValue);
	}
	//######################################################################
	void PropertySet::PropertySet_BindProperty(const std::string& name, PropertyType type, PropertySetter propertySetter, PropertyGetter propertyGetter)
	{
		PropertyMap::mapped_type item = _mPropertySubscriberList[name];
		item.type = type;
		item.propertySetter = propertySetter;
		item.propertyGetter = propertyGetter;
		_mPropertySubscriberList[name]=item;
	}
	//######################################################################



	//######################################################################
	void strTrim(std::string& str)
	{
		std::string::size_type pos = str.find_last_not_of(' ');
		if(pos != std::string::npos) {
			str.erase(pos + 1);
			pos = str.find_first_not_of(' ');
			if(pos != std::string::npos) str.erase(0, pos);
		}
		else str.erase(str.begin(), str.end());
	}
	//######################################################################
	bool PropertyParser::toStrBool(const bool& value, std::string& result)
	{
		if(value)
			result = "true";
		else
			result = "false";
		return true;
	}
	//######################################################################
	bool PropertyParser::fromStrBool(const std::string& value, bool& result)
	{
		std::string tmp=value;
		strTrim(tmp);
		if(tmp == "0"){
			result = false;
			return true;
		}
		if(tmp == "1"){
			result = true;
			return true;
		}
		std::transform(tmp.begin(),tmp.end(),tmp.begin(),std::tolower);
		if(tmp == "true"){
			result = true;
			return true;
		}
		if(tmp == "false"){
			result = false;
			return true;
		}
		return false;
	}
	//######################################################################
	bool PropertyParser::toStrFloat(const float& value, std::string& result)
	{
		std::stringstream ss;
		ss << value;
		result = ss.str();
		return true;
	}
	//######################################################################
	bool PropertyParser::fromStrFloat(const std::string& value, float& result)
	{
		std::string tmp = value;
		strTrim(tmp);
		std::istringstream iss;
		iss.exceptions(std::ios_base::failbit | std::ios_base::badbit);
		iss.str(tmp);
		try{
			iss >> result;
		}catch(...){
			return false;
		}
		return true;
	}
	//######################################################################
	bool PropertyParser::toStrFVector2(const FVector2& value, std::string& result)
	{
		result = value.toStr();
		return true;
	}
	//######################################################################
	bool PropertyParser::fromStrFVector2(const std::string& value, FVector2& result)
	{
		std::string tmp = value;
		strTrim(tmp);
		if(tmp.substr(0,1) != "(")
			return false;
		tmp = tmp.substr(1);
		if(tmp.substr(tmp.length()-1,1) != ")")
			return false;
		tmp = tmp.substr(0,tmp.length()-1);

		std::string::size_type tokenPos = tmp.find("x");
		if(tokenPos == std::string::npos)
			return false;
		std::string xHalf = tmp.substr(0,tokenPos);
		std::string yHalf = tmp.substr(tokenPos+1,std::string::npos);

		if(PropertyParser::fromStrFloat(xHalf,result.x) &&
			PropertyParser::fromStrFloat(yHalf,result.y))
			return true;

		return false;
	}
	//######################################################################
	bool PropertyParser::toStrFRect(const FRect& value, std::string& result)
	{
		result = value.toStr();
		return true;
	}
	//######################################################################
	bool PropertyParser::fromStrFRect(const std::string& value, FRect& result)
	{
		std::string tmp = value;
		strTrim(tmp);
		if(tmp.substr(0,1) != "{")
			return false;
		tmp = tmp.substr(1);
		if(tmp.substr(tmp.length()-1,1) != "}")
			return false;
		tmp = tmp.substr(0,tmp.length()-1);

		std::string::size_type tokenPos = tmp.find("X");
		if(tokenPos == std::string::npos)
			return false;
		std::string minHalf = tmp.substr(0,tokenPos);
		std::string maxHalf = tmp.substr(tokenPos+1,std::string::npos);

		if(PropertyParser::fromStrFVector2(minHalf,result.min) &&
			PropertyParser::fromStrFVector2(maxHalf,result.max))
			return true;

		return false;
	}
	//######################################################################
	bool PropertyParser::toStrInt(const int& value, std::string& result)
	{
		std::stringstream ss;
		ss << value;
		result = ss.str();
		return true;
	}
	//######################################################################
	bool PropertyParser::fromStrInt(const std::string& value, int& result)
	{
		std::string tmp = value;
		strTrim(tmp);
		std::istringstream iss;
		iss.exceptions(std::ios_base::failbit | std::ios_base::badbit);
		iss.str(tmp);
		try{
			iss >> result;
		}catch(...){
			return false;
		}
		return true;
	}
	//######################################################################
	bool PropertyParser::toStrIVector2(const IVector2& value, std::string& result)
	{
		result = value.toStr();
		return true;
	}
	//######################################################################
	bool PropertyParser::fromStrIVector2(const std::string& value, IVector2& result)
	{
		std::string tmp = value;
		strTrim(tmp);
		if(tmp.substr(0,1) != "(")
			return false;
		tmp = tmp.substr(1);
		if(tmp.substr(tmp.length()-1,1) != ")")
			return false;
		tmp = tmp.substr(0,tmp.length()-1);

		std::string::size_type tokenPos = tmp.find("x");
		if(tokenPos == std::string::npos)
			return false;
		std::string xHalf = tmp.substr(0,tokenPos);
		std::string yHalf = tmp.substr(tokenPos+1,std::string::npos);

		if(PropertyParser::fromStrInt(xHalf,result.x) &&
			PropertyParser::fromStrInt(yHalf,result.y))
			return true;

		return false;
	}
	//######################################################################
	bool PropertyParser::toStrIRect(const IRect& value, std::string& result)
	{
		result = value.toStr();
		return true;
	}
	//######################################################################
	bool PropertyParser::fromStrIRect(const std::string& value, IRect& result)
	{
		std::string tmp = value;
		strTrim(tmp);
		if(tmp.substr(0,1) != "{")
			return false;
		tmp = tmp.substr(1);
		if(tmp.substr(tmp.length()-1,1) != "}")
			return false;
		tmp = tmp.substr(0,tmp.length()-1);

		std::string::size_type tokenPos = tmp.find("X");
		if(tokenPos == std::string::npos)
			return false;
		std::string minHalf = tmp.substr(0,tokenPos);
		std::string maxHalf = tmp.substr(tokenPos+1,std::string::npos);

		if(PropertyParser::fromStrIVector2(minHalf,result.min) &&
			PropertyParser::fromStrIVector2(maxHalf,result.max))
			return true;

		return false;
	}
	//######################################################################

};