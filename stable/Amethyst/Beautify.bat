@echo off
setlocal

del *.orig > nul
echo Fixing Amethyst
call ..\tools\style.bat *.h *.cpp > nul

echo Cleaning Up
del *.orig > nul

endlocal
pause
