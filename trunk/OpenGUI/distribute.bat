@echo off

IF EXIST ..\bin\OpenGUI_d.dll (
	copy ..\bin\OpenGUI_d.dll ..\Renderers\OpenGL\bin\
	copy ..\bin\OpenGUI_d.dll ..\Renderers\Ogre\bin\Debug\
)

IF EXIST ..\bin\OpenGUI_d.pdb (
	copy ..\bin\OpenGUI_d.pdb ..\Renderers\OpenGL\bin\
	copy ..\bin\OpenGUI_d.pdb ..\Renderers\Ogre\bin\Debug\
)

IF EXIST ..\bin\OpenGUI.dll (
	copy ..\bin\OpenGUI.dll ..\Renderers\OpenGL\bin\
	copy ..\bin\OpenGUI.dll ..\Renderers\Ogre\bin\Release\
)

IF EXIST ..\bin\OpenGUI.pdb (
	copy ..\bin\OpenGUI.pdb ..\Renderers\OpenGL\bin\
	copy ..\bin\OpenGUI.pdb ..\Renderers\Ogre\bin\Release\
)
