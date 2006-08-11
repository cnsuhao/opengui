@echo off

rem This is just a little madness added to prevent pauses during full-auto builds
IF "%1" == "SKIP" GOTO SKIP
echo PLEASE MAKE SURE YOU ARE NOT CURRENTLY RUNNING VISUAL STUDIO!
pause
GOTO SKIP
:SKIP

set VCVARS="C:\Program Files\Microsoft Visual Studio .NET 2003\Common7\Tools\vsvars32.bat"
REM I guess P stands for Path?
set P_tmp="..\winSRC"
set P_="OpenGUIsrc"
set PI_exbin="examples\bin"
set P_doc="OpenGUI\doc"
set P_OFdoc="OgreFusion\doc"
set LOG=sourceBuildLog.txt

echo Loading Visual Studio Environment...
call %VCVARS% > %LOG% 2>&1

rem Delete any previous SRC data
rmdir /s /q %P_% >> %LOG% 2>&1
rmdir /s /q %P_tmp% >> %LOG% 2>&1

echo Cleaning Solution...
devenv OpenGUI.sln /clean "Debug - All" >> %LOG%
devenv OpenGUI.sln /clean "Release - All" >> %LOG%
call CleanAll.bat


echo Build directory tree...
xcopy /E * "%P_tmp%\" >> %LOG% 2>&1
xcopy /H /Y OpenGUI.suo "%P_tmp%\" >> %LOG% 2>&1
xcopy /H /Y "OpenGUI VC8.suo" "%P_tmp%\" >> %LOG% 2>&1
move "%P_tmp%" "%P_%" >> %LOG% 2>&1

echo Cleaning source tree...
cd %P_%
del /S *.ilk > NUL 2>&1
del /S *.pdb > NUL 2>&1
del *.ncb > NUL 2>&1
rmdir /Q /S OpenGUI_OGLRenderer\Debug > NUL 2>&1
rmdir /Q /S OpenGUI_OGLRenderer\Release > NUL 2>&1
rmdir /Q /S examples\Demo1\Debug > NUL 2>&1
rmdir /Q /S examples\Demo1\Release > NUL 2>&1
rmdir /Q /S examples\TachometerWidget\Debug > NUL 2>&1
rmdir /Q /S examples\TachometerWidget\Release > NUL 2>&1
rmdir /Q /S examples\glfw\Debug > NUL 2>&1
rmdir /Q /S examples\glfw\Release > NUL 2>&1
rmdir /Q /S OgreFusion\Debug > NUL 2>&1
rmdir /Q /S OgreFusion\Release > NUL 2>&1

rmdir /Q /S dependancies\OgreSDK_vc71
mkdir dependancies\OgreSDK_vc71
copy ..\dependancies\OgreSDK_vc71\README.txt dependancies\OgreSDK_vc71\
rmdir /Q /S dependancies\OgreSDK_vc8
mkdir dependancies\OgreSDK_vc8
copy ..\dependancies\OgreSDK_vc8\README.txt dependancies\OgreSDK_vc8\
rmdir /Q /S dependancies\MSVC Redist

rmdir /Q /S dependancies\corona-linux > NUL 2>&1
del *.bat *.nsi > NUL 2>&1
rmdir /Q /S OpenGUI\doc > NUL 2>&1
rmdir /Q /S OgreFusion\doc > NUL 2>&1
rmdir /Q /S Debug > NUL 2>&1
rmdir /Q /S Release > NUL 2>&1
del "%PI_exbin%\*.pdb" "%PI_exbin%\*.dll" "%PI_exbin%\*.log" > NUL 2>&1
del sdkInstaller.aip > NUL 2>&1
del sourceBuildLog.txt > NUL 2>&1
cd..


echo Including documentation...
rem OpenGUI Docs
cd "%P_doc%"
call buildDocs.bat
call buildUserDocs.bat
cd ..\..
copy "%P_doc%\OpenGUI_INTERNAL.chm" "%P_%\" > NUL 2>&1
copy "%P_doc%\OpenGUI.chm" "%P_%\" > NUL 2>&1

rem OgreFusion docs
cd "%P_OFdoc%"
call buildDocs.bat
cd ..\..
copy "%P_OFdoc%\OgreFusion.chm" "%P_%\" > NUL 2>&1

IF "%1" == "SKIP" exit
