@echo off
REM This should take care of all DLLs across all build types.
del /S *.dll

REM And this cleans out the OgreCore.zip
del Debug\OgreCore.zip
del Release\OgreCore.zip

REM remove the DemoO resource zip
del Debug\DemoO.zip
del Release\DemoO.zip

REM delete resources.cfg and plugins.cfg
del Debug\*.cfg
del Release\*.cfg
