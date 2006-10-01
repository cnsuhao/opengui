#include "OpenGUI_Value.h"
#include "OpenGUI_Exception.h"
namespace OpenGUI {
	//#####################################################################
	void Value::constructor() {
		mRaw = 0;
		mHasValue = false;
	}
	//#####################################################################
	Value::Value( const Value& copy ) {
		constructor();

		if ( copy.isSet() ) {
			switch ( copy.getType() ) {
			case T_BOOL:
				setValue( copy.getValueAsBool() );
				break;
			case T_COLOR:
				setValue( copy.getValueAsColor() );
				break;
			case T_ENUM:
				setValue( copy.getValueAsEnum() );
				break;
			case T_FLOAT:
				setValue( copy.getValueAsFloat() );
				break;
			case T_FRECT:
				setValue( copy.getValueAsFRect() );
				break;
			case T_FVECTOR2:
				setValue( copy.getValueAsFVector2() );
				break;
			case T_INTEGER:
				setValue( copy.getValueAsInt() );
				break;
			case T_IRECT:
				setValue( copy.getValueAsIRect() );
				break;
			case T_IVECTOR2:
				setValue( copy.getValueAsIVector2() );
				break;
			case T_STRING:
				setValue( copy.getValueAsString() );
				break;
			}
		}
	}
	//#####################################################################
	Value::Value( const std::string& value ) {
		constructor();
		setValue( value );
	}
	//#####################################################################
	Value::Value( const char* value ) {
		constructor();
		setValue( value );
	}
	//#####################################################################
	Value::Value( bool value ) {
		constructor();
		setValue( value );
	}
	//#####################################################################
	Value::Value( float value ) {
		constructor();
		setValue( value );
	}
	//#####################################################################
	Value::Value( const FVector2& value ) {
		constructor();
		setValue( value );
	}
	//#####################################################################
	Value::Value( const FRect& value ) {
		constructor();
		setValue( value );
	}
	//#####################################################################
	Value::Value( int value ) {
		constructor();
		setValue( value );
	}
	//#####################################################################
	Value::Value( const IVector2& value ) {
		constructor();
		setValue( value );
	}
	//#####################################################################
	Value::Value( const IRect& value ) {
		constructor();
		setValue( value );
	}
	//#####################################################################
	Value::Value( const Enum& value ) {
		constructor();
		setValue( value );
	}
	//#####################################################################
	Value::Value( const Color& value ) {
		constructor();
		setValue( value );
	}
	//#####################################################################
	Value::Value() {
		constructor();
	}
	//#####################################################################
	Value::~Value() {
		clearValue();
	}
	//#####################################################################
	/*! Only valid if isSet() == true */
	Value::ValueType Value::getType() const {
		return mType;
	}
	//#####################################################################
	void Value::setValue( const std::string& std_string ) {
		clearValue();
		mType = T_STRING;
		mString = new std::string;
		*mString = std_string;
		mHasValue = true;
	}
	//#####################################################################
	std::string Value::getValueAsString() const {
		if ( !isSet() || getType() != T_STRING )
			OG_THROW( Exception::OP_FAILED, "Cannot convert stored value to requested type", "Value::getValueAsString" );
		return *mString;
	}
	//#####################################################################
	void Value::setValue( const char* cString ) {
		std::string str = cString;
		setValue( str );
	}
	//#####################################################################
	/*! You must copy this if you wish to keep it, the buffer is temporary */
	const char* Value::getValueAsCString() const {
		std::string str = getValueAsString();
		return str.c_str();
	}
	//#####################################################################
	void Value::setValue( bool boolean ) {
		clearValue();
		mType = T_BOOL;
		mBool = new bool;
		*mBool = boolean;
		mHasValue = true;
	}
	//#####################################################################
	bool Value::getValueAsBool() const {
		if ( !isSet() || getType() != T_BOOL )
			OG_THROW( Exception::OP_FAILED, "Cannot convert stored value to requested type", "Value::getValueAsBool" );
		return *mBool;
	}
	//#####################################################################
	void Value::setValue( float floatingPoint ) {
		clearValue();
		mType = T_FLOAT;
		mFloat = new float;
		*mFloat = floatingPoint;
		mHasValue = true;
	}
	//#####################################################################
	float Value::getValueAsFloat() const {
		if ( !isSet() || getType() != T_FLOAT )
			OG_THROW( Exception::OP_FAILED, "Cannot convert stored value to requested type", "Value::getValueAsFloat" );
		return *mFloat;
	}
	//#####################################################################
	void Value::setValue( const FVector2& floatVector ) {
		clearValue();
		mType = T_FVECTOR2;
		mFVector2 = new FVector2();
		*mFVector2 = floatVector;
		mHasValue = true;
	}
	//#####################################################################
	FVector2 Value::getValueAsFVector2() const {
		if ( !isSet() || getType() != T_FVECTOR2 )
			OG_THROW( Exception::OP_FAILED, "Cannot convert stored value to requested type", "Value::getValueAsFVector2" );
		return *mFVector2;
	}
	//#####################################################################
	void Value::setValue( const FRect& floatRect ) {
		clearValue();
		mType = T_FRECT;
		mFRect = new FRect();
		*mFRect = floatRect;
		mHasValue = true;
	}
	//#####################################################################
	FRect Value::getValueAsFRect() const {
		if ( !isSet() || getType() != T_FRECT )
			OG_THROW( Exception::OP_FAILED, "Cannot convert stored value to requested type", "Value::getValueAsFRect" );
		return *mFRect;
	}
	//#####################################################################
	void Value::setValue( int integer ) {
		clearValue();
		mType = T_INTEGER;
		mInt = new int;
		*mInt = integer;
		mHasValue = true;
	}
	//#####################################################################
	int Value::getValueAsInt() const {
		if ( !isSet() || getType() != T_INTEGER )
			OG_THROW( Exception::OP_FAILED, "Cannot convert stored value to requested type", "Value::getValueAsInt" );
		return *mInt;
	}
	//#####################################################################
	void Value::setValue( const IVector2& intVector ) {
		clearValue();
		mType = T_IVECTOR2;
		mIVector2 = new IVector2();
		*mIVector2 = intVector;
		mHasValue = true;
	}
	//#####################################################################
	IVector2 Value::getValueAsIVector2() const {
		if ( !isSet() || getType() != T_IVECTOR2 )
			OG_THROW( Exception::OP_FAILED, "Cannot convert stored value to requested type", "Value::getValueAsIVector2" );
		return *mIVector2;
	}
	//#####################################################################
	void Value::setValue( const IRect& intRect ) {
		clearValue();
		mType = T_IRECT;
		mIRect = new IRect();
		*mIRect = intRect;
		mHasValue = true;
	}
	//#####################################################################
	IRect Value::getValueAsIRect() const {
		if ( !isSet() || getType() != T_IRECT )
			OG_THROW( Exception::OP_FAILED, "Cannot convert stored value to requested type", "Value::getValueAsIRect" );
		return *mIRect;
	}
	//#####################################################################
	void Value::setValue( const Enum& string_enumeration ) {
		clearValue();
		mType = T_ENUM;
		mEnum = new Enum();
		*mEnum = string_enumeration;
		mHasValue = true;
	}
	//#####################################################################
	Enum Value::getValueAsEnum() const {
		if ( !isSet() || getType() != T_ENUM )
			OG_THROW( Exception::OP_FAILED, "Cannot convert stored value to requested type", "Value::getValueAsEnum" );
		return *mEnum;
	}
	//#####################################################################
	void Value::setValue( const Color& color ) {
		clearValue();
		mType = T_COLOR;
		mColor = new Color();
		*mColor = color;
		mHasValue = true;
	}
	//#####################################################################
	Color Value::getValueAsColor() const {
		if ( !isSet() || getType() != T_COLOR )
			OG_THROW( Exception::OP_FAILED, "Cannot convert stored value to requested type", "Value::getValueAsColor" );
		return *mColor;
	}
	//#####################################################################
	void Value::clearValue() {
		if ( isSet() ) {
			mHasValue = false;
			switch ( mType ) {
			case T_BOOL:
				if ( mBool ) delete mBool;
				break;
			case T_COLOR:
				if ( mColor ) delete mColor;
				break;
			case T_ENUM:
				if ( mEnum ) delete mEnum;
				break;
			case T_FLOAT:
				if ( mFloat ) delete mFloat;
				break;
			case T_FRECT:
				if ( mFRect ) delete mFRect;
				break;
			case T_FVECTOR2:
				if ( mFVector2 ) delete mFVector2;
				break;
			case T_INTEGER:
				if ( mInt ) delete mInt;
				break;
			case T_IRECT:
				if ( mIRect ) delete mIRect;
				break;
			case T_IVECTOR2:
				if ( mIVector2 ) delete mIVector2;
				break;
			case T_STRING:
				if ( mString ) delete mString;
				break;
			default:
				if ( mRaw ) delete mRaw;
			}
			mRaw = 0;
		}
	}
	//#####################################################################
	bool Value::isSet() const {
		return mHasValue;
	}
	//#####################################################################
	bool Value::operator==( const Value& right ) const {
		if ( mHasValue != right.mHasValue )
			return false; //false for comparisons of set and unset Values
		if ( mHasValue == false )
			return true; //true if we're both unset
		if ( mType != right.mType )
			return false; //false if we're both set but stored types differ

		switch ( mType ) {
		case T_BOOL:
			return right.getValueAsBool() == ( *mBool );
			break;
		case T_COLOR:
			return right.getValueAsColor() == ( *mColor );
			break;
		case T_ENUM:
			return right.getValueAsEnum() == ( *mEnum );
			break;
		case T_FLOAT:
			return right.getValueAsFloat() == ( *mFloat );
			break;
		case T_FRECT:
			return right.getValueAsFRect() == ( *mFRect );
			break;
		case T_FVECTOR2:
			return right.getValueAsFVector2() == ( *mFVector2 );
			break;
		case T_INTEGER:
			return right.getValueAsInt() == ( *mInt );
			break;
		case T_IRECT:
			return right.getValueAsIRect() == ( *mIRect );
			break;
		case T_IVECTOR2:
			return right.getValueAsIVector2() == ( *mIVector2 );
			break;
		case T_STRING:
			return right.getValueAsString() == ( *mString );
			break;
		default:
			return false; //should never happen
		}
	}
	//#####################################################################
	bool Value::operator!=( const Value& right ) const {
		return !operator==( right );
	}
	//#####################################################################




	//#####################################################################
	//#####################################################################
	//#####################################################################
	void ValueList::push_front( const Value& value ) {
		mValueDeQue.push_front( value );
	}
	//#####################################################################
	void ValueList::push_back( const Value& value ) {
		mValueDeQue.push_back( value );
	}
	//#####################################################################
	/*! Throws an Exception if the Value stack is empty when called. */
	Value ValueList::pop_front() {
		if ( size() <= 0 )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "cannot pop an empty stack", "ValueList::pop_front" );

		//deque doens't return values on pops
		ValueDeQue::const_iterator iter = mValueDeQue.begin();
		Value retval = *iter;
		removeMappedValue( &( *iter ) );
		mValueDeQue.pop_front();
		return retval;
	}
	//#####################################################################
	/*! Throws an Exception if the Value stack is empty when called. */
	Value ValueList::pop_back() {
		if ( size() <= 0 )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "cannot pop an empty stack", "ValueList::pop_back" );

		//deque doens't return values on pops
		ValueDeQue::const_reverse_iterator iter = mValueDeQue.rbegin();
		Value retval = *iter;
		removeMappedValue( &( *iter ) );
		mValueDeQue.pop_back();
		return retval;
	}
	//#####################################################################
	size_t ValueList::size() const {
		return  mValueDeQue.size();
	}
	//#####################################################################
	/*! Setting the same \c name multiple times will redefine the \c name to link
		to the new \c value each time. The old \c value will remain on the stack
		in the position it was originally added, only it will be unnamed.
	*/
	void ValueList::set( const Value& value, const std::string& name ) {
		push_back( value );
		ValueDeQue::reverse_iterator iter = mValueDeQue.rbegin();
		Value* valuePtr = &( *iter );
		mValueMap[name] = valuePtr;
	}
	//#####################################################################
	/*! If a Value by the requested \c name cannot be found, an Exception will be thrown. */
	const Value& ValueList::get( const std::string& name ) const {
			ValueMap::const_iterator iter = mValueMap.find( name );
			if ( iter == mValueMap.end() )
				OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Named value not found", "ValueList::get" );
			const Value* valuePtr = iter->second;
			return *( valuePtr );
		}
	//#####################################################################
	/*! Throws an Exception if the given \c index is out of range. */
	const Value& ValueList::get ( unsigned int index ) const {
			//try to catch bad index attempts
			if ( mValueDeQue.size() <= index )
				OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "index is out of range", "ValueList::get" );
			//then just return whatever is appropriate
			return mValueDeQue[index];
		}
	//#####################################################################
	void ValueList::removeMappedValue( const Value* valuePtr ) {
		for ( ValueMap::iterator iter = mValueMap.begin();
				iter != mValueMap.end(); iter++ ) {
			if ( iter->second == valuePtr ) {
				//need a copy of the iterator otherwise we'll chop ourself off the map
				mValueMap.erase( iter );
				removeMappedValue( valuePtr );
				return;
			}
		}
	}
	//#####################################################################

}//namespace OpenGUI{