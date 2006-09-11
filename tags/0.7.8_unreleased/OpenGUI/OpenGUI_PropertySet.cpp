
#include "OpenGUI.h"

namespace OpenGUI{

	//######################################################################
	PropertyList PropertySet::propertyList()
	{
		PropertyList retval;
		PropertyMap::iterator iter =_mPropertySubscriberList.begin();
		while(iter != _mPropertySubscriberList.end()){
			PropertyListItem item;
			item.propertyName =  iter->first;
			item.propertyType = iter->second.type;
			retval.push_back(item);
			iter++;
		}
		return retval;
	}
	//######################################################################
	PT_Enum::EnumList PropertySet::enumValues(const std::string& propertyName)
	{
		PT_Enum::EnumList retval;
		std::string tmpstr = propertyName;
		std::transform(tmpstr.begin(),tmpstr.end(),tmpstr.begin(),static_cast<int(*)(int)>(std::tolower));
		PropertyMap::iterator iter =_mPropertySubscriberList.find(tmpstr);
		if(iter == _mPropertySubscriberList.end())
			return retval;
		if( 0 == iter->second.enumPtr )
			return retval;
		retval = iter->second.enumPtr->getList();
		return retval;
	}
	//######################################################################
	bool PropertySet::propertySet(const std::string& propertyName, const std::string& newValue)
	{
		std::string tmpstr = propertyName;
		std::transform(tmpstr.begin(),tmpstr.end(),tmpstr.begin(),static_cast<int(*)(int)>(std::tolower));

		LogManager::SlogMsg("PropertySet", OGLL_INSANE) << "Set Property:  "
			<< "<" << ((void*)this) << "> "
			<< "\"" << tmpstr << "\" << " << newValue << Log::endlog;

		PropertyMap::iterator iter = _mPropertySubscriberList.find(tmpstr);
		//if the property doesn't exist, return false
		if(iter == _mPropertySubscriberList.end()){
			LogManager::SlogMsg("PropertySet", OGLL_WARN) << "Property Does Not Exist: " << tmpstr << Log::endlog;
			return false;
		}
		//if the property setter doesn't exist, return false
		if(iter->second.propertySetter == PropertySetter(0)){
			LogManager::SlogMsg("PropertySet", OGLL_WARN) << "Property Does Not Have Valid PropertySetter(): " << tmpstr << Log::endlog;
			return false;
		}

		//waste of stack space. =(
		bool boolHolder;
		float floatHolder;
		FVector2 fv2Holder;
		FRect frHolder;
		int intHolder;
		IVector2 iv2Holder;
		IRect irHolder;
		std::string strHolder = newValue;

		if(iter->second.type == PT_ENUM){
			if( 0 == iter->second.enumPtr)
				return false;
			if(! iter->second.enumPtr->testValue(newValue) )
				return false;
			std::transform(strHolder.begin(),strHolder.end(),strHolder.begin(),static_cast<int(*)(int)>(std::tolower));
		}

		switch(iter->second.type){
			case PT_ENUM: //if the enum made it this far, treat it like a string
			case PT_STRING:
				return (*iter->second.propertySetter)(this, propertyName, strHolder, 0);
			case PT_BOOL:
				if(PropertyParser::fromStrBool(newValue,boolHolder))
					return (*iter->second.propertySetter)(this, propertyName, newValue, &boolHolder);
				else
					return (*iter->second.propertySetter)(this, propertyName, newValue, 0);
			case PT_FLOAT:
				if(PropertyParser::fromStrFloat(newValue,floatHolder))
					return (*iter->second.propertySetter)(this, propertyName, newValue, &floatHolder);
				else
					return (*iter->second.propertySetter)(this, propertyName, newValue, 0);
			case PT_FVECTOR2:
				if(PropertyParser::fromStrFVector2(newValue,fv2Holder))
					return (*iter->second.propertySetter)(this, propertyName, newValue, &fv2Holder);
				else
					return (*iter->second.propertySetter)(this, propertyName, newValue, 0);
			case PT_FRECT:
				if(PropertyParser::fromStrFRect(newValue,frHolder))
					return (*iter->second.propertySetter)(this, propertyName, newValue, &frHolder);
				else
					return (*iter->second.propertySetter)(this, propertyName, newValue, 0);
			case PT_INTEGER:
				if(PropertyParser::fromStrInt(newValue,intHolder))
					return (*iter->second.propertySetter)(this, propertyName, newValue, &intHolder);
				else
					return (*iter->second.propertySetter)(this, propertyName, newValue, 0);
			case PT_IVECTOR2:
				if(PropertyParser::fromStrIVector2(newValue,iv2Holder))
					return (*iter->second.propertySetter)(this, propertyName, newValue, &iv2Holder);
				else
					return (*iter->second.propertySetter)(this, propertyName, newValue, 0);
			case PT_IRECT:
				if(PropertyParser::fromStrIRect(newValue,irHolder))
					return (*iter->second.propertySetter)(this, propertyName, newValue, &irHolder);
				else
					return (*iter->second.propertySetter)(this, propertyName, newValue, 0);

			default: // unhandled type, throw!
				OG_THROW(Exception::ERR_NOT_IMPLEMENTED, "Unimplemented property type", "PropertySet::propertySet");
				return false;
		}

		return false;
	}
	//######################################################################
	bool PropertySet::propertyGet(const std::string& propertyName, std::string& curValue)
	{
		std::string tmpstr = propertyName;
		std::transform(tmpstr.begin(),tmpstr.end(),tmpstr.begin(),static_cast<int(*)(int)>(std::tolower));

		LogManager::SlogMsg("PropertySet", OGLL_INSANE) << "Get Property:  "
			<< "<" << ((void*)this) << "> "
			<< "\"" << tmpstr << "\"" << Log::endlog;

		PropertyMap::iterator iter = _mPropertySubscriberList.find(tmpstr);
		//if the property doesn't exist, return false
		if(iter == _mPropertySubscriberList.end()){
			LogManager::SlogMsg("PropertySet", OGLL_WARN) << "Property Does Not Exist: " << tmpstr << Log::endlog;
			return false;
		}

		//if the property getter doesn't exist, return false
		if(iter->second.propertyGetter == PropertyGetter(0)){
			LogManager::SlogMsg("PropertySet", OGLL_WARN) << "Property Does Not Have Valid PropertyGetter(): " << tmpstr << Log::endlog;
			return false;
		}

		return (*iter->second.propertyGetter)(this, propertyName,curValue);
	}
	//######################################################################
	std::string propertyTypeToStr(PropertyType type)
	{
		switch(type){
			case PT_STRING: return "STRING";
			case PT_BOOL: return "BOOL";
			case PT_FLOAT: return "FLOAT";
			case PT_FVECTOR2: return "FVECTOR2";
			case PT_FRECT: return "FRECT";
			case PT_INTEGER: return "INTEGER";
			case PT_IVECTOR2: return "IVECTOR2";
			case PT_IRECT: return "IRECT";
			case PT_ENUM:  return "ENUM";
			default: return "**UNKNOWN**";
		}
	}
	//######################################################################
	void PropertySet::PropertySet_BindProperty(const std::string& propertyName, PropertyType type, PropertySetter propertySetter, PropertyGetter propertyGetter)
	{
		if(type == PT_ENUM){
			OG_THROW(Exception::ERR_INVALIDPARAMS, "You cannot specify a PT_ENUM with this PropertySet_BindProperty(). Use the other one.", "PropertySet_BindProperty");
		}else
			PropertySet_BindProperty(propertyName, type, 0, propertySetter, propertyGetter);
	}
	//######################################################################
	void PropertySet::PropertySet_BindProperty(const std::string& propertyName, PropertyType type, PT_Enum* pt_EnumPtr, PropertySetter propertySetter, PropertyGetter propertyGetter)
	{
		std::string tmpstr = propertyName;
		std::transform(tmpstr.begin(),tmpstr.end(),tmpstr.begin(),static_cast<int(*)(int)>(std::tolower));

		LogManager::SlogMsg("PropertySet", OGLL_INSANE) << "Bind Property: "
			<< "<" << ((void*)this) << "> "
			<< "\"" << tmpstr
			<< "\" type: " << propertyTypeToStr(type) << Log::endlog;


		PropertyMap::mapped_type item = _mPropertySubscriberList[tmpstr];
		item.type = type;
		item.propertySetter = propertySetter;
		item.propertyGetter = propertyGetter;
		item.enumPtr = pt_EnumPtr;
		_mPropertySubscriberList[tmpstr]=item;
	}


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
	unsigned char chrLower(unsigned char c)
	{
		return std::tolower(c);
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
		std::transform(tmp.begin(),tmp.end(),tmp.begin(),static_cast<int(*)(int)>(std::tolower));
		// If the previous fails to work, use this instead
		//std::transform(tmp.begin(),tmp.end(),tmp.begin(),chrLower);
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
	//######################################################################
	//######################################################################
	PT_Enum::PT_Enum()
	{
		//
	}
	//######################################################################
	PT_Enum::~PT_Enum()
	{
		//
	}
	//######################################################################
	void PT_Enum::addValue(std::string value)
	{
		//make it all lower case
		std::transform(value.begin(),value.end(),value.begin(),static_cast<int(*)(int)>(std::tolower));

		//safe insert (ignore duplicates)
		if(! testValue(value) )
			mEnumList.insert(value);
	}
	//######################################################################
	bool PT_Enum::testValue(std::string value)
	{
		//make it all lower case
		std::transform(value.begin(),value.end(),value.begin(),static_cast<int(*)(int)>(std::tolower));

		//try to find it
		EnumList::iterator iter = mEnumList.find(value);
		if(iter != mEnumList.end())
			return true; //if we found it, it is valid
		return false; //otherwise it is not
	}
	//######################################################################
	PT_Enum::EnumList PT_Enum::getList()
	{
		return mEnumList;
	}
	//######################################################################
	PT_Enum_TextAlignment_H::PT_Enum_TextAlignment_H()
	{
		addValue("ALIGN_LEFT");
		addValue("ALIGN_RIGHT");
		addValue("ALIGN_CENTER");
		addValue("ALIGN_JUSTIFIED");
	}
	//######################################################################
	PT_Enum_TextAlignment_V::PT_Enum_TextAlignment_V()
	{
		addValue("ALIGN_TOP");
		addValue("ALIGN_BOTTOM");
		addValue("ALIGN_CENTER");
		addValue("ALIGN_JUSTIFIED");
	}
	//######################################################################
};

