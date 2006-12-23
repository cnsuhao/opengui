========================================================================
    Renderer_Ogre : Ogre Integration for OpenGUI
========================================================================

Renderer_Ogre requires the Ogre library (http://www.ogre3d.org/).
Since Ogre is far too large and frequently updated, it is not included
directly into the OpenGUI source tree. You will either need to download
the Ogre SDK, or obtain and compile the source yourself.

To build Renderer_Ogre, you are highly encouraged to use scons. The
flags to build it can be obtained by returning to the project root
and typing "scons -h".



If you insist on using the Renderer_Ogre.sln, you will need to first
manually build OpenGUI before building the Ogre renderer. The project
settings must also be edited to point to your already built Ogre tree
before it will compile correctly. You will need to correct both the
include search path and the library path to point to the correct
directories. Renderer_Ogre specifically needs OgreMain(_d).lib and the
corresponding headers.

If you're looking for an easy way out, install the prebuilt Ogre SDK.
Renderer_Ogre is already set up to use the environment variables that
are set by the Ogre SDK during its installation, and should build out
of the box with this setup.

*** BRIEF HISTORY ***
Renderer_Ogre was originally loosely based on the OgreCEGUIRenderer
project that comes with the Ogre rendering engine, but has since been
completely rewritten from scratch, incorporating several optimizations
that OpenGUI natively supports as well as performing best effort batch
combining to lower the load on the video card and driver. This has
resulted in much better performance than the original OgreCEGUIRenderer
was ever capable of attaining. There is no longer any doubt that OpenGUI
is fully prepared to run under heavy workloads with minimal impact on
scene performance.
