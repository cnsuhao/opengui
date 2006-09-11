# Microsoft Developer Studio Project File - Name="test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "test.mak" CFG="test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "test - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "test - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../../src" /I "../../test/cppunit-1.6.2" /D "NDEBUG" /D for="if (0) ; else for" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"../bin/Release/test.exe"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../../src" /I "../../test/cppunit-1.6.2" /D "_DEBUG" /D for="if (0) ; else for" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"../bin/Debug/test.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "test - Win32 Release"
# Name "test - Win32 Debug"
# Begin Group "files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\test\APITests.cpp
# End Source File
# Begin Source File

SOURCE=..\..\test\APITests.h
# End Source File
# Begin Source File

SOURCE=..\..\test\BMPTests.cpp
# End Source File
# Begin Source File

SOURCE=..\..\test\BMPTests.h
# End Source File
# Begin Source File

SOURCE=..\..\test\CoronaTest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\test\FileTests.cpp
# End Source File
# Begin Source File

SOURCE=..\..\test\FileTests.h
# End Source File
# Begin Source File

SOURCE=..\..\test\GIFTests.cpp
# End Source File
# Begin Source File

SOURCE=..\..\test\GIFTests.h
# End Source File
# Begin Source File

SOURCE=..\..\test\ImageTestCase.h
# End Source File
# Begin Source File

SOURCE=..\..\test\JPEGTests.cpp
# End Source File
# Begin Source File

SOURCE=..\..\test\JPEGTests.h
# End Source File
# Begin Source File

SOURCE=..\..\test\PaletteTests.cpp
# End Source File
# Begin Source File

SOURCE=..\..\test\PaletteTests.h
# End Source File
# Begin Source File

SOURCE=..\..\test\PCXTests.cpp
# End Source File
# Begin Source File

SOURCE=..\..\test\PCXTests.h
# End Source File
# Begin Source File

SOURCE=..\..\test\PNGTests.cpp
# End Source File
# Begin Source File

SOURCE=..\..\test\PNGTests.h
# End Source File
# Begin Source File

SOURCE=..\..\test\TestFramework.h
# End Source File
# Begin Source File

SOURCE=..\..\test\TGATests.cpp
# End Source File
# Begin Source File

SOURCE=..\..\test\TGATests.h
# End Source File
# End Group
# Begin Group "cppunit"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\extensions\AutoRegisterSuite.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\config-auto.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\config-msvc6.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\Exception.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\Exception.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\extensions\HelperMacros.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\NotEqualException.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\NotEqualException.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\extensions\Orthodox.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\Portability.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\RepeatedTest.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\extensions\RepeatedTest.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\Test.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\TestAssert.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\TestAssert.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\TestCaller.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\TestCase.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\TestCase.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\extensions\TestDecorator.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\extensions\TestFactory.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\TestFactoryRegistry.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\extensions\TestFactoryRegistry.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\TestFailure.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\TestFailure.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\TestListener.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\TestRegistry.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\TestRegistry.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\TestResult.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\TestResult.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\extensions\TestSetUp.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\TestSuite.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\TestSuite.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\extensions\TestSuiteBuilder.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\extensions\TestSuiteFactory.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\TextTestResult.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\TextTestResult.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\TextTestRunner.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\TextTestRunner.h"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\TypeInfoHelper.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\test\cppunit-1.6.2\cppunit\extensions\TypeInfoHelper.h"
# End Source File
# End Group
# End Target
# End Project
