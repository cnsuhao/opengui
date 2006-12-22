========================================================================
    OpenGUI.Net : OpenGUI integration for Managed Languages
========================================================================

The main purpose of OpenGUI.NET is to provide an access layer for any
managed language to work with OpenGUI. It is not intended to provide a
complete port, nor is it intended to fully expose every aspect of the
OpenGUI library. For example, you cannot create custom widgets using
OpenGUI.NET as the necessary functions to fully allow this are not
exposed. What you can do is initialize the system, load and unload
plugins, load XML configuration files, manipulate Screens and the
Widgets they contain, inject input, and bind to existing events. The
primary use of an access layer such as this is not to provide an avenue
for using OpenGUI within games that are written in managed languages.
Instead, the intention is to provide a consistent interface for adding
OpenGUI support to editors and other content creation tools.

As a project we recognize the desire for bringing a sophisticated GUI
environment to games that are entirely written in managed languages, but
we feel that creating a .NET access layer to a prebuilt C++ based
system is a shim, not a solution. The OpenGUI library itself is an
entirely open source system, and as a project we would encourage anyone
to fully bridge the gap between the managed/native world by providing a
full port to managed languages. Ideally, such a port would be written in
100% managed languages, including any dependencies. This would allow
such a system to work with existing technologies such as Microsoft's XNA
environment to truly provide the level of integration that such a
platform requires. If anyone is interested in spearheading such an
endeavor, please do not hesitate to approach the OpenGUI development
team. Most would be pleased to assist you in some manner to help you
make such a port a reality.
