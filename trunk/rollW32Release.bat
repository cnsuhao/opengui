@echo off
set MAKENSIS="C:\Program Files\NSIS\makensis.exe"
echo BEFORE CONTINUING, PERFORM THESE STEPS!
echo * CLOSE VISUAL STUDIO! (and please leave it in a sane state...)
echo * Did you update the ChangeLog.txt?
echo * Make sure both doxygen config files have the correct version number set.
echo * Make sure that OpenGUI.h has the correct version number set.
echo * Update the NSIS script (win32sdkInstaller.nsi) to reflect the new ver number.
echo .
echo = Note: You need to have Ogre setup and compiled correctly for OgreFusion SDK =
echo When you're done with all of that, press a key and come back in an hour.
pause




echo .
echo Cleaning Slate...
start /WAIT CleanAll.bat SKIP
echo DONE: Clean Slate!


echo .
echo Preparing Source Release...
start /WAIT buildSRC_W32.bat SKIP
echo DONE: Building Source Release



echo .
echo Building SDK Release (VC 7.1)...
start /WAIT buildSDK_W32_VC71.bat SKIP
echo DONE: Building SDK Release (VC 7.1)


echo .
echo Building SDK Release (VC 8)...
start /WAIT buildSDK_W32_VC8.bat SKIP
echo DONE: Building SDK Release (VC 8)


echo Generating documentation...
rem OpenGUI Docs
cd OpenGUI\doc
rmdir /Q /S html
call buildDocs.bat
call buildUserDocs.bat
cd ..\..
rem OgreFusion docs
cd OgreFusion\doc
rmdir /Q /S html
call buildDocs.bat
cd ..\..
copy /Y OpenGUI\doc\OpenGUI.chm win32rel
copy /Y OgreFusion\doc\OgreFusion.chm win32rel
copy /Y CHANGELOG.txt win32rel
copy /Y CONTRIBUTERS.txt win32rel
copy /Y OpenGUI\LICENSE.txt win32rel
echo.
echo Now check all build logs for any issues. Next operation builds the package.
pause
echo Building install script...
%MAKENSIS% sdkInstaller.nsi

echo .
echo .
echo NOW YOU JUST NEED TO
echo * Check the sdk build log for build errors.
echo * Place the winSRC directory in a zip file with an appropriate name.
echo * Upload the new zip file and the sdk installer to SF.net and publish the release.
echo * Post a release announcement on the OpenGUI website (opengui.rightbracket.com)
echo * Post a release announcement on the Ogre forums (www.ogre3d.org)
pause
