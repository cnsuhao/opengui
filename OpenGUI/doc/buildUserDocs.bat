@echo Building HTML Docs...
@"C:\Program Files\doxygen\bin\doxygen.exe" DoxyfileUsers > buildLogUsers.txt 2>&1
@echo Compiling CHM...
@"c:\Program Files\HTML Help Workshop\hhc.exe" html-users\index.hhp >> buildLogUsers.txt 2>&1
@echo DONE!