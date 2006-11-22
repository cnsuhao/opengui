@echo off
mkdir Debug
mkdir Release

set OgreSDKdir=%OGRE_HOME_vc8%

copy DemoO.zip Debug\
copy DemoO.zip Release\
copy resources.cfg Debug\
copy resources.cfg Release\
copy Plugins.cfg Debug\
copy Plugins.cfg Release\

copy ..\..\Debug\OpenGUI_d.dll Debug\
copy ..\..\Release\OpenGUI.dll Release\
copy ..\..\Debug\Renderer_Ogre_d.dll Debug\
copy ..\..\Release\Renderer_Ogre.dll Release\
copy ..\bin\TachometerWidget_d.dll Debug\
copy ..\bin\TachometerWidget.dll Release\

rem Copy Ogre Debug
copy %OgreSDKdir%\bin\debug\cg.dll Debug\
copy %OgreSDKdir%\bin\debug\DevIL.dll Debug\
copy %OgreSDKdir%\bin\debug\ILU.dll Debug\
copy %OgreSDKdir%\bin\debug\ILUT.dll Debug\
copy %OgreSDKdir%\bin\debug\zlib1.dll Debug\
copy %OgreSDKdir%\bin\debug\OgreMain_d.dll Debug\
copy %OgreSDKdir%\bin\debug\OgrePlatform_d.dll Debug\
copy %OgreSDKdir%\bin\debug\Plugin_CgProgramManager.dll Debug\
copy %OgreSDKdir%\bin\debug\Plugin_ParticleFX.dll Debug\
copy %OgreSDKdir%\bin\debug\Plugin_OctreeSceneManager.dll Debug\
copy %OgreSDKdir%\bin\debug\Plugin_BSPSceneManager.dll Debug\
copy %OgreSDKdir%\bin\debug\RenderSystem_Direct3D9.dll Debug\
copy %OgreSDKdir%\bin\debug\RenderSystem_GL.dll Debug\
copy %OgreSDKdir%\media\packs\OgreCore.zip Debug\

rem Copy Ogre Release
copy %OgreSDKdir%\bin\release\cg.dll Release\
copy %OgreSDKdir%\bin\release\DevIL.dll Release\
copy %OgreSDKdir%\bin\release\ILU.dll Release\
copy %OgreSDKdir%\bin\release\ILUT.dll Release\
copy %OgreSDKdir%\bin\release\zlib1.dll Release\
copy %OgreSDKdir%\bin\release\OgreMain.dll Release\
copy %OgreSDKdir%\bin\release\OgrePlatform.dll Release\
copy %OgreSDKdir%\bin\release\Plugin_CgProgramManager.dll Release\
copy %OgreSDKdir%\bin\release\Plugin_ParticleFX.dll Release\
copy %OgreSDKdir%\bin\release\Plugin_OctreeSceneManager.dll Release\
copy %OgreSDKdir%\bin\release\Plugin_BSPSceneManager.dll Release\
copy %OgreSDKdir%\bin\release\RenderSystem_Direct3D9.dll Release\
copy %OgreSDKdir%\bin\release\RenderSystem_GL.dll Release\
copy %OgreSDKdir%\media\packs\OgreCore.zip Release\
