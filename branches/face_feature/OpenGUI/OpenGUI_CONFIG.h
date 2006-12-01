#ifndef C5B841BF_4337_4748_9069_7E4604B23DE2
#define C5B841BF_4337_4748_9069_7E4604B23DE2

// This file is meant to hold configuration settings in the form of C macros.
// Please give your configuration settings useful comments so people know what they do.

//###########################################################################################
//###########################################################################################
//###########################################################################################

//***********************//
//  FONT CACHE SETTINGS  //
//***********************//

// This setting turns on the size guessing code for guessing the size of the
// next font atlas to create. Without this turned on, the font cache will
// simply make the smallest possible font atlas that will hold the next glyph.
//
// This code is highly experimental, and it is recommended that you don't use it.
//
// To turn on, uncomment. To turn off, just comment out.
// #define FONTCACHE_GUESS_FONTATLAS_SIZE


// These next two settings control the maximum and minimum sizes of font atlas
// textures. Settings these to non-power of 2 sizes, or sizes that most video
// cards cannot handle is not recommended. This setting will dictate the maximum
// size of pixel aligned font that OpenGUI can display.
//
// These settings are required in all configurations,
// and the defaults are good enough for most applications.
#define FONTCACHE_MIN_FONTATLAS_DIM 256
#define FONTCACHE_MAX_FONTATLAS_DIM 1024


//###########################################################################################
//###########################################################################################
//###########################################################################################

// These settings are used to hold the default Screen UPI (Units per Inch). These are used to
// determine constant font glyph scaling along each axis. These defaults are normally adequate
// for most situations. They are held here in a #define to allow easy changing in the event
// that the desired UPI for all Screens should change uniformly across your application.
#define DEFAULT_SCREEN_UPI_X 96.0f
#define DEFAULT_SCREEN_UPI_Y 96.0f


//###########################################################################################
//###########################################################################################
//###########################################################################################

//*******************************//
//  DYNAMIC LIB LOADER SETTINGS  //
//*******************************//
/*! \page PMANGLE Plugin Filename Mangling
This section is copied verbatim from OpenGUI_CONFIG.h:
\verbatim
// The DynamicLib class provides cross platform loading of dynamic libraries. Because of
// the differences in file naming conventions of dynamic libraries on different platforms,
// it also has the ability to provide a filename mangling service. This allows you to
// provide dynamic library names by filename prefix only, and will automatically generate
// the correct suffix (filename extension) according to the current platform.
// 	( .dll for Windows; .so for Linux )
// It also provides the ability to append "_d" to the filename prefix if OpenGUI was built
// as a debug version.
//
// Sets the style of filename mangling that is performed.
// 0 - Mangling is DISABLED completely (default action if DYNAMICLIB_FILENAME_MANGLING is not defined)
// 1 - Mangling is ALWAYS performed, even if the given filename already matches an existing file
//	( "_d" is ALWAYS appended to filename prefixes if OpenGUI is debug )
// 2 - Mangling is performed ONLY when the given filename does not match an existing file
//	( "_d" is ONLY appended to filename prefixes if the given filename is not found if OpenGUI is debug )
// 3 - Mangling is performed when the given filename does not match an existing file,
//	except "_d" is ALWAYS appended to the filename prefix if OpenGUI was built in debug mode
//	( in release mode, will act the same as setting 2 )
//
// In order to properly supply cross platform builds of demos with the least effort, the default
// setting is 1 (full mangling ALWAYS enforced). Changing this value will likely break at least some
// demos, as it will invalidate the xml config files they utilize.
\endverbatim */
#define DYNAMICLIB_FILENAME_MANGLING 1


#endif
