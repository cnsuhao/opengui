@echo off
setlocal

echo Fixing Renderer_OpenGL
call tools\style.bat Renderer_OpenGL\*.h Renderer_OpenGL\*.cpp > nul

echo Fixing Renderer_Ogre
call tools\style.bat Renderer_Ogre\*.h Renderer_Ogre\*.cpp > nul

echo Fixing OpenGUI
call tools\style.bat OpenGUI\*.h OpenGUI\*.cpp > nul

echo Cleaning Up
del /s *.orig > nul

endlocal
pause