@echo off

echo BEFORE CONTINUING, PERFORM THESE STEPS!
echo * Did you update the ChangeLog.txt?
echo * Make sure both doxygen config files have the correct version number set.
echo * Make sure that OpenGUI.h has the correct version number set.
echo * Update the NSIS script (win32sdkInstaller.nsi) to reflect the new version number.
echo .
echo When you're done with all of that, press a key and come back in 10 minutes.
pause

start /WAIT buildSRC_W32.bat SKIP
start /WAIT buildSDK_W32.bat SKIP

set NSIS="C:\Program Files\NSIS\makensis.exe"
%NSIS% win32sdkInstaller.nsi

echo .
echo .
echo NOW YOU JUST NEED TO
echo * Check the sdk build log for build errors.
echo * Place the winSRC directory in a zip file with an appropriate name.
echo * Upload the new zip file and the sdk installer to SF.net and publich the release.
echo * Post a release article on the OpenGUI website (opengui.sf.net)
pause
