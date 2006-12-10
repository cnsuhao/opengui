/*! \addtogroup Macros
@{
*/

/*! \file OpenGUI_NoMacros.h
This file undefines the helper macros. It can be included multiple times with
no ill effect. It will only undefine the %OpenGUI helper macros if they have
been previously included.
*/

/*! @} */

#ifdef __H_OENGUI_MACROS__

#undef __H_OENGUI_MACROS__

#undef SimpleProperty
#undef SimpleProperty_String
#undef SimpleProperty_Bool
#undef SimpleProperty_Float
#undef SimpleProperty_FVector2
#undef SimpleProperty_FRect
#undef SimpleProperty_Integer
#undef SimpleProperty_IVector2
#undef SimpleProperty_IRect
#undef SimpleProperty_Color
#undef SimpleProperty_Font
#undef SimpleProperty_TextAlignment
#undef SimpleProperty_Imagery
#undef SimpleProperty_Face

#endif
