@echo off

rem This is just a little madness added to prevent pauses during full-auto builds
IF "%1" == "SKIP" GOTO SKIP
echo PLEASE MAKE SURE YOU ARE NOT CURRENTLY RUNNING VISUAL STUDIO!
pause
GOTO SKIP
:SKIP

set VCVARS="C:\Program Files\Microsoft Visual Studio .NET 2003\Common7\Tools\vsvars32.bat"
REM I guess P stands for Path?
set P_doc="OpenGUI\doc"
set P_OFdoc="OgreFusion\doc"
set LOG=sourceBuildLog.txt

echo Loading Visual Studio Environment...
call %VCVARS% > %LOG% 2>&1


echo Cleaning Solution...
devenv OpenGUI.sln /clean "Debug - All" >> %LOG%
devenv OpenGUI.sln /clean "Release - All" >> %LOG%
call CleanAll.bat




echo Generating documentation...
rem OpenGUI Docs
cd "%P_doc%"
rmdir /Q /S html
call buildDocs.bat
call buildUserDocs.bat
cd ..\..

rem OgreFusion docs
cd "%P_OFdoc%"
rmdir /Q /S html
call buildDocs.bat
cd ..\..

echo.
echo Update the Installer Script now, then
pause

IF "%1" == "SKIP" exit
