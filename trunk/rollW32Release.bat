@echo off

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
echo Building Source Release...
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

echo.
echo Update the Installer Script now, then
pause
echo Building install script...
set INSTALLER="C:\Program Files\Caphyon\Advanced Installer\AdvancedInstaller.com"
%INSTALLER% /build sdkInstaller.aip

echo .
echo .
echo NOW YOU JUST NEED TO
echo * Check the sdk build log for build errors.
echo * Place the winSRC directory in a zip file with an appropriate name.
echo * Upload the new zip file and the sdk installer to SF.net and publish the release.
echo * Post a release announcement on the OpenGUI website (opengui.rightbracket.com)
echo * Post a release announcement on the Ogre forums (www.ogre3d.org)
pause
