// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_Value.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_StrConv.h"
#include "OpenGUI_XML.h"
#include "OpenGUI_Font.h"
#include "OpenGUI_Imagery.h"
#include "OpenGUI_Face.h"
#include "OpenGUI_ImageryManager.h"
#include "OpenGUI_Cursor.h"
#include "OpenGUI_CursorManager.h"

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
			case T_FONT:
				setValue( copy.getValueAsFont() );
				break;
			case T_TEXTALIGNMENT:
				setValue( copy.getValueAsTextAlignment() );
				break;
			case T_IMAGERY:
				setValue( copy.getValueAsImageryPtr() );
				break;
			case T_FACE:
				setValue( copy.getValueAsFacePtr() );
				break;
			case T_CURSOR:
				setValue( copy.getValueAsCursorPtr() );
				break;
			default:
				OG_THROW( Exception::ERR_NOT_IMPLEMENTED, "Unknown type for source Value", __FUNCTION__ );
			}
		}
		setName( copy.getName() );
	}
	//#####################################################################
	Value::Value( const String& value, const String& Name ) {
		constructor();
		setValue( value );
		setName( Name );
	}
	//#####################################################################
	Value::Value( const char* value, const String& Name ) {
		constructor();
		setValue( value );
		setName( Name );
	}
	//#####################################################################
	Value::Value( bool value, const String& Name ) {
		constructor();
		setValue( value );
		setName( Name );
	}
	//#####################################################################
	Value::Value( float value, const String& Name ) {
		constructor();
		setValue( value );
		setName( Name );
	}
	//#####################################################################
	Value::Value( const FVector2& value, const String& Name ) {
		constructor();
		setValue( value );
		setName( Name );
	}
	//#####################################################################
	Value::Value( const FRect& value, const String& Name ) {
		constructor();
		setValue( value );
		setName( Name );
	}
	//#####################################################################
	Value::Value( int value, const String& Name ) {
		constructor();
		setValue( value );
		setName( Name );
	}
	//#####################################################################
	Value::Value( const IVector2& value, const String& Name ) {
		constructor();
		setValue( value );
		setName( Name );
	}
	//#####################################################################
	Value::Value( const IRect& value, const String& Name ) {
		constructor();
		setValue( value );
		setName( Name );
	}
	//#####################################################################
	Value::Value( const Color& value, const String& Name ) {
		constructor();
		setValue( value );
		setName( Name );
	}
	//#####################################################################
	Value::Value( const Font& value, const String& Name ) {
		constructor();
		setValue( value );
		setName( Name );
	}
	//#####################################################################
	Value::Value( const TextAlignment& value, const String& Name ) {
		constructor();
		setValue( value );
		setName( Name );
	}
	//#####################################################################
	Value::Value( const ImageryPtr& value, const String& Name ) {
		constructor();
		setValue( value );
		setName( Name );
	}
	//#####################################################################
	Value::Value( const FacePtr& value, const String& Name ) {
		constructor();
		setValue( value );
		setName( Name );
	}
	//#####################################################################
	Value::Value( const CursorPtr& value, const String& Name ) {
		constructor();
		setValue( value );
		setName( Name );
	}
	//#####################################################################
	Value::Value( const String& Name ) {
		constructor();
		setName( Name );
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
	void Value::setValue( const String& str ) {
		clearValue();
		mType = T_STRING;
		mString = new String;
		*mString = str;
		mHasValue = true;
	}
	//#####################################################################
	String Value::getValueAsString() const {
		if ( !isSet() || getType() != T_STRING )
			OG_THROW( Exception::OP_FAILED, "Stored value is not a string", __FUNCTION__ );
		return *mString;
	}
	//#####################################################################
	void Value::setValue( const char* cString ) {
		String str = cString;
		setValue( str );
	}
	//#####################################################################
	/*! You must copy this if you wish to keep it, the buffer is temporary */
	const char* Value::getValueAsCString() const {
		String str = getValueAsString();
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
			OG_THROW( Exception::OP_FAILED, "Stored value is not a bool", __FUNCTION__ );
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
			OG_THROW( Exception::OP_FAILED, "Stored value is not a float", __FUNCTION__ );
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
			OG_THROW( Exception::OP_FAILED, "Stored value is not a FVector2", __FUNCTION__ );
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
			OG_THROW( Exception::OP_FAILED, "Stored value is not a FRect", __FUNCTION__ );
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
			OG_THROW( Exception::OP_FAILED, "Stored value is not an integer", __FUNCTION__ );
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
			OG_THROW( Exception::OP_FAILED, "Stored value is not an IVector2", __FUNCTION__ );
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
			OG_THROW( Exception::OP_FAILED, "Stored value is not an IRect", __FUNCTION__ );
		return *mIRect;
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
			OG_THROW( Exception::OP_FAILED, "Stored value is not a Color", __FUNCTION__ );
		return *mColor;
	}
	//#####################################################################
	void Value::setValueAsFont( const String& fontStr ) {
		Font value;
		StrConv::toFont( fontStr, value );
		setValue( value );
	}
	//#####################################################################
	void Value::setValue( const Font& font ) {
		clearValue();
		mType = T_FONT;
		mFont = new Font();
		*mFont = font;
		mHasValue = true;
	}
	//#####################################################################
	Font Value::getValueAsFont() const {
		if ( !isSet() || getType() != T_FONT )
			OG_THROW( Exception::OP_FAILED, "Stored value is not a Font", __FUNCTION__ );
		return *mFont;
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
			case T_FONT:
				if ( mFont ) delete mFont;
				break;
			case T_TEXTALIGNMENT:
				if ( mTextAlignment ) delete mTextAlignment;
				break;
			case T_IMAGERY:
				if ( mImageryPtr ) delete mImageryPtr;
				break;
			case T_FACE:
				if ( mFacePtr ) delete mFacePtr;
				break;
			case T_CURSOR:
				if ( mCursorPtr ) delete mCursorPtr;
				break;
			default:
				OG_THROW( Exception::ERR_NOT_IMPLEMENTED, "Unknown type for held Value", __FUNCTION__ );
			}
			mRaw = 0;
		}
	}
	//#####################################################################
	bool Value::isSet() const {
		return mHasValue;
	}
	//#####################################################################
	/*! If you want to create a complete clone, including the name, use the copy constructor. */
	Value& Value::operator=( const Value& right ) {
		clearValue();
		if ( right.isSet() ) {
			switch ( right.getType() ) {
			case T_BOOL:
				setValue( right.getValueAsBool() );
				break;
			case T_COLOR:
				setValue( right.getValueAsColor() );
				break;
			case T_FLOAT:
				setValue( right.getValueAsFloat() );
				break;
			case T_FRECT:
				setValue( right.getValueAsFRect() );
				break;
			case T_FVECTOR2:
				setValue( right.getValueAsFVector2() );
				break;
			case T_INTEGER:
				setValue( right.getValueAsInt() );
				break;
			case T_IRECT:
				setValue( right.getValueAsIRect() );
				break;
			case T_IVECTOR2:
				setValue( right.getValueAsIVector2() );
				break;
			case T_STRING:
				setValue( right.getValueAsString() );
				break;
			case T_FONT:
				setValue( right.getValueAsFont() );
				break;
			case T_TEXTALIGNMENT:
				setValue( right.getValueAsTextAlignment() );
				break;
			case T_IMAGERY:
				setValue( right.getValueAsImageryPtr() );
				break;
			case T_FACE:
				setValue( right.getValueAsFacePtr() );
				break;
			case T_CURSOR:
				setValue( right.getValueAsCursorPtr() );
				break;
			default:
				OG_THROW( Exception::ERR_NOT_IMPLEMENTED, "Unknown type for source Value", __FUNCTION__ );
			}
		}
		return *this;
	}
	//#####################################################################
	/*! Values are only equal under fairly strict conditions.
		- They have the same "set" state (either set or not set)
		- Their stored values are of the same type
		- Their stored values are equal according to the == C++ operator as defined for that type
		\note The \c Name of the Values is \b not compared, as it is considered to be metadata
		\exception Exception::ERR_NOT_IMPLEMENTED
		If this is received it is because you tried to compare two values of a type that
		\b should have been implemented but wasn't. This would make it a bug, so please report it!
	*/
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
		case T_FONT:
			return right.getValueAsFont() == ( *mFont );
			break;
		case T_TEXTALIGNMENT:
			return right.getValueAsTextAlignment() == ( *mTextAlignment );
			break;
		case T_IMAGERY:
			return right.getValueAsImageryPtr() == ( *mImageryPtr );
			break;
		case T_FACE:
			return right.getValueAsFacePtr() == ( *mFacePtr );
			break;
		case T_CURSOR:
			return right.getValueAsCursorPtr() == ( *mCursorPtr );
			break;
		default:
			OG_THROW( Exception::ERR_NOT_IMPLEMENTED, "Comparison of type that is not implemented but should be!", __FUNCTION__ );
			return false; //should never happen
		}
	}
	//#####################################################################
	/*! \code return !operator==( right ); \endcode \see operator==()*/
	bool Value::operator!=( const Value& right ) const {
		return !operator==( right );
	}
	//#####################################################################
	void Value::setValueAsInt( const String& intStr ) {
		int value;
		StrConv::toInt( intStr, value );
		setValue( value );
	}
	//#####################################################################
	void Value::setValueAsFloat( const String& floatStr ) {
		float value;
		StrConv::toFloat( floatStr, value );
		setValue( value );
	}
	//#####################################################################
	void Value::setValueAsFVector2( const String& fv2Str ) {
		FVector2 value;
		StrConv::toFVector2( fv2Str, value );
		setValue( value );
	}
	//#####################################################################
	void Value::setValueAsFRect( const String& frectStr ) {
		FRect value;
		StrConv::toFRect( frectStr, value );
		setValue( value );
	}
	//#####################################################################
	void Value::setValueAsIVector2( const String& iv2Str ) {
		IVector2 value;
		StrConv::toIVector2( iv2Str, value );
		setValue( value );
	}
	//#####################################################################
	void Value::setValueAsIRect( const String& irectStr ) {
		IRect value;
		StrConv::toIRect( irectStr, value );
		setValue( value );
	}
	//#####################################################################
	void Value::setValueAsColor( const String& colorStr ) {
		Color value;
		StrConv::toColor( colorStr, value );
		setValue( value );
	}
	//#####################################################################
	/*! Yes, this is redundant. */
	void Value::setValueAsString( const String& stringStr ) {
		setValue( stringStr );
	}
	//#####################################################################
	void Value::setValueAsBool( const String& boolStr ) {
		bool value;
		StrConv::toBool( boolStr, value );
		setValue( value );
	}
	//#####################################################################
	bool _isNumber( char c ) {
		return c == '1' || c == '2' || c == '3' || c == '4' || c == '5' ||
			   c == '6' || c == '7' || c == '8' || c == '9' || c == '0';
	}
	//#####################################################################
	String Value::toStr() const {
		String ret;
		switch ( mType ) {
		case T_BOOL:
			StrConv::fromBool( getValueAsBool(), ret );
			return ret;
			break;
		case T_COLOR:
			StrConv::fromColor( getValueAsColor(), ret );
			return ret;
			break;
		case T_FLOAT:
			StrConv::fromFloat( getValueAsFloat(), ret );
			return ret;
			break;
		case T_FRECT:
			StrConv::fromFRect( getValueAsFRect(), ret );
			return ret;
			break;
		case T_FVECTOR2:
			StrConv::fromFVector2( getValueAsFVector2(), ret );
			return ret;
			break;
		case T_INTEGER:
			StrConv::fromInt( getValueAsInt(), ret );
			return ret;
			break;
		case T_IRECT:
			StrConv::fromIRect( getValueAsIRect(), ret );
			return ret;
			break;
		case T_IVECTOR2:
			StrConv::fromIVector2( getValueAsIVector2(), ret );
			return ret;
			break;
		case T_STRING:
			return getValueAsString();
			break;
		case T_FONT:
			StrConv::fromFont( getValueAsFont(), ret );
			return ret;
			break;
		case T_TEXTALIGNMENT:
			StrConv::fromTextAlignment( getValueAsTextAlignment(), ret );
			return ret;
			break;
		case T_IMAGERY:
			ret = getValueAsImageryPtr()->getFQN();
			return ret;
			break;
		case T_FACE:
			ret = getValueAsFacePtr()->getName();
			return ret;
			break;
		case T_CURSOR:
			ret = getValueAsCursorPtr()->getName();
			return ret;
			break;
		default:
			OG_THROW( Exception::ERR_NOT_IMPLEMENTED, "Unknown type, cannot convert to string", __FUNCTION__ );
		}
	}
	//#####################################################################
	/*! This works by storing the necessary information in attributes of the given tag.
	If any of the attributes already exist, their contents are silently overwritten.
	\n The used attributes are:
	- ValueType - identifies the type of data held within ValueData
	- ValueName - the Name of this Value
	- ValueData - the data of this Value in string format
	*/
	void Value::SaveToXMLNode( XMLNode& node ) const {
		node.setAttribute( "ValueType", _TypeToString( mType ) );
		node.setAttribute( "ValueName", mName );
		node.setAttribute( "ValueData", toStr() );
	}
	//#####################################################################
	/*! This expects the given \c node to contain all necessary data as
	XMLNode attributes. Only the \c ValueName attribute may be missing
	- \c ValueName - defines the string based name for the Value (given to setName())
	- \c ValueData - string representation of the data to store
	- \c ValueType - defines the type of data held in \c ValueData. Valid values include:
	  - INTEGER
	  - FLOAT
	  - BOOL
	  - FVECTOR2
	  - FRECT
	  - IVECTOR2
	  - IRECT
	  - COLOR
	  - STRING
	  - FONT
	  - TEXTALIGNMENT
	  - IMAGERY
	  - FACE
	  - CURSOR

	  \see \ref StringFormats for further information on the text formatting syntax of %OpenGUI objects.
	*/
	void Value::LoadFromXMLNode( const XMLNode& node ) {
		String typestr = node.getAttribute( "ValueType" );
		String valuestr = node.getAttribute( "ValueData" );

		if ( node.hasAttribute( "ValueName" ) ) {
			String namestr = node.getAttribute( "ValueName" );
			setName( namestr );
		} else {
			setName( "" );
		}

		ValueType type = _TypeFromString( typestr );
		switch ( type ) {
		case T_BOOL:
			setValueAsBool( valuestr );
			break;
		case T_COLOR:
			setValueAsColor( valuestr );
			break;
		case T_FLOAT:
			setValueAsFloat( valuestr );
			break;
		case T_FRECT:
			setValueAsFRect( valuestr );
			break;
		case T_FVECTOR2:
			setValueAsFVector2( valuestr );
			break;
		case T_INTEGER:
			setValueAsInt( valuestr );
			break;
		case T_IRECT:
			setValueAsIRect( valuestr );
			break;
		case T_IVECTOR2:
			setValueAsIVector2( valuestr );
			break;
		case T_STRING:
			setValueAsString( valuestr );
			break;
		case T_FONT:
			setValueAsFont( valuestr );
			break;
		case T_TEXTALIGNMENT:
			setValueAsTextAlignment( valuestr );
			break;
		case T_IMAGERY:
			setValueAsImageryPtr( valuestr );
			break;
		case T_FACE:
			setValueAsFacePtr( valuestr );
			break;
		case T_CURSOR:
			setValueAsCursorPtr( valuestr );
			break;
		default:
			OG_THROW( Exception::ERR_NOT_IMPLEMENTED, "Unhandled type", __FUNCTION__ );
		}
	}
	//#####################################################################
	String Value::_TypeToString( ValueType type ) {
		switch ( type ) {
		case T_BOOL:
			return "BOOL";
			break;
		case T_COLOR:
			return "COLOR";
			break;
		case T_FLOAT:
			return "FLOAT";
			break;
		case T_FRECT:
			return "FRECT";
			break;
		case T_FVECTOR2:
			return "FVECTOR2";
			break;
		case T_INTEGER:
			return "INTEGER";
			break;
		case T_IRECT:
			return "IRECT";
			break;
		case T_IVECTOR2:
			return "IVECTOR2";
			break;
		case T_STRING:
			return "STRING";
			break;
		case T_FONT:
			return "FONT";
			break;
		case T_TEXTALIGNMENT:
			return "TEXTALIGNMENT";
			break;
		case T_IMAGERY:
			return "IMAGERY";
			break;
		case T_FACE:
			return "FACE";
			break;
		case T_CURSOR:
			return "CURSOR";
			break;
		default:
			OG_THROW( Exception::ERR_NOT_IMPLEMENTED, "Unknown type, cannot convert to string", __FUNCTION__ );
		}
	}
	//#####################################################################
	Value::ValueType Value::_TypeFromString( const String& type ) {
		if ( type == "STRING" )
			return T_STRING;

		if ( type == "FLOAT" )
			return T_FLOAT;

		if ( type == "INTEGER" )
			return T_INTEGER;

		if ( type == "FVECTOR2" )
			return T_FVECTOR2;
		if ( type == "FRECT" )
			return T_FRECT;
		if ( type == "IVECTOR2" )
			return T_IVECTOR2;
		if ( type == "IRECT" )
			return T_IRECT;

		if ( type == "BOOL" )
			return T_BOOL;

		if ( type == "COLOR" )
			return T_COLOR;

		if ( type == "FONT" )
			return T_FONT;

		if ( type == "TEXTALIGNMENT" )
			return T_TEXTALIGNMENT;

		if ( type == "IMAGERY" )
			return T_IMAGERY;
		if ( type == "FACE" )
			return T_FACE;

		if ( type == "CURSOR" )
			return T_CURSOR;

		OG_THROW( Exception::ERR_NOT_IMPLEMENTED, "Given string does not match a known type: " + type, __FUNCTION__ );
	}
	//#####################################################################
	void Value::setValue( const TextAlignment& textAlignment ) {
		clearValue();
		mType = T_TEXTALIGNMENT;
		mTextAlignment = new TextAlignment( textAlignment );
		mHasValue = true;
	}
	//#####################################################################
	TextAlignment Value::getValueAsTextAlignment() const {
		if ( !isSet() || getType() != T_TEXTALIGNMENT )
			OG_THROW( Exception::OP_FAILED, "Stored value is not a TextAlignment", __FUNCTION__ );
		return *mTextAlignment;
	}
	//#####################################################################
	void Value::setValueAsTextAlignment( const String& textAlignmentStr ) {
		TextAlignment value;
		StrConv::toTextAlignment( textAlignmentStr, value );
		setValue( value );
	}
	//#####################################################################
	void Value::setValue( const ImageryPtr& imageryPtr ) {
		clearValue();
		mType = T_IMAGERY;
		mImageryPtr = new ImageryPtr;
		*mImageryPtr = imageryPtr;
		mHasValue = true;
	}
	//#####################################################################
	ImageryPtr Value::getValueAsImageryPtr() const {
		if ( !isSet() || getType() != T_IMAGERY )
			OG_THROW( Exception::OP_FAILED, "Stored value is not an ImageryPtr", __FUNCTION__ );
		return *mImageryPtr;
	}
	//#####################################################################
	void Value::setValueAsImageryPtr( const String& imageryName ) {
		ImageryPtr value;
		value = ImageryManager::getSingleton().getImagery( imageryName );
		setValue( value );
	}
	//#####################################################################
	void Value::setValue( const FacePtr& facePtr ) {
		clearValue();
		mType = T_FACE;
		mFacePtr = new FacePtr;
		*mFacePtr = facePtr;
		mHasValue = true;
	}
	//#####################################################################
	FacePtr Value::getValueAsFacePtr() const {
		if ( !isSet() || getType() != T_FACE )
			OG_THROW( Exception::OP_FAILED, "Stored value is not a FacePtr", __FUNCTION__ );
		return *mFacePtr;
	}
	//#####################################################################
	void Value::setValueAsFacePtr( const String& faceName ) {
		FacePtr value;
		value = ImageryManager::getSingleton().getFace( faceName );
		setValue( value );
	}
	//#####################################################################
	void Value::setValue( const CursorPtr& cursorPtr ) {
		clearValue();
		mType = T_CURSOR;
		mCursorPtr = new CursorPtr;
		*mCursorPtr = cursorPtr;
		mHasValue = true;
	}
	//#####################################################################
	CursorPtr Value::getValueAsCursorPtr() const {
		if ( !isSet() || getType() != T_CURSOR )
			OG_THROW( Exception::OP_FAILED, "Stored value is not a CursorPtr", __FUNCTION__ );
		return *mCursorPtr;
	}
	//#####################################################################
	void Value::setValueAsCursorPtr( const String& cursorName ) {
		CursorPtr value;
		value = CursorManager::getSingleton().CreateDefinedCursor( cursorName );
		setValue( value );
	}
	//#####################################################################

//##########################################################################################################################################
//################  Can you tell I like fencing?  ##########################################################################################
//##########################################################################################################################################


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

		//deque doesn't return values on pops
		ValueDeQue::const_iterator iter = mValueDeQue.begin();
		Value retval = *iter;
		mValueDeQue.pop_front();
		return retval;
	}
	//#####################################################################
	/*! Throws an Exception if the Value stack is empty when called. */
	Value ValueList::pop_back() {
		if ( size() <= 0 )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "cannot pop an empty stack", "ValueList::pop_back" );

		//deque doesn't return values on pops
		ValueDeQue::const_reverse_iterator iter = mValueDeQue.rbegin();
		Value retval = *iter;
		mValueDeQue.pop_back();
		return retval;
	}
	//#####################################################################
	size_t ValueList::size() const {
		return  mValueDeQue.size();
	}
	//#####################################################################
	/*! If a Value by the requested \c name cannot be found, an Exception will be thrown. */
	const Value& ValueList::get( const String& name ) const {
			ValueDeQue::const_iterator iter = mValueDeQue.begin();
			while ( iter != mValueDeQue.end() ) {
				const Value& val = ( *iter );
				if ( val.getName() == name )
					return val;
				iter++;
			}
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Named value not found", "ValueList::get" );
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
}//namespace OpenGUI{