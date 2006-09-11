@echo off
setlocal

echo Fixing OpenGUI_OGLRenderer
call tools\style.bat OpenGUI_OGLRenderer\*.h OpenGUI_OGLRenderer\*.cpp > nul

echo Fixing OgreFusion
call tools\style.bat OgreFusion\*.h OgreFusion\*.cpp > nul

echo Fixing OpenGUI
call tools\style.bat OpenGUI\*.h OpenGUI\*.cpp > nul

endlocal
pause