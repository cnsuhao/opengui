#ifndef A276FC6E_2DB9_4c84_BDA0_027C4AC5E47C
#define A276FC6E_2DB9_4c84_BDA0_027C4AC5E47C

#define OPENGUI_VERSION_STR "0.7"

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
#include "OpenGUI_Types.h"
#include "OpenGUI_RefPtr.h"
#include "OpenGUI_Resource.h"


//Abstract classes for custom renderers/data providers/etc
#include "OpenGUI_ResourceProvider.h"
#include "OpenGUI_Texture.h"
#include "OpenGUI_RenderOperation.h"
#include "OpenGUI_Primitives.h"
#include "OpenGUI_Renderer.h"

//Includes necessary for core functionality

#include "OpenGUI_MouseButton.h"
#include "OpenGUI_Event.h"
#include "OpenGUI_Message.h"
#include "OpenGUI_Subscriber.h"
#include "OpenGUI_PropertySet.h"
#include "OpenGUI_Element.h"
#include "OpenGUI_GUISheet.h"
#include "OpenGUI_TextureData.h"
#include "OpenGUI_XMLParser.h"
#include "OpenGUI_Imagery.h"
#include "OpenGUI_Imageset.h"
#include "OpenGUI_ImageryManager.h"
#include "OpenGUI_Cursor.h"
#include "OpenGUI_CursorManager.h"
#include "OpenGUI_Timer.h"
#include "OpenGUI_TimerManager.h"
#include "OpenGUI_LayoutLoader.h"
#include "OpenGUI_WidgetTemplateManager.h"
#include "OpenGUI_WidgetFactoryManager.h"
#include "OpenGUI_DynamicLib.h"
#include "OpenGUI_PluginManager.h"
#include "OpenGUI_Font.h"
#include "OpenGUI_FontManager.h"
#include "OpenGUI_System.h"


//Generic Implementation of ResourceProvider
#include "OpenGUI_GenericResourceProvider.h"

//Base Widget
#include "OpenGUI_Widget.h"

//Generic Cursor Implementation
#include "OpenGUI_GenericCursor.h"


#endif
