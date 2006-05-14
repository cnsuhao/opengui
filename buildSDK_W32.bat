@echo off

rem This is just a little madness added to prevent pauses during full-auto builds
IF "%1" == "SKIP" GOTO SKIP
echo PLEASE MAKE SURE YOU ARE NOT CURRENTLY RUNNING VISUAL STUDIO!
pause
GOTO SKIP
:SKIP

set VCVARS="C:\Program Files\Microsoft Visual Studio .NET 2003\Common7\Tools\vsvars32.bat"
set P_="winSDK"
set P_OG="winSDK\OpenGUI"
set P_OGinc="winSDK\OpenGUI\include"
set P_OGlib="winSDK\OpenGUI\lib"
set P_OGLinc="winSDK\OGLRenderer\include"
set P_OGLlib="winSDK\OGLRenderer\lib"
set P_TACHinc="winSDK\Tachometer\include"
set P_TACHlib="winSDK\Tachometer\lib"
set P_demo="winSDK\Demos"
set LOG="sdkBuildLog.txt"

rem Reset the Build Log
echo Begin Build > %LOG% 2>&1

echo Loading Visual Studio Environment...
call %VCVARS% >> %LOG% 2>&1

rem Delete any previous SDK data
rmdir /s /q %P_% >> %LOG% 2>&1

echo Cleaning Solution...
echo ################ >> %LOG% 2>&1
echo ### CLEANING ### >> %LOG% 2>&1
echo ################ >> %LOG% 2>&1
echo ############################################### >> %LOG% 2>&1
devenv OpenGUI.sln /clean Debug >> %LOG%
devenv OpenGUI.sln /clean Release >> %LOG%

echo Building Solution...
echo ################ >> %LOG% 2>&1
echo ### BUILDING ### >> %LOG% 2>&1
echo ################ >> %LOG% 2>&1
echo ############################################### >> %LOG% 2>&1
devenv OpenGUI.sln /build Debug >> %LOG%
devenv OpenGUI.sln /build Release >> %LOG%

IF "%1" == "SKIP" GOTO SKIP2
echo PLEASE CHECK THE SDK BUILD LOG AND ENSURE THAT EVERYTHING BUILT CORRECTLY BEFORE CONTINUING
pause
GOTO SKIP2
:SKIP2

echo Build directory tree...
mkdir %P_OGinc%
mkdir %P_OGlib%
mkdir %P_OGLinc%
mkdir %P_OGLlib%
mkdir %P_TACHinc%
mkdir %P_TACHlib%
mkdir %P_demo%

echo Copying OpenGUI files...
copy OpenGUI\LICENSE.TXT %P_OG% >> %LOG% 2>&1
copy OpenGUI\*.h %P_OGinc% >> %LOG% 2>&1
copy Debug\OpenGUI_d.lib %P_OGlib% >> %LOG% 2>&1
copy Debug\OpenGUI_d.dll %P_OGlib% >> %LOG% 2>&1
copy Release\OpenGUI.lib %P_OGlib% >> %LOG% 2>&1
copy Release\OpenGUI.dll %P_OGlib% >> %LOG% 2>&1
copy OpenGUI\*.h %P_OGinc% >> %LOG% 2>&1

echo Copying OpenGL Renderer files...
copy OpenGUI_OGLRenderer\*.h %P_OGLinc% >> %LOG% 2>&1
copy Release\OpenGUI_OGLRenderer.lib %P_OGLlib% >> %LOG% 2>&1
copy Debug\OpenGUI_OGLRenderer_d.lib %P_OGLlib% >> %LOG% 2>&1

echo Copying Tachometer files
copy examples\TachometerWidget\*.h %P_TACHinc% >> %LOG% 2>&1
copy examples\bin\TachometerWidget.dll %P_TACHlib% >> %LOG% 2>&1
copy examples\bin\TachometerWidget.lib %P_TACHlib% >> %LOG% 2>&1
copy examples\bin\TachometerWidget_d.dll %P_TACHlib% >> %LOG% 2>&1
copy examples\bin\TachometerWidget_d.lib %P_TACHlib% >> %LOG% 2>&1

echo Copying Demos...
copy examples\bin\licenses.txt %P_demo% >> %LOG% 2>&1
copy examples\bin\pecot.ttf %P_demo% >> %LOG% 2>&1
copy examples\bin\kongtext.ttf %P_demo% >> %LOG% 2>&1
copy examples\bin\TachometerWidget.dll %P_demo% >> %LOG% 2>&1
copy examples\bin\tachometer.png %P_demo% >> %LOG% 2>&1
copy examples\bin\tachometer.xml %P_demo% >> %LOG% 2>&1
copy examples\bin\metal.png %P_demo% >> %LOG% 2>&1
copy examples\bin\metal.xml %P_demo% >> %LOG% 2>&1
copy examples\bin\OpenGUI.dll %P_demo% >> %LOG% 2>&1
copy examples\bin\demo1.xml %P_demo% >> %LOG% 2>&1
copy examples\bin\Demo1.exe %P_demo% >> %LOG% 2>&1

echo Copying Documentation...
copy OpenGUI\doc\OpenGUI.chm %P_% >> %LOG% 2>&1
copy CHANGELOG.txt %P_% >> %LOG% 2>&1

GOTO END
:END
IF "%1" == "SKIP" exit
