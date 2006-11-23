setlocal
@del /S *.ilk > NUL 2>&1
@del /S *.a > NUL 2>&1
@del /S *.obj > NUL 2>&1
@rem del /S *.dll > NUL 2>&1

del /Q /F dependancies\tinyxml\Debug\*.* > NUL 2>&1
del /Q /F dependancies\tinyxml\Release\*.* > NUL 2>&1

del /Q /F dependancies\corona\Debug\*.* > NUL 2>&1
del /Q /F dependancies\corona\Release\*.* > NUL 2>&1

del /Q /F Debug\*.* > NUL 2>&1
del /Q /F Release\*.* > NUL 2>&1

del /Q /F OgreFusion\Release\*.* > NUL 2>&1
del /Q /F OgreFusion\Debug\*.* > NUL 2>&1

del /Q /F examples\Demo1\Debug\*.* > NUL 2>&1
del /Q /F examples\Demo1\Release\*.* > NUL 2>&1

del /Q /F examples\DemoO\Debug\*.* > NUL 2>&1
del /Q /F examples\DemoO\Release\*.* > NUL 2>&1

del /Q /F examples\TachometerWidget\Debug\*.* > NUL 2>&1
del /Q /F examples\TachometerWidget\Release\*.* > NUL 2>&1

cd examples\DemoO
call cleanEnv.bat
cd ..\..
endlocal

GOTO END
:END
IF "%1" == "SKIP" exit
pause