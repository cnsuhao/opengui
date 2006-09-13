#ifndef D8213470_947C_4A26_A6E3_2ED806D2B523
#define D8213470_947C_4A26_A6E3_2ED806D2B523

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"

namespace OpenGUI {
	//! Contains all special base object types
	namespace Types {

		//############################################################################
		//! An encapsulation class used for passing values back and forth in the Accessor system
		class OPENGUI_API Value {
		public:
			//! Constructor
			Value();
			//! Copy Constructor
			Value( const Value& copy );
			//! Constructor, initializes object with copy of given \c value
			Value( const std::string& value );
			//! Constructor, initializes object with copy of given \c value
			Value( const char* value );
			//! Constructor, initializes object with copy of given \c value
			Value( bool boolean );
			//! Constructor, initializes object with copy of given \c value
			Value( float value );
			//! Constructor, initializes object with copy of given \c value
			Value( const FVector2& value );
			//! Constructor, initializes object with copy of given \c value
			Value( const FRect& value );
			//! Constructor, initializes object with copy of given \c value
			Value( int value );
			//! Constructor, initializes object with copy of given \c value
			Value( const IVector2& value );
			//! Constructor, initializes object with copy of given \c value
			Value( const IRect& value );
			//! Constructor, initializes object with copy of given \c value
			Value( const Enum& value );
			//! Constructor, initializes object with copy of given \c value
			Value( const Color& value );

			//! Destructor
			~Value();

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
				T_ENUM = 8, //!< Enum value type
				T_COLOR = 9 //!< Color value type
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
			void setValue( const Enum& string_enumeration );
			//! Sets the value, stored value is a copy
			void setValue( const Color& color );

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
			Enum getValueAsEnum() const;
			//! Gets the stored value, throws exception if no value is stored
			Color getValueAsColor() const;


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
				Enum* mEnum;
				Color* mColor;
			};
		};

		//############################################################################
		class ValueListDecl {
		public:
			ValueListDecl();
			~ValueListDecl();
		};
		//############################################################################
		class OPENGUI_API ValueList {
		public:
			void push();
			void pop();
		};


	}//namespace Test{
}//namespace OpenGUI{

#endif
