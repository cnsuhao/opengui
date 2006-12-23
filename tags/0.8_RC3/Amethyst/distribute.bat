@echo off

IF EXIST ..\bin\Amethyst_d.dll (
	copy ..\bin\Amethyst_d.dll ..\Renderers\OpenGL\bin\
	copy ..\bin\Amethyst_d.dll ..\Renderers\Ogre\bin\Debug\
)

IF EXIST ..\bin\Amethyst_d.pdb (
	copy ..\bin\Amethyst_d.pdb ..\Renderers\OpenGL\bin\
	copy ..\bin\Amethyst_d.pdb ..\Renderers\Ogre\bin\Debug\
)

IF EXIST ..\bin\Amethyst.dll (
	copy ..\bin\Amethyst.dll ..\Renderers\OpenGL\bin\
	copy ..\bin\Amethyst.dll ..\Renderers\Ogre\bin\Release\
)

IF EXIST ..\bin\Amethyst.pdb (
	copy ..\bin\Amethyst.pdb ..\Renderers\OpenGL\bin\
	copy ..\bin\Amethyst.pdb ..\Renderers\Ogre\bin\Release\
)
