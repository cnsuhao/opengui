
### THIS IS THE VERSION OF SCONS I WROTE THESE ON
### LOWERING IT WILL PROBABLY WORK, BUT YOUR MILAGE MAY VARY
EnsureSConsVersion(0, 96)
###################################################
############# DEFAULT FLAGS AND PATHS #############
###################################################
#### C Compiler Options ################
G_CCFLAGS              = [] # c flags
G_DEBUG_CCFLAGS        = []
G_RELEASE_CCFLAGS      = []
#### C++ Compiler Options ##############
G_CXXFLAGS             = [] # c++ flags
G_DEBUG_CXXFLAGS       = []
G_RELEASE_CXXFLAGS     = []
#### C PreProcessor Options ############
G_CPPDEFINES           = [] # preprocessor defines
G_DEBUG_CPPDEFINES     = []
G_RELEASE_CPPDEFINES   = []
G_CPPPATH              = [] # preprocessor search path
G_DEBUG_CPPPATH        = []
G_RELEASE_CPPPATH      = []
#### Linker Options ####################
G_LIBPATH              = [] # lib paths
G_DEBUG_LIBPATH        = []
G_RELEASE_LIBPATH      = []
G_LINKFLAGS            = [] # linker flags
G_DEBUG_LINKFLAGS      = []
G_RELEASE_LINKFLAGS    = []
G_LIBS                 = [] # libs linked to all projects
G_DEBUG_LIBS           = []
G_RELEASE_LIBS         = []

###################################################
#  USERS SHOULDN'T NEED TO EDIT BELOW THIS LINE   #
###################################################



############### PLATFORM DETECTION ################
platform = str(ARGUMENTS.get('OS', Platform()))
print "Detected Platform: " + platform 
Export('platform')



############ COMPILER SUITE DETECTION #############
# We fully expect EVERY SConscript to inherit this default build_env
base_env = Environment()
Export('base_env')

if base_env.has_key('MSVS'):
	print 'Visual Studio Detected...',
	ver = ARGUMENTS.get('VS', 0)
	if bool(ver):
		print 'Requesting VS version: ' + ver,
		tmpenv = Environment(MSVS_VERSION=ver)
		msvs = tmpenv['MSVS']
		if msvs.has_key('VCINSTALLDIR') and msvs.has_key('VSINSTALLDIR'):
			print '...FOUND!',
			base_env = tmpenv
		else:
			print '...NOT FOUND! Aborting!'
			Exit(-1)
	print 'Using MSVS ' + base_env['MSVS']['VERSION']

if not (bool(base_env['CC']) and bool(base_env['CXX']) and bool(base_env['LINK'])):
	print 'No compiler detected! Abort!'
	Exit(-1)



########## SELECT DEBUG / RELEASE MODE ############
# detect debug/release and export the flag
debug = bool( ARGUMENTS.get('debug', 0) )
Export('debug')
if debug:
	print "Build Mode: DEBUG"
else:
	print "Build Mode: RELEASE"


############ PLATFORM SPECIFIC FLAGS ##############
# At this point, we determine platform and perform special operations based on that

if platform == "win32":
	G_CCFLAGS            += Split('/EHsc /W3 /GR /nologo /Z7 /Gy')
	G_DEBUG_CCFLAGS      += Split('/Od /RTC1 /MDd')
	G_RELEASE_CCFLAGS    += Split('/Ox /Ob2 /Oi /Ot /MD /GL /GF /GT')
	G_CPPDEFINES         += Split('WIN32 _WINDOWS')
	G_DEBUG_CPPDEFINES   += Split('_DEBUG')
	G_RELEASE_CPPDEFINES += Split('NDEBUG')
	G_LINKFLAGS          += Split('/NOLOGO /DEBUG /OPT:NOWIN98')
	G_DEBUG_LINKFLAGS    += Split('/INCREMENTAL')
	G_DEBUG_LINKFLAGS    += Split('/INCREMENTAL')
	G_RELEASE_LINKFLAGS  += Split('/INCREMENTAL:NO /LTCG:STATUS /OPT:REF /OPT:ICF')
	
	# VC8 has a few extra options that need tuning
	if base_env['MSVS']['VERSION'] == "8.0":
		G_RELEASE_CCFLAGS += Split('/GS- /fp:fast')

if platform == 'posix':
	G_CXXFLAGS           += ['-Wall']
	G_DEBUG_CXXFLAGS     += Split('-g')
	G_RELEASE_CXXFLAGS   += Split('-O3')
	G_CPPDEFINES         += []
	G_DEBUG_CPPDEFINES   += Split('_DEBUG')
	G_RELEASE_CPPDEFINES += Split('NDEBUG')

###################################################
# Process debug/release, combining the specifics with the generals

if debug:
	G_CCFLAGS    += G_DEBUG_CCFLAGS
	G_CXXFLAGS   += G_DEBUG_CXXFLAGS
	G_CPPDEFINES += G_DEBUG_CPPDEFINES
	G_CPPPATH    += G_DEBUG_CPPPATH
	G_LIBPATH    += G_DEBUG_LIBPATH
	G_LINKFLAGS  += G_DEBUG_LINKFLAGS
	G_LIBS       += G_DEBUG_LIBS
else:
	G_CCFLAGS    += G_RELEASE_CCFLAGS
	G_CXXFLAGS   += G_RELEASE_CXXFLAGS
	G_CPPDEFINES += G_RELEASE_CPPDEFINES
	G_CPPPATH    += G_RELEASE_CPPPATH
	G_LIBPATH    += G_RELEASE_LIBPATH
	G_LINKFLAGS  += G_RELEASE_LINKFLAGS
	G_LIBS       += G_RELEASE_LIBS


# Finally we update the global 'base_env' with this new and improved information
# C compiler
base_env.Append(CCFLAGS = G_CCFLAGS)
# C++ compiler
base_env.Append(CXXFLAGS = G_CXXFLAGS)
# C PreProcessor
base_env.Append(CPPDEFINES = G_CPPDEFINES)
base_env.Append(CPPPATH = G_CPPPATH)
# Linker
base_env.Append(LIBPATH = G_LIBPATH)
base_env.Append(LINKFLAGS = G_LINKFLAGS)
base_env.Append(LIBS = G_LIBS)

Export('base_env') # Need to re-export to update changes


############ HELP MESSAGE DEFINITION ##############

HelpText = """
Build Targets:
	opengui    - the OpenGUI library
	amethyst   - the Amethyst widget library
	tachometer - the TachometerWidget
	opengl     - the OpenGL renderer with examples
	ogre       - the Ogre renderer with examples
	deps       - all dependencies
	(default)  - If no targets are specified, the defaults are:
		opengui
		amethyst
		tachometer
		opengl

Build Modes:
	Specify debug=1 to build a debug version. Otherwise release is assumed.
"""
if platform == "win32":
	HelpText += """
Visual Studio compiler selection:
	VS=<version> -  Replace <version> with the version number.
			Ex: VS=8.0  -or-  VS=7.1
	
"""
	
Help(HelpText)


############ SUB PROJECTS PROCESSING ##############

SConscript(['OpenGUI/SConscript'])
SConscript(['TachometerWidget/SConscript'])
SConscript(['Amethyst/SConscript'])

#SConscript(['OpenGUI_OGLRenderer/SConscript'])


if platform == "win32":
	# we need this for the following dependencies on win32
	base_env.Append(CPPDEFINES = ['_CRT_SECURE_NO_DEPRECATE'])

SConscript(['deps/tinyxml/SConscript'])
SConscript(['deps/freetype2/SConscript'])
Alias('deps',['freetype'])
Alias('deps',['tinyxml'])


SConscript(['Renderers/OpenGL/deps/corona/SConscript'])

Default(['opengui','amethyst','tachometer'])


print 'Selected Build Targets: ',
for i in BUILD_TARGETS:
	print i,
print






