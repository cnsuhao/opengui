@del /S *.ilk
@del /S *.a
@del /S *.obj
@rem del /S *.dll

del /S /F dependancies\tinyxml\Debug\*.*
del /S /F dependancies\tinyxml\Release\*.*

del /S /F dependancies\corona\Debug\*.*
del /S /F dependancies\corona\Release\*.*

del /S /F Debug\ *.*
del /S /F Release\*.*

del /S /F OgreFusion\Release\*.*
del /S /F OgreFusion\Debug\*.*

del /S /F examples\Demo1\Debug\*.*
del /S /F examples\Demo1\Release\*.*

del /S /F examples\DemoO\Debug\*.*
del /S /F examples\DemoO\Release\*.*

del /S /F examples\TachometerWidget\Debug\*.*
del /S /F examples\TachometerWidget\Release\*.*

cd examples\DemoO
cleanEnv.bat
cd ..\..
