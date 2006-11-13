
### THIS IS THE VERSION I WROTE THESE ON
### REDUCING IT WILL PROBABLY WORK, BUT YOUR MILAGE MAY VARY
EnsureSConsVersion(0, 96)



base_env = Environment()
Export('base_env')

############# DEFAULT FLAGS AND PATHS #############

G_CPPFLAGS = [] # general cpp flags
G_DEBUG_CPPFLAGS = [] # debug specific cpp flags
G_RELEASE_CPPFLAGS = [] # release specific cpp flags

G_CPPDEFINES = [] # general defines for cpp
G_DEBUG_CPPDEFINES = []
G_RELEASE_CPPDEFINES = []

G_LIBPATH = [] # general lib paths
G_DEBUG_LIBPATH = []
G_RELEASE_LIBPATH = []


###################################################
# detect debug/release and export the flag
debug = bool( ARGUMENTS.get('debug', 0) )
Export('debug')
if debug:
	print "Build Mode: DEBUG"
else:
	print "Build Mode: RELEASE"


###################################################
# At this point, we determine platform and perform special operations based on that
platform = str(ARGUMENTS.get('OS', Platform()))
print "Detected Platform: " + platform 
Export('platform')
if platform == "win32":
	G_DEBUG_CPPFLAGS += Split("/Od /EHsc /RTC1 /MDd /W3 /nologo /c /Wp64")
	G_RELEASE_CPPFLAGS += Split("/Ox /Ob2 /Oi /Ot /GL /c /Wp64  /FD /EHsc /MD /W3")
	G_CPPDEFINES += ['WIN32','_WINDOWS']
	G_DEBUG_CPPDEFINES += ['_DEBUG']
	G_RELEASE_CPPDEFINES += ['NDEBUG']



###################################################
# Process debug/release, combining the specifics with the generals
if debug:
	G_CPPFLAGS   += G_DEBUG_CPPFLAGS
	G_CPPDEFINES += G_DEBUG_CPPDEFINES
	G_LIBPATH    += G_DEBUG_LIBPATH
else:
	G_CPPFLAGS   += G_RELEASE_CPPFLAGS
	G_CPPDEFINES += G_RELEASE_CPPDEFINES
	G_LIBPATH    += G_RELEASE_LIBPATH

# Finally we update the global 'base_env' with this new and improved information
base_env.Append(CPPFLAGS = G_CPPFLAGS)
base_env.Append(CPPDEFINES = G_CPPDEFINES)
base_env.Append(LIBPATH = G_LIBPATH)


Help("""
Build Targets:
	opengui   - the OpenGUI library
	amethyst  - the Amethyst widget library
	examples  - the examples
	deps      - all dependencies
	(default) - If no targets are specified, the defaults are:
		opengui
		amethyst
		examples

Build Modes:
	Specify debug=1 to build a debug version. Otherwise release is assumed.
""")

SConscript(['OpenGUI/SConscript'])
#SConscript(['OpenGUI_OGLRenderer/SConscript'])



SConscript(['dependencies/tinyxml/SConscript'])
SConscript(['dependencies/freetype2/SConscript'])


