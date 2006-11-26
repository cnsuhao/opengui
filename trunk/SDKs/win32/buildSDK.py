BUILD_VS8  = True
BUILD_VS71 = True
DEMO_VER   = "VS71" # VS71 or VS8
OGRE_HOME_VS71 = 'C:\OgreSDK_vc71' # To skip, set to: OGRE_HOME_VS71 = None
OGRE_HOME_VS8 = 'C:\OgreSDK_vc8'   # To skip, set to: OGRE_HOME_VS8 = None
WORKDIR = "tmp"
SCONSROOT = '../../'
SCONSCMD = 'scons -Q -s all'

### Environment variables from installer
# OPENGUI_INCLUDE
# OPENGUI_VC8
# OPENGUI_VC71
# OPENGUI_HOME

############################

OGRE_STR_VS8  = ""
OGRE_STR_VS71 = ""
if len(OGRE_HOME_VS8) > 0:
	OGRE_STR_VS8  = 'OGRE=' + OGRE_HOME_VS8
if len(OGRE_HOME_VS71) > 0:
	OGRE_STR_VS71 = 'OGRE=' + OGRE_HOME_VS71

if BUILD_VS8 and not BUILD_VS71:
	print " *** Demo Override: Using VS8 ***"
	DEMO_VER = "VS8"
if BUILD_VS71 and not BUILD_VS8:
	print " *** Demo Override: Using VS71 *** "
	DEMO_VER = "VS71"

from os import *
from shutil import *
from sys import *
import fnmatch

def MAIN():

##### CLEAN PREVIOUS BUILD #####
	print 'Cleaning any previous builds...',
	if access(WORKDIR,F_OK):
		rmtree(WORKDIR)
	print 'DONE!'



##### CREATE DIRECTORY LAYOUT #####
	print 'Building directory layout...'
	DirTree = []
	DirTree += [WORKDIR + '/Demos/OpenGL']
	DirTree += [WORKDIR + '/Demos/Ogre']
	DirTree += [WORKDIR + '/Renderer_Ogre']
	DirTree += [WORKDIR + '/Renderer_Ogre/include']
	DirTree += [WORKDIR + '/Renderer_Ogre/vc8/lib']
	DirTree += [WORKDIR + '/Renderer_Ogre/vc8/bin']
	DirTree += [WORKDIR + '/Renderer_Ogre/vc71/lib']
	DirTree += [WORKDIR + '/Renderer_Ogre/vc71/bin']
	DirTree += [WORKDIR + '/Renderer_OpenGL']
	DirTree += [WORKDIR + '/Renderer_OpenGL/include']
	DirTree += [WORKDIR + '/Renderer_OpenGL/vc8/lib']
	DirTree += [WORKDIR + '/Renderer_OpenGL/vc8/bin']
	DirTree += [WORKDIR + '/Renderer_OpenGL/vc71/lib']
	DirTree += [WORKDIR + '/Renderer_OpenGL/vc71/bin']
	DirTree += [WORKDIR + '/OpenGUI']
	DirTree += [WORKDIR + '/OpenGUI/include']
	DirTree += [WORKDIR + '/OpenGUI/vc8/lib']
	DirTree += [WORKDIR + '/OpenGUI/vc8/bin']
	DirTree += [WORKDIR + '/OpenGUI/vc71/lib']
	DirTree += [WORKDIR + '/OpenGUI/vc71/bin']
	MakeTree(DirTree)



##### EXPORT SOURCE TREE #######
	RunCommand('Exporting source tree...','svn export ../../ ' + WORKDIR + '/src')



##### REMOVE SOURCE TOOLS ######
	rmtree(WORKDIR + '/src/tools/')



##### CLEANING ALL BUILDS #######
	if BUILD_VS71:
		CMD = SCONSCMD + ' -c VS=7.1 ' + OGRE_STR_VS71
		RunCommand('Cleaning VS 7.1 RELEASE build', CMD, SCONSROOT)
		CMD += ' debug=1'
		RunCommand('Cleaning VS 7.1 DEBUG build', CMD, SCONSROOT)
	if BUILD_VS8:
		CMD = SCONSCMD + ' -c VS=8.0 ' + OGRE_STR_VS8
		RunCommand('Cleaning VS 8.0 RELEASE build', CMD, SCONSROOT)
		CMD += ' debug=1'
		RunCommand('Cleaning VS 8.0 DEBUG build', CMD, SCONSROOT)



##### COPY INCLUDE FILES ########
	CopyIncludes()



##### BUILD VC 7.1 BINARIES #####
	if BUILD_VS71:
		CMD = SCONSCMD + ' VS=7.1 ' + OGRE_STR_VS71
		DBGCMD = CMD + ' debug=1'
		# DEBUG
		RunCommand('Building VS 7.1 Binaries: DEBUG', DBGCMD, SCONSROOT)
		CopyDebugBins('vc71')
		DBGCMD += ' -c'
		RunCommand('Cleaning VS 7.1 Binaries: DEBUG', DBGCMD, SCONSROOT)
		# RELEASE
		RunCommand('Building VS 7.1 Binaries: RELEASE', CMD, SCONSROOT)
		if DEMO_VER == "VS71":
			CopyDemos()
		CopyReleaseBins('vc71')
		CMD += ' -c'
		RunCommand('Cleaning VS 7.1 Binaries: RELEASE', CMD, SCONSROOT)



##### BUILD VS 8.0 BINARIES #####
	if BUILD_VS8:
		CMD = SCONSCMD + ' VS=8.0 ' + OGRE_STR_VS8
		DBGCMD = CMD + ' debug=1'
		# DEBUG
		RunCommand('Building VS 8.0 Binaries: DEBUG', DBGCMD, SCONSROOT)
		CopyDebugBins('vc8')
		DBGCMD += ' -c'
		RunCommand('Cleaning VS 8.0 Binaries: DEBUG', DBGCMD, SCONSROOT)
		# RELEASE
		RunCommand('Building VS 8.0 Binaries: RELEASE', CMD, SCONSROOT)
		if DEMO_VER == "VS8":
			CopyDemos()
		CopyReleaseBins('vc8')
		CMD += ' -c'
		RunCommand('Cleaning VS 8.0 Binaries: RELEASE', CMD, SCONSROOT)






######################################################
#    BELOW ARE FUNCTIONS USED IN ABOVE PROCESSING    #
######################################################

#### Builds the given list of directories
def MakeTree(dirs):
	for d in dirs:
		print '    ', d
		makedirs(d)

#### Change directory with reporting
def ChDir(newDir):
	print ' * ChDir:',newDir
	chdir(newDir)

#### Runs the given command with the provided message
def RunCommand(message, command, newdir = None):
	retDir = getcwd()
	print
	print '############################################'
	if newdir:
		ChDir(newdir)
	print message
	print '    -:',command
	system(command)
	for i in message:
		print '',
	print '...DONE!'
	if newdir:
		ChDir(retDir)
	print '############################################'
	print

#### Copies the Demos into the demo dir for the sdk
def CopyDemos():
	print "Copying DEMOS!..."
	global WORKDIR
	global SCONSROOT
	OpenGL_src = SCONSROOT + '/Renderers/OpenGL/bin/'
	Ogre_src   = SCONSROOT + '/Renderers/Ogre/bin/release/'
	OpenGL_dst = WORKDIR   + '/Demos/OpenGL/'
	Ogre_dst   = WORKDIR   + '/Demos/Ogre/'
	
	dstdir = Ogre_dst
	srcdir = Ogre_src
	files = listdir(srcdir)
	tmp =  fnmatch.filter(files,"*.dll")
	tmp += fnmatch.filter(files,"*.exe")
	tmp += fnmatch.filter(files,"*.cfg")
	tmp += fnmatch.filter(files,"*.zip")
	files = tmp
	CopyFiles(srcdir,dstdir,files)

	dstdir = OpenGL_dst
	srcdir = OpenGL_src
	files = listdir(srcdir)
	tmp =  fnmatch.filter(files,"*.dll")
	tmp += fnmatch.filter(files,"*.exe")
	tmp += fnmatch.filter(files,"*.png")
	tmp += fnmatch.filter(files,"*.xml")
	tmp += fnmatch.filter(files,"*.txt")
	tmp += fnmatch.filter(files,"*.ttf")
	files = tmp
	CopyFiles(srcdir,dstdir,files)

def CopyIncludes():
	global WORKDIR
	global SCONSROOT
	print "Copying INCLUDES..."
	# OpenGUI
	dstdir = WORKDIR + '/OpenGUI/include/'
	srcdir = SCONSROOT + '/OpenGUI/'
	files = listdir(srcdir)
	files = fnmatch.filter(files,"*.h")
	CopyFiles(srcdir,dstdir,files)
	# Renderer_OpenGL
	dstdir = WORKDIR + '/Renderer_OpenGL/include/'
	srcdir = SCONSROOT + '/Renderers/OpenGL/Renderer_OpenGL/'
	files = listdir(srcdir)
	files = fnmatch.filter(files,"*.h")
	CopyFiles(srcdir,dstdir,files)
	# Renderer_Ogre
	dstdir = WORKDIR + '/Renderer_Ogre/include/'
	srcdir = SCONSROOT + '/Renderers/Ogre/Renderer_Ogre/'
	files = listdir(srcdir)
	files = fnmatch.filter(files,"*.h")
	CopyFiles(srcdir,dstdir,files)
	print "Copying INCLUDES...DONE!"
	pass

def CopyReleaseBins(SDKtype):
	SDKtype = SDKtype.lower()
	print "Copying RELEASE binaries..."
	# OpenGUI
	dstdir = WORKDIR + '/OpenGUI/' + SDKtype + '/bin/'
	srcdir = SCONSROOT + '/bin/'
	files = ['OpenGUI.dll','OpenGUI.pdb']
	CopyFiles(srcdir,dstdir,files)
	dstdir = WORKDIR + '/OpenGUI/' + SDKtype + '/lib/'
	srcdir = SCONSROOT + '/lib/'
	files = ['OpenGUI.lib']
	CopyFiles(srcdir,dstdir,files)
	# Renderer_OpenGL
	dstdir = WORKDIR + '/Renderer_OpenGL/' + SDKtype + '/lib/'
	srcdir = SCONSROOT + '/Renderers/OpenGL/lib/'
	files = ['Renderer_OpenGL.lib']
	CopyFiles(srcdir,dstdir,files)
	# Renderer_Ogre
	dstdir = WORKDIR + '/Renderer_Ogre/' + SDKtype + '/bin/'
	srcdir = SCONSROOT + '/Renderers/Ogre/bin/release/'
	files = ['Renderer_Ogre.dll','Renderer_Ogre.pdb']
	CopyFiles(srcdir,dstdir,files)
	dstdir = WORKDIR + '/Renderer_Ogre/' + SDKtype + '/lib/'
	srcdir = SCONSROOT + '/Renderers/Ogre/lib/'
	files = ['Renderer_Ogre.lib']
	CopyFiles(srcdir,dstdir,files)
	pass
def CopyDebugBins(SDKtype):
	SDKtype = SDKtype.lower()
	print "Copying DEBUG binaries..."
	# OpenGUI
	dstdir = WORKDIR + '/OpenGUI/' + SDKtype + '/bin/'
	srcdir = SCONSROOT + '/bin/'
	files = ['OpenGUI_d.dll','OpenGUI_d.pdb']
	CopyFiles(srcdir,dstdir,files)
	dstdir = WORKDIR + '/OpenGUI/' + SDKtype + '/lib/'
	srcdir = SCONSROOT + '/lib/'
	files = ['OpenGUI_d.lib']
	CopyFiles(srcdir,dstdir,files)
	# Renderer_OpenGL
	dstdir = WORKDIR + '/Renderer_OpenGL/' + SDKtype + '/lib/'
	srcdir = SCONSROOT + '/Renderers/OpenGL/lib/'
	files = ['Renderer_OpenGL_d.lib']
	CopyFiles(srcdir,dstdir,files)
	# Renderer_Ogre
	dstdir = WORKDIR + '/Renderer_Ogre/' + SDKtype + '/bin/'
	srcdir = SCONSROOT + '/Renderers/Ogre/bin/debug/'
	files = ['Renderer_Ogre_d.dll','Renderer_Ogre_d.pdb']
	CopyFiles(srcdir,dstdir,files)
	dstdir = WORKDIR + '/Renderer_Ogre/' + SDKtype + '/lib/'
	srcdir = SCONSROOT + '/Renderers/Ogre/lib/'
	files = ['Renderer_Ogre_d.lib']
	CopyFiles(srcdir,dstdir,files)
	pass

def CopyFiles(srcdir,dstdir,fileList):
	print "  COPY: " + srcdir + ' -> ' + dstdir
	for f in fileList:
		src = srcdir + f
		dst = dstdir + f
		print "        ->",f
		copyfile(src,dst)
#### Begin execution
MAIN()
