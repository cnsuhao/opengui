#ifndef D98EC1D8_CF89_4121_8D5C_7EBEBBAB8CDA
#define D98EC1D8_CF89_4121_8D5C_7EBEBBAB8CDA

#include "OpenGUI.h"


namespace OpenGUI{
	class PropertySet;

	/*! \brief This is the typedef used for callbacks to Property Set handlers.

	\param widget Pointer to the widget whose property is being set
	\param propertyName The name of the property that is being set
	\param newValueStr The new value of the property, in the form of a string
	\param newValuePtr A pointer to a converted object of the type that was specified when the
	property was bound. If conversion to the registered type failed, or the type is PT_STRING,
	this value will be 0.

	\return Implementors should return \c TRUE if the property set was successful, \c FALSE otherwise.
		This is not enforced within %OpenGUI, but the return value does get passed back to the
		caller of setProperty, and its functionality should be honored.

	Example usage:
\code
bool myPropertySetterCallback(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
{
  //
  // Your code in here...
  //

  return true;
}
\endcode
	\see \ref WhyCallbacks "Why Callbacks?"
	*/
	typedef bool(*PropertySetter)(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
	/*! \brief This is the typedef used for callbacks to Property Get handlers.

	\param widget Pointer to the widget whose property is being gotten
	\param propertyName The name of the property that is being gotten
	\param curValue The current value of the property should be written to this parameter

	\return Implementors should return \c TRUE if the property get was successful, \c FALSE otherwise.
	This is not enforced within %OpenGUI, but the return value does get passed back to the
	caller of getProperty, and its functionality should be honored.

	Example usage:
\code
bool myPropertyGetterCallback(PropertySet* widget, const std::string& propertyName, std::string& curValue)
{
  //
  // Your code in here...
  //

  return true;
}
\endcode
	\see \ref WhyCallbacks "Why Callbacks?"
	*/
	typedef bool (*PropertyGetter)(PropertySet* widget, const std::string& propertyName, std::string& curValue);

	//#####################################################################
	//! \internal Experimental class. Not finished
	class Enum{
	public:
		Enum(std::string firstValue);
		void addValue(std::string value);
	};
	//#####################################################################
	//! Properties defined during calls to PropertySet::PropertySet_BindProperty() will require a type from this list.
	typedef enum{
		PT_STRING = 0,
		PT_BOOL = 1,
		PT_FLOAT = 2,
		PT_FVECTOR2 = 3,
		PT_FRECT = 4,
		PT_INTEGER = 5,
		PT_IVECTOR2 = 6,
		PT_IRECT = 7,
		PT_ENUM = 8 //!< Reserved for Enum type. <b>Not yet implemented.</b>
	} PropertyType;
	//#####################################################################
	typedef struct _PropertyListItem{
		std::string propertyName;
		PropertyType propertyType;
	} PropertyListItem;
	typedef std::list<PropertyListItem> PropertyList;
	//#####################################################################


	//! This base class provides advanced string parsing and callback functionality for inheritors to easily support a text based get/set Property system.
	/*!
	Here is list of known types that the property system can natively read and interpret with examples:
	- Type: String
	  - Values: it's a string, treat it like one
	- Type: Boolean
	  - Values: 0 1 TRUE FALSE
	- Type: Float
	  - Values: any float looking number such as "1.0", "1", "0.1", or ".1"
	- Type: FVector2
	  - Values: (1.0 x 1.0), parenthesis and lower case 'x' are mandatory, spaces are optional. Each side of 'x' is filled with a valid Float in string form.
	- Type: FRect
	  - Values: { (1.0 x 1.0) X (1.0 x 1.0) }, curly braces and upper case 'X' are mandatory, spaces are optional. Each side of the 'X' is filled with a valid FVector2 in string form.
	- Type: Integer
	  - Values: any int looking number such as "1"
	- Type: IVector2
	  - Values: (1 x 1), parenthesis and lower case 'x' are mandatory, spaces are optional. Each side of 'x' is filled with a valid Integer in string form.
	- Type: IRect
	  - Values:  { (1 x 1) X (1 x 1) }, curly braces and upper case 'X' are mandatory, spaces are optional. Each side of the 'X' is filled with a valid IVector2 in string form.

	*/
	class OPENGUI_API PropertySet{
	public:
		//! Sets a property
		bool propertySet(const std::string& propertyName, const std::string& newValue);
		//! Gets a property
		bool propertyGet(const std::string& propertyName, std::string& curValue);
		//! Returns a list of properties
		PropertyList propertyList();
	protected:
		//! Binds a new property, complete with property name, type, getter function and setter function.
		/*! Widgets that implement new properties, or reimplement existing ones will need to call this
			function for each property they provide. (This is best done during the object constructor.)
			\note
			If an existing property is bound with a new handler, the old handler information is thrown
			away. Because of this, widgets that inherit other widgets can easily override the behavior
			of a previously defined property setter/getter.
			\see
			- PropertySetter
			- PropertyGetter
		*/
		void PropertySet_BindProperty(const std::string& name, PropertyType type, PropertySetter propertySetter, PropertyGetter propertyGetter);
	private:

		typedef struct _PropertyMapItem{
			PropertyType type;
			PropertySetter propertySetter;
			PropertyGetter propertyGetter;
		} PropertyMapItem;
		typedef std::map<std::string, PropertyMapItem> PropertyMap;

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
	class OPENGUI_API PropertyParser{
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

