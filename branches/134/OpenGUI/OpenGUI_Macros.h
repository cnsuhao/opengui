// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef __H_OPENGUI_MACROS__
#define __H_OPENGUI_MACROS__

/*! \addtogroup Macros
	%OpenGUI provides a few macros to make certain common operations quicker to implement.
	Their usage is not required, and they are not defined  by default. In order to use
	these macros, you will need to specifically include them by including OpenGUI_Macros.h.
@{
*/


/*! \file OpenGUI_Macros.h
	This file defines the helper macros. You can include this file wherever it is needed.
	The macros that it defines can be undefined by including OpenGUI_NoMacros.h when you
	no longer need/want them.
*/

//! Helper macro for quick creation of generic properties for Object derived classes.
/*! This is the final stage helper macro. It requires the most arguments and is probably
not what you want to actually use. There are several other helper macros that are more specific
that will make defining generic properties even easier.
\param CLASS_NAME This is used as part of the class name, but will be used verbatim as the resulting object name.
\param PROPERTY_NAME A string literal that will be used as the name of the property
\param PROPERTY_TYPE A ValueType that is used as the property type
\param TARGET_OBJECT_CLASS The name of the Object class that contains the GETTER and SETTER methods
\param GETTER The name of the TARGET_OBJECT_CLASS method that is used to get the current value of the property
\param SETTER The name of the TARGET_OBJECT_CLASS method that is used to set the value of the property
\param VALUE_GET_FUNC The Value method to use to retrieve the Value for sending to the SETTER
*/
#define SimpleProperty( CLASS_NAME, PROPERTY_NAME, PROPERTY_TYPE, TARGET_OBJECT_CLASS, GETTER, SETTER, VALUE_GET_FUNC ) \
class CLASS_NAME##_OPENGUI_SPA_CLASS : public ObjectProperty { \
public: \
	virtual const char* getAccessorName() { \
		return PROPERTY_NAME; \
	} \
	virtual void get( Object& objectRef, Value& valueOut ) { \
		try { \
			TARGET_OBJECT_CLASS& target = dynamic_cast<TARGET_OBJECT_CLASS&>( objectRef ); \
			valueOut.setValue( target.GETTER() ); \
		} catch ( std::bad_cast e ) { \
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ ); \
		} \
	} \
	virtual void set( Object& objectRef, Value& valueIn ) { \
		try { \
			TARGET_OBJECT_CLASS& target = dynamic_cast<TARGET_OBJECT_CLASS&>( objectRef ); \
			target.SETTER( valueIn.VALUE_GET_FUNC() ); \
		} catch ( std::bad_cast e ) { \
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ ); \
		} \
	} \
	virtual Value::ValueType getPropertyType() { \
		return PROPERTY_TYPE; \
	} \
} \
CLASS_NAME

//! Helper macro for quick creation of generic string properties for Object derived classes.
/*!
\param CLASS_NAME This is used as part of the class name, but will be used verbatim as the resulting object name.
\param PROPERTY_NAME A string literal that will be used as the name of the property
\param TARGET_OBJECT_CLASS The name of the Object class that contains the GETTER and SETTER methods
\param GETTER The name of the TARGET_OBJECT_CLASS method that is used to get the current value of the property
\param SETTER The name of the TARGET_OBJECT_CLASS method that is used to set the value of the property
*/
#define SimpleProperty_String(CLASS_NAME, PROPERTY_NAME, TARGET_OBJECT_CLASS, GETTER, SETTER) \
	SimpleProperty( CLASS_NAME, PROPERTY_NAME, Value::T_STRING, TARGET_OBJECT_CLASS, GETTER, SETTER, getValueAsString )

//! Helper macro for quick creation of generic boolean properties for Object derived classes.
/*!
\param CLASS_NAME This is used as part of the class name, but will be used verbatim as the resulting object name.
\param PROPERTY_NAME A string literal that will be used as the name of the property
\param TARGET_OBJECT_CLASS The name of the Object class that contains the GETTER and SETTER methods
\param GETTER The name of the TARGET_OBJECT_CLASS method that is used to get the current value of the property
\param SETTER The name of the TARGET_OBJECT_CLASS method that is used to set the value of the property
*/
#define SimpleProperty_Bool(CLASS_NAME, PROPERTY_NAME, TARGET_OBJECT_CLASS, GETTER, SETTER) \
	SimpleProperty( CLASS_NAME, PROPERTY_NAME, Value::T_BOOL, TARGET_OBJECT_CLASS, GETTER, SETTER, getValueAsBool )

//! Helper macro for quick creation of generic float properties for Object derived classes.
/*!
\param CLASS_NAME This is used as part of the class name, but will be used verbatim as the resulting object name.
\param PROPERTY_NAME A string literal that will be used as the name of the property
\param TARGET_OBJECT_CLASS The name of the Object class that contains the GETTER and SETTER methods
\param GETTER The name of the TARGET_OBJECT_CLASS method that is used to get the current value of the property
\param SETTER The name of the TARGET_OBJECT_CLASS method that is used to set the value of the property
*/
#define SimpleProperty_Float(CLASS_NAME, PROPERTY_NAME, TARGET_OBJECT_CLASS, GETTER, SETTER) \
	SimpleProperty( CLASS_NAME, PROPERTY_NAME, Value::T_FLOAT, TARGET_OBJECT_CLASS, GETTER, SETTER, getValueAsFloat )

//! Helper macro for quick creation of generic FVector2 properties for Object derived classes.
/*!
\param CLASS_NAME This is used as part of the class name, but will be used verbatim as the resulting object name.
\param PROPERTY_NAME A string literal that will be used as the name of the property
\param TARGET_OBJECT_CLASS The name of the Object class that contains the GETTER and SETTER methods
\param GETTER The name of the TARGET_OBJECT_CLASS method that is used to get the current value of the property
\param SETTER The name of the TARGET_OBJECT_CLASS method that is used to set the value of the property
*/
#define SimpleProperty_FVector2(CLASS_NAME, PROPERTY_NAME, TARGET_OBJECT_CLASS, GETTER, SETTER) \
	SimpleProperty( CLASS_NAME, PROPERTY_NAME, Value::T_FVECTOR2, TARGET_OBJECT_CLASS, GETTER, SETTER, getValueAsFVector2 )

//! Helper macro for quick creation of generic FRect properties for Object derived classes.
/*!
\param CLASS_NAME This is used as part of the class name, but will be used verbatim as the resulting object name.
\param PROPERTY_NAME A string literal that will be used as the name of the property
\param TARGET_OBJECT_CLASS The name of the Object class that contains the GETTER and SETTER methods
\param GETTER The name of the TARGET_OBJECT_CLASS method that is used to get the current value of the property
\param SETTER The name of the TARGET_OBJECT_CLASS method that is used to set the value of the property
*/
#define SimpleProperty_FRect(CLASS_NAME, PROPERTY_NAME, TARGET_OBJECT_CLASS, GETTER, SETTER) \
	SimpleProperty( CLASS_NAME, PROPERTY_NAME, Value::T_FRECT, TARGET_OBJECT_CLASS, GETTER, SETTER, getValueAsFRect )

//! Helper macro for quick creation of generic integer properties for Object derived classes.
/*!
\param CLASS_NAME This is used as part of the class name, but will be used verbatim as the resulting object name.
\param PROPERTY_NAME A string literal that will be used as the name of the property
\param TARGET_OBJECT_CLASS The name of the Object class that contains the GETTER and SETTER methods
\param GETTER The name of the TARGET_OBJECT_CLASS method that is used to get the current value of the property
\param SETTER The name of the TARGET_OBJECT_CLASS method that is used to set the value of the property
*/
#define SimpleProperty_Integer(CLASS_NAME, PROPERTY_NAME, TARGET_OBJECT_CLASS, GETTER, SETTER) \
	SimpleProperty( CLASS_NAME, PROPERTY_NAME, Value::T_INTEGER, TARGET_OBJECT_CLASS, GETTER, SETTER, getValueAsInt )

//! Helper macro for quick creation of generic IVector2 properties for Object derived classes.
/*!
\param CLASS_NAME This is used as part of the class name, but will be used verbatim as the resulting object name.
\param PROPERTY_NAME A string literal that will be used as the name of the property
\param TARGET_OBJECT_CLASS The name of the Object class that contains the GETTER and SETTER methods
\param GETTER The name of the TARGET_OBJECT_CLASS method that is used to get the current value of the property
\param SETTER The name of the TARGET_OBJECT_CLASS method that is used to set the value of the property
*/
#define SimpleProperty_IVector2(CLASS_NAME, PROPERTY_NAME, TARGET_OBJECT_CLASS, GETTER, SETTER) \
	SimpleProperty( CLASS_NAME, PROPERTY_NAME, Value::T_IVECTOR2, TARGET_OBJECT_CLASS, GETTER, SETTER, getValueAsIVector2 )

//! Helper macro for quick creation of generic IRect properties for Object derived classes.
/*!
\param CLASS_NAME This is used as part of the class name, but will be used verbatim as the resulting object name.
\param PROPERTY_NAME A string literal that will be used as the name of the property
\param TARGET_OBJECT_CLASS The name of the Object class that contains the GETTER and SETTER methods
\param GETTER The name of the TARGET_OBJECT_CLASS method that is used to get the current value of the property
\param SETTER The name of the TARGET_OBJECT_CLASS method that is used to set the value of the property
*/
#define SimpleProperty_IRect(CLASS_NAME, PROPERTY_NAME, TARGET_OBJECT_CLASS, GETTER, SETTER) \
	SimpleProperty( CLASS_NAME, PROPERTY_NAME, Value::T_IRECT, TARGET_OBJECT_CLASS, GETTER, SETTER, getValueAsIRect )

//! Helper macro for quick creation of generic Color properties for Object derived classes.
/*!
\param CLASS_NAME This is used as part of the class name, but will be used verbatim as the resulting object name.
\param PROPERTY_NAME A string literal that will be used as the name of the property
\param TARGET_OBJECT_CLASS The name of the Object class that contains the GETTER and SETTER methods
\param GETTER The name of the TARGET_OBJECT_CLASS method that is used to get the current value of the property
\param SETTER The name of the TARGET_OBJECT_CLASS method that is used to set the value of the property
*/
#define SimpleProperty_Color(CLASS_NAME, PROPERTY_NAME, TARGET_OBJECT_CLASS, GETTER, SETTER) \
	SimpleProperty( CLASS_NAME, PROPERTY_NAME, Value::T_COLOR, TARGET_OBJECT_CLASS, GETTER, SETTER, getValueAsColor )

//! Helper macro for quick creation of generic Font properties for Object derived classes.
/*!
\param CLASS_NAME This is used as part of the class name, but will be used verbatim as the resulting object name.
\param PROPERTY_NAME A string literal that will be used as the name of the property
\param TARGET_OBJECT_CLASS The name of the Object class that contains the GETTER and SETTER methods
\param GETTER The name of the TARGET_OBJECT_CLASS method that is used to get the current value of the property
\param SETTER The name of the TARGET_OBJECT_CLASS method that is used to set the value of the property
*/
#define SimpleProperty_Font(CLASS_NAME, PROPERTY_NAME, TARGET_OBJECT_CLASS, GETTER, SETTER) \
	SimpleProperty( CLASS_NAME, PROPERTY_NAME, Value::T_FONT, TARGET_OBJECT_CLASS, GETTER, SETTER, getValueAsFont )

//! Helper macro for quick creation of generic TextAlignment properties for Object derived classes.
/*!
\param CLASS_NAME This is used as part of the class name, but will be used verbatim as the resulting object name.
\param PROPERTY_NAME A string literal that will be used as the name of the property
\param TARGET_OBJECT_CLASS The name of the Object class that contains the GETTER and SETTER methods
\param GETTER The name of the TARGET_OBJECT_CLASS method that is used to get the current value of the property
\param SETTER The name of the TARGET_OBJECT_CLASS method that is used to set the value of the property
*/
#define SimpleProperty_TextAlignment(CLASS_NAME, PROPERTY_NAME, TARGET_OBJECT_CLASS, GETTER, SETTER) \
	SimpleProperty( CLASS_NAME, PROPERTY_NAME, Value::T_TEXTALIGNMENT, TARGET_OBJECT_CLASS, GETTER, SETTER, getValueAsTextAlignment )

//! Helper macro for quick creation of generic Imagery properties for Object derived classes.
/*!
\param CLASS_NAME This is used as part of the class name, but will be used verbatim as the resulting object name.
\param PROPERTY_NAME A string literal that will be used as the name of the property
\param TARGET_OBJECT_CLASS The name of the Object class that contains the GETTER and SETTER methods
\param GETTER The name of the TARGET_OBJECT_CLASS method that is used to get the current value of the property
\param SETTER The name of the TARGET_OBJECT_CLASS method that is used to set the value of the property
*/
#define SimpleProperty_Imagery(CLASS_NAME, PROPERTY_NAME, TARGET_OBJECT_CLASS, GETTER, SETTER) \
	SimpleProperty( CLASS_NAME, PROPERTY_NAME, Value::T_IMAGERY, TARGET_OBJECT_CLASS, GETTER, SETTER, getValueAsImageryPtr )

//! Helper macro for quick creation of generic Face properties for Object derived classes.
/*!
\param CLASS_NAME This is used as part of the class name, but will be used verbatim as the resulting object name.
\param PROPERTY_NAME A string literal that will be used as the name of the property
\param TARGET_OBJECT_CLASS The name of the Object class that contains the GETTER and SETTER methods
\param GETTER The name of the TARGET_OBJECT_CLASS method that is used to get the current value of the property
\param SETTER The name of the TARGET_OBJECT_CLASS method that is used to set the value of the property
*/
#define SimpleProperty_Face(CLASS_NAME, PROPERTY_NAME, TARGET_OBJECT_CLASS, GETTER, SETTER) \
	SimpleProperty( CLASS_NAME, PROPERTY_NAME, Value::T_FACE, TARGET_OBJECT_CLASS, GETTER, SETTER, getValueAsFacePtr )

//! Helper macro for quick creation of generic Cursor properties for Object derived classes.
/*!
\param CLASS_NAME This is used as part of the class name, but will be used verbatim as the resulting object name.
\param PROPERTY_NAME A string literal that will be used as the name of the property
\param TARGET_OBJECT_CLASS The name of the Object class that contains the GETTER and SETTER methods
\param GETTER The name of the TARGET_OBJECT_CLASS method that is used to get the current value of the property
\param SETTER The name of the TARGET_OBJECT_CLASS method that is used to set the value of the property
*/
#define SimpleProperty_Cursor(CLASS_NAME, PROPERTY_NAME, TARGET_OBJECT_CLASS, GETTER, SETTER) \
	SimpleProperty( CLASS_NAME, PROPERTY_NAME, Value::T_CURSOR, TARGET_OBJECT_CLASS, GETTER, SETTER, getValueAsCursorPtr )

//@}


#endif // __H_OPENGUI_MACROS__
