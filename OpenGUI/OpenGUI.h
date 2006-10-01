#ifndef A276FC6E_2DB9_4c84_BDA0_027C4AC5E47C
#define A276FC6E_2DB9_4c84_BDA0_027C4AC5E47C

#define OPENGUI_VERSION_STR "0.7.7 [beta]"

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
#include "OpenGUI_Math.h"
#include "OpenGUI_Types.h"
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
//#include "OpenGUI_Primitives.h" //REMOVED replacing with new Brush based system
#include "OpenGUI_Renderer.h"

//Includes necessary for core functionality

//#include "OpenGUI_MouseButton.h"  //REMOVED replacing with more generic Input namespace to handle specifics of special input values

#include "OpenGUI_Event.h"
#include "OpenGUI_EventHandler.h"

//#include "OpenGUI_Message.h"  //REMOVED replacing with new Object based system
//#include "OpenGUI_EventListener.h" //REMOVED replacing with new Object based system
//#include "OpenGUI_PropertySet.h"  //REMOVED replacing with new Object based system

//#include "OpenGUI_RenderCache.h" //The RenderCache system is included where needed, and is not for use by client applications.

//#include "OpenGUI_Element.h" //REMOVED replacing with new Object based system
//#include "OpenGUI_GUISheet.h" //REMOVED replacing with new Object based system

#include "OpenGUI_TextureManager.h"
#include "OpenGUI_TextureData.h"
#include "OpenGUI_XMLParser.h"
#include "OpenGUI_Imagery.h"
#include "OpenGUI_Imageset.h"
#include "OpenGUI_ImageryManager.h"

#include "OpenGUI_Timer.h"
#include "OpenGUI_TimerManager.h"


//#include "OpenGUI_LayoutLoader.h" //temporarily removed. Will re-add after Object system in place
//#include "OpenGUI_WidgetTemplateManager.h" //temporarily removed. Will re-add after Object system in place
//#include "OpenGUI_WidgetFactoryManager.h" //temporarily removed. Will re-add after Object system in place

#include "OpenGUI_DynamicLib.h"
#include "OpenGUI_PluginManager.h"
#include "OpenGUI_Font.h"
#include "OpenGUI_FontManager.h"
#include "OpenGUI_System.h"


//Generic Implementation of ResourceProvider
#include "OpenGUI_GenericResourceProvider.h"

//Base Widget
//#include "OpenGUI_Widget.h" //REMOVED replacing with new Object based system

//Generic Cursor Implementation
//#include "OpenGUI_GenericCursor.h" //removed, maybe temporary. Yet to be determined.

#include "OpenGUI_Object.h"
#include "OpenGUI_ObjectAccessor.h"

#include "OpenGUI_BrushModifier.h"
#include "OpenGUI_Brush.h"

#include "OpenGUI_Widget.h"

#include "OpenGUI_Screen.h"
#include "OpenGUI_ScreenManager.h"

#endif
