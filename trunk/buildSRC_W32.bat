@echo off

set P_tmp="..\winSRC"
set P_="OpenGUIsrc"
set PI_exbin="examples\bin"
set P_doc="OpenGUI\doc"


rem
rem Delete any previous SRC data
rem
rmdir /s /q %P_% > NUL 2>&1
rmdir /s /q %P_tmp% > NUL 2>&1

echo Build directory tree...
xcopy /E * %P_tmp%\ > NUL 2>&1
move %P_tmp% %P_% > NUL 2>&1

echo Cleaning source tree...
cd %P_%
del /S *.ilk > NUL 2>&1
del *.ncb > NUL 2>&1
rmdir /Q /S dependancies\corona-linux > NUL 2>&1
del *.bat *.nsi > NUL 2>&1
rmdir /Q /S OpenGUI\doc > NUL 2>&1
rmdir /Q /S Debug > NUL 2>&1
rmdir /Q /S Release > NUL 2>&1
del %PI_exbin%\*.pdb %PI_exbin%\*.dll %PI_exbin%\*.log > NUL 2>&1
cd..


echo Including documentation...
cd %P_doc%
call buildDocs.bat
call buildUserDocs.bat
cd ..\..
copy %P_doc%\OpenGUI_INTERNAL.chm %P_%\ > NUL 2>&1
copy %P_doc%\OpenGUI.chm %P_%\ > NUL 2>&1
