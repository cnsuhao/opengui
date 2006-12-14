#ifndef D8213470_947C_4A26_A6E3_2ED806D2B523
#define D8213470_947C_4A26_A6E3_2ED806D2B523

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"

namespace OpenGUI {
	class XMLNode; // forward declaration
	class Font; // forward declaration
	template<typename> class RefPtr; // forward declaration
	class Imagery; // forward declaration
	typedef RefPtr<Imagery> ImageryPtr; // forward declaration
	class Face; // forward declaration
	typedef RefPtr<Face> FacePtr; // forward declaration
	class Cursor; // forward declaration
	typedef RefPtr<Cursor> CursorPtr; // forward declaration

	/*! \addtogroup Types
		@{
	*/

	//############################################################################
	//! An encapsulation class used for passing values back and forth in the Accessor system
	/*! Each Value has a stored value of \c ValueType as well as the option to carry
	a string based \c Name.
	*/
	class OPENGUI_API Value {
	public:
		//! Constructor. \c Name is optional, but will set the name of this Value if given
		Value( const std::string& Name = "" );
		//! Copy Constructor
		Value( const Value& copy );
		//! Destructor
		~Value();

//!\name Assigning constructors that auto detect type based on parameter type
//@{
		//! Constructor, initializes object with copy of given \c value, the \c Name is optional
		Value( const std::string& value, const std::string& Name = "" );
		//! Constructor, initializes object with copy of given \c value, the \c Name is optional
		Value( const char* value, const std::string& Name = "" );
		//! Constructor, initializes object with copy of given \c value, the \c Name is optional
		Value( bool boolean, const std::string& Name = "" );
		//! Constructor, initializes object with copy of given \c value, the \c Name is optional
		Value( float value, const std::string& Name = "" );
		//! Constructor, initializes object with copy of given \c value, the \c Name is optional
		Value( const FVector2& value, const std::string& Name = "" );
		//! Constructor, initializes object with copy of given \c value, the \c Name is optional
		Value( const FRect& value, const std::string& Name = "" );
		//! Constructor, initializes object with copy of given \c value, the \c Name is optional
		Value( int value, const std::string& Name = "" );
		//! Constructor, initializes object with copy of given \c value, the \c Name is optional
		Value( const IVector2& value, const std::string& Name = "" );
		//! Constructor, initializes object with copy of given \c value, the \c Name is optional
		Value( const IRect& value, const std::string& Name = "" );
		//! Constructor, initializes object with copy of given \c value, the \c Name is optional
		Value( const Color& value, const std::string& Name = "" );
		//! Constructor, initializes object with copy of given \c value, the \c Name is optional
		Value( const Font& value, const std::string& Name = "" );
		//! Constructor, initializes object with copy of given \c value, the \c Name is optional
		Value( const TextAlignment& value, const std::string& Name = "" );
		//! Constructor, initializes object with copy of given \c value, the \c Name is optional
		Value( const ImageryPtr& value, const std::string& Name = "" );
		//! Constructor, initializes object with copy of given \c value, the \c Name is optional
		Value( const FacePtr& value, const std::string& Name = "" );
		//! Constructor, initializes object with copy of given \c value, the \c Name is optional
		Value( const CursorPtr& value, const std::string& Name = "" );
//@}

		//! gets the name of this Value
		const std::string& getName()const {
			return mName;
		}
		//! sets the name of this Value
		void setName( const std::string& Name = "" ) {
			mName = Name;
		}

		//! signifies the stored value type
		enum ValueType {
			T_STRING = 0, //!< String value type
			T_BOOL = 1, //!< Boolean value type
			T_FLOAT = 2, //!< Float value type
			T_FVECTOR2 = 3, //!< FVector2 value type
			T_FRECT = 4, //!< FRect value type
			T_INTEGER = 5, //!< Integer value type
			T_IVECTOR2 = 6, //!< IVector2 value type
			T_IRECT = 7, //!< IRect value type
			T_COLOR = 8, //!< Color value type
			T_FONT = 9, //!< Font value type
			T_TEXTALIGNMENT = 10, //!< TextAlignment value type
			T_IMAGERY = 11, //!< ImageryPtr value type
			T_FACE = 12, //!< FacePtr value type
			T_CURSOR = 13, //!< CursorPtr value type
		};

		//! Returns the type of this value
		ValueType getType() const;
		//! clears the stored value if one is stored, otherwise does nothing
		void clearValue();
		//! returns true if a value is stored
		bool isSet() const;

		// Comparison operator for (Left == Right)
		bool operator==( const Value& right ) const;
		// Comparison operator for (Left != Right)
		bool operator!=( const Value& right ) const;
		//! Returns true if this Value is empty (contains no stored value)
		bool operator!() const {
			return !isSet();
		}
		//! Returns true if this Value is not empty (has a value stored)
		operator bool() const {
			return isSet();
		}
		//! Assignment operation creates a complete copy of the contents (clones), but does \b not alter the \c Name of the assign target.
		Value& operator=( const Value& right );

//!\name Auto detect type based on parameter type
//@{
		//! Sets the value, stored value is a copy
		void setValue( const std::string& std_string );
		//! Sets the value, stored value is a copy
		void setValue( const char* cString );
		//! Sets the value, stored value is a copy
		void setValue( bool boolean );
		//! Sets the value, stored value is a copy
		void setValue( float floatingPoint );
		//! Sets the value, stored value is a copy
		void setValue( const FVector2& floatVector );
		//! Sets the value, stored value is a copy
		void setValue( const FRect& floatRect );
		//! Sets the value, stored value is a copy
		void setValue( int integer );
		//! Sets the value, stored value is a copy
		void setValue( const IVector2& intVector );
		//! Sets the value, stored value is a copy
		void setValue( const IRect& intRect );
		//! Sets the value, stored value is a copy
		void setValue( const Color& color );
		//! Sets the value, stored value is a copy
		void setValue( const Font& font );
		//! Sets the value, stored value is a copy
		void setValue( const TextAlignment& textAlignment );
		//! Sets the value, stored value is a copy
		void setValue( const ImageryPtr& imageryPtr );
		//! Sets the value, stored value is a copy
		void setValue( const FacePtr& facePtr );
		//! Sets the value, stored value is a copy
		void setValue( const CursorPtr& cursorPtr );
//@}

//!\name Get value as explicit type
//@{
		//! Gets the stored value, throws exception if no value is stored
		std::string getValueAsString() const;
		//! Gets the stored value, throws exception if no value is stored
		const char* getValueAsCString() const;
		//! Gets the stored value, throws exception if no value is stored
		bool getValueAsBool() const;
		//! Gets the stored value, throws exception if no value is stored
		float getValueAsFloat() const;
		//! Gets the stored value, throws exception if no value is stored
		FVector2 getValueAsFVector2() const;
		//! Gets the stored value, throws exception if no value is stored
		FRect getValueAsFRect() const;
		//! Gets the stored value, throws exception if no value is stored
		int getValueAsInt() const;
		//! Gets the stored value, throws exception if no value is stored
		IVector2 getValueAsIVector2() const;
		//! Gets the stored value, throws exception if no value is stored
		IRect getValueAsIRect() const;
		//! Gets the stored value, throws exception if no value is stored
		Color getValueAsColor() const;
		//! Gets the stored value, throws exception if no value is stored
		Font getValueAsFont() const;
		//! Gets the stored value, throws exception if no value is stored
		TextAlignment getValueAsTextAlignment() const;
		//! Gets the stored value, throws exception if no value is stored
		ImageryPtr getValueAsImageryPtr() const;
		//! Gets the stored value, throws exception if no value is stored
		FacePtr getValueAsFacePtr() const;
		//! Gets the stored value, throws exception if no value is stored
		CursorPtr getValueAsCursorPtr() const;
//@}

//!\name Set from string with explicit type conversion
//@{
		//! Sets the value from a string, parsed into an int
		void setValueAsInt( const std::string& intStr );
		//! Sets the value from a string, parsed into a float
		void setValueAsFloat( const std::string& floatStr );
		//! Sets the value from a string, parsed into an FVector2
		void setValueAsFVector2( const std::string& fv2Str );
		//! Sets the value from a string, parsed into an FRect
		void setValueAsFRect( const std::string& frectStr );
		//! Sets the value from a string, parsed into an IVector2
		void setValueAsIVector2( const std::string& iv2Str );
		//! Sets the value from a string, parsed into an IRect
		void setValueAsIRect( const std::string& irectStr );
		//! Sets the value from a string, parsed into a Color
		void setValueAsColor( const std::string& colorStr );
		//! Sets the value from a string, parsed into a string
		void setValueAsString( const std::string& stringStr );
		//! Sets the value from a string, parsed into a boolean
		void setValueAsBool( const std::string& boolStr );
		//! Sets the value from a string, parsed into a Font
		void setValueAsFont( const std::string& fontStr );
		//! Sets the value from a string, parsed into a TextAlignment
		void setValueAsTextAlignment( const std::string& textAlignmentStr );
		//! Sets the value from a string, used to look up the Imagery (can be either short name or FQN)
		void setValueAsImageryPtr( const std::string& imageryName );
		//! Sets the value from a string, used to look up the Face
		void setValueAsFacePtr( const std::string& faceName );
		//! Sets the value from a string, used to look up the Cursor via CursorManager::CreateDefinedCursor()
		void setValueAsCursorPtr( const std::string& cursorName );
//@}

//!\name Purely string based functions
//@{
		//! Sets the value from a string, performing auto detection to try to fit it into the best type
		void setValueAuto( const std::string& std_string );

		//! Returns a string representation of the stored value
		std::string toStr() const;
//@}
		//! Saves this Value to the given XMLNode object, overwriting any colliding content
		void SaveToXMLNode( XMLNode& node ) const;
		//! Loads this value from the given XMLNode object
		void LoadFromXMLNode( const XMLNode& node );

	private:
		void constructor();
		bool mHasValue;
		ValueType mType;
		union {
			void* mRaw;
			std::string* mString;
			bool* mBool;
			float* mFloat;
			FVector2* mFVector2;
			FRect* mFRect;
			int* mInt;
			IVector2* mIVector2;
			IRect* mIRect;
			Color* mColor;
			Font* mFont;
			TextAlignment* mTextAlignment;
			ImageryPtr* mImageryPtr;
			FacePtr* mFacePtr;
			CursorPtr* mCursorPtr;
		};
		std::string mName;

		static std::string _TypeToString( ValueType type );
		static ValueType _TypeFromString( const std::string& type );
	};

	//############################################################################
	//! Container of multiple Value objects. Provides stack, and name based access.
	/*! This class provides access to a grouping of Value objects with both a stack
		interface as well as a by-name interface. Care must be taken when using the
		by-name interface, as stack pops can remove named entries from the container,
		causing subsequent by-name get() operations for the missing Value to result
		in an Exception.
	*/
	class OPENGUI_API ValueList {
	public:
		//! Push the given \c value to the front of the stack
		void push_front( const Value& value );
		//! Push the given \c value to the back of the stack
		void push_back( const Value& value );
		//! Pops a Value from the front of the stack
		Value pop_front();
		//! Pops a Value from the back of the stack
		Value pop_back();
		//! Returns the current stack size
		size_t size() const;

		//! Retrieves the first Value in the list with the given \c name
		const Value& get( const std::string& name ) const;
		//! Retrieves a Value by its stack \c index
		const Value& get ( unsigned int index ) const;
	private:
		typedef std::deque<Value> ValueDeQue;
		ValueDeQue mValueDeQue;
	};

	/*! @} */ //end of Types group
}//namespace OpenGUI{

#endif
