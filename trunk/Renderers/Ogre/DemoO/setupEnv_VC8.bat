@echo off
mkdir Debug
mkdir Release

set OgreSDKdir=%OGRE_HOME_vc8%

copy DemoO.zip ..\bin\Debug\
copy DemoO.zip ..\bin\Release\
copy resources.cfg ..\bin\Debug\
copy resources.cfg ..\bin\Release\
copy Plugins.cfg ..\bin\Debug\
copy Plugins.cfg ..\bin\Release\


rem Copy Ogre Debug
copy %OgreSDKdir%\bin\debug\cg.dll ..\bin\Debug\
copy %OgreSDKdir%\bin\debug\DevIL.dll ..\bin\Debug\
copy %OgreSDKdir%\bin\debug\ILU.dll ..\bin\Debug\
copy %OgreSDKdir%\bin\debug\ILUT.dll ..\bin\Debug\
copy %OgreSDKdir%\bin\debug\zlib1.dll ..\bin\Debug\
copy %OgreSDKdir%\bin\debug\OgreMain_d.dll ..\bin\Debug\
copy %OgreSDKdir%\bin\debug\OgrePlatform_d.dll ..\bin\Debug\
copy %OgreSDKdir%\bin\debug\Plugin_CgProgramManager.dll ..\bin\Debug\
copy %OgreSDKdir%\bin\debug\Plugin_ParticleFX.dll ..\bin\Debug\
copy %OgreSDKdir%\bin\debug\Plugin_OctreeSceneManager.dll ..\bin\Debug\
copy %OgreSDKdir%\bin\debug\Plugin_BSPSceneManager.dll ..\bin\Debug\
copy %OgreSDKdir%\bin\debug\RenderSystem_Direct3D9.dll ..\bin\Debug\
copy %OgreSDKdir%\bin\debug\RenderSystem_GL.dll ..\bin\Debug\
copy %OgreSDKdir%\media\packs\OgreCore.zip ..\bin\Debug\

rem Copy Ogre Release
copy %OgreSDKdir%\bin\release\cg.dll ..\bin\Release\
copy %OgreSDKdir%\bin\release\DevIL.dll ..\bin\Release\
copy %OgreSDKdir%\bin\release\ILU.dll ..\bin\Release\
copy %OgreSDKdir%\bin\release\ILUT.dll ..\bin\Release\
copy %OgreSDKdir%\bin\release\zlib1.dll ..\bin\Release\
copy %OgreSDKdir%\bin\release\OgreMain.dll ..\bin\Release\
copy %OgreSDKdir%\bin\release\OgrePlatform.dll ..\bin\Release\
copy %OgreSDKdir%\bin\release\Plugin_CgProgramManager.dll ..\bin\Release\
copy %OgreSDKdir%\bin\release\Plugin_ParticleFX.dll ..\bin\Release\
copy %OgreSDKdir%\bin\release\Plugin_OctreeSceneManager.dll ..\bin\Release\
copy %OgreSDKdir%\bin\release\Plugin_BSPSceneManager.dll ..\bin\Release\
copy %OgreSDKdir%\bin\release\RenderSystem_Direct3D9.dll ..\bin\Release\
copy %OgreSDKdir%\bin\release\RenderSystem_GL.dll ..\bin\Release\
copy %OgreSDKdir%\media\packs\OgreCore.zip ..\bin\Release\
