@echo off

IF EXIST ..\bin\TachometerWidget_d.dll (
	copy ..\bin\TachometerWidget_d.dll ..\Renderers\OpenGL\bin\
)

IF EXIST ..\bin\TachometerWidget_d.pdb (
	copy ..\bin\TachometerWidget_d.pdb ..\Renderers\OpenGL\bin\
)

IF EXIST ..\bin\TachometerWidget.dll (
	copy ..\bin\TachometerWidget.dll ..\Renderers\OpenGL\bin\
)

IF EXIST ..\bin\TachometerWidget.pdb (
	copy ..\bin\TachometerWidget.pdb ..\Renderers\OpenGL\bin\
)
