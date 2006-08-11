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

	\warning The propery system does \b not honor property case. All registered property names are automatically 
		translated to <i>lower case</i> before they are stored. This means that all property handler callbacks
		will receive the property in lower case form \b only. If you want to save yourself some pain, I highly
		recommend having your PropertySetter and PropertyGetter callbacks only perform case-insensitive string
		comparisons if they need to do such tests.
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
	//! This is the class that provides PT_ENUM support for properties.
	/*! A PT_ENUM works like a filtered PT_STRING, only allowing predefined values through to the widget.
		In addition, applications can query the PT_ENUM for a list of acceptable values.

		\note The filtering is only one way. Any time a PropertyGet request is made to the widget, the
		PT_Enum is bypassed. The widget is assumed to do "the right thing" and only return values that
		can be successfully fed right back through the PT_Enum.

		\remarks You'll probably notice there is no way to clear or remove PT_Enum values once you've added them.
		That's not a bug, nor an oversight. ENUMs aren't something you're supposed to dynamically play with.
		Set them once at widget creation and leave them alone. You'll be much happier, I promise.

		\warning PT_Enum values are case \b insensitive. All values added or tested are first converted to
		all lower case.
	*/
	class OPENGUI_API PT_Enum{
	public:
		//! This is a list of acceptable ENUM values for the PT_Enum from which it was obtained
		typedef std::set<std::string> EnumList;

		//! The constructor does not require any default values, as this object is intended to be instantiated and held as a widget object member.
		/*! \warning Care must be taken to ensure that a PT_Enum is filled out by the widget or no property set requests will ever make it through.
		
			This class is written to be sub-classed on purpose, as it is generally much easier for a widget to create
			a private sub-classing of this object that will automatically fill itself with the desired values.
		*/
		PT_Enum();
		//! Default destructor, does nothing special.
		virtual ~PT_Enum();
		//! Adds the given value to the list of acceptable enum values
		void addValue(std::string value);
		//! Tests a single value to see if it passes the ENUM filter. \c true for pass, \c false for fail
		/*! \note This performs no case modification.*/
		bool testValue(std::string value);
		//! Returns a copy of the valid ENUM value list
		EnumList getList();
	private:
		EnumList mEnumList;
	};


	//! This is a sub-class of PT_Enum that is already set up to handle horizontal TextAlignment requests.
	class OPENGUI_API PT_Enum_TextAlignment_H : public PT_Enum{
	public:
		//! Everything important happens in the constructor automatically. I'm ready to use "out of the box".
		PT_Enum_TextAlignment_H();
	};

	//! This is a sub-class of PT_Enum that is already set up to handle horizontal TextAlignment requests.
	class OPENGUI_API PT_Enum_TextAlignment_V : public PT_Enum{
	public:
		//! Everything important happens in the constructor automatically. I'm ready to use "out of the box".
		PT_Enum_TextAlignment_V();
	};

	//#####################################################################
	//! Properties defined during calls to PropertySet::PropertySet_BindProperty() will require a type from this list.
	typedef enum{
		PT_STRING = 0, //!< String property type
		PT_BOOL = 1, //!< Boolean property type
		PT_FLOAT = 2, //!< Float property type
		PT_FVECTOR2 = 3, //!< FVector2 property type
		PT_FRECT = 4, //!< FRect property type
		PT_INTEGER = 5, //!< Integer property type
		PT_IVECTOR2 = 6, //!< IVector2 property type
		PT_IRECT = 7, //!< IRect property type
		PT_ENUM = 8 //!< PT_Enum property type
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
		//! Returns a list of valid values for the requested PT_ENUM typed property. If the given \c propertyName is not a PT_ENUM type, or it doesn't exist, an empty list is returned.
		PT_Enum::EnumList enumValues(const std::string& propertyName);
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
		//! As the other PropertySet_BindProperty() with the addition of \c pt_EnumPtr, which needs to be a pointer to a valid PT_Enum if \c type = PT_ENUM
		/*! If \c type is PT_ENUM, then the passed \c pt_EnumPtr \b must remain valid for the life of the widget.
			The easiest way to accomplish this is to place the PT_Enum directly into the widget's class as a member variable.
			<i>Yes, this is the intended method.</i>
		*/
		void PropertySet_BindProperty(const std::string& name, PropertyType type, PT_Enum* pt_EnumPtr, PropertySetter propertySetter, PropertyGetter propertyGetter);
	private:

		typedef struct _PropertyMapItem{
			PropertyType type;
			PropertySetter propertySetter;
			PropertyGetter propertyGetter;
			PT_Enum* enumPtr;
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
		//! convert a boolean to a string
		static bool toStrBool(const bool& value, std::string& result);
		//! convert a string to a boolean
		static bool fromStrBool(const std::string& value, bool& result);

		//! convert a float to a string
		static bool toStrFloat(const float& value, std::string& result);
		//! convert a string to a float
		static bool fromStrFloat(const std::string& value, float& result);

		//! convert a FVector2 to a string
		static bool toStrFVector2(const FVector2& value, std::string& result);
		//! convert a string to a FVector2
		static bool fromStrFVector2(const std::string& value, FVector2& result);

		//! convert a FRect to a string
		static bool toStrFRect(const FRect& value, std::string& result);
		//! convert a string to a FRect
		static bool fromStrFRect(const std::string& value, FRect& result);

		//! convert an integer to a string
		static bool toStrInt(const int& value, std::string& result);
		//! convert a string to an integer
		static bool fromStrInt(const std::string& value, int& result);

		//! convert a IVector2 to a string
		static bool toStrIVector2(const IVector2& value, std::string& result);
		//! convert a string to a IVector2
		static bool fromStrIVector2(const std::string& value, IVector2& result);

		//! convert a IRect to a string
		static bool toStrIRect(const IRect& value, std::string& result);
		//! convert a string to a IRect
		static bool fromStrIRect(const std::string& value, IRect& result);
	};

};//namespace OpenGUI{

#endif

