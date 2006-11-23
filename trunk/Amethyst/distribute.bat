@echo off

IF EXIST ..\bin\Amethyst_d.dll (
	copy ..\bin\Amethyst_d.dll ..\Renderers\OpenGL\bin\
)

IF EXIST ..\bin\Amethyst_d.pdb (
	copy ..\bin\Amethyst_d.pdb ..\Renderers\OpenGL\bin\
)

IF EXIST ..\bin\Amethyst.dll (
	copy ..\bin\Amethyst.dll ..\Renderers\OpenGL\bin\
)

IF EXIST ..\bin\Amethyst.pdb (
	copy ..\bin\Amethyst.pdb ..\Renderers\OpenGL\bin\
)
