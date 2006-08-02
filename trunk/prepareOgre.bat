@echo off
setlocal
set LOG=autoBuildLog.txt
cd ..
IF "%1" == "VC71" GOTO VC71
IF "%1" == "VC8" GOTO VC8
GOTO BADCMD


:VC71
echo Selected VC 7.1 Build
echo Selected VC 7.1 Build > %LOG% 2>&1
set VCVARS="C:\Program Files\Microsoft Visual Studio .NET 2003\Common7\Tools\vsvars32.bat"
set VCSOL="Ogre.sln"
GOTO DOIT

:VC8
echo Selected VC 8 Build
echo Selected VC 8 Build > %LOG% 2>&1
set VCVARS="C:\Program Files\Microsoft Visual Studio 8\Common7\Tools\vsvars32.bat"
set VCSOL="Ogre_vc8.sln"
GOTO DOIT


:DOIT
call %VCVARS% >> %LOG% 2>&1
echo Cleaning Ogre...
echo ################ >> %LOG% 2>&1
echo ### CLEANING ### >> %LOG% 2>&1
echo ################ >> %LOG% 2>&1
echo ############################################### >> %LOG% 2>&1
echo    ...Debug
devenv %VCSOL% /clean "Debug" >> %LOG%
echo    ...Release
devenv %VCSOL% /clean "Release" >> %LOG%

echo Building Ogre...
echo ################ >> %LOG% 2>&1
echo ### BUILDING ### >> %LOG% 2>&1
echo ################ >> %LOG% 2>&1
echo ############################################### >> %LOG% 2>&1

echo    ...Debug
devenv %VCSOL% /build "Debug" >> %LOG%
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! >> %LOG% 2>&1
echo !!!!!!!!!!!!!!!!!!! >> %LOG% 2>&1
echo !!!  END DEBUG  !!! >> %LOG% 2>&1
echo !!!!!!!!!!!!!!!!!!! >> %LOG% 2>&1

echo    ...Release
devenv %VCSOL% /build "Release" >> %LOG%
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! >> %LOG% 2>&1
echo !!!!!!!!!!!!!!!!!!! >> %LOG% 2>&1
echo !!! END RELEASE !!! >> %LOG% 2>&1
echo !!!!!!!!!!!!!!!!!!! >> %LOG% 2>&1

GOTO END

:BADCMD
echo You need to specify either VC71 or VC8 as a parameter.
pause
GOTO END

:END
endlocal
