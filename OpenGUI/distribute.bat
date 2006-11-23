@echo off

IF EXIST ..\bin\OpenGUI_d.dll (
	copy ..\bin\OpenGUI_d.dll ..\Renderers\OpenGL\bin\
)

IF EXIST ..\bin\OpenGUI_d.pdb (
	copy ..\bin\OpenGUI_d.pdb ..\Renderers\OpenGL\bin\
)

IF EXIST ..\bin\OpenGUI.dll (
	copy ..\bin\OpenGUI.dll ..\Renderers\OpenGL\bin\
)

IF EXIST ..\bin\OpenGUI.pdb (
	copy ..\bin\OpenGUI.pdb ..\Renderers\OpenGL\bin\
)
