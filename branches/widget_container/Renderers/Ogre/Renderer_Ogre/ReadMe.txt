========================================================================
    Renderer_Ogre : Ogre Integration for OpenGUI
========================================================================

Renderer_Ogre requires the Ogre library (http://www.ogre3d.org/). Since
Ogre is far too large and frequently updated, it is not included
directly into the OpenGUI source tree. The Renderer_Ogre project settings
must be editted to point to your already built Ogre tree before it will
compile correctly. You will need to correct both the include search path
and the library path to point to the correct directory. Renderer_Ogre
specifically needs OgreMain(_d).lib and the corresponding headers.

If you're looking for an easy way out, place the Ogre SDK directory
directly into dependancies\OgreSDK_vc71 or dependancies\OgreSDK_vc8
(depending on which build environment you are using). Renderer_Ogre is
already set up for compiling under this configuration, and should build
out of the box with this setup.

Renderer_Ogre is loosely based on the OgreCEGUIRenderer project that comes
with the Ogre rendering engine.
