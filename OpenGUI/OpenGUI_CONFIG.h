#ifndef C5B841BF_4337_4748_9069_7E4604B23DE2
#define C5B841BF_4337_4748_9069_7E4604B23DE2

// This file is meant to hold configuration settings in the form of C macros.
// Please give your configuration settings useful comments so people know what they do.


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


#endif
