#ifndef D98EC1D8_CF89_4121_8D5C_7EBEBBAB8CDA
#define D98EC1D8_CF89_4121_8D5C_7EBEBBAB8CDA

#include "OpenGUI.h"


namespace OpenGUI{
	
	
	typedef Functors::GenericFunctorImpl_Ret_3Arg<bool, const std::string&, const std::string&, const void*> PropertySetter;
	typedef Functors::GenericFunctorImpl_Ret_2Arg<bool, const std::string&, std::string&> PropertyGetter;


	//#####################################################################


	class PropertySet{
	public:
		typedef enum{
			PT_STRING = 0, PT_BOOL = 1,
			PT_FLOAT = 2, PT_FVECTOR2 = 3, PT_FRECT = 4,
			PT_INTEGER = 5, PT_IVECTOR2 = 6, PT_IRECT = 7
		} PropertyType;
		typedef struct _PropertyMapItem{
			PropertyType type;
			PropertySetter propertySetter;
			PropertyGetter propertyGetter;
		} PropertyMapItem;
		typedef std::map<std::string, PropertyMapItem> PropertyMap;

		typedef struct _PropertyListItem{
			std::string propertyName;
			PropertyType propertyType;
		} PropertyListItem;
		typedef std::list<PropertyListItem> PropertyList;

		bool propertySet(const std::string& propertyName, const std::string& newValue);
		bool propertyGet(const std::string& propertyName, std::string& curValue);
		PropertyList propertyList();
	protected:
		void PropertySet_BindProperty(const std::string& name, PropertyType type, PropertySetter propertySetter, PropertyGetter propertyGetter);
	private:
		//some sort of property map
		PropertyMap _mPropertySubscriberList;
	};


	//#####################################################################


	//! This is a static function container that provides several functions to convert properties to and from strings
	/*! All functions take the initial type as input, and write their result to the result (2nd) parameter.
		The return value of the function indicates if a successful conversion was achieved.
		\return
		\c FALSE - Could not convert the given input to the desired output. Value of \c result is undefined.
		\c TRUE - Conversion successful, value stored in \c result.

		\note All of these functions are case insensitive. They always output the results of
			toStr operations in all lower case.
	*/
	class PropertyParser{
	public:
		static bool toStrBool(const bool& value, std::string& result);
		static bool fromStrBool(const std::string& value, bool& result);

		static bool toStrFloat(const float& value, std::string& result);
		static bool fromStrFloat(const std::string& value, float& result);

		static bool toStrFVector2(const FVector2& value, std::string& result);
		static bool fromStrFVector2(const std::string& value, FVector2& result);

		static bool toStrFRect(const FRect& value, std::string& result);
		static bool fromStrFRect(const std::string& value, FRect& result);

		static bool toStrInt(const int& value, std::string& result);
		static bool fromStrInt(const std::string& value, int& result);

		static bool toStrIVector2(const IVector2& value, std::string& result);
		static bool fromStrIVector2(const std::string& value, IVector2& result);

		static bool toStrIRect(const IRect& value, std::string& result);
		static bool fromStrIRect(const std::string& value, IRect& result);
	};

};//namespace OpenGUI{

#endif

