// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#ifndef _OGR_OGRE_PLATFORM_H_
#define _OGR_OGRE_PLATFORM_H_

/*
The purpose of this include file is to identify the system type and
compiler that is being used. This is required for certain system
specific function calls and includes.

If your platform and/or compiler are not listed here, then you will
have to port OpenGUI to your environment. If you're porting OpenGUI
to a new target, please put your platform/compiler detection updates
in this file.
*/


//Initial definitions of known platforms and compilers
#define OGR_OGRE_PLATFORM_WIN32 1
#define OGR_OGRE_PLATFORM_LINUX 2

#define OGR_OGRE_COMPILER_MSVC 1
#define OGR_OGRE_COMPILER_GCC  2




/* Detect compiler */
//check for MSVC
#if defined ( _MSC_VER )
#define OGR_OGRE_COMPILER OPENGUI_COMPILER_MSVC
//	#pragma message( "Detected Compiler: MSVC" )

//check for GCC
#elif defined ( __GNUC__ )
#define OGR_OGRE_COMPILER OPENGUI_COMPILER_GCC

#else
#pragma error "Unknown compiler! Refer to Renderer_Ogre_Platform.h"

#endif


/* Detect Platform */
//checking for win32 is easy
#if defined( __WIN32__ ) || defined( _WIN32 )
#define OGR_OGRE_PLATFORM OGR_OGRE_PLATFORM_WIN32
//	#pragma message( "Detected Platform: WIN32" )

//assume linux if nothing else fits
#else
#define OGR_OGRE_PLATFORM OGR_OGRE_PLATFORM_LINUX

#endif

#if defined ( _DEBUG )
#define OGR_OGRE_DEBUG
#endif

#if OGR_OGRE_COMPILER == OGR_OGRE_COMPILER_MSVC
// This warning can be disregarded
#pragma warning (disable : 4251)
#endif

#endif
