@echo off

rem This is just a little madness added to prevent pauses during full-auto builds
IF "%1" == "SKIP" GOTO SKIP
echo PLEASE MAKE SURE YOU ARE NOT CURRENTLY RUNNING VISUAL STUDIO!
pause
GOTO SKIP
:SKIP

setlocal
set VCVARS="C:\Program Files\Microsoft Visual Studio .NET 2003\Common7\Tools\vsvars32.bat"
REM I guess P stands for Path?
set P_out="win32rel\src"
set P_doc="OpenGUI\doc"
set P_OFdoc="OgreFusion\doc"
set LOG=sourceBuildLog.txt
set xcopy=xcopy /R /S /Y
set copy=copy /Y
echo Loading Visual Studio Environment...
call %VCVARS% > %LOG% 2>&1

echo Cleaning Solution...
devenv OpenGUI.sln /clean "Debug - All" >> %LOG% 2>&1
devenv OpenGUI.sln /clean "Release - All" >> %LOG% 2>&1
call CleanAll.bat

echo Building Tree....
mkdir %P_out%\dependancies\tinyxml >> %LOG% 2>&1
%xcopy% dependancies\tinyxml %P_out%\dependancies\tinyxml\ >> %LOG% 2>&1
mkdir %P_out%\dependancies\freetype2  >> %LOG% 2>&1
%xcopy% dependancies\freetype2 %P_out%\dependancies\freetype2\ >> %LOG% 2>&1
mkdir %P_out%\dependancies\corona >> %LOG% 2>&1
%xcopy% dependancies\corona %P_out%\dependancies\corona\ >> %LOG% 2>&1
mkdir %P_out%\dependancies\OgreSDK_vc8 >> %LOG% 2>&1
%copy% dependancies\OgreSDK_vc8\README.txt %P_out%\dependancies\OgreSDK_vc8\
mkdir %P_out%\dependancies\OgreSDK_vc71 >> %LOG% 2>&1
%copy% dependancies\OgreSDK_vc71\README.txt %P_out%\dependancies\OgreSDK_vc71\ >> %LOG% 2>&1

mkdir %P_out%\OpenGUI >> %LOG% 2>&1
%copy% OpenGUI\*.h %P_out%\OpenGUI >> %LOG% 2>&1
%copy% OpenGUI\*.cpp %P_out%\OpenGUI >> %LOG% 2>&1
%copy% OpenGUI\*.vcproj %P_out%\OpenGUI >> %LOG% 2>&1

mkdir %P_out%\OpenGUI_OGLRenderer  >> %LOG% 2>&1
%copy% OpenGUI_OGLRenderer\*.h %P_out%\OpenGUI_OGLRenderer >> %LOG% 2>&1
%copy% OpenGUI_OGLRenderer\*.cpp %P_out%\OpenGUI_OGLRenderer >> %LOG% 2>&1
%copy% OpenGUI_OGLRenderer\*.vcproj %P_out%\OpenGUI_OGLRenderer >> %LOG% 2>&1

mkdir %P_out%\OgreFusion  >> %LOG% 2>&1
%copy% OgreFusion\*.h %P_out%\OgreFusion >> %LOG% 2>&1
%copy% OgreFusion\*.cpp %P_out%\OgreFusion >> %LOG% 2>&1
%copy% OgreFusion\*.vcproj %P_out%\OgreFusion >> %LOG% 2>&1

mkdir %P_out%\examples\bin >> %LOG% 2>&1
%copy% examples\bin\*.ttf %P_out%\examples\bin >> %LOG% 2>&1
%copy% examples\bin\*.png %P_out%\examples\bin >> %LOG% 2>&1
%copy% examples\bin\*.xml %P_out%\examples\bin >> %LOG% 2>&1
%copy% examples\bin\*.txt %P_out%\examples\bin >> %LOG% 2>&1


mkdir %P_out%\examples\DemoAppFramework >> %LOG% 2>&1
%copy% examples\DemoAppFramework\*.h %P_out%\examples\DemoAppFramework >> %LOG% 2>&1
%copy% examples\DemoAppFramework\*.cpp %P_out%\examples\DemoAppFramework >> %LOG% 2>&1

mkdir %P_out%\examples\TachometerWidget >> %LOG% 2>&1
%copy% examples\TachometerWidget\*.h %P_out%\examples\TachometerWidget >> %LOG% 2>&1
%copy% examples\TachometerWidget\*.cpp %P_out%\examples\TachometerWidget >> %LOG% 2>&1
%copy% examples\TachometerWidget\*.vcproj %P_out%\examples\TachometerWidget >> %LOG% 2>&1

mkdir %P_out%\examples\Demo1 >> %LOG% 2>&1
%copy% examples\Demo1\*.h %P_out%\examples\Demo1 >> %LOG% 2>&1
%copy% examples\Demo1\*.cpp %P_out%\examples\Demo1 >> %LOG% 2>&1
%copy% examples\Demo1\*.vcproj %P_out%\examples\Demo1 >> %LOG% 2>&1

mkdir %P_out%\examples\DemoO >> %LOG% 2>&1
%copy% examples\DemoO\*.h %P_out%\examples\DemoO >> %LOG% 2>&1
%copy% examples\DemoO\*.cpp %P_out%\examples\DemoO >> %LOG% 2>&1
%copy% examples\DemoO\*.vcproj %P_out%\examples\DemoO >> %LOG% 2>&1
%copy% examples\DemoO\*.bat %P_out%\examples\DemoO >> %LOG% 2>&1
%copy% examples\DemoO\*.cfg %P_out%\examples\DemoO >> %LOG% 2>&1
%copy% examples\DemoO\*.zip %P_out%\examples\DemoO >> %LOG% 2>&1

mkdir %P_out%\examples\glfw  >> %LOG% 2>&1
%xcopy% examples\glfw %P_out%\examples\glfw\ >> %LOG% 2>&1
%copy% examples\GLFW-2.5.txt %P_out%\examples >> %LOG% 2>&1



%copy% CHANGELOG.txt %P_out% >> %LOG% 2>&1
%copy% CONTRIBUTERS.txt %P_out% >> %LOG% 2>&1
%copy% BUILDING.txt %P_out% >> %LOG% 2>&1
xcopy /Y /H *.sln %P_out% >> %LOG% 2>&1
xcopy /Y /H *.suo %P_out% >> %LOG% 2>&1

GOTO END

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
endlocal
:END
IF "%1" == "SKIP" exit
