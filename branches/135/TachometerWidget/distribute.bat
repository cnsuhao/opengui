@echo off

IF EXIST ..\bin\TachometerWidget_d.dll (
	copy ..\bin\TachometerWidget_d.dll ..\Renderers\OpenGL\bin\
	copy ..\bin\TachometerWidget_d.dll ..\Renderers\Ogre\bin\Debug\
)

IF EXIST ..\bin\TachometerWidget_d.pdb (
	copy ..\bin\TachometerWidget_d.pdb ..\Renderers\OpenGL\bin\
	copy ..\bin\TachometerWidget_d.pdb ..\Renderers\Ogre\bin\Debug\
)

IF EXIST ..\bin\TachometerWidget.dll (
	copy ..\bin\TachometerWidget.dll ..\Renderers\OpenGL\bin\
	copy ..\bin\TachometerWidget.dll ..\Renderers\Ogre\bin\Release\
)

IF EXIST ..\bin\TachometerWidget.pdb (
	copy ..\bin\TachometerWidget.pdb ..\Renderers\OpenGL\bin\
	copy ..\bin\TachometerWidget.pdb ..\Renderers\Ogre\bin\Release\
)
