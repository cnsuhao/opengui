platform = str(ARGUMENTS.get('OS', Platform()))
print "Detected Platform: " + platform 
debug = bool( ARGUMENTS.get('debug', 0) )
Export('debug')
if debug:
	print "Build Mode: DEBUG"
else:
	print "Build Mode: RELEASE"


DEBUG_CPPFLAGS = "/Od /EHsc /RTC1 /MDd /W3 /nologo /c /Wp64"
RELEASE_CPPFLAGS = "/Ox /Ob2 /Oi /Ot /GL /c /Wp64  /FD /EHsc /MD /W3"
G_CPPDEFINES = ['WIN32','_WINDOWS']

G_LIBPATH = []

if debug:
	G_CPPFLAGS = DEBUG_CPPFLAGS
	G_CPPDEFINES = G_CPPDEFINES + ['_DEBUG']
else:
	G_CPPFLAGS = RELEASE_CPPFLAGS
	G_CPPDEFINES = G_CPPDEFINES + ['NDEBUG']

Export('G_CPPFLAGS')
Export('G_CPPDEFINES')
Export('G_LIBPATH')


SConscript(['OpenGUI/SConscript'])
SConscript(['OpenGUI_OGLRenderer/SConscript'])
