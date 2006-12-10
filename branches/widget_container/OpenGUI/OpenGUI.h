#ifndef A276FC6E_2DB9_4c84_BDA0_027C4AC5E47C
#define A276FC6E_2DB9_4c84_BDA0_027C4AC5E47C

#define OPENGUI_VERSION_STR "0.8 [Kunzite]"

//Just a bunch of macros to determine platform
#include "OpenGUI_Platform.h"

//All system library includes go here
#include "OpenGUI_PreRequisites.h"

//=================================================================================//
// > If you plan on adding a memory manager, this is probably a good spot for it < //
//=================================================================================//

//Custom data types and import/export macros
#include "OpenGUI_Exports.h"
#include "OpenGUI_LogSystem.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_Math.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_StrConv.h"
#include "OpenGUI_Value.h"
#include "OpenGUI_RefPtr.h"
#include "OpenGUI_RefObject.h"
#include "OpenGUI_Resource.h"


//Abstract classes for custom renderers/data providers/etc
#include "OpenGUI_ResourceProvider.h"
#include "OpenGUI_Texture.h"
#include "OpenGUI_RenderTexture.h"
#include "OpenGUI_TextureManager.h"
#include "OpenGUI_RenderOperation.h"
#include "OpenGUI_Renderer.h"
#include "OpenGUI_Viewport.h"

//Includes necessary for core functionality
#include "OpenGUI_Event.h"
#include "OpenGUI_EventHandler.h"
#include "OpenGUI_Object.h"
#include "OpenGUI_ObjectAccessor.h"

#include "OpenGUI_TextureManager.h"
#include "OpenGUI_TextureData.h"
#include "OpenGUI_XML.h"
#include "OpenGUI_XMLParser.h"
#include "OpenGUI_Imagery.h"
#include "OpenGUI_Face.h"
#include "OpenGUI_FaceDef.h"
#include "OpenGUI_Imageset.h"
#include "OpenGUI_ImageryManager.h"

#include "OpenGUI_Timer.h"
#include "OpenGUI_TimerManager.h"

#include "OpenGUI_PluginManager.h"
#include "OpenGUI_Font.h"
#include "OpenGUI_FontSet.h"
#include "OpenGUI_FontManager.h"
#include "OpenGUI_System.h"

#include "OpenGUI_Cursor.h"
#include "OpenGUI_CursorManager.h"
#include "OpenGUI_WidgetManager.h"
#include "OpenGUI_FormManager.h"

//Generic Implementation of ResourceProvider
#include "OpenGUI_GenericResourceProvider.h"

//Generic Cursor Implementation
#include "OpenGUI_GenericCursor.h"

#include "OpenGUI_BrushModifier.h"
#include "OpenGUI_Brush.h"
#include "OpenGUI_Brush_Memory.h"
#include "OpenGUI_Brush_RTT.h"
#include "OpenGUI_Brush_Caching.h"

#include "OpenGUI_Widget.h"
#include "OpenGUI_I_WidgetContainer.h"

#include "OpenGUI_Control.h"
#include "OpenGUI_ContainerControl.h"
#include "OpenGUI_Window.h"

#include "OpenGUI_Screen.h"
#include "OpenGUI_ScreenManager.h"

#endif
