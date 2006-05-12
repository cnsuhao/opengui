@echo off
rem
rem Delete any previous SDK data
rem
rmdir /s /q winSDK > NUL 2>&1

set P_="winSDK"
set P_OG="winSDK\OpenGUI"
set P_OGinc="winSDK\OpenGUI\include"
set P_OGlib="winSDK\OpenGUI\lib"
set P_OGLinc="winSDK\OGLRenderer\include"
set P_OGLlib="winSDK\OGLRenderer\lib"
set P_TACHinc="winSDK\Tachometer\include"
set P_TACHlib="winSDK\Tachometer\lib"
set P_demo="winSDK\Demos"

echo Build directory tree...
mkdir %P_OGinc%
mkdir %P_OGlib%

mkdir %P_OGLinc%
mkdir %P_OGLlib%

mkdir %P_TACHinc%
mkdir %P_TACHlib%

mkdir %P_demo%

echo Copying OpenGUI files...
copy OpenGUI\LICENSE.TXT %P_OG% > NUL 2>&1
copy OpenGUI\*.h %P_OGinc% > NUL 2>&1
copy Debug\OpenGUI_d.lib %P_OGlib% > NUL 2>&1
copy Debug\OpenGUI_d.dll %P_OGlib% > NUL 2>&1
copy Release\OpenGUI.lib %P_OGlib% > NUL 2>&1
copy Release\OpenGUI.dll %P_OGlib% > NUL 2>&1
copy OpenGUI\*.h %P_OGinc% > NUL 2>&1

echo Copying OpenGL Renderer files...
copy OpenGUI_OGLRenderer\*.h %P_OGLinc% > NUL 2>&1
copy Release\OpenGUI_OGLRenderer.lib %P_OGLlib% > NUL 2>&1
copy Debug\OpenGUI_OGLRenderer_d.lib %P_OGLlib% > NUL 2>&1

echo Copying Tachometer files
copy examples\TachometerWidget\*.h %P_TACHinc% > NUL 2>&1
copy examples\bin\TachometerWidget.dll %P_TACHlib% > NUL 2>&1
copy examples\bin\TachometerWidget.lib %P_TACHlib% > NUL 2>&1
copy examples\bin\TachometerWidget_d.dll %P_TACHlib% > NUL 2>&1
copy examples\bin\TachometerWidget_d.lib %P_TACHlib% > NUL 2>&1

echo Copying Demos...
copy examples\bin\licenses.txt %P_demo% > NUL 2>&1
copy examples\bin\pecot.ttf %P_demo% > NUL 2>&1
copy examples\bin\kongtext.ttf %P_demo% > NUL 2>&1
copy examples\bin\TachometerWidget.dll %P_demo% > NUL 2>&1
copy examples\bin\tachometer.png %P_demo% > NUL 2>&1
copy examples\bin\tachometer.xml %P_demo% > NUL 2>&1
copy examples\bin\metal.png %P_demo% > NUL 2>&1
copy examples\bin\metal.xml %P_demo% > NUL 2>&1
copy examples\bin\OpenGUI.dll %P_demo% > NUL 2>&1
copy examples\bin\demo1.xml %P_demo% > NUL 2>&1
copy examples\bin\Demo1.exe %P_demo% > NUL 2>&1

copy OpenGUI\doc\OpenGUI.chm %P_% > NUL 2>&1

